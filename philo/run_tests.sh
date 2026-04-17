#!/bin/bash
# run_tests.sh — philo_tests.md içindeki tüm testleri paralel çalıştırır
# Kullanım:
#   ./run_tests.sh [TIMEOUT] [JOBS]
#     TIMEOUT: live testlerin max süresi (default: 6s)
#     JOBS:    aynı anda çalışacak test sayısı (default: 3)
#
# Örnek: ./run_tests.sh 8 4   # 8s timeout, 4 paralel

set -u

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PHILO="$SCRIPT_DIR/philo"

TIMEOUT="${1:-6}"
JOBS="${2:-3}"

if [ ! -x "$PHILO" ]; then
	echo "philo executable bulunamadı: $PHILO"
	echo "önce 'make' çalıştırın."
	exit 1
fi

RED=$'\e[31m'
GREEN=$'\e[32m'
YELLOW=$'\e[33m'
CYAN=$'\e[36m'
BOLD=$'\e[1m'
RESET=$'\e[0m'

TMPDIR=$(mktemp -d)
trap 'rm -rf "$TMPDIR"' EXIT

# run_one MODE ARGS HAS_MUST_EAT RESULT_FILE
# MODE: live|die
# HAS_MUST_EAT: yes|no (live için anlamlı)
run_one() {
	local mode="$1"
	local args="$2"
	local has_must_eat="$3"
	local result_file="$4"
	local out
	local rc
	local status
	local detail=""

	out=$(timeout --preserve-status -s INT "$TIMEOUT" "$PHILO" $args 2>&1)
	rc=$?

	if [ "$mode" = "live" ]; then
		if echo "$out" | grep -q " died"; then
			status="FAIL"
			detail=$(echo "$out" | grep " died" | head -1)
		elif [ "$has_must_eat" = "yes" ] && [ $rc -eq 124 ]; then
			status="FAIL"
			detail="timeout — must_eat tamamlanmadı"
		else
			status="OK"
		fi
	else
		# die
		if [ $rc -eq 124 ]; then
			status="FAIL"
			detail="timeout — died basılmadı"
		elif echo "$out" | grep -q " died"; then
			status="OK"
			detail=$(echo "$out" | grep " died" | head -1)
		else
			status="FAIL"
			detail="died basılmadı"
		fi
	fi

	printf "%s|%s|%s|%s\n" "$mode" "$args" "$status" "$detail" >"$result_file"
}

