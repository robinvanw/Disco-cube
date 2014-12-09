#include <avr/io.h>

#define r0	0
#define r1	1
#define r2	3
#define r3	2
#define g0	4
#define g1	5
#define g2	7
#define g3	6
#define b0	0
#define b1	1
#define b2	3
#define b3	2
#define in1	4
#define in2	5

int ledr[4],ledg[4],ledb[4];

int main(void)
{
	DDRD = 255;
	DDRB  |=  (1<<0);	DDRB  |=  (1<<1);	DDRB  |=  (1<<2);	DDRB  |=  (1<<3);	DDRB  &= ~(1<<4);	DDRB  &= ~(1<<5);

	PORTD = 0;
	PORTB &= ~(1<<0);	PORTB &= ~(1<<1);	PORTB &= ~(1<<2);	PORTB &= ~(1<<3);	PORTB &= ~(1<<4);	PORTB &= ~(1<<5);
	
	int knop1,knop2,select=0,kleur=0,tijd=400,a,b,rgb[3]={1,2,4},c;
	
	while(1)
	{
		knop1 = PINB&(1<<in1);	//==16 is hoog
		knop2 = PINB&(1<<in2);	//==32 is hoog
		
		if      ((knop1==16)&&(knop2==32))
		{
			for (a=0;a<3;a+=1)
			{
				for (b=0;b<10;b+=1)
				{
					ledon (7,rgb[a]);	waitms (50);	dark();		waitms (50);
				}
			}
			
			for (b=0;b<10;b+=1)
			{
				for (a=0;a<3;a+=1)
				{
					ledon (7,rgb[a]);	waitms (50);	dark();		waitms (50);
				}
			}
			
			for (c=120;c>=0;c-=20)
			{
				ledon (1,1);	waitms (c);		dark();
				ledon (2,2);	waitms (c);		dark();
				ledon (3,4);	waitms (c);		dark();
				ledon (4,1);	waitms (c);		dark();
				ledon (1,2);	waitms (c);		dark();
				ledon (2,4);	waitms (c);		dark();
				ledon (3,1);	waitms (c);		dark();
				ledon (4,2);	waitms (c);		dark();
				ledon (1,4);	waitms (c);		dark();
				ledon (2,1);	waitms (c);		dark();
				ledon (3,2);	waitms (c);		dark();
				ledon (4,4);	waitms (c);		dark();
			}
			
			for (c=0;c<=120;c+=20)
			{
				ledon (1,1);	waitms (c);		dark();
				ledon (2,2);	waitms (c);		dark();
				ledon (3,4);	waitms (c);		dark();
				ledon (4,1);	waitms (c);		dark();
				ledon (1,2);	waitms (c);		dark();
				ledon (2,4);	waitms (c);		dark();
				ledon (3,1);	waitms (c);		dark();
				ledon (4,2);	waitms (c);		dark();
				ledon (1,4);	waitms (c);		dark();
				ledon (2,1);	waitms (c);		dark();
				ledon (3,2);	waitms (c);		dark();
				ledon (4,4);	waitms (c);		dark();
			}
			
			fadein (7,7,500);
			fadeout(7,7,500);
			
			dark();
		}
		
		else if ((knop1==16)&&(knop2!=32))
		{
			ledon (5,1);	ledon (6,2);	waitms (tijd);	dark();
			ledon (5,2);	ledon (6,4);	waitms (tijd);	dark();
			ledon (5,4);	ledon (6,1);	waitms (tijd);	dark();
			ledon (5,1);	ledon (6,2);	waitms (tijd);	dark();
			ledon (5,2);	ledon (6,4);	waitms (tijd);	dark();
			ledon (5,4);	ledon (6,1);	waitms (tijd);	dark();
			dark();
		}
		
		else if ((knop1!=16)&&(knop2==32))
		{
			for (kleur=1;kleur<8;kleur+=1)
			{
				fadein (7,kleur,700);
				fadeout(7,kleur,700);
				waitms(600);
			}
			dark();
		}
		
		else
		{
			fadein (7,1,700);
			fadeout(7,1,700);
			waitms (600);
			dark();
		}
	}
}

