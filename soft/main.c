/*
 * main.c
 *
 *  Created on: 09-03-2021
 *      Author: Pawel
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/alarm/HD44780.h>
#include "avr/alarm/HD44780.c"

#define LEDy (1<<PA6) //zolta dioda statusu
#define LEDr (1<<PA7) //czerwona dioda uzbrojenia

#define esc (1<<PC2) // esc
#define jeden (1<<PC3) // 1
#define dwa (1<<PC4) // 2
#define trzy (1<<PC5) // 3
#define cztery (1<<PC6) // 4
#define ok (1<<PC7) //  ok / uzbrajanie

#define relay (1<<PD0) // przekaznik

#define wej1 (1<<PD2) // wejscie Z1
#define wej2 (1<<PD3) // wejscie Z2
#define wej3 (1<<PD4) // wejscie Z3
#define wej4 (1<<PD5) // wejscie Z4
#define wej5 (1<<PD6) // wejscie Z5
#define wej6 (1<<PD7) // wejscie Z6


int main(void)
{
//wyjscia
DDRA |= LEDy;
DDRA |= LEDr;
DDRD |= relay;
//wejscia
PORTC |= esc;
PORTC |= jeden;
PORTC |= dwa;
PORTC |= trzy;
PORTC |= cztery;
PORTC |= ok;
PORTD |= wej1;
PORTD |= wej2;
PORTD |= wej3;
PORTD |= wej4;
PORTD |= wej5;
PORTD |= wej6;
//inicjalizacja LCD
_delay_ms(10);

LCD_Initalize();
LCD_Clear();
LCD_GoTo(0,0);

_delay_ms(10);
//deklaracja zmiennych
int niepoprawnehaslo=0;
int wyjsciowa=0;
int uzbrojenie=0;
int haslopoprawne=0;
int alarm=0;
int naruszenie1=0;
int naruszenie2=0;
int naruszenie3=0;
int naruszenie4=0;
int naruszenie5=0;
int naruszenie6=0;
int wlamanie=0;
int timer=0;	//100ms kazdy cykl

powitanie(); // wyswietl ekran startowy


while(1){
	if((uzbrojenie==0)&&(alarm==0)){
	ekran_start(wlamanie, timer);
	}

	if(!(PINC & ok))
	{
		//funkcje wpisania hasla

		wyjsciowa=funkcjaHasla();
		_delay_ms(250);
	}

	if(wyjsciowa>=1)
	{
	switch(wyjsciowa)
		{
	case 0:

	break;

	case 1:
		//haslo niepoprawne
		niepoprawnehaslo++;
		wysHasloNiepoprawne();
		wyjsciowa=0;
		if(niepoprawnehaslo>=3){
			alarm=1;
			niepoprawnehaslo=0;
			uzbrojenie=1;
		}
		break;

	case 2:
		//haslo poprawne

		niepoprawnehaslo=0;
		wysHasloPoprawne();
		if(uzbrojenie==0){
		wlamanie=0;
		OdliczanieDoUzbrojenia();
		uzbrojenie=1;
		haslopoprawne=0;
		}

		else if(uzbrojenie==1){
		if(PIND & relay){
			PORTD ^= relay;
		}
		uzbrojenie=0;
		alarm=0;
		naruszenie1=0;
		naruszenie2=0;
		naruszenie3=0;
		naruszenie4=0;
		naruszenie5=0;
		naruszenie6=0;
		}
		wyjsciowa=0;
		break;

	case 3:
		//cofnij dzialanie , nie rob nic
		wyjsciowa=0;
		break;



		}
	}

	if((uzbrojenie==1)&&(alarm==0))
	{
		stanUzbrojony();

	if(PIND & wej1)
	{
	naruszenie1++;
		if(naruszenie1>=15){
			wyjsciowa=funkcjaHasla();
			naruszenie1=16;
		}
	}
	else if(!(PIND & wej1)){
		if(naruszenie1>=1){
		naruszenie1--;
		}
	}


	if(PIND & wej2)
	{
	naruszenie2++;
		if(naruszenie2>=15){
			wyjsciowa=funkcjaHasla();
			naruszenie2=16;
		}
	}
	else if(!(PIND & wej2)){
		if(naruszenie2>=1){
		naruszenie2--;
		}
	}


	if(PIND & wej3)
	{
	naruszenie3++;
		if(naruszenie3>=15){
			wyjsciowa=funkcjaHasla();
			naruszenie3=16;
		}
	}
	else if(!(PIND & wej3)){
		if(naruszenie3>=1){
		naruszenie3--;
		}
	}


	if(PIND & wej4)
	{
	naruszenie4++;
		if(naruszenie4>=15){
			wyjsciowa=funkcjaHasla();
			naruszenie4=16;
		}
	}
	else if(!(PIND & wej4)){
		if(naruszenie4>=1){
		naruszenie4--;
		}
	}


	if(PIND & wej5)
	{
	naruszenie5++;
		if(naruszenie5>=15){
			wyjsciowa=funkcjaHasla();
			naruszenie5=16;
		}
	}
	else if(!(PIND & wej5)){
		if(naruszenie5>=1){
		naruszenie5--;
		}
	}

	if(PIND & wej6)
	{
	naruszenie6++;
		if(naruszenie6>=15){
			wyjsciowa=funkcjaHasla();
			naruszenie6=16;
		}
	}
	else if(!(PIND & wej6)){
		if(naruszenie6>=1){
		naruszenie6--;
		}
	}

	}


	if(alarm==1)
	{
		if(!(PIND & relay)){
			PORTD ^= relay;
		}
		if(!(PINA & LEDr)){
		PORTA ^= LEDr;
		}
		wysAlarm();
		wlamanie=1;
	}


	_delay_ms(100); //globalny timer
	timer++;
	if(timer>=100){
		timer=0;
	}
	}
}

void powitanie()
{
	PORTA ^= LEDr;
	PORTA ^= LEDy;
	LCD_Clear();
	LCD_GoTo(2,0);
	LCD_WriteText("Centrala ASS");
	LCD_GoTo(5,1);
	LCD_WriteText("v0.2");
	_delay_ms(2500);
	PORTA ^= LEDr;
	PORTA ^= LEDy;
	LCD_Clear();
	LCD_GoTo(4,0);
	LCD_WriteText("Made by");
	LCD_GoTo(2,1);
	LCD_WriteText("Pawel Zaremba");
	_delay_ms(1500);
}


void ekran_start(int wlam, int time)
{
	int t;
	int t1;
	if(PINA & LEDr){
		PORTA^= LEDr;
	}
	if(PINA & LEDy){
		PORTA^= LEDy;
	}
	if(PINA & relay){
		PORTA^= relay;
	}
	t=time%20;
	t1=time%40;
	LCD_GoTo(0,0);
	LCD_WriteText("  Centrala ASS  ");
if(wlam==0)
{
	LCD_GoTo(0,1);
	LCD_WriteText("Brak powiadomien");
	if((t==0)&&(t1!=0)){
		PORTA ^= LEDy;
	}
	if((t==0)&&(t1==0)){
		PORTA ^=LEDy;
	}
}
if(wlam==1)
{
			if((t==0)&&(t1!=0)){
				PORTA ^= LEDy;
				PORTA^= LEDr;

			}
			if((t==0)&&(t1==0)){
				PORTA ^=LEDy;
				PORTA^= LEDr;
			}
	LCD_GoTo(0,1);
	LCD_WriteText("wys. Naruszenie!");

}
}

int funkcjaHasla(){
	int wyjsciowa=0;
	int haslo[5];
	haslo[0] = 3;
	haslo[1] = 4;
	haslo[2] = 1;
	haslo[3] = 1;
	haslo[4] = 3;
	int wpisywanehaslo[5];
	wpisywanehaslo[0] = 0;
	wpisywanehaslo[1] = 0;
	wpisywanehaslo[2] = 0;
	wpisywanehaslo[3] = 0;
	wpisywanehaslo[4] = 0;
	int a=0; // wpisano liczbe
	//int wyjscie=0;
	int sprawdzanie=0;
	int time=0;
	int poprawne[5];
	poprawne[0]=0;
	poprawne[1]=0;
	poprawne[2]=0;
	poprawne[3]=0;
	poprawne[4]=0;
	if(PINA & LEDr){
		PORTA^= LEDr;
	}
	if(PINA & LEDy){
		PORTA^= LEDy;
	}
	_delay_ms(500);
		for(int i=0;i<=150;i++)
		{
		if(!(PINC & jeden))
		{

			wpisywanehaslo[a]=1;

			if(wpisywanehaslo[a]==haslo[a]){
				poprawne[a]=1;
			}
			else{
				poprawne[a]=0;
			}
			a++;
			_delay_ms(250);
		}
		else if(!(PINC & dwa))
		{

			wpisywanehaslo[a]=2;
			if(wpisywanehaslo[a]==haslo[a]){
				poprawne[a]=1;
			}
			else{
				poprawne[a]=0;
			}
			a++;
			_delay_ms(250);
		}
		else if(!(PINC & trzy))
		{

			wpisywanehaslo[a]=3;
			if(wpisywanehaslo[a]==haslo[a]){
				poprawne[a]=1;
			}
			else{
				poprawne[a]=0;
			}
			a++;
			_delay_ms(250);
		}
		else if(!(PINC & cztery))
		{

			wpisywanehaslo[a]=4;
			if(wpisywanehaslo[a]==haslo[a]){
				poprawne[a]=1;
			}
			else{
				poprawne[a]=0;
			}
			a++;
			_delay_ms(250);
		}
		if(a==0){
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText("Wpisz Haslo:");

		}
		else if(a==1){
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText("Wpisz Haslo:");
			LCD_GoTo(0,1);
			LCD_WriteText("*");
		}
		else if(a==2){
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText("Wpisz Haslo:");
			LCD_GoTo(0,1);
			LCD_WriteText("**");
		}
		else if(a==3){
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText("Wpisz Haslo:");
			LCD_GoTo(0,1);
			LCD_WriteText("***");
		}
		else if(a==4){
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText("Wpisz Haslo:");
			LCD_GoTo(0,1);
			LCD_WriteText("****");
		}
		else if(a==5){
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText("Wpisz Haslo:");
			LCD_GoTo(0,1);
			LCD_WriteText("*****");
		}
		if(!(PINC & esc))
		{

			wyjsciowa=3;
			_delay_ms(250);
			break;
		}
		if(!(PINC & ok)){
			_delay_ms(250);
			break;

		}

		_delay_ms(100);



	}
	if(wyjsciowa==3){

	}
	else{
		if((poprawne[0]==1)&&(poprawne[1]==1)&&(poprawne[2]==1)&&(poprawne[3]==1)&&(poprawne[4]==1)){
			wyjsciowa=2;
		}
		else{
			wyjsciowa=1;
		}
	}

	return wyjsciowa;
}

void wysHasloNiepoprawne(){
	LCD_Clear();
	LCD_GoTo(5,0);
	LCD_WriteText("Haslo");
	LCD_GoTo(2,1);
	LCD_WriteText("Niepoprawne!");
	_delay_ms(800);
	LCD_Clear();
	_delay_ms(600);
	LCD_GoTo(5,0);
	LCD_WriteText("Haslo");
	LCD_GoTo(2,1);
	LCD_WriteText("Niepoprawne!");
	_delay_ms(800);
	LCD_Clear();
	_delay_ms(600);
	LCD_GoTo(5,0);
	LCD_WriteText("Haslo");
	LCD_GoTo(2,1);
	LCD_WriteText("Niepoprawne!");
	_delay_ms(800);
	LCD_Clear();
}

void wysHasloPoprawne(){
	LCD_Clear();
		LCD_GoTo(5,0);
		LCD_WriteText("Haslo");
		LCD_GoTo(2,1);
		LCD_WriteText("Poprawne");
		_delay_ms(1000);
		LCD_Clear();
}

void OdliczanieDoUzbrojenia(){
	if(PINA & LEDr){
		PORTA^= LEDr;
	}
	if(PINA & LEDy){
		PORTA^= LEDy;
	}
	LCD_Clear();
	PORTA^= LEDy;
	LCD_GoTo(0,0);
	LCD_WriteText("Uzbrajanie");
	LCD_GoTo(0,1);
	LCD_WriteText("20s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("19s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("18s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("17s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("16s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("15s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("14s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("13s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("12s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("11s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("10s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteText("Uzbrajanie");
	LCD_GoTo(0,1);
	LCD_WriteText("9s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("8s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("7s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("6s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("5s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("4s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("3s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("2s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	LCD_GoTo(0,1);
	LCD_WriteText("1s");
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
	_delay_ms(200);
	PORTA^= LEDy;
if(PINA & LEDy){
	PORTA^= LEDy;
}

}

void wysAlarm(){
LCD_Clear();
LCD_GoTo(4,0);
LCD_WriteText("ALARM !");
}

void stanUzbrojony(){
	if(PINA & LEDr){
		PORTA^= LEDr;
	}
	if(PINA & LEDy){
		PORTA^= LEDy;
	}
	PORTA ^= LEDy;
	LCD_Clear();
	LCD_GoTo(4,0);
	LCD_WriteText("Centrala");
	LCD_GoTo(4,1);
	LCD_WriteText("Uzbrojona");
}
