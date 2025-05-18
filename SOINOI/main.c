#include <csl.h>
#include <csl_irq.h>

#include <stdio.h>
#include <math.h>
#include "signals.h"
#include "mcbsp.h"
#include "filters.h"
//deklaracja wskaznika do tablicy obslugi przerwan (16 blokow po 8 rozkazow)
extern far void IRQ_service(void);


void main()
{
	Int16 data;
	signal_err(0);
	CSL_init();
	IRQ_resetAll();
	IRQ_setVecs(IRQ_service);

	setupMCBSP(); //konfigurowanie portu szeregowego
	IRQ_nmiEnable();
	IRQ_globalEnable();

	while(1)
	{
		while(circ_get(&input,&data));
		while(circ_put(&output,data));
	}
}