void waitms(unsigned u)
{
	int j;
	while(u--)
	{
		j=245;
		while(j--);
	}
}

void dark(void)
{	
	PORTD = 0;	PORTB &= ~(1<<0);	PORTB &= ~(1<<1);	PORTB &= ~(1<<2);	PORTB &= ~(1<<3);
}

void selectie(int select)	//Select : 1=1,2=2,3=3,4=4,5=1&3,6=2&4,7=alle
{
	switch (select)
	{
		case 1 : ledr[0]=r0;	ledg[0]=g0;	ledb[0]=b0;	ledr[1]=r0;	ledg[1]=g0;	ledb[1]=b0;	ledr[2]=r0;	ledg[2]=g0;	ledb[2]=b0;	ledr[3]=r0;	ledg[3]=g0;	ledb[3]=b0;	break;
		case 2 : ledr[0]=r1;	ledg[0]=g1;	ledb[0]=b1;	ledr[1]=r1;	ledg[1]=g1;	ledb[1]=b1;	ledr[2]=r1;	ledg[2]=g1;	ledb[2]=b1;	ledr[3]=r1;	ledg[3]=g1;	ledb[3]=b1;	break;
		case 3 : ledr[0]=r2;	ledg[0]=g2;	ledb[0]=b2;	ledr[1]=r2;	ledg[1]=g2;	ledb[1]=b2;	ledr[2]=r2;	ledg[2]=g2;	ledb[2]=b2;	ledr[3]=r2;	ledg[3]=g2;	ledb[3]=b2;	break;
		case 4 : ledr[0]=r3;	ledg[0]=g3;	ledb[0]=b3;	ledr[1]=r3;	ledg[1]=g3;	ledb[1]=b3;	ledr[2]=r3;	ledg[2]=g3;	ledb[2]=b3;	ledr[3]=r3;	ledg[3]=g3;	ledb[3]=b3;	break;
		case 5 : ledr[0]=r0;	ledg[0]=g0;	ledb[0]=b0;	ledr[1]=r0;	ledg[1]=g0;	ledb[1]=b0;	ledr[2]=r2;	ledg[2]=g2;	ledb[2]=b2;	ledr[3]=r2;	ledg[3]=g2;	ledb[3]=b2;	break;
		case 6 : ledr[0]=r1;	ledg[0]=g1;	ledb[0]=b1;	ledr[1]=r1;	ledg[1]=g1;	ledb[1]=b1;	ledr[2]=r3;	ledg[2]=g3;	ledb[2]=b3;	ledr[3]=r3;	ledg[3]=g3;	ledb[3]=b3;	break;
		case 7 : ledr[0]=r0;	ledg[0]=g0;	ledb[0]=b0;	ledr[1]=r1;	ledg[1]=g1;	ledb[1]=b1;	ledr[2]=r2;	ledg[2]=g2;	ledb[2]=b2;	ledr[3]=r3;	ledg[3]=g3;	ledb[3]=b3;	break;
		default: return; 																																			break;
	}
}

void ledon (int select,int kleur)	//Select : 1=1,2=2,3=3,4=4,5=1&3,6=2&4,7=alle	Kleur : 1=blauw,2=groen,3=cyaan,4=rood,5=paars,6=geel,7=wit
{
	selectie (select);
	
	switch (kleur)
	{
		case 1 :	PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	break;
		case 2 :	PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);	break;
		case 3 :	PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);
					PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	break;
		case 4 :	PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);	break;
		case 5 :	PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);
					PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	break;
		case 6 :	PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);
					PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);	break;
		case 7 :	PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);
					PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);
					PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	break;
		default:	return; 																						break;
	}	
}

