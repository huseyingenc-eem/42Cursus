// ft_strncmp fonksiyonu, s1 ve s2 string'lerinin en fazla 'n' karakterini karşılaştırır.
// Karşılaştırma sonucuna göre bir tamsayı döndürür:
//   < 0 ise s1, s2'den küçüktür.
//   = 0 ise s1 ve s2'nin ilk n karakteri eşittir (veya her ikisi de n'den kısadır ve eşittir).
//   > 0 ise s1, s2'den büyüktür.
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i; // Karakterleri saymak ve dizinlemek için sayaç.
    // int result; // Bu değişken kodda kullanılmıyor, kaldırılabilir.

    i = 0; // Sayacı sıfırdan başlat.

    // En fazla 'n' karakter karşılaştırılana kadar veya bir fark bulunana/string sonuna ulaşılana kadar döngüye gir.
    while (i < n)
    {
        // 1. Karakterleri Karşılaştır veya String Sonlarını Kontrol Et:
        //    - s1[i] ve s2[i] farklı mı?
        //    - VEYA s1[i] NUL karakteri mi (s1 string'inin sonu)?
        //    - VEYA s2[i] NUL karakteri mi (s2 string'inin sonu)?
        //    Bu koşullardan herhangi biri doğruysa, karşılaştırma bu noktada sonlanmalıdır.
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
        {
            // Karakterlerin farkını (ASCII değerleri üzerinden) döndür.
            // Standart strncmp davranışına uygun olarak, karakterler
            // unsigned char olarak değerlendirilerek fark alınır.
            // Eğer karakterler eşitse (örneğin ikisi de '\0' ise), fark 0 olur.
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        }
        // Eğer karakterler aynıysa ve hiçbiri NUL değilse, bir sonraki karaktere geç.
        i++;
    }

    // 2. Döngü Tamamlandı (n karaktere ulaşıldı):
    // Eğer döngü 'n' defa çalıştıysa ve yukarıdaki 'if' koşulu hiç sağlanmadıysa,
    // bu, ilk 'n' karakterin her iki string'de de aynı olduğu anlamına gelir.
    // Bu durumda, string'ler 'n' karaktere kadar eşittir, 0 döndür.
    return (0);
}