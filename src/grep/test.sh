#!/bin/bash

SUCCESS=0
FAIL=0
DIFF_RESULT=""
TEST_FILE="$1"
TEST_FILE2="$2"
PATTERNS_FILE="patterns.txt"
ALL_FLAGS="i v c l n h s"
TMP1="P"
TMP2="!"
TMP3="ff"
TMP4="644"
TMP5="nn"
TMP6="h"
TMP7="\"[0-9]\""
TMP8="\"[a-z]\""
TMP9="\"[A-Z0-9]\""
TEMPLATES_ARRAY=($TMP1 $TMP2 $TMP3 $TMP4 $TMP5 $TMP6 $TMP7 $TMP8 $TMP9)

size=${#TEMPLATES_ARRAY[@]}

if [ ! -f "$1" ]; then
    echo "The file \"$1\" does not exist!"
    exit 1
fi

for var in $ALL_FLAGS
do
  for tmp in "${TEMPLATES_ARRAY[@]}"
  do 
    TEST1="-$var -f $PATTERNS_FILE -e $tmp $TEST_FILE"
    ./s21_grep $TEST1 > s21_grep.txt
    grep $TEST1 > grep.txt
    DIFF_RESULT="$(diff s21_grep.txt grep.txt)"
    echo $DIFF_RESULT
    if [ -z "$DIFF_RESULT" ]
      then
        (( SUCCESS++ ))
        echo "$TEST1 SUCCESS"
      else
        (( FAIL++ ))
        echo "$TEST1 FAIL"
    fi
    rm -f s21_grep.txt grep.txt
  done
done


for var in $ALL_FLAGS
do
  for var2 in $ALL_FLAGS
  do
    if [ $var != $var2 ]
    then
      N1=$((RANDOM % $size))
      N2=$((RANDOM % $size))
      RANDOM_EL1=${TEMPLATES_ARRAY[$N1]}
      RANDOM_EL2=${TEMPLATES_ARRAY[$N2]}
      TEST1="-$var$var2 -f $PATTERNS_FILE -e $RANDOM_EL1 -e $RANDOM_EL2 $TEST_FILE $TEST_FILE2"
      ./s21_grep $TEST1 > s21_grep.txt
      grep $TEST1 > grep.txt
      DIFF_RESULT="$(diff s21_grep.txt grep.txt)"
      echo $DIFF_RESULTs
      if [ -z "$DIFF_RESULT" ]
        then
          (( SUCCESS++ ))
          echo "$TEST1 SUCCESS"
        else
          (( FAIL++ ))
          echo "$TEST1 FAIL"
      fi
      rm -f s21_grep.txt grep.txt
    fi
  done
done



for var in $ALL_FLAGS
do
  for var2 in $ALL_FLAGS
  do
    for var3 in $ALL_FLAGS
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] 
        then
          N1=$((RANDOM % $size))
          N2=$((RANDOM % $size))
          N3=$((RANDOM % $size))
          RANDOM_EL1=${TEMPLATES_ARRAY[$N1]}
          RANDOM_EL2=${TEMPLATES_ARRAY[$N2]}
          RANDOM_EL3=${TEMPLATES_ARRAY[$N3]}
          TEST1="-$var -$var2 -$var3 -f $PATTERNS_FILE -e $RANDOM_EL1 -e $RANDOM_EL2 -e $RANDOM_EL3 $TEST_FILE $TEST_FILE2"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RESULT="$(diff s21_grep.txt grep.txt)"
          echo $DIFF_RESULTs
          if [ -z "$DIFF_RESULT" ]
            then
              (( SUCCESS++ ))
              echo "$TEST1 SUCCESS"
            else
              (( FAIL++ ))
              echo "$TEST1 FAIL"
          fi
          rm -f s21_grep.txt grep.txt
        fi
      done
  done
done


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
              N1=$((RANDOM % $size))
              N2=$((RANDOM % $size))
              N3=$((RANDOM % $size))
              N4=$((RANDOM % $size))
              RANDOM_EL1=${TEMPLATES_ARRAY[$N1]}
              RANDOM_EL2=${TEMPLATES_ARRAY[$N2]}
              RANDOM_EL3=${TEMPLATES_ARRAY[$N3]}
              RANDOM_EL4=${TEMPLATES_ARRAY[$N4]}
              TEST1="-$var -$var2 -$var3 -$var4 -f $PATTERNS_FILE -e $RANDOM_EL1 -e $RANDOM_EL2 -e $RANDOM_EL3 -e $RANDOM_EL4 $TEST_FILE $TEST_FILE2"
              ./s21_grep $TEST1 > s21_grep.txt
              grep $TEST1 > grep.txt
              DIFF_RESULT="$(diff s21_grep.txt grep.txt)"
              echo $DIFF_RESULT
              if [ -z "$DIFF_RESULT" ]
                then
                  (( SUCCESS++ ))
                  echo "$TEST1 SUCCESS"
                else
                  (( FAIL++ ))
                  echo "$TEST1 FAIL"

              fi
              rm -f s21_grep.txt grep.txt
            fi
          done
      done
  done
done

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"