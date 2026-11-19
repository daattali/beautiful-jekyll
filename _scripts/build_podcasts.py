"""Regenerate _data/podcasts.yml for thegeekspeaks.io from a Pocket Casts OPML export.

Run: python3 _scripts/build_podcasts.py <pocketcasts-export.opml> _data/podcasts.yml
Never commit the OPML export: it contains private feed URLs with access tokens.

Private/paid feeds (Patreon auth tokens, Substack private feeds, premium feeds)
are never written to the public page: they get a public page link or no link.
"""
import html
import json
import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

opml_path, out_path = sys.argv[1], sys.argv[2]

SECTIONS = [
    "Film",
    "TV & Pop Culture",
    "Technology & Product",
    "Government & Civic Tech",
    "Arizona & Phoenix",
    "News & Politics",
    "Comedy",
]

CATEGORY = {
    # Film
    "Geek On Film": "Film",
    "The No Film School Podcast": "Film",
    "70mm": "Film",
    "You Must Remember This": "Film",
    "Duel of the Fates": "Film",
    "The Next Picture Show": "Film",
    "The Next Best Picture Podcast": "Film",
    "The Cinematic Schematic": "Film",
    "The Town with Matthew Belloni": "Film",
    "The Box Office Podcast": "Film",
    "MUBI Podcast": "Film",
    "/Film Weekly": "Film",
    "Blank Check with Griffin & David": "Film",
    "Blank Check: Special Features": "Film",
    "Free With Ads": "Film",
    "Little Gold Men by Vanity Fair": "Film",
    "See It or Shove It": "Film",
    "You Need To See This!": "Film",
    "Doug Loves Movies": "Film",
    "The Director’s Cut - A DGA Podcast": "Film",
    "The A24 Podcast": "Film",
    "Filmspotting Family": "Film",
    "The History on Film Podcast": "Film",
    "21st Century Spielberg": "Film",
    "Unspooled": "Film",
    "This Had Oscar Buzz": "Film",
    "Academy Conversations Uncut": "Film",
    "Haven't Scene It: A Movie Podcast": "Film",
    "Film School Fridays": "Film",
    "The Rewatchables": "Film",
    "The Directors Series Podcast": "Film",
    "Pulling Focus": "Film",
    "We Love It Really": "Film",
    "Critical Darlings": "Film",
    "Talking Pictures": "Film",
    "Ankler Agenda": "Film",
    "The Laser Age": "Film",
    "This Aged Great!": "Film",
    "The Filmcast": "Film",
    "FilmWeek": "Film",
    "Weekend Film Reviews": "Film",
    "Popcorn Cinema": "Film",
    "Filmspotting: Streaming Video Unit (SVU)": "Film",
    "The Big Picture": "Film",
    "CRWN CINEMA Podcast": "Film",
    "Movies That Raised Us": "Film",
    "IndieWire: Screen Talk": "Film",
    "Don't Kill the Messenger with Movie Strategist Kevin Goetz": "Film",
    "Film Vs Film": "Film",
    "The History of Film": "Film",
    "The Letterboxd Show": "Film",
    "Cinephobe": "Film",
    "The Rough Cut": "Film",
    "Blindspotters": "Film",
    "Flixwise Podcast": "Film",
    "The Podcorn Kernels": "Film",
    "Feeling Seen": "Film",
    "Eye of the Duck: A Film Podcast": "Film",
    "Who Watches The Watchlist?": "Film",
    "Ruined with Alison Leiby and Halle Kiefer": "Film",
    "The Revisionist’s Almanac": "Film",
    # TV & Pop Culture
    "Critics at Large | The New Yorker": "TV & Pop Culture",
    "Culturally Relevant with David Chen": "TV & Pop Culture",
    "Pluribus: The Official Podcast": "TV & Pop Culture",
    "Prestige Junkie": "TV & Pop Culture",
    "The Prestige TV Podcast": "TV & Pop Culture",
    "Cannonball with Wesley Morris": "TV & Pop Culture",
    "Jam Session": "TV & Pop Culture",
    "Pop Culture Happy Hour": "TV & Pop Culture",
    "iFanboy - Comic Books": "TV & Pop Culture",
    "House of R": "TV & Pop Culture",
    "The Ringer-Verse": "TV & Pop Culture",
    "Pop Cultured": "TV & Pop Culture",
    "The Watch": "TV & Pop Culture",
    "The Hottest Take": "TV & Pop Culture",
    "X-Ray Vision": "TV & Pop Culture",
    "Forever Fangirls": "TV & Pop Culture",
    "The Official Game of Thrones Podcast: House of the Dragon": "TV & Pop Culture",
    "HBO's The Last of Us Podcast": "TV & Pop Culture",
    "Damn Fine Podcast - A Twin Peaks Podcast": "TV & Pop Culture",
    "Still Watching": "TV & Pop Culture",
    "IMDb Is Obsessed": "TV & Pop Culture",
    "Fresh Air": "TV & Pop Culture",
    "The Sam Sanders Show": "TV & Pop Culture",
    "I Think You're Overthinking It": "TV & Pop Culture",
    "Martini Shot": "TV & Pop Culture",
    "Search Engine": "TV & Pop Culture",
    "Fat Man Beyond": "TV & Pop Culture",
    "The Bill Simmons Podcast": "TV & Pop Culture",
    "WatchCats": "TV & Pop Culture",
    "The Confused Breakfast": "TV & Pop Culture",
    "Commentarely Legal": "TV & Pop Culture",
    "Oh, hi! Stories Podcast": "TV & Pop Culture",
    # Technology & Product
    "Giant Robots Smashing Into Other Giant Robots": "Technology & Product",
    "The Product Podcast": "Technology & Product",
    "The Last Invention": "Technology & Product",
    "Pivot": "Technology & Product",
    # Government & Civic Tech
    "GovLove - A Podcast About Local Government": "Government & Civic Tech",
    "The Business of Government Hour": "Government & Civic Tech",
    "GovEx Data Points": "Government & Civic Tech",
    "Civic Tech Chat": "Government & Civic Tech",
    "The GovNavigators Show": "Government & Civic Tech",
    "Game Changers for Government Contractors": "Government & Civic Tech",
    "Think Civic": "Government & Civic Tech",
    "Community IT Innovators Nonprofit Technology Topics": "Government & Civic Tech",
    "The Strong Towns Podcast": "Government & Civic Tech",
    # Arizona & Phoenix
    "Phoenix Prosperity Podcast": "Arizona & Phoenix",
    "Venture Cafe Phoenix an Extraordinary Podcast": "Arizona & Phoenix",
    "Arizona Technology Council’s TechFocus Member Spotlight Podcast": "Arizona & Phoenix",
    "AZ TechCast": "Arizona & Phoenix",
    # News & Politics
    "Somebody's Gotta Win with Tara Palmeri": "News & Politics",
    "Up First from NPR": "News & Politics",
    "The NPR Politics Podcast": "News & Politics",
    "Mo News": "News & Politics",
    "The Powers That Be: Daily": "News & Politics",
    "Political Gabfest": "News & Politics",
    "Rachel Maddow Presents: Ultra": "News & Politics",
    "The Rachel Maddow Show": "News & Politics",
    "Pod Save America": "News & Politics",
    "All In with Chris Hayes": "News & Politics",
    "What A Day": "News & Politics",
    "The Daily": "News & Politics",
    "The Ezra Klein Show": "News & Politics",
    "Hysteria": "News & Politics",
    "FiveThirtyEight Politics": "News & Politics",
    "Pod Save the World": "News & Politics",
    "Lovett or Leave It": "News & Politics",
    "Still Counting": "News & Politics",
    # Comedy
    "All Fantasy Everything": "Comedy",
    "Never Not Funny": "Comedy",
    "Dumb People Town": "Comedy",
    "Fitzdog Radio": "Comedy",
    "Mohr Stories": "Comedy",
    "Nerd Poker": "Comedy",
    "SModcast": "Comedy",
    "Hollywood Babble-On": "Comedy",
    "The Daily Show: Ears Edition": "Comedy",
    "Alison Rosen Is Your New Best Friend": "Comedy",
    "Inside of You with Michael Rosenbaum": "Comedy",
    "The Lonely Island and Seth Meyers Podcast": "Comedy",
    "We Should Be Working": "Comedy",
    "Childish": "Comedy",
    "How To Survive with Danielle & Kristine": "Comedy",
}

