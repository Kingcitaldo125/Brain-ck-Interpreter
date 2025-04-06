#!/bin/bash

# Path to clang-format (can also be just 'clang-format' if it's in PATH)
CLANG_FORMAT=clang-format

# Find and format all .cpp and .hpp files recursively
find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -print0 | while IFS= read -r -d '' file; do
    "$CLANG_FORMAT" -i "$file"
done
