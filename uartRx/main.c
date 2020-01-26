#include "_ffmc16.h"
#include "extern.h"
#include "monitor.h"

#define RS IO_PDR2.bit.P24		//RS at P24
#define RW IO_PDR5.bit.P53		//RW at P53
#define E IO_PDR5.bit.P52		//E at P52
#define BF IO_PDR2.bit.P23		//Busy Flag at P23
#define LCD_DATA_IN IO_DDR2.byte = 0xB0		//sets LCD data bus <P23:P20> to input (reading from LCD)
#define LCD_DATA_OUT IO_DDR2.byte = 0xBF	//sets LCD data bus <P23:P20> to input (reading from LCD)
#define LCD_DATA IO_PDR2.byte	//LCD Data Bus (4-bit)

/* Function prototypes */
void init_LCD();
void inst_Ctrl(unsigned char data);
void data_Ctrl(unsigned char data);
void inst_Ctrl_4bit(unsigned char data);
void read_BF();
void delay(long int);
void LCD_Print(unsigned char line_num);
void setLine(char line_number);
void Home();
void ON1();
void ON2();
void ON3();
void ON4();
void OFF1();
void OFF2();
void OFF3();
void OFF4();

int Rx_data;
int temp;
int state1;
int state2;
int state3;
int state4;