void ledoff(int select,int kleur)	//Select : 1=1,2=2,3=3,4=4,5=1&3,6=2&4,7=alle	Kleur : 1=blauw,2=groen,3=cyaan,4=rood,5=paars,6=geel,7=wit
{
	selectie (select);
	
	switch (kleur)
	{
		case 1 :	PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	break;
		case 2 :	PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);	break;
		case 3 :	PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);
					PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	break;
		case 4 :	PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);	break;
		case 5 :	PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);
					PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	break;
		case 6 :	PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);
					PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);	break;
		case 7 :	PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);
					PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);
					PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	break;
		default:	return; 																						break;
	}			
}

void fadein (int select,int kleur,int tijd)	//Select : 1=1,2=2,3=3,4=4,5=1&3,6=2&4,7=alle	Kleur : 1=blauw,2=groen,3=cyaan,4=rood,5=paars,6=geel,7=wit
{
	int wait=0,count=0,puls=0;
	
	selectie (select);
	
	switch (kleur)
	{
		case 1 :	{for (wait=tijd;wait>=0;wait-=1)	{	PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	for (count=wait;count>=0;)	{count=count-1;}
															PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	for (count=puls;count>=0;)	{count=count-1;}	puls=puls+1;}}	break;
		case 2 :	{for (wait=tijd;wait>=0;wait-=1)	{	PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);	for (count=wait;count>=0;)	{count=count-1;}
															PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);	for (count=puls;count>=0;)	{count=count-1;}	puls=puls+1;}}	break;
		case 3 :	{for (wait=tijd;wait>=0;wait-=1)	{	PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);
															PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	for (count=wait;count>=0;)	{count=count-1;}	
															PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);
															PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	for (count=puls;count>=0;)	{count=count-1;}	puls=puls+1;}}	break;
		case 4 :	{for (wait=tijd;wait>=0;wait-=1)	{	PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);	for (count=wait;count>=0;)	{count=count-1;}	
															PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);	for (count=puls;count>=0;)	{count=count-1;}	puls=puls+1;}}	break;
		case 5 :	{for (wait=tijd;wait>=0;wait-=1)	{	PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);
															PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	for (count=wait;count>=0;)	{count=count-1;}	
															PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);
															PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	for (count=puls;count>=0;)	{count=count-1;}	puls=puls+1;}}	break;
		case 6 :	{for (wait=tijd;wait>=0;wait-=1)	{	PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);
															PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);	for (count=wait;count>=0;)	{count=count-1;}	
															PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);
															PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);	for (count=puls;count>=0;)	{count=count-1;}	puls=puls+1;}}	break;
		case 7 :	{for (wait=tijd;wait>=0;wait-=1)	{	PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);
															PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);
															PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	for (count=wait;count>=0;)	{count=count-1;}	
															PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);
															PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);
															PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	for (count=puls;count>=0;)	{count=count-1;}	puls=puls+1;}}	break;
		default:	return; 																																																break;
	}
}

