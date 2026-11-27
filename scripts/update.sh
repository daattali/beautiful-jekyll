#!/usr/bin/env bash
# Publish your edits. Saves everything you changed and pushes it to GitHub;
# the workflow then redeploys the live site automatically (about a minute).
# Usage: bash scripts/update.sh "Added my headshot"
set -euo pipefail
cd "$(dirname "$0")/.."
MESSAGE="${1:-Update website}"
git add -A
if git diff --cached --quiet; then
  echo "No changes to publish."
  exit 0
fi
git commit -m "$MESSAGE"
git push
echo "Pushed! The live site updates in about a minute. Progress: the Actions tab of your repository."
