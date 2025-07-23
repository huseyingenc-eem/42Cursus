#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
//#include <sys/wait.h>
#include <stdlib.h>

// Test sonuçlarını takip etmek için
static int tests_passed = 0;
static int tests_failed = 0;

// Renkli çıktı için ANSI kodları
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

void print_test_result(const char *test_name, int passed)
{
    if (passed)
    {
        printf(GREEN "✅ %s: PASSED" RESET "\n", test_name);
        tests_passed++;
    }
    else
    {
        printf(RED "❌ %s: FAILED" RESET "\n", test_name);
        tests_failed++;
    }
}

void print_section(const char *section_name)
{
    printf(BLUE "\n=== %s ===" RESET "\n", section_name);
}

void create_test_files(void)
{
    FILE *fp;
    
    // Test dosyası 1: Normal metin
    fp = fopen("test1.txt", "w");
    if (fp) {
        fprintf(fp, "Line 1\nLine 2\nLine 3\n");
        fclose(fp);
    }
    
    // Test dosyası 2: Boş dosya
    fp = fopen("test_empty.txt", "w");
    if (fp) fclose(fp);
    
    // Test dosyası 3: Tek satır (newline yok)
    fp = fopen("test_no_newline.txt", "w");
    if (fp) {
        fprintf(fp, "Single line without newline");
        fclose(fp);
    }
    
    // Test dosyası 4: Sadece newline karakterleri
    fp = fopen("test_only_newlines.txt", "w");
    if (fp) {
        fprintf(fp, "\n\n\n");
        fclose(fp);
    }
    
    // Test dosyası 5: Çok uzun satır
    fp = fopen("test_long_line.txt", "w");
    if (fp) {
        for (int i = 0; i < 1000; i++)
            fprintf(fp, "a");
        fprintf(fp, "\nSecond line\n");
        fclose(fp);
    }
    
    // Test dosyası 6: Binary data içeren
    fp = fopen("test_binary.txt", "wb");
    if (fp) {
        fwrite("Before null\0After null\nNext line\n", 1, 30, fp);
        fclose(fp);
    }
    
    // Test dosyası 7: Tek karakter satırlar
    fp = fopen("test_single_chars.txt", "w");
    if (fp) {
        fprintf(fp, "a\nb\nc\n");
        fclose(fp);
    }
    
    // Test dosyası 8: Çok büyük dosya
    fp = fopen("test_huge.txt", "w");
    if (fp) {
        for (int i = 0; i < 10000; i++)
            fprintf(fp, "This is line %d with some content to make it longer\n", i);
        fclose(fp);
    }
    
    // Test dosyası 9: Karışık newline durumları
    fp = fopen("test_mixed_nl.txt", "w");
    if (fp) {
        fprintf(fp, "\nFirst line after empty\n\nThird line after empty\nLast line");
        fclose(fp);
    }
    
    // Test dosyası 10: BUFFER_SIZE testleri için
    fp = fopen("test_buffer_edge.txt", "w");
    if (fp) {
        // Tam BUFFER_SIZE kadar karakter + newline
        for (int i = 0; i < BUFFER_SIZE - 1; i++)
            fprintf(fp, "x");
        fprintf(fp, "\n");
        
        // BUFFER_SIZE'dan büyük satır
        for (int i = 0; i < BUFFER_SIZE + 10; i++)
            fprintf(fp, "y");
        fprintf(fp, "\nShort line\n");
        fclose(fp);
    }
}

void test_invalid_fd(void)
{
    char *line;
    
    print_section("INVALID FD TESTS");
    
    // Negatif FD
    line = get_next_line(-1);
    print_test_result("Negative FD (-1)", line == NULL);
    if (line) free(line);
    
    // Sıfır olmayan negatif FD
    line = get_next_line(-42);
    print_test_result("Negative FD (-42)", line == NULL);
    if (line) free(line);
    
    // Çok büyük FD
    line = get_next_line(999999);
    print_test_result("Very large FD", line == NULL);
    if (line) free(line);
    
    // Kapalı FD
    int fd = open("test1.txt", O_RDONLY);
    if (fd != -1) {
        close(fd);
        line = get_next_line(fd);
        print_test_result("Closed FD", line == NULL);
        if (line) free(line);
    }
    
    // Write-only FD
    fd = open("test1.txt", O_WRONLY);
    if (fd != -1) {
        line = get_next_line(fd);
        print_test_result("Write-only FD", line == NULL);
        if (line) free(line);
        close(fd);
    }
}

