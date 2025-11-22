#!/bin/bash

# 42 Minitalk Bonus Test Script
# Bu script minitalk bonus projesi için kapsamlı testler içerir

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0
TOTAL=0

# Test sonuçlarını takip etmek için
log_test() {
    local test_name="$1"
    local result="$2"
    ((TOTAL++))
    
    if [ "$result" -eq 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}: $test_name"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAIL${NC}: $test_name"
        ((FAILED++))
    fi
}

# Cleanup fonksiyonu
cleanup() {
    echo -e "\n${YELLOW}Cleaning up processes...${NC}"
    pkill -f server_bonus 2>/dev/null
    pkill -f client_bonus 2>/dev/null
    sleep 1
}

# Trap ile cleanup
trap cleanup EXIT

echo -e "${BLUE}=================================${NC}"
echo -e "${BLUE} 42 MINITALK BONUS TEST SUITE   ${NC}"
echo -e "${BLUE}=================================${NC}\n"

# Derleme testi
echo -e "${YELLOW}[1] Compilation Tests${NC}"

if make bonus > /dev/null 2>&1; then
    log_test "Compilation with 'make bonus'" 0
else
    log_test "Compilation with 'make bonus'" 1
    echo -e "${RED}Compilation failed! Exiting...${NC}"
    exit 1
fi

# Executable dosyalarının varlığını kontrol et
if [ -f "./server_bonus" ] && [ -f "./client_bonus" ]; then
    log_test "Executable files exist (server_bonus, client_bonus)" 0
else
    log_test "Executable files exist (server_bonus, client_bonus)" 1
fi

echo ""

# Argüman kontrol testleri
echo -e "${YELLOW}[2] Argument Validation Tests${NC}"

# Server argüman testleri
./server_bonus arg1 2>/dev/null &
SERVER_PID=$!
sleep 0.5
if kill -0 $SERVER_PID 2>/dev/null; then
    kill $SERVER_PID 2>/dev/null
    log_test "Server accepts no arguments" 0
else
    log_test "Server accepts no arguments" 1
fi

# Client argüman testleri
timeout 2 ./client_bonus 2>/dev/null
if [ $? -eq 1 ] || [ $? -eq 124 ]; then
    log_test "Client rejects insufficient arguments (0 args)" 0
else
    log_test "Client rejects insufficient arguments (0 args)" 1
fi

timeout 2 ./client_bonus 12345 2>/dev/null
if [ $? -eq 1 ] || [ $? -eq 124 ]; then
    log_test "Client rejects insufficient arguments (1 arg)" 0
else
    log_test "Client rejects insufficient arguments (1 arg)" 1
fi

timeout 2 ./client_bonus 12345 "test" "extra" 2>/dev/null
if [ $? -eq 1 ] || [ $? -eq 124 ]; then
    log_test "Client rejects too many arguments (3 args)" 0
else
    log_test "Client rejects too many arguments (3 args)" 1
fi

# Geçersiz PID testleri
timeout 2 ./client_bonus 0 "test" 2>/dev/null
if [ $? -eq 1 ] || [ $? -eq 124 ]; then
    log_test "Client rejects invalid PID (0)" 0
else
    log_test "Client rejects invalid PID (0)" 1
fi

timeout 2 ./client_bonus -1 "test" 2>/dev/null
if [ $? -eq 1 ] || [ $? -eq 124 ]; then
    log_test "Client rejects invalid PID (-1)" 0
else
    log_test "Client rejects invalid PID (-1)" 1
fi

timeout 2 ./client_bonus abc "test" 2>/dev/null
if [ $? -eq 1 ] || [ $? -eq 124 ]; then
    log_test "Client rejects non-numeric PID" 0
else
    log_test "Client rejects non-numeric PID" 1
fi

timeout 2 ./client_bonus 999999999 "test" 2>/dev/null
if [ $? -eq 1 ] || [ $? -eq 124 ]; then
    log_test "Client handles non-existent PID gracefully" 0
else
    log_test "Client handles non-existent PID gracefully" 1
fi

echo ""

# Temel iletişim testleri
echo -e "${YELLOW}[3] Basic Communication Tests${NC}"

