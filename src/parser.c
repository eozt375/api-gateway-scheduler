#include "parser.h"
#include <string.h>
#include <stdio.h>

HttpRequest parse_priority_header(int req_id, const char* header_str) {
    HttpRequest req;
    req.request_id = req_id;
    
    // RFC 9213 Kuralı: Eğer header'da değer belirtilmemişse, 
    // varsayılan olarak urgency=3 ve incremental=false kabul edilir.
    req.urgency = 3;         
    req.incremental = false; 
    
    // Gelen orjinal veriyi kopyalıyoruz (Güvenlik için sınır koyarak)
    strncpy(req.raw_header, header_str, sizeof(req.raw_header) - 1);
    req.raw_header[sizeof(req.raw_header) - 1] = '\0';

    // Boş string gelirse varsayılan değerlerle direkt dön
    if (header_str == NULL || strlen(header_str) == 0) {
        return req;
    }

    // "u=" parametresini bulma işlemi
    const char* u_ptr = strstr(header_str, "u=");
    if (u_ptr != NULL) {
        int u_val;
        if (sscanf(u_ptr, "u=%d", &u_val) == 1) {
            // RFC 9213 Kuralı: Urgency 0 ile 7 arasında sınırlandırılmıştır.
            if (u_val >= 0 && u_val <= 7) {
                req.urgency = u_val;
            }
        }
    }

    // "i" (incremental) parametresini bulma işlemi
    const char* i_ptr = strstr(header_str, "i");
    if (i_ptr != NULL) {
        if (strstr(header_str, "i=?0") != NULL) {
            req.incremental = false;
        } else {
            req.incremental = true;
        }
    }

    return req;
}