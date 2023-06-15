#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "nextfit.h"

/* der Speicherpool */
static char mem_pool[MEM_POOL_SIZE];
/* die Bitliste, die anzeigt, welche Bloecke frei sind: 1 Bit fuer jew. CHUNK_SIZE Bytes */
static unsigned char free_list[MEM_POOL_SIZE / CHUNK_SIZE / 8];

/* Anzahl der Bits in free_list */
#define FREELIST_BIT_COUNT (sizeof(free_list) * 8)

/* ----------------------------- Hilfsfunktionen ----------------------------- */

/* Funktion zum Debuggen, die die Freispeicher-Bitliste ausgibt */
#ifdef DEBUG

static void dump_free_mem(void)
{
	int i;

	fprintf(stderr, "Freispeicherliste: ");
	for (i = 0; i < sizeof(free_list); ++i)
	{
		if ((i % 32) == 0)
		{
			fprintf(stderr, "\n%03X: ", i);
		}
		fprintf(stderr, "%02X ", free_list[i]);
	}
	fprintf(stderr, "\n");
}
#else
#define dump_free_mem()
#endif

/* rechnet aus, wie viele Chunks fuer 'size' Bytes belegt werden muessen
   (rundet automatisch auf) */
static size_t size_to_chunks(size_t size)
{
	if ((size % CHUNK_SIZE) != 0)
	{
		return size / CHUNK_SIZE + 1;
	}
	else
	{
		return size / CHUNK_SIZE;
	}
}

/* testet, ob im Bitfeld bitfield das Bit bitnr gesetzt ist:
 * liefert 0, wenn es nicht gesetzt ist, sonst eine Zahl > 0 */
static int bit_is_set(const unsigned char *bitfield, unsigned bitnr)
{
	return (bitfield[bitnr / 8] & (1 << (7 - bitnr % 8)));
}

/* setzt im Bitfeld bitfield das Bit mit der Nummer bitnr */
static void set_bit(unsigned char *bitfield, unsigned bitnr)
{
	bitfield[bitnr / 8] |= 1 << (7 - bitnr % 8);
}

/* loescht im Bitfeld bitfield das Bit mit der Nummer bitnr */
static void clear_bit(unsigned char *bitfield, unsigned bitnr)
{
	bitfield[bitnr / 8] &= ~(1 << (7 - bitnr % 8));
}

/* ----------------------------- Speicherverwaltung ----------------------------- */

void *nf_alloc(size_t size)
{

	dump_free_mem();

	/* HIER MUESST IHR EUREN CODE EINFUEGEN! */

	/* 
	Diese Funktion wird aufgerufen mit dem Auftrag Speicher der Größe size zu belegen
	1. mit n=size_to_chunks(size) die Anzahl der Chunks berechnen
	2. wir müssen n freie, hintereinander liegende bits in der Bitliste free_list finden, ausgehend vom letzten Zugriff
		-> wir müssen irgendwo den letzten Zugriff speichern, e.g. neue globale Variable "lastAsccess"
		-> da es nextfit ist, müssen wir bei lastAccess anfangen bis Ende, und dann von Anfang bis lastAccess
		-> return (offset + position*CHUNK_SIZE), offset = &mem_pool, wenn gefunden, sonst NULL
	3. 
	*/

	/* DENKT AUCH DARAN, DAS "return NULL;" GEEIGNET ANZUPASSEN! */

	return NULL;
}

void nf_free(void *ptr, size_t size)
{

	/* HIER MUESST IHR EUREN CODE EINFUEGEN! */

	dump_free_mem();
}
