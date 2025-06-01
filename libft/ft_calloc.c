#include "libft.h" // ft_bzero ve muhtemelen malloc'un olduğu başlık dosyanız

// ft_calloc fonksiyonu, her biri 'size' byte olan 'nmemb' adet eleman için
// bellek ayırır ve ayrılan belleği sıfırlarla doldurur.
// Başarılı olursa ayrılan belleğe bir pointer, hata durumunda NULL döndürür.
void *ft_calloc(size_t nmemb, size_t size)
{
    size_t total_size; // Toplam ayrılacak byte sayısını tutmak için.
    void *ptr;         // Ayrılan belleğin adresini tutacak pointer.

    // 1. Toplam bellek boyutunu hesapla (eleman sayısı * her elemanın boyutu).
    total_size = nmemb * size;

    // 2. İstenen toplam boyutun sıfır olup olmadığını kontrol et.
    //    Eğer nmemb veya size (ya da her ikisi) sıfırsa, total_size da sıfır olur.
    //    Bu implementasyon, sıfır boyutlu bir istek için NULL döndürür.
    //    (Not: Standart calloc, size=0 durumunda NULL veya free() ile kullanılabilecek
    //    benzersiz bir pointer döndürebilir. Bu implementasyon NULL döndürmeyi seçiyor.)
    //    Ayrıca, nmemb veya size sıfır değilken çarpım sonucu (total_size) sıfırsa,
    //    bu durum bir taşma olmadığını, gerçekten sıfır byte istendiğini gösterir.
    //    Ancak, eğer nmemb ve size çok büyükse ve çarpımları SIZE_MAX'ı aşıp
    //    sıfıra geri dönerse (çok olası değil ama teorik), aşağıdaki taşma kontrolü bunu yakalar.
    if (nmemb == 0 || size == 0) // Bu kontrolü total_size == 0 yerine yapmak daha net olabilir.
                                  // Çünkü total_size == 0, nmemb veya size'ın 0 olmasından kaynaklanabilir.
        return (NULL); // Bu implementasyonda 0 byte'lık istek için NULL döndürülüyor.

    // 3. Çarpma işleminde tamsayı taşması (integer overflow) olup olmadığını kontrol et.
    //    Eğer nmemb veya size sıfır değilse (yukarıdaki kontrolle bu durum elenmiş olmalıydı
    //    eğer total_size == 0 kontrolü yerine nmemb == 0 || size == 0 kullanılsaydı),
    //    (total_size / nmemb) işleminin 'size'a eşit olması gerekir. Eşit değilse taşma olmuştur.
    //    Bu kontrol, total_size'ın nmemb ve size'ın geçerli bir çarpımı olup olmadığını doğrular.
    //    nmemb sıfır olamayacağından (önceki if ile elenmiş varsayılırsa), bölme güvenlidir.
    if (total_size / nmemb != size) // Daha güvenli bir taşma kontrolü: if (size != 0 && nmemb > SIZE_MAX / size)
        return (NULL); // Taşma durumunda NULL döndür.

    // 4. malloc kullanarak hesaplanan toplam boyutta bellek ayır.
    ptr = malloc(total_size);

    // 5. malloc'un bellek ayırıp ayıramadığını kontrol et.
    //    Eğer malloc NULL döndürürse, bellek ayrılamamıştır.
    if (ptr == NULL)
        return (NULL); // Bellek ayrılamazsa NULL döndür.

    // 6. Ayrılan belleği sıfırlarla doldur (calloc'un temel özelliği).
    //    ft_bzero (veya memset) fonksiyonu bu iş için kullanılır.
    ft_bzero(ptr, total_size);

    // 7. Başarıyla ayrılan ve sıfırlanan belleğin başlangıç adresini döndür.
    return (ptr);
}