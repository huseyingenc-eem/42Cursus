# 🌟 Libft — Kişisel C Kütüphanem

<div align="center">
  
  ![Libft Banner](https://img.shields.io/badge/42-Libft-00babc?style=for-the-badge&logo=42)
  
  [![Norm](https://img.shields.io/badge/Norm-v3-brightgreen?style=flat-square)](https://github.com/42School/norminette)
  [![Status](https://img.shields.io/badge/Status-125%25_Completed-success?style=flat-square&logo=checkmarx)](.)
  [![Grade](https://img.shields.io/badge/Grade-125%2F100-brightgreen?style=flat-square&logo=42)](.)
  [![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](.)
  
  *42 Cursus'un temel taşı — Sıfırdan inşa edilmiş, güçlü bir C kütüphanesi*
  
  [Kurulum](#-kurulum) • [Kullanım](#-kullanım) • [API Dokümantasyonu](#-api-dokümantasyonu) • [Test](#-test)

</div>

---

## 📖 Proje Hakkında

**Libft**, 42 Okulu'nun ilk ve en önemli projesidir. Bu projede, C dilinin standart kütüphane fonksiyonlarını sıfırdan yeniden yazarak dilin derinliklerine inerken, gelecek projelerde kullanacağınız **güçlü bir araç seti** oluşturursunuz.

### 🎯 Neden Libft?

- **🧠 Bellek Yönetiminde Ustalaşın** — `malloc`, `free` ve bellek sızıntıları konusunda tam kontrol  
- **🔗 İşaretçi Sihirbazı Olun** — Adres aritmetiği, pointer manipülasyonu, güvenli bellek erişimi  
- **📚 Kendi Kütüphanenizi İnşa Edin** — Sonraki tüm projelerde kullanacağınız `libft.a`  
- **🛡️ Güvenli Kod Yazın** — Buffer overflow, segfault ve tanımsız davranışlardan kaçının  
- **⚡ Performans Odaklı** — Optimize edilmiş algoritmalar ve verimli implementasyonlar  

---

## ✨ Özellikler

<table>
<tr>
<td width="50%">

### 🔤 String İşlemleri
- Güvenli kopyalama & birleştirme  
- Akıllı arama algoritmaları  
- Dinamik bellek yönetimi  
- Unicode desteği hazır altyapı  

</td>
<td width="50%">

### 🧮 Bellek Yönetimi
- Sıfır-sızıntı garantisi  
- Örtüşen bellek blokları desteği  
- Optimize kopyalama/taşıma  
- Güvenli tahsis ve serbest bırakma  

</td>
</tr>
<tr>
<td width="50%">

### 🔗 Bağlı Liste Yapıları
- Generic `void*` içerik desteği  
- Baştan/sondan ekleme  
- Map & iterate fonksiyonları  
- Bellek güvenli temizleme  

</td>
<td width="50%">

### 🛠️ Yardımcı Araçlar
- Tip dönüşümleri (`atoi`, `itoa`)  
- File descriptor I/O  
- String bölme & birleştirme  
- Karakter kontrol fonksiyonları  

</td>
</tr>
</table>

---

## 📁 Proje Yapısı
```

libft/
├── inc/
│   └── libft.h              # Ana header dosyası
├── src/
│   ├── ctype/               # Karakter kontrolleri (isalpha, isdigit, ...)
│   ├── mem/                 # Bellek fonksiyonları (memset, memcpy, ...)
│   ├── str/                 # String işlemleri (strlen, strdup, ...)
│   ├── extra/               # Ekstra fonksiyonlar (split, substr, ...)
│   └── bonus/               # Bağlı liste yapıları (t_list)
├── Makefile                 # Otomatik derleme sistemi
└── README.md                # Bu dosya

````

---

## 🚀 Kurulum

### Gereksinimler
- GCC veya Clang derleyici  
- Make build tool  
- UNIX/Linux/MacOS ortamı  

### Hızlı Başlangıç
```bash
# Repository'yi klonlayın
git clone https://github.com/yourusername/libft.git
cd libft

# Kütüphaneyi derleyin
make

# Bonus fonksiyonlarını ekleyin
make bonus

# Test edin!
make test
````

### Derleme Komutları

| Komut                  | Açıklama                       |
| ---------------------- | ------------------------------ |
| `make` veya `make all` | Kütüphaneyi derler (`libft.a`) |
| `make bonus`           | Bonus fonksiyonlarını ekler    |
| `make clean`           | Object dosyalarını siler       |
| `make fclean`          | Tüm derleme çıktılarını siler  |
| `make re`              | Baştan derler (clean + all)    |

---

## 💻 Kullanım

### Projenize Dahil Etme

```bash
gcc -Wall -Wextra -Werror your_file.c -L. -lft -I inc -o your_program
```

### Örnek Kod

```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    char *str = ft_strdup("Hello, 42!");
    printf("String: %s (len: %zu)\n", str, ft_strlen(str));
    
    char **words = ft_split("one,two,three", ',');
    for (int i = 0; words[i]; i++)
        printf("Word[%d]: %s\n", i, words[i]);
    
    free(str);
    for (int i = 0; words[i]; i++)
        free(words[i]);
    free(words);
    
    return 0;
}
```

---

## 📚 API Dokümantasyonu

### 🔤 Karakter İşlemleri (ctype)

<details>
<summary><b>Karakter Kontrol Fonksiyonları</b> (tıklayın)</summary>

| Fonksiyon    | Prototype               | Açıklama                         |
| ------------ | ----------------------- | -------------------------------- |
| `ft_isalpha` | `int ft_isalpha(int c)` | Alfabetik karakter kontrolü      |
| `ft_isdigit` | `int ft_isdigit(int c)` | Rakam kontrolü (0–9)             |
| `ft_isalnum` | `int ft_isalnum(int c)` | Alfanümerik kontrolü             |
| `ft_isascii` | `int ft_isascii(int c)` | ASCII aralığı kontrolü (0–127)   |
| `ft_isprint` | `int ft_isprint(int c)` | Yazdırılabilir karakter kontrolü |
| `ft_toupper` | `int ft_toupper(int c)` | Küçük → büyük harf               |
| `ft_tolower` | `int ft_tolower(int c)` | Büyük → küçük harf               |

</details>

---

### 🧮 Bellek İşlemleri (mem)

<details>
<summary><b>Bellek Yönetim Fonksiyonları</b> (tıklayın)</summary>

| Fonksiyon    | Prototype                                                 | Açıklama                        |
| ------------ | --------------------------------------------------------- | ------------------------------- |
| `ft_memset`  | `void *ft_memset(void *s, int c, size_t n)`               | Belleği sabit byte ile doldurur |
| `ft_bzero`   | `void ft_bzero(void *s, size_t n)`                        | Belleği sıfırlar                |
| `ft_memcpy`  | `void *ft_memcpy(void *dest, const void *src, size_t n)`  | Belleği kopyalar                |
| `ft_memmove` | `void *ft_memmove(void *dest, const void *src, size_t n)` | Güvenli taşıma                  |
| `ft_memchr`  | `void *ft_memchr(const void *s, int c, size_t n)`         | Byte arama                      |
| `ft_memcmp`  | `int ft_memcmp(const void *s1, const void *s2, size_t n)` | Karşılaştırma                   |
| `ft_calloc`  | `void *ft_calloc(size_t nmemb, size_t size)`              | Sıfırlanmış bellek tahsisi      |

</details>

---

### 📝 String İşlemleri (str)

<details>
<summary><b>Temel String Fonksiyonları</b> (tıklayın)</summary>

| Fonksiyon    | Prototype                                                           | Açıklama            |
| ------------ | ------------------------------------------------------------------- | ------------------- |
| `ft_strlen`  | `size_t ft_strlen(const char *s)`                                   | String uzunluğu     |
| `ft_strlcpy` | `size_t ft_strlcpy(char *dst, const char *src, size_t size)`        | Güvenli kopyalama   |
| `ft_strlcat` | `size_t ft_strlcat(char *dst, const char *src, size_t size)`        | Güvenli birleştirme |
| `ft_strchr`  | `char *ft_strchr(const char *s, int c)`                             | İlk karakter arama  |
| `ft_strrchr` | `char *ft_strrchr(const char *s, int c)`                            | Son karakter arama  |
| `ft_strncmp` | `int ft_strncmp(const char *s1, const char *s2, size_t n)`          | Karşılaştırma       |
| `ft_strnstr` | `char *ft_strnstr(const char *big, const char *little, size_t len)` | Alt string arama    |
| `ft_strdup`  | `char *ft_strdup(const char *s)`                                    | String kopyası      |

</details>

---

### ⭐ Ekstra Fonksiyonlar

<details>
<summary><b>Gelişmiş String Fonksiyonları</b> (tıklayın)</summary>

| Fonksiyon     | Prototype                                                        | Açıklama                          |
| ------------- | ---------------------------------------------------------------- | --------------------------------- |
| `ft_substr`   | `char *ft_substr(char const *s, unsigned int start, size_t len)` | Alt string çıkarma                |
| `ft_strjoin`  | `char *ft_strjoin(char const *s1, char const *s2)`               | String birleştirme                |
| `ft_strtrim`  | `char *ft_strtrim(char const *s1, char const *set)`              | Kenar karakterleri temizle        |
| `ft_split`    | `char **ft_split(char const *s, char c)`                         | Ayırıcıya göre böl                |
| `ft_itoa`     | `char *ft_itoa(int n)`                                           | Sayıyı stringe çevir              |
| `ft_strmapi`  | `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))` | Fonksiyonla map et                |
| `ft_striteri` | `void ft_striteri(char *s, void (*f)(unsigned int, char*))`      | Karakterleri iterasyonla değiştir |

</details>

---

### 📤 File Descriptor Fonksiyonları

<details>
<summary><b>Dosya Çıkış Fonksiyonları</b> (tıklayın)</summary>

| Fonksiyon       | Prototype                             | Açıklama                |
| --------------- | ------------------------------------- | ----------------------- |
| `ft_putchar_fd` | `void ft_putchar_fd(char c, int fd)`  | Karakter yaz            |
| `ft_putstr_fd`  | `void ft_putstr_fd(char *s, int fd)`  | String yaz              |
| `ft_putendl_fd` | `void ft_putendl_fd(char *s, int fd)` | String + yeni satır yaz |
| `ft_putnbr_fd`  | `void ft_putnbr_fd(int n, int fd)`    | Sayı yaz                |

</details>

---

### 🔗 Bonus: Bağlı Liste (t_list)

<details>
<summary><b>Linked List Fonksiyonları</b> (tıklayın)</summary>

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

| Fonksiyon         | Prototype                                                                 | Açıklama                      |
| ----------------- | ------------------------------------------------------------------------- | ----------------------------- |
| `ft_lstnew`       | `t_list *ft_lstnew(void *content)`                                        | Yeni düğüm oluşturur          |
| `ft_lstadd_front` | `void ft_lstadd_front(t_list **lst, t_list *new)`                         | Başa düğüm ekler              |
| `ft_lstadd_back`  | `void ft_lstadd_back(t_list **lst, t_list *new)`                          | Sona düğüm ekler              |
| `ft_lstsize`      | `int ft_lstsize(t_list *lst)`                                             | Liste boyutunu döndürür       |
| `ft_lstlast`      | `t_list *ft_lstlast(t_list *lst)`                                         | Son düğümü döndürür           |
| `ft_lstdelone`    | `void ft_lstdelone(t_list *lst, void (*del)(void *))`                     | Düğümü siler                  |
| `ft_lstclear`     | `void ft_lstclear(t_list **lst, void (*del)(void *))`                     | Tüm listeyi temizler          |
| `ft_lstiter`      | `void ft_lstiter(t_list *lst, void (*f)(void *))`                         | Her elemana fonksiyon uygular |
| `ft_lstmap`       | `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` | Listeyi map eder              |

</details>

---

## 🧪 Test

### Manuel Test

```c
#include "libft.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    assert(ft_strlen("Hello") == strlen("Hello"));  
    char *dup = ft_strdup("Test");  
    assert(strcmp(dup, "Test") == 0);  
    free(dup);  

    assert(ft_atoi("42") == 42);
    assert(ft_atoi("-123") == -123);

    printf("✅ Tüm testler başarılı!\n");
    return 0;
}
```

### Test Araçları

* [**Libft Unit Test**](https://github.com/alelievr/libft-unit-test)
* [**Libftest**](https://github.com/jtoty/Libftest)
* [**War Machine**](https://github.com/y3ll0w42/libft-war-machine)
* **Valgrind** — Bellek sızıntısı kontrolü

```bash
valgrind --leak-check=full ./your_program
```

---

## 📊 Norm Uyumluluğu

```bash
norminette -R CheckForbiddenSourceHeader *.c *.h
```

✅ **Norm Kuralları**

* Her fonksiyon maksimum 25 satır
* Satır başına maksimum 80 karakter
* Fonksiyon başına en fazla 4 parametre
* Global değişken yok
* Header koruma (`#ifndef LIBFT_H`)
* Tutarlı isimlendirme (`ft_` prefix)

---

## 🎓 Öğrenilen Kavramlar

<table>
<tr>
<td width="50%">
💡 **Teknik Beceriler**
<ul>
<li>Bellek Yönetimi (`malloc`, `free`, heap/stack farkı)</li>
<li>İşaretçi Manipülasyonu</li>
<li>Veri Yapıları: linked list, array</li>
<li>Güvenli Kodlama: null check, buffer kontrol</li>
<li>Algoritma Tasarımı: arama, sıralama, işleme</li>
</ul>
</td>
<td width="50%">
🔧 **Geliştirme Araçları**
<ul>
<li>Makefile & Otomasyon</li>
<li>Debugging: GDB, Valgrind</li>
<li>API Dokümantasyonu</li>
<li>Unit Test Tasarımı</li>
<li>Performans Analizi</li>
</ul>
</td>
</tr>
</table>

---

## 🔍 Sık Karşılaşılan Hatalar

<details>
<summary><b>❌ Segmentation Fault (SIGSEGV)</b></summary>

```c
// YANLIŞ ❌
char *str = NULL;
ft_strlen(str);

// DOĞRU ✅
if (str != NULL)
    ft_strlen(str);
```

</details>

<details>
<summary><b>⚠️ Memory Leak</b></summary>

```c
// YANLIŞ ❌
char *str = ft_strdup("test");
return (0);

// DOĞRU ✅
char *str = ft_strdup("test");
free(str);
return (0);
```

</details>

<details>
<summary><b>🔄 Buffer Overflow</b></summary>

```c
// YANLIŞ ❌
char dest[5];
ft_strlcpy(dest, "Hello World", 5);

// DOĞRU ✅
char dest[12];
ft_strlcpy(dest, "Hello World", sizeof(dest));
```

</details>

---

## 📈 Performans İpuçları

⚡ **Optimizasyon Stratejileri**

```c
// Gereksiz fonksiyon çağrısından kaçının
for (int i = 0; i < ft_strlen(str); i++); // ❌ Yavaş

size_t len = ft_strlen(str);
for (int i = 0; i < len; i++); // ✅ Hızlı
```

```c
// Bellek tahsisini minimize edin
size_t total_len = ft_strlen(s1) + ft_strlen(s2);
char *result = malloc(total_len + 1);
```

```c
// Cache-friendly kod yazın
// Sequential bellek erişimi tercih edin
```

---

## 🤝 Katkıda Bulunma

1. 🍴 Fork yap
2. 🌿 Feature branch oluştur (`git checkout -b feature/amazing-feature`)
3. 💾 Commit at (`git commit -m 'feat: Add amazing feature'`)
4. 📤 Push yap (`git push origin feature/amazing-feature`)
5. 🔀 Pull Request aç

### Commit Konvansiyonları

| Tür         | Açıklama      |
| ----------- | ------------- |
| `feat:`     | Yeni özellik  |
| `fix:`      | Bug düzeltme  |
| `docs:`     | Dokümantasyon |
| `style:`    | Formatlama    |
| `refactor:` | Kod düzenleme |
| `test:`     | Test ekleme   |
| `chore:`    | Bakım işlemi  |

---

## 📜 Lisans

Bu proje **MIT Lisansı** altındadır. Detaylar için `LICENSE` dosyasına bakın.

---

## 🌟 Yıldızlamayı Unutmayın!

Bu proje size yardımcı olduysa ⭐ vermeyi unutmayın!

---

## 📞 İletişim

<div align="center">
👤 Your Name  
<a href="https://github.com/yourusername">GitHub</a> • <a href="mailto:you@example.com">E-posta</a>
</div>

---

## 🔖 Ek Kaynaklar

* 📘 *The C Programming Language* (K&R)
* 📗 Understanding Pointers in C
* 📕 Memory Management Guide
* 📙 42 Network Curriculum
* 🎥 C Programming Tutorials

<div align="center">
⚡ Happy Coding! ⚡
</div>
