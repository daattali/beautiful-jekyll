---
layout: post
published: true
title: 'Errores de novato'
subtitle: Evitando NullPointerExceptions
date: '2018-02-15'
tags: [programming, java, tips]
share-img: /assets/img/null-pointer-exception.png
image: /assets/img/java_coffee.jpg
---

```NullPointerException```, no creo equivocarme  al afirmar que difícilmente encontraremos un programador de Java que no haya visto esa excepción en su vida. Esta excepción nos indica que hemos intentado utilizar un ```null``` donde un objeto era requerido, esto incluye intentar:

- Ejecutar un método en un ```null```
- Acceder o modificar un campo de un ```null```
- Obtener la longitud de un ```null``` como si fuera un ```array```
- Acceder o modificar las casillas de un ```null``` como si fuera un ```array```
- ```Throw``` un null como si fuera un valor ```Throwable```

 Algunas practicas hacen que su frecuencia sea mayor en algunos proyectos más que en otros, pero me atrevería a decir que el solo hecho de **no** retornar ```null``` mejorará la robustez del código y disminuirá la presencia de los ```NullPointerException``` en los logs.

Principalmente, los ```null``` se suelen retornar en 2 casos: (1) denotar que no se encontraron valores para llenar una colección, (2) señalar que un valor no se encontró o no estaba presente, incluso aunque no haya habido ningún error.

Estos 2 casos se pueden afrontar de mejor forma evitando retornar ```null``` y por lo tanto causando que los clientes de nuestro código no tengan que adivinar si deben verificar que el valor retornado sea ```null``` o no antes de hacer algo con él.

## Colección vacía

Cuando un método retorna una lista (o cualquier otra colección) de elementos, puede ser común retornar ```null``` para señalar que ningún elemento se pudo encontrar para la lista solicitada. Por ejemplo, pudiéramos implementar un *servicio* encargado de gestionar los usuarios de una plataforma de la siguiente forma (algunos métodos y clases han sido omitidos para simplificar):

```java

public class UserService {
    public List<User> getUsers() {
        User[] usersFromDb = getUsersFromDatabase();
        if (usersFromDb == null) {
            // No users found in database
            return null;
        }
        else {
            return Arrays.asList(usersFromDb);
        }
    }
}
UserServer service = new UserService();
List<Users> users = service.getUsers();
if (users != null) {
    for (User user: users) {
        System.out.println("User found: " + user.getName());
    }
}

```
Como hemos elegido retornar ```null``` en caso de que no hayan usuarios, estamos forzando a nuestros clientes a tener en cuenta este caso antes de intentar iterar sobre la lista de usuarios. Si en lugar de ello, retornaramos una lista vacia para denotar que ningún usuario fue encontrado, el cliente pudiera remover la verificación del ```null``` y simplemente iterar sobre la lista de usuarios. Si no hay ningún usuario, la iteración se saltará implícitamente sin tener que verificar manualmente dicho caso; en esencia, iterar sobre la lista de usuarios funciona como queremos en ambos casos (con usuarios o vacía) sin tener que revisar manualmente ambos casos.

```java

public class UserService {
    public List<User> getUsers() {
        User[] usersFromDb = getUsersFromDatabase();
        if (usersFromDb == null) {
            // No users found in database
            return Collections.emptyList();
        }
        else {
            return Arrays.asList(usersFromDb);
        }
    }
}
UserServer service = new UserService();
List<Users> users = service.getUsers();
for (User user: users) {
    System.out.println("User found: " + user.getName());
}

```

