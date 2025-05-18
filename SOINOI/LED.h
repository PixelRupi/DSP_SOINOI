/*
 * LABORATORIUM PROCESOROW SYGNALOWYCH
 * \author GRZEGORZ JOZWIAK
 * \file LED.h
 * \brief Makrodefiniacje do sterowania diodami
 */

#ifndef LED_H_
#define LED_H_

/*! \def LED(p)
 *  \brief Makrodefinicja sterujaca praca diodami
 *  \param p 4 bitowe slowo sterujace praca diodami
 *  Kazdy bit umozliwia zapalenie lub zgaszenie diody (1- zapal,  0-zgas)
 */

#define LED(p) (*((volatile char*)0x90080000)=((p)&0xf))

#endif /* LED_H_ */