void fadeout(int select,int kleur,int tijd)	//Select : 1=1,2=2,3=3,4=4,5=1&3,6=2&4,7=alle	Kleur : 1=blauw,2=groen,3=cyaan,4=rood,5=paars,6=geel,7=wit
{
	int wait=0,count=tijd,puls=tijd;
	
	selectie (select);	
	
	switch (kleur)
	{
		case 1 :	{for (wait=0;wait<=tijd;wait+=1)	{	PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	for (count=puls;count>=0;)	{count=count-1;}
															PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	for (count=wait;count>=0;)	{count=count-1;}	puls=puls-1;}}	break;
		case 2 :	{for (wait=0;wait<=tijd;wait+=1)	{	PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);	for (count=puls;count>=0;)	{count=count-1;}
															PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);	for (count=wait;count>=0;)	{count=count-1;}	puls=puls-1;}}	break;
		case 3 :	{for (wait=0;wait<=tijd;wait+=1)	{	PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);
															PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	for (count=puls;count>=0;)	{count=count-1;}
															PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);
															PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	for (count=wait;count>=0;)	{count=count-1;}	puls=puls-1;}}	break;
		case 4 :	{for (wait=0;wait<=tijd;wait+=1)	{	PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);	for (count=puls;count>=0;)	{count=count-1;}
															PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);	for (count=wait;count>=0;)	{count=count-1;}	puls=puls-1;}}	break;
		case 5 :	{for (wait=0;wait<=tijd;wait+=1)	{	PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);
															PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	for (count=puls;count>=0;)	{count=count-1;}
															PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);
															PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	for (count=wait;count>=0;)	{count=count-1;}	puls=puls-1;}}	break;
		case 6 :	{for (wait=0;wait<=tijd;wait+=1)	{	PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);
															PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);	for (count=puls;count>=0;)	{count=count-1;}
															PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);
															PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);	for (count=wait;count>=0;)	{count=count-1;}	puls=puls-1;}}	break;
		case 7 :	{for (wait=0;wait<=tijd;wait+=1)	{	PORTD |=  (1<<ledr[0]);	PORTD |=  (1<<ledr[1]);	PORTD |=  (1<<ledr[2]);	PORTD |=  (1<<ledr[3]);
															PORTD |=  (1<<ledg[0]);	PORTD |=  (1<<ledg[1]);	PORTD |=  (1<<ledg[2]);	PORTD |=  (1<<ledg[3]);
															PORTB |=  (1<<ledb[0]);	PORTB |=  (1<<ledb[1]);	PORTB |=  (1<<ledb[2]);	PORTB |=  (1<<ledb[3]);	for (count=puls;count>=0;)	{count=count-1;}
															PORTD &= ~(1<<ledr[0]);	PORTD &= ~(1<<ledr[1]);	PORTD &= ~(1<<ledr[2]);	PORTD &= ~(1<<ledr[3]);
															PORTD &= ~(1<<ledg[0]);	PORTD &= ~(1<<ledg[1]);	PORTD &= ~(1<<ledg[2]);	PORTD &= ~(1<<ledg[3]);
															PORTB &= ~(1<<ledb[0]);	PORTB &= ~(1<<ledb[1]);	PORTB &= ~(1<<ledb[2]);	PORTB &= ~(1<<ledb[3]);	for (count=wait;count>=0;)	{count=count-1;}	puls=puls-1;}}	break;
		default:	return; 																																																break;
	}
}

void rider (int select,int kleur,int tijd)	//Select : 1=aan-links,2=uit-links,3=aan-rechts,4=uit-rechts,5=loop-links,6=loop-rechts,7=rider-links,8=rider-rechts	Kleur : 1=blauw,2=groen,3=cyaan,4=rood,5=paars,6=geel,7=wit
{
	switch (select)
	{
		case 1 :	ledon (1,kleur);	waitms(tijd);	ledon (2,kleur);	waitms(tijd);	ledon (3,kleur);	waitms(tijd);	ledon (4,kleur);	waitms(tijd);	break;
		case 2 :	ledoff(1,kleur);	waitms(tijd);	ledoff(2,kleur);	waitms(tijd);	ledoff(3,kleur);	waitms(tijd);	ledoff(4,kleur);	waitms(tijd);	break;
		case 3 :	ledon (4,kleur);	waitms(tijd);	ledon (3,kleur);	waitms(tijd);	ledon (2,kleur);	waitms(tijd);	ledon (1,kleur);	waitms(tijd);	break;
		case 4 :	ledoff(4,kleur);	waitms(tijd);	ledoff(3,kleur);	waitms(tijd);	ledoff(2,kleur);	waitms(tijd);	ledoff(1,kleur);	waitms(tijd);	break;
		
		case 5 :	ledon (1,kleur);	waitms(tijd);	ledoff(1,kleur);	ledon (2,kleur);	waitms(tijd);	ledoff(2,kleur);
					ledon (3,kleur);	waitms(tijd);	ledoff(3,kleur);	ledon (4,kleur);	waitms(tijd);	ledoff(4,kleur);									break;
					
		case 6 :	ledon (4,kleur);	waitms(tijd);	ledoff(4,kleur);	ledon (3,kleur);	waitms(tijd);	ledoff(3,kleur);
					ledon (2,kleur);	waitms(tijd);	ledoff(2,kleur);	ledon (1,kleur);	waitms(tijd);	ledoff(1,kleur);									break;
					
		case 7 :	ledon (1,kleur);	waitms(tijd);	ledon (2,kleur);	waitms(tijd);	ledon (3,kleur);	waitms(tijd);	ledon (4,kleur);	waitms(tijd);
					ledoff(1,kleur);	waitms(tijd);	ledoff(2,kleur);	waitms(tijd);	ledoff(3,kleur);	waitms(tijd);	ledoff(4,kleur);	waitms(tijd);	break;
					
		case 8 :	ledon (4,kleur);	waitms(tijd);	ledon (3,kleur);	waitms(tijd);	ledon (2,kleur);	waitms(tijd);	ledon (1,kleur);	waitms(tijd);
					ledoff(4,kleur);	waitms(tijd);	ledoff(3,kleur);	waitms(tijd);	ledoff(2,kleur);	waitms(tijd);	ledoff(1,kleur);	waitms(tijd);	break;
					
		default:	return; 																																		break;
	}
}

