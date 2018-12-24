#!/bin/bash
$SCRIPT_BEGIN

return_code=0

# Checking that source code has proper @file tag
for file in $(find * -type f \( -name \*.cpp -o -name \*.h -o -name \*.ih \))
do
  expected_name=$(basename $file)
  if ! $(grep -aqE "^\s*(\**|//[/!]|/\*[\*!])\s*?[@\\\\]file(\s+${expected_name})?\s*$" $file)
  then
    echo -E "Error in file $file:"
    echo -E "  expecting \" * @file ${expected_name}\""
    echo -E "  or simply \" * @file\""
    echo -E "  but found \"$(grep -m 1 -aP '[@\\]file' $file)\""
    echo

    return_code=1
  fi
done

$SCRIPT_END

exit $return_code
