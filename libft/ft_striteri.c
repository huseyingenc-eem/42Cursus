#include "libft.h" // Gerekli olabilecek libft başlıkları

// ft_striteri: 's' string'inin her bir karakterine (NUL karakteri hariç) 'f' fonksiyonunu uygular.
// 'f' fonksiyonu, parametre olarak karakterin indeksini ve karakterin kendisine bir
// pointer'ı (char *) alır. Bu, 'f' fonksiyonunun string'in karakterlerini
// doğrudan (yerinde) değiştirmesine olanak tanır.
// Fonksiyon bir şey döndürmez (void).
void ft_striteri(char *s, void (*f)(unsigned int, char *))
{
    size_t i; // String üzerinde gezinmek ve 'f' fonksiyonuna indeks sağlamak için sayaç.

    // 1. Girdi string 's' veya fonksiyon pointer 'f' NULL mu diye kontrol et.
    //    (Not: Mevcut implementasyon sadece 's'yi kontrol ediyor. İdealde 'f' de kontrol edilmeli.)
    if (!s) // Eğer string 's' NULL ise, işlem yapma ve fonksiyondan çık.
        return;
    // if (!s || !f) return; // Daha güvenli bir kontrol.

    // 2. String üzerinde gezinmek için sayacı ayarla.
    //    Döngüde ++i kullanılacağı için -1 ile başlanır.
    //    Bu sayede döngünün ilk iterasyonunda 'i' 0 olur.
    i = -1;

    // 3. 's' string'inin her bir karakteri için 'f' fonksiyonunu çağır.
    //    s[++i] ifadesi, önce 'i'yi artırır (ilk adımda 0 yapar), sonra s[i]'nin
    //    NUL ('\0') olup olmadığını kontrol eder. Döngü, NUL karakterine
    //    ulaşılana kadar devam eder (NUL karakteri İŞLENMEZ).
    while (s[++i] != '\0') // veya while (s[i]) (eğer i başlangıçta 0 ise ve sonda artırılıyorsa)
    {
        // 'f' fonksiyonunu çağır:
        //   - İlk argüman: mevcut karakterin indeksi (i).
        //   - İkinci argüman: mevcut karakterin adresi (&s[i]).
        //     Bu, 'f' fonksiyonunun s[i] karakterini doğrudan (yerinde)
        //     değiştirmesine olanak tanır.
        f(i, &s[i]);
    }
    // Fonksiyon void olduğu için bir dönüş değeri yoktur.
    // 's' string'i, 'f' fonksiyonu tarafından yapılan değişiklikleri yansıtır.
}