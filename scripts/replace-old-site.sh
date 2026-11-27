#!/usr/bin/env bash
# REPLACE AN EXISTING <username>.github.io SITE WITH THIS ONE
# - saves your old site in a backup branch (nothing is deleted from GitHub)
# - puts this new site on the branch your repo already uses (master or main)
# - switches GitHub Pages to deploy with the included GitHub Actions workflow
#
# Usage (run from inside this unzipped aarushi-website folder):
#   bash scripts/replace-old-site.sh                 -> uses <username>.github.io
#   bash scripts/replace-old-site.sh some-repo-name  -> uses another repo
#
# Needs git and the GitHub CLI ("gh"), logged in once with: gh auth login
set -euo pipefail
SITE_DIR="$(cd "$(dirname "$0")/.." && pwd)"

command -v git >/dev/null || { echo "Please install git first: https://git-scm.com/downloads"; exit 1; }
command -v gh  >/dev/null || { echo "Please install the GitHub CLI first: https://cli.github.com"; exit 1; }
gh auth status >/dev/null 2>&1 || { echo "Please log in first by running: gh auth login"; exit 1; }
gh auth setup-git >/dev/null 2>&1 || true   # lets git push using your gh login

USER_NAME="$(gh api user --jq .login)"
USER_LOWER="$(echo "$USER_NAME" | tr '[:upper:]' '[:lower:]')"
REPO="${1:-$USER_LOWER.github.io}"
CLONE_DIR="$(dirname "$SITE_DIR")/$REPO"

if [ -e "$CLONE_DIR" ]; then
  echo "A folder already exists at $CLONE_DIR"
  echo "Move or rename it, then run this script again."
  exit 1
fi

echo "1/5  Downloading your current repository $USER_NAME/$REPO ..."
gh repo clone "$USER_NAME/$REPO" "$CLONE_DIR" -- --quiet
cd "$CLONE_DIR"
BRANCH="$(git symbolic-ref --short HEAD)"
BACKUP="old-site-backup"
git ls-remote --exit-code --heads origin "$BACKUP" >/dev/null 2>&1 && BACKUP="old-site-backup-$(date +%Y%m%d-%H%M%S)"

echo "2/5  Saving your old site to the branch '$BACKUP' ..."
git push --quiet origin "HEAD:refs/heads/$BACKUP"

echo "3/5  Replacing the files on '$BRANCH' with the new site ..."
git config user.name  >/dev/null || git config user.name  "$USER_NAME"
git config user.email >/dev/null || git config user.email "$USER_NAME@users.noreply.github.com"
if [ -n "$(git ls-files)" ]; then git rm -r -q .; fi
( cd "$SITE_DIR" && tar -cf - --exclude=./.git . ) | tar -xf -
if [ "$BRANCH" != "main" ] && [ "$BRANCH" != "master" ]; then
  # make the deploy workflow run on pushes to this repository's branch too
  sed -i.bak "s/branches: \[main, master\]/branches: [main, master, $BRANCH]/" .github/workflows/deploy.yml
  rm -f .github/workflows/deploy.yml.bak
  grep -q "branches: \[main, master, $BRANCH\]" .github/workflows/deploy.yml \
    || { echo "Couldn't add '$BRANCH' to .github/workflows/deploy.yml; add it to the 'branches:' line by hand."; exit 1; }
fi
git add -A
git commit -q -m "Launch new website (old site saved in branch $BACKUP)"

echo "4/5  Switching GitHub Pages to deploy with GitHub Actions ..."
if gh api -X PUT "repos/$USER_NAME/$REPO/pages" -f build_type=workflow >/dev/null 2>&1 \
   || gh api -X POST "repos/$USER_NAME/$REPO/pages" -f build_type=workflow >/dev/null 2>&1; then
  echo "     Done."
else
  echo "     Couldn't switch automatically. On GitHub open: Settings > Pages > Source > GitHub Actions"
fi

echo "5/5  Uploading the new site ..."
git push --quiet origin "$BRANCH"

if git ls-remote --exit-code --heads origin main >/dev/null 2>&1 && [ "$BRANCH" != "main" ]; then
  echo ""
  echo "Note: there's also a 'main' branch (perhaps from an earlier setup attempt). The live site comes"
  echo "from '$BRANCH'. You can delete 'main' with:  git push origin --delete main"
fi

if [ "$REPO" = "$USER_LOWER.github.io" ]; then URL="https://$USER_LOWER.github.io/"; else URL="https://$USER_LOWER.github.io/$REPO/"; fi
echo ""
echo "All done! Your new site will be live in 1-2 minutes at: $URL"
echo "Watch it deploy:      https://github.com/$USER_NAME/$REPO/actions"
echo "Your old site is safe in the branch '$BACKUP'."
echo ""
echo "From now on, make changes in this folder:  $CLONE_DIR"
echo "  bash scripts/preview.sh    and    bash scripts/update.sh \"what you changed\""