# Display-name cleanups for feeds whose title describes a private feed.
RENAME = {
    "The Next Best Picture Podcast - Patreon Exclusive": "The Next Best Picture Podcast",
    "Never Not Funny | Platinum Audio": "Never Not Funny",
}
# Title prefixes for private feeds whose full title includes personal details
# (e.g. a subscriber email) that must not be committed to this public repo.
RENAME_PREFIX = {
    "The Box Office Podcast (private feed": "The Box Office Podcast",
}

# Private or premium feeds: never publish the feed URL. Public page only, if known.
PRIVATE = {
    "The Next Best Picture Podcast": {
        "url": "https://nextbestpicture.com/",
        "support": "https://www.patreon.com/NextBestPicture"},
    # Merged into the public Blank Check entry below.
    "Blank Check: Special Features": None,
    "Pop Cultured": {"support": "https://www.patreon.com/popcultured"},
    "The Box Office Podcast": {
        "url": "https://scottmendelson.substack.com/",
        "itunes": "https://podcasts.apple.com/us/podcast/id1731232795",
        "support": "https://scottmendelson.substack.com/subscribe"},
    "Filmspotting Family": {
        "name": "Filmspotting",
        "url": "https://www.filmspotting.net/",
        "support": "https://filmspotting.supportingcast.fm/"},
    # Platinum is the paid feed; link the public show (from the existing page).
    "Never Not Funny": {
        "url": "https://www.nevernotfunny.com/",
        "itunes": "https://podcasts.apple.com/us/podcast/never-not-funny/id142348028",
        "rss": "https://rss.art19.com/never-not-funny",
        "x": "nevernotfunny"},
}

