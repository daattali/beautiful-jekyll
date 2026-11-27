#!/usr/bin/env bash
# Optional: use your own domain (for example aarushisehgal.com) instead of <username>.github.io
# Usage: bash scripts/set-custom-domain.sh aarushisehgal.com [repository-name]
set -euo pipefail
DOMAIN="${1:?Usage: bash scripts/set-custom-domain.sh yourdomain.com}"
USER_NAME="$(gh api user --jq .login)"
USER_LOWER="$(echo "$USER_NAME" | tr '[:upper:]' '[:lower:]')"
REPO="${2:-$USER_LOWER.github.io}"

gh api -X PUT "repos/$USER_NAME/$REPO/pages" -f cname="$DOMAIN" >/dev/null
echo "GitHub now expects your site at $DOMAIN."
echo ""
echo "Next, add these DNS records where you bought the domain:"
echo "  Type A     Name @     Value 185.199.108.153"
echo "  Type A     Name @     Value 185.199.109.153"
echo "  Type A     Name @     Value 185.199.110.153"
echo "  Type A     Name @     Value 185.199.111.153"
echo "  Type CNAME Name www   Value $USER_LOWER.github.io"
echo ""
echo "DNS can take up to a day. Once the domain loads, switch on HTTPS with:"
echo "  gh api -X PUT repos/$USER_NAME/$REPO/pages -F https_enforced=true"
