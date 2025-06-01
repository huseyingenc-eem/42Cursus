// ft_atoi fonksiyonu, bir string (str) içinde temsil edilen sayıyı
// int (tamsayı) veri tipine dönüştürür.
int ft_atoi(const char *str)
{
    int result; // Dönüştürülen sayıyı tutacak değişken.
    int sign;   // Sayının işaretini tutacak değişken (1 pozitif, -1 negatif).

    // 1. Sonuç ve işareti başlangıç değerlerine ata.
    result = 0;
    sign = 1; // Varsayılan olarak pozitif kabul et.

    // 2. String'in başındaki boşluk karakterlerini (whitespace) atla.
    //    ASCII 32: boşluk (' ')
    //    ASCII 9-13: yatay tab, satır başı, dikey tab, sayfa ilerletme, carriage return.
    while (*str == 32 || (*str >= 9 && *str <= 13))
        str++; // Boşluk karakteri olduğu sürece pointer'ı ilerlet.

    // 3. İşaret karakterini kontrol et ve işle.
    //    Eğer mevcut karakter '-' veya '+' ise:
    if (*str == '-' || *str == '+')
    {
        // Eğer karakter '-' ise, sayının işaretini negatif yap.
        if (*str == '-')
            sign = -1;
        // İşaret karakterini geçmek için pointer'ı ilerlet.
        str++;
    }

    // 4. Sayısal karakterleri (rakamları) işle ve tamsayıya dönüştür.
    //    Mevcut karakter '0' ile '9' arasında olduğu sürece döngüye devam et.
    while (*str >= '0' && *str <= '9')
    {
        // Mevcut sonucu 10 ile çarp (bir sonraki basamağa yer aç).
        // Mevcut karakterin sayısal değerini ('0' karakterinin ASCII değerini çıkararak) ekle.
        result = result * 10 + (*str - '0');
        // Bir sonraki karaktere geçmek için pointer'ı ilerlet.
        str++;
    }

    // 5. Elde edilen sonuca işareti uygula ve döndür.
    return (result * sign);
}