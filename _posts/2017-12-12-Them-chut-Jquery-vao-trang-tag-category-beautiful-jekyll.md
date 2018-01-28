---
layout: post
title: Thêm chút - Jquery vào trang blog sử dụng theme beautiful-jekyll
image: /img/2017-12-12-Jekyll/create_jekyll_blog.jpg
tags: [Lap-trinh, programming-language, Front-end, Jquery]
categories: [Dev-Frontend]
date:   2017-12-12

---
**Phiên bản mặc định của theme beautiful-jekyll khá là đơn điệu không có trang tags và category. Sau đó cộng đồng sử dụng beautiful-jekyll có thêm các template cho phép sử dụng markup # để di chuyển đến các vị trí trong trang. Việc nhảy nhảy trang này khá rối mắt. Nhân tiện đang xem lại Jquery, thực hiện áp dụng tí css, jquery vào để cho sinh động hơn chút**

Mô tả thay đổi:
Bạn vào trang tags, category sẽ thấy mặc định hiển thị ra hết. Khi chúng ta nhấn vào 1 tag hoặc 1 category nào đó trên cloud thì ẩn hết các container chứa các tag/category khác và di chuyển đến container chứa tag/category mới chọn.

![tag](/img/2017-12-12-Jekyll/tag1.png)

![tag](/img/2017-12-12-Jekyll/tag2.png)

![tag](/img/2017-12-12-Jekyll/tag3.png)


# Cách thực hiện với phần tags:

## HTML:
Tạo một file tags.html ở thư mục gốc của blog (hoặc chỗ nào đó tùy ý tác giả) có nội dung: 
```HTML
---
layout: page
title: Tags
---

<div class="tags-expo">
  <div class="tags-expo-list">
    {% for tag in site.tags %}
	<a href="/tag#{{ tag[0] }}-ref" class="post-tag" id="{{ tag[0] }}"><i class="fa fa-tag" aria-hidden="true"></i> 
		{{ tag[0] }} ({{ tag[1].size }})</a>
    {% endfor %}
    <br>
    <a href="#" class="post-tag1" id="showall"><i class="fa fa-tags" aria-hidden="true"></i> Xem tất cả </a>
  </div>

  <hr/>

  <div class="tags-expo-section">
	{% for tag in site.tags %}
		<div class="tags-container" id="{{ tag[0] }}-con">
			<h2 id="{{ tag[0] }}-ref">{{ tag[0] }}</h2>
			<ul class="tags-expo-posts">
			{% for post in tag[1] %}
				<a class="post-title" href="{{ site.baseurl }}{{ post.url }}">
			<li>
				{{ post.title }}
			<small class="post-date">({{ post.date | date_to_string }})</small>
			</li>
			</a>
			{% endfor %}
			</ul>
		</div>
	{% endfor %}
  </div>
  
</div>

```

# CSS:

Mở file main.css thuộc thư mục css\main.css, thêm đoạn code sau:

```CSS

/* tag define */

.post-tag {
  display: inline-block;
  background: rgba(106,159,181,0.15);
  padding: 0 .5rem;
  margin-right: .5rem;
  border-radius: 4px;
  color:#6a9fb5;
  font-family: "PT Sans",Helvetica,Arial,sans-serif;
  font-size: 90%;
}

.post-tag::before
{
    /* content: "\f02b"; */
    padding-right: .5em;
}

a.post-tag:hover
{
    text-decoration: none;
    background: #327490;
    color: white;
  }
  

.tags-expo {
  :target:before {
    content:"";
    display:block;
    height:72px; /* fixed header height*/
    margin:-72px 0 0; /* negative fixed header height */
  }
  .tags-expo-list {
    @media (min-width: 38em) {
      font-size: 0.9rem;
      .post-tag {
        margin: .2em .3em;
      }
    }
  }

.tags-expo-section {
    ul {
      list-style-type: circle;
      list-style-position: inside;
      padding: 0;
      li {
        @include transition(all .1s ease-in-out);
        padding: 0 1rem;
        &:hover {
          list-style-type: disc;
          padding: 0 .5rem;
        }
      }
    }
    a {
      text-decoration: none;
    }
    .post-date {
      display: inline-block;
      font-size: 80%;
      color: gray;
      margin: 0;
      padding: 0;
    }
  }
}

.hide-tag{
  display: none
}
```

