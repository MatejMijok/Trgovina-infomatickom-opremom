#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Functions.h"
#include "Structure.h"

static int brojArtikala = 0;
static int brojKategorija = 0;

void meni() {
	int n = 0;
	static ARTIKL* poljeArtikala = NULL;
	static KATEGORIJE* poljeKategorija = NULL;
	static ARTIKL* pronadeniArtikl = NULL;

	FILE* fp = NULL;

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
		fp = fopen("artikli.bin", "rb");
		if (fp == NULL && errno == 2)
		{
			perror("Dodavanje artikla u datoteku artikli.bin");
			printf("Kreiranje datoteke artikli.bin\n");
			//exit(EXIT_FAILURE);
			kreiranjeDatoteke("artikli.bin");
			//fp = fopen("artikli.bin", "rb+");
		}

		fp = fopen("kategorije.bin", "rb");

		if (fp == NULL && errno == 2)
		{
			perror("Dodavanje artikla u datoteku kategorije.bin");
			printf("Kreiranje datoteke artikli.bin\n");
			//exit(EXIT_FAILURE);
			kreiranjeDatoteke("kategorije.bin");
			//fp = fopen("kategorije.bin", "rb+");
		}

		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitavanjeArtikala();

		if (poljeArtikala == NULL)
			exit(EXIT_FAILURE);
		

		if (poljeKategorija != NULL) {
			free(poljeKategorija);
			poljeKategorija = NULL;
		}

		poljeKategorija = (KATEGORIJE*)ucitavanjeKategorija();
		if (poljeKategorija == NULL)
			exit(EXIT_FAILURE);

		ispisivanjeArtikala(poljeArtikala, poljeKategorija);
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
	case 5: 

		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitavanjeArtikala();

		if (poljeArtikala == NULL)
			exit(EXIT_FAILURE);
		
		if (poljeKategorija != NULL) {
			free(poljeKategorija);
			poljeKategorija = NULL;
		}
		poljeKategorija = (KATEGORIJE*)ucitavanjeKategorija();

		if (poljeKategorija == NULL)
			exit(EXIT_FAILURE);

		pronadeniArtikl = (ARTIKL*)pretrazivanjeArtikala(poljeArtikala);
		
		for (int j = 0; j < brojKategorija; j++) {
			if (((pronadeniArtikl)->brojKategorije) == ((poljeKategorija + j)->id)) {
				printf("\n%d. artikl: %s\n cijena: %0.2f\n kolicina: %d\n kategorija: %s\n %s: %s\n %s: %s\n %s: %s\n %s: %s \n",
					1, ((pronadeniArtikl)->imeArtikla), (pronadeniArtikl)->cijena
					, (pronadeniArtikl)->kolicina, (poljeKategorija + j)->imeKategorije
					, (poljeKategorija + j)->imePrveSpecifikacije, (pronadeniArtikl)->vrijednostPrveSpecifikacije
					, (poljeKategorija + j)->imeDrugeSpecifikacije, (pronadeniArtikl)->vrijednostDrugeSpecifikacije
					, (poljeKategorija + j)->imeTreceSpecifikacije, (pronadeniArtikl)->vrijednostTreceSpecifikacije
					, (poljeKategorija + j)->imeCetvrteSpecifikacije, (pronadeniArtikl)->vrijednostCetvrteSpecifikacije);
			}
		}
		  break;

	}

	} while (n != 0);

	fp = NULL;

	//return 0;
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
	FILE* fp1 = NULL, *fp2 = NULL;
	ARTIKL noviArtikl = { 0 };
	KATEGORIJE* poljeKategorija = NULL;
	int odabir = 0;

	fp1 = fopen("artikli.bin", "rb+");
	if (fp1 == NULL && errno == 2)
	{
		perror("Dodavanje artikla u datoteku artikli.bin");
		printf("Kreiranje datoteke artikli.bin\n");
		//exit(EXIT_FAILURE);
		kreiranjeDatoteke("artikli.bin");
		fp1 = fopen("artikli.bin", "rb+");
	}
	fread(&brojArtikala, sizeof(int), 1, fp1);
	//fclose(fp);
	
	fp2 = fopen("kategorije.bin", "rb+");
	if (fp2 == NULL && errno == 2)
	{
		perror("Dodavanje artikla u datoteku kategorije.bin");
		printf("Kreiranje datoteke kategorije.bin\n");
		//exit(EXIT_FAILURE);
		kreiranjeDatoteke("kategorije.bin");
		fp2 = fopen("kategorije.bin", "rb+");
	}
	fread(&brojKategorija, sizeof(int), 1, fp2);
	//fclose(fp2);

	
	
	if (poljeKategorija != NULL) {
		free(poljeKategorija);
		poljeKategorija = NULL;
	}
	poljeKategorija = (KATEGORIJE*)ucitavanjeKategorija();

	
	printf("Odaberite kategoriju koju zelite: ");

	if (poljeKategorija == NULL)
	{
		printf("Unesite kategoriju za koju upisujete podatke: \n");
		unosKategorije();
	}
	poljeKategorija = (KATEGORIJE*)ucitavanjeKategorija();
	for (int i = 0; i < brojKategorija; i++)
	{
		printf("%d. %s, ID: %d\n",  i + 1, (poljeKategorija + i)->imeKategorije, (poljeKategorija + i)->id);
	}
	printf("%d. Dodavanje nove kategorije.", brojKategorija + 1);
	printf("\nVas unos: ");
	scanf("%d", &odabir);

	if (odabir == brojKategorija + 1) {
		unosKategorije();

		if (poljeKategorija != NULL) {
			free(poljeKategorija);
			poljeKategorija = NULL;
		}

		poljeKategorija = (KATEGORIJE*)ucitavanjeKategorija();
		if (poljeKategorija == NULL)
			exit(EXIT_FAILURE);
	}

	printf("\nBroj artikala %d\n", brojArtikala);
	noviArtikl.id = brojArtikala;
	printf("Unesite ime artikla: ");
	getchar();
	fgets(noviArtikl.imeArtikla, 100, stdin);


	printf("Unesite cijenu artikla: ");
	scanf("%f", &noviArtikl.cijena);
	printf("Unesite kolicinu artikla: ");
	scanf("%d", &noviArtikl.kolicina);
	printf("Unesite vrijednost za %s ", ((poljeKategorija + (odabir - 1))->imePrveSpecifikacije));
	getchar();
	scanf("%100[^\n]", noviArtikl.vrijednostPrveSpecifikacije);
	printf("Unesite vrijednost za %s ", ((poljeKategorija + (odabir - 1))->imeDrugeSpecifikacije));
	getchar();
	scanf("%100[^\n]", noviArtikl.vrijednostDrugeSpecifikacije);
	printf("Unesite vrijednost za %s ", ((poljeKategorija + (odabir - 1))->imeTreceSpecifikacije));
	getchar();
	scanf("%100[^\n]", noviArtikl.vrijednostTreceSpecifikacije);
	printf("Unesite vrijednost za %s ", ((poljeKategorija + (odabir - 1))->imeCetvrteSpecifikacije));
	getchar();
	scanf("%100[^\n]", noviArtikl.vrijednostCetvrteSpecifikacije);
	noviArtikl.brojKategorije = (odabir - 1);
	
	printf("%d. artikl: %s\n cijena: %0.2f\n kolicina: %d\n kategorija: %s\n %s: %s\n %s: %s\n %s: %s\n %s: %s \n",
		0, ((noviArtikl).imeArtikla), (noviArtikl).cijena
		, (noviArtikl).kolicina, (poljeKategorija + (odabir - 1))->imeKategorije
		, (poljeKategorija + (odabir - 1))->imePrveSpecifikacije, (noviArtikl).vrijednostPrveSpecifikacije
		, (poljeKategorija + (odabir - 1))->imeDrugeSpecifikacije, (noviArtikl).vrijednostDrugeSpecifikacije
		, (poljeKategorija + (odabir - 1))->imeTreceSpecifikacije, (noviArtikl).vrijednostTreceSpecifikacije
		, (poljeKategorija + (odabir - 1))->imeCetvrteSpecifikacije, (noviArtikl).vrijednostCetvrteSpecifikacije);


	fseek(fp1, sizeof(ARTIKL) * brojArtikala, SEEK_CUR);
	fwrite(&noviArtikl, sizeof(ARTIKL), 1, fp1);
	rewind(fp1);
	brojArtikala++;
	fwrite(&brojArtikala, sizeof(int), 1, fp1);
	fclose(fp1);
	fclose(fp2);
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
		//fclose(fp);
		kreiranjeDatoteke("artikli.bin");
		fp = fopen("artikli.bin", "rb+");
	}

	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Broj artikala: %d\n", brojArtikala);

	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));

	if (poljeArtikala == NULL)
	{
		perror("Zauzimanje memorije za artikle");
		exit(EXIT_FAILURE);
	}

	fread(poljeArtikala, sizeof(ARTIKL), brojArtikala, fp);

	return poljeArtikala;
}

