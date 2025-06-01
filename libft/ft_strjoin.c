#include "libft.h" // ft_strlen ve malloc için gerekli başlıklar

// ft_strjoin fonksiyonu, s1 ve s2 string'lerini birleştirerek yeni bir string oluşturur.
// Yeni string için bellek dinamik olarak (malloc ile) ayrılır.
// Başarılı olursa yeni birleştirilmiş string'e bir pointer, hata durumunda NULL döndürür.
char *ft_strjoin(char const *s1, char const *s2)
{
    char *ptr;         // Oluşturulacak yeni birleşik string'i tutacak pointer.
    size_t total_size; // s1, s2 ve NUL sonlandırıcı için gereken toplam boyutu tutacak.
    size_t i;          // s1'i kopyalamak için döngü sayacı/indeksi.
    size_t j;          // s2'yi kopyalamak için döngü sayacı/indeksi.

    // 1. Girdi string'lerinin NULL olup olmadığını kontrol et.
    //    Eğer s1 veya s2 (ya da her ikisi) NULL ise, birleştirme yapılamaz, NULL döndür.
    if (!s1 || !s2) // s1 == NULL || s2 == NULL ile aynı
        return (NULL);

    // 2. Yeni string için gereken toplam bellek boyutunu hesapla.
    //    Bu, s1'in uzunluğu + s2'nin uzunluğu + 1 (NUL sonlandırıcı için) kadardır.
    total_size = ft_strlen(s1) + ft_strlen(s2) + 1;

    // 3. Hesaplanan toplam boyutta bellek ayır.
    ptr = malloc(total_size);

    // 4. Bellek ayırma işleminin başarılı olup olmadığını kontrol et.
    //    Eğer malloc NULL döndürürse (bellek ayrılamazsa), fonksiyon da NULL döndürür.
    if (!ptr) // ptr == NULL ile aynı
        return (NULL);

    // 5. İlk string'i (s1) yeni ayrılan bellek alanına (ptr) kopyala.
    i = -1; // Döngüde ++i kullanılacağı için -1 ile başla (ilk erişim i=0 olacak).
    while (s1[++i]) // s1[i] NUL karakteri olana kadar devam et.
        ptr[i] = s1[i]; // Karakteri ptr'ye kopyala.

    // 6. İkinci string'i (s2) yeni ayrılan bellek alanına, s1'in bittiği yerden itibaren kopyala.
    j = -1; // s2 için sayacı sıfırla (döngüde ++j kullanılacak).
    while(s2[++j]) // s2[j] NUL karakteri olana kadar devam et.
        ptr[i + j] = s2[j]; // Karakteri ptr'ye, s1'in sonundan itibaren ekle.

    // 7. Birleştirilmiş string'in sonuna NUL sonlandırıcıyı ekle.
    //    Bu, ptr'nin geçerli bir C string'i olmasını sağlar.
    ptr[i + j] = '\0';

    // 8. Yeni oluşturulan ve birleştirilmiş string'in başlangıç adresini döndür.
    //    Bu bellek `free()` ile serbest bırakılmalıdır.
    return (ptr);
}