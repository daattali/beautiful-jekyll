---
layout: post
title: Basic Markdown
subtitle: Markdown Basic You Must Know
tags: [git, github, markdown, md]
image: /img/diary.png
bigimg: /img/background.png
share-img: /img/diary.png
toc: true
toc_float: true
---

# Markdown Cheetsheat for Easy Note Taking

You may have heard about Markdown, if you have it's a good thing.

Markdown is a plain text formatting syntax designed so that it can optionally be converted to HTML.

# Markdown Cheatsheet<a name="TOP"></a>
_Qucik Link to Specific Topic:_
- [Markdown Cheetsheat for Easy Note Taking](#markdown-cheetsheat-for-easy-note-taking)
- [Markdown Cheatsheet<a name="TOP"></a>](#markdown-cheatsheet)
- [Heading 1](#heading-1)
  - [Heading 2](#heading-2)
    - [Heading 3](#heading-3)
      - [Heading 4](#heading-4)
  - [Block Elements](#block-elements)
    - [Paragraphs and Line Breaks](#paragraphs-and-line-breaks)
      - [Paragraphs](#paragraphs)
      - [Line Breaks](#line-breaks)
    - [Headers](#headers)
      - [Setext](#setext)
- [This is an H1](#this-is-an-h1)
  - [This is an H2](#this-is-an-h2)
      - [atx](#atx)
- [This is an H1](#this-is-an-h1-1)
  - [This is an H2](#this-is-an-h2-1)
          - [This is an H6](#this-is-an-h6)
- [This is an H1](#this-is-an-h1-2)
  - [This is an H2](#this-is-an-h2-2)
    - [This is an H3](#this-is-an-h3)
    - [Blockquotes](#blockquotes)
    - [Lists](#lists)
      - [Unordered](#unordered)
      - [Ordered](#ordered)
      - [Indented](#indented)
        - [Blockquote](#blockquote)
        - [Code Block](#code-block)
        - [Nested List](#nested-list)
    - [Code Blocks](#code-blocks)
      - [Fenced Code Blocks](#fenced-code-blocks)
      - [Syntax Highlighting](#syntax-highlighting)
    - [Horizontal Rules](#horizontal-rules)
    - [Table](#table)
  - [Span Elements](#span-elements)
    - [Links](#links)
      - [Inline](#inline)
      - [Reference](#reference)
    - [Emphasis](#emphasis)
    - [Code](#code)
    - [Images](#images)
      - [Inline](#inline-1)
      - [Reference](#reference-1)
    - [Strikethrough](#strikethrough)
  - [Miscellaneous](#miscellaneous)
    - [Automatic Links](#automatic-links)
    - [Backslash Escapes](#backslash-escapes)
  - [Inline HTML](#inline-html)
  - [Boxes](#boxes)
    - [Notification](#notification)
    - [Warning](#warning)
    - [Error](#error)

---

# Heading 1

    Markup :  # Heading 1 #

    -OR-

    Markup :  ============= (below H1 text)

## Heading 2

    Markup :  ## Heading 2 ##

    -OR-

    Markup: --------------- (below H2 text)

### Heading 3

    Markup :  ### Heading 3 ###

#### Heading 4

    Markup :  #### Heading 4 ####

Common text

    Markup :  Common text

_Emphasized text_

    Markup :  _Emphasized text_ or *Emphasized text*

~~Strikethrough text~~

    Markup :  ~~Strikethrough text~~

**Strong text**

    Markup :  __Strong text__ or **Strong text**

**_Strong emphasized text_**

    Markup :  ___Strong emphasized text___ or ***Strong emphasized text***

[Named Link](http://www.google.fr/ "Named link title") and http://www.google.fr/ or <http://example.com/>

    Markup :  [Named Link](http://www.google.fr/ "Named link title") and http://www.google.fr/ or <http://example.com/>

[heading-1](#heading-1 "Goto heading-1")

    Markup: [heading-1](#heading-1 "Goto heading-1")

Table, like this one :

| First Header | Second Header |
| ------------ | ------------- |
| Content Cell | Content Cell  |
| Content Cell | Content Cell  |

```
First Header  | Second Header
------------- | -------------
Content Cell  | Content Cell
Content Cell  | Content Cell
```

Adding a pipe `|` in a cell :

| First Header | Second Header |
| ------------ | ------------- |
| Content Cell | Content Cell  |
| Content Cell | \|            |

```
First Header  | Second Header
------------- | -------------
Content Cell  | Content Cell
Content Cell  |  \|
```

Left, right and center aligned table

| Left aligned Header | Right aligned Header | Center aligned Header |
| :------------------ | -------------------: | :-------------------: |
| Content Cell        |         Content Cell |     Content Cell      |
| Content Cell        |         Content Cell |     Content Cell      |

```
Left aligned Header | Right aligned Header | Center aligned Header
| :--- | ---: | :---:
Content Cell  | Content Cell | Content Cell
Content Cell  | Content Cell | Content Cell
```

`code()`

    Markup :  `code()`

```javascript
var specificLanguage_code = {
  data: {
    lookedUpPlatform: 1,
    query: "Kasabian+Test+Transmission",
    lookedUpItem: {
      name: "Test Transmission",
      artist: "Kasabian",
      album: "Kasabian",
      picture: null,
      link: "http://open.spotify.com/track/5jhJur5n4fasblLSCOcrTp",
    },
  },
};
```

    Markup : ```javascript
             ```

- Bullet list
  - Nested bullet
    - Sub-nested bullet etc
- Bullet list item 2

```
 Markup : * Bullet list
              * Nested bullet
                  * Sub-nested bullet etc
          * Bullet list item 2

-OR-

 Markup : - Bullet list
              - Nested bullet
                  - Sub-nested bullet etc
          - Bullet list item 2
```

1. A numbered list
   1. A nested numbered list
   2. Which is numbered
2. Which is numbered

```
 Markup : 1. A numbered list
              1. A nested numbered list
              2. Which is numbered
          2. Which is numbered
```

- [ ] An uncompleted task
- [x] A completed task

```
 Markup : - [ ] An uncompleted task
          - [x] A completed task
```

- [ ] An uncompleted task
  - [ ] A subtask

```
 Markup : - [ ] An uncompleted task
              - [ ] A subtask
```

> Blockquote
>
> > Nested blockquote

    Markup :  > Blockquote
              >> Nested Blockquote

_Horizontal line :_

---

    Markup :  - - - -

_Image with alt :_

![picture alt](https://github.com/rafayethossain/rafayethossain.github.io/blob/master/img/background.png?raw=true/200x150 "Title is optional")

    Markup : ![picture alt](https://github.com/rafayethossain/rafayethossain.github.io/blob/master/img/background.png?raw=true/200x150 "Title is optional")

Foldable text:

<details>
  <summary>Title 1</summary>
  <p>Content 1 Content 1 Content 1 Content 1 Content 1</p>
</details>
<details>
  <summary>Title 2</summary>
  <p>Content 2 Content 2 Content 2 Content 2 Content 2</p>
</details>

    Markup : <details>
               <summary>Title 1</summary>
               <p>Content 1 Content 1 Content 1 Content 1 Content 1</p>
             </details>

```html
<h3>HTML</h3>
<p>Some HTML code here</p>
```

Link to a specific part of the page:

[Go To TOP](#TOP)

    Markup : [text goes here](#section_name)
              section_title<a name="section_name"></a>

Hotkey list:

| Key       | Symbol |
| --------- | ------ |
| Option    | ⌥      |
| Control   | ⌃      |
| Command   | ⌘      |
| Shift     | ⇧      |
| Caps Lock | ⇪      |
| Tab       | ⇥      |
| Esc       | ⎋      |
| Power     | ⌽      |
| Return    | ↩      |
| Delete    | ⌫      |
| Up        | ↑      |
| Down      | ↓      |
| Left      | ←      |
| Right     | →      |

## Block Elements

### Paragraphs and Line Breaks

#### Paragraphs

HTML Tag: `<p>`

One or more blank lines. (A blank line is a line containing nothing but **spaces** or **tabs** is considered blank.)

Code:

    This will be
    inline.

    This is second paragraph.

Preview:

---

This will be
inline.

This is second paragraph.

---

#### Line Breaks

HTML Tag: `<br />`

End a line with **two or more spaces**.

Code:

    This will be not
    inline.

Preview:

---

This will be not  
inline.

---

### Headers

Markdown supports two styles of headers, Setext and atx.

#### Setext

HTML Tags: `<h1>`, `<h2>`

“Underlined” using **equal signs (=)** as `<h1>` and **dashes (-)** as `<h2>` in any number.

Code:

    This is an H1
    =============
    This is an H2
    -------------

Preview:

---

# This is an H1

## This is an H2

---

#### atx

HTML Tags: `<h1>`, `<h2>`, `<h3>`, `<h4>`, `<h5>`, `<h6>`

Uses 1-6 **hash characters (#)** at the start of the line, corresponding to `<h1>` - `<h6>`.

Code:

    # This is an H1
    ## This is an H2
    ###### This is an H6

Preview:

---

# This is an H1

## This is an H2

###### This is an H6

---

Optionally, you may “close” atx-style headers. The closing hashes **don’t need to match** the number of hashes used to open the header.

Code:

    # This is an H1 #
    ## This is an H2 ##
    ### This is an H3 ######

Preview:

---

# This is an H1

## This is an H2

### This is an H3

---

### Blockquotes

HTML Tag: `<blockquote>`

Markdown uses email-style **>** characters for blockquoting. It looks best if you hard wrap the text and put a > before every line.

Code:

    > This is a blockquote with two paragraphs. Lorem ipsum dolor sit amet,
    > consectetuer adipiscing elit. Aliquam hendrerit mi posuere lectus.
    > Vestibulum enim wisi, viverra nec, fringilla in, laoreet vitae, risus.
    >
    > Donec sit amet nisl. Aliquam semper ipsum sit amet velit. Suspendisse
    > id sem consectetuer libero luctus adipiscing.

Preview:

---

> This is a blockquote with two paragraphs. Lorem ipsum dolor sit amet,
> consectetuer adipiscing elit. Aliquam hendrerit mi posuere lectus.
> Vestibulum enim wisi, viverra nec, fringilla in, laoreet vitae, risus.
>
> Donec sit amet nisl. Aliquam semper ipsum sit amet velit. Suspendisse
> id sem consectetuer libero luctus adipiscing.

---

Markdown allows you to be lazy and only put the > before the first line of a hard-wrapped paragraph.

Code:

    > This is a blockquote with two paragraphs. Lorem ipsum dolor sit amet,
    consectetuer adipiscing elit. Aliquam hendrerit mi posuere lectus.
    Vestibulum enim wisi, viverra nec, fringilla in, laoreet vitae, risus.

    > Donec sit amet nisl. Aliquam semper ipsum sit amet velit. Suspendisse
    id sem consectetuer libero luctus adipiscing.

Preview:

---

> This is a blockquote with two paragraphs. Lorem ipsum dolor sit amet,
> consectetuer adipiscing elit. Aliquam hendrerit mi posuere lectus.
> Vestibulum enim wisi, viverra nec, fringilla in, laoreet vitae, risus.

> Donec sit amet nisl. Aliquam semper ipsum sit amet velit. Suspendisse
> id sem consectetuer libero luctus adipiscing.

---

Blockquotes can be nested (i.e. a blockquote-in-a-blockquote) by adding additional levels of >.

Code:

    > This is the first level of quoting.
    >
    > > This is nested blockquote.
    >
    > Back to the first level.

Preview:

---

> This is the first level of quoting.
>
> > This is nested blockquote.
>
> Back to the first level.

---

Blockquotes can contain other Markdown elements, including headers, lists, and code blocks.

Code:

    > ## This is a header.
    >
    > 1.   This is the first list item.
    > 2.   This is the second list item.
    >
    > Here's some example code:
    >
    >     return shell_exec("echo $input | $markdown_script");

Preview:

---

> ## This is a header.
>
> 1.  This is the first list item.
> 2.  This is the second list item.
>
> Here's some example code:
>
>     return shell_exec("echo $input | $markdown_script");

---

### Lists

Markdown supports ordered (numbered) and unordered (bulleted) lists.

#### Unordered

HTML Tag: `<ul>`

Unordered lists use **asterisks (\*)**, **pluses (+)**, and **hyphens (-)**.

Code:

    *   Red
    *   Green
    *   Blue

Preview:

---

- Red
- Green
- Blue

---

is equivalent to:

Code:

    +   Red
    +   Green
    +   Blue

and:

Code:

    -   Red
    -   Green
    -   Blue

#### Ordered

HTML Tag: `<ol>`

Ordered lists use numbers followed by periods:

Code:

    1.  Bird
    2.  McHale
    3.  Parish

Preview:

---

1.  Bird
2.  McHale
3.  Parish

---

It’s possible to trigger an ordered list by accident, by writing something like this:

Code:

    1986. What a great season.

Preview:

---

1986. What a great season.

---

You can **backslash-escape (\\)** the period:

Code:

    1986\. What a great season.

Preview:

---

1986\. What a great season.

---

#### Indented

##### Blockquote

To put a blockquote within a list item, the blockquote’s > delimiters need to be indented:

Code:

    *   A list item with a blockquote:

        > This is a blockquote
        > inside a list item.

Preview:

---

- A list item with a blockquote:

  > This is a blockquote
  > inside a list item.

---

##### Code Block

To put a code block within a list item, the code block needs to be indented twice — **8 spaces** or **two tabs**:

Code:

    *   A list item with a code block:

            <code goes here>

Preview:

---

- A list item with a code block:

      <code goes here>

---

##### Nested List

Code:

    * A
      * A1
      * A2
    * B
    * C

Preview:

---

- A
  - A1
  - A2
- B
- C

---

### Code Blocks

HTML Tag: `<pre>`

Indent every line of the block by at least **4 spaces** or **1 tab**.

Code:

    This is a normal paragraph:

        This is a code block.

Preview:

---

This is a normal paragraph:

    This is a code block.

---

A code block continues until it reaches a line that is not indented (or the end of the article).

Within a code block, **_ampersands (&)_** and angle **brackets (< and >)** are automatically converted into HTML entities.

Code:

        <div class="footer">
            &copy; 2004 Foo Corporation
        </div>

Preview:

---

    <div class="footer">
        &copy; 2004 Foo Corporation
    </div>

---

Following sections Fenced Code Blocks and Syntax Highlighting are extensions, you can use the other way to write the code block.

#### Fenced Code Blocks

Just wrap your code in ` ``` ` (as shown below) and you won't need to indent it by four spaces.

Code:

    Here's an example:

    ```
    function test() {
      console.log("notice the blank line before this function?");
    }
    ```

Preview:

---

Here's an example:

```
function test() {
  console.log("notice the blank line before this function?");
}
```

---

#### Syntax Highlighting

In your fenced block, add an optional language identifier and we'll run it through syntax highlighting ([Support Languages](https://github.com/github/linguist/blob/master/lib/linguist/languages.yml)).

Code:

    ```ruby
    require 'redcarpet'
    markdown = Redcarpet.new("Hello World!")
    puts markdown.to_html
    ```

Preview:

---

```ruby
require 'redcarpet'
markdown = Redcarpet.new("Hello World!")
puts markdown.to_html
```

---

### Horizontal Rules

HTML Tag: `<hr />`
Places **three or more hyphens (-), asterisks (\*), or underscores (\_)** on a line by themselves. You may use spaces between the hyphens or asterisks.

Code:

    * * *
    ***
    *****
    - - -
    ---------------------------------------
    ___

Preview:

---

---

---

---

---

---

---

---

### Table

HTML Tag: `<table>`

It's an extension.

Separates column by **pipe (|)** and header by **dashes (-)**, and uses **colon (:)** for alignment.

The outer **pipes (|)** and alignment are optional. There are **3 delimiters** each cell at least for separating header.

Code:

```
| Left | Center | Right |
|:-----|:------:|------:|
|aaa   |bbb     |ccc    |
|ddd   |eee     |fff    |

 A | B
---|---
123|456


A |B
--|--
12|45
```

Preview:

---

| Left | Center | Right |
| :--- | :----: | ----: |
| aaa  |  bbb   |   ccc |
| ddd  |  eee   |   fff |

| A   | B   |
| --- | --- |
| 123 | 456 |

| A   | B   |
| --- | --- |
| 12  | 45  |

---

## Span Elements

### Links

HTML Tag: `<a>`

Markdown supports two style of links: inline and reference.

#### Inline

Inline link format like this: `[Link Text](URL "Title")`

Title is optional.

Code:

    This is [an example](http://example.com/ "Title") inline link.

    [This link](http://example.net/) has no title attribute.

Preview:

---

This is [an example](http://example.com/ "Title") inline link.

[This link](http://example.net/) has no title attribute.

---

If you’re referring to a local resource on the same server, you can use relative paths:

Code:

    See my [About](/about/) page for details.

Preview:

---

See my [About](/about/) page for details.

---

#### Reference

You could predefine link references. Format like this: `[id]: URL "Title"`

Title is also optional. And the you refer the link, format like this: `[Link Text][id]`

Code:

    [id]: http://example.com/  "Optional Title Here"
    This is [an example][id] reference-style link.

Preview:

---

[id]: http://example.com/ "Optional Title Here"

This is [an example][id] reference-style link.

---

That is:

- Square brackets containing the link identifier (**not case sensitive**, optionally indented from the left margin using up to three spaces);
- followed by a colon;
- followed by one or more spaces (or tabs);
- followed by the URL for the link;
- The link URL may, optionally, be surrounded by angle brackets.
- optionally followed by a title attribute for the link, enclosed in double or single quotes, or enclosed in parentheses.

The following three link definitions are equivalent:

Code:

    [foo]: http://example.com/  "Optional Title Here"
    [foo]: http://example.com/  'Optional Title Here'
    [foo]: http://example.com/  (Optional Title Here)
    [foo]: <http://example.com/>  "Optional Title Here"

Uses an empty set of square brackets, the link text itself is used as the name.

Code:

    [Google]: http://google.com/
    [Google][]

Preview:

---

[google]: http://google.com/

[Google][]

---

### Emphasis

HTML Tags: `<em>`, `<strong>`

Markdown treats **asterisks (\*)** and **underscores (\_)** as indicators of emphasis. **One delimiter** will be `<em>`; \*_double delimiters_ will be `<strong>`.

Code:

    *single asterisks*

    _single underscores_

    **double asterisks**

    __double underscores__

Preview:

---

_single asterisks_

_single underscores_

**double asterisks**

**double underscores**

---

But if you surround an \* or \_ with spaces, it’ll be treated as a literal asterisk or underscore.

You can backslash escape it:

Code:

    \*this text is surrounded by literal asterisks\*

Preview:

---

\*this text is surrounded by literal asterisks\*

---

### Code

HTML Tag: `<code>`

Wraps it with **backtick quotes (`)**.

Code:

    Use the `printf()` function.

Preview:

---

Use the `printf()` function.

---

To include a literal backtick character within a code span, you can use **multiple backticks** as the opening and closing delimiters:

Code:

    ``There is a literal backtick (`) here.``

Preview:

---

`` There is a literal backtick (`) here. ``

---

The backtick delimiters surrounding a code span may include spaces — one after the opening, one before the closing. This allows you to place literal backtick characters at the beginning or end of a code span:

Code:

    A single backtick in a code span: `` ` ``

    A backtick-delimited string in a code span: `` `foo` ``

Preview:

---

A single backtick in a code span: `` ` ``

A backtick-delimited string in a code span: `` `foo` ``

---

### Images

HTML Tag: `<img />`

Markdown uses an image syntax that is intended to resemble the syntax for links, allowing for two styles: inline and reference.

#### Inline

Inline image syntax looks like this: `![Alt text](URL "Title")`

Title is optional.

Code:

    ![Alt text](/path/to/img.jpg)

    ![Alt text](/path/to/img.jpg "Optional title")

Preview:

---

![Alt text](/path/to/img.jpg)

![Alt text](/path/to/img.jpg "Optional title")

---

That is:

- An exclamation mark: !;
- followed by a set of square brackets, containing the alt attribute text for the image;
- followed by a set of parentheses, containing the URL or path to the image, and an optional title attribute enclosed in double or single quotes.

#### Reference

Reference-style image syntax looks like this: `![Alt text][id]`

Code:

    [img id]: url/to/image  "Optional title attribute"
    ![Alt text][img id]

Preview:

---

[img id]: url/to/image "Optional title attribute"

![Alt text][img id]

---

### Strikethrough

HTML Tag: `<del>`

It's an extension.

GFM adds syntax to strikethrough text.

Code:

```
~~Mistaken text.~~
```

Preview:

---

~~Mistaken text.~~

---

## Miscellaneous

### Automatic Links

Markdown supports a shortcut style for creating “automatic” links for URLs and email addresses: simply surround the URL or email address with angle brackets.

Code:

    <http://example.com/>

    <address@example.com>

Preview:

---

<http://example.com/>

<address@example.com>

---

GFM will autolink standard URLs.

Code:

```
https://github.com/emn178/markdown
```

Preview:

---

https://github.com/emn178/markdown

---

### Backslash Escapes

Markdown allows you to use backslash escapes to generate literal characters which would otherwise have special meaning in Markdown’s formatting syntax.

Code:

    \*literal asterisks\*

Preview:

---

\*literal asterisks\*

---

Markdown provides backslash escapes for the following characters:

Code:

    \   backslash
    `   backtick
    *   asterisk
    _   underscore
    {}  curly braces
    []  square brackets
    ()  parentheses
    #   hash mark
    +   plus sign
    -   minus sign (hyphen)
    .   dot
    !   exclamation mark

## Inline HTML

For any markup that is not covered by Markdown’s syntax, you simply use HTML itself. There’s no need to preface it or delimit it to indicate that you’re switching from Markdown to HTML; you just use the tags.

Code:

    This is a regular paragraph.

    <table>
        <tr>
            <td>Foo</td>
        </tr>
    </table>

    This is another regular paragraph.

Preview:

---

This is a regular paragraph.

<table>
    <tr>
        <td>Foo</td>
    </tr>
</table>

This is another regular paragraph.

---

Note that Markdown formatting syntax is **not processed within block-level HTML tags**.

Unlike block-level HTML tags, Markdown syntax is **processed within span-level tags**.

Code:

    <span>**Work**</span>

    <div>
        **No Work**
    </div>

Preview:

---

<span>**Work**</span>

<div>
  **No Work**
</div>
***


## Boxes
You can add notification, warning and error boxes like this:

### Notification

{: .box-note}
**Note:** This is a notification box.

{: .box-success}
**Success:** This is a success box.

{: .box-primary}
**Primary:** This is a primary box.


### Warning

{: .box-warning}
**Warning:** This is a warning box.

### Error

{: .box-error}
**Error:** This is an error box.

Enjoy !!!
**See Yaaa, Next.**
