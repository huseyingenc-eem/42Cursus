#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <locale.h>
#include "ft_printf.h"

// Renk kodlari
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Test sonuclari
static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

// Test fonksiyonu prototipleri
void test_char(void);
void test_string(void);
void test_pointer(void);
void test_decimal(void);
void test_integer(void);
void test_unsigned(void);
void test_hex_lower(void);
void test_hex_upper(void);
void test_percent(void);
void test_mixed(void);
void test_edge_cases(void);

// Yardimci fonksiyonlar
int compare_outputs(int original_ret, int my_ret, char *test_name);
void print_test_header(char *test_name);
void print_summary(void);

int main(void)
{
    // Turkce karakter destegi icin locale ayari
    setlocale(LC_ALL, "tr_TR.UTF-8");
    
    printf(BOLD CYAN "\n=== FT_PRINTF KAPSAMLI TEST SUITI ===" RESET "\n\n");
    
    test_char();
    test_string();
    test_pointer();
    test_decimal();
    test_integer();
    test_unsigned();
    test_hex_lower();
    test_hex_upper();
    test_percent();
    test_mixed();
    test_edge_cases();
    
    print_summary();
    return (0);
}

int compare_outputs(int original_ret, int my_ret, char *test_name)
{
    total_tests++;
    if (original_ret == my_ret) {
        printf(GREEN "✓ PASS" RESET " - %s (Return: %d)\n", test_name, original_ret);
        passed_tests++;
        return 1;
    } else {
        printf(RED "✗ FAIL" RESET " - %s " YELLOW "(Original: %d, My Func: %d)" RESET "\n", 
               test_name, original_ret, my_ret);
        failed_tests++;
        return 0;
    }
}

void print_test_header(char *test_name)
{
    printf(BOLD BLUE "\n%s" RESET "\n", test_name);
    printf("────────────────────────────────────────────────────────────────────\n");
}

void print_summary(void)
{
    printf(BOLD CYAN "\n=== TEST SONUCLARI ===" RESET "\n");
    printf("────────────────────────\n");
    printf(BOLD "Toplam Test: %d\n" RESET, total_tests);
    printf(GREEN BOLD "Basarili: %d\n" RESET, passed_tests);
    printf(RED BOLD "Basarisiz: %d\n" RESET, failed_tests);
    
    if (failed_tests == 0) {
        printf(GREEN BOLD "\n🎉 TUM TESTLER BASARILI! 🎉\n" RESET);
    } else {
        printf(RED BOLD "\n⚠️  %d TEST BASARISIZ OLDU ⚠️\n" RESET, failed_tests);
    }
    printf("\n");
}

void test_char(void)
{
    int original_ret, my_ret;
    
    print_test_header("%%c - KARAKTER TESTLERI");
    
    // Normal karakterler
    printf(MAGENTA "Test 1A: " RESET "Normal Karakter 'A'\n");
    original_ret = printf("Original: [%c]\n", 'A');
    my_ret = ft_printf("My Func : [%c]\n", 'A');
    compare_outputs(original_ret, my_ret, "Karakter 'A'");
    
    printf(MAGENTA "Test 1B: " RESET "Normal Karakter 'z'\n");
    original_ret = printf("Original: [%c]\n", 'z');
    my_ret = ft_printf("My Func : [%c]\n", 'z');
    compare_outputs(original_ret, my_ret, "Karakter 'z'");
    
    // Ozel karakterler
    printf(MAGENTA "Test 2A: " RESET "Newline Karakteri\n");
    original_ret = printf("Original: [%c]\n", '\n');
    my_ret = ft_printf("My Func : [%c]\n", '\n');
    compare_outputs(original_ret, my_ret, "Newline Karakteri");
    
    printf(MAGENTA "Test 2B: " RESET "Tab Karakteri\n");
    original_ret = printf("Original: [%c]\n", '\t');
    my_ret = ft_printf("My Func : [%c]\n", '\t');
    compare_outputs(original_ret, my_ret, "Tab Karakteri");
    
    // Null karakter
    printf(MAGENTA "Test 3: " RESET "Null Karakter\n");
    original_ret = printf("Original: [%c]\n", '\0');
    my_ret = ft_printf("My Func : [%c]\n", '\0');
    compare_outputs(original_ret, my_ret, "Null Karakter");
    
    // ASCII degerleri
    printf(MAGENTA "Test 4A: " RESET "ASCII 32 (Space)\n");
    original_ret = printf("Original: [%c]\n", 32);
    my_ret = ft_printf("My Func : [%c]\n", 32);
    compare_outputs(original_ret, my_ret, "ASCII 32 (Space)");
    
    printf(MAGENTA "Test 4B: " RESET "ASCII 126 (~)\n");
    original_ret = printf("Original: [%c]\n", 126);
    my_ret = ft_printf("My Func : [%c]\n", 126);
    compare_outputs(original_ret, my_ret, "ASCII 126 (~)");
}

