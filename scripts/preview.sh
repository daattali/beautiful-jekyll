#!/usr/bin/env bash
# Preview the site on your own computer before publishing.
# Usage: bash scripts/preview.sh   then open http://localhost:8000   (Ctrl+C to stop)
cd "$(dirname "$0")/.."
PORT="${1:-8000}"
echo "Preview running at http://localhost:$PORT  (press Ctrl+C to stop)"
if command -v python3 >/dev/null; then python3 -m http.server "$PORT"; else python -m http.server "$PORT"; fi
