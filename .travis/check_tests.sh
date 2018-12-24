#!/bin/bash
$SCRIPT_BEGIN

echo "Running the unit tests."
### DGtal Tests
echo "PWD = $PWD"
ls
ctest -j $BJOBS --output-on-failure
$SCRIPT_END


#if [ -f io/writers/testMagickWriter ]; then
#    io/writers/testMagickWriter -s
#fi
#
#if [ -f io/readers/testMagickReader ]; then
#    io/readers/testMagickReader
#fi
