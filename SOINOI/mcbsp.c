#include <csl_mcbsp.h>
#include "mcbsp.h"
#include "signals.h"

/*! \var MCBSP_Handle hMcbsp0
 * \brief Uchwyt do obslugi portu MCBSP0
 */
MCBSP_Handle hMcbsp0;


/*! \var MCBSP_Handle hMcbsp1
 * \brief Uchwyt do obslugi portu MCBSP1
 */
MCBSP_Handle hMcbsp1;

/*! \var Uint32 mcbsp1RcvEventId
 * \brief Identyfikator zdarzenia przerwania od odbiornika portu MCBSP1
 */
Uint32 mcbsp1RcvEventId;
Uint32 mcbsp1XmtEventId;

/*! \var Int16 in_array[128]
 * \brief Tablica do obslugi bufora wejsciowego odbiornika portu MCBSP1
 */
Int16 in_array[128];
Int16 out_array[128];


/*! \var CIRCBUFFER input
 * \brief Bufor wejsciowy odbiornika portu MCBSP1
 */
CIRCBUFFER input;
CIRCBUFFER output;

/*! \type AIC23_Params
 * \brief Typ strukturalny do konfiguracji wszystki rejestrow ukladu kodeka audio
 */
typedef struct AIC23_Params {
    Uns regs[ 10 ];
} AIC23_Params;



/*! \var MCBSP_Config MCBSP_cfg0
 * \brief Zmienna strukturalna z konfiguracja wszystkich rejestrow portu MCBSP0
 */
MCBSP_Config MCBSP_cfg0 = {
		// Wartosc wpisana do rejestru SPCR portu MCBSP0
        MCBSP_FMKS(SPCR, FREE, NO)              |
        MCBSP_FMKS(SPCR, SOFT, NO)              |
        MCBSP_FMKS(SPCR, FRST, YES)             |
        MCBSP_FMKS(SPCR, GRST, YES)             |
        MCBSP_FMKS(SPCR, XINTM, XRDY)           |
        MCBSP_FMKS(SPCR, XSYNCERR, NO)          |
        MCBSP_FMKS(SPCR, XRST, YES)             |
        MCBSP_FMKS(SPCR, DLB, OFF)              |
        MCBSP_FMKS(SPCR, RJUST, RZF)            |
        MCBSP_FMKS(SPCR, CLKSTP, NODELAY)       |
        MCBSP_FMKS(SPCR, DXENA, OFF)            |
        MCBSP_FMKS(SPCR, RINTM, RRDY)           |
        MCBSP_FMKS(SPCR, RSYNCERR, NO)          |
        MCBSP_FMKS(SPCR, RRST, YES),
        // Wartosc wpisana do rejestru RCR portu MCBSP0
        MCBSP_FMKS(RCR, RPHASE, DEFAULT)        |
        MCBSP_FMKS(RCR, RFRLEN2, DEFAULT)       |
        MCBSP_FMKS(RCR, RWDLEN2, DEFAULT)       |
        MCBSP_FMKS(RCR, RCOMPAND, DEFAULT)      |
        MCBSP_FMKS(RCR, RFIG, DEFAULT)          |
        MCBSP_FMKS(RCR, RDATDLY, DEFAULT)       |
        MCBSP_FMKS(RCR, RFRLEN1, DEFAULT)       |
        MCBSP_FMKS(RCR, RWDLEN1, DEFAULT)       |
        MCBSP_FMKS(RCR, RWDREVRS, DEFAULT),
        // Wartosc wpisana do rejestru XCR portu MCBSP0
        MCBSP_FMKS(XCR, XPHASE, SINGLE)         |
        MCBSP_FMKS(XCR, XFRLEN2, OF(0))         |
        MCBSP_FMKS(XCR, XWDLEN2, 8BIT)          |
        MCBSP_FMKS(XCR, XCOMPAND, MSB)          |
        MCBSP_FMKS(XCR, XFIG, NO)               |
        MCBSP_FMKS(XCR, XDATDLY, 1BIT)          |
        MCBSP_FMKS(XCR, XFRLEN1, OF(0))         |
        MCBSP_FMKS(XCR, XWDLEN1, 16BIT)         |
        MCBSP_FMKS(XCR, XWDREVRS, DISABLE),
        // Wartosc wpisana do rejestru SRGR portu MCBSP0
        MCBSP_FMKS(SRGR, GSYNC, FREE)           |
        MCBSP_FMKS(SRGR, CLKSP, RISING)         |
        MCBSP_FMKS(SRGR, CLKSM, INTERNAL)       |
        MCBSP_FMKS(SRGR, FSGM, DXR2XSR)         |
        MCBSP_FMKS(SRGR, FPER, OF(0))           |
        MCBSP_FMKS(SRGR, FWID, OF(19))          |
        MCBSP_FMKS(SRGR, CLKGDV, OF(99)),
        // Wartosc wpisana do rejestru MCR portu MCBSP0
        MCBSP_MCR_DEFAULT,
        // Wartosc wpisana do rejestru RCER portu MCBSP0
        MCBSP_RCER_DEFAULT,
        // Wartosc wpisana do rejestru XCER portu MCBSP0
        MCBSP_XCER_DEFAULT,
        // Wartosc wpisana do rejestru PCR portu MCBSP0
        MCBSP_FMKS(PCR, XIOEN, SP)              |
        MCBSP_FMKS(PCR, RIOEN, SP)              |
        MCBSP_FMKS(PCR, FSXM, INTERNAL)         |
        MCBSP_FMKS(PCR, FSRM, EXTERNAL)         |
        MCBSP_FMKS(PCR, CLKXM, OUTPUT)          |
        MCBSP_FMKS(PCR, CLKRM, INPUT)           |
        MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT)      |
        MCBSP_FMKS(PCR, DXSTAT, DEFAULT)        |
        MCBSP_FMKS(PCR, FSXP, ACTIVELOW)        |
        MCBSP_FMKS(PCR, FSRP, DEFAULT)          |
        MCBSP_FMKS(PCR, CLKXP, FALLING)         |
        MCBSP_FMKS(PCR, CLKRP, DEFAULT)
};

