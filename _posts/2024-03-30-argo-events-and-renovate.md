---
layout: post
title: Start Renovate from a dashboard with Argo Events
date: 2024-03-30T11:00:20.305Z
---

Over the last few months I have been slowly adding features to my home setup (I don't call it a home lab). I have several services I use at home like Home Assistant, Zigbee2mqtt, ESPHome dashboard and many more, running on a K3s node (mini pc with core-i3 and 16GB of RAM). Everything is defined in yaml manifests stored in a private Github repo and reconciled in the Kubernetes cluster by ArgoCD. 

Like a lot of self-hosters, one of the things I run is [Homepage](https://github.com/gethomepage/homepage) dashboard. It is a great Open-Source dashboard project with yaml configuration, making it perfect for my Gitops setup.

I also use [Renovate](https://github.com/renovatebot/renovate) configured as a weekly cronjob to automatically open pull requests in my repo with the new image tags of the containers I use. This setup is great because I don't need to think about upgrades, I just check the PRs every Sunday and merge them if I'm happy with the changelogs. Note that **this blog doesn't explain how to setup Renovate**.

Running Renovate weekly is perfectly fine for my use case but, now and again, I want to run it manually for various reasons. The simple way to do it is to open my terminal, switch to the right kube context and create a new job from the existing cronjob (`kubectl create job --from=cronjob/renovate manualrun -n renovate`). This is perfectly fine but, being as lazy as I am, **I wanted a button to click on my dashboard to start Renovate**. 

There are various ways to do this, like [OliveTin](https://github.com/OliveTin/OliveTin), which is a web ui to start shell commands. While the project looks interesting, I wasn't too keen on giving Kubernetes API access to it or running commands on the node. As a result, I decided on using [Argo Events](https://argoproj.github.io/argo-events/) with a simple webhook.

## What is a webhook?

Webhooks are used everywhere, it means that something exposes an http endpoint, and when accessed on a specific path, an action is triggered. For instance, you could create a webhook in Home Assistant to turn on a light when accessed. So when you run `curl https://homeassistant.int.vxav.fr/turnonthelights`, the web server picks up the request and triggers the action.

This is what I am going to use here with Argo Events. The idea is to create a Renovate pod when I access `argo-events.int.vxav.fr/renovate`, which I can simple add as a button on my dashboard.

![renovate-webhook](renovate-webhook.png)

## Argo Events

Argo Events lets you run triggers (Kubernetes resources, service messages and [many more](https://argoproj.github.io/argo-events/concepts/trigger/)) based on an events (Github comment, release, webhook, schedule and [many more](https://argoproj.github.io/argo-events/concepts/event_source/)). The `Sensor` Custom Resource (CR) is what will link `Triggers` and `Events`. The same thing could be achieved with Tekton pipelines which work great (we automate our E2E testing at Giant Swarm with it), but I thought I'd stick with Argo since I already use ArgoCD for Gitops.

This was the super short summary of Argo Events but you can learn more about the components in the [documentation](https://argoproj.github.io/argo-events/concepts/architecture/).

Note that I am not using Argo Workflows here, only Argo Events. Argo Workflows can be triggered by Argo Events and are very powerful workflow engine for Kubernetes but way overkill for my simple use case.

![Argo Events](argo-events-diagram.png)

## Installation of Argo Events via ArgoCD

There are several ways to install Argo Events (manifests, kustomize or community maintained Helm chart). I am going to use the upstream kustomization to install all the components, you can find the other procedures in the [documentation](https://argoproj.github.io/argo-events/installation/).

Because I use ArgoCD to deploy resources to my clusters, I will be printing the manifests I have in my Gitops repo for Argo Events and the ArgoCD app for it.

### ArgoCD app

Having the ArgoCD app defined in the repo saves you from manually creating it in the UI. In my case, the file is stored under `/gitops/argocd/apps/argo-events.yaml` :

```yaml
apiVersion: argoproj.io/v1alpha1
kind: Application
metadata:
  name: argo-events
  namespace: argocd
spec:
  destination:
    namespace: argo-events
    server: https://kubernetes.default.svc
  project: default
  source:
    path: gitops/argo-events
    repoURL: git@github.com:vxav/home-automation.git
    targetRevision: main
  syncPolicy:
    automated:
      prune: true
      selfHeal: true
```

### Argo Events controllers and other components

I decided to use the upstream kustomization because I am not too keen on using community maintained Helm charts as these tend to become obsolete over time, and copying all the manifests in my repo isn't ideal for staying up to date. In my case, the structure looks like so:

```
└── gitops/
    └── argo-events/
        ├── event-source.yaml
        ├── ingress.yaml
        ├── kustomization.yaml
        ├── namespace.yaml
        └── sensor-renovate.yaml
```

- **kustomization.yaml**

The kustomization will apply the upstream manifests containing everything you need to run Argo Events, along with the other yaml files I created in the directory.

```yaml
apiVersion: kustomize.config.k8s.io/v1beta1
kind: Kustomization
namespace: argo-events

resources:
- github.com/argoproj/argo-events/manifests/cluster-install
- namespace.yaml
- sensor-renovate.yaml
- ingress.yaml
- event-source.yaml
```

- **namespace.yaml**

```yaml
apiVersion: v1
kind: Namespace
metadata:
  labels:
    kubernetes.io/metadata.name: argo-events
  name: argo-events
```

- **event-source.yaml**

The event source is how we create the webhook to listen on. In this case it will create a pod listening on port 12000 with a webhook at `/renovate` and `GET` method. So a simple curl command to the pod would return `success`. At this point the service is only accessible within the Kubernetes cluster so we'll need an ingress to be able to consume it from the LAN (next step).

```yaml
apiVersion: argoproj.io/v1alpha1
kind: EventSource
metadata:
  name: webhook
spec:
  service:
    ports:
      - port: 12000
        targetPort: 12000
  webhook:
    renovate:
      port: "12000"
      endpoint: /renovate
      method: GET
```

- **ingress.yaml**

My ingress is deployed as a Traefik IngressRoute custom resource (CR). The implementation will vary depending on your environment. The end result here is that I will be able to hit the `renovate` Argo Events webhook by simply browsing to `argo-events.int.vxav.fr/renovate`

In my case I use external-dns to create a CNAME record (`argo-events.int.vxav.fr`) that points to an A record (`ingress.int.vxav.fr`) which resolves to the IP of the service of type load balancer serving the ingress controller.

I also add a certificate CR from cert-manager to have https but I didn't include it here for better readability. I think there are ways to handle lets encrypt certificates within Traefik itself without cert-manager but I haven't gotten around looking into this yet.

```yaml
apiVersion: traefik.io/v1alpha1
kind: IngressRoute
metadata:
  annotations:
    external-dns.alpha.kubernetes.io/target: ingress.int.vxav.fr
    kubernetes.io/ingress.class: traefik
  name: argo-events
  namespace: argo-events
  labels:
    app: argo-events
spec:
  entryPoints:
    - websecure
  routes:
  - match: Host(`argo-events.int.vxav.fr`)
    kind: Rule
    services:
    - kind: Service
      name: webhook-eventsource-svc
      namespace: argo-events
      port: 12000
  tls:
    secretName: argo-events-cert
```

- **sensor-renovate.yaml**

The sensor instructs what Kubernetes resource to create when a specific dependency is accessed (webhook in our case).

As you can see, the `eventSourceName` and `eventName` point to the event source and webhook we created earlier. In the service account section, I used the embedded argo-events one as it has enough permissions (and it's one less thing to create). Finally, the `Trigger` section contains the definition of the pod to create. Note that the pod `name` spec has been replaced with `generateName` to get an automatically generated unique name.

The rest of the pod definition is essentially a copy of my cronjob.

As a first step, you can change this to a generic random pod for testing purpose.

```yaml
apiVersion: argoproj.io/v1alpha1
kind: Sensor
metadata:
  name: webhook
spec:
  template:
    serviceAccountName: argo-events-sa
  dependencies:
    - name: webhook-renovate
      eventSourceName: webhook
      eventName: renovate
  triggers:
    - template:
        name: start-renovate
        k8s:
          operation: create
          source:
            resource:
              apiVersion: v1
              kind: Pod
              metadata:
                generateName: renovate-webhooked-
                namespace: renovate
              spec:
                containers:
                - env:
                  - name: LOG_LEVEL
                    value: debug
                  - name: RENOVATE_REVIEWERS
                    value: vxav
                  - name: RENOVATE_PLATFORM
                    value: github
                  - name: RENOVATE_AUTODISCOVER
                    value: "false"
                  - name: RENOVATE_BASE_DIR
                    value: /tmp/renovate/
                  - name: RENOVATE_CONFIG_FILE
                    value: /opt/renovate/config.json
                  - name: RENOVATE_TOKEN
                    valueFrom:
                      secretKeyRef:
                        key: pat
                        name: renovate-gh-pat
                  image: renovate/renovate:37.267.1
                  imagePullPolicy: Always
                  name: renovate
                  terminationMessagePath: /dev/termination-log
                  terminationMessagePolicy: File
                  volumeMounts:
                  - mountPath: /opt/renovate/
                    name: config-volume
                  - mountPath: /tmp/renovate/
                    name: work-volume
                dnsPolicy: ClusterFirst
                restartPolicy: Never
                schedulerName: default-scheduler
                terminationGracePeriodSeconds: 30
                volumes:
                - configMap:
                    defaultMode: 420
                    name: renovate-config
                  name: config-volume
                - name: work-volume
```

### ArgoCD reconciliation

Once you merge all these into the repo, ArgoCD will create the Argo App.

![argo-events-app](argo-events-app.png)

which will then apply the resources in `/gitops/argo-events/` and install everything for you.

![argo-events-resources](argo-events-resources.png)

Once you observed that everything has been created successfully in the Kubernetes cluster, you can check that it works by accessing the webhook and it should start a Renovate pod.

```
curl https://argo-events.int.vxav.fr/renovate
success
```

This should start the Renovate pod in Kubernetes which will perhaps result in new PRs on the repo if new image tags are available.

```
> kubectl get pod -n renovate --watch
NAME                       READY   STATUS      RESTARTS   AGE
renovate-webhooked-g97hc   1/1     Running     0          118s
renovate-webhooked-g97hc   0/1     Completed   0          4m31s
```

![renovate-pr](renovate-pr.png)

## Adding a button in Homepage dashboard

Again, you may or may not be using Homepage but I'll go ahead and add it here anyway. Just generally speaking, since you can trigger the Renovate action by browsing to the specific url, you can add it wherever you will need it.

In the case of [Homepage](https://gethomepage.dev/latest/configs/services/), I stored the Renovate logo in my public repo and the config is in my `services.yaml`:

```yaml
- App Management:
    ...
    - Renovate:
        icon: https://avatars3.githubusercontent.com/u/38656520?s=400&v=4
        href: https://argo-events.int.vxav.fr/renovate
        description: Run Renovate (Argo Event webhook)
```

And this is what it looks like on the dashboard. It will now start a Renovate pod when I click on that button.

![renovate-in-homepage](renovate-in-homepage.png)

## Wrap up

As you can imagine, this is a pretty simple use case of using Argo Events at home to make my life a tiny bit easier but I can think of a lot of possibilities for this tool in the professional space, especially when paired with Argo Worflows or Tekton Pipelines.

I am yet to find more uses for this in my home setup but adding webhooks and triggers will now be straightforward. I can then add the interface to homepage, home assistant, a function in my zshrc profile. The possibilities for triggers are also very wide as you can craft whatever container you like to run specific actions.