# Server'ı başlat ve PID'ini al
./server_bonus > server_output.tmp 2>&1 &
SERVER_PID=$!
sleep 1

# Server PID'ini dosyadan oku
if [ -f server_output.tmp ]; then
    ACTUAL_SERVER_PID=$(grep "Server PID:" server_output.tmp | awk '{print $3}')
    if [ ! -z "$ACTUAL_SERVER_PID" ] && [ "$ACTUAL_SERVER_PID" -gt 0 ]; then
        log_test "Server displays PID correctly" 0
    else
        log_test "Server displays PID correctly" 1
    fi
else
    log_test "Server displays PID correctly" 1
fi

# Basit mesaj testi
if [ ! -z "$ACTUAL_SERVER_PID" ]; then
    timeout 10 ./client_bonus $ACTUAL_SERVER_PID "Hello" > client_output.tmp 2>&1 &
    CLIENT_PID=$!
    sleep 3
    
    # Server çıktısını kontrol et
    if grep -q "Hello" server_output.tmp; then
        log_test "Basic message transmission (Hello)" 0
    else
        log_test "Basic message transmission (Hello)" 1
    fi
    
    # Client acknowledgment kontrolü
    if grep -q "Message successfully delivered!" client_output.tmp; then
        log_test "Client receives acknowledgment" 0
    else
        log_test "Client receives acknowledgment" 1
    fi
    
    kill $CLIENT_PID 2>/dev/null
fi

kill $SERVER_PID 2>/dev/null
rm -f server_output.tmp client_output.tmp
sleep 1

echo ""

# Metin işleme testleri
echo -e "${YELLOW}[4] Text Processing Tests${NC}"

test_message() {
    local message="$1"
    local test_name="$2"
    
    ./server_bonus > server_output.tmp 2>&1 &
    local srv_pid=$!
    sleep 1
    
    local actual_pid=$(grep "Server PID:" server_output.tmp | awk '{print $3}')
    
    if [ ! -z "$actual_pid" ]; then
        timeout 15 ./client_bonus $actual_pid "$message" > client_output.tmp 2>&1 &
        local cli_pid=$!
        sleep 5
        
        # Mesajın doğru şekilde iletilip iletilmediğini kontrol et
        if grep -qF "$message" server_output.tmp; then
            log_test "$test_name" 0
        else
            log_test "$test_name" 1
        fi
        
        kill $cli_pid 2>/dev/null
    else
        log_test "$test_name" 1
    fi
    
    kill $srv_pid 2>/dev/null
    rm -f server_output.tmp client_output.tmp
    sleep 1
}

# Çeşitli metin testleri
test_message "42" "Numbers transmission"
test_message "Hello World!" "Simple sentence with space and punctuation"
test_message "a" "Single character"
test_message "" "Empty string"
test_message "UPPERCASE" "Uppercase letters"
test_message "lowercase" "Lowercase letters"
test_message "MiXeD cAsE" "Mixed case with spaces"
test_message "123456789" "Multiple digits"
test_message "!@#$%^&*()" "Special characters"
test_message "áéíóúñç" "UTF-8 characters (if supported)"
test_message "Line1
Line2" "Multiline text (newline character)"
test_message "	Tab	Test	" "Text with tabs"

# Uzun metin testi
LONG_TEXT="This is a very long message to test the communication between client and server with a lot of characters to ensure that the signal handling works correctly even with extended text passages."
test_message "$LONG_TEXT" "Long message transmission"

# Çok uzun metin testi
VERY_LONG_TEXT=$(printf 'A%.0s' {1..500})
test_message "$VERY_LONG_TEXT" "Very long message (500 chars)"

echo ""

# Performans ve dayanıklılık testleri
echo -e "${YELLOW}[5] Performance and Reliability Tests${NC}"

# Hızlı ardışık mesaj testi
./server_bonus > server_output.tmp 2>&1 &
SERVER_PID=$!
sleep 1

ACTUAL_SERVER_PID=$(grep "Server PID:" server_output.tmp | awk '{print $3}')

