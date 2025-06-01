void *ft_memcpy(void *dest, const void *src, size_t n)
{
    // Yerel değişkenlerin tanımlanması:
    unsigned char *dest_ptr;      // Hedef bellek bölgesine byte byte erişim için pointer.
    const unsigned char *src_ptr; // Kaynak bellek bölgesine byte byte erişim için (sadece okunabilir) pointer.
    size_t i;                     // Kopyalanan byte sayısını takip etmek için sayaç.

    // void* olan genel amaçlı pointer'ları, byte byte işlem yapabilmek için
    // unsigned char* tipine dönüştürerek yerel pointer'lara ata.
    dest_ptr = (unsigned char *)dest;
    src_ptr = (const unsigned char *)src;

    i = 0; // Sayacı başlat.

    // Belirtilen 'n' byte sayısı kadar döngüyü çalıştır.
    while (i < n)
    {
        // Kaynaktaki mevcut byte'ı (src_ptr[i]) hedefin mevcut byte'ına (dest_ptr[i]) kopyala.
        dest_ptr[i] = src_ptr[i];
        i++; // Bir sonraki byte'a geçmek için sayacı artır.
    }

    // Fonksiyon, hedef bellek bölgesinin başlangıç adresini geri döndürür.
    return (dest);
}