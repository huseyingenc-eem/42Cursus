// ft_memchr fonksiyonu, 's' ile işaret edilen bellek bloğunun ilk 'n' byte'ı içinde,
// 'c' (unsigned char'a dönüştürülmüş) byte'ının ilk geçtiği yeri arar.
// Bulunursa o konuma bir pointer, bulunamazsa NULL döndürür.
void *ft_memchr(const void *s, int c, size_t n)
{
    // Yerel değişkenlerin tanımlanması:
    const unsigned char *s_ptr; // Bellek bloğunda byte byte gezinmek için pointer.
                                // 'unsigned char' olarak tanımlanır çünkü byte değerleriyle
                                // (0-255) çalışmak ve işaret sorunlarından kaçınmak için en uygunudur.
    size_t i;                   // Taranan byte sayısını ve dizinini takip etmek için sayaç.

    // 1. Genel void* pointer'ını, byte byte işlem yapabilmek için
    //    const unsigned char* tipine dönüştürerek yerel pointer'a ata.
    s_ptr = (const unsigned char *)s;

    // 2. Tarama için sayacı sıfırla.
    i = 0;

    // 3. Bellek bloğunun ilk 'n' byte'ını tara.
    //    Döngü, 'i' (taranan byte sayısı) 'n'ye ulaşana kadar devam eder.
    while (i < n)
    {
        // Eğer mevcut byte (s_ptr[i]), aranan 'c' byte'ına eşitse:
        // 'c' (int) değeri, karşılaştırma için (unsigned char)'a dönüştürülür.
        if (s_ptr[i] == (unsigned char)c)
        {
            // Byte bulundu. Bulunan byte'ın adresini (void * türüne dönüştürülmüş olarak) döndür.
            // (s_ptr + i) ifadesi, bulunan byte'ın bellek adresini verir.
            return ((void *)(s_ptr + i));
        }
        // Eğer byte eşleşmiyorsa, bir sonraki byte'a geçmek için sayacı artır.
        i++;
    }

    // 4. Byte bulunamadı.
    // Eğer döngü 'n' byte'ı taradıktan sonra aranan byte bulunamadıysa, NULL döndür.
    return (NULL);
}