/*
 * LABORATORIUM PROCESOROW SYGNALOWYCH
 * \author GRZEGORZ JOZWIAK
 * \file mcbsp.h
 * \brief Modul do konfiguracji portow MCBSP0 i MCBSP1 oraz ukladu kodeka audio
 */
#include <csl.h>
#include <csl_edma.h>
#include <csl_mcbsp.h>
#include <stdio.h>
#include "circbuf.h"

/*!\var CIRCBUFFER input
 * \brief Zmienna u¿ywana przez funkcje circ_put, circ_get i circ_len do obslugi bufora wejsciowego
 */
extern CIRCBUFFER input;
extern CIRCBUFFER output;

/*!\fn void setupMCBSP(void)
 * \brief Funkcja konfiguruj¹ca uklady portow MCBSP0 i MCBSP1 procesora tms320c6713 oraz uklad kodeka audio
 */
void setupMCBSP(void);

/*!\fn void writeData(Int16 x)
 * \brief Funkcja zapisujaca 16bitowa wartosc do rejestru nadajnika portu MCBSP1
 * \param x 16bitowa liczba, ktora zostanie zapisana bezposrednio do rejestru nadajnika portu MCBSP1
 */
void writeData(Int16 x);

