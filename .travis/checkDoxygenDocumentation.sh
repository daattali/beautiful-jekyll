#!/bin/bash
$SCRIPT_BEGIN

return_code=0

DOXYGENLOG=doxygen.log

## We first check that the doxygen.log is empty
if [[ -f "$DOXYGENLOG" ]]
then

    # Filtering doxygen log (e.g. to ignore some bugs)
    # See https://github.com/doxygen/doxygen/issues/6352
    rm -f /tmp/doxygen.*.log
    awk '/unexpected token TK_EOF as the argument of ref/ \
        {print $0 > "/tmp/doxygen.ignored.log"; next} \
        {print $0 > "/tmp/doxygen.kept.log"}' \
        "$DOXYGENLOG"

    if [[ -s "/tmp/doxygen.kept.log" ]]
    then
        return_code=1
        echo "Doxygen log file not empty !"
        echo "====================================="
        cat "/tmp/doxygen.kept.log"
        echo "====================================="
    else
        echo "Doxygen log OK"
        return_code=0
    fi

    if [[ -s "/tmp/doxygen.ignored.log" ]]
    then
        echo "Ignored doxygen log messages:"
        echo "====================================="
        cat "/tmp/doxygen.ignored.log"
        echo "====================================="
    fi
else
  return_code=1
  echo "Doxygen log file not found !"
fi


## We check src code consitency
cd "$SRC_DIR/src"
"$SRC_DIR/.travis/check_src_file_tag.sh"
if [[ $? == 0 ]]
then
    echo "@file tag OK"
else
    return_code=1;
fi
cd ..

## We check examples consistency
#
# TODO
#

$SCRIPT_END

exit $return_code
