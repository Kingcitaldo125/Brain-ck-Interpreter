#!/bin/bash

# Find and format all .cpp and .hpp files recursively
find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -print0 | while IFS= read -r -d '' file; do
    clang-format -i "$file"
done
