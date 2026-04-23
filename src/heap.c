#include "heap.h"
#include <stdio.h>

void heap_init(MinHeap* heap) {
    heap->size = 0; 
}

static void swap(HttpRequest* a, HttpRequest* b) {
    HttpRequest temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Karşılaştırma fonksiyonumuz iki şeye bakar:
 * 1. Urgency: Düşük rakam (0), yüksek rakama (7) göre DAHA ÖNCELİKLİDİR.
 * 2. Request ID: Eğer aciliyetler EŞİTSE, sisteme daha önce giren önceliklidir (FIFO).
 */
static int compare(HttpRequest a, HttpRequest b) {
    if (a.urgency != b.urgency) {
        return a.urgency - b.urgency; 
    }
    return a.request_id - b.request_id;
}

void heap_insert(MinHeap* heap, HttpRequest req) {
    if (heap->size >= MAX_QUEUE_SIZE) {
        printf("[Hata] Sunucu asiri yuk altinda, kuyruk dolu!\n");
        return;
    }
    
    int i = heap->size++;
    heap->data[i] = req;

    // Heapify Up (Yukarı Onarım - O(log N))
    while (i != 0 && compare(heap->data[i], heap->data[(i - 1) / 2]) < 0) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HttpRequest heap_extract_min(MinHeap* heap) {
    if (heap->size <= 0) {
        HttpRequest empty_req = {-1, -1, false, ""};
        return empty_req;
    }
    
    if (heap->size == 1) {
        return heap->data[--heap->size];
    }

    HttpRequest root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    // Heapify Down (Aşağı Onarım - O(log N))
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && compare(heap->data[left], heap->data[smallest]) < 0) {
            smallest = left;
        }
        if (right < heap->size && compare(heap->data[right], heap->data[smallest]) < 0) {
            smallest = right;
        }

        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}