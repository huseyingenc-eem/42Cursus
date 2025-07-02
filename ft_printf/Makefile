# # Projenin ana çıktısı olan kütüphanenin adı
# NAME = libftprintf.a

# # Derleyici ve derleme sırasında kullanılacak bayraklar (hataları gösterir)
# CC = cc
# CFLAGS = -Wall -Wextra -Werror

# # Arşivleme ve silme komutları için kısaltmalar
# AR = ar rcs
# RM = rm -f

# # --- Kaynak Dosyaları ---

# # Kendi projenizin (ft_printf) kaynak dosyalarını buraya listeleyin
# SRCS = ft_printf.c \
#        ft_printf_utils.c

# # Kaynak dosyası listesinden (.c) obje dosyası listesini (.o) otomatik oluştur
# OBJS = $(SRCS:.c=.o)

# # --- Libft Kütüphanesi Ayarları ---

# # libft kütüphanesinin bulunduğu dizin
# LIBFT_DIR = libft

# # libft kütüphanesinin tam yolu
# LIBFT = $(LIBFT_DIR)/libft.a

# #
# # --- Derleme Kuralları ---
# #

# # 'make' komutu çalıştırıldığında çalışacak ana kural.
# all: $(LIBFT) $(NAME)

# # Kendi kütüphanemizi (libftprintf.a) oluşturma kuralı
# $(NAME): $(OBJS)
# 	$(AR) $(NAME) $(OBJS)

# # libft kütüphanesini derleme kuralı.
# $(LIBFT):
# 	make -C $(LIBFT_DIR)

# # .c uzantılı kaynak dosyalarını .o uzantılı obje dosyalarına derleme kuralı
# %.o: %.c ft_printf.h
# 	$(CC) $(CFLAGS) -c $< -o $@

# # --- Temizlik Kuralları ---

# # Sadece obje dosyalarını temizler.
# clean:
# 	$(RM) $(OBJS)
# 	make clean -C $(LIBFT_DIR)

# # Obje dosyaları ve ana kütüphane dosyası dahil her şeyi temizler.
# fclean: clean
# 	$(RM) $(NAME)
# 	make fclean -C $(LIBFT_DIR)

# # Projeyi tamamen temizleyip baştan derler.
# re: fclean all

# # Bu hedeflerin birer dosya olmadığını, komut olduğunu belirtir.
# .PHONY: all clean fclean re






#######################################################################




# NAME = libftprintf.a
# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# AR = ar rcs
# RM = rm -f

# SRCS = ft_printf.c \
#        ft_printf_utils.c \

# OBJS = $(SRCS:.c=.o)


# LIBFT_DIR = libft
# LIBFT = $(LIBFT_DIR)/libft.a

# all: $(NAME)

# $(NAME): $(OBJS)
# 	# Sadece kendi obje dosyalarınızı kullanarak kütüphaneyi oluşturun.
# 	# libft.a'yı bunun içine kopyalamayın!
# 	$(AR) $(NAME) $(OBJS)

# libft:
# 	make -C $(LIBFT_DIR)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) $(OBJS)
# 	make clean -C $(LIBFT_DIR)

# fclean:
# 	$(RM) $(OBJS)
# 	$(RM) $(NAME)
# 	make fclean -C $(LIBFT_DIR)

# re: fclean all

# .PHONY: all clean fclean re libft


# Kütüphanenin adı
NAME = libftprintf.a

# Derleyici ve bayraklar
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Arşivleme ve silme komutları
AR = ar rcs
RM = rm -f

# --- Kaynak Dosyaları ---

# ft_printf'in kendi kaynak dosyaları
SRCS = ft_printf.c \
       ft_printf_utils.c

# Kaynak dosyalarından obje dosyası isimlerini otomatik türetme (.c -> .o)
OBJS = $(SRCS:.c=.o)

# --- Libft Ayarları ---

# libft kütüphanesinin bulunduğu dizin
LIBFT_DIR = libft
# libft kütüphane dosyasının tam yolu
LIBFT = $(LIBFT_DIR)/libft.a

# --- Test Dosyası Ayarları ---
TEST_SRC = main.c
TEST_NAME = test_printf

#
# --- Ana Kurallar ---
#

# 'make' komutu çalıştırıldığında ilk bu kural çalışır
# Önce libft'yi, sonra kendi kütüphanemizi derler
all: $(LIBFT) $(NAME)

# libftprintf.a kütüphanesini oluşturma kuralı
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Libft kütüphanesini derleme kuralı
$(LIBFT):
	make -C $(LIBFT_DIR)

# .c dosyalarını .o dosyalarına derlemek için genel kural
%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

# --- Test Kuralı ---
# 'make test' komutu ile çalışır
test: all
	@# Test dosyasını, hem kendi kütüphanemiz hem de libft ile birlikte derliyoruz
	$(CC) $(CFLAGS) $(TEST_SRC) $(NAME) $(LIBFT) -o $(TEST_NAME)
	@# Derlenen test programını çalıştırıyoruz
	./$(TEST_NAME)

# --- Temizlik Kuralları ---

clean:
	$(RM) $(OBJS)
	$(RM) $(TEST_NAME)
	make clean -C $(LIBFT_DIR)

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

# Bu kuralların dosya olmadığını belirtir
.PHONY: all clean fclean re test
