---
layout: page
title: Books
subtitle: I've read
published: true
---

|Title                                           |Comment             |Rating            |
|------------------------------------------------|--------------------|------------------|
{% for book in site.data.books_review.rows -%}
{% if book.title -%}
|<a href="{{ book.url }}"> {{ book.title }}  </a>| {{ book.comment }} | {{ book.rating}} |
{% endif %}
{%- endfor -%}
|------------------------------------------------|--------------------|------------------|