/*! \var MCBSP_Config MCBSP_cfg1
 * \brief Zmienna strukturalna z konfiguracja wszystkich rejestrow portu MCBSP1
 */
MCBSP_Config MCBSP_cfg1 = {
		// Wartosc wpisana do rejestru SPCR portu MCBSP1
        MCBSP_FMKS(SPCR, FREE, NO)              |
        MCBSP_FMKS(SPCR, SOFT, NO)              |
        MCBSP_FMKS(SPCR, FRST, YES)             |
        MCBSP_FMKS(SPCR, GRST, YES)             |
        MCBSP_FMKS(SPCR, XINTM, XRDY)           |
        MCBSP_FMKS(SPCR, XSYNCERR, NO)          |
        MCBSP_FMKS(SPCR, XRST, YES)             |
        MCBSP_FMKS(SPCR, DLB, OFF)              |
        MCBSP_FMKS(SPCR, RJUST, RZF)            |
        MCBSP_FMKS(SPCR, CLKSTP, DISABLE)       |
        MCBSP_FMKS(SPCR, DXENA, OFF)            |
        MCBSP_FMKS(SPCR, RINTM, RRDY)           |
        MCBSP_FMKS(SPCR, RSYNCERR, NO)          |
        MCBSP_FMKS(SPCR, RRST, YES),
        // Wartosc wpisana do rejestru RCR portu MCBSP1
        MCBSP_FMKS(RCR, RPHASE, SINGLE)         |
        MCBSP_FMKS(RCR, RFRLEN2, DEFAULT)       |
        MCBSP_FMKS(RCR, RWDLEN2, DEFAULT)       |
        MCBSP_FMKS(RCR, RCOMPAND, MSB)          |
        MCBSP_FMKS(RCR, RFIG, NO)               |
        MCBSP_FMKS(RCR, RDATDLY, 0BIT)          |
        MCBSP_FMKS(RCR, RFRLEN1, OF(1))         |
        MCBSP_FMKS(RCR, RWDLEN1, 16BIT)         |
        MCBSP_FMKS(RCR, RWDREVRS, DISABLE),
        // Wartosc wpisana do rejestru XCR portu MCBSP1
        MCBSP_FMKS(XCR, XPHASE, SINGLE)         |
        MCBSP_FMKS(XCR, XFRLEN2, DEFAULT)       |
        MCBSP_FMKS(XCR, XWDLEN2, DEFAULT)       |
        MCBSP_FMKS(XCR, XCOMPAND, MSB)          |
        MCBSP_FMKS(XCR, XFIG, NO)               |
        MCBSP_FMKS(XCR, XDATDLY, 0BIT)          |
        MCBSP_FMKS(XCR, XFRLEN1, OF(1))         |
        MCBSP_FMKS(XCR, XWDLEN1, 16BIT)         |
        MCBSP_FMKS(XCR, XWDREVRS, DISABLE),
        // Wartosc wpisana do rejestru SRGR portu MCBSP1
        MCBSP_FMKS(SRGR, GSYNC, DEFAULT)        |
        MCBSP_FMKS(SRGR, CLKSP, DEFAULT)        |
        MCBSP_FMKS(SRGR, CLKSM, DEFAULT)        |
        MCBSP_FMKS(SRGR, FSGM, DEFAULT)         |
        MCBSP_FMKS(SRGR, FPER, DEFAULT)         |
        MCBSP_FMKS(SRGR, FWID, DEFAULT)         |
        MCBSP_FMKS(SRGR, CLKGDV, DEFAULT),
        // Wartosc wpisana do rejestru MCR portu MCBSP1
        MCBSP_MCR_DEFAULT,
        // Wartosc wpisana do rejestru RCER portu MCBSP1
        MCBSP_RCER_DEFAULT,
        // Wartosc wpisana do rejestru XCER portu MCBSP1
        MCBSP_XCER_DEFAULT,
        // Wartosc wpisana do rejestru PCR portu MCBSP1
        MCBSP_FMKS(PCR, XIOEN, SP)              |
        MCBSP_FMKS(PCR, RIOEN, SP)              |
        MCBSP_FMKS(PCR, FSXM, EXTERNAL)         |
        MCBSP_FMKS(PCR, FSRM, EXTERNAL)         |
        MCBSP_FMKS(PCR, CLKXM, INPUT)           |
        MCBSP_FMKS(PCR, CLKRM, INPUT)           |
        MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT)      |
        MCBSP_FMKS(PCR, DXSTAT, DEFAULT)        |
        MCBSP_FMKS(PCR, FSXP, ACTIVEHIGH)       |
        MCBSP_FMKS(PCR, FSRP, ACTIVEHIGH)       |
        MCBSP_FMKS(PCR, CLKXP, FALLING)         |
        MCBSP_FMKS(PCR, CLKRP, RISING)
};

