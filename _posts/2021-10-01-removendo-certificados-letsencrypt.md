---
layout: post
title: Remoção de certificados expirados gerados pelo Let's Encrypt
subtitle: Reduza a quantidade de erros na hora da renovação
#gh-repo: rauhmaru/zabbix-docs
#gh-badge: [star, fork, follow]
tags: [lets encrypt, linux, shellscript]
comments: true
---

Lá na empresa, nós usamos um proxy reverso, e todos os endereços publicados para fora da nossa infraestrutura possuem um certificado digital válido, gerado através do Let’s Encrypt.

![let's encrypt](https://miro.medium.com/max/500/1*hU2wTKioVyyruVR0MXaQ4w.png)

Muitas vezes esses sites são para prover serviços para clientes, e como tudo na vida, um dia acaba.
Não nos interessa renovar os certificados de sites que já não mais constam no DNS externo ou mesmo na nossa infraestrutura. Então, como fazer para remover?
Primeiro, liste os seus certificados:

```shell
certbot-auto certificates
```

Depois, verifique o Campo Certificate Name, é ele que usaremos na remoção. Por exemplo, o seu site/certificado é o www.medium.com.br:

```
Certificate Name: www.medium.com.br
    Serial Number: 4ca9aed73543ac2933595bbb17cc671b08d
    Key Type: RSA
    Domains: www.medium.com.br
    Expiry Date: 2021-07-07 13:07:00+00:00 (VALID: 85 days)
    Certificate Path: /etc/letsencrypt/live/www.medium.com.br/fullchain.pem
    Private Key Path: /etc/letsencrypt/live/www.medium.com.br/privkey.pem
```

Com isso, fica fácil. É só executar o comando
```certbot-auto delete --cert-name www.medium.com.br``` 

## E dá pra melhorar?

Sim, podemos fazer um shellscript

```shell
#!/bin/bash
# Remoção de certificados expirados
CertsExpirados="certificados_expirados.txt"
# Liste os certificados expirados, e retorne o nome deles
certbot-auto certificates | grep -B4 EXPIRED \
| awk /Certificate\ Name/'{ print $NF}' >> $CertsExpirados
# Com os nomes dos certificados na mao, hora da remocao
for certificado in $(cat $Expirados); do
  certbot-auto delete --name $certificado
done
```

E é isso aí. Só precisa dar o enter pra confirmar a remoção de cada um.
Até a próxima.