# 🐾 Automatic Cat Feeder ESP32

Automatic Cat Feeder adalah solusi modern untuk memastikan kucing kesayangan Anda tetap mendapatkan asupan makanannya secara tepat waktu, bahkan ketika Anda sibuk atau sedang tidak di rumah. Sistem ini mengintegrasikan teknologi ESP32, kontrol servo motor, dan aplikasi Blynk untuk pengoperasian otomatis dan manual melalui internet.

## 📌 Fitur

- ✅ Memberi makan kucing secara otomatis dengan durasi tertentu
- ✅ Kontrol manual melalui aplikasi Blynk
- ✅ Web UI kontrol sudut servo via WiFi
- ✅ Sistem konfigurasi WiFi otomatis (WiFiManager)
- ✅ Desain antarmuka web minimalis dan responsif

## 🧩 Komponen yang Digunakan

| Komponen       | Fungsi                                     |
|----------------|---------------------------------------------|
| ESP32          | Otak sistem dan koneksi WiFi                |
| Servo Motor    | Menggerakkan pengeluaran makanan            |
| Dispenser Makanan | Menampung dan mengalirkan makanan kucing |
| Aplikasi Blynk | Remote kontrol via smartphone               |

## 🛠️ Instalasi

1. Pasang library berikut di Arduino IDE:
   - `Blynk`
   - `WiFiManager`
   - `ESP32Servo`
   - `WiFi` (default ESP32)

2. Upload kode dari file `cat_feeder.ino` ke board ESP32 Anda.

3. Jalankan dan koneksikan WiFi melalui portal otomatis dari ESP32 (`SSID: PET_FEEDER`).

4. Gunakan Blynk App dan Web UI untuk memberi makan.

## 🌐 Web Interface

Setelah ESP32 terhubung ke WiFi, Anda dapat mengakses kontrol manual servo via browser:
```
http://<alamat_IP_ESP32>
```

## 📱 Kontrol Blynk

- Virtual Pin: `V0`
- Tombol ON/OFF untuk mengaktifkan/mematikan servo selama 5 detik

## 💬 Credit

Proyek ini dibuat oleh Muhammad Anwar Lain dan tim.  
Institut: Global Institute
