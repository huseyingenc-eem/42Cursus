#include "libft.h" // Bu başlık dosyası ft_putstr_fd ve ft_putchar_fd fonksiyonlarını içeriyor olmalı.

// ft_putendl_fd: Verilen 's' string'ini, belirtilen 'fd' dosya tanımlayıcısına yazar
//                ve ardından bir yeni satır ('\n') karakteri ekler.
//                'endl' "end line" (satır sonu) anlamına gelir.
void ft_putendl_fd(char *s, int fd)
{
    // 1. Girdi string 's' NULL mu diye kontrol et.
    //    Eğer string NULL ise, herhangi bir işlem yapma ve fonksiyondan güvenle çık.
    //    Bu, NULL pointer'a erişimden kaynaklanabilecek bir çökmeyi önler.
    if (!s) // s == NULL ile aynı
        return;

    // 2. 'ft_putstr_fd' fonksiyonunu kullanarak 's' string'ini 'fd'ye yaz.
    //    Bu fonksiyon, string'in kendisini (NUL karakteri hariç) yazar.
    ft_putstr_fd(s, fd);

    // 3. 'ft_putchar_fd' fonksiyonunu kullanarak yeni satır ('\n') karakterini 'fd'ye yaz.
    //    Bu, yazılan string'in ardından imlecin bir sonraki satırın başına geçmesini sağlar
    //    veya dosyada yeni bir satır başlatır.
    ft_putchar_fd('\n', fd);
}