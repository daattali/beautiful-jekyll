---
layout: post
published: true
title: '¿Como mantener actualizado el entorno de múltiples desarrolladores?'
subtitle: git hooks
date: '2018-09-02'
image: /assets/img/git-logo.png
share-img: /assets/img/git-hooks.jpg
tags: [devops, git]
---

Vuelven de vacaciones a la oficina y se encuentran con decenas de correos, y entre ellos alguno sobre actualizar "*X*" variable de entorno, o sobre la creación de un nuevo microservicio por lo que debes actualizar tu ```/etc/hosts``` con el nuevo dominio. Naturalmente, seguir esta "metodología" mantiene altas las probabilidades de dejar pasar accidentalmente algunos de estos correos y luego pasar horas averiguando porque "sin ninguna razón aparente" cierto proyecto ha dejado de funcionar.

*Disclaimer: Sabemos que hay otras posibles soluciones (vía DNS, por ejemplo), no digo que ésta sea la única o la mejor, solo que es una posibilidad más. Que no solo se limita al caso acá expuesto, sino a la necesidad que pueda surgir en cualquier equipo y que pueda ser solventado con git hooks.*

## Git al rescate

**git** es una herramienta muy versátil, incluso con funcionalidades que muchos programadores aun teniendo años usándolo no han descubierto. Una de estas funcionalidades son los [git-hooks](https://git-scm.com/book/pl/v2/Customizing-Git-Git-Hooks).

Los hooks son como "triggers" que se disparan cuando cierto evento sucede. Por ejemplo, **post-merge** es el evento que se *dispara* luego de ejecutar un ```git pull``` (siempre que hayan cambios en la rama remota). Estos scripts se encuentran en la carpeta ```{PROJECT_NAME}/.git/hooks```. Ficheros de ejemplo crean automáticamente con la inicialización de cualquier repositorio git.

La versatilidad que nos provee esta funcionalidad (git-hooks) nos permite, por ejemplo, que luego de un *push* automáticamente se ejecuten tareas de verificación de estilos. O que antes de un merge a master se ejecuten las pruebas de integración. Junto a un largo etcétera que se ve limitado solo por lo que puedas lograr a través de un script.

Para conocer en profundidad los eventos disponibles echa un vistazo [acá](https://git-scm.com/docs/githooks#_hooks).

## Propuesta

Recordemos que queremos evitar lo propenso a errores que puede ser actualizar el entorno de desarrollo de múltiples desarrolladores en una misma empresa, asumiendo incluso que algunos pueden trabajar desde casa y por lo tanto no trabajar sobre la misma red. 

La propuesta para este problema es hacer un **git-hook** que cada vez que hayan cambios verifique que el archivo de hosts ```/etc/hosts``` se encuentre actualizado, y regenere un archivo en ```/etc/profile.d/``` en el cual se pueden definir las variables de entorno, independientemente de si usas bash, zsh, dash...

### post-merge

Por ejemplo, este sería el contenido del **post-merge**, script que se ejecutará automáticamente luego de cada ```git pull``` que detecte cambios en la rama remota:

```bash
#!/bin/bash
# Post update hook script.
# Color definition.
GREEN='\033[01;32m'

echo -e "${GREEN}Starting post update hook${NONE}"

if [ $EUID != 0 ]; then
    echo "Updating /etc/hosts file, sudo privileges required..."
    sudo "$0" "$@"
    exit $?
fi

echo -e "Ensuring /etc/hosts is up to date"
git-hooks/1-change-hosts.sh hosts-list
echo -e "Ensuring environment variables are up to date"
git-hooks/2-add-env-var.sh

echo -e "${GREEN}Finished post update hook${NONE}"
exit 0
```

Como pueden notar, además de pedir permisos de superusuario (debido a la modificación de archivos del sistema), simplemente ejecuta 2 scripts: **1-change-hosts.sh** y **2-add-env-var.sh**. Yo los he separado de esta forma para mantener una especie de separación de responsabilidades entre los scripts. Pero fácilmente toda la lógica pudo haber estado en el mismo script.

Para este ejemplo, se asume que estos 2 scripts forman parte del repositorio en una carpeta llamada *git-hooks*.

### 1-change-hosts.sh

Este es el contenido del script **1-change-hosts.sh**:

```bash
#!/bin/bash
# Should be automatically triggered by a post-merge git hook.
ENV_HOSTS=$1

if [[ $ENV_HOSTS != 'host-list' ]]; then
    echo "No correct host file was given"
    exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
HOSTS_FILE='/etc/hosts'
START_DELIMITER='### START OF MyCompany HOSTS ###'
END_DELIMITER='### END OF MyCompany HOSTS ###'

echo "Updating $HOSTS_FILE"

# If the placeholders are not yet in the /etc/hosts file, this must be the
# first run of this script. Add them.
PLACEHOLDER=`grep "$START_DELIMITER" $HOSTS_FILE`

if [[ ! $PLACEHOLDER ]]; then
    echo "No placeholders detected, this must be first run. Adding placeholders..."
    echo -e "\n$START_DELIMITER\n$END_DELIMITER\n" >> $HOSTS_FILE
fi

sed -i.bak -e "/^$START_DELIMITER\$/,/^$END_DELIMITER\$/{ /^$START_DELIMITER\$/{p; r $DIR/$ENV_HOSTS
}; /^$END_DELIMITER\$/p; d; }" $HOSTS_FILE

rm "$HOSTS_FILE.bak" &>/dev/null || true
````

Este script simplemente busca dentro de tu ```/etc/hosts``` por los delimitadores ```### START OF MyCompany HOSTS ###``` y ```### END OF MyCompany HOSTS ###```, si no existen, los escribe y luego pone entre estos delimitadores los hosts que hayas definido en el archivo que pasaste por parametro, en nuestro ejemplo es el contenido del fichero ```hosts-list```. De esta forma no modificamos cualquier otro host que alguien haya definido en su fichero.

### hosts-list

Un ejemplo del contenido del fichero ```hosts-list```:

```bash
127.0.0.1     dev-services.domain.com
10.0.3.1      dev-stats.other-domain.com
```

Con este contenido, estaríamos agregando ambos hosts al ```/etc/hosts``` de todos los desarrolladores con simplemente hacer un ```git pull``` del repositorio.

### 2-add-env-var.sh

Finalmente, este es el contenido del script **2-add-env-var.sh**:

```bash
echo "Adding env variables"

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ENV_FILE='environment_var.sh'
ENV_DIR='/etc/profile.d'

cp $DIR/$ENV_FILE $ENV_DIR/$ENV_FILE
source $ENV_DIR/$ENV_FILE
```

El resultado de este script sería la creación de un archivo ```environment_var.sh``` en ```/etc/profile.d``` con el contenido del fichero definido en ```git-hooks/environment_var.sh```. De esta forma, independientemente del shell que utilices, tendrás definidas las variables de entorno allí definidas.

### environment_var.sh

Un ejemplo de este fichero pudiera ser:

```bash
export USER_ID=`id -u`
export GROUP_ID=`id -g`
```

Con esto definiríamos una variable **$USER_ID** con el id del usuario unix y otra **$GROUP_ID** con el respectivo id del grupo. Es decir, el equivalente a las variables **$UID** y **$GID**.

Probablemente requiera un reinicio para que puedas hacer uso de las variables definidas luego del git hook.

## Finalizando

Es importante destacar que el contenido del script ```post-merge``` debe ser puesto manualmente dentro del directorio ```{PROJECT_NAME}/.git/hooks```, ya que los hooks no se guardan dentro del repositorio remoto. Por lo tanto es aconsejable crear otro script que simplemente haga un enlace al directorio correspondiente.

Por ejemplo, un fichero ```link-hook.sh```:

```bash
#!/bin/bash

# assuming the script is in a "git-hooks" directory, one level into the repo
HOOK_DIR=$(git rev-parse --show-toplevel)/.git/hooks

ln -sf ../../git-hooks/post-merge $HOOK_DIR/
```

Como ya comenté anteriormente, asumimos que el archivo ```post-merge``` se encuentra en un directorio llamado ```git-hooks``` dentro de tu repositorio. Es decir, este sería un supuesto árbol de directorios luego de ejecutar el script anterior:

```bash
/my-project/
            .git/
                ...
                hooks/
                        [hooks.sample]
                        post-merge -> ../../git-hooks/post-merge
                ...
            git-hooks/
                    1-change-hosts.sh
                    2-add-env-var.sh
                    environment_var.sh
                    hosts-list
                    post-merge
            src/
                main/
                ...
            link-hook.sh
            ...
```

El script habría creado un enlace dentro de ```.git/hooks/post-merge``` al script definido en ```git-hooks/post-merge```. De esta forma, si en algún momento se modifica el archivo del repositorio, automáticamente el hook podrá ejecutar el cambio sin ninguna otra acción requerida. Esto solo sería necesario ejecutarlo la primera vez que se clona el repositorio, para crear el enlace. Posteriormente, la magia la hará git automaticamente con cada ```git pull``` que detecte cambios en el repo.
