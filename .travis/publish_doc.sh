#!/bin/bash
$SCRIPT_BEGIN

rsync -azv --delete --delete-after -e "ssh -oStrictHostKeyChecking=no -i '$SRC_DIR/.travis/dgtal_rsa'" "$BUILD_DIR/html/" dgtal@connect.liris.cnrs.fr:/home-projets/dgtal/public_html/doc/nightly/

##DOCSET build
cd "$BUILD_DIR/html"

set +e
make  # Build is expected to fail when launching docsetutil. However, the result is still usable in Dash.
set -e

wget --no-check-certificate http://dgtal.org/doc/docset/template.tgz
tar zxvf template.tgz ; mv template/* org.dgtal.docset
tar zcvf DGtal-devel.tgz org.dgtal.docset

rsync  -azv --delete --delete-after -e "ssh -oStrictHostKeyChecking=no -i '$SRC_DIR/.travis/dgtal_rsa'" "$BUILD_DIR/html/DGtal-devel.tgz" dgtal@connect.liris.cnrs.fr:/home-projets/dgtal/public_html/doc/docset

###TAGS for DGtalTools
scp -i "$SRC_DIR/.travis/dgtal_rsa"  "$BUILD_DIR/DGtal-tagfile" dgtal@connect.liris.cnrs.fr:/home-projets/dgtal/public_html/doc/tags/

$SCRIPT_END