void test_string(void)
{
    int original_ret, my_ret;
    char *null_str = NULL;
    
    print_test_header("%%s - STRING TESTLERI");
    
    // Normal string
    printf(MAGENTA "Test 1: " RESET "Normal String\n");
    original_ret = printf("Original: [%s]\n", "Hello World");
    my_ret = ft_printf("My Func : [%s]\n", "Hello World");
    compare_outputs(original_ret, my_ret, "Normal String");
    
    // Bos string
    printf(MAGENTA "Test 2: " RESET "Bos String\n");
    original_ret = printf("Original: [%s]\n", "");
    my_ret = ft_printf("My Func : [%s]\n", "");
    compare_outputs(original_ret, my_ret, "Bos String");
    
    // NULL pointer
    printf(MAGENTA "Test 3: " RESET "NULL Pointer\n");
    original_ret = printf("Original: [%s]\n", null_str);
    my_ret = ft_printf("My Func : [%s]\n", null_str);
    compare_outputs(original_ret, my_ret, "NULL Pointer");
    
    // Ozel karakterler iceren string
    printf(MAGENTA "Test 4: " RESET "Ozel Karakterler\n");
    original_ret = printf("Original: [%s]\n", "Hello\nWorld\t!");
    my_ret = ft_printf("My Func : [%s]\n", "Hello\nWorld\t!");
    compare_outputs(original_ret, my_ret, "Ozel Karakterler");
    
    // Uzun string
    printf(MAGENTA "Test 5: " RESET "Uzun String\n");
    original_ret = printf("Original: [%s]\n", "Bu cok uzun bir string ornegidir ve performans testinde kullanilir");
    my_ret = ft_printf("My Func : [%s]\n", "Bu cok uzun bir string ornegidir ve performans testinde kullanilir");
    compare_outputs(original_ret, my_ret, "Uzun String");
}

void test_pointer(void)
{
    int original_ret, my_ret;
    int x = 42;
    char *str = "test";
    void *null_ptr = NULL;
    
    print_test_header("%%p - POINTER TESTLERI");
    
    // Gecerli pointer
    printf(MAGENTA "Test 1: " RESET "Integer Pointer\n");
    original_ret = printf("Original: [%p]\n", &x);
    my_ret = ft_printf("My Func : [%p]\n", &x);
    compare_outputs(original_ret, my_ret, "Integer Pointer");
    
    // String pointer
    printf(MAGENTA "Test 2: " RESET "String Pointer\n");
    original_ret = printf("Original: [%p]\n", str);
    my_ret = ft_printf("My Func : [%p]\n", str);
    compare_outputs(original_ret, my_ret, "String Pointer");
    
    // NULL pointer
    printf(MAGENTA "Test 3: " RESET "NULL Pointer\n");
    original_ret = printf("Original: [%p]\n", null_ptr);
    my_ret = ft_printf("My Func : [%p]\n", null_ptr);
    compare_outputs(original_ret, my_ret, "NULL Pointer");
    
    // Fonksiyon pointer
    printf(MAGENTA "Test 4: " RESET "Fonksiyon Pointer\n");
    original_ret = printf("Original: [%p]\n", &test_pointer);
    my_ret = ft_printf("My Func : [%p]\n", &test_pointer);
    compare_outputs(original_ret, my_ret, "Fonksiyon Pointer");
}

