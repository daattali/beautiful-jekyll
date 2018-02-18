---
layout: post
published: false
title: 'Errores de novato I'
subtitle: Evitando los nulls
date: '2018-02-15'
tags: [programming, java, tips]
---

```NullPointerException```, no creo equivocarme  al afirmar que difícilmente encontraremos un programador de Java que no haya visto esa excepción en su vida. Esta excepción nos indica que hemos intentado utilizar un ```null``` donde un objeto era requerido, esto incluye intentar:

- Ejecutar un método en un ```null```
- Acceder o modificar un campo de un ```null```
- Obtener la longitud de un ```null``` como si fuera un ```array```
- Acceder o modificar las casillas de un ```null``` como si fuera un ```array```
- ```Throw``` un null como si fuera un valor ```Throwable```

 Algunas practicas hacen que su frecuencia sea mayor en algunos proyectos más que en otros, pero me atrevería a decir que el solo hecho de **no** retornar ```null``` mejorará la robustez del código y disminuirá la presencia de los ```NullPointerException``` en los logs.

Principalmente, los ```null``` se suelen retornar en 3 casos: (1) denotar que no se encontraron valores para una colección, (2) señalar que no se encontró un valor válido, incluso aunque no haya habido ningún error. (3) denotar un caso especial. 

Estos 3 casos se pueden afrontar de mejor forma evitando retornar ```null``` y por lo tanto causando que los clientes de nuestro código no tengan que adivinar si deben verificar que el valor retornado sea ```null``` o no antes de hacer algo con él.

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
Todo se resume al consejo de [Effective Java](https://books.google.co.kr/books/about/Effective_Java.html) que nos dice que deberíamos de retornar una colección vacía para denotar que no hay elementos.

## Optional

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

## Caso especial



> Ejemplos extraídos de [3 Things Every Java Developer Should Stop Doing](https://dzone.com/articles/3-things-every-java-developer-should-stop-doing)