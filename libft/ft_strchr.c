// strchr fonksiyonu, 's' string'i içinde 'c' karakterinin ilk geçtiği yeri arar.
// Bulunursa o konuma bir pointer, bulunamazsa NULL döndürür.
char *strchr(const char *s, int c)
{
    // String boyunca karakterleri kontrol etmek için sonsuz bir döngü başlat.
    // Döngü, karakter bulunduğunda veya string'in sonuna ulaşıldığında içeriden sonlandırılacak.
    while (1)
    {
        // 1. Mevcut karakteri kontrol et:
        //    's' pointer'ının gösterdiği mevcut karakter, aranan 'c' karakterine eşit mi?
        //    'c' (int) explicit olarak (char)'a dönüştürülür, çünkü karşılaştırma char seviyesindedir.
        if (*s == (char)c)
            // Eğer eşitse, karakter bulunmuştur. 's' pointer'ını (char * türüne dönüştürülmüş olarak) döndür.
            // const char * olan s'nin char * olarak döndürülmesi, standart strchr davranışıdır;
            // bu, bulunan karakterin olduğu yerden string'in modifiye edilebilir bir parçasını işaret eder.
            return ((char *)s);

        // 2. String sonu kontrolü:
        //    Eğer mevcut karakter NUL sonlandırıcı ('\0') ise, string'in sonuna gelinmiştir.
        //    Bu noktaya gelinmişse ve aranan karakter ('c') önceki if'te bulunamamışsa,
        //    'c' karakteri string'de yok demektir.
        //    Not: Eğer aranan karakter 'c' zaten '\0' ise, bu durum bir önceki 'if' koşulunda yakalanır
        //    ve '\0' karakterine bir pointer döndürülür. Bu 'if' bloğu, '\0' olmayan bir 'c'
        //    aranırken string sonuna gelindiğinde çalışır.
        if (*s == '\0')
            return (NULL); // Karakter bulunamadı, NULL döndür.

        // 3. Bir sonraki karaktere geç:
        //    Eğer karakter bulunamadıysa ve string sonuna gelinmediyse,
        //    's' pointer'ını bir sonraki karaktere ilerlet.
        s++;
    }
}