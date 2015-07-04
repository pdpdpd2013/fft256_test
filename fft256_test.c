#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

unsigned char signal[8]={0x80,0xbc,0xd5,0xbc,0x80,0x43,0x2a,0x43};
float out_r[8];
float out_i[8];
float output_meg[8];
float output_phs[8];
#define N 8
#define PI 3.14159265

float multi_r(unsigned char n,unsigned char k)
{
	float temp;
	temp=signal[n]*sin(-2*PI/N*k*n);
	return temp;
}

float multi_i(unsigned char n,unsigned char k)
{
	float temp;
	temp=signal[n]*cos(-2*PI/N*k*n);
	return temp;
}

void X_k(unsigned char k)
{
	float temp_r=0,temp_i=0;
	int i;
	for(i=0;i<N;i++)
	{
		temp_r+=multi_r(i,k);
		temp_i+=multi_i(i,k);
	}
	out_r[k]=temp_r;
	out_i[k]=temp_i;
}

void meg_k(unsigned char k)
{
	output_meg[k]=sqrt(out_r[k]*out_r[k]+out_i[k]*out_i[k]);
}

void phs_k(unsigned char k)
{
	output_phs[k]=atan(out_i[k]/out_r[k]);
}

void main()
{
	int k;
	for(k=0;k<N;k++)
	{
		X_k(k);
		meg_k(k);
		phs_k(k);
	}
}
