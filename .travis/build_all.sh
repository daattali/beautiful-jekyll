#!/bin/bash
$SCRIPT_BEGIN


export CONFIG="Debug,Magick,GMP,ITK,FFTW3,Debug,Cairo,QGLviewer,HDF5,EIGEN"

# OS dependent deps
source "$SRC_DIR/.travis/install_eigen.sh"
echo $EIGEN_ROOT

export BTYPE="$BTYPE -DBUILD_EXAMPLES=false -DBUILD_TESTING=true"
export BTYPE="$BTYPE -DCMAKE_BUILD_TYPE=Debug -DWITH_MAGICK=true -DWITH_GMP=true\
                     -DWITH_FFTW3=true -DWARNING_AS_ERROR=ON -DCMAKE_BUILD_TYPE=Debug \
                     -DWITH_HDF5=true -DWITH_CAIRO=true -DWITH_QGLVIEWER=true -DWITH_EIGEN=true\
                     -DWARNING_AS_ERROR=OFF -DEIGEN3_INCLUDE_DIR='$EIGEN_ROOT/include/eigen3'"

if [ $TRAVIS_OS_NAME == osx ]; then source "$SRC_DIR/.travis/install_deps_macos.sh"; fi

#############################
#     cmake
#############################
#Build directory
cd build
# Common build options
export BTYPE="$BTYPE -DCMAKE_CXX_COMPILER=$CXXCOMPILER -DCMAKE_C_COMPILER=$CCOMPILER"

# Cmake
echo "Using C++ = $CXXCOMPILER"
echo "CMake options = $BTYPE"
echo "Pwd = $PWD"
echo "SRC_dir=$SRC_DIR"
cmake "$SRC_DIR" $BTYPE -G Ninja

#############################
#     make all
#############################
echo "Preparing the build..."

#Sequential DEC examples, this would also build library
#make examplePropagation
ninja testDiscreteExteriorCalculusExtended
#make exampleDiscreteExteriorCalculusChladni
ninja
$SCRIPT_END
