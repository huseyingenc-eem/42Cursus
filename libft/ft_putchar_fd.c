#include "libft.h" // Bu başlık dosyası muhtemelen <unistd.h> içinde bulunan 'write' fonksiyonunu
                   // dolaylı olarak içeriyordur ya da projenizin bir parçasıdır.

// ft_putchar_fd: Verilen 'c' karakterini, belirtilen 'fd' dosya tanımlayıcısına yazar.
// Bu fonksiyon, tek bir karakteri standart çıktı, standart hata veya açık bir dosya gibi
// belirli bir çıktı hedefine göndermek için kullanılır.
void ft_putchar_fd(char c, int fd)
{
    // 'write' sistem çağrısını kullanarak 'c' karakterini 'fd'ye yaz.
    // Parametreler:
    //   1. fd: Yazma işleminin yapılacağı dosya tanımlayıcısı (file descriptor).
    //          Örneğin, 1 standart çıktı (stdout), 2 standart hata (stderr) anlamına gelir.
    //   2. &c: Yazılacak karakterin bellek adresi. 'write' bir pointer beklediği için
    //          karakterin adresi verilir.
    //   3. 1: Yazılacak byte sayısı. Bir 'char' genellikle 1 byte olduğu için 1 yazılır.
    //
    // 'write' fonksiyonu normalde yazılan byte sayısını veya hata durumunda -1 döndürür.
    // Bu basit implementasyonda 'write'ın dönüş değeri kontrol edilmiyor veya kullanılmıyor,
    // bu tür yardımcı fonksiyonlarda bu yaygın bir yaklaşımdır.
    write(fd, &c, 1);
}