# Shows Robbie pays to support: they stay in their own section and get a support
# link, which the layout marks with a $ icon. (PRIVATE shows also set support.)
SUPPORTED_EXTRA = {
    "Blank Check with Griffin & David": {"support": "https://www.patreon.com/blankcheck"},
    "Never Not Funny": {"support": "https://www.nevernotfunny.com/"},
}

SKIP = {
    "The 20th Anniversary Spectacular",  # one-off premium special
    # Subscribed in Pocket Casts but left off the page (trimmed by Robbie, 2026-11-19).
    "21st Century Spielberg", "70mm", "Blindspotters", "The Cinematic Schematic", "Cinephobe",
    "CRWN CINEMA Podcast", "Don't Kill the Messenger with Movie Strategist Kevin Goetz",
    "Doug Loves Movies", "Duel of the Fates", "Eye of the Duck: A Film Podcast", "Feeling Seen",
    "Film School Fridays", "Film Vs Film", "Flixwise Podcast", "Free With Ads",
    "Haven't Scene It: A Movie Podcast", "The History of Film", "The History on Film Podcast",
    "The Laser Age", "Movies That Raised Us", "The Podcorn Kernels", "Popcorn Cinema",
    "Pulling Focus", "The Revisionist’s Almanac", "The Rough Cut", "See It or Shove It",
    "Talking Pictures", "This Aged Great!", "Unspooled", "We Love It Really",
    "Who Watches The Watchlist?", "You Must Remember This", "You Need To See This!",
    "The Bill Simmons Podcast", "Commentarely Legal", "The Confused Breakfast",
    "Culturally Relevant with David Chen", "Damn Fine Podcast - A Twin Peaks Podcast",
    "Forever Fangirls", "Fresh Air", "HBO's The Last of Us Podcast", "The Hottest Take",
    "Jam Session", "Martini Shot", "Pluribus: The Official Podcast", "Search Engine", "WatchCats",
    "GovEx Data Points", "The Strong Towns Podcast", "Rachel Maddow Presents: Ultra",
    "Somebody's Gotta Win with Tara Palmeri", "Fitzdog Radio", "Hollywood Babble-On",
    "Inside of You with Michael Rosenbaum", "The Lonely Island and Seth Meyers Podcast", "SModcast",
    "We Should Be Working",
    "The Directors Series Podcast",  # feed 404s and no confirmed new home (2026-11-19)
}