Todo se resume al consejo de [Effective Java](https://books.google.co.kr/books/about/Effective_Java.html) que sugiere que debemos de retornar una colección vacía para denotar que no hay elementos, no ```null```.

## Optional

En ocaciones, retornamos ```null``` para informar al cliente que un valor opcional no se encuentra presente, no porque sea un error, sino porque su presencia o ausencia son estados validos. Por ejemplo, obtener un parametro de un URL. En algunos casos, el parametro puede estar presente, pero en otros no. La ausencia del parametro no necesariamente representa un error, sino que el usuario no deseaba la funcionalidad que provee dicho parametro. Esto se puede lograr retornando ```null``` si el parámetro no está presente o el valor del parámetro si llega a estar presente (algunos métodos han sido omitidos):

```java

public class UserListUrl {
    private final String url;
    public UserListUrl(String url) {
        this.url = url;
    }
    public String getSortingValue() {
        if (urlContainsSortParameter(url)) {
            return extractSortParameter(url);
        }
        else {
            return null;
        }
    }
}
UserService userService = new UserService();
UserListUrl url = new UserListUrl("http://localhost/api/v2/users");
String sortingParam = url.getSortingValue();
if (sortingParam != null) {
    UserSorter sorter = UserSorter.fromParameter(sortingParam);
    return userService.getUsers(sorter);
}
else {
    return userService.getUsers();
}

```

En este ejemplo, cuando no se provee un parámetro para ordenar se retorna ```null``` y el cliente debe de manejar este caso, sin dejar claro en la firma del método ```getSortingValue``` que el valor del parámetro para ordenar es opcional. Para saber que el valor de este parametro es opcional y que nos retornará ```null``` si no está presente, debemos ir a la fuente del código o a la documentación (de ser posible).

Sin embargo, podemos hacer explicita la naturaleza opcional de este parámetro, cambiando la firma de nuestro método ```getSortingValue``` para que retorne un objecto del tipo ```Optional```. Como se puede observar, el cliente sigue teniendo que manejar el caso en el que el parámetro no está presente, pero ahora la necesidad del mismo está explicita. Incluso, la clase ```Optional``` provee de mecanismos para manejar la ausencia de un parámetro mas allá de simplemente revisar si es ```null```. Por ejemplo, podemos simplemente verificar la presencia del parametro con el metodo ```isPresent``` que provee ```Optional```:

```java

public class UserListUrl {
    private final String url;
    public UserListUrl(String url) {
        this.url = url;
    }
    public Optional<String> getSortingValue() {
        if (urlContainsSortParameter(url)) {
            return Optional.of(extractSortParameter(url));
        }
        else {
            return Optional.empty();
        }
    }
}
UserService userService = new UserService();
UserListUrl url = new UserListUrl("http://localhost/api/v2/users");
Optional<String> sortingParam = url.getSortingValue();
if (sortingParam.isPresent()) {
    UserSorter sorter = UserSorter.fromParameter(sortingParam.get());
    return userService.getUsers(sorter);
}
else {
    return userService.getUsers();
}

```

Si, es casi idéntico al código donde revisamos la nulidad del objeto, pero en este caso hemos hecho explicita la naturaleza opcional del parámetro y quien use este método sabrá que puede esperar inmediatamente al ver la firma del método. Si no estuviésemos interesados en retornar la lista de usuarios en base al parámetro opcional de la URL, sino en consumir el parámetro de alguna forma, pudiéramos utilizar el método ```ifPresentOrElse``` de la siguiente forma:

```java

sortingParam.ifPresentOrElse(
    param -> System.out.println("Parameter is :" + param),
    () -> System.out.println("No parameter supplied.")
);

```

Esto reduce toda la ceremonia requerida para verificar la nulidad de una variable. Incluso, si no nos importa el caso en el que no está presente el valor, podemos hacerlo con ```ifPresent``` de la siguiente forma:

```java

sortingParam.ifPresent(param -> System.out.println("Parameter is :" + param));

```

En cualquier caso, utilizando un objeto ```Optional```, en lugar de retornar un ```null```, le informamos explicitamente a nuestro cliente que el valor de retorno puede o no estar presente e incluso le ofrecemos múltiples formas de manejar ese valor. Por lo que como norma general, si el valor de retorno de una función es *opcional*, asegura que tus clientes manejen la presencia o ausencia del valor retornando un objeto del tipo ```Optional```.

> Ejemplos extraídos de [3 Things Every Java Developer Should Stop Doing](https://dzone.com/articles/3-things-every-java-developer-should-stop-doing)