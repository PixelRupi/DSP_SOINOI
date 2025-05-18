/*
 * LABORATORIUM PROCESOROW SYGNALOWYCH
 * \author GRZEGORZ JOZWIAK
 * \file circbuf.h
 * \brief Modul implementujacy obsluge bufora kolowego
 */
#ifndef CIRCBUF_H_
#define CIRCBUF_H_


/*!\type CIRCBUFFER
 * \brief Typ strukturalny do implementacji bufora kolowego
 */
typedef struct _CIRCBUFFER
{
	volatile Int16 *buf;
	volatile int w;
	volatile int r;
	volatile int L;
}CIRCBUFFER;

/*!\fn void init_circular_buffer(CIRCBUFFER *b, Int16 *buf, int N)
 * \brief Funkcja inicjujaca bufor kolowy
 * \param b wskaznik na strukture CIRCBUFFER
 * \param buf wskaznik na tablice typu Int16, ktora bedzie wykorzystywana przez bufor kolowy
 * \param N rozmiar tablicy buf
 */
void init_circular_buffer(CIRCBUFFER *b, Int16 *buf, int N);

/*!\fn void int circ_put(CIRCBUFFER* b, Int16 data)
 * \brief Funkcja zapisujaca 16bitowa probke do bufora kolowego
 * \param b wskaznik na strukture CIRCBUFFER
 * \param data 16bitowa probka zapisywana do bufora kolowego b
 * \return 1 - jesli bufor jest pelny 0- w przeciwnym wypadku
 */
int circ_put(CIRCBUFFER* b, Int16 data);


/*!\fn void int circ_get(CIRCBUFFER* b, Int16* data)
 * \brief Funkcja odczytujaca 16bitowa probke z bufora kolowego
 * \param b wskaznik na strukture CIRCBUFFER
 * \param data wskaznik na zmienna typu Int16, do ktorej zostanie zapisana probka z bufora kolowego
 * \return 1 - jesli bufor jest pusty 0- w przeciwnym wypadku
 */
int circ_get(CIRCBUFFER *b, Int16* data);



/*!\fn int circ_len(CIRCBUFFER *b)
 * \brief Funkcja zwracajaca ilosc probek aktualnie zapisanych w buforze
 * \param b wskaznik na strukture CIRCBUFFER
 * \return Aktualna ilosc probek w buforze
 */
int circ_len(CIRCBUFFER *b);


#endif /* CIRCBUF_H_ */
