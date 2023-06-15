#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "nextfit.h"

#define DEFAULT_NUM_AREAS	50
#define MIN_AREA_SIZE		(2*sizeof(unsigned int))
#define MAX_AREA_SIZE		100

typedef struct {
	void *ptr;
	unsigned size;
} SAllocInfo;

static void checked_nfalloc(SAllocInfo *pai /*in-out*/)
{
	assert(pai != NULL && "Invalid argument (null-ptr)!");
	assert(pai->size >= MIN_AREA_SIZE && "Invalid memory size (< MIN_AREA_SIZE)!");

	pai->ptr = nf_alloc(pai->size);
	if (!pai->ptr) {
		fprintf(stderr, "Speicher alle (%ul bytes)!\n", pai->size);
		exit(1);
	}
	/* Größe an den Anfang und Größe*2 ans Ende */
	*((unsigned *) pai->ptr) = pai->size;
	*(((unsigned *) pai->ptr) + (pai->size - sizeof(unsigned)) / sizeof(unsigned)) = pai->size * 2;
}

static void checked_nffree(SAllocInfo *ai /*in*/)
{
	unsigned sizeStored, doubledSize;

	assert(ai->ptr != NULL && "Invalid argument (null-ptr)!");

	sizeStored = *((unsigned *)ai->ptr);

	if (sizeStored != ai->size) {
		fprintf(stderr, "Speicherinhalt beschaedigt (%p: %ul)!\n", ai->ptr, ai->size);
		abort();
	}
	doubledSize = *(((unsigned *) ai->ptr) + (ai->size - sizeof(unsigned)) / sizeof(unsigned));
	if (doubledSize != ai->size * 2) {
		fprintf(stderr, "Speicherinhalt beschaedigt (%p: %ul)!\n", ai->ptr, ai->size);
		abort();
	}

	nf_free(ai->ptr, ai->size);
}

int main(int argc, char **argv)
{
	SAllocInfo ai[] = {
		/* 0: Die ersten 75% belegen */
		{ NULL, 0.75 * MEM_POOL_SIZE },
		/* 1: Direkt danach ein Chunk belegen (Speicher kann noch nicht voll sein!) */
		{ NULL, CHUNK_SIZE },
		/* 2: wg. Freigabe von 0 muss wieder vorne begonnen werden (NextFit) */
		{ NULL, 0.75 * MEM_POOL_SIZE - 0.125 * MEM_POOL_SIZE },
		/* 3: Landet zwischen 2 und 1 */
		{ NULL, CHUNK_SIZE * 2 },
		/* 4: Sollten am Ende landen, da Luecken vorher zu klein */
		{ NULL, 0.125 * MEM_POOL_SIZE + 1 }
	};
	SAllocInfo *pData;
	void *ptr;
	unsigned long num_areas, allocated_areas;
	unsigned i, repetitions;

	/* Parameter vorhanden? */
	if (argc < 2) {
		/* nein -> Defaultwert */
		num_areas = DEFAULT_NUM_AREAS;
	} else {
		/* ja -> nach unsigned long konvertieren */
		char *endptr;
		num_areas = strtoul(argv[1], &endptr, 0);
		if (endptr == argv[1] || *endptr) {
			fprintf(stderr, "ungueltiger Parameter\n");
			return 1;
		}
	}

	printf("Anzahl Speicherbereiche: %lu\n", num_areas);

	/* Speicher fuer Zeigerarray besorgen */
	pData = malloc(num_areas * sizeof(SAllocInfo));

	if (!pData) {
		fprintf(stderr, "Speicher fuer Zeigerarray konnte nicht alloziert werden (malloc).\n");
		return 1;
	}

	srand(time(NULL));

	/* Testet die Funktionen nf_alloc/nf_free bzw. das NextFit-Verfahren. */
	for (repetitions = 0; repetitions < 2; repetitions++) { /* => alles 2x */
		for (i = 0; i < num_areas; i++) {
			pData[i].ptr = NULL;
			pData[i].size = MIN_AREA_SIZE + rand() % (MAX_AREA_SIZE-MIN_AREA_SIZE+1);

			checked_nfalloc(pData + i);
		}

		allocated_areas = i;

		/* alle durch 3 teilbaren freigeben */
		for (i = 0; i < allocated_areas; i += 3) {
			checked_nffree(&pData[i]);
		}
		/* die restlichen freigeben */
		for (i = 0; i < allocated_areas; ++i) {
			if ((i % 3) == 0) continue;
			checked_nffree(&pData[i]);
		}

		/* Die Einrückung kennzeichnet die paarweisen Aufrufe von alloc/free. */
		checked_nfalloc(&ai[0]);
		  checked_nfalloc(&ai[1]);
		checked_nffree(&ai[0]);
		    checked_nfalloc(&ai[2]);
		      checked_nfalloc(&ai[3]);
		    checked_nffree(&ai[2]);
		        checked_nfalloc(&ai[4]);
		  checked_nffree(&ai[1]);
		      checked_nffree(&ai[3]);
		        checked_nffree(&ai[4]);
	}
	free(pData);

	/* Wir sind sehr Speicher-hungrig ... (Maximalanforderung)! */
	ptr = nf_alloc(MEM_POOL_SIZE);
	if (ptr == NULL) {
		fprintf(stderr, "Da ging wohl was schief (Anforderung mit: %lu bytes)!", MEM_POOL_SIZE);
		abort();
	}
	nf_free(ptr, MEM_POOL_SIZE);

	if (nf_alloc(MEM_POOL_SIZE+1) != NULL) {
		fprintf(stderr, "Speicherbereich (Memory-Pool) verlassen!");
		abort();
	}

/*
 * Diesen Code koennt ihr zum Testen des finalen Falles "Speicher voll"
 * einschalten (indem ihr #if 0 durch #if 1 ersetzt):
 */
#if 0
	while (1) {
		void *ptr;
		if ((ptr = nf_alloc(MAX_AREA_SIZE))) {
			memset(ptr, 42, MAX_AREA_SIZE);
			continue;
		}
		fprintf(stderr, "Speicher alle\n");
		break;
	}
#endif
	return 0;
}
