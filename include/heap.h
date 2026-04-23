#ifndef HEAP_H
#define HEAP_H

#include "parser.h"

// Bellek taşmasını önlemek için kuyruğun alabileceği maksimum istek sayısı
#define MAX_QUEUE_SIZE 1000

/*
 * Min-Heap Veri Yapısı
 * Neden Dizi (Array) değil? Çünkü hem ekleme (insert) hem de en acil olanı alma (extract_min)
 * işlemleri O(log N) karmaşıklığında, yani çok daha performanslı çalışır.
 */
typedef struct {
    HttpRequest data[MAX_QUEUE_SIZE]; // Ağaç yapısını bellekte ardışık bir dizi olarak tutuyoruz
    int size;                         // Kuyrukta o an bekleyen aktif istek sayısı
} MinHeap;

void heap_init(MinHeap* heap);
void heap_insert(MinHeap* heap, HttpRequest req);
HttpRequest heap_extract_min(MinHeap* heap);

#endif