# Apple Podcasts links, public RSS feeds and X handles looked up per show (2026-11-19),
# keyed by display name. Applied after KEEP; fills in or replaces those fields.
with open(Path(__file__).with_name("podcast_links.json"), encoding="utf-8") as f:
    LINKS = json.load(f)

# Links and handles already curated on the current page, kept for shows still on the list.
KEEP = {
    "Geek On Film": {"url": "https://geekonfilm.com/",
                     "itunes": "https://podcasts.apple.com/us/podcast/geek-on-film/id1637502307",
                     "x": "geekonfilmcom"},
    "Giant Robots Smashing Into Other Giant Robots": {
        "url": "https://giantrobots.fm/",
        "itunes": "https://podcasts.apple.com/us/podcast/giant-robots-smashing-into/id535121941",
        "x": "thoughtbot"},
    "All Fantasy Everything": {"url": "https://headgum.com/all-fantasy-everything",
                               "itunes": "https://podcasts.apple.com/us/podcast/id1155320115",
                               "x": "AllFantasyPod"},
    "The Filmcast": {"url": "https://www.slashfilm.com/category/features/slashfilmcast/",
                     "itunes": "https://podcasts.apple.com/us/podcast/the-filmcast-aka-the-slashfilmcast/id281400220",
                     "x": "slashfilmcast"},
    "Pop Culture Happy Hour": {"url": "https://www.npr.org/podcasts/510282/pop-culture-happy-hour",
                               "itunes": "https://podcasts.apple.com/podcast/id278974813",
                               "x": "pchh"},
}


def looks_private(url):
    u = url.lower()
    return any(s in u for s in ("auth=", "/private/", "supportingcast.fm", "nevernotfunny.com/rss",
                                "specials.nevernotfunny.com"))


def clean_name(name):
    if name in RENAME:
        return RENAME[name]
    for prefix, new in RENAME_PREFIX.items():
        if name.startswith(prefix):
            return new
    return name


def q(s):
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'


shows, seen = {}, set()
for o in ET.parse(opml_path).iter("outline"):
    feed = o.get("xmlUrl")
    if not feed:
        continue
    name = clean_name(html.unescape(o.get("text")).strip())
    if name in SKIP or name in seen:  # dedupe (Giant Robots appears twice)
        continue
    seen.add(name)
    entry = {"name": name}
    if name in PRIVATE:
        if PRIVATE[name] is None:
            continue
        entry.update(PRIVATE[name])
    elif looks_private(feed):
        sys.exit(f"Unmapped private feed for {name!r}; add it to PRIVATE before publishing.")
    else:
        entry["rss"] = feed
    entry.update(KEEP.get(name, {}))
    entry.update(LINKS.get(entry["name"], {}))
    entry.update(SUPPORTED_EXTRA.get(name, {}))
    section = CATEGORY.get(name)
    if not section:
        sys.exit(f"No section for {name!r}; add it to CATEGORY.")
    shows.setdefault(section, []).append(entry)

lines = ["# Generated from a Pocket Casts OPML export by build_podcasts.py.",
         "# Private/paid feed URLs are intentionally omitted.", ""]
for section in SECTIONS:
    items = shows.get(section, [])
    if not items:
        continue
    pinned = [i for i in items if i["name"] == "Geek On Film"]
    rest = sorted((i for i in items if i["name"] != "Geek On Film"),
                  key=lambda i: i["name"].lower().lstrip("/").removeprefix("the "))
    lines.append(f"- section: {q(section)}")
    lines.append("  podcasts:")
    for i in pinned + rest:
        lines.append(f"    - name: {q(i['name'])}")
        for k in ("url", "itunes", "rss", "x", "support"):
            if i.get(k):
                lines.append(f"      {k}: {q(i[k])}")
text = "\n".join(lines) + "\n"
# Same patterns as the pre-merge grep in the Trello card. (Narrower than looks_private, which
# would also flag the public filmspotting.supportingcast.fm support page.)
if re.search(r"auth=|/private/|supportingcast\.fm/content|nevernotfunny\.com/RSS", text, re.I):
    sys.exit("Refusing to write: a private-looking feed URL made it into the output.")
with open(out_path, "w", encoding="utf-8") as f:
    f.write(text)
print({s: len(shows.get(s, [])) for s in SECTIONS}, "total", sum(len(v) for v in shows.values()))