void test_decimal(void)
{
    int original_ret, my_ret;
    
    print_test_header("%%d - DECIMAL TESTLERI");
    
    // Pozitif sayilar
    printf(MAGENTA "Test 1A: " RESET "Pozitif Sayi (42)\n");
    original_ret = printf("Original: [%d]\n", 42);
    my_ret = ft_printf("My Func : [%d]\n", 42);
    compare_outputs(original_ret, my_ret, "Pozitif Sayi (42)");
    
    printf(MAGENTA "Test 1B: " RESET "Pozitif Sayi (12345)\n");
    original_ret = printf("Original: [%d]\n", 12345);
    my_ret = ft_printf("My Func : [%d]\n", 12345);
    compare_outputs(original_ret, my_ret, "Pozitif Sayi (12345)");
    
    // Negatif sayilar
    printf(MAGENTA "Test 2A: " RESET "Negatif Sayi (-42)\n");
    original_ret = printf("Original: [%d]\n", -42);
    my_ret = ft_printf("My Func : [%d]\n", -42);
    compare_outputs(original_ret, my_ret, "Negatif Sayi (-42)");
    
    printf(MAGENTA "Test 2B: " RESET "Negatif Sayi (-12345)\n");
    original_ret = printf("Original: [%d]\n", -12345);
    my_ret = ft_printf("My Func : [%d]\n", -12345);
    compare_outputs(original_ret, my_ret, "Negatif Sayi (-12345)");
    
    // Sifir
    printf(MAGENTA "Test 3: " RESET "Sifir\n");
    original_ret = printf("Original: [%d]\n", 0);
    my_ret = ft_printf("My Func : [%d]\n", 0);
    compare_outputs(original_ret, my_ret, "Sifir");
    
    // Sinir degerleri
    printf(MAGENTA "Test 4A: " RESET "INT_MAX\n");
    original_ret = printf("Original: [%d]\n", INT_MAX);
    my_ret = ft_printf("My Func : [%d]\n", INT_MAX);
    compare_outputs(original_ret, my_ret, "INT_MAX");
    
    printf(MAGENTA "Test 4B: " RESET "INT_MIN\n");
    original_ret = printf("Original: [%d]\n", INT_MIN);
    my_ret = ft_printf("My Func : [%d]\n", INT_MIN);
    compare_outputs(original_ret, my_ret, "INT_MIN");
}

void test_integer(void)
{
    int original_ret, my_ret;
    
    print_test_header("%%i - INTEGER TESTLERI");
    
    printf(MAGENTA "Test 1: " RESET "Pozitif Sayi (42)\n");
    original_ret = printf("Original: [%i]\n", 42);
    my_ret = ft_printf("My Func : [%i]\n", 42);
    compare_outputs(original_ret, my_ret, "Integer Pozitif (42)");
    
    printf(MAGENTA "Test 2: " RESET "Negatif Sayi (-42)\n");
    original_ret = printf("Original: [%i]\n", -42);
    my_ret = ft_printf("My Func : [%i]\n", -42);
    compare_outputs(original_ret, my_ret, "Integer Negatif (-42)");
    
    printf(MAGENTA "Test 3: " RESET "Sifir\n");
    original_ret = printf("Original: [%i]\n", 0);
    my_ret = ft_printf("My Func : [%i]\n", 0);
    compare_outputs(original_ret, my_ret, "Integer Sifir");
    
    printf(MAGENTA "Test 4A: " RESET "INT_MAX\n");
    original_ret = printf("Original: [%i]\n", INT_MAX);
    my_ret = ft_printf("My Func : [%i]\n", INT_MAX);
    compare_outputs(original_ret, my_ret, "Integer INT_MAX");
    
    printf(MAGENTA "Test 4B: " RESET "INT_MIN\n");
    original_ret = printf("Original: [%i]\n", INT_MIN);
    my_ret = ft_printf("My Func : [%i]\n", INT_MIN);
    compare_outputs(original_ret, my_ret, "Integer INT_MIN");
}

