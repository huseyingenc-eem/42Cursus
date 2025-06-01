#include "libft.h" // Diğer ft_ fonksiyonları ve malloc için

// ft_count_digits: Verilen 'n' tamsayısının string temsilindeki karakter sayısını
// (işaret dahil, NUL karakteri hariç) hesaplar.
static int ft_count_digits(int n)
{
    int len;          // Uzunluğu (karakter sayısını) tutacak değişken.
    long long temp_n; // 'n' değerini taşma riskine karşı (özellikle INT_MIN için) long long olarak tutar.

    len = 0;
    if (n == 0) // Eğer sayı 0 ise, string temsili "0" olup 1 karakterdir.
        return (1);
    // INT_MIN (-2147483648) özel durumu: 1 (işaret) + 10 (basamak) = 11 karakter.
    if (n == INT_MIN)
        return (11);

    temp_n = n; // 'n'yi geçici değişkene ata.
    if (temp_n < 0) // Eğer sayı negatifse:
    {
        temp_n *= -1; // Sayının mutlak değerini al (işareti daha sonra ekleyeceğiz).
        len++;        // '-' işareti için uzunluğa 1 ekle.
    }
    // Sayı pozitifken (veya pozitife çevrilmişken) ve 0'dan büyükken:
    while (temp_n > 0)
    {
        temp_n /= 10; // Sayının son basamağını at (örn: 123 -> 12).
        len++;        // Basamak sayısını bir artır.
    }
    return (len); // Hesaplanan toplam karakter sayısını döndür.
}

// ft_convert_to_string: Verilen 'n' (long long) tamsayısını, önceden ayrılmış 'ptr'
// karakter dizisine, 'num_len' uzunluğunda bir string olarak yazar.
// Sayıyı string'e çevirirken basamakları sondan başa doğru (sağdan sola) yerleştirir.
static void ft_convert_to_string(long long n, char *ptr, int num_len)
{
    int i; // Karakter dizisi 'ptr' içinde yazılacak konumu gösteren indeks.

    i = num_len - 1; // İndeksi, string'in son yazılabilir karakter pozisyonuna ayarla (NUL öncesi).

    if (n == 0) // Eğer dönüştürülecek sayı 0 ise:
    {
        ptr[0] = '0'; // String'e '0' karakterini yaz.
        // NUL sonlandırıcı ana ft_itoa fonksiyonunda eklenecek.
        return;
    }

    if (n < 0) // Eğer sayı negatifse:
    {
        ptr[0] = '-'; // String'in ilk karakteri olarak '-' işaretini koy.
        n *= -1;      // Sayının mutlak değerini alarak basamakları işle.
        // İşaret ptr[0]'a konulduğu için basamaklar ptr[1]'den itibaren sağa dayalı yazılacak.
        // Döngü i'yi kullandığı için bu durum doğal olarak ele alınır:
        // Örn: n=-123, num_len=4. i=3. ptr[3]='3', i=2. ptr[2]='2', i=1. ptr[1]='1'. i=0. Döngü biter.
    }

    // Sayı (artık pozitif) 0'dan büyük olduğu sürece basamakları string'e ekle.
    // Basamaklar string'e sondan başa doğru yerleştirilir.
    while (n > 0)
    {
        // Sayının 10'a bölümünden kalanı (son basamağı) al, ASCII karaktere çevir ('0' ekleyerek)
        // ve string'in uygun pozisyonuna (sağdan sola doğru) yaz.
        ptr[i] = (n % 10) + '0';
        n /= 10; // Sayının son basamağını at.
        i--;     // Bir önceki pozisyona geç (sondan başa doğru yazmak için).
    }
}

// ft_itoa: Verilen 'n' tamsayısını, karakter dizisine (string) dönüştürür.
// Yeni string için bellek dinamik olarak (malloc ile) ayrılır.
// Başarılı olursa yeni string'e bir pointer, hata durumunda NULL döndürür.
char *ft_itoa(int n)
{
    int num_len;      // 'n' sayısının string temsilinin uzunluğu (işaret dahil, NUL hariç).
    char *ptr;        // Oluşturulacak string'i tutacak pointer.
    long long temp_n; // 'n' değerini (özellikle INT_MIN için taşmayı önlemek amacıyla) geçici olarak tutar.

    // 1. Sayının string olarak kaç karakterden oluşacağını hesapla.
    num_len = ft_count_digits(n);

    // 2. Hesaplanan uzunluk + 1 (NUL sonlandırıcı '\0' için) kadar bellek ayır.
    ptr = malloc(num_len + 1);
    if (!ptr) // Eğer malloc başarısız olursa (bellek ayrılamazsa):
        return (NULL); // NULL döndür.

    // 3. String'in sonuna NUL sonlandırıcıyı yerleştir.
    //    Bu, ptr'nin geçerli bir C string'i olmasını sağlar.
    ptr[num_len] = '\0';

    // 4. 'n' tamsayısını string'e dönüştürmek için yardımcı fonksiyonu çağır.
    //    'n' (int) değeri, potansiyel INT_MIN taşmasını (negatifinin pozitif int'e sığmaması)
    //    önlemek için 'long long' tipine dönüştürülerek yardımcı fonksiyona verilir.
    temp_n = n;
    ft_convert_to_string(temp_n, ptr, num_len);

    // 5. Yeni oluşturulan ve NUL ile sonlandırılmış string'in başlangıç adresini döndür.
    //    Bu bellek `free()` ile serbest bırakılmalıdır.
    return (ptr);
}