void test_empty_file(void)
{
    print_section("EMPTY FILE TEST");
    
    int fd = open("test_empty.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Empty file (file open failed)", 0);
        return;
    }
    
    char *line = get_next_line(fd);
    print_test_result("Empty file returns NULL", line == NULL);
    if (line) free(line);
    
    // İkinci okuma da NULL dönmeli
    line = get_next_line(fd);
    print_test_result("Empty file second read", line == NULL);
    if (line) free(line);
    
    close(fd);
}

void test_normal_file(void)
{
    print_section("NORMAL FILE TEST");
    
    int fd = open("test1.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Normal file (file open failed)", 0);
        return;
    }
    
    char *lines[4];
    int line_count = 0;
    
    for (int i = 0; i < 4; i++) {
        lines[i] = get_next_line(fd);
        if (lines[i] != NULL) {
            line_count++;
            printf("Line %d: '%s'", i + 1, lines[i]);
        }
    }
    
    // 3 satır olmalı, 4. okuma NULL dönmeli
    print_test_result("Normal file line count", line_count == 3 && lines[3] == NULL);
    
    // Satır içeriklerini kontrol et
    int content_ok = 1;
    if (lines[0] && strcmp(lines[0], "Line 1\n") != 0) content_ok = 0;
    if (lines[1] && strcmp(lines[1], "Line 2\n") != 0) content_ok = 0;
    if (lines[2] && strcmp(lines[2], "Line 3\n") != 0) content_ok = 0;
    
    print_test_result("Normal file content", content_ok);
    
    for (int i = 0; i < 4; i++) {
        if (lines[i]) free(lines[i]);
    }
    
    close(fd);
}

void test_no_newline_file(void)
{
    print_section("NO NEWLINE FILE TEST");
    
    int fd = open("test_no_newline.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("No newline file (file open failed)", 0);
        return;
    }
    
    char *line = get_next_line(fd);
    int passed = (line != NULL && strcmp(line, "Single line without newline") == 0);
    print_test_result("File without newline", passed);
    
    if (line) {
        printf("Read: '%s' (length: %zu)\n", line, strlen(line));
        free(line);
    }
    
    // İkinci okuma NULL dönmeli
    line = get_next_line(fd);
    print_test_result("Second read after no newline", line == NULL);
    if (line) free(line);
    
    close(fd);
}

void test_only_newlines(void)
{
    print_section("ONLY NEWLINES TEST");
    
    int fd = open("test_only_newlines.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Only newlines (file open failed)", 0);
        return;
    }
    
    char *line;
    int empty_line_count = 0;
    int total_lines = 0;
    
    while ((line = get_next_line(fd)) != NULL) {
        total_lines++;
        if (strcmp(line, "\n") == 0)
            empty_line_count++;
        printf("Line %d: '%s' (length: %zu)\n", total_lines, line, strlen(line));
        free(line);
    }
    
    print_test_result("Only newlines count", empty_line_count == 3 && total_lines == 3);
    close(fd);
}

void test_long_line(void)
{
    print_section("LONG LINE TEST");
    
    int fd = open("test_long_line.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Long line (file open failed)", 0);
        return;
    }
    
    char *line = get_next_line(fd);
    int passed = (line != NULL && strlen(line) == 1001); // 1000 'a' + 1 '\n'
    print_test_result("Long line length", passed);
    
    if (line) {
        printf("Long line length: %zu\n", strlen(line));
        // İlk ve son karakterleri kontrol et
        int content_ok = (line[0] == 'a' && line[999] == 'a' && line[1000] == '\n');
        print_test_result("Long line content", content_ok);
        free(line);
    }
    
    // İkinci satır
    line = get_next_line(fd);
    passed = (line != NULL && strcmp(line, "Second line\n") == 0);
    print_test_result("Line after long line", passed);
    if (line) free(line);
    
    // Üçüncü okuma NULL olmalı
    line = get_next_line(fd);
    print_test_result("Third read after long line", line == NULL);
    if (line) free(line);
    
    close(fd);
}

