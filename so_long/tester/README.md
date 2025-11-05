# SO_LONG AUTOMATIC TESTER

Bu klasör, `so_long` projesinin otomatik test aracını içerir.

## Kullanım

### 1. Test aracını derle:
```bash
cd tester
make
```

### 2. Testleri çalıştır:
```bash
./test_runner
```

## Test Edilen Durumlar

✅ **Oyuncu Hataları:**
- Oyuncu yok
- Birden fazla oyuncu

✅ **Çıkış Hataları:**
- Çıkış yok
- Birden fazla çıkış

✅ **Koleksiyon Hataları:**
- Koleksiyon yok

✅ **Duvar Hataları:**
- Üst duvar eksik
- Alt duvar eksik
- Sol duvar eksik
- Sağ duvar eksik

✅ **Harita Şekil Hataları:**
- Dikdörtgen değil
- Geçersiz karakter

✅ **Yol Bulma Hataları:**
- Koleksiyona ulaşılamıyor
- Çıkışa ulaşılamıyor

## Çıktı Örneği

```
╔════════════════════════════════════════════╗
║         SO_LONG AUTOMATIC TESTER          ║
╚════════════════════════════════════════════╝

[TEST  1] Testing: No Player                    ✓
[TEST  2] Testing: No Exit                      ✓
[TEST  3] Testing: No Collectible               ✓
...

╔════════════════════════════════════════════╗
║              TEST SUMMARY                  ║
╠════════════════════════════════════════════╣
║  Passed: 13 | Failed:  0 | Total: 13      ║
╚════════════════════════════════════════════╝

🎉 ALL TESTS PASSED! 🎉
```

## Temizlik

```bash
make fclean
```

## Notlar

- Test aracı, `../so_long` binary dosyasını kullanır
- Önce ana projeyi derlemelisiniz: `cd .. && make`
- Test haritaları `../assets/maps/` klasöründe bulunur
