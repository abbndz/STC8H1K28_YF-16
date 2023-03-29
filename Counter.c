/*-------------------------------------------------------------*/
/* --- by ABBN ------------------------------------------------*/
/* --- STC8H1K28 MCU Counter Programme ------------------------*/
/* --- Carte (module) : YF-16  --------------------------------*/
/* --- Mobile: (213)770502578 ---------------------------------*/
/* --- Web: www.abbndz.com ------------------------------------*/
/* --- Web: www.abbndz.net ------------------------------------*/
/* --- Date : 21/03/2023 --------------------------------------*/
/*-------------------------------------------------------------*/

/*GPIOs: P0.0~P0.3, P1, P2, P3, P5.4
P1 = 8 Seg didital
1=P2.6, 2=P2.7, 3=P0.0, 4=P0.3, 5=P0.2, 6=P0.1.
k1=P3.4, k2=P3.5, k3=P5.4
in0=pnp=P2.0, in1=npn=P2.1, out=P2.2
*/


#include "reg51.h"
#include "intrins.h"

#define MAIN_Fosc 24000000L
typedef unsigned char u8;
typedef unsigned int u16;

sfr TH2 = 0xD6;
sfr TL2 = 0xD7;
sfr IE2 = 0xAF;
sfr INTCLKO = 0x8f;
sfr AUXR = 0x8E;
sfr P_SW1 = 0xA2;
sfr P_SW2 = 0xBA;
sfr P4 = 0xC0;
sfr P5 = 0xC8;

sfr P1M1 = 0x91;
sfr P1M0 = 0x92;
sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xB1;
sfr P3M0 = 0xB2;
sfr P4M1 = 0xB3;
sfr P4M0 = 0xB4;
sfr P5M1 = 0xC9;
sfr P5M0 = 0xCA;
sfr P6M1 = 0xCB;
sfr P6M0 = 0xCC;
sfr P7M1 = 0xE1;
sfr P7M0 = 0xE2;
sfr RSTCFG = 0xff;

sfr IAP_DATA = 0xC2;
sfr IAP_ADDRH = 0xC3;
sfr IAP_ADDRL = 0xC4;
sfr IAP_CMD = 0xC5;
sfr IAP_TRIG = 0xC6;
sfr IAP_CONTR = 0xC7;
sfr IAP_TPS = 0xF5;

sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;
sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;
sbit P40 = P4^0;
sbit P41 = P4^1;
sbit P42 = P4^2;
sbit P43 = P4^3;
sbit P44 = P4^4;
sbit P45 = P4^5;
sbit P46 = P4^6;
sbit P47 = P4^7;
sbit P50 = P5^0;
sbit P51 = P5^1;
sbit P52 = P5^2;
sbit P53 = P5^3;
sbit P54 = P5^4;
sbit P55 = P5^5;
sbit P56 = P5^6;
sbit P57 = P5^7;


#define ENLVR 0x40 //RSTCFG.6
#define LVD2V0 0x00 //LVD@2.0V
#define LVD2V4 0x01 //LVD@2.4V
#define LVD2V7 0x02 //LVD@2.7V
#define LVD3V0 0x03 //LVD@3.0V
//AUXINTIF EFH - INT4IF INT3IF INT2IF - T4IF T3IF T2IF
#define AUXINTIF 0xEF
//sbit INT2IF = AUXINTIF^4;
//sbit INT3IF = AUXINTIF^5;
//sbit INT4IF = AUXINTIF^6;