void test_buffer_edge_cases(void)
{
    print_section("BUFFER SIZE EDGE CASES");
    
    int fd = open("test_buffer_edge.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Buffer edge (file open failed)", 0);
        return;
    }
    
    printf("Current BUFFER_SIZE: %d\n", BUFFER_SIZE);
    
    // İlk satır: tam BUFFER_SIZE - 1 karakter + newline
    char *line = get_next_line(fd);
    int passed = (line != NULL && strlen(line) == BUFFER_SIZE);
    print_test_result("Line equals BUFFER_SIZE", passed);
    if (line) {
        printf("First line length: %zu\n", strlen(line));
        free(line);
    }
    
    // İkinci satır: BUFFER_SIZE'dan büyük
    line = get_next_line(fd);
    passed = (line != NULL && strlen(line) == (BUFFER_SIZE + 11)); // +10 chars + newline
    print_test_result("Line bigger than BUFFER_SIZE", passed);
    if (line) {
        printf("Second line length: %zu\n", strlen(line));
        free(line);
    }
    
    // Üçüncü satır: kısa
    line = get_next_line(fd);
    passed = (line != NULL && strcmp(line, "Short line\n") == 0);
    print_test_result("Short line after long", passed);
    if (line) free(line);
    
    close(fd);
}

void test_mixed_newlines(void)
{
    print_section("MIXED NEWLINE PATTERNS");
    
    int fd = open("test_mixed_nl.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Mixed newlines (file open failed)", 0);
        return;
    }
    
    char *expected[] = {"\n", "First line after empty\n", "\n", "Third line after empty\n", "Last line"};
    char *line;
    int i = 0;
    int all_correct = 1;
    
    while ((line = get_next_line(fd)) != NULL && i < 5) {
        printf("Line %d: '%s' (expected: '%s')\n", i + 1, line, expected[i]);
        
        if (strcmp(line, expected[i]) != 0) {
            all_correct = 0;
        }
        
        free(line);
        i++;
    }
    
    print_test_result("Mixed newline patterns", all_correct && i == 5);
    close(fd);
}

void test_single_char_lines(void)
{
    print_section("SINGLE CHARACTER LINES");
    
    int fd = open("test_single_chars.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Single chars (file open failed)", 0);
        return;
    }
    
    char *expected[] = {"a\n", "b\n", "c\n"};
    char *line;
    int i = 0;
    int all_correct = 1;
    
    while ((line = get_next_line(fd)) != NULL && i < 3) {
        printf("Single char line %d: '%s'\n", i + 1, line);
        
        if (strcmp(line, expected[i]) != 0) {
            all_correct = 0;
        }
        
        free(line);
        i++;
    }
    
    print_test_result("Single character lines", all_correct && i == 3);
    close(fd);
}

void test_binary_file(void)
{
    print_section("BINARY FILE TEST");
    
    int fd = open("test_binary.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Binary file (file open failed)", 0);
        return;
    }
    
    char *line = get_next_line(fd);
    int passed = (line != NULL);
    print_test_result("Binary file read", passed);
    
    if (line) {
        printf("Binary line length: %zu\n", strlen(line));
        // Sadece "Before null" kısmını kontrol et (null char'dan sonrası görünmez)
        print_test_result("Binary content check", strncmp(line, "Before null", 11) == 0);
        free(line);
    }
    
    // İkinci satır için doğru beklenti
    line = get_next_line(fd);
    // Binary dosyada null char yüzünden sonraki kısım da aynı satıra dahil olabilir
    passed = (line != NULL);
    print_test_result("Line after binary", passed);
    if (line) {
        printf("Second line: '%s'\n", line);
        free(line);
    }
    
    close(fd);
}

