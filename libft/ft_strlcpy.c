#include "libft.h" // Kendi kütüphane başlık dosyanız (ft_strlen'i içerir varsayımıyla)

// ft_strlcpy fonksiyonu, bir string'i (src) başka bir string'e (dest)
// güvenli bir şekilde kopyalar. Hedef buffer'ın (dest) taşmasını önler
// ve her zaman NUL ile sonlandırılmasını sağlar (eğer size > 0 ise).
// Dönen değer, kaynak string'in (src) orijinal uzunluğudur.
size_t ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t src_len; // Kaynak string'in uzunluğunu saklamak için değişken.
    size_t i;       // Kopyalama döngüsü için sayaç.

    // 1. Kaynak string'in gerçek uzunluğunu hesapla.
    // Bu, kopyalamanın başarılı olup olmadığını (kesilme olup olmadığını)
    // anlamak için dönüş değeri olarak kullanılacaktır.
    src_len = ft_strlen(src);

    // 2. Kopyalama için sayacı sıfırla.
    i = 0;

    // 3. Hedef buffer boyutunun (size) sıfır olma durumunu kontrol et.
    // Eğer hedef buffer'ın boyutu sıfır ise, hiçbir şey kopyalanamaz.
    // Bu durumda, sadece kaynak string'in uzunluğunu döndür.
    if (size == 0)
        return (src_len);

    // 4. Karakterleri kopyalama döngüsü.
    // Döngü şu koşullarda devam eder:
    //    a) Kaynak string'in sonuna (`\0`) gelinmediği sürece.
    //    b) Hedef buffer'da hala yer olduğu sürece (NUL sonlandırıcı için bir byte bırakarak, yani `i < size - 1`).
    while (src[i] != '\0' && i < size - 1)
    {
        // Kaynaktaki mevcut karakteri hedefe kopyala.
        dest[i] = src[i];
        // Bir sonraki karaktere geçmek için sayacı artır.
        i++;
    }

    // 5. Hedef string'i NUL karakteri ile sonlandır.
    // Döngüden sonra `i` indeksi, NUL karakterinin yerleştirileceği konumu gösterir.
    // Bu, hedef string'in her zaman geçerli bir C string'i olmasını sağlar.
    dest[i] = '\0';

    // 6. Kaynak string'in orijinal uzunluğunu döndür.
    // Bu, çağıran fonksiyonun, kopyalama sırasında kesilme (truncation)
    // olup olmadığını anlamasına olanak tanır (eğer src_len >= size ise kesilme olmuştur).
    return (src_len);
}