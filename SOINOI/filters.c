#include <math.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209

float a[5];
float b[128];
int M;

float x[8192];
int p=0;

void reset_ab()
{
	int i;
	for(i=0;i<128;i++)
		b[i]=0;
	for(i=0;i<5;i++)
		a[i]=0;
}
void reset_x()
{
	int i=0;
	for(i=0;i<8192;i++)
		x[i]=0;
}


void IIR4th(double fs,double fc)
{
	double a1[3], a2[3], b1[3], b2[3];
	double wc, K, MM, c, d;
	int i,j;
	K=2*fs;  wc=2*PI*fc;	c=wc*wc;   d=-2.0*wc*cos(PI*5.0/8.0);
	MM=K*K+d*K+c;
	b1[0]=c/MM;	b1[1]=2*c/MM;  b1[2]=c/MM;
	a1[0]=1; a1[1]=(2*c-2*K*K)/MM; a1[2]=(K*K-d*K+c)/MM;

	d=-2.0*wc*cos(PI*7.0/8.0);
	MM=K*K+d*K+c;
	b2[0]=c/MM;	b2[1]=2*c/MM;  b2[2]=c/MM;
	a2[0]=1; a2[1]=(2*c-2*K*K)/MM; a2[2]=(K*K-d*K+c)/MM;
	reset_ab();
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			a[i+j]+=a1[i]*a2[j];
			b[i+j]+=b1[i]*b2[j];
		}
	reset_x();

}

void sincfilter(float fs, float fc, int N)
{
	int i,h;
	float f0,s;
	M=N;
	h=(N-1)>>1;
	f0=fc/fs;
	s=0;
	for(i=0;i<N;i++)
	{
		b[i]=0.42-0.5*cos(2*PI*i/(N-1))+0.08*cos(4*PI*i/(N-1));
		if(i==h)
			b[i]*=1.0;
		else
			b[i]*=sin(2.0*PI*(i-h)*f0)/2.0/PI/f0/(i-h);
		s+=b[i];
	}
	for(i=0;i<N;i++)
		b[i]/=s;
	reset_x();
}

float FIR(float xx)
{
	return xx;
}

float IIR(float xx)
{
	return xx;
}
float echo(float xx)
{
	return xx;
}

