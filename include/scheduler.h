#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "heap.h"

// Gateway zamanlayıcısını başlatır
void scheduler_init();

// Gateway'e yeni bir string istek geldiğinde bunu parse edip kuyruğa atar
void scheduler_add_request(const char* priority_header);

// Kuyruktaki en öncelikli 1 (bir) isteği işler
void scheduler_process_next();

// Kuyruk bitene kadar tüm istekleri öncelik sırasına göre eritir
void scheduler_process_all();

#endif