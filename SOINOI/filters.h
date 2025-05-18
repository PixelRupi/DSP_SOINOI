/*
 * LABORATORIUM PROCESOROW SYGNALOWYCH
 * \author GRZEGORZ JOZWIAK
 * \file filters.h
 * \brief Modul z funkcjami do projektowani i filtracji sygna³ów
 */
#ifndef FILTERS_H_
#define FILTERS_H_

/*!\fn void IIR4th(double fs, double fc)
 * \brief Funkcja projektuj¹ca filtr Butterwortha czwartego rzêdu (5 wspó³czynników a i 5 wspó³czynników b, a[0]=1)
 * \param fs czestotliwosc probkowania w Hz
 * \param fc czestotliwosc odciecia filtru w Hz
 */
void IIR4th(double fs, double fc);

/*!\fn void sincfilter(float fs, float fc, int N)
 * \brief Funkcja projektuj¹ca filtr SOI z oknem Blackmana
 * \param fs czestotliwosc probkowania w Hz
 * \param fc czestotliwosc odciecia filtru w Hz
 * \param N dlugosc odpowiedzi impulsowej filtru, musi byc nieparzysta liczba calkowita od 1 do 128
 * \details
 * Filtr zapisuje wspolczynniki do tablicy b. Funkcja FIR powinna sie odwolywac do pierwszych M elementow tablicy b.
 * M jest rowne N
 */
void sincfilter(float fs, float fc, int N);

/*!\fn float FIR(float xx)
 * \brief Funkcja powinna realizowac filtr SOI
 * \param xx Biezaca probka sygnalu
 * \return Probka sygnalu wyjsciowego
 * \details
 * Funkcja powinna wykorzystywac tablice b i bufor kolowy x (zmienne globalne) do realizacji filtru SOI
 * Pozycje w buforze x okresla zmienna globalna p
 */
float FIR(float xx);

/*!\fn float IIR(float xx)
 * \brief Funkcja powinna realizowac filtr NOI
 * \param xx Biezaca probka sygnalu
 * \return Probka sygnalu wyjsciowego
 * \details
 * Funkcja powinna wykorzystywac tablice a i b i bufor kolowy x (zmienne globalne) do realizacji filtru NOI
 * Pozycje w buforze x okresla zmienna globalna p
 */
float IIR(float xx);

/*!\fn float echo(float xx)
 * \brief Funkcja powinna realizowac efekt echa
 * \param xx Biezaca probka sygnalu
 * \return Probka sygnalu wyjsciowego
 * \details
 * Funkcja powinna wykorzystywac bufor kolowy x (zmienna globalne) do realizacji filtru SOI
 * Pozycje w buforze x okresla zmienna globalna p
 */
float echo(float xx);

#endif /* FILTERS_H_ */
