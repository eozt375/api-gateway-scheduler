#include "scheduler.h"
#include <stdio.h>

/*
 * TEST SENARYOLARI (Sunum sırasında hocanın en çok dikkat edeceği yer)
 * Burada istekleri kuyruğa karışık olarak atıyoruz.
 * İşleme sırasına geçtiğimizde sistemin bunları RFC 9213 kurallarına göre
 * nasıl sıraya dizdiğini konsolda göreceksiniz.
 */
int main() {
    scheduler_init();

    // 1. Normal bir istek
    scheduler_add_request("u=5");
    
    // 2. Çok acil bir istek (Urgency 1) - Sonra gelse de ilk işlenmeli!
    scheduler_add_request("u=1, i");
    
    // 3. Öncelik belirtilmeyen bir istek - RFC 9213'e göre varsayılan(u=3) atanmalı
    scheduler_add_request("");
    
    // 4. En acil istek (Urgency 0) - Açıkça false edilmiş incremental
    scheduler_add_request("u=0, i=?0");
    
    // 5. 2. İstek ile aynı aciliyette (u=1). ID'si büyük olduğu için 2'den SONRA işlenmeli (FIFO testi)
    scheduler_add_request("u=1");
    
    // 6. Standart dışı aciliyet değeri (u=9). Parser bunu reddetmeli ve u=3 kabul etmeli.
    scheduler_add_request("u=9");

    // Tüm istekleri Gateway'e gönderdik. Şimdi Gateway'in bu karmaşayı nasıl
    // mükemmel bir sıraya koyduğunu ekranda yazdıralım.
    scheduler_process_all();

    return 0;
}