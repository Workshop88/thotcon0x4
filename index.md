---
layout: page
---
{% include JB/setup %}

![Badge Rendering](badge.png "Badge Rendering")

<ul class="posts">
  {% for post in site.posts %}
    <li><span>{{ post.date | date_to_string }}</span> &raquo; <a href="{{ BASE_PATH }}{{ post.url }}">{{ post.title }}</a></li>
  {% endfor %}
</ul>


Links to other Badge Related Posts:<br>
<ul><li> 
Kyle Essobi was the first to pull the firmware: <a href="http://www.repyoblog.com/index.php/2013/05/thotcon-0x4-badge/">read more here</a>
</li></ul>
 
