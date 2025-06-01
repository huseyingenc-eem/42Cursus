#include "libft.h" // ft_strchr, ft_strlen, malloc, ft_memcpy için gerekli başlıklar

// ft_strtrim fonksiyonu, 's1' string'inin başından ve sonundan, 'set' string'inde
// bulunan karakterleri temizler (trim). Örneğin, s1="--Merhaba!--" ve set="-" ise
// sonuç "Merhaba!" olur.
// Yeni, temizlenmiş string için bellek dinamik olarak (malloc ile) ayrılır.
// Başarılı olursa yeni string'e bir pointer, hata durumunda (örn: s1 veya set NULL ise, malloc hatası) NULL döndürür.
char *ft_strtrim(char const *s1, char const *set)
{
    char *ptr;      // Oluşturulacak yeni, temizlenmiş string'i tutacak pointer.
    size_t str_len; // Temizlendikten sonraki string'in (veya temizlenecek kısmın) uzunluğunu tutacak.
    char const *original_s1_start; // s1'in orijinal başlangıcını kaybetmemek için (gerekirse).
                                  // Bu implementasyonda doğrudan s1 pointer'ı kaydırılıyor.

    // 1. Girdi string'lerinin NULL olup olmadığını kontrol et.
    //    Eğer s1 veya set (ya da her ikisi) NULL ise, işlem yapılamaz, NULL döndür.
    if (!s1 || !set)
        return (NULL);

    // 2. s1'in başındaki 'set' içinde bulunan karakterleri atla/temizle.
    //    Döngü, s1'in sonuna gelinmediği VE s1'in gösterdiği mevcut karakterin
    //    'set' string'i içinde bulunduğu sürece devam eder.
    //    ft_strchr(set, *s1) != NULL ifadesi, *s1 karakterinin set içinde olduğunu gösterir.
    original_s1_start = s1; // Orijinal s1'i sakla (eğer hiç trim edilmezse diye, ama bu koddaki mantıkta s1 kayıyor)
                           // Bu satır aslında mevcut mantıkla gereksiz, çünkü s1 kaydırılıyor.
                           // Ancak, eğer s1'in orijinalini başka bir yerde kullanmak isteseydik önemli olurdu.
                           // Bu implementasyon için doğrudan s1'i ilerletmek yeterli.
    while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
        s1++; // s1 pointer'ını, 'set' içinde olmayan ilk karaktere veya string sonuna kadar ilerlet.

    // 3. Başı temizlenmiş s1 string'inin mevcut uzunluğunu hesapla.
    //    Bu noktada s1, baştaki trim edilecek karakterlerden sonraki kısmı gösterir.
    str_len = ft_strlen(s1);

    // 4. s1'in (artık başı temizlenmiş olan kısmının) sonundaki 'set' içinde bulunan karakterleri atla/temizle.
    //    Bu işlem, hesaplanan 'str_len'i azaltarak yapılır.
    //    Döngü, str_len > 0 olduğu (string boş olmadığı) VE s1'in (str_len - 1) indeksindeki
    //    (yani sondaki) karakterin 'set' içinde bulunduğu sürece devam eder.
    while (str_len > 0 && ft_strchr(set, s1[str_len - 1]) != NULL)
        str_len--; // Uzunluğu bir azalt, böylece sondaki karakter 'atılmış' olur.

    // 5. Temizlenmiş string için bellek ayır.
    //    Gereken boyut, sondan da temizlendikten sonra kalan 'str_len' kadar karakter
    //    artı 1 byte NUL sonlandırıcı içindir.
    ptr = malloc(str_len + 1);

    // 6. Bellek ayırma işleminin başarılı olup olmadığını kontrol et.
    //    Eğer malloc NULL döndürürse (bellek ayrılamazsa), fonksiyon da NULL döndürür.
    if (!ptr) // ptr == NULL ile aynı
        return (NULL);

    // 7. s1 string'inin temizlenmiş bölümünü yeni ayrılan belleğe (ptr) kopyala.
    //    s1 şu anda başı temizlenmiş string'in başlangıcını göstermektedir.
    //    str_len ise kopyalanacak karakter sayısını (NUL hariç) belirtir.
    //    ft_memcpy, str_len kadar byte kopyalar.
    ft_memcpy(ptr, s1, str_len);

    // 8. Yeni oluşturulan temizlenmiş string'in sonuna NUL sonlandırıcıyı ekle.
    //    Bu, ptr'nin geçerli bir C string'i olmasını sağlar.
    ptr[str_len] = '\0';

    // 9. Yeni oluşturulan ve temizlenmiş string'in başlangıç adresini döndür.
    //    Bu bellek `free()` ile serbest bırakılmalıdır.
    return (ptr);
}