# Javascript (Jquery)

Mở file main.js thuộc thư mục js/main.js
Thêm đoạn mã sau vào đầu tiên của đoạn   `init : function()`

```JS
    // TAG
    url_window = $(location).attr('href');
		t_index = url_window.indexOf("#");
		if(t_index > -1)
		{
			$('.tags-container').addClass('hide-tag');
			tag_id = url_window.substring(t_index + 1, url_window.length - 4);
			$('#' + tag_id + '-con').removeClass('hide-tag');
		}

		$('.post-tag').click(function(){
			var tag_id = $(this).attr('id');
			$('.tags-container').addClass('hide-tag');
			$('#' + tag_id + '-con').removeClass('hide-tag');
			$('body,html').animate({scrollTop:$('#' + tag_id + '-con').offset().top});
			return false;
    });
       
    $('#showall').click(function(){
      $('.tags-container').removeClass('hide-tag');
      return false;
    });
    // #Endtag
```

## file sinh dữ liệu _tag_gen.rb
tạo file  _tag_gen.rb trong thư mục _plugins có nội dung:

```ruby
module Jekyll
  class TagIndex < Page
    def initialize(site, base, dir, tag)
      @site = site
      @base = base
      @dir = dir
      @name = 'index.html'
      self.process(@name)
      self.read_yaml(File.join(base, '_layouts'), 'tag_index.html')
      self.data['tag'] = tag
      tag_title_prefix = site.config['tag_title_prefix'] || 'Posts Tagged &ldquo;'
      tag_title_suffix = site.config['tag_title_suffix'] || '&rdquo;'
      self.data['title'] = "#{tag_title_prefix}#{tag}#{tag_title_suffix}"
    end
  end
  class TagGenerator < Generator
    safe true
    def generate(site)
      if site.layouts.key? 'tag_index'
        dir = site.config['tag_dir'] || 'tag'
        site.tags.keys.each do |tag|
          write_tag_index(site, File.join(dir, tag), tag)
        end
      end
    end
    def write_tag_index(site, dir, tag)
      index = TagIndex.new(site, site.source, dir, tag)
      index.render(site.layouts, site.site_payload)
      index.write(site.dest)
      site.pages << index
    end
  end
end
```

# Cách thực hiện với phần category:

## HTML:
tạo file category.html

```HTML
---
layout: page
title: Category
---

<div class="tags-expo">
  <!-- <div class="tags-expo-list">
    {% for tag in site.categories %}
    <a href="#{{ tag[0] | slugify }}" class="post-tag">{{ tag[0] }}</a>
    {% endfor %}
  </div> -->

  <div class="tags-expo-list">
        {% for tag in site.categories %}
      <a href="/category#{{ tag[0] }}-ref" class="post-tag" id="{{ tag[0] }}"><i class="fa fa-bars" aria-hidden="true"></i> 
        {{ tag[0] }} ({{ tag[1].size }})</a>
        {% endfor %}
        <br>
        <a href="" class="post-tag1" id="showall"><i class="fa fa-th-list" aria-hidden="true"></i> Xem tất cả </a>
      </div>

  <hr/>
  <div class="tags-expo-section">
    {% for tag in site.categories %}
      <div class="tags-container" id="{{ tag[0] }}-con">
        <h2 id="{{ tag[0] | slugify }}">{{ tag[0] }}</h2>
        <ul class="tags-expo-posts">
          {% for post in tag[1] %}
            <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">
          <li>
            {{ post.title }} 
          <small class="post-date">({{ post.date | date_to_string }})</small>
          </li>
          </a>
          {% endfor %}
        </ul>
    </div>
    {% endfor %}
  </div>
</div>
```

# Sửa phần hiển thị TAG trên post

## Post
Mở file post.html tại thư mục layout\post.html, tìm đến đoạn:

```HTML
      {% if page.tags.size > 0 %}
        <div class="blog-tags">
          Tags:
          {% if site.link-tags %}
          {% for tag in page.tags %}
            <a href="/tag/{{ tag }}">{{ tag }}</a>
          {% endfor %}
          {% else %}
            {{ page.tags | join: ", " }}
          {% endif %}
        </div>
      {% endif %}

```

Thay đổi `<a href="/tag/{{ tag }}">{{ tag }}</a>` thành 
`<a href="/tags/#{{ tag }}-ref">{{ tag }}</a>`

