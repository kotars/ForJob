FUNC_SUCCESS=0
FUNC_FAIL=0
COUNTER=0
DIFF=""

declare -a e=(
"-e"
)

declare -a flags=(
"-i"
"-v"
"-c"
"-l"
"-n"
)

declare -a files=(
"s21_greptest1.txt s21_greptest2.txt"
)

declare -a commline=(
"OPT FILE"
)



function testing()
{
    str=$(echo $@ | sed "s/OPT/$options/")
    str=$(echo $str | sed "s/FILE/$file/g")
    ./s21_grep $str > s21_grep_testing.log
    grep $str > system_grep_testing.log
    DIFF="$(diff -s s21_grep_testing.log system_grep_testing.log)"
    (( COUNTER++ ))
    if [ "$DIFF" == "Files s21_grep_testing.log and system_grep_testing.log are identical" ]
    then
        (( FUNC_SUCCESS++ ))
        echo "grep $str FUNCTIONALITY SUCCESS $COUNTER"
    else
        (( FUNC_FAIL++ ))
        echo "grep $str FUNCTIONALITY FAIL $COUNTER"
    fi
    rm s21_grep_testing.log system_grep_testing.log
}

for e in "${e[@]}"
do

for file in "${files[@]}"
do
    options="$e $e str"
    testing $commline
done

for opt1 in "${flags[@]}"
do
    for file in "${files[@]}"
        do
            options="$e $e str $opt1"
            testing $commline
    done
done

for opt1 in "${flags[@]}"
do
    for opt2 in "${flags[@]}"
    do
        if [ $opt1 != $opt2 ]
        then
            for file in "${files[@]}"
            do
                options="$e $e str $opt1 $opt2"
                testing $commline
            done
        fi
    done
done

for opt1 in "${flags[@]}"
do
    for opt2 in "${flags[@]}"
    do
        for opt3 in "${flags[@]}"
        do
            if [ $opt1 != $opt2 ] && [ $opt1 != $opt3 ] && [ $opt2 != $opt3 ]
            then
                for file in "${files[@]}"
                do
                    options="$e $e str $opt1 $opt2 $opt3"
                    testing $commline
                done
            fi
        done
    done
done

for opt1 in "${flags[@]}"
do
    for opt2 in "${flags[@]}"
    do
        for opt3 in "${flags[@]}"
        do
            for opt4 in "${flags[@]}"
            do
            
                if [ $opt1 != $opt2 ] && [ $opt1 != $opt3 ] && [ $opt1 != $opt4 ] && [ $opt2 != $opt3 ] && [ $opt2 != $opt4 ] && [ $opt3 != $opt4 ]
                then
                    for file in "${files[@]}"
                    do
                        options="$e $e str $opt1 $opt2 $opt3 $opt4"
                        testing $commline
                    done
                fi
            done
        done
    done
done

for file in "${files[@]}"
do
    options="$e $e str -i -l -v -c -n"
    testing $commline
done
done

echo "FAIL: $FUNC_FAIL"
echo "SUCCESS: $FUNC_SUCCESS"
echo "ALL: $COUNTER"