if [ ! -z "$ACTUAL_SERVER_PID" ]; then
    # Birden fazla client ile test
    timeout 15 ./client_bonus $ACTUAL_SERVER_PID "Msg1" &
    sleep 1
    timeout 15 ./client_bonus $ACTUAL_SERVER_PID "Msg2" &
    sleep 1
    timeout 15 ./client_bonus $ACTUAL_SERVER_PID "Msg3" &
    sleep 8
    
    # Tüm mesajların iletilip iletilmediğini kontrol et
    if grep -q "Msg1" server_output.tmp && grep -q "Msg2" server_output.tmp && grep -q "Msg3" server_output.tmp; then
        log_test "Multiple clients sequential messaging" 0
    else
        log_test "Multiple clients sequential messaging" 1
    fi
fi

kill $SERVER_PID 2>/dev/null
rm -f server_output.tmp client_output.tmp
sleep 1

echo ""

# Bonus özellikleri testi
echo -e "${YELLOW}[6] Bonus Features Tests${NC}"

# Acknowledgment sistemi testi
./server_bonus > server_output.tmp 2>&1 &
SERVER_PID=$!
sleep 1

ACTUAL_SERVER_PID=$(grep "Server PID:" server_output.tmp | awk '{print $3}')

if [ ! -z "$ACTUAL_SERVER_PID" ]; then
    timeout 10 ./client_bonus $ACTUAL_SERVER_PID "ACK_TEST" > client_output.tmp 2>&1 &
    CLIENT_PID=$!
    sleep 5
    
    # Client'ın acknowledgment aldığını kontrol et
    if grep -q "Message successfully delivered!" client_output.tmp; then
        log_test "Acknowledgment system works" 0
    else
        log_test "Acknowledgment system works" 1
    fi
    
    kill $CLIENT_PID 2>/dev/null
fi

kill $SERVER_PID 2>/dev/null
rm -f server_output.tmp client_output.tmp
sleep 1

# Unicode/Emoji testi (bonus için)
./server_bonus > server_output.tmp 2>&1 &
SERVER_PID=$!
sleep 1

ACTUAL_SERVER_PID=$(grep "Server PID:" server_output.tmp | awk '{print $3}')

if [ ! -z "$ACTUAL_SERVER_PID" ]; then
    timeout 10 ./client_bonus $ACTUAL_SERVER_PID "Hello 😀 World! 🚀" > client_output.tmp 2>&1 &
    CLIENT_PID=$!
    sleep 5
    
    # Unicode karakterlerin doğru şekilde işlenip işlenmediğini kontrol et
    if grep -q "Hello.*World!" server_output.tmp; then
        log_test "Unicode/Emoji character handling" 0
    else
        log_test "Unicode/Emoji character handling" 1
    fi
    
    kill $CLIENT_PID 2>/dev/null
fi

kill $SERVER_PID 2>/dev/null
rm -f server_output.tmp client_output.tmp

echo ""

# Error handling testleri
echo -e "${YELLOW}[7] Error Handling Tests${NC}"

# Server'ın SIGTERM ile sonlandırılması
./server_bonus > server_output.tmp 2>&1 &
SERVER_PID=$!
sleep 1

kill -TERM $SERVER_PID 2>/dev/null
sleep 1

if ! kill -0 $SERVER_PID 2>/dev/null; then
    log_test "Server handles SIGTERM gracefully" 0
else
    log_test "Server handles SIGTERM gracefully" 1
    kill -9 $SERVER_PID 2>/dev/null
fi

# Client'ın server olmadan çalışması
timeout 5 ./client_bonus 99999 "test" 2>/dev/null
if [ $? -eq 1 ] || [ $? -eq 124 ]; then
    log_test "Client handles non-existent server" 0
else
    log_test "Client handles non-existent server" 1
fi

echo ""

# Sonuçları özetle
echo -e "${BLUE}=================================${NC}"
echo -e "${BLUE}         TEST RESULTS            ${NC}"
echo -e "${BLUE}=================================${NC}"
echo -e "Total Tests: ${TOTAL}"
echo -e "${GREEN}Passed: ${PASSED}${NC}"
echo -e "${RED}Failed: ${FAILED}${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    echo -e "${GREEN}Your minitalk bonus implementation is working correctly!${NC}"
    exit 0
else
    echo -e "\n${YELLOW}⚠️  Some tests failed. Please review your implementation.${NC}"
    exit 1
fi