#include "libft.h" // ft_strlen, ft_strlcpy, malloc, free için gerekli başlıklar

// count_words: Verilen 's' string'indeki 'c' ayıracına göre kelime sayısını hesaplar.
// Bu implementasyonun ardışık ayraçlar ve baştaki/sondaki ayraçlarla ilgili
// davranışları, beklenen standart 'split' davranışından farklılık gösterebilir.
// (Not: Bu fonksiyonun mantığı, özellikle baştaki/sondaki veya ardışık
// ayraçlar için bazı kenar durumlarını doğru işlemeyebilir. Standart bir split
// için genellikle ayraçlar atlanır ve sadece gerçek kelimeler sayılır.)
static int count_words(char const *s, char c) // 'static' eklendi, çünkü genellikle split'in yardımcı fonksiyonudur.
{
    int count;     // Bulunan kelime sayısını tutar.
    int in_word;   // Mevcut pozisyonun bir kelime içinde olup olmadığını belirten bayrak.
    size_t i;      // String üzerinde gezinmek için sayaç.

    count = 0;   // Kelime sayacını sıfırla.
    in_word = 0; // Başlangıçta bir kelime içinde değiliz.
    i = 0;       // String'in başından başla.
    while (s[i]) // String sonuna (NUL) kadar dön.
    {
        // Eğer mevcut karakter ayraçsa VE bir kelime içindeysek, kelimeden çıktık.
        if (s[i] == c && in_word == 1)
            in_word = 0;
        // Eğer mevcut karakter ayraç değilse VEYA ayraç ama kelime içinde değilsek (bu else bloğu biraz karmaşık)
        else if (s[i] != c) // Bu koşulu netleştirmek daha iyi olabilir: Sadece ayraç değilse kelimeye gir/devam et.
        {
            // Eğer bir kelime içinde değilsek (yani yeni bir kelime başlıyor):
            if (in_word == 0)
            {
                in_word = 1; // Artık bir kelime içindeyiz.
                count++;     // Yeni bir kelime bulundu, sayacı artır.
            }
        }
        i++; // Bir sonraki karaktere geç.
    }
    return (count); // Toplam kelime sayısını döndür.
}

// get_word_len: Verilen 's' string'inde, 'start_index'ten başlayarak
// bir sonraki 'c' ayıracına veya string sonuna kadar olan kelimenin uzunluğunu hesaplar.
static size_t get_word_len(char const *s, size_t start_index, char c) // 'static' eklendi
{
    size_t len; // Kelime uzunluğunu tutar.
    size_t i;   // String üzerinde gezinmek için sayaç.

    len = 0;
    i = start_index; // Verilen başlangıç indeksinden başla.
    // Mevcut karakter string sonu (NUL) olmadığı VE ayraç karakteri ('c') olmadığı sürece dön.
    while (s[i] && s[i] != c)
    {
        len++; // Kelime uzunluğunu artır.
        i++;   // Bir sonraki karaktere geç.
    }
    return (len); // Hesaplanan kelime uzunluğunu döndür.
}

// free_result: ft_split tarafından ayrılmış olan string dizisini ('result') ve
// içindeki her bir string'i serbest bırakır. Hata durumunda bellek temizliği için kullanılır.
// 'index', 'result' dizisinde o ana kadar başarıyla doldurulmuş (veya doldurulmaya çalışılmış)
// string sayısını (veya bir sonraki boş indeksi) gösterir.
static char **free_result(char **result, size_t index) // 'static' eklendi
{
    // 'index'ten geriye doğru giderek, 'result' dizisindeki her bir string pointer'ını serbest bırak.
    // Bu implementasyon, 'index'in bir sonraki boş slotu işaret ettiğini varsayarak
    // index-1'den başlayarak free eder.
    while (index > 0)
    {
        index--;             // Bir önceki indekse git (son eklenen/ayrılan string).
        free(result[index]); // Mevcut indeksteki string'i serbest bırak.
    }
    free(result); // 'result' dizisinin kendisini (pointer dizisini) serbest bırak.
    return (NULL); // Her zaman NULL döndürerek, çağıran fonksiyonda kolay hata yönetimi sağlar.
}