/*! \var AIC23_Params AIC23_cfg
 * \brief Zmienna strukturalna z konfiguracja wszystkich rejestrow ukladu kodeka
 */

AIC23_Params AIC23_cfg = {
    0x0017, // 0 DSK6713_AIC23_LEFTINVOL  Glosnosc lewego wejscia liniowego
    0x0017, // 1 DSK6713_AIC23_RIGHTINVOL Glosnosc prawego wejscia liniowego
    0x007f, // 2 DSK6713_AIC23_LEFTHPVOL  Glosnosc lewego wyjscia sluchawkowego
    0x007f, // 3 DSK6713_AIC23_RIGHTHPVOL Glosnosc prawego wyjscia sluchawkowego
    0x0015, // 4 DSK6713_AIC23_ANAPATH    Konfiguracja polaczen analogowych
    0x0000, // 5 DSK6713_AIC23_DIGPATH    Konfiguracja wewnetrznych ukladow cyfrowych
    0x0000, // 6 DSK6713_AIC23_POWERDOWN  Kontrola poboru mocy
    0x0043, // 7 DSK6713_AIC23_DIGIF      Konfiguracja cyfrowego interfejsu audio
    0x0001, // 8 DSK6713_AIC23_SAMPLERATE Konfiguracja szybkosci probkowania
    0x0001  // 9 DSK6713_AIC23_DIGACT     Aktywacja interfejsu cyfrowego
};


