#include "libft.h" // ft_strlen ve malloc için gerekli başlıklar

// ft_strmapi: 's' string'inin her bir karakterine 'f' fonksiyonunu uygulayarak
//             yeni bir string oluşturur. 'f' fonksiyonu, karakterin indeksini (i) ve
//             karakterin kendisini (s[i]) parametre olarak alır ve bu karakterin
//             dönüştürülmüş/işlenmiş halini döndürür.
//             Yeni string için bellek dinamik olarak (malloc ile) ayrılır.
//             Başarılı olursa yeni string'e bir pointer, hata durumunda (s veya f NULL ise,
//             veya malloc hatası) NULL döndürür.
//             (Not: Bu implementasyon 'f' NULL kontrolü yapmıyor, ama idealde yapılmalı.)
char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
    size_t s_len; // Kaynak string 's'in uzunluğunu saklamak için.
    size_t i;     // String üzerinde gezinmek ve 'f' fonksiyonuna indeks sağlamak için sayaç.
    char *ptr;    // Oluşturulacak yeni string'i tutacak pointer.

    // 1. Girdi string 's' NULL mu diye kontrol et.
    //    (İdealde 'f' fonksiyon pointer'ı da NULL kontrolünden geçirilmeliydi.)
    if (!s) // Eğer kaynak string NULL ise, işlem yapılamaz, NULL döndür.
        return (NULL);

    // 2. Kaynak string'in NUL karakteri hariç uzunluğunu hesapla.
    s_len = ft_strlen(s);

    // 3. Yeni string için bellek ayır.
    //    Gereken boyut, kaynak string'in uzunluğu + 1 (NUL sonlandırıcı için).
    ptr = malloc(s_len + 1);
    // Bellek ayırma başarısız olursa (malloc NULL döndürürse), NULL döndür.
    if (!ptr)
        return (NULL);

    // 4. String üzerinde gezinmek ve 'f' fonksiyonuna indeks olarak göndermek için
    //    sayacı ayarla. Döngüde ++i kullanılacağı için -1 ile başlanır,
    //    böylece ilk karakter için i=0 olur.
    i = -1;

    // 5. 's' string'inin her bir karakterini işle.
    //    s[++i] ifadesi, önce 'i'yi artırır, sonra s[i]'nin NUL olup olmadığını kontrol eder.
    //    Döngü, NUL karakterine ulaşılana kadar devam eder.
    while (s[++i] != '\0')
    {
        // 'f' fonksiyonunu çağır:
        //   - İlk argüman: mevcut karakterin indeksi (i).
        //   - İkinci argüman: mevcut karakterin kendisi (s[i]).
        // 'f' fonksiyonundan dönen (işlenmiş/dönüştürülmüş) karakteri,
        // yeni string'in (ptr) ilgili pozisyonuna ata.
        ptr[i] = f(i, s[i]);
    }

    // 6. Yeni oluşturulan string'in sonuna NUL sonlandırıcıyı ekle.
    //    Döngü bittiğinde 'i' indeksi, NUL karakterinin yerleştirileceği doğru konumu gösterir.
    ptr[i] = '\0';

    // 7. Yeni oluşturulan ve NUL ile sonlandırılmış string'e pointer'ı döndür.
    //    Bu bellek `free()` ile serbest bırakılmalıdır.
    return (ptr);
}