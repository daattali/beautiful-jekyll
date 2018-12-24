#!/bin/bash
$SCRIPT_BEGIN

return_code=0

# Checking that examples has proper @file tag
for file in `find * -type f \( -name \*.c -o -name \*.cpp -o -name \*.cxx -o -name \*.h -o -name \*.hpp -o -name \*.hxx \)`
do
  expected_name=$file
  if ! $(grep -aqE "^\s*(\**|//[/!]|/\*[\*!])\s*?[@\\\\]example(\s+${expected_name})?\s*$" $file)
  then
    echo -E "Error in file $file:"
    echo -E "  expecting \" * @example ${expected_name}\""
    echo -E "  but found \"$(grep -m 1 -aP '[@\\](example|file)' $file)\""
    echo

    return_code=1
  fi
done

$SCRIPT_END

exit $return_code
