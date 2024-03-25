#!/bin/bash

# Check if correct number of arguments are provided
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 file1 file2 [file3 ...]"
    exit 1
fi

# Extract student numbers from each file and sort them
studentNumbers=$(cut -d ',' -f 1 "$@" | tail -n +2 | sort -u)

# Create the header line for the merged file
header="number"

# Loop through each input file to extract header names and initialize the merged data
for file in "$@"; do
    header+=",$(head -n 1 "$file" | cut -d ',' -f 2)"
done

echo "$header"

# Loop through each student number and merge their marks
for number in $studentNumbers; do
    line="$number"
    for file in "$@"; do
        mark=$(grep "^$number," "$file" | cut -d ',' -f 2)
        if [ -z "$mark" ]; then
            line+=",-"
        else
            line+=",$mark"
        fi
    done
    echo "$line"
done
