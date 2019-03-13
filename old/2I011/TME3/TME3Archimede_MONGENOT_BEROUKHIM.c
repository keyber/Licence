#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

//TME ex2
float sumJFloatDec(unsigned int n){
	unsigned int i;
	float s=0;
	for(i=1;i<=n;i++)
		s=s+(float)1/i;
	return s;
}

float sumJFloatInc(unsigned int n){
	float s=0;
	while(n>0){
		s=s+(float)1/n;
		n--;
	}
	return s;
}
double sumJDoubleDec(unsigned int n){
	unsigned int i;
	double s=0;
	for(i=1;i<=n;i++)
		s=s+(double)1/i;
	return s;
}

double sumJDoubleInc(unsigned int n){
	double s=0;
	while(n>0){
		s=s+(double)1/n;
		n--;
	}
	return s;
}
//TME Ex3
double integralDirect(unsigned int n){//entre 0 et 1 (devient négatif car propagation erreur en n!) 
	double e = -exp((double)(-1));
	double Ii=1+e;
	
	unsigned int i;
	for(i=1;i<=n;i++)
		Ii=e+i*Ii;
	return Ii;
}
double integralIndirect(unsigned int n,unsigned int m,double Im){
	double e = exp((double)(-1));
	for(;m>n;m--)
		Im=(e+Im)/m;
	return Im;
}

double archimedes(unsigned int k){
	double L= .5;//variable stocke L2^icarré/4
	unsigned int i;
	for(i=2;i<k;i++)
		L=L/(2*(1+sqrt(1-L)));
	return pow(2,k)*sqrt(L);//pi=n*(Ln)/2
}
int main (){
	//unsigned int i;
	/*
	//Ex 2
	for(i=10;i<10000000;i*=10){
		printf("%f : %f\n",sumJFloatDec(i),sumJFloatInc(i));
		printf("%lf : %lf\n",sumJDoubleDec(i),sumJDoubleInc(i));
	}*/
	/*
	//Ex 3
	for(i=1;i<100;i++){
		printf("%lf\n",integralDirect(i));
	}
	printf("%lf\n",integralIndirect(10,51,1));
	*/
	printf("%lf =? %lf\n",M_PI, archimedes (100));
	return 0;
}