void main(void)
{
	long int i;
	
    __set_il(7);
	__EI();		/* enable interrupt(for Accemic) */
			//set Port P52-P57 as digital I/O (not analog input) -- very important
	
	IO_DDR1.byte=0xFF;
	IO_PDR1.byte=0xFF;
	IO_DDR2.bit.D25=0;
	IO_DDR4.bit.D40 = 0;	
	
	IO_DDR2.byte = 0xBF;		//sets all Port 2 to output except P26
	IO_DDR5.byte = 0x0C;		//sets all Port 5 to input except P52 & P53
	IO_ADER.byte = 0x03;		//set Port P52-P57 as digital I/O (not analog input) -- very important
		
	IO_ICR13.byte = 0x02;
	IO_CDCR1.byte = 0x80;
	IO_SMR1.byte = 0x03;
	IO_SCR1.byte = 0x17;
	IO_SSR1.byte = 0x00;
	
	Rx_data=0;
	state1=0;
	state2=0;
 	state3=0;
	state4=0;
	
	init_LCD();
	while(1)
	{
	if(IO_SSR1.bit.RDRF)
		{
			Rx_data = IO_SIDR1.byte;
			temp=~(Rx_data-48);
			if(Rx_data==0x31){//(enable)living room light code=0x31
			IO_PDR1.byte=temp;
			IO_PDR1.bit.P14=IO_PDR1.bit.P14^1;
			state1=1;
			ON1(); OFF2(); OFF3(); OFF4();
				if(state2==1){
				IO_PDR1.bit.P15=IO_PDR1.bit.P15^1;
				ON1(); ON2(); OFF3(); OFF4();
				}
				if(state3==1){
				IO_PDR1.bit.P16=IO_PDR1.bit.P16^1;
				ON1(); ON2(); ON3(); OFF4();
				}
				if(state4==1){
				IO_PDR1.bit.P17=IO_PDR1.bit.P17^1;
				ON1(); ON2(); ON3(); ON4();
				}
			}
			else if(Rx_data==0x35){//(disable)living room light code=0x35
			IO_PDR1.byte=temp;
			IO_PDR1.bit.P14=~(IO_PDR1.bit.P14^1);
			state1=0;
			OFF1(); OFF2(); OFF3(); OFF4();
				if(state2==1){
				IO_PDR1.bit.P15=IO_PDR1.bit.P15^1;
				OFF1(); ON2(); OFF3(); OFF4();
				}
				if(state3==1){
				IO_PDR1.bit.P16=IO_PDR1.bit.P16^1;
				OFF1(); ON2(); ON3(); OFF4();
				}
				if(state4==1){
				IO_PDR1.bit.P17=IO_PDR1.bit.P17^1;
				OFF1(); ON2(); ON3(); ON4();
				}
			}
			
			else if(Rx_data==0x32){//(enable)bedroom light code=0x32
			IO_PDR1.byte=temp;
			IO_PDR1.bit.P15=IO_PDR1.bit.P15^1;
			state2=1;
			OFF1(); ON2(); OFF3(); OFF4();
				if(state1==1){
				IO_PDR1.bit.P14=IO_PDR1.bit.P14^1;
				ON1(); ON2(); OFF3(); OFF4();
				}
				if(state3==1){
				IO_PDR1.bit.P16=IO_PDR1.bit.P16^1;
				ON1(); ON2(); ON3(); OFF4();
				}
				if(state4==1){
				IO_PDR1.bit.P17=IO_PDR1.bit.P17^1;
				ON1(); ON2(); ON3(); ON4();
				}
			}
			else if(Rx_data==0x36){//(disable)bedroom light code=0x36
			IO_PDR1.byte=temp;
			IO_PDR1.bit.P15=~(IO_PDR1.bit.P15^1);
			state2=0;
			OFF1(); OFF2(); OFF3(); OFF4();
				if(state1==1){
				IO_PDR1.bit.P14=IO_PDR1.bit.P14^1;
				ON1(); OFF2(); OFF3(); OFF4();
				}
				if(state3==1){
				IO_PDR1.bit.P16=IO_PDR1.bit.P16^1;
				ON1(); OFF2(); ON3(); OFF4();
				}
				if(state4==1){
				IO_PDR1.bit.P17=IO_PDR1.bit.P17^1;
				ON1(); OFF2(); ON3(); ON4();
				}
			}
			
			else if(Rx_data==0x33){//(enable)terrace area light code=0x33
			IO_PDR1.byte=temp;
			IO_PDR1.bit.P16=IO_PDR1.bit.P16^1;
			state3=1;
			OFF1(); OFF2(); ON3(); OFF4();
				if(state1==1){
				IO_PDR1.bit.P14=IO_PDR1.bit.P14^1;
				ON1(); OFF2(); ON3(); OFF4();
				}
				if(state2==1){
				IO_PDR1.bit.P15=IO_PDR1.bit.P15^1;
				ON1(); ON2(); ON3(); OFF4();
				}
				if(state4==1){
				IO_PDR1.bit.P17=IO_PDR1.bit.P17^1;
				ON1(); ON2(); ON3(); ON4();
				}
			}
			else if(Rx_data==0x37){//(disable)terrace area light code=0x37
			IO_PDR1.byte=temp;
			IO_PDR1.bit.P16=~(IO_PDR1.bit.P16^1);
			state3=0;
			OFF1(); OFF2(); OFF3(); OFF4();
				if(state1==1){
				IO_PDR1.bit.P14=IO_PDR1.bit.P14^1;
				ON1(); OFF2(); OFF3(); OFF4();
				}
				if(state2==1){
				IO_PDR1.bit.P15=IO_PDR1.bit.P15^1;
				ON1(); ON2(); OFF3(); OFF4();
				}
				if(state4==1){
				IO_PDR1.bit.P17=IO_PDR1.bit.P17^1;
				ON1(); ON2(); OFF3(); ON4();
				}
			}
			else if(Rx_data==0x34){//(enable)garage area light code=0x34
			IO_PDR1.byte=temp;
			IO_PDR1.bit.P17=IO_PDR1.bit.P17^1;
			state4=1;
			OFF1(); OFF2(); OFF3(); ON4();
				if(state1==1){
				IO_PDR1.bit.P14=IO_PDR1.bit.P14^1;
				ON1(); OFF2(); OFF3(); ON4();
				}
				if(state2==1){
				IO_PDR1.bit.P15=IO_PDR1.bit.P15^1;
				ON1(); ON2(); OFF3(); ON4();
				}
				if(state3==1){
				IO_PDR1.bit.P16=IO_PDR1.bit.P16^1;
				ON1(); ON2(); ON3(); ON4();
				}
			}
			else if(Rx_data==0x38){//(disable)garage area light code=0x38
			IO_PDR1.byte=temp;
			IO_PDR1.bit.P17=~(IO_PDR1.bit.P17^1);
			state4=0;
			OFF1(); OFF2(); OFF3(); OFF4();
				if(state1==1){
				IO_PDR1.bit.P14=IO_PDR1.bit.P14^1;
				ON1(); OFF2(); OFF3(); OFF4();
				}
				if(state2==1){
				IO_PDR1.bit.P15=IO_PDR1.bit.P15^1;
				ON1(); ON2(); OFF3(); OFF4();
				}
				if(state3==1){
				IO_PDR1.bit.P16=IO_PDR1.bit.P16^1;
				ON1(); ON2(); ON3(); OFF4();
				}
			}	
			}		
			else{//awaiting tweet
			IO_PDR1.byte=0xFF;
			//state1=0;
			//state2=0;
			//state3=0;
			//state4=0;
			//OFF1(); OFF2(); OFF3(); OFF4();
			}
	}
}
void setLine(char line_number){
	if(line_number=='1')
		inst_Ctrl(0x80);
	else if(line_number=='2')
		inst_Ctrl(0xC0);
	else if(line_number=='3')
		inst_Ctrl(0x94);
	else if(line_number=='4')
		inst_Ctrl(0xD4);
}