#define Timer0_Reload (65536UL -(MAIN_Fosc / 1000)) // Timer0 interrupt frequency, 1000 times/second
#define PWMA_ENO (*(unsigned char volatile xdata *) 0xFEB1)
#define PWMA_PS (*(unsigned char volatile xdata *) 0xFEB2)
#define PWMB_ENO (*(unsigned char volatile xdata *) 0xFEB5)
#define PWMB_PS (*(unsigned char volatile xdata *) 0xFEB6)
#define PWMA_CR1 (*(unsigned char volatile xdata *) 0xFEC0)
#define PWMB_CR1 (*(unsigned char volatile xdata *) 0xFEE0)
#define PWMA_CR2 (*(unsigned char volatile xdata *) 0xFEC1)
#define PWMA_SMCR (*(unsigned char volatile xdata *) 0xFEC2)
#define PWMA_ETR (*(unsigned char volatile xdata *) 0xFEC3)
#define PWMA_IER (*(unsigned char volatile xdata *) 0xFEC4)
#define PWMB_IER (*(unsigned char volatile xdata *) 0xFEE4)
#define PWMA_SR1 (*(unsigned char volatile xdata *) 0xFEC5)
#define PWMA_SR2 (*(unsigned char volatile xdata *) 0xFEC6)
#define PWMB_SR1 (*(unsigned char volatile xdata *) 0xFEE5)
#define PWMA_EGR (*(unsigned char volatile xdata *) 0xFEC7)
#define PWMA_CCMR1 (*(unsigned char volatile xdata *) 0xFEC8)
#define PWMB_CCMR1 (*(unsigned char volatile xdata *) 0xFEE8)
#define PWMA_CCMR2 (*(unsigned char volatile xdata *) 0xFEC9)
#define PWMB_CCMR2 (*(unsigned char volatile xdata *) 0xFEE9)
#define PWMA_CCMR3 (*(unsigned char volatile xdata *) 0xFECA)
#define PWMA_CCMR4 (*(unsigned char volatile xdata *) 0xFECB)
#define PWMA_CCER1 (*(unsigned char volatile xdata *) 0xFECC)
#define PWMA_CCER2 (*(unsigned char volatile xdata *) 0xFECD)
#define PWMB_CCER1 (*(unsigned char volatile xdata *) 0xFEEC)
#define PWMB_CCER2 (*(unsigned char volatile xdata *) 0xFEED)
#define PWMA_CNTR (*(unsigned int volatile xdata *) 0xFECE)
#define PWMA_CNTRH (*(unsigned char volatile xdata *) 0xFECE)
#define PWMA_CNTRL (*(unsigned char volatile xdata *) 0xFECF)
#define PWMA_PSCRH (*(unsigned char volatile xdata *) 0xFED0)
#define PWMA_PSCRL (*(unsigned char volatile xdata *) 0xFED1)
#define PWMA_ARR (*(unsigned int volatile xdata *) 0xFED2)
#define PWMA_ARRH (*(unsigned char volatile xdata *) 0xFED2)
#define PWMA_ARRL (*(unsigned char volatile xdata *) 0xFED3)
#define PWMA_RCR (*(unsigned char volatile xdata *) 0xFED4)
#define PWMA_CCR1 (*(unsigned int volatile xdata *) 0xFED5)
#define PWMA_CCR1H (*(unsigned char volatile xdata *) 0xFED5)
#define PWMA_CCR1L (*(unsigned char volatile xdata *) 0xFED6)
#define PWMA_CCR2 (*(unsigned int volatile xdata *) 0xFED7)
#define PWMA_CCR2H (*(unsigned char volatile xdata *) 0xFED7)
#define PWMA_CCR2L (*(unsigned char volatile xdata *) 0xFED8)
#define PWMA_CCR3 (*(unsigned int volatile xdata *) 0xFED9)
#define PWMA_CCR3H (*(unsigned char volatile xdata *) 0xFED9)
#define PWMA_CCR3L (*(unsigned char volatile xdata *) 0xFEDA)
#define PWMA_CCR4 (*(unsigned int volatile xdata *) 0xFEDB)
#define PWMA_CCR4H (*(unsigned char volatile xdata *) 0xFEDB)
#define PWMA_CCR4L (*(unsigned char volatile xdata *) 0xFEDC)
#define PWMA_BKR (*(unsigned char volatile xdata *) 0xFEDD)
#define PWMA_DTR (*(unsigned char volatile xdata *) 0xFEDE)
#define PWMA_OISR (*(unsigned char volatile xdata *) 0xFEDF)
	
#define P0INTE (*(unsigned char volatile xdata *) 0xFD00)
#define P1INTE (*(unsigned char volatile xdata *) 0xFD01)
#define P2INTE (*(unsigned char volatile xdata *) 0xFD02)
#define P3INTE (*(unsigned char volatile xdata *) 0xFD03)
#define P5INTE (*(unsigned char volatile xdata *) 0xFD05)
	
#define P0INTF (*(unsigned char volatile xdata *) 0xFD10)
#define P1INTF (*(unsigned char volatile xdata *) 0xFD11)
#define P2INTF (*(unsigned char volatile xdata *) 0xFD12)
#define P3INTF (*(unsigned char volatile xdata *) 0xFD13)
#define P5INTF (*(unsigned char volatile xdata *) 0xFD15)
	
