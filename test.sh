#!/bin/bash

prog=$1

for f in data/input.*; do
  n="${f##*.}"
  output="$(./$prog $f)"
  expected="$(cat data/output.$n)"
  if [[ "$output" != "$expected" ]]; then
    echo "Test $n failed (output differs):"
    echo ----------------- Output ---------------
    echo $ouptut | cat -v
    echo ----------------- Expected -------------
    echo $expected | cat -v
    echo ----------------------------------------
  fi
  /usr/bin/time --format "%C: %E" ./$prog $f > /dev/null
done

echo All tests passed!
