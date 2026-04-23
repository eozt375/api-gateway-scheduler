#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

/*
 * RFC 9213 standardına göre bir HTTP isteğinin öncelik yapısı.
 * Sunum Notu: Bu struct, API Gateway'in karar mekanizmasının kalbidir.
 */
typedef struct {
    int request_id;     // İsteğin sisteme geliş sırasını tutar (Aynı aciliyetlerde FIFO uygulamak için)
    int urgency;        // Aciliyet: 0 (En acil) ile 7 (En düşük öncelik) arasında değer alır.
    bool incremental;   // İsteğin parça parça (incremental) işlenip işlenemeyeceğini belirtir.
    char raw_header[64];// Debugging (Hata ayıklama) için orjinal header string'ini saklarız.
} HttpRequest;

// İstemciden gelen metin tabanlı başlığı okuyup anlamlı bir struct'a dönüştürür.
HttpRequest parse_priority_header(int req_id, const char* header_str);

#endif