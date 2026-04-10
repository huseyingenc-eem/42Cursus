#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Programs
PUSH_SWAP="./push_swap"
CHECKER="./checker_linux"

# Test result function
print_result() {
    local test_name=$1
    local result=$2
    local details=$3
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ "$result" == "OK" ]; then
        PASSED_TESTS=$((PASSED_TESTS + 1))
        echo -e "${GREEN}✓${NC} $test_name: ${GREEN}PASSED${NC} $details"
    else
        FAILED_TESTS=$((FAILED_TESTS + 1))
        echo -e "${RED}✗${NC} $test_name: ${RED}FAILED${NC} $details"
    fi
}

# Header function
print_header() {
    echo -e "\n${CYAN}════════════════════════════════════════════════════════${NC}"
    echo -e "${CYAN}$1${NC}"
    echo -e "${CYAN}════════════════════════════════════════════════════════${NC}\n"
}

# Check if programs exist
check_programs() {
    if [ ! -f "$PUSH_SWAP" ]; then
        echo -e "${RED}Error: push_swap not found!${NC}"
        exit 1
    fi
    
    if [ ! -f "$CHECKER" ]; then
        echo -e "${YELLOW}Warning: checker_linux not found! Checker tests will be skipped.${NC}"
        CHECKER=""
    fi
}

# Test with checker
test_with_checker() {
    local input=$1
    local test_name=$2
    
    if [ -z "$CHECKER" ]; then
        return
    fi
    
    local result=$($PUSH_SWAP "$input" 2>/dev/null | $CHECKER "$input" 2>&1)
    
    if [ "$result" == "OK" ]; then
        print_result "$test_name" "OK"
    else
        print_result "$test_name" "FAIL" "(Result: $result)"
    fi
}

# Test move count
test_move_count() {
    local input=$1
    local test_name=$2
    
    local count=$($PUSH_SWAP "$input" 2>/dev/null | wc -l)
    echo -e "${BLUE}ℹ${NC} $test_name: ${MAGENTA}$count moves${NC}"
}

# Test error handling with valgrind
test_error_valgrind() {
    local input=$1
    local test_name=$2
    
    # Valgrind çıktısını geçici dosyaya kaydet
    local temp_file=$(mktemp)
    valgrind --leak-check=full --error-exitcode=42 --log-file="$temp_file" $PUSH_SWAP "$input" > /dev/null 2>&1
    local exit_code=$?
    
    local valgrind_output=$(cat "$temp_file")
    rm -f "$temp_file"
    
    # Leak kontrolü
    if echo "$valgrind_output" | grep -q "ERROR SUMMARY: 0 errors" && \
       echo "$valgrind_output" | grep -q "All heap blocks were freed"; then
        print_result "$test_name" "OK" "(No leaks)"
    elif echo "$valgrind_output" | grep -q "no leaks are possible"; then
        print_result "$test_name" "OK" "(No leaks possible)"
    else
        # Detaylı hata mesajı
        local error_detail=""
        if echo "$valgrind_output" | grep -q "definitely lost"; then
            error_detail="Memory leak detected"
        elif echo "$valgrind_output" | grep -q "Invalid"; then
            error_detail="Invalid memory access"
        else
            error_detail="Valgrind error"
        fi
        print_result "$test_name" "FAIL" "($error_detail)"
    fi
}

# Test with valgrind and checker
test_valgrind_checker() {
    local input=$1
    local test_name=$2
    
    if [ -z "$CHECKER" ]; then
        return
    fi
    
    # Valgrind ile leak kontrolü
    local temp_file=$(mktemp)
    valgrind --leak-check=full --error-exitcode=42 --log-file="$temp_file" $PUSH_SWAP "$input" 2>&1 > /dev/null
    local valgrind_exit=$?
    local valgrind_output=$(cat "$temp_file")
    rm -f "$temp_file"
    
    # Checker ile doğruluk kontrolü
    local checker_result=$($PUSH_SWAP "$input" 2>/dev/null | $CHECKER "$input" 2>&1)
    
    # Leak var mı?
    local has_leaks=0
    if ! echo "$valgrind_output" | grep -q "ERROR SUMMARY: 0 errors"; then
        has_leaks=1
    fi
    if ! echo "$valgrind_output" | grep -q "All heap blocks were freed\|no leaks are possible"; then
        has_leaks=1
    fi
    
    if [ "$checker_result" == "OK" ] && [ $has_leaks -eq 0 ]; then
        print_result "$test_name" "OK" "(No leaks, sorted correctly)"
    elif [ "$checker_result" == "OK" ]; then
        print_result "$test_name" "FAIL" "(Sorted but has leaks)"
    elif [ $has_leaks -eq 0 ]; then
        print_result "$test_name" "FAIL" "(No leaks but wrong result: $checker_result)"
    else
        print_result "$test_name" "FAIL" "(Has leaks and wrong result)"
    fi
}

