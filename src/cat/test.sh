#!/bin/bash

SUCCESS=0
FAIL=0
DIFF_RESULT=""
TEST_FILE="$1"
ALL_FLAGS="-b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank"

if [ ! -f "$1" ]; then
    echo "The file \"$1\" does not exist!"
    exit 1
fi

for var in $ALL_FLAGS
do
  for var2 in $ALL_FLAGS
  do
      for var3 in $ALL_FLAGS
      do
          for var4 in $ALL_FLAGS
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              TEST1="$var $var2 $var3 $var4 $TEST_FILE"
              ./s21_cat $TEST1 > s21_cat.txt
              cat $TEST1 > cat.txt
              DIFF_RESULT="$(diff s21_cat.txt cat.txt)"
              if [ -z "$DIFF_RESULT" ]
                then
                  (( SUCCESS++ ))
                  echo "$TEST1 SUCCESS"
                else
                  (( FAIL++ ))
                  echo "$TEST1 FAIL"

              fi
              rm -f s21_cat.txt cat.txt
            fi
          done
      done
  done
done

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"