void test_unsigned(void)
{
    int original_ret, my_ret;
    
    print_test_header("%%u - UNSIGNED TESTLERI");
    
    printf(MAGENTA "Test 1A: " RESET "Pozitif Sayi (42)\n");
    original_ret = printf("Original: [%u]\n", 42U);
    my_ret = ft_printf("My Func : [%u]\n", 42U);
    compare_outputs(original_ret, my_ret, "Unsigned (42)");
    
    printf(MAGENTA "Test 1B: " RESET "Buyuk Sayi\n");
    original_ret = printf("Original: [%u]\n", 4294967295U);
    my_ret = ft_printf("My Func : [%u]\n", 4294967295U);
    compare_outputs(original_ret, my_ret, "Unsigned Buyuk Sayi");
    
    printf(MAGENTA "Test 2: " RESET "Sifir\n");
    original_ret = printf("Original: [%u]\n", 0U);
    my_ret = ft_printf("My Func : [%u]\n", 0U);
    compare_outputs(original_ret, my_ret, "Unsigned Sifir");
    
    printf(MAGENTA "Test 3: " RESET "Negatif Cast\n");
    original_ret = printf("Original: [%u]\n", (unsigned int)-1);
    my_ret = ft_printf("My Func : [%u]\n", (unsigned int)-1);
    compare_outputs(original_ret, my_ret, "Unsigned Negatif Cast");
    
    printf(MAGENTA "Test 4: " RESET "UINT_MAX\n");
    original_ret = printf("Original: [%u]\n", UINT_MAX);
    my_ret = ft_printf("My Func : [%u]\n", UINT_MAX);
    compare_outputs(original_ret, my_ret, "UINT_MAX");
}

void test_hex_lower(void)
{
    int original_ret, my_ret;
    
    print_test_header("%%x - HEXADECIMAL LOWERCASE TESTLERI");
    
    printf(MAGENTA "Test 1A: " RESET "Sifir\n");
    original_ret = printf("Original: [%x]\n", 0);
    my_ret = ft_printf("My Func : [%x]\n", 0);
    compare_outputs(original_ret, my_ret, "Hex Lower Sifir");
    
    printf(MAGENTA "Test 1B: " RESET "Kucuk Sayi (10)\n");
    original_ret = printf("Original: [%x]\n", 10);
    my_ret = ft_printf("My Func : [%x]\n", 10);
    compare_outputs(original_ret, my_ret, "Hex Lower (10)");
    
    printf(MAGENTA "Test 1C: " RESET "255 (ff)\n");
    original_ret = printf("Original: [%x]\n", 255);
    my_ret = ft_printf("My Func : [%x]\n", 255);
    compare_outputs(original_ret, my_ret, "Hex Lower (255)");
    
    printf(MAGENTA "Test 2: " RESET "Buyuk Sayi\n");
    original_ret = printf("Original: [%x]\n", 37359285);
    my_ret = ft_printf("My Func : [%x]\n", 37359285);
    compare_outputs(original_ret, my_ret, "Hex Lower Buyuk Sayi");
    
    printf(MAGENTA "Test 3: " RESET "Negatif Cast\n");
    original_ret = printf("Original: [%x]\n", (unsigned int)-1);
    my_ret = ft_printf("My Func : [%x]\n", (unsigned int)-1);
    compare_outputs(original_ret, my_ret, "Hex Lower Negatif Cast");
}

void test_hex_upper(void)
{
    int original_ret, my_ret;
    
    print_test_header("%%X - HEXADECIMAL UPPERCASE TESTLERI");
    
    printf(MAGENTA "Test 1A: " RESET "Sifir\n");
    original_ret = printf("Original: [%X]\n", 0);
    my_ret = ft_printf("My Func : [%X]\n", 0);
    compare_outputs(original_ret, my_ret, "Hex Upper Sifir");
    
    printf(MAGENTA "Test 1B: " RESET "Kucuk Sayi (10)\n");
    original_ret = printf("Original: [%X]\n", 10);
    my_ret = ft_printf("My Func : [%X]\n", 10);
    compare_outputs(original_ret, my_ret, "Hex Upper (10)");
    
    printf(MAGENTA "Test 1C: " RESET "255 (FF)\n");
    original_ret = printf("Original: [%X]\n", 255);
    my_ret = ft_printf("My Func : [%X]\n", 255);
    compare_outputs(original_ret, my_ret, "Hex Upper (255)");
    
    printf(MAGENTA "Test 2: " RESET "Buyuk Sayi\n");
    original_ret = printf("Original: [%X]\n", 37359285);
    my_ret = ft_printf("My Func : [%X]\n", 37359285);
    compare_outputs(original_ret, my_ret, "Hex Upper Buyuk Sayi");
    
    printf(MAGENTA "Test 3: " RESET "Negatif Cast\n");
    original_ret = printf("Original: [%X]\n", (unsigned int)-1);
    my_ret = ft_printf("My Func : [%X]\n", (unsigned int)-1);
    compare_outputs(original_ret, my_ret, "Hex Upper Negatif Cast");
}