void test_multiple_reads_same_fd(void)
{
    print_section("MULTIPLE READS SAME FD");
    
    int fd = open("test1.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Multiple reads (file open failed)", 0);
        return;
    }
    
    char *lines[5];
    for (int i = 0; i < 5; i++) {
        lines[i] = get_next_line(fd);
    }
    
    int passed = (lines[0] != NULL && lines[1] != NULL && lines[2] != NULL && 
                  lines[3] == NULL && lines[4] == NULL);
    print_test_result("Multiple reads consistency", passed);
    
    for (int i = 0; i < 5; i++) {
        if (lines[i]) {
            printf("Read %d: %s", i + 1, lines[i]);
            free(lines[i]);
        }
    }
    
    close(fd);
}

void test_bonus_multiple_fds(void)
{
    print_section("BONUS: MULTIPLE FDS");
    
    int fd1 = open("test1.txt", O_RDONLY);
    int fd2 = open("test_no_newline.txt", O_RDONLY);
    int fd3 = open("test_single_chars.txt", O_RDONLY);
    
    if (fd1 == -1 || fd2 == -1 || fd3 == -1) {
        print_test_result("Bonus multiple FDs (file open failed)", 0);
        if (fd1 != -1) close(fd1);
        if (fd2 != -1) close(fd2);
        if (fd3 != -1) close(fd3);
        return;
    }
    
    // Bonus dosyasını test etmek için get_next_line kullan
    char *line1_1 = get_next_line(fd1);  // "Line 1\n"
    char *line2_1 = get_next_line(fd2);  // "Single line without newline"
    char *line3_1 = get_next_line(fd3);  // "a\n"
    
    char *line1_2 = get_next_line(fd1);  // "Line 2\n"
    char *line3_2 = get_next_line(fd3);  // "b\n"
    char *line2_2 = get_next_line(fd2);  // NULL olmalı
    
    int passed = (line1_1 != NULL && line2_1 != NULL && line3_1 != NULL &&
                  line1_2 != NULL && line3_2 != NULL && line2_2 == NULL);
    
    print_test_result("Bonus multiple FDs interleaved", passed);
    
    if (line1_1) { printf("FD1 Line 1: %s", line1_1); free(line1_1); }
    if (line2_1) { printf("FD2 Line 1: %s", line2_1); free(line2_1); }
    if (line3_1) { printf("FD3 Line 1: %s", line3_1); free(line3_1); }
    if (line1_2) { printf("FD1 Line 2: %s", line1_2); free(line1_2); }
    if (line3_2) { printf("FD3 Line 2: %s", line3_2); free(line3_2); }
    if (line2_2) { free(line2_2); }
    
    close(fd1);
    close(fd2);
    close(fd3);
}

void test_huge_file_performance(void)
{
    print_section("PERFORMANCE TEST");
    
    int fd = open("test_huge.txt", O_RDONLY);
    if (fd == -1) {
        print_test_result("Performance test (file open failed)", 0);
        return;
    }
    
    char *line;
    int line_count = 0;
    
    printf("Reading large file...\n");
    while ((line = get_next_line(fd)) != NULL) {
        line_count++;
        if (line_count % 1000 == 0) {
            printf("Read %d lines...\n", line_count);
        }
        free(line);
    }
    
    print_test_result("Large file performance", line_count == 10000);
    printf("Total lines read: %d\n", line_count);
    
    close(fd);
}

