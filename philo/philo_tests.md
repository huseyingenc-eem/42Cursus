# 42 Philosophers Tester Kapsamındaki Test Senaryoları

Tester script'inden (test.sh) alınan tüm test vakaları aşağıdadır. "Live" = kimse ölmemeli, "Die" = simülasyon bir filozofun ölümüyle durmalı.

> [!TIP]
> Sondaki argüman (yemek yeme sayısı limiti) tester'da varsayılan olarak `10` alınmıştır. Elle çalıştırırken isterseniz `10` ekleyebilirsiniz veya bırakabilirsiniz.

### 📌 Mandatory (Zorunlu) Testler

| Test Komutu (Elle Çalıştırmak İçin) | Beklenen Sonuç | Tester Komutu |
| :--- | :--- | :--- |
| `./philo 1 800 200 200 10` | 💀 Biri ölmeli (Tek filozof çatalı alır, açlıktan ölür) | `die 1 800 200 200 10` |
| `./philo 5 800 200 200 7` | 🟢 Yaşamalılar (Herkes 7 kez yedikten sonra başarılı çıkış) | `live 5 800 200 200 7` |
| `./philo 4 410 200 200 10` | 🟢 Yaşamalılar | `live 4 410 200 200 10` |
| `./philo 4 310 200 100 10` | 💀 Biri ölmeli (`time_to_die` düşük - 310ms) | `die 4 310 200 100 10` |

---

### 🟢 Tek Sayıda Filozof - Yaşamalı

| Test Komutu | Beklenen Sonuç |
| :--- | :--- |
| `./philo 5 800 200 200` | 🟢 Yaşamalılar |
| `./philo 5 610 200 200` | 🟢 Yaşamalılar |
| `./philo 199 610 200 200` | 🟢 Yaşamalılar (Çok ağır yük) |

<details>
<summary><b>(Genişletilmiş) Tek Sayıda Filozof - Yaşamalı</b></summary>

```bash
./philo 5 610 200 100
./philo 5 601 200 200
./philo 31 610 200 100
./philo 31 610 200 200
./philo 31 605 200 200
./philo 31 601 200 200
./philo 131 610 200 100
./philo 131 610 200 200
./philo 131 605 200 200
./philo 131 601 200 200
./philo 199 610 200 100
./philo 199 610 200 200
./philo 199 605 200 200
./philo 199 601 200 200
```
</details>

---

### 🟢 Çift Sayıda Filozof - Yaşamalı

| Test Komutu | Beklenen Sonuç |
| :--- | :--- |
| `./philo 4 410 200 100` | 🟢 Yaşamalılar |
| `./philo 4 410 200 200` | 🟢 Yaşamalılar |
| `./philo 198 610 200 200` | 🟢 Yaşamalılar |
| `./philo 198 800 200 200` | 🟢 Yaşamalılar |

<details>
<summary><b>(Genişletilmiş) Çift Sayıda Filozof - Yaşamalı</b></summary>

```bash
./philo 50 410 200 100
./philo 50 410 200 200
./philo 50 405 200 200
./philo 50 401 200 200
./philo 130 410 200 100
./philo 130 410 200 200
./philo 130 405 200 200
./philo 130 401 200 200
./philo 198 410 200 100
./philo 198 410 200 200
./philo 198 405 200 200
./philo 198 401 200 200
```
</details>

---

### 💀 Tek Sayıda Filozof - Ölmeli

| Test Komutu | Beklenen Sonuç |
| :--- | :--- |
| `./philo 4 310 200 100` | 💀 Biri ölmeli (Aslında çift sayı, hata var script'te muhtemelen) |
| `./philo 1 800 200 100` | 💀 Biri ölmeli |

<details>
<summary><b>(Genişletilmiş) Tek Sayıda Filozof - Ölmeli</b></summary>

```bash
./philo 3 596 200 200
./philo 3 599 200 200
./philo 3 600 200 200
./philo 31 596 200 200
./philo 31 599 200 200
./philo 31 600 200 200
./philo 131 596 200 200
./philo 131 599 200 200
./philo 131 600 200 200
./philo 199 596 200 200
./philo 199 599 200 200
./philo 199 600 200 200
```
</details>

---

### 💀 Çift Sayıda Filozof - Ölmeli

| Test Komutu | Beklenen Sonuç |
| :--- | :--- |
| `./philo 3 599 200 200` | 💀 Biri ölmeli (Aslında tek sayı, tester scriptinde isimlendirmede böyle duruyor) |
| `./philo 31 599 200 200` | 💀 Biri ölmeli |
| `./philo 131 596 200 200` | 💀 Biri ölmeli |

<details>
<summary><b>(Genişletilmiş) Çift Sayıda Filozof - Ölmeli</b></summary>

```bash
./philo 4 310 200 100
./philo 50 396 200 200
./philo 50 399 200 200
./philo 50 400 200 200
./philo 130 396 200 200
./philo 130 399 200 200
./philo 130 400 200 200
./philo 198 396 200 200
./philo 198 399 200 200
./philo 198 400 200 200
```
</details>
