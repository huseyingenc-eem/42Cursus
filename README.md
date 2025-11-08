<div align="center">
  <img src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&weight=700&size=28&duration=3500&pause=900&color=00B8A9&center=true&vCenter=true&width=720&lines=H%C3%BCseyin+Gen%C3%A7;42+Okulları+Cursus+Projeleri" alt="Typing SVG" />
</div>

<p align="center">
  <a href="https://github.com/huseyingenc-eem">
    <img src="https://img.shields.io/badge/GitHub-huseyingenc--eem-181717?style=for-the-badge&logo=github&logoColor=white" alt="GitHub"/>
  </a>
  <a href="https://profile.intra.42.fr/users/hgenc">
    <img src="https://img.shields.io/badge/42_Intra-hgenc-00B8A9?style=for-the-badge&logo=42&logoColor=white" alt="42 Intra"/>
  </a>
  <a href="https://www.linkedin.com/in/huseyingenceem/">
    <img src="https://img.shields.io/badge/LinkedIn-H%C3%BCseyin_Gen%C3%A7-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white" alt="LinkedIn"/>
  </a>
</p>

---

## Hakkında (42 Ağı)
**42**; peer-to-peer (akran tabanlı), proje odaklı, öz-yönetimli bir yazılım okulları ağıdır. Bu depo, 42 yolculuğumda (başlangıç: **42 Kocaeli**) tamamladığım projeleri ve her projede geliştirdiğim becerileri özetler. İleride başka diller/teknolojiler eklendikçe README çok dilli hâle getirilecektir.

---

## 📁 Projeler

> Bu bölüm, 42 Cursus sürecinde tamamlanan projelerin **net açıklamaları** ve **kazanımları** ile birlikte gelir. Her başlığın yanında küçük bir **PDF** simgesi bulunmaktadır; açıklamaların altında **Kodu Gör** butonu ve yanına **tamamlanma yüzdesi** yer alır.

---

### **Libft** <a href="./PDF/libft_subject.pdf" title="Subject PDF">📄</a>
C dilinde en sık kullanılan fonksiyonların (ör. `memset`, `strlen`, `atoi`, `calloc`, `strlcpy`) **sıfırdan** yazıldığı bir temel kütüphane çalışmasıdır. Hedef; **bellek yönetimi**, **işaretçi aritmetiği** ve **string işlemlerinde** ustalaşmak, aynı zamanda **Makefile** ve modüler geliştirme disiplini kazanmaktır.  
**Kazanımlar:** Statik/dinamik bellek ayrımı, `malloc/free` sorumluluğu, güvenli kopyalama ve ayırma rutinleri, norm kurallarına uygun fonksiyon tasarımı; ileri projelerde tekrar kullanılabilir **`libft.a`** altyapısının kurulması.

<p align="center">
  <a href="./libft/"><img src="https://img.shields.io/badge/Kodu_G%C3%B6r-181717?style=for-the-badge&logo=github&logoColor=white" alt="code"></a>
  <img src="https://img.shields.io/badge/Tamamlanma-██████████%20100%25-00B8A9?style=for-the-badge" alt="completion"/>
</p>

---

### **get_next_line** <a href="./PDF/get_next_line_subject.pdf" title="Subject PDF">📄</a>
Bir **dosya tanımlayıcısından** her çağrıda **yalnızca bir satır** döndüren fonksiyonun geliştirilmesi. Odak noktaları: `read()` ile **buffer yönetimi**, **satır sonu** yakalama, **artık verinin** bir sonraki çağrıya devri ve **`static` değişkenin** kapsam/ömür davranışı.  
**Kazanımlar:** Akış kontrollü okuma, çoklu dosya desteği (multi-FD) stratejileri, bellek sızıntısını önleyici desenler, hatalı/edge-case girişler için dayanıklı implementasyon.

<p align="center">
  <a href="./get_next_line/"><img src="https://img.shields.io/badge/Kodu_G%C3%B6r-181717?style=for-the-badge&logo=github&logoColor=white" alt="code"></a>
  <img src="https://img.shields.io/badge/Tamamlanma-██████████%20100%25-00B8A9?style=for-the-badge" alt="completion"/>
</p>

---

### **ft_printf** <a href="./PDF/ft_printf.pdf" title="Subject PDF">📄</a>
Standart `printf()` işlevinin çekirdek formatlayıcılarının (`cspdiuxX%`) yeniden yazımıdır. **Variadic** çağrılar (`stdarg.h`) ile tip güvenliği, **taban dönüşümleri** ve **adres/işaretçi gösterimleri** ele alınır.  
**Kazanımlar:** Biçim çözücü (parser) tasarımı, çıktı tamponlama/akış mantığı, taşma/negatif durumları için sınır koşulları, test güdümlü kontrol çıktıları ve hata toleranslı API tasarımı.