void test_percent(void)
{
    int original_ret, my_ret;
    
    print_test_header("%%%% - YUZDE ISARETI TESTLERI");
    
    printf(MAGENTA "Test 1: " RESET "Tek Yuzde Isareti\n");
    original_ret = printf("Original: [%%]\n");
    my_ret = ft_printf("My Func : [%%]\n");
    compare_outputs(original_ret, my_ret, "Tek Yuzde Isareti");
    
    printf(MAGENTA "Test 2: " RESET "Coklu Yuzde Isareti\n");
    original_ret = printf("Original: [%%%%%%]\n");
    my_ret = ft_printf("My Func : [%%%%%%]\n");
    compare_outputs(original_ret, my_ret, "Coklu Yuzde Isareti");
    
    printf(MAGENTA "Test 3: " RESET "Yuzde Isareti Metinle\n");
    original_ret = printf("Original: 100%% basari orani!\n");
    my_ret = ft_printf("My Func : 100%% basari orani!\n");
    compare_outputs(original_ret, my_ret, "Yuzde Isareti Metinle");
}

void test_mixed(void)
{
    //int original_ret, my_ret;
    
    print_test_header("KARMA TESTLERI");
    
    // printf(MAGENTA "Test 1: " RESET "Coklu Format Specifier\n");
    // original_ret = printf("Original: Karakter: %c, String: %s, Sayi: %d\n", 'A', "test", 42);
    // my_ret = ft_printf("My Func : Karakter: %c, String: %s, Sayi: %d\n", 'A', "test", 42);
    // compare_outputs(original_ret, my_ret, "Coklu Format Specifier");
    
    // printf(MAGENTA "Test 2: " RESET "Tum Format Specifier'lar\n");
    // original_ret = printf("Original: %c|%s|%p|%d|%i|%u|%x|%X|%%\n", 'X', "hello", &original_ret, -42, 42, 42U, 255, 255);
    // my_ret = ft_printf("My Func : %c|%s|%p|%d|%i|%u|%x|%X|%%\n", 'X', "hello", &my_ret, -42, 42, 42U, 255, 255);
    // compare_outputs(original_ret, my_ret, "Tum Format Specifier'lar");
    
    // printf(MAGENTA "Test 3: " RESET "Kompleks Metin\n");
    // original_ret = printf("Original: Isim: %s, Yas: %d, Adres: %p, Maas: %u TL (%x hex)\n", "Ahmet", 25, &original_ret, 5000U, 5000);
    // my_ret = ft_printf("My Func : Isim: %s, Yas: %d, Adres: %p, Maas: %u TL (%x hex)\n", "Ahmet", 25, &my_ret, 5000U, 5000);
    // compare_outputs(original_ret, my_ret, "Kompleks Metin");
}

void test_edge_cases(void)
{
    int original_ret, my_ret;
    
    print_test_header("EDGE CASE TESTLERI");
    
    printf(MAGENTA "Test 1: " RESET "Sadece Metin (Format Yok)\n");
    original_ret = printf("Original: Bu sadece duz metindir.\n");
    my_ret = ft_printf("My Func : Bu sadece duz metindir.\n");
    compare_outputs(original_ret, my_ret, "Sadece Metin");
    
    printf(MAGENTA "Test 2: " RESET "Ardisik Format Specifier'lar\n");
    original_ret = printf("Original: %d%d%d%d\n", 1, 2, 3, 4);
    my_ret = ft_printf("My Func : %d%d%d%d\n", 1, 2, 3, 4);
    compare_outputs(original_ret, my_ret, "Ardisik Format Specifier'lar");
    
    printf(MAGENTA "Test 3: " RESET "Cok Sayida Arguman\n");
    original_ret = printf("Original: %d %d %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    my_ret = ft_printf("My Func : %d %d %d %d %d %d %d %d %d %d\n", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    compare_outputs(original_ret, my_ret, "Cok Sayida Arguman");
    
    printf(MAGENTA "Test 4: " RESET "Null Byte Karakteri\n");
    original_ret = printf("Original: Before null%cAfter null\n", '\0');
    my_ret = ft_printf("My Func : Before null%cAfter null\n", '\0');
    compare_outputs(original_ret, my_ret, "Null Byte Karakteri");
}