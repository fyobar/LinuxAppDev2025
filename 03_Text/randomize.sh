#!/bin/sh


# store input and process delay parameter

input_variable=$(cat)

if [[ "$1" =~ ^-?[0-9]+([.][0-9]+)?$ ]]; then
    delay="$1"
else
    delay=0
fi

delay_is_non_zero=$(echo "$delay != 0" | bc)


# process lines

IFS=$'\n'
max_length=0
line_number=0
lines=()

for line in $input_variable; do
    length=${#line}
    lines+=("$line")
    line_number=$((line_number+1))
    if (( length > max_length )); then
        max_length=$length
    fi
done

unset IFS


#  build array of indeces

indices=()

for ((i = 0; i < max_length; i++)); do
    for ((j = 0; j < line_number; j++)); do
        indices+=("$i $j")
    done
done


# Fisher-Yates shuffle

for ((i = (line_number * max_length) - 1; i > 0; i--)); do
    j=$((RANDOM % (i + 1)))
    tmp=${indices[i]}
    indices[i]=${indices[j]}
    indices[j]=$tmp
done


# perform output

tput clear

for index in "${indices[@]}"; do
    read col row <<< "$index"
    line=${lines[$row]}
    char=${line:$col:1}

    if [[ ! "$char" == [[:space:]] ]]; then
        tput cup $row $col
        if [[ "$delay_is_non_zero" -eq 1 ]]; then
            sleep $delay
        fi
        /bin/echo "$char"
    fi
done

tput cup $line_number 0
