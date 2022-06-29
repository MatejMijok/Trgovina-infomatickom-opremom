#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Functions.h"
#include "Structure.h"

static int brojArtikala = 0;
static int brojKategorija = 0;

void meni() {
	int n = 0;
	static ARTIKL* poljeArtikala = NULL;
	static KATEGORIJE* poljeKategorija = NULL;

	do {
	printf("\n1. Unos novog artikla\n");
	printf("2. Kreiranje kategorije i specifikacija za uredaj\n");
	printf("3. Ispisivanje unesenih artikala\n");
	printf("4. Ispisivanje unesenih kategorija sa specifikacijama\n");
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

	case 4: if (poljeKategorija != NULL) {
			free(poljeKategorija);
			poljeKategorija = NULL;
				}
		  poljeKategorija = (KATEGORIJE*)ucitavanjeKategorija();
		  if (poljeKategorija == NULL)
			  exit(EXIT_FAILURE);
		  ispisivanjeKategorija(poljeKategorija);
		  break;
	}

	//return 0;

	} while (n != 0);
}
	
void kreiranjeDatoteke(char imeDatoteke[101]) {
	FILE* fp = fopen(imeDatoteke, "wb");
	if (fp == NULL) {
		perror("Kreiranje datoteke");
		exit(EXIT_FAILURE);
	}
	if (imeDatoteke == "artikli.bin")
		fwrite(&brojArtikala, sizeof(int), 1, fp);
	else
		fwrite(&brojKategorija, sizeof(int), 1, fp);

	fclose(fp);
}

int unosNovogArtikla() {
	FILE* fp = NULL;
	ARTIKL noviArtikl = { 0 };
	fp = fopen("artikli.bin", "rb+");
	if (fp == NULL && errno == 2)
	{
		perror("Dodavanje artikla u datoteku artikli.bin");
		//exit(EXIT_FAILURE);
		kreiranjeDatoteke("artikli.bin");
		fp = fopen("artikli.bin", "rb+");
	}
	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("\nBroj artikala %d\n", brojArtikala);
	noviArtikl.id = brojArtikala;
	printf("Unesite ime artikla: ");
	getchar();
	fgets(noviArtikl.imeArtikla, 100, stdin);
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
	FILE* fp = NULL;
	KATEGORIJE kategorija = { 0 };

	fp = fopen("kategorije.bin", "rb+");
	if (fp == NULL && errno == 2)
	{
		perror("Ucitavanje podataka iz datoteke kategorije.bin");
		kreiranjeDatoteke("kategorije.bin");
		fp = fopen("kategorije.bin", "rb+");		
	}

	fread(&brojKategorija, sizeof(int), 1, fp);
	printf("\nBroj kategorija %d\n", brojKategorija);
	kategorija.id = brojKategorija;
	printf("Unesite ime kategorije: ");
	getchar();
	fgets(kategorija.imeKategorije, 100, stdin);
	printf("Unesite ime prve specifikacije: ");
	//getchar();
	fgets(kategorija.imePrveSpecifikacije, 100, stdin);
	
	printf("Unesite ime druge specifikacije: ");
	//getchar();
	fgets(kategorija.imeDrugeSpecifikacije, 100, stdin);
	printf("Unesite ime trece specifikacije: ");
	//getchar();
	fgets(kategorija.imeTreceSpecifikacije, 100, stdin);
	printf("Unesite ime cetvrte specifikacije: ");
	//getchar();
	fgets(kategorija.imeCetvrteSpecifikacije, 100, stdin);

	printf("%s %s %s %s %s", kategorija.imeKategorije, kategorija.imePrveSpecifikacije , kategorija.imeDrugeSpecifikacije, kategorija.imeTreceSpecifikacije, kategorija.imeCetvrteSpecifikacije);

	fseek(fp, sizeof(KATEGORIJE) * brojKategorija, SEEK_CUR);
	fwrite(&kategorija, sizeof(KATEGORIJE), 1, fp);
	rewind(fp);
	brojKategorija++;
	fwrite(&brojKategorija, sizeof(int), 1, fp);
	fclose(fp);

	return 0;
}

void* ucitavanjeArtikala() {
	FILE* fp = fopen("artikli.bin", "rb");
	if (fp == NULL && errno == 2)
	{
		perror("Ucitavanje podataka iz datoteke artikli.bin");
		//exit(EXIT_FAILURE);
		fclose(fp);
		kreiranjeDatoteke("artikli.bin");
		fp = fopen("artikli.bin", "rb+");
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
		printf("%d. artikl: %s, cijena: %0.2f, kolicina: %d \n", i+1, (poljeArtikala + i)->imeArtikla, (poljeArtikala + i)->cijena, (poljeArtikala + i)->kolicina);
	}

}

void* ucitavanjeKategorija() {
	FILE* fp = fopen("kategorije.bin", "rb");
	if (fp == NULL && errno == 2)
	{
		perror("Ucitavanje podataka iz datoteke artikli.bin");
		//exit(EXIT_FAILURE);
		fclose(fp);
		kreiranjeDatoteke("kategorije.bin");
		fp = fopen("kategorije.bin", "rb+");
	}
	fread(&brojKategorija, sizeof(int), 1, fp);
	printf("Broj kategorija: %d\n", brojKategorija);
	KATEGORIJE* poljeKategorija = (KATEGORIJE*)calloc(brojKategorija, sizeof(KATEGORIJE));

	if (poljeKategorija == NULL)
	{
		perror("Zauzimanje memorije za kategorije");
		exit(EXIT_FAILURE);
	}
	fread(poljeKategorija, sizeof(KATEGORIJE), brojKategorija, fp);

	return poljeKategorija;
}

void ispisivanjeKategorija(const KATEGORIJE* const poljeKategorija) {
	if (poljeKategorija == NULL) {
		printf("Polje artikala je prazno! \n");
		return;
	}
	for (int i = 0; i < brojKategorija; i++)
	{
		printf("Ime %d. kategorije je %s, dodijeljene specifikacije kategorije su: \t%s, \t%s, \t%s, \t%s \n",
			i + 1, (poljeKategorija + i)->imeKategorije, (poljeKategorija + i)->imePrveSpecifikacije,
			(poljeKategorija + i)->imeDrugeSpecifikacije, (poljeKategorija + i)->imeTreceSpecifikacije,
			(poljeKategorija + i)->imeCetvrteSpecifikacije);
	}

}