# 📜 Philosophers — Proje Dokümantasyonu

> _I never thought philosophy would be so deadly._

---

## 📖 İçindekiler

1. [Proje Özeti](#-proje-özeti)
2. [Problem Tanımı — Dining Philosophers](#-problem-tanımı--dining-philosophers)
3. [Program Argümanları](#-program-argümanları)
4. [Genel Kurallar](#-genel-kurallar)
5. [Mandatory Part — Zorunlu Kısım](#-mandatory-part--zorunlu-kısım)
6. [İzin Verilen Fonksiyonlar (Mandatory)](#-i̇zin-verilen-fonksiyonlar-mandatory)
7. [Yasak ve Kısıtlamalar](#-yasak-ve-kısıtlamalar)
8. [Log Formatı](#-log-formatı)
9. [Bonus Part](#-bonus-part)
10. [İzin Verilen Fonksiyonlar (Bonus)](#-i̇zin-verilen-fonksiyonlar-bonus)
11. [Makefile Kuralları](#-makefile-kuralları)
12. [Norm Kuralları](#-norm-kuralları)
13. [README Gereksinimleri](#-readme-gereksinimleri)
14. [Değerlendirme ve Teslim](#-değerlendirme-ve-teslim)

---

## 🧠 Proje Özeti

| Alan                | Değer                             |
| ------------------- | --------------------------------- |
| **Proje Adı**       | `philo`                           |
| **Dil**             | C                                 |
| **Konu**            | Thread, Mutex, Process, Semaphore |
| **Versiyon**        | 13.0                              |
| **Mandatory Dizin** | `philo/`                          |
| **Bonus Dizin**     | `philo_bonus/`                    |

Bu projede bir **süreç içinde thread oluşturma** ve **mutex kullanımının** temellerini öğreneceksin. Bonus kısımda ise **process** ve **semaphore** kavramlarına geçiş yapılır.

---

## 🍝 Problem Tanımı — Dining Philosophers

Klasik bir eşzamanlılık (concurrency) problemidir:

```
        [F]
    P1      P5
  [F]        [F]
    P2      P4
        [F]
      P3
     [F]
```

### Senaryo

- Bir veya daha fazla filozof **yuvarlak bir masada** oturur.
- Masanın ortasında büyük bir **spagetti tabağı** vardır.
- Filozoflar sırayla **yemek yer**, **düşünür** ve **uyur**.
  - Yemek yerken → düşünmez ve uyumaz.
  - Düşünürken → yemek yemez ve uyumaz.
  - Uyurken → yemek yemez ve düşünmez.
- Masada **filozof sayısı kadar çatal** bulunur.
- Spagetti yemek için **iki çatal** (sağ ve sol) gereklidir.
- Filozof yemeğini bitirdiğinde çatalları **masaya geri bırakır** ve uyumaya başlar.
- Uyandığında **düşünmeye** başlar.
- Simülasyon, bir filozof **açlıktan öldüğünde** durur.

### Kritik Kurallar

| Kural                 | Açıklama                                                      |
| --------------------- | ------------------------------------------------------------- |
| **Açlıktan ölmemeli** | Her filozof yemek yemeli ve asla aç kalmamalı                 |
| **İletişim yok**      | Filozoflar birbirleriyle iletişim kuramaz                     |
| **Bilgi yok**         | Bir filozof, başka bir filozofun ölmek üzere olduğunu bilemez |
| **Ölümden kaçınmalı** | Filozoflar ölmekten kaçınmalıdır!                             |

---

## 🔢 Program Argümanları

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argüman                                     | Tip        | Zorunlu | Açıklama                                                                                                                 |
| ------------------------------------------- | ---------- | ------- | ------------------------------------------------------------------------------------------------------------------------ |
| `number_of_philosophers`                    | `int`      | ✅      | Filozof sayısı = çatal sayısı                                                                                            |
| `time_to_die`                               | `int` (ms) | ✅      | Son yemeğinden (veya simülasyon başlangıcından) itibaren bu süre içinde yemeye **başlamazsa** ölür                       |
| `time_to_eat`                               | `int` (ms) | ✅      | Yemek yeme süresi. Bu süre boyunca iki çatalı elinde tutmalı                                                             |
| `time_to_sleep`                             | `int` (ms) | ✅      | Uyuma süresi                                                                                                             |
| `number_of_times_each_philosopher_must_eat` | `int`      | ❌      | Tüm filozoflar bu sayıda yemek yediğinde simülasyon durur. Belirtilmezse simülasyon yalnızca bir filozof öldüğünde biter |

### Filozof Numaralandırma

- Her filozof **1'den `number_of_philosophers`'a** kadar numaralanır.
- Filozof **1**, filozof **number_of_philosophers**'ın yanında oturur.
- Filozof **N**, filozof **N-1** ve filozof **N+1** arasında oturur.

---

## 📏 Genel Kurallar

### Kesinlikle Uyulması Gerekenler

| #   | Kural                                                                                                       |
| --- | ----------------------------------------------------------------------------------------------------------- |
| 1   | Proje **C dilinde** yazılmalıdır                                                                            |
| 2   | **Global değişkenler YASAKTIR!**                                                                            |
| 3   | Proje **42 Norm**'a uygun yazılmalıdır                                                                      |
| 4   | Fonksiyonlar beklenmedik şekilde çökmemeli (segfault, bus error, double free vb.) — tanımsız davranış hariç |
| 5   | Heap'te ayrılan tüm bellek uygun şekilde **free** edilmelidir. Memory leak tolere edilmez                   |
| 6   | Programda **data race** (veri yarışı) bulunmamalıdır                                                        |
| 7   | Derleme bayrakları: `-Wall -Wextra -Werror` ve `cc` derleyicisi                                             |

---

## 🔧 Mandatory Part — Zorunlu Kısım

| Alan                 | Değer                                         |
| -------------------- | --------------------------------------------- |
| **Program Adı**      | `philo`                                       |
| **Teslim Dosyaları** | `Makefile`, `*.h`, `*.c` — `philo/` dizininde |
| **Libft**            | Kullanılamaz                                  |

### Mandatory Özel Kurallar

1. Her filozof **ayrı bir thread** olarak temsil edilmelidir.
2. Her filozof çifti arasında **bir çatal** bulunur:
   - Birden fazla filozof varsa → her filozofun solunda ve sağında birer çatal vardır.
   - **Tek filozof** varsa → yalnızca bir çatala erişimi olur (yemek yiyemez, ölür).
3. Çatalların durumunun çoğaltılmasını önlemek için her çatalın durumu **bir mutex ile korunmalıdır**.

---

## ✅ İzin Verilen Fonksiyonlar (Mandatory)

> ⚠️ **YALNIZCA aşağıdaki fonksiyonlar kullanılabilir. Başka hiçbir fonksiyon kullanılamaz!**

| Fonksiyon               | Header         | Açıklama                                       |
| ----------------------- | -------------- | ---------------------------------------------- |
| `memset`                | `<string.h>`   | Bellek bloğunu belirtilen değerle doldurur     |
| `printf`                | `<stdio.h>`    | Formatlanmış çıktı yazdırır                    |
| `malloc`                | `<stdlib.h>`   | Dinamik bellek ayırır                          |
| `free`                  | `<stdlib.h>`   | Dinamik belleği serbest bırakır                |
| `write`                 | `<unistd.h>`   | Dosya tanımlayıcısına yazar                    |
| `usleep`                | `<unistd.h>`   | Mikrosaniye cinsinden uyur                     |
| `gettimeofday`          | `<sys/time.h>` | Geçerli zamanı mikrosaniye hassasiyetiyle alır |
| `pthread_create`        | `<pthread.h>`  | Yeni bir thread oluşturur                      |
| `pthread_detach`        | `<pthread.h>`  | Thread'i ayırır (detach eder)                  |
| `pthread_join`          | `<pthread.h>`  | Thread'in bitmesini bekler                     |
| `pthread_mutex_init`    | `<pthread.h>`  | Mutex başlatır                                 |
| `pthread_mutex_destroy` | `<pthread.h>`  | Mutex'i yok eder                               |
| `pthread_mutex_lock`    | `<pthread.h>`  | Mutex'i kilitler                               |
| `pthread_mutex_unlock`  | `<pthread.h>`  | Mutex kilidini açar                            |

### Fonksiyon Prototipleri (Referans)

```c
// Bellek
void *memset(void *s, int c, size_t n);
void *malloc(size_t size);
void  free(void *ptr);

// I/O
int    printf(const char *format, ...);
ssize_t write(int fd, const void *buf, size_t count);

// Zaman
int    usleep(useconds_t usec);
int    gettimeofday(struct timeval *tv, struct timezone *tz);

// Thread
int    pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                      void *(*start_routine)(void *), void *arg);
int    pthread_detach(pthread_t thread);
int    pthread_join(pthread_t thread, void **retval);

// Mutex
int    pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int    pthread_mutex_destroy(pthread_mutex_t *mutex);
int    pthread_mutex_lock(pthread_mutex_t *mutex);
int    pthread_mutex_unlock(pthread_mutex_t *mutex);
```

---

## 🚫 Yasak ve Kısıtlamalar

| #   | Yasak                                                                                               |
| --- | --------------------------------------------------------------------------------------------------- |
| 1   | **Global değişken** kullanımı kesinlikle yasaktır                                                   |
| 2   | Yukarıda listelenen fonksiyonlar **dışında** hiçbir harici fonksiyon kullanılamaz                   |
| 3   | **libft** kullanılamaz                                                                              |
| 4   | **Data race** (veri yarışı) bulunmamalıdır                                                          |
| 5   | Norm hataları durumunda proje **0** puan alır                                                       |
| 6   | Beklenmedik çökmeler (**segfault**, **bus error**, **double free**) durumunda proje **0** puan alır |
| 7   | **Memory leak** tolere edilmez                                                                      |

---

## 📋 Log Formatı

Her filozof durum değişikliği aşağıdaki formatta yazdırılmalıdır:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

| Alan              | Açıklama                                   |
| ----------------- | ------------------------------------------ |
| `timestamp_in_ms` | Milisaniye cinsinden geçerli zaman damgası |
| `X`               | Filozof numarası (1'den başlar)            |

### Log Kuralları

| #   | Kural                                                                                      |
| --- | ------------------------------------------------------------------------------------------ |
| 1   | Mesajlar birbiriyle **örtüşmemeli** (overlap olmamalı)                                     |
| 2   | Ölüm mesajı, filozofun gerçek ölümünden itibaren **en fazla 10 ms** içinde gösterilmelidir |
| 3   | Filozoflar ölmekten kaçınmalıdır!                                                          |

### Örnek Çıktı

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
400 1 is thinking
400 2 is sleeping
...
```

---

## 🌟 Bonus Part

| Alan                 | Değer                                               |
| -------------------- | --------------------------------------------------- |
| **Program Adı**      | `philo_bonus`                                       |
| **Teslim Dosyaları** | `Makefile`, `*.h`, `*.c` — `philo_bonus/` dizininde |
| **Libft**            | Kullanılamaz                                        |

### Bonus Özel Kuralları

| #   | Kural                                                                                      |
| --- | ------------------------------------------------------------------------------------------ |
| 1   | Tüm çatallar **masanın ortasına** konur                                                    |
| 2   | Çatalların bellekte durumu yoktur; mevcut çatal sayısı bir **semaphore** ile temsil edilir |
| 3   | Her filozof **ayrı bir process** olarak temsil edilmelidir                                 |
| 4   | Ana (main) process bir filozof olarak **davranmamalıdır**                                  |

> ⚠️ **Bonus kısım YALNIZCA mandatory kısım MÜKEMMEL ise değerlendirilir.**
> Mükemmel = Mandatory kısım eksiksiz yapılmış ve hatasız çalışıyor.

---

## ✅ İzin Verilen Fonksiyonlar (Bonus)

> ⚠️ **YALNIZCA aşağıdaki fonksiyonlar kullanılabilir. Başka hiçbir fonksiyon kullanılamaz!**

| Fonksiyon        | Header          | Açıklama                                               |
| ---------------- | --------------- | ------------------------------------------------------ |
| `memset`         | `<string.h>`    | Bellek bloğunu belirtilen değerle doldurur             |
| `printf`         | `<stdio.h>`     | Formatlanmış çıktı yazdırır                            |
| `malloc`         | `<stdlib.h>`    | Dinamik bellek ayırır                                  |
| `free`           | `<stdlib.h>`    | Dinamik belleği serbest bırakır                        |
| `write`          | `<unistd.h>`    | Dosya tanımlayıcısına yazar                            |
| `usleep`         | `<unistd.h>`    | Mikrosaniye cinsinden uyur                             |
| `gettimeofday`   | `<sys/time.h>`  | Geçerli zamanı mikrosaniye hassasiyetiyle alır         |
| `fork`           | `<unistd.h>`    | Yeni bir child process oluşturur                       |
| `kill`           | `<signal.h>`    | Bir process'e sinyal gönderir                          |
| `exit`           | `<stdlib.h>`    | Process'i sonlandırır                                  |
| `pthread_create` | `<pthread.h>`   | Yeni bir thread oluşturur                              |
| `pthread_detach` | `<pthread.h>`   | Thread'i ayırır                                        |
| `pthread_join`   | `<pthread.h>`   | Thread'in bitmesini bekler                             |
| `waitpid`        | `<sys/wait.h>`  | Child process'in bitmesini bekler                      |
| `sem_open`       | `<semaphore.h>` | İsimli semaphore açar/oluşturur                        |
| `sem_close`      | `<semaphore.h>` | Semaphore'u kapatır                                    |
| `sem_post`       | `<semaphore.h>` | Semaphore değerini artırır (sinyal gönderir)           |
| `sem_wait`       | `<semaphore.h>` | Semaphore değeri > 0 olana kadar bekler, sonra azaltır |
| `sem_unlink`     | `<semaphore.h>` | İsimli semaphore'u siler                               |

### Bonus Fonksiyon Prototipleri (Referans)

```c
// Process
pid_t   fork(void);
int     kill(pid_t pid, int sig);
void    exit(int status);
pid_t   waitpid(pid_t pid, int *status, int options);

// Semaphore
sem_t  *sem_open(const char *name, int oflag, ...);
int     sem_close(sem_t *sem);
int     sem_post(sem_t *sem);
int     sem_wait(sem_t *sem);
int     sem_unlink(const char *name);
```

---

## 🔨 Makefile Kuralları

Makefile aşağıdaki kurallara uymalıdır:

| Kural     | Zorunlu         | Açıklama                                           |
| --------- | --------------- | -------------------------------------------------- |
| `$(NAME)` | ✅              | Programı derler                                    |
| `all`     | ✅              | Programı derler                                    |
| `clean`   | ✅              | Obje dosyalarını siler                             |
| `fclean`  | ✅              | Obje dosyalarını ve çalıştırılabilir dosyayı siler |
| `re`      | ✅              | `fclean` + `all` yapar                             |
| `bonus`   | ❌ (bonus için) | Bonus dosyaları derler                             |

### Derleme Gereksinimleri

```makefile
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
# Gereksiz relinking yapılmamalıdır!
```

> ⚠️ Makefile **gereksiz relinking** yapmamalıdır (kaynak dosya değişmediğinde yeniden derleme olmamalı).

---

## 📐 Norm Kuralları

42 Norm'a uyulması zorunludur. Başlıca kurallar:

| Kural                   | Açıklama                                        |
| ----------------------- | ----------------------------------------------- |
| Fonksiyon uzunluğu      | Maksimum **25 satır** (süslü parantezler hariç) |
| Fonksiyon parametreleri | Maksimum **4 parametre**                        |
| Değişken bildirimi      | Fonksiyon başında, boş satırdan sonra kod       |
| Satır uzunluğu          | Maksimum **80 karakter**                        |
| Bir satırda bir bildiri | Her satırda yalnızca bir değişken bildirimi     |
| Dosya başına fonksiyon  | Maksimum **5 fonksiyon**                        |
| `for` döngüsü           | **Yasak**                                       |
| Açıklama (comment)      | Fonksiyon içinde **yasak**                      |
| Header koruması         | Her `.h` dosyasında **include guard** olmalı    |

> Norm kontrolü için: `norminette` komutu kullanılır.

---

## 📄 README Gereksinimleri

`README.md` dosyası Git repository'nin **kök dizininde** bulunmalıdır.

### Zorunlu İçerik

| Bölüm            | Açıklama                                                                                  |
| ---------------- | ----------------------------------------------------------------------------------------- |
| **İlk satır**    | İtalik olmalı: _This project has been created as part of the 42 curriculum by \<login\>._ |
| **Description**  | Projenin amacı ve kısa genel bakış                                                        |
| **Instructions** | Derleme, kurulum ve/veya çalıştırma bilgileri                                             |
| **Resources**    | Konuyla ilgili kaynaklar + AI'ın hangi görevlerde kullanıldığının açıklaması              |

> README **İngilizce** yazılmalıdır.

---

## 📦 Değerlendirme ve Teslim

### Dizin Yapısı

```
.
├── philo/              ← Mandatory part
│   ├── Makefile
│   ├── *.h
│   └── *.c
│
├── philo_bonus/        ← Bonus part (opsiyonel)
│   ├── Makefile
│   ├── *.h
│   └── *.c
│
└── README.md
```

### Teslim Kuralları

| #   | Kural                                                                     |
| --- | ------------------------------------------------------------------------- |
| 1   | Atanan **Git repository**'sine teslim edilmelidir                         |
| 2   | Yalnızca repository içindeki çalışma değerlendirilir                      |
| 3   | Dosya adlarını **tekrar kontrol et**                                      |
| 4   | Değerlendirme sırasında **küçük kod değişiklikleri** istenebilir          |
| 5   | Bu değişiklikler birkaç dakika içinde yapılabilecek kadar basit olacaktır |

### Değerlendirme Sırası

1. Peer evaluation (Akran değerlendirmesi)
2. Deepthought (Otomatik değerlendirme) — herhangi bir bölümde hata varsa değerlendirme durur

---

## 🧪 Test Senaryoları (Önerilen)

Aşağıdaki test komutları projenin doğruluğunu kontrol etmek için kullanılabilir:

```bash
# Tek filozof — ölmeli (sadece 1 çatal var)
./philo 1 800 200 200

# Hiç kimse ölmemeli
./philo 5 800 200 200

# Hiç kimse ölmemeli
./philo 4 410 200 200

# Bir filozof ölmeli
./philo 4 310 200 100

# Yemek sayısı limiti — herkes 7 kez yemek yedikten sonra durmalı
./philo 5 800 200 200 7

# Geçersiz argümanlar
./philo -5 800 200 200
./philo 5 -800 200 200
./philo 0 800 200 200
```

---

## 📚 Faydalı Kaynaklar

| Kaynak                                  | Link                                                              |
| --------------------------------------- | ----------------------------------------------------------------- |
| Dining Philosophers Problem (Wikipedia) | [Link](https://en.wikipedia.org/wiki/Dining_philosophers_problem) |
| POSIX Threads Programming               | [Link](https://computing.llnl.gov/tutorials/pthreads/)            |
| Mutex vs Semaphore                      | [Link](https://www.geeksforgeeks.org/mutex-vs-semaphore/)         |
| `man pthread_create`                    | Terminal'de `man pthread_create`                                  |
| `man pthread_mutex_lock`                | Terminal'de `man pthread_mutex_lock`                              |
| `man sem_open`                          | Terminal'de `man sem_open`                                        |
| `man usleep`                            | Terminal'de `man usleep`                                          |
| `man gettimeofday`                      | Terminal'de `man gettimeofday`                                    |
