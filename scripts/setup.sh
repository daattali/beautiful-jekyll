#!/usr/bin/env bash
# ONE-TIME SETUP
# Creates your GitHub repository, uploads the site, and switches on GitHub Pages.
#
# Usage:   bash scripts/setup.sh              -> site at https://<username>.github.io/
#          bash scripts/setup.sh my-website   -> site at https://<username>.github.io/my-website/
#
# Needs git and the GitHub CLI ("gh"), logged in once with: gh auth login
set -euo pipefail
cd "$(dirname "$0")/.."

command -v git >/dev/null || { echo "Please install git first: https://git-scm.com/downloads"; exit 1; }
command -v gh  >/dev/null || { echo "Please install the GitHub CLI first: https://cli.github.com"; exit 1; }
gh auth status >/dev/null 2>&1 || { echo "Please log in first by running: gh auth login"; exit 1; }

USER_NAME="$(gh api user --jq .login)"
USER_LOWER="$(echo "$USER_NAME" | tr '[:upper:]' '[:lower:]')"
REPO="${1:-$USER_LOWER.github.io}"
echo "Setting up https://github.com/$USER_NAME/$REPO ..."

# Local git repository
[ -d .git ] || git init -b main >/dev/null
git config user.name  >/dev/null || git config user.name  "$USER_NAME"
git config user.email >/dev/null || git config user.email "$USER_NAME@users.noreply.github.com"
git add -A
git commit -m "Launch personal website" >/dev/null || echo "Nothing new to commit."
git branch -M main

# Create the GitHub repository (or reuse it if it already exists) and push
if gh repo view "$USER_NAME/$REPO" >/dev/null 2>&1; then
  git remote get-url origin >/dev/null 2>&1 || git remote add origin "https://github.com/$USER_NAME/$REPO.git"
  git push -u origin main
else
  gh repo create "$REPO" --public --source . --remote origin --push \
    --description "Personal website of Aarushi Sehgal"
fi

# Switch on GitHub Pages, deployed by the workflow in .github/workflows/deploy.yml
if gh api -X POST "repos/$USER_NAME/$REPO/pages" -f build_type=workflow >/dev/null 2>&1 \
   || gh api -X PUT "repos/$USER_NAME/$REPO/pages" -f build_type=workflow >/dev/null 2>&1; then
  echo "GitHub Pages is on."
else
  echo "Couldn't switch Pages on automatically. On GitHub open: Settings > Pages > Source > GitHub Actions"
fi

# The first push ran before Pages existed, so run the deploy once more
sleep 3
gh workflow run deploy.yml --repo "$USER_NAME/$REPO" >/dev/null 2>&1 || true

if [ "$REPO" = "$USER_LOWER.github.io" ]; then URL="https://$USER_LOWER.github.io/"; else URL="https://$USER_LOWER.github.io/$REPO/"; fi
echo ""
echo "Done! Your site will be live in 1-2 minutes at: $URL"
echo "Watch it deploy at: https://github.com/$USER_NAME/$REPO/actions"
