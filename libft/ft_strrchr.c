#include "libft.h" // Kendi kütüphane başlık dosyanız (ft_strlen'i içerir varsayımıyla)

// ft_strrchr fonksiyonu, 's' string'i içinde 'c' karakterinin
// son (en sağdaki) geçtiği yeri arar.
// Bulunursa o konuma bir pointer, bulunamazsa NULL döndürür.
char *ft_strrchr(const char *s, int c)
{
    // Yerel değişkenlerin tanımlanması:
    char *candidate; // Aranan karakterin bulunduğu son konumu tutacak pointer.
    size_t s_len;    // Kaynak string 's'nin uzunluğunu saklamak için.
    size_t i;        // String içinde gezinmek için sayaç.

    // 1. Kaynak string'in uzunluğunu hesapla.
    // Döngünün string sonunu (NUL karakteri dahil) doğru şekilde işlemesi için bu gereklidir.
    s_len = ft_strlen(s);

    // 2. Sayacı ve aday pointer'ı başlangıç değerlerine ata.
    i = 0;
    candidate = NULL; // Başlangıçta karakter bulunamadı olarak ayarla.

    // 3. String boyunca (NUL karakteri dahil) karakterleri kontrol et.
    // `i <= s_len` koşulu, NUL karakterinin de kontrol edilmesini sağlar.
    // Bu, eğer aranan karakter 'c' NUL ('\0') ise, NUL karakterinin adresinin
    // doğru şekilde döndürülmesi için önemlidir.
    while (i <= s_len)
    {
        // Eğer mevcut karakter s[i], aranan 'c' karakterine eşitse:
        if (s[i] == (char)c)
        {
            // 'candidate' pointer'ını bu bulunan konuma ayarla.
            // Döngü devam ettikçe, 'candidate' her zaman bulunan en son eşleşmeyi tutacaktır.
            // const char * olan s'nin bir bölümüne işaret eden adres,
            // (char *)'a dönüştürülerek atanır, çünkü fonksiyon char * döndürür.
            candidate = (char *)s + i;
        }
        // Bir sonraki karaktere geç.
        i++;
    }

    // 4. Son bulunan adayı (veya karakter hiç bulunamadıysa NULL'u) döndür.
    return (candidate);
}