void frider (int select,int kleur,int tijd)	//Select : 1=aan-links,2=uit-links,3=aan-rechts,4=uit-rechts,5=loop-links,6=loop-rechts,7=rider-links,8=rider-rechts	Kleur : 1=blauw,2=groen,3=cyaan,4=rood,5=paars,6=geel,7=wit
{
	switch (select)
	{
		case 1 :	fadein (1,kleur,tijd);	fadein (2,kleur,tijd);	fadein (3,kleur,tijd);	fadein (4,kleur,tijd);	break;
		case 2 :	fadeout(1,kleur,tijd);	fadeout(2,kleur,tijd);	fadeout(3,kleur,tijd);	fadeout(4,kleur,tijd);	break;
		case 3 :	fadein (4,kleur,tijd);	fadein (3,kleur,tijd);	fadein (2,kleur,tijd);	fadein (1,kleur,tijd);	break;
		case 4 :	fadeout(4,kleur,tijd);	fadeout(3,kleur,tijd);	fadeout(2,kleur,tijd);	fadeout(1,kleur,tijd);	break;
		
		case 5 :	fadein (1,kleur,tijd);	fadeout(1,kleur,tijd);	fadein (2,kleur,tijd);	fadeout(2,kleur,tijd);
					fadein (3,kleur,tijd);	fadeout(3,kleur,tijd);	fadein (4,kleur,tijd);	fadeout(4,kleur,tijd);	break;
					
		case 6 :	fadein (4,kleur,tijd);	fadeout(4,kleur,tijd);	fadein (3,kleur,tijd);	fadeout(3,kleur,tijd);
					fadein (2,kleur,tijd);	fadeout(2,kleur,tijd);	fadein (1,kleur,tijd);	fadeout(1,kleur,tijd);	break;
					
		case 7 :	fadein (1,kleur,tijd);	fadein (2,kleur,tijd);	fadein (3,kleur,tijd);	fadein (4,kleur,tijd);
					fadeout(1,kleur,tijd);	fadeout(2,kleur,tijd);	fadeout(3,kleur,tijd);	fadeout(4,kleur,tijd);	break;
					
		case 8 :	fadein (4,kleur,tijd);	fadein (3,kleur,tijd);	fadein (2,kleur,tijd);	fadein (1,kleur,tijd);
					fadeout(4,kleur,tijd);	fadeout(3,kleur,tijd);	fadeout(2,kleur,tijd);	fadeout(1,kleur,tijd);	break;
					
		default:	return; 																						break;
	}
}