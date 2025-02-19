run_test() {
  local test_name="$1"
  local rod_length="$2"
  local input_data="$3"
  local expected_value="$4"
  local expected_remainder="$5"

  echo "----------------------------------------------------------"
  echo "$test_name"
  echo "Rod length: $rod_length"
  echo "Pieces:"
  echo "$input_data"
  echo

  OUTPUT=$(echo "$input_data" | ./rod_cut "$rod_length" 2>&1)

  echo "=== Program Output ==="
  echo "$OUTPUT"
  echo "======================"

  # Check if the 'Value: <expected_value>' and the 'Remainder: <expected_remainder> ' match 
  VALUE_OK=$(echo "$OUTPUT" | grep -c "Value: $expected_value")
  REMAINDER_OK=$(echo "$OUTPUT" | grep -c "Remainder: $expected_remainder")

  if [ "$VALUE_OK" -gt 0 ] && [ "$REMAINDER_OK" -gt 0 ]; then
    echo "Result: PASS"
  else
    echo "Result: FAIL"
  fi
  echo
}

# Test Case 1
# -----------------------------------------------------
run_test \
  "Test 1: short rod" \
  "4" \
  "1, 1
2, 5
4, 10" \
  "10" \
  "0"

# Test Case 2
# -----------------------------------------------------
run_test \
  "Test 2: Two pieces total 18" \
  "8" \
  "1, 1
2, 3
3, 7
4, 9" \
  "18" \
  "0"

# Test Case 3
# -----------------------------------------------------
run_test \
  "Test 3: Remainder situation" \
  "10" \
  "3, 5
6, 12" \
  "17" \
  "1"

# Test Case 4
# -----------------------------------------------------
run_test \
  "Test 4: Single piece" \
  "50" \
  "1, 2" \
  "100" \
  "0"

# Test Case 5
# -----------------------------------------------------
run_test \
  "Test 5: Medium rod" \
  "5" \
  "2, 10
5, 25
10, 100" \
  "25" \
  "0"
echo "All tests completed."