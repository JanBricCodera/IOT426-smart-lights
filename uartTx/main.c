#include "_ffmc16.h"
#include "extern.h"
#include "monitor.h"

int tx_flag;
void main(void){
__set_il(7);
__EI();

IO_DDR2.bit.D25=0;
IO_DDR4.bit.D42=1;
IO_ICR13.byte=0x00;
IO_CDCR1.byte=0x08;
IO_SMR1.byte=0x19;
IO_SCR1.byte=0x21;
IO_SSR1.bit.TIE=1;

tx_flag=0;
while(1){

	while(IO_PDR2.bit.P25);
	IO_SODR1.byte=0x13;
}
}
/*****************************************************************************
interrupt routine
******************************************************************************/
__interrupt void TXt_int(void){
	tx_flag=1;
}
/* Vector Table */
#pragma section INTVECT,locate=0xfffc00
#pragma intvect _start 0x8 0x0
#pragma intvect TXt_int 38
