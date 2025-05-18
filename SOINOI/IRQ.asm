; LABORATORIUM PROCESOROW SYGNALOWYCH
;\author GRZEGORZ JOZWIAK
;\file IRQ.asm
;\brief Definicja tablicy wektorow przerwan dla procesora tms320c6717

 .global _c_int00
 .global _IRQ_service
 .global _receiver
 .global _transmitter
VEC_ENTRY .macro addr
 stw b0,*--b15
 mvkl addr,b0
 mvkh addr,b0
 b b0
 ldw *b15++,b0
 nop 2
 nop
 nop
 .endm

Default:
 b irp
 nop 5

DefaultNMI:
 b nrp
 nop 5

 .sect ".text:vecs"
 .align 1024
_IRQ_service:
 VEC_ENTRY _c_int00 ;   00
 VEC_ENTRY DefaultNMI ; 01
 VEC_ENTRY Default ;    02
 VEC_ENTRY Default ;    03
 VEC_ENTRY Default ;    04
 VEC_ENTRY Default ;    05
 VEC_ENTRY Default ;    06
 VEC_ENTRY Default ;    07
 VEC_ENTRY Default ;    08
 VEC_ENTRY Default ;    09
 VEC_ENTRY Default ;    10
 VEC_ENTRY Default ;    11
 VEC_ENTRY Default ;    12
 VEC_ENTRY Default ;    13
 VEC_ENTRY _receiver;   14
 VEC_ENTRY _transmitter ;    15