# Main testing
echo -e "${MAGENTA}"
echo "╔════════════════════════════════════════════════════════╗"
echo "║         PUSH_SWAP COMPREHENSIVE TESTER                 ║"
echo "╚════════════════════════════════════════════════════════╝"
echo -e "${NC}"

check_programs

# ============================================================
# TEST 1: All 5-element permutations with checker
# ============================================================
print_header "TEST 1: All 5-Element Permutations (94 tests)"

test_with_checker "1 0 3 2 4" "5-elem perm #1"
test_with_checker "1 0 3 4 2" "5-elem perm #2"
test_with_checker "1 0 4 2 3" "5-elem perm #3"
test_with_checker "1 0 4 3 2" "5-elem perm #4"
test_with_checker "1 2 0 3 4" "5-elem perm #5"
test_with_checker "1 2 0 4 3" "5-elem perm #6"
test_with_checker "1 2 3 0 4" "5-elem perm #7"
test_with_checker "1 2 3 4 0" "5-elem perm #8"
test_with_checker "1 2 4 0 3" "5-elem perm #9"
test_with_checker "1 2 4 3 0" "5-elem perm #10"
test_with_checker "1 3 0 2 4" "5-elem perm #11"
test_with_checker "1 3 0 4 2" "5-elem perm #12"
test_with_checker "1 3 2 0 4" "5-elem perm #13"
test_with_checker "1 3 2 4 0" "5-elem perm #14"
test_with_checker "1 3 4 0 2" "5-elem perm #15"
test_with_checker "1 3 4 2 0" "5-elem perm #16"
test_with_checker "1 4 0 2 3" "5-elem perm #17"
test_with_checker "1 4 0 3 2" "5-elem perm #18"
test_with_checker "1 4 2 0 3" "5-elem perm #19"
test_with_checker "1 4 2 3 0" "5-elem perm #20"
test_with_checker "1 4 3 0 2" "5-elem perm #21"
test_with_checker "1 4 3 2 0" "5-elem perm #22"
test_with_checker "2 0 1 3 4" "5-elem perm #23"
test_with_checker "2 0 1 4 3" "5-elem perm #24"
test_with_checker "2 0 3 1 4" "5-elem perm #25"
test_with_checker "2 0 3 4 1" "5-elem perm #26"
test_with_checker "2 0 4 1 3" "5-elem perm #27"
test_with_checker "2 0 4 3 1" "5-elem perm #28"
test_with_checker "2 1 0 3 4" "5-elem perm #29"
test_with_checker "2 1 0 4 3" "5-elem perm #30"
test_with_checker "2 1 3 0 4" "5-elem perm #31"
test_with_checker "2 1 3 4 0" "5-elem perm #32"
test_with_checker "2 1 4 0 3" "5-elem perm #33"
test_with_checker "2 1 4 3 0" "5-elem perm #34"
test_with_checker "2 3 0 1 4" "5-elem perm #35"
test_with_checker "2 3 0 4 1" "5-elem perm #36"
test_with_checker "2 3 1 0 4" "5-elem perm #37"
test_with_checker "2 3 1 4 0" "5-elem perm #38"
test_with_checker "2 3 4 0 1" "5-elem perm #39"
test_with_checker "2 3 4 1 0" "5-elem perm #40"
test_with_checker "2 4 0 1 3" "5-elem perm #41"
test_with_checker "2 4 0 3 1" "5-elem perm #42"
test_with_checker "2 4 1 0 3" "5-elem perm #43"
test_with_checker "2 4 1 3 0" "5-elem perm #44"
test_with_checker "2 4 3 0 1" "5-elem perm #45"
test_with_checker "2 4 3 1 0" "5-elem perm #46"
test_with_checker "3 0 1 2 4" "5-elem perm #47"
test_with_checker "3 0 1 4 2" "5-elem perm #48"
test_with_checker "3 0 2 1 4" "5-elem perm #49"
test_with_checker "3 0 2 4 1" "5-elem perm #50"
test_with_checker "3 0 4 1 2" "5-elem perm #51"
test_with_checker "3 0 4 2 1" "5-elem perm #52"
test_with_checker "3 1 0 2 4" "5-elem perm #53"
test_with_checker "3 1 0 4 2" "5-elem perm #54"
test_with_checker "3 1 2 0 4" "5-elem perm #55"
test_with_checker "3 1 2 4 0" "5-elem perm #56"
test_with_checker "3 1 4 0 2" "5-elem perm #57"
test_with_checker "3 1 4 2 0" "5-elem perm #58"
test_with_checker "3 2 0 1 4" "5-elem perm #59"
test_with_checker "3 2 0 4 1" "5-elem perm #60"
test_with_checker "3 2 1 0 4" "5-elem perm #61"
test_with_checker "3 2 1 4 0" "5-elem perm #62"
test_with_checker "3 2 4 0 1" "5-elem perm #63"
test_with_checker "3 2 4 1 0" "5-elem perm #64"
test_with_checker "3 4 0 1 2" "5-elem perm #65"
test_with_checker "3 4 0 2 1" "5-elem perm #66"
test_with_checker "3 4 1 0 2" "5-elem perm #67"
test_with_checker "3 4 1 2 0" "5-elem perm #68"
test_with_checker "3 4 2 0 1" "5-elem perm #69"
test_with_checker "3 4 2 1 0" "5-elem perm #70"
test_with_checker "4 0 1 2 3" "5-elem perm #71"
test_with_checker "4 0 1 3 2" "5-elem perm #72"
test_with_checker "4 0 2 1 3" "5-elem perm #73"
test_with_checker "4 0 2 3 1" "5-elem perm #74"
test_with_checker "4 0 3 1 2" "5-elem perm #75"
test_with_checker "4 0 3 2 1" "5-elem perm #76"
test_with_checker "4 1 0 2 3" "5-elem perm #77"
test_with_checker "4 1 0 3 2" "5-elem perm #78"
test_with_checker "4 1 2 0 3" "5-elem perm #79"
test_with_checker "4 1 2 3 0" "5-elem perm #80"
test_with_checker "4 1 3 0 2" "5-elem perm #81"
test_with_checker "4 1 3 2 0" "5-elem perm #82"
test_with_checker "4 2 0 1 3" "5-elem perm #83"
test_with_checker "4 2 0 3 1" "5-elem perm #84"
test_with_checker "4 2 1 0 3" "5-elem perm #85"
test_with_checker "4 2 1 3 0" "5-elem perm #86"
test_with_checker "4 2 3 0 1" "5-elem perm #87"
test_with_checker "4 2 3 1 0" "5-elem perm #88"
test_with_checker "4 3 0 1 2" "5-elem perm #89"
test_with_checker "4 3 0 2 1" "5-elem perm #90"
test_with_checker "4 3 1 0 2" "5-elem perm #91"
test_with_checker "4 3 1 2 0" "5-elem perm #92"
test_with_checker "4 3 2 0 1" "5-elem perm #93"
test_with_checker "4 3 2 1 0" "5-elem perm #94"

