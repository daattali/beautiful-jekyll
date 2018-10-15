---
layout: post
title: Kubernetes, pierwszy cluster
image: /img/2018-10-15-kubernetes-pierwszy-cluster/kubernetes-logo.png
tags: [docker, kontenery, kubernetes, okiestracja, vps, linux]
---

Ten artykuł będzie poświęcony temu jak rozpocząć tworzenie klastra kubernetes używając taniego VPS. Będzie to środowisko, w którym możemy uruchomić nasze projekty, hostować portfolio, czy testować rozwiązania. Artykuł będzie zawierał listę kroków, pozwalającą uruchomić działający klaster z dostępem do niego z poziomu linii komend, jak i interfejsu graficznego. 

## Przygotowanie
Do stworzenie klastra będziemy potrzebować
* Jeden tani VPS - Ja użyje serwera o 4xCPU, 8GB RAM, 40GB ssd, oczywiście mogą być słabsze.

{: .box-error}
**Ważne:** VPS musi być w technologi np. KVM. OpenVZ nie nadają się ze względu na współdzielone jądro, co powoduje najczęściej problemy z brakującymi modułami.
* Możliwość instalacji systemu z obrazem Ubuntu
* Trochę wolnego czasu i dostęp do internetu

## Instalacja niezbędnych narzędzi

Gdy już mamy serwery z czystym, aktualnym Ubuntu na pokładzie możemy przejść do instalacji.

Zaczynamy od zainstalowania potrzebnych paczek systemowych:

{% highlight bash linenos %}
apt-get install apt-transport-https ca-certificates curl software-properties-common
{% endhighlight %}

Dodajemy klucze gpg do repozytoriów Docker i Kubernetesa:

{% highlight bash linenos %}
#Klucz Docker
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
#Klucz Kubernetes
curl -fsSL https://packages.cloud.google.com/apt/doc/apt-key.gpg | apt-key add -
{% endhighlight %}

Dodajemy repozytorium do apt i instalujemy potrzebne składowe naszego klastra:

{% highlight bash linenos %}
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
cat <<EOF >/etc/apt/sources.list.d/kubernetes.list
deb http://apt.kubernetes.io/ kubernetes-xenial main
EOF
apt-get update
apt-get install -y docker-ce kubelet kubeadm kubernetes-cni
{% endhighlight %}

Przed dalszym etapem prac zostało nam tylko jedno.

Wyłączenie swap. Można to zrobić poleceniem.

{% highlight bash linenos %}
swapoff -a
{% endhighlight %}

## Uruchomienie klastra

Klaster uruchamiamy za pomocą komendy.

{% highlight bash linenos %}
kubeadm init
{% endhighlight %}

Pod koniec instalacji dostajemy polecenie do podłączania nowych serwerów do klastra. Warto ją sobie zapisać. Wygląda następująco:

{% highlight bash linenos %}
kubeadm join 112.218.178.128:6443 --token arsv8l.hjse61jkrocyve49 --discovery-token-ca-cert-hash sha256:c0d68edd20fc539db23f35d935d1e40276895b465a852cb78e83da6335986def
{% endhighlight %}

## Konfiguracja klienta

Na maszynie lokalnej jest nam potrzebne narzędzie kubectl. Instalacja jest bardzo dobrze opisana w [dokumentacji Kubernetesa](https://kubernetes.io/docs/tasks/tools/install-kubectl/). Odsyłam do niej w tym celu.

Musimy je skonfigurować. Klaster generuje plik, który wystarczy skopiować do katalogu ~/.kube

{% highlight bash linenos %}
scp user@112.218.178:/etc/kubernetes/admin.conf ~/.kube/config
{% endhighlight %}

## Master musi być workerem.

Standardowo master kubernetesa ma zablokowaną możliwość uruchamiania na nim podów. Jeśli twój klaster to więcej niż jeden serwer to możesz to pominąć.
Jednak jeśli tak jak ja robisz wszystko na jednym serwerze, to trzeba z poziomu maszyny klient wykonać polecenie:

{% highlight bash linenos %}
kubectl taint nodes --all node-role.kubernetes.io/master-
{% endhighlight %}

## Wybieramy sieć

Teraz musimy podjąć bardzo ważną decyzję, jakiego providera sieci wybierzemy. Ja ze swojej strony polecam Weave ze względu na bardzo fajny dashboard.
Konfigurujemy sieć po stronie systemu operacyjnego
{% highlight bash linenos %}
sudo sysctl net.bridge.bridge-nf-call-iptables=1
echo "net.bridge.bridge-nf-call-iptables=1" >> /etc/sysctl.conf
{% endhighlight %}

Instalujemy weave za pomocą kubectl z poziomu maszyny klienckiej.

{% highlight bash linenos %}
$ kubectl apply -f "https://cloud.weave.works/k8s/net?k8s-version=$(kubectl version | base64 | tr -d '\n')"

serviceaccount/weave-net created
clusterrole.rbac.authorization.k8s.io/weave-net created
clusterrolebinding.rbac.authorization.k8s.io/weave-net created
role.rbac.authorization.k8s.io/weave-net created
rolebinding.rbac.authorization.k8s.io/weave-net created
daemonset.extensions/weave-net created

{% endhighlight %}

Od tej chwili mamy już pełno prawny działający klaster Kubernetes.

## Bo GUI też jest ważne.

Pierwszą rzeczą do zrobienia jest instalacja Dashboardu. Jest to bardzo przydatne i wygodne narzędzie.

{% highlight bash linenos %}
kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/master/src/deploy/recommended/kubernetes-dashboard.yaml
{% endhighlight %}

Ostatnia rzecz to stworzenie użytkownika, który będzie miał uprawnienia do używania z tego narzędzia.

admin-user.yaml
{% highlight yaml linenos %}
apiVersion: v1
kind: ServiceAccount
metadata:
name: admin
namespace: kube-system
---
apiVersion: rbac.authorization.k8s.io/v1beta1
kind: ClusterRoleBinding
metadata:
name: admin
roleRef:
apiGroup: rbac.authorization.k8s.io
kind: ClusterRole
name: cluster-admin
subjects:
- kind: ServiceAccount
name: admin
namespace: kube-system
---
{% endhighlight %}

{% highlight bash linenos %}
kubectl create -f admin-user.yaml
{% endhighlight %}

Gdy mamy stworzonego użytkownika możemy pobrać jego token i użyć do zalogowania się w Dashboard

{% highlight bash linenos %}
kubectl -n kube-system describe secret $(kubectl -n kube-system get secret | grep admin | awk '{print $1}')
{% endhighlight %}

Żeby się zalogować do Dashbordu trzeba uruchomić proxy

{% highlight bash linenos %}
kubectl proxy
{% endhighlight %}

Aplikacja będzie dostępna pod adresem proxy, które właśnie zostało uruchomione:
[http://localhost:8001/api/v1/namespaces/kube-system/services/https:kubernetes-dashboard:/proxy/](http://localhost:8001/api/v1/namespaces/kube-system/services/https:kubernetes-dashboard:/proxy/)

Należy wybrać token jako forma uwierzytelnienia i wkleić go w pole tekstowe.
![Dashboard](/img/2018-10-15-kubernetes-pierwszy-cluster/kubernetes-dashboard.jpg)

Po zalogowaniu zobaczymy nasz dashboard gdzie możemy robić wszystko tak samo, jak przez kubectl.

![Dashboard](/img/2018-10-15-kubernetes-pierwszy-cluster/kubernetes-dashboard.png)

W taki o to sposób mamy działający klaster Kubernetesa gotowy do uruchomienia pierwszej aplikacji.
