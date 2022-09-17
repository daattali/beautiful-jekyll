---
layout: post
title: Syncronization of parse objects, how it work internally.
gh-badge: [star, fork, follow]
tags: [Android, Parse, Parse-Android-SDK]
---

When we use a [Parse-Android-SDK](https://docs.parseplatform.org/android/guide/) usually we have a remote object and a local one. Both objects need to be syncronized. Parse sugest something like this:

## From server to local datastore

```java
ParseQuery<ParseObject> query = ParseQuery.getQuery("Profile");
query.orderByDescending("score");

// Query for new results from the network.
query.findInBackground(new FindCallback<ParseObject>() {
  public void done(final List<ParseObject> profiles, ParseException e) {
    // Remove the previously cached results.
    ParseObject.unpinAllInBackground("profile", new DeleteCallback() {
    public void done(ParseException e) {
      // Cache the new results.
      ParseObject.pinAllInBackground("profile", scores);
    }
  });
  }
});
```


## From local datastore to server

## How it work?

ParseObject has three hashmaps, serverData, estimateData and operationSetQueue:
- serverData: the hashmap that is populated when se retreive a ParseObject from the server.
- estimateData: the hashmap that is populated when se retreive a ParseObject from the local datastore.
- operationSetQueue: the hashmap that store the changes we made in the local ParseObject and we don't save jet.

As the description indicate those hashmaps are populated as needed by the [Parse-Android-SDK](https://docs.parseplatform.org/android/guide/).  To ilustrate how it work suppose that we have a Profile ParseObject with a displayName and sex parameters.

```Java
ParseObject profile = new ParseObject("Profile");
profile.put("displayName", "nmlemus");
profile.put("sex", "Male");
profile.saveInBackground();
```
To retrieve the object from the network we use this code:

```Java
ParseQuery<ParseObject> query = ParseQuery.getQuery("Profile");
query.getInBackground("xWMyZ4YEGZ", new GetCallback<ParseObject>() {
  public void done(ParseObject profile, ParseException e) {
    if (e == null) {
      // object will be your game score
      String displayName = profile.get("displayName");
    } else {
      // something went wrong
    }
  }
});
```