void* ucitavanjeKategorija() {
	FILE* fp = fopen("kategorije.bin", "rb");
	if (fp == NULL && errno == 2)
	{
		perror("Ucitavanje podataka iz datoteke kategorije.bin");
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

void ispisivanjeArtikala(const ARTIKL* const poljeArtikala, const KATEGORIJE* const poljeKategorija) {
	if (poljeArtikala == NULL) {
		printf("Polje artikala je prazno! \n");
	}
	if (poljeKategorija == NULL) {
		printf("Polje kategorija je prazno! \n");
	}

	for (int i = 0; i < brojArtikala; i++)
	{
		for(int j = 0; j<brojKategorija; j++) {
		if(((poljeArtikala + i)->brojKategorije) == ((poljeKategorija + j)->id)){
		printf("%d. artikl: %s\n cijena: %0.2f\n kolicina: %d\n kategorija: %s\n %s: %s\n %s: %s\n %s: %s\n %s: %s \n",
				i+1, ((poljeArtikala + i)->imeArtikla), (poljeArtikala + i)->cijena
				,(poljeArtikala + i)->kolicina, (poljeKategorija + j)->imeKategorije
				,(poljeKategorija + j)->imePrveSpecifikacije, (poljeArtikala + i)->vrijednostPrveSpecifikacije
				,(poljeKategorija + j)->imeDrugeSpecifikacije, (poljeArtikala + i)->vrijednostDrugeSpecifikacije
				,(poljeKategorija + j)->imeTreceSpecifikacije, (poljeArtikala + i)->vrijednostTreceSpecifikacije
				,(poljeKategorija + j)->imeCetvrteSpecifikacije, (poljeArtikala + i)->vrijednostCetvrteSpecifikacije);
				}
			}
		}
	}


void ispisivanjeKategorija(const KATEGORIJE* const poljeKategorija) {
	if (poljeKategorija == NULL) {
		printf("Polje artikala je prazno! \n");
		return;
	}
	for (int i = 0; i < brojKategorija; i++)
	{
		printf("ID: %d. Ime %d. kategorije je %s, dodijeljene specifikacije kategorije su: \t%s, \t%s, \t%s, \t%s \n",
			(poljeKategorija + i)->id, i + 1, (poljeKategorija + i)->imeKategorije, (poljeKategorija + i)->imePrveSpecifikacije,
			(poljeKategorija + i)->imeDrugeSpecifikacije, (poljeKategorija + i)->imeTreceSpecifikacije,
			(poljeKategorija + i)->imeCetvrteSpecifikacije);
	}

}

void* pretrazivanjeArtikala(ARTIKL* const poljeArtikala) {
	if (poljeArtikala == NULL) {
		printf("Polje artikala je prazno!");
			return NULL;
	}
	char trazeniPodatak[101] = {'\0'};
	char dodavanje[2] = {'\n' };

	printf("Unesite trazeni podatak za pronalazak artikala: ");
	getchar();
	scanf("%100[^\n]", trazeniPodatak);
	strcat(trazeniPodatak, dodavanje);
	
	
	printf("  %s", (poljeArtikala + 0)->imeArtikla);
	for (int i = 0; i < brojArtikala; i++)
	{
		if (strcmp((poljeArtikala + i)->imeArtikla, trazeniPodatak) == 0) {
			printf("Artikl koji se slaze sa kriterijem uspjesno pronaden!");
			return (poljeArtikala + i);
		}
	}
	printf("Trazeni podatak ne postoji!\n");
	return NULL;
}