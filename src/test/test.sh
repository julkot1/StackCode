#!/bin/bash

set -e

echo "Starting tests..."
ROOT="$(dirname "$0")"
echo "Test root: $ROOT"
COMPILER="${ROOT}/../../stcc"

if [ ! -x "$COMPILER" ]; then
    echo "Compiler not found or not executable: $COMPILER"
    exit 1
fi

found=0
passed=0
failed=0
total=0

test_files=($(find "$ROOT" -name "*.rpn"))
for rpn_file in "${test_files[@]}"; do
    found=1
    total=$((total+1))
    test_dir="$(dirname "$rpn_file")"
    test_name="$(basename "$rpn_file" .rpn)"
    expected="${test_dir}/out"
    out="${test_dir}/${test_name}.out"
    exe="${test_dir}/${test_name}"

    echo "Running test: $test_name in $test_dir"

    "$COMPILER" compile "$rpn_file" -o "$exe"
    "$exe" > "$out"

    if diff -u "$expected" "$out"; then
        echo "Test $test_name: PASS"
        passed=$((passed+1))
        rm -f "$exe" "$out" "${test_dir}/${test_name}.ll" "${test_dir}/${test_name}.s"
    else
        echo "Test $test_name: FAIL"
        failed=$((failed+1))
    fi

done

if [ "$found" -eq 0 ]; then
    echo "No .rpn test files found."
    exit 0
fi

echo "=============================="
echo "Test summary:"
echo "Total: $total"
echo "Passed: $passed"
echo "Failed: $failed"
echo "=============================="

if [ "$failed" -gt 0 ]; then
    exit 1
fi