# ============================================================
# TEST 2: Error Handling with Valgrind
# ============================================================
print_header "TEST 2: Error Handling - Invalid Inputs (No Leaks Expected)"

test_error_valgrind " " "Empty space"
test_error_valgrind "" "Empty string"
test_error_valgrind " a" "Letter input"
test_error_valgrind "1 2 3 " "Trailing space"
test_error_valgrind "99999999999999999999999999999999999" "Overflow positive"
test_error_valgrind "-99999999999999999999999999999999999" "Overflow negative"
test_error_valgrind "-1 -2 ++3 " "Double plus sign"
test_error_valgrind " ++ " "Only plus signs"

# ============================================================
# TEST 3: Move Count Tests
# ============================================================
print_header "TEST 3: Move Count Tests (Efficiency Check)"

test_move_count "4 0 3 2 1" "Move count #1"
test_move_count "4 1 0 2 3" "Move count #2"
test_move_count "4 1 0 3 2" "Move count #3"
test_move_count "4 1 2 0 3" "Move count #4"
test_move_count "4 1 2 3 0" "Move count #5"
test_move_count "4 1 3 0 2" "Move count #6"
test_move_count "4 1 3 2 0" "Move count #7"
test_move_count "4 2 0 1 3" "Move count #8"
test_move_count "4 2 0 3 1" "Move count #9"
test_move_count "4 2 1 0 3" "Move count #10"
test_move_count "4 2 1 3 0" "Move count #11"
test_move_count "4 2 3 0 1" "Move count #12"
test_move_count "4 2 3 1 0" "Move count #13"
test_move_count "4 3 0 1 2" "Move count #14"
test_move_count "4 3 0 2 1" "Move count #15"
test_move_count "4 3 1 0 2" "Move count #16"
test_move_count "4 3 1 2 0" "Move count #17"
test_move_count "4 3 2 0 1" "Move count #18"
test_move_count "4 3 2 1 0" "Move count #19"

