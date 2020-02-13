---
layout: post
title: Use Json Patch in Spring application
categories: [spring, java]
tags: [spring, json-p, json-processing, json-patch, spring-boot, jsr-374, rest]
---

# What is JSON Patch?

Json Patch is a format defined in [RFC 6902](https://tools.ietf.org/html/rfc6902) that describes changes to a JSON document.
According to RFC 6902 we can define JSON patch like this:

>JSON Patch defines a JSON document structure for expressing a
   sequence of operations to apply to a JavaScript Object Notation
   (JSON) document; it is suitable for use with the HTTP PATCH method.
   The "application/json-patch+json" media type is used to identify such
   patch documents.

Lets take as example the following JSON document. This document defines the tipical User model used by most applications.

```json
{
  "email": "john@email.com",
  "name": "Bruce Wayne",
  "mobilePhoneNumber": "+35191919191",
  "landlinePhoneNumber": "+3511010101010",
  "address": "Street something 99"
}
```

If we want to represent changes to this document we can use JSON Patch.

```json
[
     { "op": "remove", "path": "/phoneNumber" },
     { "op": "add", "path": "/alias", "value": "Batman" },
     { "op": "replace", "path": "/address", "value": "batcave" },
]
```

The previous example represents a set of changes to the original document. This can be very usefully for update operations on REST APIs. 
With JSON Patch we only send to the server a smaller JSON document that represents the changes we want to make to the original resource.

## Json Patch operations

Each operation consists on the following members:

+ **op** This is a mandatory parameter, it defines the operation we want to perform. Its value MUST be one of "add", "remove", "replace", "move", "copy", or "test"
+ **path** This is also a mandatory parameter. It defines the target of the operation. From now on we will refer to this field as the "target location"
+ **value** This parameter can be optional depending on the operation. It contains the value of the operation.

#### add

```json
[
     { "op": "add", "path": "/alias", "value": "Batman" },
]
```

Adds a new member to the JSON document. In this case it will create the alias property on the document.

#### remove

```json
[
     { "op": "remove", "path": "/phoneNumber" },
]
```

Removes the value at the the target location.

#### replace

```json
[
     { "op": "replace", "path": "/address", "value": "batcave" },
]
```

Updates the element at the target location to have the new value. 

#### move

```json
[
   { "op": "move", "from": "/mobilePhoneNumber", "path": "/landlinePhoneNumber" }
]
```

This operation is the equivalent of a remove followed by an add. In this case it will move the value of the mobilePhoneNumber to the landlinePhoneNumber field.

#### copy

```json
[
   { "op": "copy", "from": "/mobilePhoneNumber", "path": "/landlinePhoneNumber" }
]
```

This operation copies the value of the "from" field to the target field.


---
# JSON-P: Java API for JSON Processing 1.1 - JSR 374 


The Java API for JSON Processing provides portable APIs to parse, generate, transform, and query JSON. It introduced in Java world the following classes:

| Class      | Description |
| ----------- | ----------- |
| Json      | This is a Factory class for creating JSON processing objects. Contains static methods to create JSON readers, writers, builders, and their factory objects.|
| JsonReader   | This class reads JSON data from an input source and creates in-memory object model.|
|JsonValue | Represents a JSON value that can be an object, an array, a number, a string, true, false or null|
|JsonStructure	| Super type for the two structured types in JSON: object and array|
|JsonPatch	| The implementation of JSON patch explained before|


**Note**: Java Introduced the JsonPatch in the [JSR 374](https://www.jcp.org/en/jsr/detail?id=374)
. This JSR is the evolution of JSR 353, among other changes it added the support for JsonPointer and JsonPatch.


These classes provide a full representation of a JSON document and enable us to programmatically manipulate and create JSON documents.

---
# Use JSON Patch in a Spring Controller


The first thing to do is to add the JSR 374 API to our project dependencies.

```gradle
compile group: 'javax.json', name: 'javax.json-api', version: '1.1.4'
```

Since the javax.json package only defines the API, we need to also include an implementation. For this tutorial I'll use [Apache Johnzon](https://johnzon.apache.org)

```gradle
compile group: 'org.apache.johnzon', name: 'johnzon-core', version: '1.2.3'
```

Now we can create a new endpoint that receives a JsonPatch object.

```java
@PatchMapping(value = "/", consumes = "application/json-patch+json")
@Operation(description = "Updates an existing user", summary = "Updates an existing user")
@ApiResponses(value = { @ApiResponse(responseCode = "202", description = "The user has been updated" content = @Content)})
@ResponseStatus(HttpStatus.ACCEPTED)
public void updateUser(@RequestBody JsonPatch patchDocument) {
    userService.patchUser(patchDocument, email);
    //the full code can be found in the git repository
}
```

The important thing to notice here is that the RequestBody is of type JsonPatch. Unfortunately Spring doesn't provide by default any converter for JsonPatch, so we have to implement a custom HttpMessageConverter.

```java
import javax.json.Json;
import javax.json.JsonPatch;
import javax.json.JsonReader;
import org.apache.commons.lang3.NotImplementedException;
import org.springframework.http.HttpInputMessage;
import org.springframework.http.HttpOutputMessage;
import org.springframework.http.MediaType;
import org.springframework.http.converter.AbstractHttpMessageConverter;
import org.springframework.http.converter.HttpMessageNotReadableException;
import org.springframework.http.converter.HttpMessageNotWritableException;
import org.springframework.stereotype.Component;

@Component
public class JsonPatchHttpMessageConverter extends AbstractHttpMessageConverter<JsonPatch> {

  public JsonPatchHttpMessageConverter() {
    super(MediaType.valueOf("application/json-patch+json"));
  }

  @Override
  protected JsonPatch readInternal(Class<? extends JsonPatch> clazz, HttpInputMessage inputMessage) throws HttpMessageNotReadableException {

    try (JsonReader reader = Json.createReader(inputMessage.getBody())) {
      return Json.createPatch(reader.readArray());
    } catch (Exception e) {
      throw new HttpMessageNotReadableException(e.getMessage(), inputMessage);
    }
  }

  @Override
  protected void writeInternal(JsonPatch jsonPatch, HttpOutputMessage outputMessage) throws HttpMessageNotWritableException {
    throw new NotImplementedException("The write Json patch is not implemented");
  }

  @Override
  protected boolean supports(Class<?> clazz) {
    return JsonPatch.class.isAssignableFrom(clazz);
  }

}
```

Since I don't want to serialize objects to JsonPatch objects the method writeInternal throws a NotImplementedException.

Now Spring can deserialize the received JSON document to a JsonPatch instance. With this JsonPatch instance we can implement our service that will get the original user from the database and apply the requested changes.

```java
 public void patchUser(JsonPatch patchDocument, String email) {
        //Gets the original user from the database
        User originalUser = getUserByEmail(email); //1
        logger.debug("original user  {}", originalUser);

        //Converts the original user to a JsonStructure
        JsonStructure target = objectMapper.convertValue(originalUser, JsonStructure.class); //2
        //Applies the patch to the original user
        JsonValue patchedUser = patchDocument.apply(target); //3

        //Converts the JsonValue to a User instance
        User modifiedUser = objectMapper.convertValue(patchedUser, User.class); //4
        logger.debug("modified user {}", modifiedUser);

        //Saves the modified user in the database
        usersList.put(email, modifiedUser);  //5
    }
```

As we can see the code to apply the patch is pretty straightforward. Lets see it step by step.

1. We get the original/unmodified user from the database. 
2. Convert the user to a JsonStructure using the objectMapper. As said before, the JsonStructure was introduced by JSR-374 and among other classes enable us to programmatically manipulate Json documents.
3. Apply the patch to the original user, we then get a JsonValue that represents the user with the changes present in the patch.
4. Convert the JsonValue to a user instance that we can store again on the database.
5. Store the modified user on the database.

With this implementation we can call the service like this:
```bash
curl -X PATCH "http://localhost:8080/users/bruce.wayne%40gotham.com" -H "accept: */*" -H "Content-Type: application/json-patch+json" -d "[{\"op\":\"replace\",\"path\":\"/email\",\"value\":\"batman@gotham.com\"}]"
```

There is a final step to make the previous code work. The Jackson Object mapper isn't capable of serializing/deserializing the new types defined in JSR-353/JSR-374, like the JsonValue and JsonStructure. To configure Jackson for these new types we must first add the following dependency to the project:

```
compile group: 'com.fasterxml.jackson.datatype', name: 'jackson-datatype-jsr353', version: '2.10.2'
```

Then we need to create a custom ObjectMapper bean and register the Jackson JSR-353 datatype as a module. In Spring we can create a configuration class to define a new bean:

```java
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.datatype.jsr353.JSR353Module;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class ApplicationConfig {

    @Bean
    public ObjectMapper objectMapper() {
        ObjectMapper objectMapper = new ObjectMapper();
        objectMapper.registerModule(new JSR353Module());

        return objectMapper;
    }

}
```

Obviously this is a simplified example. On the service we should validate the requested changes, for example we may want to disallow the change of the user email. On a real application we would also need to validate permissions and business rules before making the update.

The complete code can be found at [https://github.com/hugo-ma-alves/json-patch-demo](https://github.com/hugo-ma-alves/json-patch-demo). This repository contains a spring boot application, you just have to run it and then the swagger-ui interface to test the request becomes available at http://localhost:8080/swagger-ui/index.html.