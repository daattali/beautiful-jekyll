---
layout: post
title: Using kotlin with parse-server, an example
gh-badge: [star, fork, follow]
tags: [Android, Kotlin, parse-server, Parse-Android-SDK]
---

Suppose we have a problem where we have Items. The class item belongs to a Category. Using kotlin the class category could be as follow:

```kotlin
import com.parse.ParseClassName
import com.parse.ParseObject
import com.parse.ktx.delegates.stringAttribute

@ParseClassName("Category")
class Category : ParseObject() {

    var name : String by stringAttribute()
    var description : String by stringAttribute()
}
```

Now we create the clas Item. The class item have a name, a description and the Category.

Class Item
```kotlin
import com.parse.ParseClassName
import com.parse.ParseObject
import com.parse.ktx.delegates.stringAttribute

@ParseClassName("Item")
class Item : ParseObject () {

    var name: String by stringAttribute() // That's it

    var description: String by stringAttribute()

    var category : Category?
        get() = get("category") as Category?
        set(value) {
            put("category", value as Category)
        }

}
```

To save a new Item with its Category we can do as simple as:
```kotlin
var category = Category()
category.name = "Electronicos y Celulares"
category.description = "Seccion para la venta de equipos electronicos y celulares"

var item = Item()
item.name = "Moto G4 Plus"
item.category = category
item.save()
```

The save function save both the Item an the Category at the same time.

Now to find all the items we can run the following query. To do this we create a DAO class called ItemDAO:

```java
import android.util.Log;
import com.enml.bazar.data.model.Item;
import com.parse.FindCallback;
import com.parse.ParseException;
import com.parse.ParseQuery;

import java.util.List;

public class ItemDAO {

    public ItemDAO() {

    }

    public void getItems () {
        ParseQuery<Item> query = ParseQuery.getQuery(Item.class);
        query.findInBackground(new FindCallback<Item>() {
            @Override
            public void done(List<Item> objects, ParseException e) {
                for (Item object : objects) {
                    Log.d("Item name: " , object.getName());
                }
            }
        });
    }
}
```

Then we can run the query to get all the items:

```java
 ItemDAO().getItems()
 ```

