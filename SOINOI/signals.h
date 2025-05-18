/*
 * LABORATORIUM PROCESOROW SYGNALOWYCH
 * \author GRZEGORZ JOZWIAK
 * \file signals.h
 * \brief Modul implementujacy obsluge bledow
 *
 */
#ifndef SIGNALS_H_
#define SIGNALS_H_
/*!
 * LISTA SYGNALOW SYGNALIZATORA DIODOWEGO
 */
#define INPUT_BUFFER_FULL 1
#define OUTPUT_BUFFER_EMPTY 2

void signal_err(int err);
void set_err(int err);
void clear_err(int err);
#endif /* SIGNALS_H_ */
