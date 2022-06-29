#define _CRT_SECURE_NO_WARNINGS
#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct artikli {
	int id;
	char imeArtikla[101];
	char imeKategorije[101];
	char vrijednostPrveSpecifikacije[101];
	char vrijednostDrugeSpecifikacije[101];
	char vrijednostTreceSpecifikacije[101];
	char vrijednostCetvrteSpecifikacije[101];
	float cijena;
	int kolicina;
}ARTIKL;

typedef struct kategorija {
	int id;
	char imeKategorije[101];
	char imePrveSpecifikacije[101];
	char imeDrugeSpecifikacije[101];
	char imeTreceSpecifikacije[101];
	char imeCetvrteSpecifikacije[101];

}KATEGORIJE;

#endif // STRUCTURE_H