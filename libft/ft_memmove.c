void *ft_memmove(void *dest, const void *src, size_t n)
{
    // Yerel değişkenlerin tanımlanması:
    unsigned char *dest_ptr;      // Hedef bellek bölgesine byte byte erişim için pointer.
    const unsigned char *src_ptr; // Kaynak bellek bölgesine byte byte erişim için (sadece okunabilir) pointer.
    size_t i;                     // İleriye doğru kopyalama için sayaç (ilk blokta kullanılır).

    // Genel void* tipindeki pointer'ları, byte byte işlem yapabilmek için
    // unsigned char* tipine dönüştürerek yerel pointer'lara ata.
    dest_ptr = (unsigned char *)dest;
    src_ptr = (const unsigned char *)src;

    // Eğer kopyalanacak byte sayısı 0 ise veya kaynak ve hedef aynı yeri gösteriyorsa,
    // herhangi bir kopyalama işlemine gerek yoktur. Hedefi doğrudan döndür.
    if (n == 0 || dest_ptr == src_ptr)
    {
        return (dest);
    }

    // Kopyalama yönünü belirle:
    // Durum 1: Hedef adres (`dest_ptr`), kaynak adresten (`src_ptr`) daha düşükse.
    // Bu durumda, bellek bölgeleri örtüşse bile (kaynak, hedefin ilerisinde bir yeri kaplıyorsa),
    // verileri baştan sona (ileriye doğru) kopyalamak güvenlidir.
    // Çünkü yazılan her hedef byte'ı, henüz okunmamış kaynak byte'larının üzerine gelmez.
    if (dest_ptr < src_ptr)
    {
        i = 0; // Sayacı sıfırdan başlat.
        while (i < n) // Belirtilen 'n' byte sayısı kadar kopyala.
        {
            dest_ptr[i] = src_ptr[i]; // Kaynaktan hedefe byte kopyala.
            i++;                      // Bir sonraki byte'a geç.
        }
    }
    else // Durum 2: Hedef adres (`dest_ptr`), kaynak adresten (`src_ptr`) büyük veya eşitse.
         // Bu durumda, bellek bölgeleri örtüşüyorsa (hedef, kaynağın ilerisinde bir yeri kaplıyor
         // ve kaynakla kesişiyorsa), verilerin sondan başa (geriye doğru) kopyalanması gerekir.
         // Bu, kaynak verinin üzerine yazılmadan önce okunmasını garanti eder.
    {
        // 'n' değişkeni burada kalan kopyalanacak byte sayısını ve aynı zamanda
        // mevcut kopyalanacak byte'ın (sondan) indeksini temsil eder.
        while (n > 0) // Kopyalanacak byte kaldığı sürece.
        {
            // Kaynaktaki (n-1)'inci byte'ı hedefin (n-1)'inci byte'ına kopyala.
            // (n-1) çünkü diziler 0 tabanlıdır ve n toplam boyuttur.
            dest_ptr[n - 1] = src_ptr[n - 1];
            n--; // Bir önceki byte'a geç (sondan başa doğru).
        }
    }

    // Fonksiyon, hedef bellek bölgesinin başlangıç adresini geri döndürür.
    return (dest);
}