#include "libft.h" // Bu başlık dosyası ft_putstr_fd ve ft_putchar_fd fonksiyonlarını içeriyor olmalı.

// ft_putnbr_fd: Verilen 'n' tamsayısını, karakter dizisi olarak (string)
//               belirtilen 'fd' dosya tanımlayıcısına yazar.
//               Örneğin, n=123 ise "123" yazar.
void ft_putnbr_fd(int n, int fd)
{
    long int temp; // 'n' değerini işlemek için geçici bir değişken.
                   // 'long int' kullanılması, özellikle n = INT_MIN olduğunda,
                   // -n işleminin int sınırları içinde taşmasını önlemeye yardımcı olur.

    // 1. INT_MIN (-2147483648) özel durumunu ele al.
    //    Bu sayının mutlak değeri (2147483648), pozitif int'in maksimum
    //    değerini (INT_MAX = 2147483647) aştığı için, -n işlemi int tipinde
    //    taşmaya neden olabilir. Bu yüzden string olarak doğrudan yazılır.
    if (n == -2147483648) // Veya daha taşınabilir olarak: if (n == INT_MIN)
    {
        // ft_putstr_fd kullanarak INT_MIN değerini string olarak yazdır.
        ft_putstr_fd("-2147483648", fd);
        return; // Fonksiyondan çık.
    }

    temp = n; // 'n' tamsayısını geçici 'temp' (long int) değişkenine ata.

    // 2. Eğer sayı 0 ise, '0' karakterini yazdır ve fonksiyondan çık.
    //    Bu, özyinelemeli kısmın 0 için çalışmasını engeller ve doğrudan '0' yazılmasını sağlar.
    if (temp == 0)
    {
        ft_putchar_fd('0', fd);
        return;
    }

    // 3. Eğer sayı negatifse:
    if (temp < 0)
    {
        ft_putchar_fd('-', fd); // Önce '-' işaretini yazdır.
        temp *= -1;             // Sayıyı pozitife çevir (mutlak değerini al) ve işlemeye devam et.
    }

    // 4. Sayıyı basamaklarına ayırıp yazdırmak için özyineleme (recursion) kullan.
    //    Eğer sayı 10'dan büyük veya eşitse (yani birden fazla basamağı varsa):
    //    temp / 10: Sayının son basamağı hariç diğer basamaklarını alır (örn: 123 / 10 = 12).
    //    Bu kısım için ft_putnbr_fd fonksiyonu tekrar çağrılır.
    //    Bu, basamakların en anlamlıdan (soldan) başlayarak işlenmesini sağlar.
    if (temp >= 10)
        ft_putnbr_fd(temp / 10, fd);

    // 5. Mevcut (en az anlamlı veya özyinelemeden dönen) basamağı yazdır.
    //    temp % 10: Sayının son basamağını verir (örn: 123 % 10 = 3).
    //    Bu tamsayı basamağı ASCII karakterine dönüştürmek için '0' karakterinin ASCII değeri eklenir
    //    (örn: 3 (int) + '0' (char) = '3' (char)).
    //    ft_putchar_fd ile bu karakter 'fd'ye yazdırılır.
    //    Özyineleme sayesinde, en son bu satır çalıştığında en sağdaki basamak yazılır.
    ft_putchar_fd((temp % 10) + '0', fd);
}