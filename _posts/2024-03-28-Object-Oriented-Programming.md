---
layout: post
title: Object Oriented programming
subtitle: Practice for concept of object oriented programming
# cover-img: /assets/img/banditlogo.png
# thumbnail-img: /assets/img/OWASP_Logo.png
# share-img: /assets/img/path.jpg
tags: [programming, class, object-oriented, inheritance]
comments: true
author: Lantana Park
---

## What is OOP(Object Oriented Programming)?

It is one of the programming concept and has three main concepts: class and instance, inheritance, and encampsulation.

As far as I understood, it allows me to group related information together so that I can produce shorter and more reuseable code.

Building blocks: Classes, Objects, Methods, Attributes

```javascript
// Class is a blueprint
class Student {
  name, nationality,languages;
  // Constructor for creating and initializing objects
  constructor(name, nationality, languages) {
    this.name = name; // Attribute storing name
    this.nationality = nationality; // Attribute storing nationality
    this.languages = languages; // Attrubute stroing nationality
  }
  // Method of the student class
  introduceSelf() {
    console.log(
      // `this.name` refers to the property `name` of the current instance of the `Student` class. By using `this.name`, I can reach the value inside of class
      `My name is ${this.name}. I'm from ${this.nationality} and can speak ${this.languages}.`
    );
  }
}
// Creating an object 'lantana' from the student class
const lantana = new Student("Lantana Park", "Korea", "Korean and English");
// Calling introductSelf method on the lantana object
lantana.introduceSelf();
```

## Priciples of OOP

There are 4 pillars of OOP

Encapsulation, Abstraction, Inheritance, Polymorphism

1. Encapsulatiol
   This is the concept

```javascript
class Student {
  #name; // `#name` is a private field
  #major;

  constructor(name) {
    this.#name = name;
  }

  getName() {
    return this.#name;
  }

  setName(name) {
    this.#name = name;
  }
}

const person = new Person("John Doe");
console.log(person.getName()); // John Doe
person.setName("Jane Doe");
console.log(person.getName()); // Jane Doe
// person.#name; // SyntaxError: Private field '#name' must be declared in an enclosing class
```

[Watch the video here to view my explaination](https://www.loom.com/share/092080785c894d588f7b06a93ada2eb3?sid=c177950a-94e3-4145-8c74-0ecaf754a611)

```javascript
// Configuration
// It is the application setting.
const config = {
  logLevel: {
    error: 1,
    warn: 2,
    info: 3,
    debug: 4,
  }, // This is the type of log message to display
  initialName: "please input your name", // I set the initial name is world, so, at first, it will print hello world
};

// Logger with dependecy injection
// It is to print log message to the console based on the specified log level.
class Logger {
  constructor(logLevel) {
    // Assume logLevel is a key from the config.logLevel object ("error", "warn", "info", "debug")
    this.logLevelNumeric = config.logLevel[logLevel];
  }

  log(message, level = "info") {
    // Convert the string level to its numeric value based on the config
    const messageLevelNumeric = config.logLevel[level];
    if (messageLevelNumeric <= this.logLevelNumeric) {
      console.log(`${level.toUpperCase()}: ${message}`);
    }
  }
}

// Model
// It is the object for storing user's name
const model = {
  // This name property stores current name.
  name: config.initialName,
  //`setName` updates the name and logs
  setName(name) {
    if (name === "") {
      // Log an error if the name is an empty string
      logger.log("Name cannot be empty", "error");
    } else {
      this.name = name;
      logger.log(`Name updated -> ${name}`, "info");
      // Log the name update at info level
    }
  },
  // `getName` is to return the current name.
  getName() {
    return this.name;
  },
};

// View
// It is to deal with
class View {
  constructor(appElement, model) {
    this.appElement = appElement;
    this.model = model;

    this.nameInput = appElement.querySelector("#name-input");
    this.greetButton = appElement.querySelector("#greet-button");
    this.greetingElement = appElement.querySelector("#greeting");

    this.attachEventListeners();
  }

  attachEventListeners() {
    this.greetButton.addEventListener("click", (event) => {
      event.preventDefault();
      this.model.setName(this.nameInput.value);
      this.updateGreeting();
    });
  }

  updateGreeting() {
    this.greetingElement.textContent = `Hello, ${this.model.getName()}!`;
  }
}

// Controller
// It is an intermediary between the model and the view.
// It initializes the application state and updates the view to reflect the current model state when the application start.
class Controller {
  constructor(model, view, logger) {
    this.model = model;
    this.view = view;
    this.logger = logger;
  }

  start() {
    this.view.updateGreeting();
  }
}

// Manually injected the dependencies
const logger = new Logger("info");
const view = new View(document.getElementById("app"), model);
const controller = new Controller(model, view, logger);

controller.start();
```
