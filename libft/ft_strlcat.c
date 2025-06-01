#include "libft.h" // Kendi kütüphane başlık dosyanız (ft_strlen'i içerir varsayımıyla)

// ft_strlcat fonksiyonu, src string'ini dest string'inin sonuna güvenli bir şekilde ekler (birleştirir).
// Hedef buffer'ın (dest) taşmasını önler ve her zaman NUL ile sonlandırılmasını sağlar (yeterli alan varsa).
// Dönen değer, oluşturulmaya çalışılan string'in toplam uzunluğudur (başlangıçtaki dest + src).
size_t ft_strlcat (char *dest, const char *src, size_t size)
{
    size_t dest_len; // Başlangıçtaki hedef string'in (dest) uzunluğunu saklamak için.
    size_t src_len;  // Kaynak string'in (src) uzunluğunu saklamak için.
    size_t i;        // Kaynaktan hedefe karakterleri kopyalamak için sayaç.

    // 1. Hedef string'in mevcut (NUL karakterine kadar olan) uzunluğunu al.
    dest_len = ft_strlen(dest);
    // 2. Kaynak string'in tam uzunluğunu al.
    src_len = ft_strlen(src);

    // 3. Hedef buffer'ın (size) zaten dolu olup olmadığını veya ekleme için çok küçük olup olmadığını kontrol et.
    // Eğer 'size' (hedef buffer'ın toplam boyutu) 'dest_len'den (mevcut hedef string uzunluğu)
    // küçük veya eşitse, yeni bir karakter veya NUL sonlandırıcı eklemek için yer yoktur.
    // strlcat spesifikasyonuna göre, bu durumda kaynak string'in uzunluğu + 'size' döndürülür.
    // (Burada 'size', 'dest_len'den küçük veya eşit olduğu için, etkili bir şekilde
    // 'dest_len'in sığabileceği maksimum boyutu ifade eder gibi davranır).
    if (size <= dest_len)
        return (src_len + size); // Veya return (src_len + dest_len_as_if_truncated_to_size)

    // 4. Kaynaktan karakterleri kopyalamak için sayacı sıfırla.
    i = 0;

    // 5. Karakterleri src'den dest'in sonuna ekleme döngüsü.
    // Döngü şu koşullarda devam eder:
    //    a) Kaynak string'in sonuna (`\0`) gelinmediği sürece.
    //    b) Hedef buffer'da kopyalanacak karakter VE NUL sonlandırıcı için yeterli yer olduğu sürece
    //       (yani, `dest_len + i` (mevcut pozisyon) + 1 (NUL için) < `size`).
    while (src[i] != '\0' && dest_len + i + 1 < size)
    {
        // Kaynaktaki i'inci karakteri, hedef string'in sonuna (dest_len + i pozisyonuna) kopyala.
        dest[dest_len + i] = src[i];
        // Bir sonraki karaktere geçmek için sayacı artır.
        i++;
    }

    // 6. Birleştirilmiş hedef string'i NUL karakteri ile sonlandır.
    // Döngüden sonra (dest_len + i) pozisyonu, NUL karakterinin yerleştirileceği doğru yerdir.
    dest[dest_len + i] = '\0';

    // 7. Oluşturulmaya çalışılan string'in toplam teorik uzunluğunu döndür.
    // Bu, başlangıçtaki hedef string'in uzunluğu artı kaynak string'in tam uzunluğudur.
    // Çağıran fonksiyon bu değeri 'size' ile karşılaştırarak kesilme (truncation)
    // olup olmadığını anlayabilir (eğer dönen_değer >= size ise kesilme olmuştur).
    return (dest_len + src_len);
}