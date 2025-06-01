#include "libft.h" // Kendi kütüphane başlık dosyanız

// ft_strnstr fonksiyonu, 'haystack' string'inin ilk 'len' karakteri içinde
// 'needle' string'inin ilk geçtiği yeri arar.
// Bulunursa, 'haystack' içinde 'needle'ın başladığı konuma bir pointer,
// bulunamazsa NULL döndürür. Eğer 'needle' boş ise 'haystack' döndürülür.
char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t i; // 'haystack' üzerinde gezinmek için dış döngü sayacı.
    size_t j; // 'needle'ı 'haystack'in alt string'i ile karşılaştırmak için iç döngü sayacı.

    // 1. 'needle' boş string mi kontrol et.
    // Eğer 'needle' boş bir string ("") ise, standart davranışa göre 'haystack' döndürülür.
    if (*needle == '\0')
        return ((char *)haystack);

    // 2. 'haystack' üzerinde gezinmek için sayacı başlat.
    i = 0;

    // 3. Ana arama döngüsü: 'haystack' üzerinde 'len' sınırını ve string sonunu dikkate alarak gezin.
    //    'i < len': 'haystack' içinde taranacak karakter sayısı 'len'i aşmamalı.
    //    'haystack[i]': 'haystack' string'inin sonuna (NUL karakterine) ulaşılmamış olmalı.
    while (i < len && haystack[i] != '\0')
    {
        // 4. Her 'haystack' pozisyonu için 'needle' ile karşılaştırmaya başla.
        //    'j' sayacını (needle indeksi) sıfırla.
        j = 0;

        // 5. İç karşılaştırma döngüsü: 'needle'ın karakterlerini 'haystack'in
        //    mevcut 'i' pozisyonundan itibarenki karakterleriyle karşılaştır.
        //    Koşullar:
        //      a) 'i + j < len': 'haystack'te 'len' sınırı içinde kalındığından emin ol.
        //      b) 'haystack[i + j] != '\0'': 'haystack'in mevcut alt string'inin sonuna gelinmediğinden emin ol.
        //      c) 'haystack[i + j] == needle[j]': Karakterler eşleştiği sürece devam et.
        while (i + j < len && haystack[i + j] != '\0' && haystack[i + j] == needle[j])
        {
            // Eğer karakterler eşleşiyorsa, 'needle'ın bir sonraki karakterine geç.
            j++;
        }

        // 6. 'needle'ın tamamı bulundu mu kontrol et.
        // Eğer iç döngü 'needle'ın sonundaki NUL karakterine ulaştığı için bittiyse
        // (yani needle[j] == '\0'), bu 'needle'ın 'haystack' içinde tam olarak bulunduğu anlamına gelir.
        if (needle[j] == '\0')
        {
            // 'needle'ın 'haystack' içinde başladığı adresi döndür.
            // (char *)haystack + i, const niteleyicisini kaldırır ve doğru adresi verir.
            return ((char *)(haystack + i));
        }

        // 7. 'needle' bulunamadıysa, 'haystack'te bir sonraki başlangıç pozisyonuna geç.
        i++;
    }

    // 8. 'needle' bulunamadı.
    // Eğer dış döngü, 'haystack'in 'len' karakterlik kısmında 'needle'ı bulamadan biterse, NULL döndür.
    return (NULL);
}