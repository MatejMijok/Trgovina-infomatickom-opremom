#define _CRT_SECURE_NO_WARNINGS
#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct artikli {
	int id;
	char imeArtikla[51];
	char vrijednostPrveSpecifikacije[21];
	char vrijednostDrugeSpecifikacije[21];
	char vrijednostTreceSpecifikacije[21];
	char vrijednostCetvrteSpecifikacije[21];
	float cijena;
	int kolicina;
	int brojKategorije;
}ARTIKL;

typedef struct kategorija {
	int id;
	char imeKategorije[51];
	char imePrveSpecifikacije[51];
	char imeDrugeSpecifikacije[51];
	char imeTreceSpecifikacije[51];
	char imeCetvrteSpecifikacije[51];

}KATEGORIJE;

#endif // STRUCTURE_H