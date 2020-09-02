---
layout: page
title: Members
subtitle:
members:
  - name: Faculty
    list:
      - full: true
        list:
          - name: David Held
            photo_url: /img/members/daveheld.jpg
            web_url: https://davheld.github.io
  - name: Current members
    list:
      - name: PhD students
        full: true
        list:
          - name: Brian Okorn
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2016/12/okorn_brian_2019.jpg
            web_url: https://www.ri.cmu.edu/ri-people/brian-e-okorn/
          - name: Siddarth (Sid) Ancha
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2017/05/nophoto_faceboard_white.jpg
            web_url: https://scholar.google.com/citations?user=H8e3R2JADJEC&hl=en
          - name: Xingyu Lin
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2018/01/Xingyu.Lin_-1.jpg
            web_url: https://xingyu-lin.github.io/
          - name: Thomas Weng
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2017/04/weng_thomas_2018.jpg
            web_url: https://www.thomasweng.com
          - name: Wenxuan Zhou
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2017/07/zhou_wenxuan_2019_1.jpg
            web_url: https://www.ri.cmu.edu/ri-people/wenxuan-zhou/
      - name: Master students
        full: true
        list:
          - name: Gautham Narayan Narasimhan
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2017/05/nophoto_faceboard_white.jpg
            web_url: https://www.ri.cmu.edu/ri-people/gautham-narayan-narasimhan/
          - name: Sujay Bajrachaya
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2019/08/bajracharya_sujay_2019_2.jpg
            web_url: https://www.ri.cmu.edu/ri-people/sujay-bajracharya/
          - name: Qiao Gu
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2019/08/gu_qiao_2019_1.jpg
            web_url: https://www.ri.cmu.edu/ri-people/qiao-gu/
          - name: Harshit Sikchi
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2017/05/nophoto_faceboard_white.jpg
            web_url: https://hari-sikchi.github.io/
          - name: Yufei Wang
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2017/05/nophoto_faceboard_white.jpg
            web_url: https://yufeiwang63.github.io/
          - name: Himangi Mittal
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2017/05/nophoto_faceboard_white.jpg
            web_url: https://www.ri.cmu.edu/ri-people/himangi-mittal/
          - name: Jianren Wang
            photo_url: https://www.ri.cmu.edu/wp-content/uploads/2017/05/nophoto_faceboard_white.jpg
            web_url: https://jianrenw.github.io/
      - name: Visiting Students
        full: false
        list:
          - name: Khush Agrawal (RISS)
            web_url: https://khush3.github.io/
          - name: Rohan Chacko
            web_url: https://rohanchacko.github.io/
          - name: Shubham Sahoo
            web_url: https://www.scs.cmu.edu/directory/ssahoo2
  - name: Alumni
    list:
      - name: Master's students
        full: False
        list:
          - name: Jianing (Aurora) Qian (MSR)
            web_url: https://www.ri.cmu.edu/ri-people/jianing-qian/
          - name: Junyu Nan (MSCV)
            web_url: https://www.ri.cmu.edu/ri-people/junyu-nan/
      - name: Undergraduate students
        full: False
        list:
          - name: Jake Olkin
      - name: Visiting students
        full: False
        list:
          - name: Yimin Tang (RISS)
          - name: Ziwen Zhuang (RISS)
          - name: Zhaoyuan (Andy) Fang
          - name: Yujie Lu
          - name: Amith Pallankize
---

<div class="row">
  {% for big_group in page.members %}
    <h1> {{big_group.name}} </h1>
    {% for group in big_group.list %}
    {% if group.list.size > 0 %}
      {% if group.name %}
        <h2>{{ group.name }}</h2>
      {% endif %}
      {% if group.full %}
      <div class="row member-row">
        {% for member in group.list %}
          <div class="col-xl-2 col-lg-2 col-md-3 text-center col-sm-6 col-xs-6 member-col">
            <a target="_blank" href="{{ member.web_url }}">
              <img class="img-responsive" src="{{ member.photo_url }}" alt="Dave Held">
            </a>
            <a target="_blank" href="{{ member.web_url }}">
              {{ member.name }}
            </a>
          </div>
        {% endfor %}
      </div>
      {% else %}
        <ul>
          {% for member in group.list %}
            {% if member.web_url %}
              <li><a href="{{member.web_url}}"> {{member.name}} </a></li>
            {% else %}
              <li><a> {{member.name}} </a></li>
            {% endif %}
          {% endfor %}
        </ul>
      {% endif %}
    {% endif %}
    {% endfor %}
  {% endfor %}
</div>


<!-- <h3 id="undergraduate-students">Undergraduate students</h3>
<ul>
</ul>
</div> -->

<!-- <h2 id="collaborators">Collaborators</h2> -->
<!-- <ul>
  <li><a href="https://www.cs.cmu.edu/~astein/">Aaron Steinfeld</a></li>
  <li><a href="https://www.cs.cmu.edu/~kkitani/">Kris Kitani</a></li>
  <li><a href="http://www.lauravherlant.com/">Laura Herlant</a></li>
</ul> -->
