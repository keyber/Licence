#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int findZeroBisection(double *z, double (*f)(double), double a, double b, double eps){
	if((f(a)>=0) == (f(b)>=0)){ //<=> f(a) et f(b) de même signe
		printf("meme signe\n");
		return 0;
	}
	double fz=1000000;
	while (fabs(fz)>eps){
		*z=(a+b)/2;
		fz=f(*z);
		if((f(a)>=0) == (fz>=0))
			a=*z;
		else
			b=*z;
	}
	return 1;
}

int findZeroNewton(double *z, double (*f)(double), double (*fprime)(double), double a, double b, double eps){
	*z = (a+b)/2;
	double fz=1000000;
	while (fabs(fz)>eps){
		if(fprime(*z)==0)
			return 0;
		*z = *z-f(*z)/fprime(*z);
		if(*z<a || *z>b)
			return 0;
		fz=f(*z);
	}
	return 1;
}

int iterationBissection(double *z, double (*f)(double), double *a, double *b){
	if((f(*a)>=0) == (f(*b)>=0)){ //<=> f(a) et f(b) de même signe
		printf("meme signe\n");
		return 0;
	}
	if((f(*a)>=0) == (f(*z)>=0))
		*a=*z;
	else
		*b=*z;
	return 1;
}

int findZero(double *z, double (*f)(double), double (*fprime)(double), double a, double b, double eps){
	*z = (a+b)/2;
	double fz=1000000;
	while (fabs(fz)>eps){
		printf("%lf\n",z);
		if(fprime(*z)==0){
			if(iterationBissection(z,f,&a,&b)==0)
				return 0;
		}
		else{
			*z = *z-f(*z)/fprime(*z);

			if(*z<a || *z>b){
				if(iterationBissection(z,f,&a,&b)==0)
					return 0;
			}
		}
		fz=f(*z);
	}
	return 1;
}
double f(double x){
	return exp(x)-4;
}
double fp(double x){
	return exp(x);
}
double g(double x){
	return sin(x-3);
}
double gp(double x){
	return cos(x-3);
}
double h(double x){
	return (162*x*x-18)*x-3;
}
double hp(double x){
	return 486*x*x-18;
}
double p(double x){
	return (((x-2)*x-1)*x+2)*x*x;
}
double pp(double x){
	return (((5*x-8)*x-3)*x+4)*x;
}
double q(double x){
	return atan(x+1);
}
double qp(double x){
	return 1/(1+(1+x)*(1+x));
}

int main(){
	double x;/*
	printf("%d\n",findZeroBisection(&x,cos,-1.,2.,.0001));
	printf("%lf\n",2*x);
	printf("%d\n",findZeroNewton(&x,sin,cos,-1.,2.,.0001));
	printf("%lf\n",x);
	printf("%d\n",findZero(&x,sin,cos,-1.,2.,.0001));
	printf("%lf\n",x);*/

	double (*(tab []))(double)={f,g,h,p,q};
	double (*(tabP[]))(double)={fp,gp,hp,pp,qp};
	double borneInf[]={1., -0.5, -1./3, -1.5, -2.};
	double borneSup[]={1.5, 0.5, 1., 0.5, 20.};
	double e=0.000030517578125;
	int i;
	double z;
	for(i=0;i<5;i++){
		printf("i=%d\n",i);

		printf("findZeroBisection trouve : %d    ",findZeroBisection(&z,tab[i],borneInf[i],borneSup[i],e));
		printf("x=%lf\n",z);

		printf("findZeroNewton trouve : %d    ",findZeroNewton(&z,tab[i],tabP[i],borneInf[i],borneSup[i],e));
		printf("x=%lf\n",z);

		printf("findZero trouve : %d    ",findZero(&z,tab[i],tabP[i],borneInf[i],borneSup[i],e));
		printf("x=%lf\n",z);
	}

	return 1;

}