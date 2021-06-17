---
layout: post
title: {shinytitle} Change the Browser Tab Title of your Shiny App 
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [rstats, package, shiny, shinytitle]
---

Have you ever experienced a call where it starts with "let me show you something" and you both end up looking at the loading shiny app for the next 5 minutes? This is the source of inspiration to create the [`{shinytitle}`](https://ashbaldry.github.io/shinytitle) package (Well, this and [CDKeys](https://www.cdkeys.com) guilting me into returning to their site by updating their title to "We Miss You" whenever I accessed another tab).

Whilst it is best practice to minimise processing time for a shiny application, sometimes a calculation is computationally heavy or an API takes a long time to respond. `{shinytitle}` provides a more convenient alternative to you either periodically clicking to and from the app to check the status, or (like me) mindlessly stare at the loading circle until the application has loaded.

## Updating When Ready

There are currently two ways to update the browser title upon a certain event happening:

- `change_window_title` will update the title 
- `flashing_window_title` will alternate between two different titles, the current title and a second temporary title

Both of these have the option to only change when the user is looking at a different tab, and can revert when the user returns back to the application. The flashing title has a few extra features, such as being able to stop when the mouse is moved or after a certain period of time.

__Note:__ For either of these to work, `use_shiny_title()` is required in the UI in order to include the required script.

Example:
```r
library(shiny)
library(shinytitle)

ui <- fluidPage(
  title = "shinytitle Example",
  use_shiny_title(),
  inputPanel(
    actionButton("flash", "Click me for a flashing title"),
    actionButton("toggle", "Click me for an update when finished")
  )
)

server <- function(input, output, session) {
  observeEvent(input$flash, {
    flashing_window_title(session, "Calculating", interval = 1000, duration = 10000, revert_on_mousemove = FALSE)
    change_window_title(session, "shinytitle Example")
  })

  observeEvent(input$toggle, {
    Sys.sleep(3)
    change_window_title(session, "Sleep Finished", inactive_only = TRUE)
  })
}

shinyApp(ui, server)
```

Here is a before and after of clicking on the "toggle" button:

![Clicking on button to run functionality to change title](https://user-images.githubusercontent.com/8420419/121812353-6d247f80-cc5f-11eb-9674-ec91763ccd9c.png)
![Title change whilst looking at new tab](https://user-images.githubusercontent.com/8420419/121812357-6eee4300-cc5f-11eb-80c9-c08a0c470d3a.png)


## Updating When Busy

Alternatively, you can have the title change whenever the shiny application is in a "busy" state by adding `busy_shiny_title()` into the UI. This can be useful to find unexpected times that the shiny application is calculating in the background.

Example:
```r
library(shiny)
library(shinytitle)

ui <- fluidPage(
  title = "shinytitle Example",
  use_shiny_title(),
  busy_window_title(),
  inputPanel(actionButton("busy", "'Long' Function")),
  textOutput("done")
)

server <- function(input, output, session) {
  text <- eventReactive(input$busy, {
    Sys.sleep(3)
    "Completed!"
  })

  output$done <- renderPlot(text())
}

shinyApp(ui, server)
```

This package is now avialble on CRAN; please reach out about any further suggestions for this package!
