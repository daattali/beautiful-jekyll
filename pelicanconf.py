LOAD_CONTENT_CACHE = False

AUTHOR = 'PYM'
SITENAME = "A PYM's life"
SITEURL = 'http://pym.pam.poum.free.fr/blog'
# For local serve use the command :
# make html serve PELICANOPTS="-e SITEURL='\"http://localhost:8000\"'"

# Theme specific
SITESUBTITLE = "Quand l'improbable est juste le quotidien"
LICENCE = 'CC-BY-SA 4.0'

# Where to find content
PATH = 'content'

# metadata extraction from filename and path
USE_FOLDER_AS_CATEGORY = False
PATH_METADATA = '(?P<basepath>.*)/(?P<date>\d{4}-\d{2}-\d{2})-(?P<slug>.*)/(?P<shortname>.*)\..*' # the name of the file itself doesn't matter

ARTICLE_PATHS = ['blog']
ARTICLE_URL = 'blog/{date:%Y}-{date:%m}-{date:%d}-{slug}/'
ARTICLE_SAVE_AS = ARTICLE_URL + 'index.html'
STATIC_PATHS = ['blog']  # in order to have images in the same place as articles

TIMEZONE = 'Europe/Rome'

DEFAULT_LANG = 'fr'

# Theme stuffs
THEME = "themes/html5up-editorial"
THEME_TEMPLATES_OVERRIDES = ["themes/overrides"]

# Feed generation is usually not desired when developing
FEED_ALL_ATOM = None
CATEGORY_FEED_ATOM = None
TRANSLATION_FEED_ATOM = None
AUTHOR_FEED_ATOM = None
AUTHOR_FEED_RSS = None

# Blogroll
LINKS = (('Pelican', 'https://getpelican.com/'),
         ('Python.org', 'https://www.python.org/'),
         ('Jinja2', 'https://palletsprojects.com/p/jinja/'),
         ('You can modify those links in your config file', '#'),)

# Social widget
SOCIAL = (('You can add links in your config file', '#'),
          ('Another social link', '#'),)

CONTACTS = [
    ("Telegram", "telegram", "https://t.me/pymaldebaran"),
    ("Twitter", "twitter", "https://twitter.com/pymaldebaran"),
    ("Facebook", "facebook-f", "https://www.facebook.com/pym.aldebaran"),
    ("Instagram", "instagram", "https://www.instagram.com/pym.aldebaran/"),
    ("Github", "github", "https://github.com/pymaldebaran"),
]

# Number of object per index page
DEFAULT_PAGINATION = 6

# Uncomment following line if you want document-relative URLs when developing
#RELATIVE_URLS = True


PANDOC_DEFAULT_FILES = [
    "pandoc_defaults.yaml",
]