//write 8-bit instruction to Instruction Register (4-bit interface)
void inst_Ctrl(unsigned char data)
{
	LCD_DATA = data >> 4;		//upper 4-bit transfer
	RS = 0; RW = 0; E = 1; 
	delay(1);					//16 us delay
	E = 0;
	LCD_DATA = data;			//lower 4-bit transfer
	RS = 0; RW = 0; E = 1;
	delay(1);					//16 us delay
	E = 0;
	//delay(500);
	read_BF();					//reading busy flag
}


// write 4-bit instruction to Instruction Register (4-bit interface)
void inst_Ctrl_4bit(unsigned char data)
{
	LCD_DATA = data;			//lower 4-bit transfer
	RS = 0; RW = 0; E = 1;
	delay(100);					//1.6 ms delay
	E = 0;
}


//write 8-bit data to LCD Data Register (4-bit interface)
void data_Ctrl(unsigned char data)
{
	LCD_DATA = data >> 4;		//upper 4-bit transfer
	RS = 1; RW = 0; E = 1;
	delay(10);					//16 us delay
	E = 0;
	LCD_DATA = data;			//lower 4-bit transfer
	RS = 1; RW = 0; E = 1;
	delay(10);					//16 us delay
	E = 0;
	read_BF();					//reading busy flag
}


//initialize LCD routine
void init_LCD()
{
	delay(1000);				//15 ms LCD startup delay
	inst_Ctrl_4bit(0x03);		
	delay(246);					//4.1 ms delay
	inst_Ctrl_4bit(0x03);		
	delay(6);					//100 us delay
	inst_Ctrl_4bit(0x03);		
	delay(246);					//4.1 ms delay
	inst_Ctrl_4bit(0x02);		
	delay(100);					//wait for previous inst to finish
	inst_Ctrl(0x28);			//funciton set: 4-bit; dual line
	inst_Ctrl(0x08);			//display off
	inst_Ctrl(0x01);			//display clear
	inst_Ctrl(0x06);			//entry mode: increment; shift off
	inst_Ctrl(0x0C);			//display on: cursor on; blink off
	delay(1000);
}

//adjustable delay routine
void delay(long int t)
{
	long int i;
	for(i=0;i<t;i++);			//1 loop is equal to 16 us
}

