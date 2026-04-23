# RFC 9213 Priority Request Scheduler (API Gateway Simülasyonu)

Bu proje, modern bir API Gateway'in gelen HTTP trafiğini **RFC 9213 (Extensible HTTP Priorities)** standartlarına göre nasıl önceliklendirdiğini ve yönettiğini simüle eden bir sistem programlama çalışmasıdır.

## 🚀 Proje Genel Bakış
Gelen ağ istekleri her zaman geliş sırasına göre işlenmez. Kritik sistem mesajlarının, düşük öncelikli arka plan görevlerinin önüne geçmesi gerekir. Bu sistem, karmaşık bir istek yığınını analiz eder, önceliklerini belirler ve **Min-Heap** veri yapısını kullanarak en acil isteği her zaman en öne çıkarır.

[Image of HTTP request priority urgency levels 0 to 7]

## 🛠️ Teknik Özellikler ve Mimari
Proje, modüler bir yaklaşımla dört ana bileşenden oluşmaktadır:

* **Ayrıştırıcı (Parser):** İstemciden gelen ham metinleri (`u=1, i` gibi) analiz eder. RFC 9213 standartlarına göre sınır dışı değerleri (örn: u=9) otomatik olarak güvenli varsayılan değere (`u=3`) çeker.
* **Veri Yapısı (Min-Heap):** Öncelik kuyruğu için özel bir Heap yapısı kullanılmıştır.
    * **Erişim:** $O(1)$
    * **Ekleme/Çıkarma:** $O(\log N)$
* **Zamanlayıcı (Scheduler):** İsteklerin hayat döngüsünü (Giriş -> Kuyruk -> İşlenme) yönetir.
* **Ana Modül (Main):** Sistemin farklı senaryolar (acil istekler, varsayılan değerler, FIFO kuralı) altındaki performansını test eder.

[Image of binary min-heap tree structure with priority numbers]

## 📁 Proje Yapısı
```text
├── include/           # Başlık (.h) dosyaları
│   ├── heap.h         # Kuyruk algoritması tanımları
│   ├── parser.h       # RFC standart tanımları
│   └── scheduler.h    # Gateway yönetim arayüzü
├── src/               # Kaynak (.c) dosyaları
│   ├── heap.c         # Min-Heap implementasyonu
│   ├── parser.c       # String parsing mantığı
│   ├── scheduler.c    # İş akış yönetimi
│   └── main.c         # Test senaryoları
└── Makefile           # Derleme otomasyonu
