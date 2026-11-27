# Aarushi Sehgal — personal website

A fast, multi-page static site in a calm editorial style (inspired by al-folio academic sites),
with light and dark themes. No build step: edit the HTML, push, and GitHub Pages redeploys.

```
index.html                 about (home): bio, animated mosaic background, news, selected papers, off the clock
research/index.html        research rows, "try it" (mini game + repeat slider), clinical immersion
publications/index.html    papers grouped by year, each with an "in brief" summary, filters, cite button
tools/index.html           software as spec-sheet rows with copy-paste install commands
cv/index.html              CV download, experience, education, skills, teaching, mentoring
404.html                   "page not found"
assets/
  Aarushi_Sehgal_CV.pdf    the CV people download (replace to update)
  styles.css               all styling; light and dark colours at the very top
  site.js                  theme toggle, copy buttons, filters, back-to-top
  ambient.js               the home page's animated mosaic background
  game.js / repeat.js      the research page's mini game and repeat slider
.github/workflows/deploy.yml   checks pages and links, then publishes
scripts/                   setup, preview, update and custom-domain helpers
```

## Before you publish

1. **Off the clock.** Near the bottom of `index.html`, four entries are still `[in brackets]`.
   Fill them in, or delete those `<div><dt>…</dt><dd>…</dd></div>` lines. The workflow warns while any remain.
2. **Your CV file.** `assets/Aarushi_Sehgal_CV.pdf` is the resume you uploaded, including your phone
   number and home address. Replace it (same filename) if you'd rather not publish those.
3. **Facts to double-check:** the paper summaries on `publications/index.html`, and the prancSTR install
   commands and GitHub links on `tools/index.html`.
4. **Optional photo.** The round mosaic on the home page stands in for a photo. To use yours, put
   `profile.jpg` in `assets/` and replace the `<div class="avatar" …>…</div>` block in `index.html` with
   `<div class="avatar" style="padding:0"><img src="assets/profile.jpg" alt="Aarushi Sehgal"></div>`.

## Publish (about 5 minutes)

You need a free GitHub account, **git** (https://git-scm.com/downloads) and the **GitHub CLI**
(https://cli.github.com). On Windows, use *Git Bash*.

```bash
gh auth login                 # once: log in to GitHub
cd path/to/aarushi-website
bash scripts/setup.sh         # creates the repo, uploads the site, turns on Pages
```

The site goes live at `https://<your-username>.github.io/` within a couple of minutes
(watch the repository's **Actions** tab). Keep the default repository name: the 404 page assumes
the site lives at the root of the address.

**Already set up the earlier version?** Replace the files in your existing folder with these
(delete the old `about/` folder), then run `bash scripts/update.sh "New design"`.

**No terminal?** Create a public repository named `<your-username>.github.io`, upload everything
except `scripts/` and `.github/`, then set **Settings › Pages › Source** to *Deploy from a branch*,
branch `main`, folder `/ (root)`.

## Making changes

```bash
bash scripts/preview.sh                    # check edits at http://localhost:8000
bash scripts/update.sh "Added new paper"   # publish; live in about a minute
```

| To change | Do this |
|---|---|
| Add a paper | In `publications/index.html`, copy an `<li class="pub" …>` block into the right year section. Add `first` to the class for first-author work. `data-tags` drives the filters: `first`, `genomics`, `journal`, `talk`, `earlier` |
| Link a paper directly | Replace its Google Scholar link (the **Find paper** button) with the DOI link |
| Add a news item | Add an `<li><time>…</time><p>…</p></li>` at the top of the news list in `index.html` |
| Add a tool | In `tools/index.html`, copy an `<article class="spec">` block, give it an `id`, and add a matching chip to the chooser at the top |
| Replace the CV | Overwrite `assets/Aarushi_Sehgal_CV.pdf` and update the size/date line in `cv/index.html` |
| Colours | The variables at the top of `assets/styles.css` (one block for light, two identical blocks for dark) |
| Menu or footer | Repeated at the top and bottom of each page; change the same lines in each |
| Calmer background | In `assets/ambient.js`, lower `MAX_CLONES`, or delete the `<div class="ambient">` line in `index.html` to remove it |

## Optional: your own domain

```bash
bash scripts/set-custom-domain.sh aarushisehgal.com
```
Then add the DNS records it prints at your registrar, and switch on HTTPS once the domain loads.

## Troubleshooting

- **First Actions run failed:** expected, since Pages wasn't on yet. `setup.sh` re-runs it; or click **Run workflow** under *Actions › Deploy website*.
- **"Broken link" in Actions:** the error names the page and the link to fix.
- **Changes not showing:** wait a minute, then hard-refresh (Ctrl+Shift+R, or Cmd+Shift+R on a Mac).
