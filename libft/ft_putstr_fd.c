#include "libft.h" // Bu başlık dosyası ft_strlen ve 'write' sistem çağrısı için
                   // gerekli <unistd.h> gibi başlıkları içeriyor olmalı.

// ft_putstr_fd: Verilen 's' string'ini, belirtilen 'fd' dosya tanımlayıcısına yazar.
// String'in sonundaki NUL ('\0') karakteri yazılmaz.
void ft_putstr_fd(char *s, int fd)
{
    size_t  str_len; // Yazılacak string'in uzunluğunu tutmak için değişken.

    // 1. Girdi string 's' NULL mu diye kontrol et.
    //    Eğer string NULL ise, herhangi bir işlem yapma ve fonksiyondan güvenle çık.
    if (!s) // s == NULL ile aynı
        return;

    // 2. Yazılacak string'in uzunluğunu (NUL karakteri hariç) hesapla.
    //    ft_strlen, NUL karakterine kadar olan karakter sayısını döndürür.
    str_len = ft_strlen(s);

    // 3. 'write' sistem çağrısını kullanarak string'in tamamını (NUL hariç) 'fd'ye yaz.
    //    Parametreler:
    //      fd: Yazma işleminin yapılacağı dosya tanımlayıcısı (file descriptor).
    //          Örn: 1 standart çıktı (stdout), 2 standart hata (stderr).
    //      s:  Yazılacak string'in başlangıç adresi.
    //      str_len: Yazılacak byte sayısı (string'in NUL hariç uzunluğu).
    //
    //    'write' fonksiyonu normalde yazılan byte sayısını veya hata durumunda -1 döndürür.
    //    Bu implementasyonda 'write'ın dönüş değeri kontrol edilmiyor, bu tür yardımcı
    //    fonksiyonlarda yaygın bir yaklaşımdır.
    write(fd, s, str_len);
}