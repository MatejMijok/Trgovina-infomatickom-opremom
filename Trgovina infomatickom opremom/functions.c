#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Functions.h"
#include "Structure.h"

static int brojArtikala = 0;

void meni() {
	int n = 0;
	static ARTIKL* poljeArtikala = NULL;
	
	do {
	printf("\n1. Unos novog artikla\n");
	printf("2. Kreiranje kategorije i specifikacija za uredaj\n");
	printf("3. Ispisivanje unesenih artikala\n");
	printf("\n\n");
	do {
		printf("Unesite broj zeljene radnje programa: ");
		scanf("%d", &n);
	}while (n < 0 || n>5);
	

	switch (n) {
	case 1: unosNovogArtikla();
			break;
	
	case 2: unosKategorije();
			break;
	case 3: 
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}
		poljeArtikala = (ARTIKL*)ucitavanjeArtikala();
		if (poljeArtikala == NULL)
			exit(EXIT_FAILURE);
		ispisivanjeArtikala(poljeArtikala);
			break;
	}
	//return 0;

	} while (n != 0);
}
	
int provjeraPostojanja(char imeDatoteke[101]) {
	FILE* fp = NULL;
	fp = fopen(imeDatoteke,"rb");
	if (fp == NULL && errno == 2)
	{
		fp = fopen(imeDatoteke, "wb");
		//printf("Datoteka uspjesno kreirana!");
	}

	//fclose(fp);
	
	return 0;

}

void unos() {
	FILE* fp = fopen("artikli.bin", "wb");
	if (fp == NULL) {
		perror("Kreiranje datoteke artikli.bin");
		exit(EXIT_FAILURE);
	}
	fwrite(&brojArtikala, sizeof(int), 1, fp);
	fclose(fp);
}

int unosNovogArtikla() {
	FILE* fp = NULL;
	ARTIKL noviArtikl = { 0 };
	fp = fopen("artikli.bin", "rb+");
		if (fp == NULL)
	{
		perror("Dodavanje artikla u datoteku artikli.bin");
		exit(EXIT_FAILURE);
	}
	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("\nBroj artikala %d\n", brojArtikala);
	noviArtikl.id = brojArtikala;
	printf("Unesite ime artikla: ");
	getchar();
	scanf("%100s[^\n]", noviArtikl.imeArtikla);
	printf("Unesite cijenu artikla: ");
	scanf("%f", &noviArtikl.cijena);
	printf("Unesite kolicinu artikla: ");
	scanf("%d", &noviArtikl.kolicina);
	//printf("Odaberite kategoriju: ");


	fseek(fp, sizeof(ARTIKL) * brojArtikala, SEEK_CUR);
	fwrite(&noviArtikl, sizeof(ARTIKL), 1, fp);
	rewind(fp);
	brojArtikala++;
	fwrite(&brojArtikala, sizeof(int), 1, fp);
	fclose(fp);

	return 0;
}

int unosKategorije() {
	
	
	
	return 0;
}

void* ucitavanjeArtikala() {
	//provjeraPostojanja("artikli.bin");
	FILE* fp = fopen("artikli.bin", "rb");
	if (fp == NULL && errno == 2)
	{
		perror("Ucitavanje podataka iz datoteke artikli.bin");
		//exit(EXIT_FAILURE);
		fclose(fp);
		unos();
		fopen("artikli.bin", "rb");
	}
	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Broj artikala: %d\n", brojArtikala);
	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));

	if(poljeArtikala == NULL)
	{
		perror("Zauzimanje memorije za artikle");
		exit(EXIT_FAILURE);
	}
	fread(poljeArtikala, sizeof(ARTIKL), brojArtikala, fp);

	return poljeArtikala;
}

void ispisivanjeArtikala(const ARTIKL* const poljeArtikala) {
	if (poljeArtikala == NULL) {
		printf("Polje artikala je prazno! \n");
	}
	for (int i = 0; i < brojArtikala; i++)
	{
		printf("%d. artikl: %s, cijena: %0.2f, kolicina: %d \n",
			i+1, (poljeArtikala + i)->imeArtikla, (poljeArtikala + i)->cijena, (poljeArtikala + i)->kolicina);
	}

}