#include "libft.h" // ft_strlen ve muhtemelen malloc'un olduğu başlık dosyanız

// ft_strdup fonksiyonu, kendisine verilen s1 string'inin bir kopyasını oluşturur.
// Yeni string için belleği dinamik olarak (malloc ile) ayırır.
// Başarılı olursa yeni string'e bir pointer, hata durumunda NULL döndürür.
char *ft_strdup(const char *s1)
{
    size_t str_len; // Kaynak string s1'in uzunluğunu saklamak için.
    size_t i;       // Karakterleri kopyalamak için döngü sayacı.
    char *ptr;      // Yeni ayrılan ve kopyalanan string'i tutacak pointer.

    // 1. Kaynak string'in (s1) NUL karakteri hariç uzunluğunu hesapla.
    str_len = ft_strlen(s1);

    // 2. Döngü sayacını, döngüde ilk değerin 0 olmasını sağlayacak şekilde -1'e ayarla.
    //    (while (++i ...) yapısı kullanılacak)
    i = -1; // veya i = 0; ve döngüde ptr[i] = s1[i]; i++; kullanılabilir.

    // 3. Kaynak string'in uzunluğu + 1 (NUL sonlandırıcı için) kadar bellek ayır.
    ptr = malloc(str_len + 1);

    // 4. Bellek ayırma işleminin başarılı olup olmadığını kontrol et.
    //    Eğer malloc NULL döndürürse (bellek ayrılamazsa), fonksiyon da NULL döndürür.
    if (ptr == NULL)
        return (NULL);

    // 5. Kaynak string'in karakterlerini yeni ayrılan bellek alanına kopyala.
    //    ++i sayesinde 'i' döngünün ilk adımında 0 olur ve str_len'e kadar gider.
    //    Bu döngü, NUL karakteri hariç tüm karakterleri kopyalar.
    while (++i < str_len)
        ptr[i] = s1[i]; // s1'deki i'inci karakteri ptr'deki i'inci pozisyona kopyala.

    // 6. Kopyalanan string'in sonuna NUL sonlandırıcıyı ekle.
    //    Döngü bittiğinde 'i' nin değeri str_len olur, bu da NUL karakterinin
    //    yerleştirileceği doğru indekstir.
    ptr[i] = '\0';

    // 7. Yeni oluşturulan ve kopyalanan string'in başlangıç adresini döndür.
    //    Bu bellek `free()` ile serbest bırakılmalıdır.
    return (ptr);
}