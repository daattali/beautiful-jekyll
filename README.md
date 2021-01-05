# About The Site
This is the official website of [DSSE Research Group](http://dsse.github.io/) at [IIT University of Dhaka](http://iit.du.ac.bd/).
<br>
This website is powered by [Jekyll](https://jekyllrb.com/) and some Bootstrap, Bootwatch. The design is adopted from
[Allan Lab](https://github.com/mpa139/allanlab). 

## How to Update Website Contents

The site contains a [**_data**](https://github.com/DSSE/dsse.github.io/blob/gh-pages/_data/) directory to store all its content.
The directory contains several **_.yml_** files to store different types of contents as mentioned below:

* Recent News
* Members & Alumni
* Research Domains & Publications
* Blog Posts
* Photos

A short description is provided to learn how to add/update each type of content into this site.

* ### Add Recent News

To add a recent news item, it requires to append the following entry at 
**the top** of **[_news.yml_](https://github.com/DSSE/dsse.github.io/blob/gh-pages/_data/news.yml)** file.
```yml
- date: 1<sup>st</sup> January 2021
  headline: "Demo News"
```
* ### Add Members

To add a new member, it requires to append the following entry in [**_members.yml_**](https://github.com/DSSE/dsse.github.io/blob/gh-pages/_data/members.yml) file. 
In generally, the entry should be at the  end of the file.<br> 
However, it can be placed anywhere to maintain the order/ serialization of members. <br>
Similarly, to add a new alumni just add an entry to the [**_alumni.yml_**](https://github.com/DSSE/dsse.github.io/blob/gh-pages/_data/alumni.yml) file.
``` yml
- name: 
  photo: dummy_dp.png
  current_position:
  current_organization:
  email: 
  # Homepage can be personal website/ Google Scholar/ LinkedIn or any other authenticated educational profiles such as Resarch_Gate, GitHub etc.
  # However, keep it professional, do not add any social network account.
  homepage:
  # The value of number_educ varies between 1 to 5. Depending on the value, change the education1, education2 and so on.
  number_educ: 2
  education1:
  education2:  
```

* ### Add Research Domain

To add a Research Domain, it requires to append the following entry in the [**_research_domains.yml_**](https://github.com/DSSE/dsse.github.io/blob/gh-pages/_data/research_domains.yml) file.
```yaml
# serial no
- broad_domain_name: Code Search
  domain_id: code_search
```

* ### Add Publications

To add a publication, it requires to append the following entry at **the top** of [**_publication_list.yml_**](https://github.com/DSSE/dsse.github.io/blob/gh-pages/_data/publication_list.yml) file.
```yaml
  # Mandatory field
- title: "" 
  # Mandatory field. List of all authors, separated by comma 
  authors: 
  # Mandatory field
  # Add the full booktitle as DBLP provides and includes the page numbers and publisher as a single string . 
  # (For journal include volume, page number other information )
  booktitle: 
  # Mandatory field as the (filtering requires year)
  year: 2020
  # Mandatory field. Must include least one domain_id (provided in _data/research_domains.yml)
  # If the paper falls in multiple research domains, add multiple domain_id separated by 'space'
  # The domain_id must be presented in the research_domains.yml file before adding into the publications.
  domain_id:
  # Mandatory field, type must be one of these 4 (Journal, Conference, Arxiv, Thesis)
  type:
  # If available, provide the paper pdf link
  pdf:
  # If available, provide Digital Library (DL) url
  url:
  # If available, provide digital object identifier as provided in DBLP  
  doi:
  # If available, provide the paper artifacts link, such as source code GitHub link, or provided dataset link
  code_link:
```

* ### Add Blog Posts

To add a new post, it requires to create a **_YYYY-MM-DD-post-short-title.md_** 
file inside the [**__post_**](https://github.com/DSSE/dsse.github.io/tree/gh-pages/_posts) directory.<br>
The **_file name must be_** in **_YYYY-MM-DD-post-short-title.md_** format.<br>
Before writing the post contents, the following entry must be made at the top of the **_YYYY-MM-DD-post-short-title.md_** file.


```yaml
---
# Mandatory field 'posts'
layout: posts
title:
subtitle:
author: 
cover-img: /images/blog-post/img_file
thumbnail-img: /images/blog-post/img_file
share-img: /images/blog-post/img_file
tags: [tag_name]
permalink: /YYYY-MM-DD-post-short-title/
comments: false
---

# post content ...

```


* ### Add  Photos

To add a new photo, it requires to append the following entry in [**_photos.yml_**](https://github.com/DSSE/dsse.github.io/blob/gh-pages/_data/photos.yml).
<br> However, to place the photo in  specific position, make the entry in exact serialization order.

```yaml
# serial no
- title: photo description
  image: photo_file_name.jpg
```
