#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

echo -e "${BLUE}╔════════════════════════════════════════════╗${RESET}"
echo -e "${BLUE}║      SO_LONG MEMORY LEAK TESTER            ║${RESET}"
echo -e "${BLUE}╚════════════════════════════════════════════╝${RESET}"
echo ""

MAPS=(
    "assets/maps/error_no_player.ber"
    "assets/maps/error_no_exit.ber"
    "assets/maps/error_no_collectible.ber"
    "assets/maps/error_two_players.ber"
    "assets/maps/error_two_exits.ber"
    "assets/maps/error_wall_top.ber"
    "assets/maps/error_wall_bottom.ber"
    "assets/maps/error_wall_left.ber"
    "assets/maps/error_wall_right.ber"
    "assets/maps/error_not_rectangular.ber"
    "assets/maps/error_invalid_char.ber"
    "assets/maps/error_no_path_to_collectible.ber"
    "assets/maps/error_no_path_to_exit.ber"
)

PASSED=0
FAILED=0

for MAP in "${MAPS[@]}"; do
    MAP_NAME=$(basename "$MAP" .ber)
    printf "${YELLOW}[LEAK TEST]${RESET} %-35s " "$MAP_NAME"
    
    # Run valgrind and capture output
    VALGRIND_OUTPUT=$(valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all \
        --error-exitcode=1 ../so_long "$MAP" 2>&1)
    EXIT_CODE=$?
    
    # Check if no leaks
    if echo "$VALGRIND_OUTPUT" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "${GREEN}✓ NO LEAKS${RESET}"
        ((PASSED++))
    else
        echo -e "${RED}✗ LEAK DETECTED${RESET}"
        echo "$VALGRIND_OUTPUT" | grep -E "definitely lost|indirectly lost|still reachable" | head -3
        ((FAILED++))
    fi
done

echo ""
echo -e "${BLUE}╔════════════════════════════════════════════╗${RESET}"
echo -e "${BLUE}║           MEMORY TEST SUMMARY              ║${RESET}"
echo -e "${BLUE}╠════════════════════════════════════════════╣${RESET}"
printf "║  ${GREEN}No Leaks: %2d${RESET} | ${RED}Leaks: %2d${RESET} | Total: %2d      ║\n" $PASSED $FAILED $((PASSED + FAILED))
echo -e "${BLUE}╚════════════════════════════════════════════╝${RESET}"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 NO MEMORY LEAKS! 🎉${RESET}"
    exit 0
else
    echo -e "${RED}⚠️  MEMORY LEAKS DETECTED! ⚠️${RESET}"
    exit 1
fi
