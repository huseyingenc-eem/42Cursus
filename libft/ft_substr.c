#include "libft.h" // ft_strlen, ft_strlcpy ve malloc için gerekli başlıklar

// ft_substr fonksiyonu, 's' string'inden belirli bir başlangıç noktasından ('start')
// itibaren belirli bir uzunlukta ('len') yeni bir alt string oluşturur.
// Yeni alt string için bellek dinamik olarak (malloc ile) ayrılır.
// Başarılı olursa yeni alt string'e bir pointer, hata durumunda NULL döndürür.
char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *ptr; // Oluşturulacak alt string'i tutacak pointer.

    // 1. Kaynak string 's' NULL mu diye kontrol et.
    //    Eğer 's' NULL ise, alt string oluşturulamaz, NULL döndür.
    if (!s) // s == NULL ile aynı
        return (NULL);

    // 2. Başlangıç pozisyonu ('start') kaynak string'in uzunluğundan büyük veya eşit mi diye kontrol et.
    //    Eğer 'start' string'in sonunu gösteriyor veya sonundan daha ilerideyse,
    //    boş bir string ("") döndürülmelidir.
    if (start >= ft_strlen(s)) // ft_strlen(s) string'in NUL karakteri hariç uzunluğunu verir.
    {
        // Boş string için 1 byte'lık yer ayır (sadece NUL sonlandırıcı için).
        ptr = malloc(1);
        // Bellek ayırma başarısız olursa NULL döndür.
        if (ptr == NULL)
            return (NULL);
        // Ayrılan belleğe NUL sonlandırıcıyı yerleştirerek boş string oluştur.
        ptr[0] = '\0';
        // Boş string'e pointer'ı döndür.
        return (ptr);
    }

    // 3. Kopyalanacak uzunluğu ('len') ayarla.
    //    Eğer istenen 'len', 'start' pozisyonundan string sonuna kadar olan
    //    mevcut karakter sayısından fazlaysa, 'len'i mevcut karakter sayısına düşür.
    //    Bu, string sınırlarının dışına taşmayı önler.
    if (len > ft_strlen(s) - start)
        len = ft_strlen(s) - start; // Kopyalanabilecek maksimum geçerli uzunluk.

    // 4. Alt string için bellek ayır ('len' karakter + 1 NUL sonlandırıcı için).
    ptr = malloc(len + 1);
    // Bellek ayırma başarısız olursa NULL döndür.
    if (ptr == NULL)
        return (NULL);

    // 5. Kaynak string'in ilgili bölümünü yeni ayrılan belleğe kopyala.
    //    ft_strlcpy kullanılır:
    //      - ptr: hedef buffer.
    //      - s + start: kaynak string'de kopyalamanın başlayacağı adres.
    //      - len + 1: hedef buffer'ın boyutu (kopyalanacak 'len' karakter + NUL için).
    ft_strlcpy(ptr, s + start, len + 1);

    // 6. Yeni oluşturulan alt string'e pointer'ı döndür.
    //    Bu bellek `free()` ile serbest bırakılmalıdır.
    return (ptr);
}