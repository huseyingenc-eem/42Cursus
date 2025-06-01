// ft_memcmp fonksiyonu, s1 ve s2 bellek bloklarının ilk 'n' byte'ını karşılaştırır.
// Dönüş değeri:
//   < 0 ise s1, s2'den küçüktür.
//   = 0 ise s1 ve s2'nin ilk n byte'ı eşittir.
//   > 0 ise s1, s2'den büyüktür.
int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    // Yerel değişkenlerin tanımlanması:
    const unsigned char *s1_ptr; // s1 bellek bloğunda byte byte gezinmek için pointer.
    const unsigned char *s2_ptr; // s2 bellek bloğunda byte byte gezinmek için pointer.
                                 // 'unsigned char' kullanılır çünkü byte'lar işaretsiz olarak karşılaştırılmalıdır.
    size_t i;                    // Karşılaştırılan byte sayısını ve dizinini takip etmek için sayaç.

    // 1. Genel void* pointer'larını, byte byte işlem yapabilmek için
    //    const unsigned char* tipine dönüştürerek yerel pointer'lara ata.
    s1_ptr = (const unsigned char *)s1;
    s2_ptr = (const unsigned char *)s2;

    // 2. Karşılaştırma için sayacı sıfırla.
    i = 0;

    // 3. Bellek bloklarının ilk 'n' byte'ını karşılaştır.
    //    Döngü, 'i' (karşılaştırılan byte sayısı) 'n'ye ulaşana kadar devam eder.
    while (i < n)
    {
        // Eğer s1_ptr'nin gösterdiği mevcut byte, s2_ptr'nin gösterdiği mevcut byte'tan farklıysa:
        if (s1_ptr[i] != s2_ptr[i])
        {
            // Farklı byte'ların (unsigned char olarak değerlendirilmiş) değerlerinin farkını döndür.
            // Bu, s1 < s2 ise negatif, s1 > s2 ise pozitif bir değer üretecektir.
            return (s1_ptr[i] - s2_ptr[i]);
        }
        // Eğer byte'lar eşitse, bir sonraki byte'a geçmek için sayacı artır.
        i++;
    }

    // 4. Byte'lar Eşit.
    // Eğer döngü 'n' byte'ı karşılaştırdıktan sonra hiçbir fark bulunamadıysa,
    // bellek bloklarının ilk 'n' byte'ı eşittir. Bu durumda 0 döndürülmelidir.
    // NOT: 'NULL' (genellikle (void*)0) yerine doğrudan '0' (tamsayı sıfır) döndürmek daha doğrudur.
    return (0); // return (NULL); yerine bu şekilde olmalı.
}