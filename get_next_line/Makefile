# Makefile for get_next_line

# --- Değişkenler ---
# Derleyici ve derleme bayrakları
# CC, C derleyicisini belirtir (genellikle gcc).
# CFLAGS, tüm C dosyaları için kullanılacak bayrakları içerir.
# -Wall -Wextra -Werror: Tüm uyarıları göster ve bunları hata olarak kabul et.
# -D BUFFER_SIZE=... : Buffer boyutunu ayarlar. Komut satırından değiştirilebilir.
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Silme komutu
RM = rm -f

# --- Zorunlu Kısım ---
# Programın adı
NAME = gnl_tester

# Zorunlu kısım için kaynak dosyaları
SRCS_MANDATORY = get_next_line.c \
                 get_next_line_utils.c \
                 main.c

# Kaynak dosyalarından obje dosyası isimlerini türet (.c -> .o)
OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)


# --- Bonus Kısım ---
# Bonus programın adı
NAME_BONUS = gnl_bonus_tester

# Bonus kısım için kaynak dosyaları
# DİKKAT: Bonus kısmı derlemek için 'main_bonus.c' adında bir dosyanız olmalı!
SRCS_BONUS = get_next_line_bonus.c \
             get_next_line_utils_bonus.c \
             main_bonus.c

# Bonus obje dosyaları
OBJS_BONUS = $(SRCS_BONUS:.c=.o)


# --- Kurallar ---

# 'make' veya 'make all' komutu varsayılan olarak zorunlu kısmı derler
all: $(NAME)

# Zorunlu kısım için ana programı oluşturur
# Bu kural, gerekli tüm .o dosyalarını birbirine bağlar.
$(NAME): $(OBJS_MANDATORY)
	$(CC) $(CFLAGS) $(OBJS_MANDATORY) -o $(NAME)
	@echo "Zorunlu kısım derlendi. Çalıştırmak için: ./$(NAME)"

# 'make bonus' komutu bonus kısmı derler
bonus: $(NAME_BONUS)

# Bonus kısım için ana programı oluşturur
# Bu kural, bonus için gerekli tüm .o dosyalarını birbirine bağlar.
$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
	@echo "Bonus kısım derlendi. Çalıştırmak için: ./$(NAME_BONUS)"

# Genel kural: Herhangi bir .c dosyasını bir .o dosyasına nasıl derleyeceğini belirtir
# $< : Kuralın bağımlılığı (kaynak .c dosyası)
# $@ : Kuralın hedefi (çıktı .o dosyası)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Sadece obje dosyalarını (.o) temizler
clean:
	$(RM) $(OBJS_MANDATORY) $(OBJS_BONUS)

# Tüm derlenmiş dosyaları (obje dosyaları ve programlar) temizler
fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

# Projeyi tamamen temizleyip zorunlu kısmı yeniden derler
re: fclean all

# .PHONY, bu hedeflerin bir dosya olmadığını, bir komut olduğunu belirtir.
# Bu, aynı isimde bir dosya olsa bile 'make clean' gibi komutların çalışmasını sağlar.
.PHONY: all bonus clean fclean re