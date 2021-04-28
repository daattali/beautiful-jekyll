---
layout: default
title: Home
permalink: /
---

# EU-funded C0PEP0D project

## Context

Copepods are millimetric crustaceans that play a crucial role in marine ecosystems. They
live in all seas and oceans and are thought to be the most abundant multi-cellular organism of the planet. Yet, copepods are blind. To detect preys, predators and mates, copepods use highly-developed hydrodynamic and chemical sensing. How are they able to distinguish a meaningful signal in oceanic turbulence? Copepods being one of the greatest success story of marine evolution, they likely evolved smart algorithms to process this sensing information. But today, these algorithms are poorly understood.

![Graphical abstract](/assets/img/graphical_abstract.jpg)
**(Left)** View of a 5 mm long copepod _Euchaeta antarctica_ swimming (Catton et al. 2007). **(Right)** We train a virtual copepod by reinforcement learning. This copepod senses hydrodynamic and chemical signals, processes them with a neural network, and reacts.

## Objectives

The objective of C0PEP0D is to decipher how copepods exploit hydrodynamic and chemical sensing to track targets in turbulent flows. We address three questions:

* **Q1: Mating.** How do male copepods follow the pheromone trail left by females?
* **Q2: Finding.** How do copepods use hydrodynamic signals to "see"?
* **Q3: Feeding.** What are the best feeding strategies in turbulent flow?

We hypothesize that reinforcement learning can help reverse-engineer the algorithms used by copepods. To test this hypothesis, we are building a virtual environment, where copepods are trained: virtual copepods sense flow velocity and chemical concentration and this sensing information is processed by a neural network trained by reinforcement learning. This theoretical and numerical approach is complemented by experiments on real copepods with the goal of measuring how copepods reacts in turbulent flow.

## Project ID

<dl>
<dt>Title</dt><dd>Life and death of a virtual copepod in turbulence</dd>
<dt>Acronym</dt><dd>C0PEP0D</dd>
<dt>Host institution</dt><dd> <a href="https://www.centrale-marseille.fr">Centrale Marseille</a></dd>
<dt>Principal investigator</dt><dd> <a href="https://www.irphe.fr/~eloy">Christophe Eloy</a></dd>
<dt>Dates</dt><dd>2019-2024</dd>
</dl>



<!-- ----

Text can be **bold**, _italic_, or ~~strikethrough~~.

[Link to another page](./another-page.html).

There should be whitespace between paragraphs.

There should be whitespace between paragraphs. We recommend including a README, or a file with information about your project.
# Header 1

This is a normal paragraph following a header. GitHub is a code hosting platform for version control and collaboration. It lets you and others work together on projects from anywhere.

## Header 2

> This is a blockquote following a header.
>
> When something is important enough, you do it even if the odds are not in your favor.

### Header 3

```js
// Javascript code with syntax highlighting.
var fun = function lang(l) {
  dateformat.i18n = require('./lang/' + l)
  return true;
}
```

```ruby
# Ruby code with syntax highlighting
GitHubPages::Dependencies.gems.each do |gem, version|
  s.add_dependency(gem, "= #{version}")
end
```

#### Header 4

*   This is an unordered list following a header.
*   This is an unordered list following a header.
*   This is an unordered list following a header.

##### Header 5

1.  This is an ordered list following a header.
2.  This is an ordered list following a header.
3.  This is an ordered list following a header.

###### Header 6

| head1        | head two          | three |
|:-------------|:------------------|:------|
| ok           | good swedish fish | nice  |
| out of stock | good and plenty   | nice  |
| ok           | good `oreos`      | hmm   |
| ok           | good `zoute` drop | yumm  |

### There's a horizontal rule below this.

* * *

### Here is an unordered list:

*   Item foo
*   Item bar
*   Item baz
*   Item zip

### And an ordered list:

1.  Item one
1.  Item two
1.  Item three
1.  Item four

### And a nested list:

- level 1 item
  - level 2 item
  - level 2 item
    - level 3 item
    - level 3 item
- level 1 item
  - level 2 item
  - level 2 item
  - level 2 item
- level 1 item
  - level 2 item
  - level 2 item
- level 1 item

### Small image

![Octocat](https://github.githubassets.com/images/icons/emoji/octocat.png)

### Large image

![Branching](https://guides.github.com/activities/hello-world/branching.png)


### Definition lists can be used with HTML syntax.

<dl>
<dt>Name</dt>
<dd>Godzilla</dd>
<dt>Born</dt>
<dd>1952</dd>
<dt>Birthplace</dt>
<dd>Japan</dd>
<dt>Color</dt>
<dd>Green</dd>
</dl>

```
Long, single-line code blocks should not wrap. They should horizontally scroll if they are too long. This line should be long enough to demonstrate this.
```

```
The final element.
``` -->