# ============================================================
# TEST 4: Comprehensive Valgrind Tests
# ============================================================
print_header "TEST 4: Memory Leak Tests - All Invalid Inputs"

test_error_valgrind "" "Empty #1"
test_error_valgrind " " "Space #1"
test_error_valgrind "   " "Multiple spaces"
test_error_valgrind "a" "Single letter"
test_error_valgrind "1 a 2" "Letter in middle"
test_error_valgrind "1 2b 3" "Letter attached"
test_error_valgrind "1 + 2" "Plus sign alone"
test_error_valgrind "++1" "Double plus"
test_error_valgrind "--1" "Double minus"
test_error_valgrind "+-1" "Plus then minus"
test_error_valgrind "-+1" "Minus then plus"
test_error_valgrind "1 1" "Duplicate #1"
test_error_valgrind "0 1 2 3 2" "Duplicate #2"
test_error_valgrind "4 4 4" "Triple duplicate"
test_error_valgrind "10 20 30 10" "Duplicate far"
test_error_valgrind "2147483648" "INT_MAX + 1"
test_error_valgrind "-2147483649" "INT_MIN - 1"
test_error_valgrind "99999999999999999999" "Huge positive"
test_error_valgrind "-99999999999999999999" "Huge negative"
test_error_valgrind "1 2 --3" "Double minus in middle"
test_error_valgrind "+ 1 2" "Plus with space"
test_error_valgrind "1 2 +3-" "Invalid format"
test_error_valgrind "1 2 3 4  " "Trailing spaces"
test_error_valgrind "   1   2 3" "Leading spaces"
test_error_valgrind "  1   -   2" "Minus with spaces"
test_error_valgrind "--" "Only dashes"
test_error_valgrind "++" "Only pluses"

# ============================================================
# TEST 5: Valid Inputs with Valgrind + Checker
# ============================================================
print_header "TEST 5: Valid Inputs - Memory & Correctness"

test_valgrind_checker "3 1 2" "Simple 3 elem"
test_valgrind_checker "10 5 8 2 1" "Random 5 elem"
test_valgrind_checker "4 3 2 1" "Reverse 4 elem"
test_valgrind_checker "6 5 4 3 2 1 0" "Reverse 7 elem"
test_valgrind_checker "2 1" "Two elements"
test_valgrind_checker "1" "Single element"
test_valgrind_checker "1 2" "Already sorted 2"
test_valgrind_checker "0 10 5 15 20" "Mixed order #1"
test_valgrind_checker "9 8 7" "Reverse 3"
test_valgrind_checker "1 5 2 4 3" "Mixed order #2"
test_valgrind_checker "10 2 30 4 50" "Large gaps"
test_valgrind_checker "1 3 2" "Simple swap needed"
test_valgrind_checker "5 10 0 20 15" "Zero in middle"
test_valgrind_checker "8 1 3 10 5 2" "Six elements"
test_valgrind_checker "100 1 200 2 300" "Large numbers"
test_valgrind_checker "4 8 15 16" "Already sorted 4"
test_valgrind_checker "9 18 27 36 45 0" "Multiples with zero"
test_valgrind_checker "5 50 500 1 10" "Various scales"
test_valgrind_checker "7 14 21" "Multiples of 7"
test_valgrind_checker "1 2 4 8 16 32" "Powers of 2"
test_valgrind_checker "32 16 8 4 2 1" "Reverse powers"
test_valgrind_checker "10 1 9 2 8 3" "Alternating"
test_valgrind_checker "3 7 11 13 17" "Prime-like"
test_valgrind_checker "19 17 13 11 7 5" "Reverse primes"
test_valgrind_checker "5 8 13 21" "Fibonacci-like"
test_valgrind_checker "12 24 36 48 60 72" "Multiples of 12"
test_valgrind_checker "10 20 30 40 50 60 70 80" "Sorted 8 elem"
test_valgrind_checker "80 70 60 50 40 30 20 10" "Reverse 8 elem"
test_valgrind_checker "1 10 100 1000 0 -1" "With negatives"
test_valgrind_checker "6 12 18 24" "Even multiples"

