#!/bin/bash
$SCRIPT_BEGIN

#
##Download and install 1.8.1
#
mkdir ~/doxygen && cd ~/doxygen
wget http://doxygen.nl/files/doxygen-1.8.14.src.tar.gz && tar xzf doxygen-1.8.14.src.tar.gz
cd doxygen-1.8.14 ; mkdir build ; cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$SRC_DIR/doxygen/
ninja install

$SCRIPT_END