//reading busy flag
void read_BF()
{
	unsigned char busy_flag;
	LCD_DATA_IN;
	RS = 0;						//select IR
	RW = 1;						//set LCD mode to read
	E = 1;						//set enable to high
	do{
		busy_flag = BF;			//read busy flag
	}while(busy_flag);
	
	E = 0;
	LCD_DATA_OUT;
}
void ON1(){
	setLine('1');
	data_Ctrl('1');	
	data_Ctrl('.');
	data_Ctrl('L');
	data_Ctrl('I');
	data_Ctrl('V');
	data_Ctrl('I');
	data_Ctrl('N');
	data_Ctrl('G');
	data_Ctrl(' ');
	data_Ctrl('R');
	data_Ctrl('O');
	data_Ctrl('O');
	data_Ctrl('M');
	data_Ctrl(':');
	data_Ctrl(' ');
	data_Ctrl('O');
	data_Ctrl('N');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
}
void OFF1(){
	setLine('1');
	data_Ctrl('1');	
	data_Ctrl('.');
	data_Ctrl('L');
	data_Ctrl('I');
	data_Ctrl('V');
	data_Ctrl('I');
	data_Ctrl('N');
	data_Ctrl('G');
	data_Ctrl(' ');
	data_Ctrl('R');
	data_Ctrl('O');
	data_Ctrl('O');
	data_Ctrl('M');
	data_Ctrl(':');
	data_Ctrl(' ');
	data_Ctrl('O');
	data_Ctrl('F');
	data_Ctrl('F');
	data_Ctrl(' ');
	data_Ctrl(' ');
}
void ON2(){	
	setLine('2');
	data_Ctrl('2');	
	data_Ctrl('.');
	data_Ctrl('B');
	data_Ctrl('E');
	data_Ctrl('D');
	data_Ctrl('R');
	data_Ctrl('O');
	data_Ctrl('O');
	data_Ctrl('M');
	data_Ctrl(':');
	data_Ctrl(' ');
	data_Ctrl('O');
	data_Ctrl('N');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
}
void OFF2(){	
	setLine('2');
	data_Ctrl('2');	
	data_Ctrl('.');
	data_Ctrl('B');
	data_Ctrl('E');
	data_Ctrl('D');
	data_Ctrl('R');
	data_Ctrl('O');
	data_Ctrl('O');
	data_Ctrl('M');
	data_Ctrl(':');
	data_Ctrl(' ');
	data_Ctrl('O');
	data_Ctrl('F');
	data_Ctrl('F');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
}

void ON3(){	
	setLine('3');
	data_Ctrl('3');	
	data_Ctrl('.');
	data_Ctrl('T');
	data_Ctrl('E');
	data_Ctrl('R');
	data_Ctrl('R');
	data_Ctrl('A');
	data_Ctrl('C');
	data_Ctrl('E');
	data_Ctrl(':');
	data_Ctrl(' ');
	data_Ctrl('O');
	data_Ctrl('N');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
}
void OFF3(){	
	setLine('3');
	data_Ctrl('3');	
	data_Ctrl('.');
	data_Ctrl('T');
	data_Ctrl('E');
	data_Ctrl('R');
	data_Ctrl('R');
	data_Ctrl('A');
	data_Ctrl('C');
	data_Ctrl('E');
	data_Ctrl(':');
	data_Ctrl(' ');
	data_Ctrl('O');
	data_Ctrl('F');
	data_Ctrl('F');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
}
void ON4(){
	setLine('4');
	data_Ctrl('4');	
	data_Ctrl('.');
	data_Ctrl('G');
	data_Ctrl('A');
	data_Ctrl('R');
	data_Ctrl('A');
	data_Ctrl('G');
	data_Ctrl('E');
	data_Ctrl(':');
	data_Ctrl(' ');
	data_Ctrl('O');
	data_Ctrl('N');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');	
}
void OFF4(){
	setLine('4');
	data_Ctrl('4');	
	data_Ctrl('.');
	data_Ctrl('G');
	data_Ctrl('A');
	data_Ctrl('R');
	data_Ctrl('A');
	data_Ctrl('G');
	data_Ctrl('E');
	data_Ctrl(':');
	data_Ctrl(' ');
	data_Ctrl('O');
	data_Ctrl('F');
	data_Ctrl('F');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');
	data_Ctrl(' ');	
}


/* Vector Table */
#pragma section INTVECT,locate=0xfffc00
#pragma intvect _start		0x8		0x0	/* Reset Vector */
