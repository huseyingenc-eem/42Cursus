# Philosophers Projesi - Modüler ve Norm Uyumlu Uygulama Kılavuzu

Bu kılavuz, **42 Norm kurallarına** (max 25 satır/fonksiyon, max 5 fonksiyon/dosya, max 4 parametre) ve **Leak-Proof (Sızdırmaz)** mimariye göre güncellenmiştir.

## Temel Strateji: "Tek Büyük Struct" (The Big Struct)

Tüm karmaşayı ve parametre sınırını aşmak için, her şeyi kapsayan tek bir `t_table` (veya `t_data`) yapısı kullanacağız.

- Böylece fonksiyonlara 4-5 tane ayrı değişken göndermek yerine sadece `t_table` göndererek **4 parametre kuralını** kolayca aşarsınız.
- Her şey bu yapının içinde olduğu için, temizlik zamanı geldiğinde sadece bu yapıyı fonksiyona yollayıp "her şeyi temizle" diyebilirsiniz.

---

## Dizin ve Dosya Yapısı

```
philo/
├── include/
│   └── philo.h           # Tüm structlar ve prototipler
├── src/
│   ├── main.c            # Başlatıcı
│   ├── init.c            # Veri ve Mutex başlatma (Malloc burada)
│   ├── threads.c         # Thread oluşturma ve birleştirme (Join)
│   ├── routine.c         # Filozof döngüsü (Ye -> Uyu -> Düşün)
│   ├── actions.c         # Eylemler (Çatal al, Ye, Uyu...)
│   ├── monitor.c         # Ölüm kontrolü (Gözlemci)
│   ├── time.c            # Zaman fonksiyonları
│   ├── utils.c           # ft_atoi, hata yazdırma
│   └── cleanup.c         # TEK NOKTADAN Temizlik (Free & Destroy)
└── Makefile
```

---

## 1. Veri Yapıları (`include/philo.h`)

Hafıza yönetimini kolaylaştırmak için structları iç içe kullanacağız.

```c
typedef struct s_philo {
    int             id;
    int             meals_eaten;
    long long       last_meal_time;
    pthread_t       thread_id;
    pthread_mutex_t *left_fork;   // Sol çatalın adresi
    pthread_mutex_t *right_fork;  // Sağ çatalın adresi
    struct s_table  *table;       // Ana veriye erişim için geri işaretçi
} t_philo;

typedef struct s_table {
    long long       start_time;
    long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;
    int             philo_count;
    int             must_eat_count; // Opsiyonel (-1 ise yok)
    int             simulation_running; // Ölüm bayrağı
    pthread_mutex_t running_mutex;    // Bayrağı korumak için
    pthread_mutex_t print_mutex;      // Yazdırmayı korumak için
    pthread_mutex_t *forks;           // Çatal dizisi (malloc ile)
    t_philo         *philos;          // Filozof dizisi (malloc ile)
} t_table;
```

---

## 2. Modüler Dosya İçerikleri

### `src/cleanup.c` (Norm Dostu Temizlik)

Burada amaç, tek bir fonksiyon çağrısı ile her şeyi güvenle temizlemektir. Norm kuralı gereği (max 25 satır), gerekirse işlemi 2-3 küçük yardımcı fonksiyona bölebiliriz.

- `void destroy_mutexes(t_table *table)`:
  - Döngü ile `table->forks` dizisindeki tüm mutexleri yok et (`pthread_mutex_destroy`).
  - `print_mutex` ve `running_mutex`'i yok et.
- `void free_resources(t_table *table)`:
  - `if (table->forks)` -> `free(table->forks)`
  - `if (table->philos)` -> `free(table->philos)`
- `int error_cleanup(char *msg, t_table *table)`:
  - Bir hata olduğunda çağrılır. Önce hata mesajını yazar, sonra yukarıdaki temizlik fonksiyonlarını çağırır ve `1` (hata kodu) döndürür.

**Kullanım Mantığı:** `main` fonksiyonunda stack üzerinde bir `t_table table;` oluşturursunuz. Hata olursa veya program biterse sadece `cleanup(&table)` çağırırsınız.

### `src/init.c` (Başlatma)

Burada malloc kullanacağız. Tek bir noktada malloc yapmak takibi kolaylaştırır.

- `int init_data(t_table *table, char **av)`: Argümanları struct'a doldur.
- `int init_alloc(t_table *table)`:
  - `table->philos = malloc(...)`
  - `table->forks = malloc(...)`
  - Eğer malloc başarısız olursa hemen `error_cleanup` çağır ve çık.
- `int init_mutexes(t_table *table)`: Çatalları ve genel mutexleri `pthread_mutex_init` ile başlat.

### `src/main.c` (Yönetici)

Main fonksiyonu çok sade olmalı. Sadece fonksiyonları çağırmalı.

```c
int main(int ac, char **av)
{
    t_table table;

    if (ac != 5 && ac != 6)
        return (error_exit("Hatalı argüman sayısı"));
    if (init_data(&table, av) != 0) // Argümanları parse et
        return (1);
    if (init_alloc(&table) != 0) // Yer ayır
        return (1);
    if (init_mutexes(&table) != 0) // Mutexleri kur
        return (error_cleanup("Mutex hatası", &table));
    // ... Threadleri başlat ...
    // ... Temizlik yap ve çık ...
}
```

### `src/routine.c` (Limitleri Aşmak)

Bir filozofun yaşam döngüsü.

- `void *philo_routine(void *ptr)`:
  - Burada `t_philo *philo = (t_philo *)ptr;` alırsınız.
  - Artık `philo->table->time_to_die` gibi tüm verilere erişebilirsiniz. 4 parametre sınırına takılmazsınız çünkü tek parametre (`philo`) her şeye yeter!

### `src/actions.c` (Eylemler)

Norm uyumu için eylemleri ayırın.

- `void philo_eat(t_philo *philo)`: Yeme işlemi (çatal al, ye, bırak).
- `void philo_sleep_think(t_philo *philo)`: Uyuma ve düşünme.
  - Bu fonksiyonların hiçbirine `time_to_die` vs. göndermenize gerek yok, hepsi `philo->table` içinde var!

### `src/monitor.c` (Gözlemci)

- `int check_death(t_table *table)`: Herkes yaşıyor mu kontrol et.
- `int check_meals(t_table *table)`: Herkes doydu mu kontrol et.

---

## Norm İpuçları

1.  **25 Satır Kuralı:** Eğer bir fonksiyon uzarsa/karışırsa (örneğin init fonksiyonu), "yardımcı fonksiyon" (helper function) oluşturun.
    - Örnek: `init_mutexes` fonksiyonu çok uzunsa, `init_forks` ve `init_global_mutexes` diye ikiye bölün ve ana fonksiyondan bu ikisini çağırın.
2.  **5 Fonksiyon Kuralı:** Bir dosya (örn: `utils.c`) 5 fonksiyonu geçerse, `utils_2.c` diye yeni dosya açın. Dosya açmaktan korkmayın, modülerlik iyidir.