<p align="center">
  <a href="./ft_printf/"><img src="https://img.shields.io/badge/Kodu_G%C3%B6r-181717?style=for-the-badge&logo=github&logoColor=white" alt="code"></a>
  <img src="https://img.shields.io/badge/Tamamlanma-██████████%20100%25-00B8A9?style=for-the-badge" alt="completion"/>
</p>

---

### **Minitalk** <a href="./PDF/2-minitalk.pdf" title="Subject PDF">📄</a>
**UNIX sinyalleri** (`SIGUSR1`, `SIGUSR2`) ile istemci–sunucu arasında **bit seviyesinde** metin aktarımı. Sinyal gecikmeleri, paketleme (bit-to-char), **PID** ile adresleme ve **asenkron** davranış başlıca konulardır.  
**Kazanımlar:** Sinyal yakalama/kuyruklama mantığı, basit protokol tasarımı, süreçler arası minimal haberleşme, sistem çağrılarının (syscalls) dikkatli zamanlaması.

<p align="center">
  <a href="./minitalk/"><img src="https://img.shields.io/badge/Kodu_G%C3%B6r-181717?style=for-the-badge&logo=github&logoColor=white" alt="code"></a>
  <img src="https://img.shields.io/badge/Tamamlanma-██████████%20100%25-00B8A9?style=for-the-badge" alt="completion"/>
</p>

---

### **so_long** <a href="./PDF/So_Long.pdf" title="Subject PDF">📄</a>
`MiniLibX` ile **2D tile-based** oyun. Harita (map) parsing, **sprite/doku** çizimi, **çarpışma**, **toplanabilir** öğeler ve **çıkış** koşulları; olay (event) dinleme ve oyun döngüsü yönetimiyle birlikte uygulanır.  
**Kazanımlar:** Render döngüsü, tuş/olay işleme, path-check/validasyon (harita kapalı alan kontrolü), performans/frametime farkındalığı ve basit kaynak yönetimi.

<p align="center">
  <a href="./so_long/"><img src="https://img.shields.io/badge/Kodu_G%C3%B6r-181717?style=for-the-badge&logo=github&logoColor=white" alt="code"></a>
  <img src="https://img.shields.io/badge/Tamamlanma-██████████%20100%25-00B8A9?style=for-the-badge" alt="completion"/>
</p>

---

### **push_swap** <a href="./PDF/push_swap_subject.pdf" title="Subject PDF">📄</a>
İki yığın (a/b) ve kısıtlı komut setiyle **minimum hamlede** sıralama. Küçük/orta/büyük girdi setleri için farklı stratejiler, **döndürme/ters döndürme** kombinasyonları ve **maliyet (cost) hesapları**yla verimlilik sağlanır.  
**Kazanımlar:** Yığın soyutlaması, hamle optimizasyonu, karmaşıklık analizi, heuristik yaklaşım tasarımı, güvenli giriş ayrıştırma ve hata yönetimi.

<p align="center">
  <a href="./push_swap/"><img src="https://img.shields.io/badge/Kodu_G%C3%B6r-181717?style=for-the-badge&logo=github&logoColor=white" alt="code"></a>
  <img src="https://img.shields.io/badge/Tamamlanma-██████████%20100%25-00B8A9?style=for-the-badge" alt="completion"/>
</p>

---

## 🧾 Proje Puanları (Tam Genişlik Tablo)

| Proje             | Rank | Durum        | Puan    | Odak / Not                         |
|-------------------|:----:|:------------:|:-------:|------------------------------------|
| **Libft**         | 00   | ✅ Tamamlandı | 100/100 | Bellek, pointer, string            |
| **get_next_line** | 00   | ✅ Tamamlandı | 100/100 | `read()`, buffer, `static`         |
| **ft_printf**     | 00   | ✅ Tamamlandı | 100/100 | `stdarg`, biçimlendirme            |
| **Minitalk**      | 01   | ✅ Tamamlandı | 100/100 | Sinyaller, PID, async              |
| **so_long**       | 01   | ✅ Tamamlandı | 100/100 | MiniLibX, input, çarpışma          |
| **push_swap**     | 02   | ✅ Tamamlandı | 100/100 | Algoritma, optimizasyon            |


