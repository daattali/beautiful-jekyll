<!-- using projects in template
include in index.html or portfoliio.html -->

{% assign projects = site.data.projects | get_projects_from_files | sort:'date' %}
{% for project in projects reversed %}
    <!-- portfolio-item -->
    <h2>{{ project.title }} <span>{{ project.category | slugify }}</h2>

    <a href="/{{ project.dir }}">
        <img src="{{ project.image.url }}" alt="{{ project.image.alt }}" title="{{ project.image.title }}">
    </a>
    <!-- portfolio-item -->
{% endfor %}

<!-- This will show your projects with the most-recent being first (if you include the date in your project files). I recommend always using the get_projects_from_files filter. Without it, you'll have to do this, and the projects won't be in reverse chronological order: -->

{% for project_file in site.data.projects %}
    {% assign project = project_file[1] %}
    <!-- portfolio-item -->
    <h2>{{ project.title }} <span>{{ project.category | slugify }}</h2>

    <a href="/{{ project.dir }}">
        <img src="{{ project.image.url }}" alt="{{ project.image.alt }}" title="{{ project.image.title }}">
    </a>
    <!-- portfolio-item -->
{% endfor %}

Related Projects

Related projects are generated for each project by computing the number of matches between the projects and adding the projects as related if they are greater than or equal to the minimum required. They are sorted such that the most related appear first.

Using Related Projects in Templates

Assuming this is in the project.html layout file:

{% if page.related_projects.size > 0 %}
<h3>Related Projects</h3>
{% for project in page.related_projects %}
<a href="/{{ project.dir }} ">
    <img src="{{ project.image.url }}" alt="{{ project.image.alt }}" title="{{ project.image.title }}">
</a>
{% endfor %}
{% endif %}
The plugin adds all related projects, so if a project has a lot of related projects, you might have to add a limit, like so:

{% if page.related_projects.size > 0 %}
<h3>Related Projects</h3>
{% for project in page.related_projects limit:3 %}
<a href="/{{ project.dir }} ">
    <img src="{{ project.image.url }}" alt="{{ project.image.alt }}" title="{{ project.image.title }}">
</a>
{% endfor %}
{% endif %}
