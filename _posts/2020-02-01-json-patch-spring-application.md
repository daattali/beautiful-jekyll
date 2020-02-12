---
layout: post
title: Use Json Patch in Spring application
categories: [spring]
tags: [spring, json-p, spring-boot]
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

Thre previous example represents a set of changes to the original document. This can be very usefull in REST APIs when we want to update a resource. 
Instead of sending to the server the JSON Document with the full representation of the user we can send the JSON patch with the operation we want to perfom.

## Json Patch operations

Each operation consists on the following members:

+ **op** This is a mandatory parameter, it defines the operation we want to perfom. Its value MUST be one of "add", "remove", "replace", "move", "copy", or "test"
+ **path** This is also a mandatory parameter. It defines the target of the operation. From now we will refer to this field as the "target location"
+ **value** This parameter can be optional depending on the operation. It contains the value of the operation.

Lets now see what each operation does.

### add

```json
[
     { "op": "add", "path": "/alias", "value": "Batman" },
]
```

Adds a new member to the JSON document. In this case it will create the alias property on the User document.

### remove

```json
[
     { "op": "remove", "path": "/phoneNumber" },
]
```

Removes the value at the the target location.

### replace

```json
[
     { "op": "replace", "path": "/address", "value": "batcave" },
]
```

Updates the element at the target location to have the new value. 

### move

```json
[
   { "op": "move", "from": "/mobilePhoneNumber", "path": "/landlinePhoneNumber" }
]
```

This operation is the equivalent of a remove followed by an add. In this case it will move the value of the mobilePhoneNumber to the landlinePhoneNumber field.

### copy

```json
[
   { "op": "copy", "from": "/mobilePhoneNumber", "path": "/landlinePhoneNumber" }
]
```

This operation copies the value of the field indicated by from to the field indicated by path.


## JSON-P: Java API for JSON Processing 1.1 - JSR 374 


The Java API for JSON Processing provides portable APIs to parse, generate, transform, and query JSON. It introduced in Java world the following classes:

| Class      | Description |
| ----------- | ----------- |
| Json      | This is a Factory class for creating JSON processing objects. Contains static methods to create JSON readers, writers, builders, and their factory objects.|
| JsonReader   | This class reads JSON data from an input source and creates in-memory object model.|
|JsonValue | Represents a JSON value that can be an object, an array, a number, a string, true, false or null|
|JsonStructure	| Super type for the two structured types in JSON: object and array|
|JsonPatch	| The implementation of JSON patch expalined before|


**Note**: Java Introduced the JSON Patch in the [JSR 374](https://www.jcp.org/en/jsr/detail?id=374)
. This JSR is the evolution of JSR 353, among other changes it added the support for JSON Pointer and JSON Patch.


These classes provide a full representation of a JSON document and enable us to progrmatically manipulate and create JSON documents.


# Use JSON Patch in a Spring Controller


The first thing to do is to add the JSR 374 API to our project dependencies.

```gradle
compile group: 'javax.json', name: 'javax.json-api', version: '1.1.4'
```

Since the javax.json package only defines the API we need to also include an implementation. For this tutorial I'll use [Apache Johnzon](https://johnzon.apache.org)

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
    //TODO patch the user
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

Since I don't want to serialize objects to JsonPatch objects I decided to throw a NotImplementedException in the writeInternal method.

Now Spring can deserialize the received JSON document to a JsonPatch instance.


The full code for this sample is located at ......