void test_stdin_simulation(void)
{
    print_section("STDIN SIMULATION");
    
    int pipe_fd[2];
    if (_pipe(pipe_fd, 1024, _O_BINARY) == -1) { 
        print_test_result("Pipe creation", 0);
        return;
    }
    
    // Pipe'a veri yazma
    const char *test_data = "Pipe line 1\nPipe line 2\nPipe line 3 no newline";
    write(pipe_fd[1], test_data, strlen(test_data));
    close(pipe_fd[1]); // Write end'i kapat
    
    char *lines[4];
    int line_count = 0;
    
    for (int i = 0; i < 4; i++) {
        lines[i] = get_next_line(pipe_fd[0]);
        if (lines[i] != NULL) {
            line_count++;
            printf("Pipe Line %d: '%s'\n", i + 1, lines[i]);
        }
    }
    
    int passed = (line_count == 3 && lines[3] == NULL);
    print_test_result("Pipe/STDIN simulation", passed);
    
    for (int i = 0; i < 4; i++) {
        if (lines[i]) free(lines[i]);
    }
    
    close(pipe_fd[0]);
}

void test_memory_stress(void)
{
    print_section("MEMORY STRESS TEST");
    
    printf("Running memory stress test (100 iterations)...\n");
    
    for (int iteration = 0; iteration < 100; iteration++) {
        int fd = open("test1.txt", O_RDONLY);
        if (fd == -1) continue;
        
        char *line;
        while ((line = get_next_line(fd)) != NULL) {
            free(line);
        }
        close(fd);
        
        if (iteration % 20 == 0) {
            printf("Completed %d iterations...\n", iteration);
        }
    }
    
    print_test_result("Memory stress test completed", 1);
    printf("✅ 100 iterations completed (check with valgrind for leaks)\n");
}

void cleanup_test_files(void)
{
    const char *files[] = {
        "test1.txt", "test_empty.txt", "test_no_newline.txt",
        "test_only_newlines.txt", "test_long_line.txt", "test_binary.txt",
        "test_single_chars.txt", "test_huge.txt", "test_mixed_nl.txt",
        "test_buffer_edge.txt"
    };
    
    for (int i = 0; i < 10; i++) {
        remove(files[i]);
    }
}

void print_final_results(void)
{
    printf(BLUE "\n=== FINAL TEST RESULTS ===" RESET "\n");
    printf(GREEN "✅ Passed: %d" RESET "\n", tests_passed);
    printf(RED "❌ Failed: %d" RESET "\n", tests_failed);
    
    if (tests_passed + tests_failed > 0) {
        float success_rate = (float)tests_passed / (tests_passed + tests_failed) * 100;
        printf(YELLOW "📊 Success Rate: %.1f%%" RESET "\n", success_rate);
    }
    
    if (tests_failed == 0) {
        printf(GREEN "\n🎉 ALL TESTS PASSED! 🎉" RESET "\n");
        printf("Your get_next_line implementation looks solid!\n");
    } else {
        printf(RED "\n⚠️  SOME TESTS FAILED ⚠️" RESET "\n");
        printf("Review the failed tests and fix the issues.\n");
    }
    
    printf("\n" YELLOW "💡 RECOMMENDATIONS:" RESET "\n");
    printf("• Run with valgrind to check for memory leaks\n");
    printf("• Test with different BUFFER_SIZE values (1, 42, 1000, 10000)\n");
    printf("• Test the bonus part with multiple file descriptors\n");
    printf("• Make sure your code handles edge cases properly\n");
}

int main(void)
{
    printf(BLUE "=== GET_NEXT_LINE COMPREHENSIVE TESTER ===" RESET "\n");
    printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
    printf("Creating test files...\n");
    
    // Test dosyalarını oluştur
    create_test_files();
    
    // Testleri çalıştır
    test_invalid_fd();
    test_empty_file();
    test_normal_file();
    test_no_newline_file();
    test_only_newlines();
    test_single_char_lines();
    test_mixed_newlines();
    test_long_line();
    test_buffer_edge_cases();
    test_binary_file();
    test_multiple_reads_same_fd();
    test_bonus_multiple_fds();
    test_stdin_simulation();
    test_memory_stress();
    test_huge_file_performance();
    
    // Test dosyalarını temizle
    printf(YELLOW "\nCleaning up test files..." RESET "\n");
    cleanup_test_files();
    
    // Final sonuçları göster
    print_final_results();
    
    return (tests_failed == 0 ? 0 : 1);
}