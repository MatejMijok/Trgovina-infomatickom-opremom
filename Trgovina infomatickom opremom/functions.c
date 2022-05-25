#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Functions.h"
#include "Structure.h"

void meni() {
	int n = 0;
	do {
	printf("1. Upis podataka u datoteku\n");
	

	printf("\n\n");
	do {
		printf("Unesite broj zeljene radnje programa: ");
		scanf("%d", &n);
	}while (n < 0 || n>5);
	

	switch (n) {
	case 1: unosNoveKategorije();
			break;
	}
	//return 0;

	} while (n != 0);
}
	
int provjeraPostojanja(char imeDatoteke[101]) {
	FILE* fp = NULL;
	fp = fopen(imeDatoteke,"r");
	if (fp == NULL && errno == 2)
	{
		fp = fopen(imeDatoteke, "w");
		//printf("Datoteka uspjesno kreirana!");
	}

	fclose(fp);

	return 0;

}

void unos() {
	FILE* fp = NULL;
	char imeDatoteke[101], sadrzaj[101];
	printf("Unesite ime datoteke kojoj zelite dodati podatke: ");
	getchar();
	scanf("%100[^\n]", imeDatoteke);

	provjeraPostojanja(imeDatoteke);

	fp = fopen(imeDatoteke, "w");
	if (fp == NULL)
		printf("Datoteka ne postoji!");

	getchar();
	printf("Unesite zeljeni dodatni podatak: ");
	scanf("%100[^\n]", sadrzaj);
	if (fprintf(fp, "%s", sadrzaj) == 0)
		printf("Uspjesno uneseno u datoteku. \n");

	fclose(fp);

}

int unosNovogArtikla() {
	FILE* fp = NULL;
	ARTIKL *noviArtikl;
	noviArtikl = (ARTIKL*)calloc(1, sizeof(ARTIKL));
	if (noviArtikl == NULL)
		printf("Pogreska pri zauzimanju memorije! ");

	char imeDatoteke[15] = "kategorije.txt" , sadrzaj[101];
	provjeraPostojanja(imeDatoteke);

	fp = fopen(imeDatoteke, "a+");
	if (fp == NULL)
		printf("Datoteka ne postoji");
	getchar();
	printf("Unesite zeljeno ime kategorije: ");
	scanf("%100[^\n]", noviArtikl->imeKategorije);
	printf("Unesite : ");

	if (fprintf(fp, "%s ", sadrzaj) == 0)
		printf("Uspjesno upisano u datoteku! ");
	fclose(fp);
	free(noviArtikl);
	noviArtikl = NULL;
}

