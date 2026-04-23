#include "scheduler.h"
#include <stdio.h>

static MinHeap request_queue;
static int global_request_id = 1;

void scheduler_init() {
    heap_init(&request_queue);
    global_request_id = 1;
    printf("=== RFC 9213 API Gateway Scheduler Baslatildi ===\n\n");
}

void scheduler_add_request(const char* priority_header) {
    HttpRequest req = parse_priority_header(global_request_id++, priority_header);
    heap_insert(&request_queue, req);
    
    printf("[+] Istek Kuyruga Eklendi -> ID: %d | Orijinal: '%s' | Parse: u=%d, i=%s\n",
           req.request_id, req.raw_header, req.urgency, req.incremental ? "evet" : "hayir");
}

void scheduler_process_next() {
    if (request_queue.size == 0) {
        printf("[-] Kuyruk bos. Islenecek istek yok.\n");
        return;
    }
    
    HttpRequest req = heap_extract_min(&request_queue);
    
    printf("[!] ISLENIYOR -> ID: %d | Aciliyet: %d | Artimli: %s\n",
           req.request_id, req.urgency, req.incremental ? "evet" : "hayir");
}

void scheduler_process_all() {
    printf("\n--- Kuyruktaki Tum Istekler Oncelik Sirasina Gore Isleniyor ---\n");
    while (request_queue.size > 0) {
        scheduler_process_next();
    }
    printf("--- Islem Tamamlandi. Gateway Bosta. ---\n");
}