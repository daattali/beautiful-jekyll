#!/bin/bash
$SCRIPT_BEGIN

#
# Local install of Eigen on linux system
#
export EIGEN_ROOT="/usr/local/"

if [ "$TRAVIS_OS_NAME" == linux ];
then
    cd "$SRC_DIR/deps"
    wget http://bitbucket.org/eigen/eigen/get/3.2.10.tar.bz2

    bunzip2 3.2.10.tar.bz2
    tar xf 3.2.10.tar 

    cd eigen-eigen-b9cd8366d4e8
    mkdir build ; cd build

    cmake .. -DCMAKE_INSTALL_PREFIX="${SRC_DIR}/deps/local"
    make -j 2 && make install && cd "${SRC_DIR}" && export EIGEN_ROOT="$SRC_DIR/deps/local"

fi

$SCRIPT_END
