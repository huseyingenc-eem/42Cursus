# Philosophers - Felsefenin bu kadar ölümcül olacağını hiç düşünmemiştim

## Özet
Bu projede, bir işlemin (process) thread'lenmesinin temellerini öğreneceksiniz. Thread (iş parçacığı) oluşturmayı ve mutex kullanımını keşfedeceksiniz.

**Sürüm:** 13.0

---

## İçindekiler
1. Giriş
2. Genel Talimatlar
3. Yapay Zeka (AI) Talimatları
4. Genel Bakış
5. Global Kurallar
6. Zorunlu Kısım
7. Readme Gereksinimleri
8. Bonus Kısım
9. Teslim ve Akran Değerlendirmesi

---

## Bölüm I: Giriş

Felsefe (Yunanca'dan, philosophia, kelimenin tam anlamıyla "bilgelik sevgisi"), varlık, bilgi, değerler, akıl, zihin ve dil ile ilgili genel ve temel soruların incelenmesidir. Bu tür sorular genellikle analiz edilmesi veya çözülmesi gereken problemler olarak çerçevelenir. Terim muhtemelen Pisagor (M.Ö. 570 - 495) tarafından türetilmiştir. Felsefi yöntemler arasında sorgulama, eleştirel tartışma, rasyonel argüman ve sistematik sunum yer alır.

Klasik felsefi sorular şunları içerir: Herhangi bir şey gerçekten bilinebilir ve kanıtlanabilir mi? En gerçek olan nedir? Filozoflar ayrıca daha pratik ve somut sorular da sorarlar: Yaşamanın en iyi yolu var mıdır? Adil olmak mı yoksa adaletsiz olmak mı (eğer yanına kar kalacaksa) daha iyidir? İnsanların özgür iradesi var mıdır?

Tarihsel olarak, 'felsefe' terimi herhangi bir bilgi birikimini ifade ediyordu. Antik Yunan filozofu Aristoteles'ten 19. yüzyıla kadar, "doğa felsefesi" astronomi, tıp ve fiziği kapsıyordu. Örneğin, Newton'un 1687 tarihli eseri, Doğa Felsefesinin Matematiksel İlkeleri, daha sonra bir fizik kitabı olarak sınıflandırıldı.

19\. yüzyılda, modern araştırma üniversitelerinin büyümesi, akademik felsefenin ve diğer disiplinlerin profesyonelleşmesine ve uzmanlaşmasına yol açtı. Modern çağda, geleneksel olarak felsefenin bir parçası olan bazı araştırmalar, psikoloji, sosyoloji, dilbilim ve ekonomi dahil olmak üzere ayrı akademik disiplinler haline geldi.

Sanat, bilim, politika veya diğer uğraşlarla yakından ilgili diğer araştırmalar felsefenin bir parçası olarak kaldı. Örneğin, güzellik nesnel midir yoksa öznel midir? Birçok bilimsel yöntem mi vardır yoksa sadece bir tane mi? Siyasi ütopya umutlu bir rüya mı yoksa umutsuz bir fantezi mi?

Akademik felsefenin başlıca alt alanları arasında metafizik ("gerçekliğin ve varlığın temel doğasıyla ilgili"), epistemoloji ("bilginin doğası ve temelleri [ve]... sınırları ve geçerliliği hakkında"), etik, estetik, siyaset felsefesi, mantık ve bilim felsefesi yer alır.

---

## Bölüm II: Genel Talimatlar

*   Projeniz C dilinde yazılmalıdır.
*   Projeniz Norm'a uygun olarak yazılmalıdır. Bonus dosyalarınız/fonksiyonlarınız varsa, bunlar da norm kontrolüne dahildir ve bir norm hatası varsa 0 alırsınız.
*   Fonksiyonlarınız, tanımsız davranışlar dışında beklenmedik bir şekilde (segmentation fault, bus error, double free, vb.) sonlanmamalıdır. Bu meydana gelirse, projeniz işlevsiz kabul edilecek ve değerlendirme sırasında 0 alacaktır.
*   Tüm heap tahsisli bellek gerektiğinde uygun şekilde serbest bırakılmalıdır. Bellek sızıntılarına (memory leaks) tolerans gösterilmeyecektir.
*   Konu gerektiriyorsa, kaynak dosyalarınızı -Wall, -Wextra ve -Werror bayraklarıyla, cc kullanarak derleyen bir Makefile göndermelisiniz. Ayrıca, Makefile'ınız gereksiz yeniden bağlama (relinking) yapmamalıdır.
*   Makefile'ınız en az $(NAME), all, clean, fclean ve re kurallarını içermelidir.
*   Projeniz için bonusları göndermek istiyorsanız, Makefile'ınıza projenin ana kısmında izin verilmeyen çeşitli başlıkları, kütüphaneleri veya fonksiyonları ekleyecek bir bonus kuralı dahil etmelisiniz. Bonuslar, konu aksi belirtilmedikçe _bonus.{c/h} dosyalarına yerleştirilmelidir. Zorunlu ve bonus kısımların değerlendirmesi ayrı ayrı yapılır.
*   Projeniz libft kullanmanıza izin veriyorsa, kaynaklarını ve ilgili Makefile'ını bir libft klasörüne kopyalamalısınız. Projenizin Makefile'ı, kütüphaneyi kendi Makefile'ını kullanarak derlemeli, ardından projeyi derlemelidir.
*   Bu çalışma gönderilmesi gerekmese ve notlandırılmayacak olsa bile, projeniz için test programları oluşturmanızı teşvik ediyoruz. Bu, size kendi çalışmanızı ve arkadaşlarınızın çalışmasını kolayca test etme fırsatı verecektir. Bu testleri özellikle savunmanız sırasında faydalı bulacaksınız. Gerçekten de, savunma sırasında kendi testlerinizi ve/veya değerlendirdiğiniz akranınızın testlerini kullanmakta özgürsünüz.
*   Çalışmanızı atanan Git deposuna gönderin. Sadece Git deposundaki çalışma değerlendirilecektir. Çalışmanızı notlandırmak için Deepthought atanmışsa, bu akran değerlendirmelerinizden sonra gerçekleşecektir. Deepthought'un notlandırması sırasında çalışmanızın herhangi bir bölümünde bir hata oluşursa, değerlendirme duracaktır.

---

## Bölüm III: Yapay Zeka (AI) Talimatları

**Bağlam**
Öğrenme yolculuğunuz sırasında, yapay zeka birçok farklı görevde yardımcı olabilir. Yapay zeka araçlarının çeşitli yeteneklerini keşfetmek ve çalışmalarınızı nasıl destekleyebileceklerini görmek için zaman ayırın. Ancak, bunlara her zaman dikkatli yaklaşın ve sonuçları eleştirel bir şekilde değerlendirin. Kod, dokümantasyon, fikirler veya teknik açıklamalar olsun, sorunuzun iyi oluşturulduğundan veya üretilen içeriğin doğru olduğundan asla tamamen emin olamazsınız. Akranlarınız, hatalardan ve kör noktalardan kaçınmanıza yardımcı olacak değerli bir kaynaktır.

**Ana mesaj**
☛ Tekrarlayan veya sıkıcı görevleri azaltmak için yapay zekayı kullanın.
☛ Gelecekteki kariyerinize fayda sağlayacak hem kodlama hem de kodlama dışı istem (prompt) becerilerini geliştirin.
☛ Ortak riskleri, önyargıları ve etik sorunları daha iyi öngörmek ve bunlardan kaçınmak için yapay zeka sistemlerinin nasıl çalıştığını öğrenin.
☛ Akranlarınızla çalışarak hem teknik hem de güç becerilerinizi (power skills) geliştirmeye devam edin.
☛ Sadece tamamen anladığınız ve sorumluluğunu alabileceğiniz yapay zeka tarafından üretilen içeriği kullanın.

**Öğrenci kuralları:**
*   Yapay zeka araçlarını keşfetmek ve nasıl çalıştıklarını anlamak için zaman ayırmalısınız, böylece bunları etik bir şekilde kullanabilir ve potansiyel önyargıları azaltabilirsiniz.
*   İstemde bulunmadan önce probleminiz üzerinde düşünmelisiniz — bu, doğru kelime dağarcığını kullanarak daha net, daha ayrıntılı ve daha alakalı istemler yazmanıza yardımcı olur.
*   Yapay zeka tarafından üretilen her şeyi sistematik olarak kontrol etme, gözden geçirme, sorgulama ve test etme alışkanlığını geliştirmelisiniz.
*   Her zaman akran değerlendirmesi (peer review) istemelisiniz — sadece kendi doğrulamanıza güvenmeyin.

**Aşama çıktıları:**
*   Hem genel amaçlı hem de alana özgü istem becerileri geliştirmek.
*   Yapay zeka araçlarının etkili kullanımıyla üretkenliğinizi artırmak.
*   Hesaplamalı düşünme, problem çözme, uyarlanabilirlik ve işbirliğini güçlendirmeye devam etmek.

**Yorumlar ve örnekler:**
*   Sınavlar, değerlendirmeler ve daha fazlası gibi gerçek anlayışı göstermeniz gereken durumlarla düzenli olarak karşılaşacaksınız. Hazırlıklı olun, hem teknik hem de kişilerarası becerilerinizi geliştirmeye devam edin.
*   Mantığınızı açıklamak ve akranlarınızla tartışmak genellikle anlayışınızdaki boşlukları ortaya çıkarır. Akran öğrenimini (peer learning) bir öncelik haline getirin.
*   Yapay zeka araçları genellikle sizin özel bağlamınızdan yoksundur ve genel yanıtlar verme eğilimindedir. Sizin ortamınızı paylaşan akranlarınız, daha alakalı ve doğru içgörüler sunabilir.
*   Yapay zekanın en olası cevabı üretme eğiliminde olduğu durumlarda, akranlarınız alternatif bakış açıları ve değerli nüanslar sağlayabilir. Onlara bir kalite kontrol noktası olarak güvenin.

✓ İyi uygulama:
Yapay zekaya soruyorum: "Bir sıralama fonksiyonunu nasıl test ederim?" Bana birkaç fikir veriyor. Bunları deniyorum ve sonuçları bir arkadaşımla gözden geçiriyorum. Yaklaşımı birlikte geliştiriyoruz.

✗ Kötü uygulama:
Yapay zekadan bütün bir fonksiyonu yazmasını istiyorum, projeme kopyalayıp yapıştırıyorum. Akran değerlendirmesi sırasında ne yaptığını veya nedenini açıklayamıyorum. Güvenilirliğimi kaybediyorum — ve projeden kalıyorum.

✓ İyi uygulama:
Bir ayrıştırıcı (parser) tasarlamaya yardımcı olması için yapay zekayı kullanıyorum. Sonra mantığı bir arkadaşımla adım adım inceliyorum. İki hata yakalıyoruz ve birlikte yeniden yazıyoruz — daha iyi, daha temiz ve tamamen anlaşılmış.

✗ Kötü uygulama:
Copilot'un projemin önemli bir parçası için kodumu oluşturmasına izin veriyorum. Derleniyor, ancak pipe'ları nasıl yönettiğini açıklayamıyorum. Değerlendirme sırasında gerekçelendirmeyi başaramıyorum ve projeden kalıyorum.

---

## Bölüm IV: Genel Bakış

Bu ödevde başarılı olmak için bilmeniz gereken temel şeyler şunlardır:

*   Bir veya daha fazla filozof yuvarlak bir masada oturur. Masanın ortasında büyük bir kase spagetti vardır.
*   Filozoflar sırayla yemek yer, düşünür ve uyurlar.
    *   Yemek yerken ne düşünürler ne de uyurlar;
    *   düşünürken ne yemek yerler ne de uyurlar;
    *   ve elbette uyurken ne yemek yerler ne de düşünürler.
*   Masada çatallar da vardır. Filozof sayısı kadar çatal vardır.
*   Spagettiyi sadece tek çatal ile yemek pratik olmadığından, bir filozof yemek yemeden önce hem sağındaki hem de solundaki çatalı almalıdır.
*   Bir filozof yemeğini bitirdiğinde, çatallarını masaya geri koyar ve uyumaya başlar. Uyandığında tekrar düşünmeye başlar. Simülasyon, bir filozof açlıktan öldüğünde durur.
*   Her filozofun yemek yemesi gerekir ve asla aç kalmamalıdır.
*   Filozoflar birbirleriyle iletişim kurmazlar.
*   Filozoflar, başka bir filozofun ölmek üzere olup olmadığını bilmezler.
*   Söylemeye gerek yok, filozoflar ölmekten kaçınmalıdır!

---

## Bölüm V: Global Kurallar

Zorunlu kısım için bir program ve (eğer bonus kısmı yapmaya karar verirseniz) bonus kısım için başka bir program yazmalısınız. Her ikisi de aşağıdaki kurallara uymalıdır:

*   Global değişkenler yasaktır!
*   Program(lar)ınız aşağıdaki argümanları almalıdır:
    `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
    *   **number_of_philosophers (filozof_sayısı):** Filozof sayısı ve aynı zamanda çatal sayısı.
    *   **time_to_die (ölme_süresi) (milisaniye cinsinden):** Bir filozof, son yemeğinin başlangıcından veya simülasyonun başlangıcından itibaren `time_to_die` milisaniye içinde yemek yemeye başlamazsa ölür.
    *   **time_to_eat (yeme_süresi) (milisaniye cinsinden):** Bir filozofun yemek yemesi için geçen süre. Bu süre zarfında iki çatalı da ellerinde tutmaları gerekecektir.
    *   **time_to_sleep (uyuma_süresi) (milisaniye cinsinden):** Bir filozofun uyuyarak geçireceği süre.
    *   **number_of_times_each_philosopher_must_eat (her_filozofun_yemesi_gereken_miktar) (isteğe bağlı argüman):** Tüm filozoflar en az `number_of_times_each_philosopher_must_eat` kez yemek yemişse, simülasyon durur. Belirtilmezse, simülasyon bir filozof öldüğünde durur.
*   Her filozofun 1'den `number_of_philosophers`'a kadar değişen bir numarası vardır.
*   1 numaralı filozof, `number_of_philosophers` numaralı filozofun yanında oturur. N numaralı diğer herhangi bir filozof, N - 1 numaralı filozof ile N + 1 numaralı filozof arasında oturur.

**Programınızın logları hakkında:**

*   Bir filozofun herhangi bir durum değişikliği şu şekilde formatlanmalıdır:
    *   `timestamp_in_ms X has taken a fork` (ms_cinsinden_zaman_damgası X bir çatal aldı)
    *   `timestamp_in_ms X is eating` (ms_cinsinden_zaman_damgası X yemek yiyor)
    *   `timestamp_in_ms X is sleeping` (ms_cinsinden_zaman_damgası X uyuyor)
    *   `timestamp_in_ms X is thinking` (ms_cinsinden_zaman_damgası X düşünüyor)
    *   `timestamp_in_ms X died` (ms_cinsinden_zaman_damgası X öldü)
    *   `timestamp_in_ms`'i milisaniye cinsinden mevcut zaman damgasıyla ve `X`'i filozof numarasıyla değiştirin.
*   Görüntülenen bir durum mesajı başka bir mesajla karışmamalıdır.
*   Bir filozofun ölümünü duyuran mesaj, gerçek ölümünden sonraki 10 ms içinde görüntülenmelidir.
*   Tekrar ediyorum, filozoflar ölmekten kaçınmalıdır!

**Programınızda herhangi bir data race (veri yarışı) olmamalıdır.**

---

## Bölüm VI: Zorunlu Kısım

| Program Adı | philo |
| :--- | :--- |
| **Teslim Edilecek Dosyalar** | Makefile, *.h, *.c, philo/ dizininde |
| **Makefile** | NAME, all, clean, fclean, re |
| **Argümanlar** | number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] |
| **Harici Fonksiyonlar** | memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock |
| **Libft izinli mi** | Hayır |
| **Açıklama** | Thread'ler ve mutex'ler ile filozoflar |

Zorunlu kısım için özel kurallar şunlardır:

*   Her filozof ayrı bir thread olarak temsil edilmelidir.
*   Her filozof çiftinin arasında bir çatal vardır. Dolayısıyla, birden fazla filozof varsa, her filozofun sol tarafında bir çatal ve sağ tarafında bir çatal vardır. Sadece bir filozof varsa, sadece bir çatala erişimi olacaktır.
*   Filozofların çatalları kopyalamasını önlemek için, her çatalın durumunu bir mutex ile korumalısınız.

---

## Bölüm VII: Readme Gereksinimleri

Git deponuzun kökünde bir README.md dosyası sağlanmalıdır. Amacı, projeye aşina olmayan herkesin (akranlar, personel, işe alım uzmanları, vb.) projenin ne hakkında olduğunu, nasıl çalıştırılacağını ve konu hakkında daha fazla bilgiyi nerede bulacağını hızlı bir şekilde anlamasını sağlamaktır.

README.md en az şunları içermelidir:
*   İlk satır italik olmalı ve şöyle okunmalıdır: *This project has been created as part of the 42 curriculum by <giriş1>[, <giriş2>[, <giriş3>[...]]].*
*   Projenin amacını ve kısa bir genel bakışını içeren, projeyi net bir şekilde sunan bir “Açıklama” (Description) bölümü.
*   Derleme, kurulum ve/veya çalıştırma hakkında ilgili bilgileri içeren bir “Talimatlar” (Instructions) bölümü.
*   Konuyla ilgili klasik referansları (dokümantasyon, makaleler, eğitimler vb.) listeleyen, ayrıca yapay zekanın nasıl kullanıldığını açıklayan (hangi görevler ve projenin hangi kısımları için olduğunu belirten) bir “Kaynaklar” (Resources) bölümü.
*   Projeye bağlı olarak ek bölümler gerekebilir (örneğin, kullanım örnekleri, özellik listesi, teknik seçimler vb.).

README dosyanız İngilizce yazılmalıdır.

---

## Bölüm VIII: Bonus Kısım

| Program Adı | philo_bonus |
| :--- | :--- |
| **Teslim Edilecek Dosyalar** | Makefile, *.h, *.c, philo_bonus/ dizininde |
| **Makefile** | NAME, all, clean, fclean, re |
| **Argümanlar** | number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] |
| **Harici Fonksiyonlar** | memset, printf, malloc, free, write, fork, kill, exit, pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink |
| **Libft izinli mi** | Hayır |
| **Açıklama** | Süreçler (processes) ve semaforlar ile filozoflar |

Bonus kısmın programı, zorunlu programla aynı argümanları alır. Global kurallar bölümünün gerekliliklerine uymalıdır.

Bonus kısım için özel kurallar şunlardır:

*   Tüm çatallar masanın ortasına konur.
*   Bellekte durumları yoktur, ancak mevcut çatal sayısı bir semafor ile temsil edilir.
*   Her filozof ayrı bir süreç (process) olarak temsil edilmelidir. Ancak, ana süreç bir filozof gibi davranmamalıdır.

Bonus kısım, yalnızca zorunlu kısım MÜKEMMEL ise değerlendirilecektir. Mükemmel, zorunlu kısmın tamamen yapıldığı ve hatasız çalıştığı anlamına gelir. TÜM zorunlu gereksinimleri geçmediyseniz, bonus kısmınız hiç değerlendirilmeyecektir.

---

## Bölüm IX: Teslim ve akran değerlendirmesi

Ödevinizi her zamanki gibi Git deponuza gönderin. Savunma sırasında sadece deponuzun içindeki çalışma değerlendirilecektir. Doğru olduklarından emin olmak için dosyalarınızın isimlerini iki kez kontrol etmekten çekinmeyin.

*   Zorunlu kısım dizini: `philo/`
*   Bonus kısım dizini: `philo_bonus/`

Değerlendirme sırasında, bazen projede kısa bir değişiklik yapılması istenebilir. Bu, küçük bir davranış değişikliği, yazılacak veya yeniden yazılacak birkaç satır kod veya eklenmesi kolay bir özellik içerebilir. Bu adım her proje için geçerli olmasa da, değerlendirme yönergelerinde belirtilmişse buna hazırlıklı olmalısınız.

Bu adım, projenin belirli bir bölümünü gerçekten anlayıp anlamadığınızı doğrulamak içindir. Değişiklik, seçtiğiniz herhangi bir geliştirme ortamında (örneğin, normal kurulumunuz) gerçekleştirilebilir ve değerlendirmenin bir parçası olarak belirli bir zaman dilimi tanımlanmadıkça, birkaç dakika içinde yapılabilir olmalıdır. Örneğin, bir fonksiyonda veya komut dosyasında küçük bir güncelleme yapmanız, bir ekranı değiştirmeniz veya yeni bilgileri saklamak için bir veri yapısını ayarlamanız vb. istenebilir. Ayrıntılar (kapsam, hedef vb.) değerlendirme yönergelerinde belirtilecek ve aynı proje için bir değerlendirmeden diğerine değişebilecektir.