#define P0IM0 (*(unsigned char volatile xdata *) 0xFD20)
#define P0IM1 (*(unsigned char volatile xdata *) 0xFD30)
#define P1IM0 (*(unsigned char volatile xdata *) 0xFD21)
#define P1IM1 (*(unsigned char volatile xdata *) 0xFD31)
#define P2IM0 (*(unsigned char volatile xdata *) 0xFD22)
#define P2IM1 (*(unsigned char volatile xdata *) 0xFD32)
#define P3IM0 (*(unsigned char volatile xdata *) 0xFD23)
#define P3IM1 (*(unsigned char volatile xdata *) 0xFD33)
#define P5IM0 (*(unsigned char volatile xdata *) 0xFD25)
#define P5IM1 (*(unsigned char volatile xdata *) 0xFD35)


/************* local variable declaration **************/
u8 keytma,keytmb,keytmc,inttm;
bit k0a,k0b,k0c;
bit k1a,k1b,k1c; //last keys flag
bit kpa,kpb,kpc; //keys presed
bit kppa,kppb,kppc; //keys long presed
bit cnt_dir_aut;// 0 = man (l'un des deux input) , 1 = auto (les deux input).
bit cnt_dir_sel;//0 = + , 1 = -.
bit disp_cln_on;//0 = off , 1 = on.
u8  disp_cln_ind,disp_cln_tm;

u8  LED0,LED1,LED2,LED3,LED4,LED5,LED6,LED7;        //
u8  disp_ind;
u8  disp_mod;

u16  T0_cnt, T1_cnt; //


sbit PCOM1 = P2^6;
sbit PCOM2 = P2^7;
sbit PCOM3 = P0^0;
sbit PCOM4 = P0^3;
sbit PCOM5 = P0^2;
sbit PCOM6 = P0^1;


#define P3PU        (*(unsigned char volatile xdata *)0xfe13)


