---
layout: page
title: Thotcon 0x4 Badges
tagline: Workshop 88
---
{% include JB/setup %}

![Badge Rendering](badge.png "Badge Rendering")

<ul class="posts">
  {% for post in site.posts %}
    <li><span>{{ post.date | date_to_string }}</span> &raquo; <a href="{{ BASE_PATH }}{{ post.url }}">{{ post.title }}</a></li>
  {% endfor %}
</ul>