# test listesi — her satır: mode|args|has_must_eat|section
TESTS=(
	# Mandatory
	"die|1 800 200 200 10|no|Mandatory"
	"live|5 800 200 200 7|yes|Mandatory"
	"live|4 410 200 200 10|yes|Mandatory"
	"die|4 310 200 100 10|no|Mandatory"

	# Tek sayıda - yaşamalı
	"live|5 800 200 200|no|Tek-Live"
	"live|5 610 200 200|no|Tek-Live"
	"live|199 610 200 200|no|Tek-Live"
	"live|5 610 200 100|no|Tek-Live"
	"live|5 601 200 200|no|Tek-Live"
	"live|31 610 200 100|no|Tek-Live"
	"live|31 610 200 200|no|Tek-Live"
	"live|31 605 200 200|no|Tek-Live"
	"live|31 601 200 200|no|Tek-Live"
	"live|131 610 200 100|no|Tek-Live"
	"live|131 610 200 200|no|Tek-Live"
	"live|131 605 200 200|no|Tek-Live"
	"live|131 601 200 200|no|Tek-Live"
	"live|199 610 200 100|no|Tek-Live"
	"live|199 610 200 200|no|Tek-Live"
	"live|199 605 200 200|no|Tek-Live"
	"live|199 601 200 200|no|Tek-Live"

	# Çift sayıda - yaşamalı
	"live|4 410 200 100|no|Cift-Live"
	"live|4 410 200 200|no|Cift-Live"
	"live|198 610 200 200|no|Cift-Live"
	"live|198 800 200 200|no|Cift-Live"
	"live|50 410 200 100|no|Cift-Live"
	"live|50 410 200 200|no|Cift-Live"
	"live|50 405 200 200|no|Cift-Live"
	"live|50 401 200 200|no|Cift-Live"
	"live|130 410 200 100|no|Cift-Live"
	"live|130 410 200 200|no|Cift-Live"
	"live|130 405 200 200|no|Cift-Live"
	"live|130 401 200 200|no|Cift-Live"
	"live|198 410 200 100|no|Cift-Live"
	"live|198 410 200 200|no|Cift-Live"
	"live|198 405 200 200|no|Cift-Live"
	"live|198 401 200 200|no|Cift-Live"

	# Tek sayıda - ölmeli
	"die|4 310 200 100|no|Tek-Die"
	"die|1 800 200 100|no|Tek-Die"
	"die|3 596 200 200|no|Tek-Die"
	"die|3 599 200 200|no|Tek-Die"
	"die|3 600 200 200|no|Tek-Die"
	"die|31 596 200 200|no|Tek-Die"
	"die|31 599 200 200|no|Tek-Die"
	"die|31 600 200 200|no|Tek-Die"
	"die|131 596 200 200|no|Tek-Die"
	"die|131 599 200 200|no|Tek-Die"
	"die|131 600 200 200|no|Tek-Die"
	"die|199 596 200 200|no|Tek-Die"
	"die|199 599 200 200|no|Tek-Die"
	"die|199 600 200 200|no|Tek-Die"

	# Çift sayıda - ölmeli
	"die|3 599 200 200|no|Cift-Die"
	"die|31 599 200 200|no|Cift-Die"
	"die|131 596 200 200|no|Cift-Die"
	"die|4 310 200 100|no|Cift-Die"
	"die|50 396 200 200|no|Cift-Die"
	"die|50 399 200 200|no|Cift-Die"
	"die|50 400 200 200|no|Cift-Die"
	"die|130 396 200 200|no|Cift-Die"
	"die|130 399 200 200|no|Cift-Die"
	"die|130 400 200 200|no|Cift-Die"
	"die|198 396 200 200|no|Cift-Die"
	"die|198 399 200 200|no|Cift-Die"
	"die|198 400 200 200|no|Cift-Die"
)

TOTAL=${#TESTS[@]}
echo "${BOLD}Toplam $TOTAL test, timeout=${TIMEOUT}s, paralel=${JOBS}${RESET}"
echo

# testleri paralel başlat, max JOBS aynı anda
running=0
idx=0
for entry in "${TESTS[@]}"; do
	IFS='|' read -r mode args has_must_eat _section <<<"$entry"
	result_file="$TMPDIR/result_$idx"
	idx=$((idx + 1))

	run_one "$mode" "$args" "$has_must_eat" "$result_file" &
	running=$((running + 1))

	if [ $running -ge $JOBS ]; then
		wait -n
		running=$((running - 1))
	fi
done
wait

# sonuçları sırayla oku ve yazdır
PASS=0
FAIL=0
current_section=""

for i in $(seq 0 $((TOTAL - 1))); do
	entry="${TESTS[$i]}"
	IFS='|' read -r _mode _args _hme section <<<"$entry"

	if [ "$section" != "$current_section" ]; then
		echo
		echo "${BOLD}=== $section ===${RESET}"
		current_section="$section"
	fi

	result=$(cat "$TMPDIR/result_$i" 2>/dev/null || echo "|||FAIL|sonuç yok")
	IFS='|' read -r r_mode r_args r_status r_detail <<<"$result"

	if [ "$r_mode" = "live" ]; then
		tag="${CYAN}[LIVE]${RESET}"
	else
		tag="${YELLOW}[DIE ]${RESET}"
	fi

	if [ "$r_status" = "OK" ]; then
		printf "%b ./philo %-22s ${GREEN}OK${RESET}" "$tag" "$r_args"
		[ -n "$r_detail" ] && printf "  %s" "$r_detail"
		echo
		PASS=$((PASS + 1))
	else
		printf "%b ./philo %-22s ${RED}FAIL${RESET}" "$tag" "$r_args"
		[ -n "$r_detail" ] && printf "  %s" "$r_detail"
		echo
		FAIL=$((FAIL + 1))
	fi
done

echo
echo "${BOLD}============================${RESET}"
echo "${BOLD}Toplam: $TOTAL  |  ${GREEN}PASS: $PASS${RESET}  |  ${RED}FAIL: $FAIL${RESET}"
echo "${BOLD}============================${RESET}"

[ $FAIL -eq 0 ]