/***************************** display **********************************/
u8 code t_display[]={                      
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
  0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,
//black  -    .			H    J    K    L    N    o    P    U     t    G    q    r   M    y
  0x00,	0x40,	0x80, 0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
//0xFF,	0xBF,	0x7F,	0x89,0xE1,0xC7,0x38,0xC8,0xA3,0x8C,0xC1,0x87,0xC2,0x98,0xAF,0xC8,0x91,
	//0. 		1. 	2. 		3. 		4. 	5. 		6. 7. 8. 9. -1
    0xBF,0x86,0xDB,	0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    


/***************************** Var **********************************/



void delay_ms(u8 ms);
void delay_set_LED8();
void IncDecT0(void); 
void SetDir (void);
void set_key_k1_p(void); 	// k1+
void set_key_k3_p(void); 	// k3-
void set_key_k2_p(void); 	// k2 cclear
void set_key_k1_pp(void); 	// k1+
void set_key_k3_pp(void); 	// k3-
void set_key_k2_pp(void); 	// k2 cclear
void keysScan(void);
void DisplayScan(void);
void Inc_cnt_pp_mm(void);
void Set_p_out(void); 
		
void IapIdle() {
	IAP_CONTR = 0; //Disable IAP function
	IAP_CMD = 0; //Clear command register
	IAP_TRIG = 0; //Clear trigger register
	IAP_ADDRH = 0x80; //Set the address to a non-IAP area
	IAP_ADDRL = 0;
}


u8 IapReadchar(int addr) {
	u8 dat;
	IAP_CONTR = 0x80; //Enable IAP
	IAP_TPS = 12; //Set the erasing wait parameter of 12MHz
	IAP_CMD = 1; //Set IAP read command
	IAP_ADDRL = addr; //Set IAP low address
	IAP_ADDRH = addr >> 8; //Set IAP high address
	IAP_TRIG = 0x5a; //Write trigger command (0x5a)
	IAP_TRIG = 0xa5; //Write trigger command (0xa5)
	_nop_();
	_nop_();	
	dat = IAP_DATA; //Read IAP data
	IapIdle(); //Disable IAP function
	return dat;
}

u16 IapReadInt(int addr) {
	u16 dat;
	u8 datL,datH;
	IAP_CONTR = 0x80; //Enable IAP
	IAP_TPS = 12; //Set the erasing wait parameter of 12MHz
	IAP_CMD = 1; //Set IAP read command
	IAP_ADDRL = addr; //Set IAP low address
	IAP_ADDRH = addr >> 8; //Set IAP high address
	IAP_TRIG = 0x5a; //Write trigger command (0x5a)
	IAP_TRIG = 0xa5; //Write trigger command (0xa5)
	_nop_();
	_nop_();
	datL = IAP_DATA; //Read IAP data
	//IapIdle(); //Disable IAP function
	//_nop_();
	//_nop_();
	//IAP_CONTR = 0x80; //Enable IAP
	//IAP_TPS = 12; //Set the erasing wait parameter of 12MHz
	//IAP_CMD = 1; //Set IAP read command	
	addr++;
	IAP_ADDRL = addr; //Set IAP low address
	IAP_ADDRH = addr >> 8; //Set IAP high address
	IAP_TRIG = 0x5a; //Write trigger command (0x5a)
	IAP_TRIG = 0xa5; //Write trigger command (0xa5)
	_nop_();
	_nop_();
	datH = IAP_DATA; //Read IAP data	
	IapIdle(); //Disable IAP function
	dat = 0;
	dat  += datL;
	dat  += (datH*256);
	return dat;
}

void IapProgramChar(int addr, u8 dat) {
	IAP_CONTR = 0x80; //Enable IAP
	IAP_TPS = 12; //Set the erasing wait parameter of 12MHz
	IAP_CMD = 2; //Set IAP writing command
	IAP_ADDRL = addr; //Set IAP low address
	IAP_ADDRH = addr >> 8; //Set IAP high address
	IAP_DATA = dat; //Write IAP data
	IAP_TRIG = 0x5a; //Write trigger command (0x5a)
	IAP_TRIG = 0xa5; //Write trigger command (0xa5)
	_nop_();
	_nop_();
	IapIdle(); //Disable IAP function	
}

void IapProgramInt(int addr, u16 dat) {
	u8 datL,datH;
	datL = dat % 256;
	datH = dat / 256;
	IAP_CONTR = 0x80; //Enable IAP
	IAP_TPS = 12; //Set the erasing wait parameter of 12MHz
	IAP_CMD = 2; //Set IAP writing command
	IAP_ADDRL = addr; //Set IAP low address
	IAP_ADDRH = addr >> 8; //Set IAP high address
	IAP_DATA = datL; //Write IAP data
	IAP_TRIG = 0x5a; //Write trigger command (0x5a)
	IAP_TRIG = 0xa5; //Write trigger command (0xa5)
	_nop_();
	_nop_();
	//IapIdle(); //Disable IAP function
	//IAP_CONTR = 0x80; //Enable IAP
	//IAP_TPS = 12; //Set the erasing wait parameter of 12MHz
	//IAP_CMD = 2; //Set IAP writing command
	addr++;
	IAP_ADDRL = addr; //Set IAP low address
	IAP_ADDRH = addr >> 8; //Set IAP high address
	IAP_DATA = datH; //Write IAP data
	IAP_TRIG = 0x5a; //Write trigger command (0x5a)
	IAP_TRIG = 0xa5; //Write trigger command (0xa5)
	_nop_();
	_nop_();
	IapIdle(); //Disable IAP function
}

void IapErase(int addr) {
	IAP_CONTR = 0x80; //Enable IAP
	IAP_TPS = 12; //Set the erasing wait parameter of 12MHz
	IAP_CMD = 3; //Set IAP erasing command
	IAP_ADDRL = addr; //Set IAP low address
	IAP_ADDRH = addr >> 8; //Set IAP high address
	IAP_TRIG = 0x5a; //Write trigger command (0x5a)
	IAP_TRIG = 0xa5; //Write trigger command (0xa5)
	_nop_(); //
	IapIdle(); //Disable IAP function
}

void SaveData() {
	u8 dat0;
	IapErase(0x0000);
	IapProgramInt(0x0000,T1_cnt);
	dat0 = 0;
	if (cnt_dir_aut == 1) {
		dat0 += 1;
	}
	IapProgramChar(0x0002,dat0);
}
		
//IapErase(0x0400);
//P0 = IapRead(0x0400); //P0=0xff
//IapProgram(0x0400, 0x12);
//P1 = IapRead(0x0400); //P1=0x12
	
/*	
void Lvd_Isr() interrupt 6 { //ENLVR
	PCON &= ~0x20; //PCON.5; //Clear interrupt flag
	//PCON &= ~0x00; //PCON.5; //Clear interrupt flag
	cnt_dir_aut = 1;
}
*/


void PWMA_ISR() interrupt 26 {	
	//PWMA_SR1 FEC5H BIFA TIFA COMIFA CC4IF CC3IF CC2IF CC1IF UIFA
	//PWMB_SR1 FEE5H BIFB TIFB COMIFB CC8IF CC7IF CC6IF CC5IF UIFB
	if(PWMA_SR1 & 0x02)	{
		PWMA_SR1 &=~0x02; //clear flag									
		PWMA_CCR1 = 0;
		if (inttm > 10) {	
			inttm = 1;
			if (cnt_dir_aut ==1) {			
				cnt_dir_sel = 1; 
				T0_cnt--; 
				delay_set_LED8();	
			} else {
				if (cnt_dir_sel == 0 ) {
					T0_cnt++; 	
				} else {
					T0_cnt--; 	
				}
				delay_set_LED8();
			}				
		}		
		PWMA_CNTR = 0; //clear counter
	}
	PWMA_CCR1 = 0;
	PWMA_SR1 = 0; //clear flag
}


void PWMB_ISR() interrupt 27 {	
	//PWMA_SR1 FEC5H BIFA TIFA COMIFA CC4IF CC3IF CC2IF CC1IF UIFA
	//PWMB_SR1 FEE5H BIFB TIFB COMIFB CC8IF CC7IF CC6IF CC5IF UIFB
	if(PWMB_SR1 & 0x04)	{
		//PWMB_SR1 &=~0x02; //clear flag		
    PWMB_SR1 = 0x00; //clear flag			
		PWMA_CCR1 = 0;
		if (inttm > 10) {	
			inttm = 1;
			if (cnt_dir_aut == 1 ) {			
				cnt_dir_sel = 0; 
				T0_cnt++; 			
				delay_set_LED8();
			} else {
				if (cnt_dir_sel == 0 ) {
					T0_cnt++; 	
				} else {
					T0_cnt--; 	
				  }
				delay_set_LED8();
			  }			
		  }
		PWMA_CNTR = 0; //clear counter
		}
	PWMA_CCR1 = 0;
	PWMB_SR1 = 0; //clear flag
}

//========================================================================
// void main(void)
// V1.0, 12/083/2023
//========================================================================
void main() {
	u8 dat0;
	P0M0 = 0x0f; P0M1 = 0x0f;      
	P1M0 = 0xff; P1M1 = 0x00;  
	//P2M0 = 0xc0; P2M1 = 0xc3; 
	P2M0 = 0xc0; P2M1 = 0xc0; 
	//P3M0 = 0x00; P3M1 = 0x30; 
	P3M0 = 0x00; P3M1 = 0x00; 
	P5M0 = 0x00; P5M1 = 0x00; 

	//P_SW2 |= 0x80;
	//P3PU = 0x30;            //P3.4,P3.5
	//P_SW2 BAH EAXFR - I2C_S[1:0] CMPO_S S4_S S3_S S2_S
	P_SW2 &= 0x7f;   
	disp_ind = 0;
	disp_mod = 0;
	T0_cnt = 0;
	T1_cnt = 0;
	T1_cnt = IapReadInt(0x0000);
	//T1_cnt = IapReadchar(0x0000);
	cnt_dir_sel = 0;
	cnt_dir_aut = 0;	
	dat0 = IapReadchar(0x0002);
	if ((dat0 & 0x01) != 0) {
		cnt_dir_aut = 1;
	}
	keytma = 0;
	keytmb = 0;
	keytmc = 0;
	inttm = 0;
	disp_cln_ind = 0;
	disp_cln_tm = 0;
	delay_set_LED8();
	
	P_SW2 |= 0x80;
	
	//PWMA_PS FEB2H C4PS[1:0] C3PS[1:0] C2PS[1:0] C1PS[1:0]
	//PWMB_PS FEB6H C8PS[1:0] C7PS[1:0] C6PS[1:0] C5PS[1:0]
	PWMA_PS = 0x00; // Advanced PWM Channel Output Pin Selection Bits
	PWMA_PS |= 0x01; // Select 2.0-2.1 channel 1
	PWMB_PS = 0x00; // Advanced PWM Channel Output Pin Selection Bits
	PWMB_PS |= 0x00; // Select 00 P2.1 channel 6
	
	//( Capture PWM1P rising/falling edge)
	//PWMA_CCER1 FECCH CC2NP CC2NE CC2P CC2E CC1NP CC1NE CC1P CC1E
	//PWMA_CCER2 FECDH CC4NP CC4NE CC4P CC4E CC3NP CC3NE CC3P CC3E
	PWMA_CCER1 = 0x00; //CCxE must be cleared before writing to CCMRx to close the channel		
	PWMA_CCER2 = 0x00; //CCxE must be cleared before writing to CCMRx to close the channel
	PWMB_CCER1 = 0x00; //CCxE must be cleared before writing to CCMRx to close the channel
	PWMB_CCER2 = 0x00; //CCxE must be cleared before writing to CCMRx to close the channel
	//PWMA_CCMR1 FEC8H IC1F[3:0] IC1PSC[1:0] CC1S[1:0]
	//PWMB_CCMR1 FEE8H IC5F[3:0] IC5PSC[1:0] CC5S[1:0]
	PWMA_CCMR1 = 0x00;
	PWMA_CCMR1 |= 0x01; //IC1 is mapped on TI1FP1 +++++++++		
	PWMA_CCMR1 |= 0xF0;//ICnF[3:0]: Input capture n filter selection, this bit field 
	//defines the sampling frequency of TIn and the length of the digital filter. (N=1,5)			
	//PWMA_CCMR2 FEC9H IC2F[3:0] IC2PSC[1:0] CC2S[1:0]
	//PWMB_CCMR2 FEE9H IC6F[3:0] IC6PSC[1:0] CC6S[1:0]		
	PWMB_CCMR1 = 0x00;
	PWMB_CCMR2 = 0x00;
	PWMB_CCMR2 |= 0x01; //IC6 is mapped on TI6FP6 +++++++++		
	PWMB_CCMR2 |= 0xF0;//ICnF[3:0]: Input capture n filter selection, this bit field 
	//defines the sampling frequency of TIn and the length of the digital filter. (N=2,6)
	PWMA_CCER1 |= 0x01; // Enable capture function on CC1 ++++++++++++++++++++
	PWMA_CCER1 |= 0x02; // Set the capture polarity to the falling edge of CC1 1: low level is active
	PWMB_CCER1 |= 0x10;//CC6E
	PWMB_CCER1 |= 0x20;//CC6P Set the capture polarity to the falling edge of CC1 1: low level is active
	
	//PWMA_CR1 FEC0H ARPEA CMSA[1:0] DIRA OPMA URSA UDISA CENA
	PWMA_CR1 |= 0x01; // start timing
	PWMB_CR1 |= 0x01; // start timing
	
	//PWMA_IER FEC4H BIEA TIEA COMIEA CC4IE CC3IE CC2IE CC1IE UIEA
	PWMA_IER = 0x02; // Enable capture/compare 1 interrupt
	PWMB_IER |=0x04;// Enable capture/compare 6 interrupt 
			
	/*
	PCON |= 0x20; //PCON.5 LVDF; //Test port
	// RSTCFG = ENLVR | LVD3V0; //Low voltage reset when 3.0V is enabled, no LVD interrupt is generated
	RSTCFG = LVD3V0; //Low voltage interrupt when 3.0V is enabled
	IE |= 0x40;// ELVD = 1; //Enable LVD interrupt
	*/
	
	EA = 1;//Enable CPU interrupt
	
	while(1) {
		delay_ms(1);
		keysScan();
		DisplayScan();
	}
}

//========================================================================
// void delay_ms(u8 ms)
// V1.0: 12/03/2023
//========================================================================
void delay_ms(u8 ms) {
	u16 i;
	do {
		i = MAIN_Fosc / 10000;
		while(--i);   //10T per loop
		}
	while(--ms);
}

void set_key_k1_p() {		// k1+
	if(disp_mod == 0) {	
		cnt_dir_sel = 0; 	
  } else if(disp_mod == 1) {	
		if (disp_cln_ind == 0){
			T1_cnt+=1; 
		} else if (disp_cln_ind == 1){
			T1_cnt+=10; 
		} else if (disp_cln_ind == 2){
			T1_cnt+=100; 
		} else if (disp_cln_ind == 3){
			T1_cnt+=1000; 
		} else if (disp_cln_ind == 4){
			T1_cnt+=10000; 
		}
	} else if(disp_mod == 2) {	
		if(cnt_dir_aut == 0) {
			cnt_dir_aut = 1;
		} else {
			cnt_dir_aut = 0;
		}
	}
	delay_set_LED8();			
}

void set_key_k3_p() {		// k3-
	if(disp_mod == 0) {	
		cnt_dir_sel = 1;	
  } else if(disp_mod == 1) {							
		  if (disp_cln_ind == 0){
			T1_cnt-=1; 
		} else if (disp_cln_ind == 1){
			T1_cnt-=10; 
		} else if (disp_cln_ind == 2){
			T1_cnt-=100; 
		} else if (disp_cln_ind == 3){
			T1_cnt-=1000; 
		} else if (disp_cln_ind == 4){
			T1_cnt-=10000; 
		} 
  } else if(disp_mod == 2) {	
		if(cnt_dir_aut == 0) {
			cnt_dir_aut = 1;
		} else {
			cnt_dir_aut = 0;
		}
  }		
	delay_set_LED8();			
}

void set_key_k2_p() {		// k2 cclear
	u8 dat0;
	if(disp_mod == 0) {
		cnt_dir_sel = 0;	
		T0_cnt = 0;	
		disp_cln_ind = 0;		
  } else if(disp_mod == 1) {	
		if (++disp_cln_ind >= 5){
			disp_cln_ind=0; 		
		}
  } else if(disp_mod == 2) {
		disp_mod = 0;
		SaveData();
		//T1_cnt = 0;
		//T1_cnt += IapReadchar(0x0000);
		T1_cnt = IapReadInt(0x0000);
		cnt_dir_aut = 0;	
		dat0 = IapReadchar(0x0002);
		if ((dat0 & 0x01) != 0) {
			cnt_dir_aut = 1;
		}
  }	
	delay_set_LED8();	
}

void set_key_k1_pp() {		// k1+	
	if(disp_mod == 0) {	
  } else if(disp_mod == 1) {	
  } else if(disp_mod == 2) {	
  }
	delay_set_LED8();
}

void set_key_k3_pp() {		// k3-
	if(disp_mod == 0) {	
  } else if(disp_mod == 1) {	
  } else if(disp_mod == 2) {	
  }
	delay_set_LED8();
}

void set_key_k2_pp() {		// k2 cclear
	u8 dat0;
	disp_cln_ind = 0;
	if(++disp_mod >= 3) {
		disp_mod = 0;
		SaveData();
		//T1_cnt = 0;
		//T1_cnt += IapReadchar(0x0000);
		T1_cnt = IapReadInt(0x0000);
		cnt_dir_aut = 0;	
		dat0 = IapReadchar(0x0002);
		if ((dat0 & 0x01) != 0) {
			cnt_dir_aut = 1;
		}
	}  
	if(disp_mod == 0) {
		//SaveData();
		//T1_cnt = IapReadchar(0x0000);
	}	
	delay_set_LED8();
}

/********************** keys Scan ************************/
void keysScan(void) {
	kpa = 0;
	kpb = 0;
	kpc = 0;
	kppa = 0;
	kppb = 0;
	kppc = 0;
	//k1=P3.4, k2=P3.5, k3=P5.4	
	k0a = P34;// k1+
	k0b = P35;// k2 clr
	k0c = P54;// k3-
	
	if (inttm < 15) {
		inttm++;
	}
  if ((k1a == k0a)&(k0a==0)) {	
    keytma++;		
		if (keytma > 10) {
			if (keytma < 12) {
				kpa = 1;
        keytma = 13;					
			} else {
				if (keytma > 250) {
					if (keytma < 252) {
						kppa = 1;
						keytma = 253;					
					} else {
						keytma = 253;	
					}
				}
			}				
		} 
	} else {
		keytma = 0;
	}			  
	if ((k1b == k0b)&(k0b==0)) {	// k2 clr
		keytmb++;	
		if (keytmb > 10) {
			if (keytmb < 14) {
				kpb = 1;
        keytmb = 15;					
			} else {
				if (keytmb > 250) {
					if (keytmb < 252) {
						kppb = 1;
						keytmb = 253;					
					} else {
						keytmb = 253;	
					}
				}
			}				
		} 				
	} else {
		keytmb = 0;
	}		
	if ((k1c == k0c)&(k0c==0)) {	// k3  --
    keytmc++;		
		if (keytmc > 10) {
			if (keytmc < 14) {
				kpc = 1;
        keytmc = 15;					
			} else {
				if (keytmc > 250) {
					if (keytmc < 252) {
						kppc = 1;
						keytmc = 253;					
					} else {
						keytmc = 253;	
					}
				}
			}				
		} 		
	} else {
		keytmc = 0;
	}	
	if (kpa == 1) {
		set_key_k1_p();
	}
	if (kpb == 1) {
		set_key_k2_p();
	}
	if (kpc == 1) {
		set_key_k3_p();
	}
	if (kppa == 1) {
		set_key_k1_pp();
	}
	if (kppb == 1) {
		set_key_k2_pp();
	}
	if (kppc == 1) {
		set_key_k3_pp();
	}		
	k1a = k0a;
	k1b = k0b;
	k1c = k0c;
}


/********************** Display Scan ************************/
void DisplayScan(void) {   	
	if(++disp_ind >= 6) {
		disp_ind = 0;	
		if (++disp_cln_tm >= 30) {
			disp_cln_tm = 0;
			disp_cln_on = !disp_cln_on;
			delay_set_LED8();	
		}
		Set_p_out();		    	
	}
	PCOM1 = 1;
	PCOM2 = 1;
	PCOM3 = 1;
	PCOM4 = 1;
	PCOM5 = 1;
	PCOM6 = 1;		
	if (disp_ind == 0) {
		P1 = LED0;
		PCOM1 = 0;
	} else if (disp_ind == 1) {
		P1 = LED1;
		PCOM2 = 0;
	} else if (disp_ind == 2) {
		P1 = LED2;
		PCOM3 = 0;
	} else if (disp_ind == 3) {
		P1 = LED3;
		PCOM4 = 0;
	} else if (disp_ind == 4) {
		P1 = LED4;
		PCOM5 = 0;
	} else if (disp_ind == 5) {
		P1 = LED5;
		PCOM6 = 0;
	}				 				
}

void Set_p_out() {	
	if(T1_cnt != 0) {
		if(T0_cnt >= T1_cnt) {
			P22 = 0;
		} else {
			P22 = 1;
		}
	} else {
		P22 = 1;
	}
}

void delay_set_LED8() {		
	 if(disp_mod == 1) {	
		 LED0 = T1_cnt % 10;
		 LED0 = t_display[LED0];
		 LED1 = (T1_cnt % 100)/10;
		 LED1 = t_display[LED1];
		 LED2 = (T1_cnt % 1000)/100;
		 LED2 = t_display[LED2];
		 LED3 = (T1_cnt % 10000) / 1000;
		 LED3 = t_display[LED3];
		 LED4 = (T1_cnt % 100000) / 10000;
		 LED4 = t_display[LED4];
		 LED5 = t_display[12];// C 		
		 if (cnt_dir_aut == 1) {
			 LED5 |= t_display[18];// .
		 }
		 if (disp_cln_on==0){
			 if (disp_cln_ind==0){
				 LED0 = t_display[16];
			 } else if (disp_cln_ind==1){
				 LED1 = t_display[16];
			 } else if (disp_cln_ind==2){
				 LED2 = t_display[16];
			 } else if (disp_cln_ind==3){
				 LED3 = t_display[16];
			 } else if (disp_cln_ind==4){
				 LED4 = t_display[16];
			 }
		 } 
  } else if(disp_mod == 2) {	
//black  -    .			H    J    K    L    N    o    P    U     t    G    q    r   M    y
		if (cnt_dir_aut == 1) {
			if (disp_cln_on==0){
				LED0 = t_display[16];
				LED1 = t_display[16];
				LED2 = t_display[16];
				LED3 = t_display[16];
			} else {
				LED0 = t_display[24];//o
				LED1 = t_display[27];//t
				LED2 = t_display[26];//U
				LED3 = t_display[10];//A
			}
			LED4 = t_display[16];
			LED5 = t_display[13];// d 
			LED5 |= t_display[18];// .
		} else {
			if (disp_cln_on==0){
				LED0 = t_display[16];
				LED1 = t_display[16];
				LED2 = t_display[16];
				LED3 = t_display[16];
			} else {
				LED0 = t_display[26];//U
				LED1 = t_display[23];//n
				LED2 = t_display[10];//A
				LED3 = t_display[31];//M			
			}
			LED4 = t_display[16];
			LED5 = t_display[13];// d 
		}
  } else {	//if(dis_mod == 0) 
		LED0 = T0_cnt % 10;
		LED0 = t_display[LED0];
		LED1 = (T0_cnt % 100)/10;
		LED1 = t_display[LED1];
		LED2 = (T0_cnt % 1000)/100;
		LED2 = t_display[LED2];
		LED3 = (T0_cnt % 10000) / 1000;
		LED3 = t_display[LED3];
		LED4 = (T0_cnt % 100000) / 10000;
		LED4 = t_display[LED4];
		if (disp_cln_on==0){
			LED5 = t_display[16];
		} else if (cnt_dir_sel == 0) { //
			LED5 = t_display[25];// P 		
		} else {
			//LED5 = t_display[17];// -
			LED5 = t_display[23];// n
		} 
		if (cnt_dir_aut == 1) {
			LED5 |= t_display[18];// .
		}
		 
  }
}