#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "ft_printf.c"
#include "ft_printf.h"
#include <stdbool.h>

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Global test counters
int total_tests = 0;
int passed_tests = 0;
int failed_tests = 0;

// Timing variables
double total_printf_time = 0.0;
double total_ft_printf_time = 0.0;

bool	fnot(bool condition)
{
	return (!condition);
}

int	len(char *str)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		counter++;
		str++;
	}
	return (counter);
}

int	printchar(char c)
{
	return (write(1, &c, 1));
}

int	printstr(char *str)
{
	if (fnot(str))
		return (printstr("(null)"));
	return (write(1, str, len(str)));
}

// Microsecond precision timing function
double get_time_microseconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

// Nanosecond precision timing function (if available)
double get_time_nanoseconds()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000000000.0 + ts.tv_nsec);
}

void print_test_header(const char *test_name)
{
	printf("\n%s*-- %s --*%s\n", CYAN, test_name, RESET);
}

void print_test_result_with_timing(const char *test_name, int original_result, int ft_result, 
                                  double printf_time, double ft_printf_time, const char *description)
{
	total_tests++;
	
	printf("%s.  printf: %s", YELLOW, RESET);
	printf("=> (%d) [%.3f μs]\n", original_result, printf_time);
	printf("%sft_printf: %s", YELLOW, RESET);
	printf("=> (%d) [%.3f μs]\n", ft_result, ft_printf_time);
	
	// Performance comparison
	if (ft_printf_time > 0 && printf_time > 0) {
		double ratio = ft_printf_time / printf_time;
		printf("%sPerformance: %s", BLUE, RESET);
		if (ratio < 1.0) {
			printf("%sft_printf %.1fx daha hızlı%s\n", GREEN, 1.0/ratio, RESET);
		} else if (ratio > 1.0) {
			printf("%sft_printf %.1fx daha yavaş%s\n", RED, ratio, RESET);
		} else {
			printf("Yaklaşık eşit\n");
		}
	}
	
	if (original_result == ft_result) {
		printf("%s[✓ PASSED]%s %s\n", GREEN, RESET, test_name);
		passed_tests++;
	} else {
		printf("%s[✗ FAILED]%s %s\n", RED, RESET, test_name);
		printf("%s   Beklenen: %d, Alınan: %d%s\n", RED, original_result, ft_result, RESET);
		if (description) {
			printf("%s   Olası neden: %s%s\n", MAGENTA, description, RESET);
		}
		failed_tests++;
	}
	printf("\n");
}

void print_final_summary()
{
	printf("\n%s══════════════════════════════════════════════════════════════%s\n", BOLD, RESET);
	printf("%s                        TEST SONUÇLARI                        %s\n", BOLD, RESET);
	printf("%s══════════════════════════════════════════════════════════════%s\n", BOLD, RESET);
	
	printf("%sToplam Test: %s%d\n", BOLD, RESET, total_tests);
	printf("%sGeçen Test: %s%s%d%s\n", BOLD, GREEN, BOLD, passed_tests, RESET);
	printf("%sKalan Test: %s%s%d%s\n", BOLD, RED, BOLD, failed_tests, RESET);
	
	double success_rate = (double)passed_tests / total_tests * 100;
	printf("%sBaşarı Oranı: %s", BOLD, RESET);
	
	if (success_rate == 100.0) {
		printf("%s%.1f%%%s\n", GREEN, success_rate, RESET);
	} else if (success_rate >= 80.0) {
		printf("%s%.1f%%%s\n", YELLOW, success_rate, RESET);
	} else {
		printf("%s%.1f%%%s\n", RED, success_rate, RESET);
	}
	
	printf("%s══════════════════════════════════════════════════════════════%s\n", BOLD, RESET);
	
	// Performance summary
	printf("%s                      PERFORMANS ÖZETI                       %s\n", BOLD, RESET);
	printf("%s══════════════════════════════════════════════════════════════%s\n", BOLD, RESET);
	
	printf("%sToplam printf süresi: %s%.3f μs\n", BOLD, RESET, total_printf_time);
	printf("%sToplam ft_printf süresi: %s%.3f μs\n", BOLD, RESET, total_ft_printf_time);
	
	if (total_printf_time > 0 && total_ft_printf_time > 0) {
		double avg_ratio = total_ft_printf_time / total_printf_time;
		printf("%sOrtalama performans: %s", BOLD, RESET);
		if (avg_ratio < 1.0) {
			printf("%sft_printf %.1fx daha hızlı%s\n", GREEN, 1.0/avg_ratio, RESET);
		} else if (avg_ratio > 1.0) {
			printf("%sft_printf %.1fx daha yavaş%s\n", RED, avg_ratio, RESET);
		} else {
			printf("Yaklaşık eşit\n");
		}
	}
	
	printf("%s══════════════════════════════════════════════════════════════%s\n", BOLD, RESET);
}

