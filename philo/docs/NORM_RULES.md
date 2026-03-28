# 📏 42 Norm Kuralları — Philosophers

> Aşağıdaki kurallar `norminette` tarafından denetlenir. Norm hatası = **0 puan**.

---

## Genel Kurallar

| #   | Kural                    | Detay                                                  |
| --- | ------------------------ | ------------------------------------------------------ |
| 1   | Satır uzunluğu           | Maksimum**80 karakter**                                |
| 2   | Dosya başına fonksiyon   | Maksimum**5 fonksiyon**                                |
| 3   | Fonksiyon uzunluğu       | Maksimum**25 satır** (süslü parantezler hariç)         |
| 4   | Parametre sayısı         | Fonksiyon başına maksimum**4 parametre**               |
| 5   | Değişken bildirimi       | Fonksiyon başında, tanımlamadan önce boş satır         |
| 6   | Bir satırda bir bildirim | Her satırda yalnızca**bir** değişken bildirimi         |
| 7   | Yorum                    | Fonksiyon**içinde** yorum satırı **yasaktır**          |
| 8   | `for` döngüsü            | **Yasaktır**, `while` kullanılmalıdır                  |
| 9   | Header guard             | Her `.h` dosyasında `#ifndef` / `#define` / `#endif`   |
| 10  | 42 Header                | Her dosyanın başında 42 header'ı bulunmalıdır          |
| 11  | Girintileme              | **Tab** ile yapılmalıdır (space değil)                 |
| 12  | Boşluk                   | Satır sonunda boşluk (trailing whitespace) olmamalıdır |

## Naming Convention

| Tür          | Format             | Örnek               |
| ------------ | ------------------ | ------------------- |
| Fonksiyon    | `snake_case`       | `ft_check_death`    |
| Değişken     | `snake_case`       | `time_to_die`       |
| Struct       | `s_` prefix        | `s_philo`, `s_data` |
| Typedef      | `t_` prefix        | `t_philo`, `t_data` |
| Enum         | `e_` prefix        | `e_state`           |
| Macro/Define | `UPPER_SNAKE_CASE` | `MAX_PHILO`         |

## Norm Kontrolü

```bash
# Tüm dosyaları kontrol et
norminette philo/

# Belirli bir dosyayı kontrol et
norminette philo/src/main.c
```

## Yaygın Norm Hataları

```c
// ❌ YANLIŞ — for döngüsü yasak
for (int i = 0; i < n; i++)

// ✅ DOĞRU — while kullan
i = -1;
while (++i < n)
{
    // ...
}

// ❌ YANLIŞ — birden fazla değişken tek satırda
int     a, b, c;

// ✅ DOĞRU — her biri ayrı satırda
int     a;
int     b;
int     c;

// ❌ YANLIŞ — 4'ten fazla parametre
void    func(int a, int b, int c, int d, int e);

// ✅ DOĞRU — struct kullanarak parametre azalt
void    func(t_data *data);
```