// create_and_copy_word: 's' string'inden, 'start_index'ten başlayarak bir sonraki
// 'c' ayıracına kadar olan kelimeyi ayıklar, bu kelime için bellek ayırır ve kopyalar.
static char *create_and_copy_word(char const *s, size_t start_index, char c) // 'static' eklendi
{
    // Kelimenin uzunluğunu 'get_word_len' ile hesapla.
    size_t word_len = get_word_len(s, start_index, c);
    // Kelimeyi ve NUL sonlandırıcıyı tutacak kadar bellek ayır (malloc).
    char *word = malloc(word_len + 1);

    if (!word) // Eğer malloc başarısız olursa (bellek ayrılamazsa):
    {
        return (NULL); // NULL döndür.
    }
    // ft_strlcpy kullanarak, 's' string'inden (s + start_index) 'word_len' kadar
    // karakteri yeni ayrılan 'word' belleğine kopyala ve NUL ile sonlandır.
    // ft_strlcpy'nin üçüncü parametresi buffer boyutudur (word_len + 1).
    ft_strlcpy(word, s + start_index, word_len + 1);
    return (word); // Yeni oluşturulan ve kopyalanan kelime string'ini döndür.
}


// ft_split: Verilen 's' string'ini, 'c' karakterini ayraç olarak kullanarak
// alt string'lere (kelimelere) böler.
// Sonuç, NUL ile sonlandırılmış bir string (char *) dizisidir. Bu dizi de NUL ile sonlandırılır.
// Başarı durumunda bu yeni string dizisine bir pointer, hata durumunda NULL döndürür.
char **ft_split(char const *s, char c)
{
    char **result;   // Sonuçta döndürülecek string (char **) dizisi.
    size_t i;        // 's' string'i üzerinde gezinmek için ana sayaç/indeks.
    size_t j;        // 'result' dizisine kelimeleri atamak için sayaç/indeks.
    size_t num_words; // 's' string'indeki toplam kelime sayısı (count_words'e göre).

    // 1. Girdi string 's' NULL mu diye kontrol et.
    if (!s)
        return (NULL); // NULL ise NULL döndür.

    // 2. 's' string'indeki kelime sayısını hesapla (kullanılan count_words fonksiyonuna göre).
    num_words = count_words(s, c);

    // 3. Kelime pointer'larını ve sonlandırıcı NULL pointer'ı tutacak kadar bellek ayır.
    //    (num_words adet kelime pointer'ı + 1 adet sonlandırıcı NULL pointer için yer).
    result = malloc((num_words + 1) * sizeof(char *));
    if (!result) // Eğer malloc başarısız olursa:
        return (NULL); // NULL döndür.

    i = 0; // 's' string'i için indeksi (kelime başlangıçlarını bulmak için) başlat.
    j = -1; // 'result' dizisi için indeksi -1 ile başlat (ilk kelime result[0]'a gelecek şekilde ++j kullanılacak).

    // 4. 'result' dizisine kelimeleri doldurma döngüsü.
    //    j, 0'dan num_words-1'e kadar artacak.
    while (++j < num_words)
    {
        // Baştaki veya kelimeler arasındaki ayraç karakterlerini atla.
        // Bu döngü, 's' string'inde bir sonraki kelimenin başlangıcını bulur.
        // Ayrıca string sonunu da kontrol eder.
        while (s[i] == c && s[i] != '\0')
            i++;

        // Mevcut pozisyondan (i) bir sonraki ayraca kadar olan kelimeyi oluştur ve kopyala.
        result[j] = create_and_copy_word(s, i, c);

        // Eğer kelime oluşturma ve kopyalama sırasında bellek hatası olursa (create_and_copy_word NULL döndürürse):
        if (!result[j])
        {
            // O ana kadar 'result' dizisine eklenmiş tüm string'leri ve 'result' dizisinin
            // kendisini 'free_result' ile serbest bırak ve NULL döndür. 'j' burada o ana
            // kadar ayrılmış string sayısını (veya bir sonraki boş indeksi) ifade eder.
            return (free_result(result, j));
        }
        // Bir sonraki kelimeye geçmek için 's' string'indeki indeksi (i) ilerlet.
        // i'yi, az önce kopyalanan kelimenin sonrasına (bir sonraki ayraç veya string sonu) taşı.
        i += get_word_len(s, i, c);
    }
    // 5. String dizisinin sonunu belirtmek için son elemanı NULL yap.
    //    Döngü bittiğinde j, num_words değerine sahip olur. result[num_words] NULL olmalıdır.
    result[j] = NULL;

    // 6. Başarıyla oluşturulmuş string dizisini döndür.
    return (result);
}