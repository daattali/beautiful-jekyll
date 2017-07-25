---
layout: post
title:	Remarkup
subtitle: inspired tags
#image: # /path/to/img
#bigimg:	# /path/to/img - or multiple entries <- "Path": "Description">
category: Test
tags: [remarkup]
css: "/css/boxes.css"

---

## Tooltip Classes

### src

#### as markdown

![markdown box example](/img/markdown-box-example.png)

#### hybrid form
Without the fontawesome plugin you can't use the liquid tag `icon`. You have to use a hybrid form like this:

```html
{: .box-note}
<i class="fa fa-commenting icon-blue" aria-hidden="true"></i> **Note:** This is a note message.
```


#### as html

```html
<div class="box-note">
<i class="fa fa-commenting icon-blue" aria-hidden="true"></i> <b>Note:</b> This is a note.
</div>
```

### Examples

{: .box-note}
<i class="fa fa-commenting icon-blue" aria-hidden="true"/> **Note:** This is a note.

{: .box-warning}
<i class="fa fa-bolt icon-yellow" aria-hidden="true"/> **Warning:** This is is a warning message.

{: .box-error}
<i class="fa fa-exclamation-circle icon-red" aria-hidden="true"/> **Error:** This is is an error message.