#define _CRT_SECURE_NO_WARNINGS
#include "Structure.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void meni();
void kreiranjeDatoteke();
int unosNovogArtikla();
int unosKategorije();
void* ucitavanjeArtikala();
void ispisivanjeArtikala(const ARTIKL* const, const KATEGORIJE* const);
void* ucitavanjeKategorija();
void ispisivanjeKategorija(const KATEGORIJE* const);
#endif