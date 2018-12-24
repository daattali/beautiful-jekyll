#!/bin/bash
$SCRIPT_BEGIN


## Get and test if DGtalTools compiles
DGTALPATH="$SRC_DIR"
echo "DGtal path = $DGTALPATH"
echo "Build = $BUILD"
echo "TRAVIS_BUILD_DIR= $TRAVIS_BUILD_DIR"
git clone --depth 1 git://github.com/DGtal-team/DGtalTools.git
cd DGtalTools
mkdir build ; cd build
cmake .. -DDGtal_DIR=$TRAVIS_BUILD_DIR/build  -G Ninja
  #inplace
ninja
$SCRIPT_END
