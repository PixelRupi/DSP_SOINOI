/*
 * LABORATORIUM PROCESOROW SYGNALOWYCH
 * \author GRZEGORZ JOZWIAK
 * \file bit_ops.h
 * \brief Biblioteka do operacji bitowych na rejestrach
 */

#ifndef BIT_OPS_H_
#define BIT_OPS_H_
/*! \def BIT_MASK(l,u)
 * \brief Tworzenie maski bitowej z 1 na bitach od l do u
 */
#define BIT_MASK(l,u) (((1<<((u)-(l)+1))-1)<<(l))
/*! \def GET_BITS(val,l,u)
 * \brief Pobieranie wartosci bitow od l do u z liczby val
 * Makro pobiera wartosc bitow i zwraca je jak liczbe calkowita
 */
#define GET_BITS(val,l,u) (((val) & BIT_MASK(l,u))>>(l))
/*! \def MK_BITS(val,l,u)
 * \brief Tworzenie maski bitowej z polem val na bitach od l do u
 * Makro wstawia liczbe val w pole bitowe od bitu l do bitu u
 * Maska ta moze byc laczona za pomoca sumy logicznej z innymi maskami
 */
#define MK_BITS(val,l,u) (((val)<<(l)) & BIT_MASK(l,u))

/*! \def SET_BITS(reg,val,l,u)
 * \brief Zamiana bitow od l do u w liczbie reg na wartosc val
 * Makro wstawia liczbe val w pole bitowe od bitu l do bitu u liczby reg
 * makro moze modyfikawac wybrane bity rejestrow
 * np. amr=SET_BITS(amr,2,3,5) ustawia 3 bity (od 3 do 5) w zmiennej/rejestrze amr na wartosc "010"
 */

#define SET_BITS(reg,val,l,u) ((reg&~BIT_MASK(l,u))|MK_BITS(val,l,u))

#endif /* BIT_OPS_H_ */