/*!\fn void SetAudioRegister(MCBSP_Handle hMcbsp, Uint16 RegNum, Uint16 RegVal)
 * \brief Funkcja, ktora konfiguruje wybrany rejestr ukladu kodeka audio
 * \param hMcbsp uchwyt do portu MCBSP, ktory sluzy do konfiguracji kodeka audio ( w tym przypadku jest nim MCBSP0)
 * \param RegNum number rejestru, ktorego wartosc ma byc ustawiona
 * \param RegVal wartosc, ktora ma byc wpisana do rejestru RegNum
 */
void SetAudioRegister(MCBSP_Handle hMcbsp, Uint16 RegNum, Uint16 RegVal)
{
	Uint16 temp;   
    // Wait for XRDY signal before writing data to DXR
    while (!MCBSP_xrdy(hMcbsp));
	// Mask off lower 9 bits
    temp = (RegNum << 9) | (RegVal & 0x01ff);
    // Write 16 bit data value to DXR 
    MCBSP_write(hMcbsp,  temp);
    // Wait for XRDY, state machine will not update until next McBSP clock
    while (MCBSP_xrdy(hMcbsp));
}

/*!\fn void SetAllAudioParams(AIC23_Params *params)
 * \brief Funkcja, ktora konfiguruje wszystkie rejestry ukladu kodeka
 * \param params wskaznik na zmienna strukturalna z wartosciami wszystkich rejestrow ukladu kodeka
 */
void SetAllAudioParams(AIC23_Params *params)
{
    Int i;
    // Reset the AIC23
    SetAudioRegister(hMcbsp0, 0x0F, 0);    
    // Assign each register //
    for (i = 0; i < 10; i++) 
    {
        SetAudioRegister(hMcbsp0, i, params->regs[i]);
    }
}

void setupMCBSP(void)
{
	init_circular_buffer(&input, in_array, 128);
	init_circular_buffer(&output, out_array, 128);
	//Konfiguracja portu MCBSP0
	hMcbsp0 =  MCBSP_open(MCBSP_DEV0, MCBSP_OPEN_RESET);
	MCBSP_config(hMcbsp0, &MCBSP_cfg0);
	MCBSP_start(hMcbsp0, MCBSP_XMIT_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 100);

	//Reset ukladu kodeka audio
	SetAudioRegister(hMcbsp0, 15, 0); //RESET UKLADU KODEKA

	//Konfiguracja portu MCBSP1
	hMcbsp1 =  MCBSP_open(MCBSP_DEV1, MCBSP_OPEN_RESET);
	MCBSP_config(hMcbsp1, &MCBSP_cfg1);
	mcbsp1RcvEventId = MCBSP_getRcvEventId(hMcbsp1);
	IRQ_map(mcbsp1RcvEventId,14);
	IRQ_reset(mcbsp1RcvEventId);
	IRQ_enable(mcbsp1RcvEventId);

	mcbsp1XmtEventId = MCBSP_getXmtEventId(hMcbsp1);
	IRQ_map(mcbsp1XmtEventId,15);
	IRQ_reset(mcbsp1XmtEventId);
	IRQ_enable(mcbsp1XmtEventId);
	circ_put(&output,0);
	circ_put(&output,0);
	circ_put(&output,0);
	circ_put(&output,0);
	circ_put(&output,0);
	circ_put(&output,0);
	MCBSP_start(hMcbsp1, MCBSP_XMIT_START | MCBSP_RCV_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 220);

	//Konfiguracja wszystkich rejestrow ukladu kodeka audio
 	SetAllAudioParams(&AIC23_cfg);

}
/*!\fn interrupt void receiver()
 * \brief Funkcja obslugi przerwania od odbiornika portu MCBSP1
 */
interrupt void receiver()
{
	Int16 s;
	s=MCBSP_read(hMcbsp1);
	if(circ_put(&input,s))
		set_err(INPUT_BUFFER_FULL);
}
interrupt void transmitter()
{
	Int16 s=0;
	if(circ_get(&output,&s))
		set_err(OUTPUT_BUFFER_EMPTY);
	MCBSP_write(hMcbsp1,s);
}

void writeData(Int16 x)
{
	while(!MCBSP_xrdy(hMcbsp1));
	MCBSP_write(hMcbsp1,x);
}