// Macro for timing tests
#define TIME_TEST(test_name, printf_call, ft_printf_call, description) \
do { \
	print_test_header(test_name); \
	\
	double start_time, end_time; \
	double printf_time, ft_printf_time; \
	int original_result, ft_result; \
	\
	/* Time printf */ \
	start_time = get_time_microseconds(); \
	original_result = printf_call; \
	end_time = get_time_microseconds(); \
	printf_time = end_time - start_time; \
	\
	/* Time ft_printf */ \
	start_time = get_time_microseconds(); \
	ft_result = ft_printf_call; \
	end_time = get_time_microseconds(); \
	ft_printf_time = end_time - start_time; \
	\
	total_printf_time += printf_time; \
	total_ft_printf_time += ft_printf_time; \
	\
	print_test_result_with_timing(test_name, original_result, ft_result, \
	                             printf_time, ft_printf_time, description); \
} while(0)

int main()
{
    void *ponter;
    char *ponterr = "pontero";

    printf("%s\n--------------------------\n\n   ı~~~~~~~~~~~~~~~~~ı\n   |                 |\n   ~ ft_printf tests ~\n   |   with timing   |\n   ı~~~~~~~~~~~~~~~~~ı\n%s", CYAN, RESET);
    printchar('\n');

    // Test 1: NULL format string
    TIME_TEST("printf NULL", 
              printf(NULL, 42), 
              ft_printf(NULL, 42),
              "NULL format string işlemi undefined behavior'dur. Bazı sistemlerde segfault verir.");

    // Test 2: Normal format string
    TIME_TEST("printf2", 
              printf(" test_case \"\n", 42) - 2, 
              ft_printf(" test_case \"\n", 42) - 2,
              "Format specifier olmayan string'lerde extra argümanlar göz ardı edilir.");

    // Test 3: Empty string
    TIME_TEST("printf3", 
              printf("", 42), 
              ft_printf("", 42),
              "Boş string 0 karakter yazdırmalı.");

    // Test 4: Invalid format specifiers
    TIME_TEST("printf4", 
              printf(" %K btuncer %w \"\n", 'A', 48, '0', NULL) - 2, 
              ft_printf(" %K btuncer %w \"\n", 'A', 48, '0', NULL) - 2,
              "%K ve %w geçersiz format specifier'lar. Literal olarak yazdırılmalı.");

    // Test 5: Character format
    TIME_TEST("%c", 
              printf(" %c %c %c %c %c %c \"\n", 'A', 48, '0', NULL, -42, 1024) - 2, 
              ft_printf(" %c %c %c %c %c %c \"\n", 'A', 48, '0', NULL, -42, 1024) - 2,
              "%c NULL değeri ve büyük sayıları char'a cast eder. Overflow olabilir.");

    // Test 6: String format
    TIME_TEST("%s", 
              printf(" %s %s %s %s %s %s \"\n", "test_case", NULL, "intrabtuncer", "", " ", ponterr) - 2, 
              ft_printf(" %s %s %s %s %s %s \"\n", "test_case", NULL, "intrabtuncer", "", " ", ponterr) - 2,
              "%s NULL değeri için \"(null)\" yazdırmalı.");

    // Test 7: Pointer format
    TIME_TEST("%p", 
              printf(" %p %p %p %p %p %p %p %p \"\n", "ponter", ponter, NULL, "", -42, ponterr, LONG_MIN, LONG_MAX) - 2, 
              ft_printf(" %p %p %p %p %p %p %p %p \"\n", "ponter", ponter, NULL, "", -42, ponterr, LONG_MIN, LONG_MAX) - 2,
              "%p adresleri hexadecimal formatında yazdırır. NULL için \"(nil)\" veya \"0x0\" olabilir.");

    // Test 8: Advanced pointer format
    TIME_TEST("%p2 (advanced)", 
              printf(" %p %p %p %p %p %p \"\n", LONG_MIN + 1, LONG_MIN + 2, LONG_MIN + 3, -ULONG_MAX, ULONG_MAX, ULONG_MAX - 1) - 2, 
              ft_printf(" %p %p %p %p %p %p \"\n", LONG_MIN + 1, LONG_MIN + 2, LONG_MIN + 3, -ULONG_MAX, ULONG_MAX, ULONG_MAX - 1) - 2,
              "Büyük sayılar pointer'a cast edilirken implementation-defined davranış gösterir.");

    // Test 9: Decimal format
    TIME_TEST("%d && %i", 
              printf(" %d %d %d %d %d %d %d %d %d %i \"\n", 42, -42, INT_MIN, INT_MAX, NULL, "TEST", "", LONG_MIN, LONG_MAX, ponter) - 2, 
              ft_printf(" %d %d %d %d %d %d %d %d %d %i \"\n", 42, -42, INT_MIN, INT_MAX, NULL, "TEST", "", LONG_MIN, LONG_MAX, ponter) - 2,
              "%d ve %i pointer'ları int'e cast eder. Büyük değerler overflow yapar.");

    // Test 10: Unsigned format
    TIME_TEST("%u", 
              printf(" %u %u %u %u %u %u %u \"\n", INT_MIN, 2147483650, -1, NULL, ULONG_MAX, LONG_MAX, LLONG_MAX) - 2, 
              ft_printf(" %u %u %u %u %u %u %u \"\n", INT_MIN, 2147483650, -1, NULL, ULONG_MAX, LONG_MAX, LLONG_MAX) - 2,
              "%u negatif sayıları unsigned'a cast eder. -1 -> 4294967295 olur.");

    // Test 11: Lowercase hex
    TIME_TEST("%x", 
              printf(" %x %x %x %x %x %x %x %x \"\n", NULL, INT_MIN, INT_MAX, 0, '0', LONG_MIN, LONG_MAX, LLONG_MAX) - 2, 
              ft_printf(" %x %x %x %x %x %x %x %x \"\n", NULL, INT_MIN, INT_MAX, 0, '0', LONG_MIN, LONG_MAX, LLONG_MAX) - 2,
              "%x küçük harflerle hex yazdırır. Büyük değerler kesilir.");

    // Test 12: Uppercase hex
    TIME_TEST("%X", 
              printf(" %X %X %X %X %X %X %X %X \"\n", NULL, INT_MIN, INT_MAX, 0, '0', LONG_MIN, LONG_MAX, LLONG_MAX) - 2, 
              ft_printf(" %X %X %X %X %X %X %X %X \"\n", NULL, INT_MIN, INT_MAX, 0, '0', LONG_MIN, LONG_MAX, LLONG_MAX) - 2,
              "%X büyük harflerle hex yazdırır. %x ile aynı logic.");

    // Test 13: Percent format
    TIME_TEST("%%", 
              printf(" %% %%%|%%%%|%%%%% | %%%%%%%%%%%% %%%%% \"\n") - 2, 
              ft_printf(" %% %%%|%%%%|%%%%% | %%%%%%%%%%%% %%%%% \"\n") - 2,
              "%% literal '%' karakteri yazdırır.");

    // Final summary
    print_final_summary();
    return 0;
}