# ============================================================
# TEST 6: Large Set Tests
# ============================================================
print_header "TEST 6: Large Set Tests (100 elements)"

if [ -n "$CHECKER" ]; then
    echo -e "${BLUE}Testing 100 elements reverse order...${NC}"
    result=$($PUSH_SWAP "100 99 98 97 96 95 94 93 92 91 90 89 88 87 86 85 84 83 82 81 80 79 78 77 76 75 74 73 72 71 70 69 68 67 66 65 64 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1" 2>/dev/null | $CHECKER "100 99 98 97 96 95 94 93 92 91 90 89 88 87 86 85 84 83 82 81 80 79 78 77 76 75 74 73 72 71 70 69 68 67 66 65 64 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1" 2>&1)
    moves=$($PUSH_SWAP "100 99 98 97 96 95 94 93 92 91 90 89 88 87 86 85 84 83 82 81 80 79 78 77 76 75 74 73 72 71 70 69 68 67 66 65 64 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1" 2>/dev/null | wc -l)
    
    if [ "$result" == "OK" ]; then
        if [ $moves -le 700 ]; then
            print_result "100 elements reverse" "OK" "(Moves: $moves - Excellent!)"
        elif [ $moves -le 900 ]; then
            print_result "100 elements reverse" "OK" "(Moves: $moves - Good)"
        elif [ $moves -le 1100 ]; then
            print_result "100 elements reverse" "OK" "(Moves: $moves - Acceptable)"
        else
            print_result "100 elements reverse" "OK" "(Moves: $moves - Needs optimization)"
        fi
    else
        print_result "100 elements reverse" "FAIL" "(Result: $result)"
    fi
fi

# ============================================================
# TEST 7: Invalid Format Tests
# ============================================================
print_header "TEST 7: Invalid Format Tests - Characters & Symbols"

test_error_valgrind "a b c d" "All letters"
test_error_valgrind "1 2 3 a 5" "Letter at end"
test_error_valgrind "1 2 3a 4" "Letter attached #2"
test_error_valgrind "42 ok 100" "Word in middle"
test_error_valgrind "1 2 +" "Plus at end"
test_error_valgrind "1 --2 3" "Double minus #2"
test_error_valgrind "1 ++2 3" "Double plus #2"
test_error_valgrind "1 2- 3" "Minus after number"
test_error_valgrind "1 -+2 3" "Mixed signs"
test_error_valgrind "1 2 2147483648" "Overflow in list"
test_error_valgrind "1 2 -2147483649" "Underflow in list"
test_error_valgrind "10 20 99999999999999999999 40" "Huge in middle"

# ============================================================
# SUMMARY
# ============================================================
echo -e "\n${CYAN}════════════════════════════════════════════════════════${NC}"
echo -e "${CYAN}                    TEST SUMMARY                        ${NC}"
echo -e "${CYAN}════════════════════════════════════════════════════════${NC}"
echo -e "${BLUE}Total Tests:${NC}   $TOTAL_TESTS"
echo -e "${GREEN}Passed:${NC}        $PASSED_TESTS"
echo -e "${RED}Failed:${NC}        $FAILED_TESTS"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}╔════════════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║              ALL TESTS PASSED! 🎉                      ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════════════════════╝${NC}"
else
    echo -e "\n${RED}╔════════════════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║              SOME TESTS FAILED ❌                      ║${NC}"
    echo -e "${RED}╚════════════════════════════════════════════════════════╝${NC}"
fi

if [ $TOTAL_TESTS -gt 0 ]; then
    SUCCESS_RATE=$(awk "BEGIN {printf \"%.2f\", ($PASSED_TESTS/$TOTAL_TESTS)*100}")
    echo -e "\n${MAGENTA}Success Rate: ${SUCCESS_RATE}%${NC}\n"
fi