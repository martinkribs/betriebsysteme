#ifndef __NEXTFIT_H__
#define __NEXTFIT_H__

#include <stddef.h>

/* die Groesse des Speicherpools in Bytes */
#define MEM_POOL_SIZE ((unsigned long)(1024 * 12)) /* 12 Kilobyte */
/* 1 Bit in der Freispeicher-Bitliste repraesentiert 32 Bytes im Speicherpool */
#define CHUNK_SIZE 32

/* Funktionsdeklarationen (Modulschnittstelle): */
void *nf_alloc(size_t size);

void nf_free(void *ptr, size_t size);

#endif /* __NEXTFIT_H__ */
