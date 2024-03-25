#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 file1 file2 [file3 ...]"
    exit 1
fi

studentNumber=$(cut -d ',' -f 1 "$@" | tail -n +2 | sort -u)

header="number"

for file in "$@"; do
    header+=",$(head -n 1 "$file" | cut -d ',' -f 2)"
done

echo "$header"

for number in $studentNumber; do
    line="$number"
    for file in "$@"; do
        mark=$(grep "^$number," "$file" | cut -d ',' -f 2)
        if [ -z "$mark" ]; then
            line+=",-"
        else
            line+=",$mark"
        fi
    done
    
    if [ "$line" != "$header" ]; then
        echo "$line"
    fi
done
