#define _CRT_SECURE_NO_WARNINGS
#include "Structure.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void meni();
int provjeraPostojanja(char imeDatoteke[]);
void unos();
int unosNovogArtikla();
int unosKategorije();
void* ucitavanjeArtikala();
void ispisivanjeArtikala(const ARTIKL* const);
#endif