#!/usr/bin/env bash
set -u
set -o pipefail

ROOT_DIR="$(cd -- "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PS_BIN="$ROOT_DIR/push_swap"
CHECKER_BIN="$ROOT_DIR/"checker_linux""
LOG_DIR="$ROOT_DIR/tester/logs"

VALGRIND_BIN=""
if command -v valgrind >/dev/null 2>&1; then
	VALGRIND_BIN="$(command -v valgrind)"
fi
VALGRIND_FLAGS=(
	--leak-check=full
	--show-leak-kinds=all
	--errors-for-leak-kinds=all
	--track-origins=yes
	--error-exitcode=42
	--quiet
)

passes=0
failures=0
leak_failures=0

prepare() {
	mkdir -p "$LOG_DIR"
	rm -f "$LOG_DIR"/*

	if [ ! -x "$PS_BIN" ]; then
		echo "Building push_swap..."
		if ! make -C "$ROOT_DIR" >/dev/null; then
			echo "Cannot build push_swap; aborting tests."
			exit 1
		fi
	fi
	if [ ! -x "$PS_BIN" ]; then
		echo "push_swap binary is missing after build; aborting."
		exit 1
	fi

	if [ -z "$VALGRIND_BIN" ]; then
		echo "Valgrind not found in PATH -> leak checks will be skipped."
	else
		echo "Valgrind detected at: $VALGRIND_BIN"
	fi

	if [ -x "$CHECKER_BIN" ]; then
		echo "checker_linux detected and will be used for OK/KO validation."
	else
		echo "checker_linux not found; correctness checks will be skipped."
	fi
	echo
}

format_args() {
	local out=""
	local arg
	for arg in "$@"; do
		out+="\"${arg}\" "
	done
	printf "%s" "${out%% }"
}

run_valgrind_check() {
	local name=$1
	local mode=$2
	shift 2
	local args=("$@")
	local cmd=("$PS_BIN")

	if [ "$mode" = "single" ]; then
		cmd+=("${args[0]}")
	else
		cmd+=("${args[@]}")
	fi

	local log_file="$LOG_DIR/valgrind_${name}.log"
	"$VALGRIND_BIN" "${VALGRIND_FLAGS[@]}" --log-file="$log_file" "${cmd[@]}" >/dev/null 2>&1
	local status=$?

	if [ $status -eq 42 ]; then
		leak_failures=$((leak_failures + 1))
		printf "leaks (see %s)" "$(basename "$log_file")"
	else
		printf "clean"
	fi
}

report() {
	printf "%-22s | %s\n" "$1" "$2"
}

run_error_case() {
	local name=$1
	local mode=$2
	shift 2
	local args=("$@")
	local cmd_args=()

	if [ "$mode" = "single" ]; then
		cmd_args+=("${args[0]}")
	else
		cmd_args+=("${args[@]}")
	fi

	local stderr_file="$LOG_DIR/${name}_stderr.log"
	local stdout_file="$LOG_DIR/${name}_stdout.log"

	"$PS_BIN" "${cmd_args[@]}" >"$stdout_file" 2>"$stderr_file"
	local status=$?

	local leak_info="skip"
	if [ -n "$VALGRIND_BIN" ]; then
		leak_info=$(run_valgrind_check "$name" "$mode" "${args[@]}")
	fi

	local result=""
	if [ $status -eq 0 ]; then
		result="FAIL expected non-zero exit | args: $(format_args "${cmd_args[@]}")"
	elif ! grep -q "Error" "$stderr_file"; then
		result="FAIL missing \"Error\" on stderr | args: $(format_args "${cmd_args[@]}")"
	elif [ -s "$stdout_file" ]; then
		result="FAIL unexpected stdout output | args: $(format_args "${cmd_args[@]}")"
	elif [[ $leak_info == leaks* ]]; then
		result="FAIL leak detected ($leak_info) | args: $(format_args "${cmd_args[@]}")"
	else
		result="PASS (exit=$status, stderr=Error)${leak_info:+ | valgrind: $leak_info}"
	fi

	if [[ $result == PASS* ]]; then
		passes=$((passes + 1))
	else
		failures=$((failures + 1))
	fi
	report "$name [error]" "$result"
}

run_valid_case() {
	local name=$1
	local mode=$2
	shift 2
	local args=("$@")
	local cmd_args=()

	if [ "$mode" = "single" ]; then
		cmd_args+=("${args[0]}")
	else
		cmd_args+=("${args[@]}")
	fi

	local ops
	if ! ops=$("$PS_BIN" "${cmd_args[@]}"); then
		report "$name [valid]" "FAIL push_swap exited with error | args: $(format_args "${cmd_args[@]}")"
		failures=$((failures + 1))
		return
	fi
	local ops_file="$LOG_DIR/${name}_ops.log"
	printf "%s\n" "$ops" >"$ops_file"

	local checker_result="skipped"
	if [ -x "$CHECKER_BIN" ]; then
		local checker_out="$LOG_DIR/${name}_checker.out"
		local checker_err="$LOG_DIR/${name}_checker.err"
			if [ -n "$ops" ]; then
				# Ensure operations end with a newline when piping to checker
				checker_result="$(printf "%s\n" "$ops" | "$CHECKER_BIN" "${cmd_args[@]}" >"$checker_out" 2>"$checker_err"; cat "$checker_out")"
			else
				# If push_swap produced no operations, send zero bytes so checker sees EOF
				checker_result="$(printf "%s" "$ops" | "$CHECKER_BIN" "${cmd_args[@]}" >"$checker_out" 2>"$checker_err"; cat "$checker_out")"
			fi
		if [ "$checker_result" != "OK" ]; then
			report "$name [valid]" "FAIL checker returned '${checker_result:-<no output>}' | see $checker_out / $checker_err | args: $(format_args "${cmd_args[@]}")"
			failures=$((failures + 1))
			return
		fi
	fi

	local leak_info="skip"
	if [ -n "$VALGRIND_BIN" ]; then
		leak_info=$(run_valgrind_check "$name" "$mode" "${args[@]}")
	fi

	local op_count
	op_count=$(printf "%s\n" "$ops" | sed '/^$/d' | wc -l | tr -d ' ')
	local note="ops=${op_count}"
	if [ "$checker_result" != "skipped" ]; then
		note+=" | checker=$checker_result"
	fi
	if [ "$leak_info" != "skip" ]; then
		note+=" | valgrind: $leak_info"
	fi
	note+=" | ops_log=$(basename "$ops_file")"

	report "$name [valid]" "PASS $note | args: $(format_args "${cmd_args[@]}")"
	passes=$((passes + 1))
}

main() {
	prepare

	echo "== Error cases =="
	run_error_case "empty_single_arg" single ""
	run_error_case "spaces_single_arg" single "   "
	run_error_case "non_numeric_multi" multi 1 a 3
	run_error_case "non_numeric_single" single "3 4b 5"
	run_error_case "duplicate_multi" multi 1 2 1
	run_error_case "duplicate_single" single "9 -1 9"
	run_error_case "overflow" multi 2147483648
	run_error_case "underflow" multi -2147483649
	run_error_case "double_sign" multi ++2
	run_error_case "sign_only" multi "+"
	run_error_case "mixed_garbage_single" single "1 2 three 4"

	echo
	echo "== Valid cases =="
	run_valid_case "already_sorted" multi 1 2 3
	run_valid_case "two_elements" multi 2 1
	run_valid_case "reverse_order" multi 5 4 3 2 1
	run_valid_case "with_negatives" multi -3 0 2 -1 5
	run_valid_case "extreme_values" multi -2147483648 0 2147483647 1 -1
	run_valid_case "single_arg_list" single "10 3 5 8 1 7 6"

	echo
	echo "Totals -> pass: $passes | fail: $failures | leak issues: $leak_failures"
	if [ -n "$VALGRIND_BIN" ]; then
		echo "Valgrind logs: $LOG_DIR/valgrind_*.log"
	else
		echo "Leak checks skipped because valgrind is not available."
	fi

	if [ $failures -ne 0 ] || [ $leak_failures -ne 0 ]; then
		exit 1
	fi
}

main "$@"
