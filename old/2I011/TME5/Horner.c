#include <stdlib.h>
#include <stdio.h>
//#define F(X) (0) ;
double evaluatePolynomial (double *c, double x, unsigned int n){
	unsigned int i;
	double res=0;
	for (i=0;i<=n;i++){
		res=res*x+c[i];
	}
	return res;
}
	
void printPolynomialApproxError(FILE *fd, double *c, unsigned int n, double (*f) (double), double a, double b, unsigned int k){
	//fopen(fd,'w');
	double x;
	unsigned int i;
	for (i=0;i<k;i++){
		x=a+i*(b-a)/(k-1);
		fprintf(fd,"%+1.18e\t%+1.18e\n",x,evaluatePolynomial(c,x,n)-f(x));
	}	
	//printf("%d",n);
	//fclose(fd);
}

//fonction à approcher
double fn (double a) {
	return 0;//3*a;
}


int main(){
	unsigned int n, k;
	printf("n k a b c[i]\n");
	scanf(" %d",&n);
	scanf(" %d",&k);
	double c[n],a,b;
	scanf(" %lf",&a);
	scanf(" %lf",&b);
	unsigned int i;
	for (i=0;i<=n;i++){
		scanf(" %lf",c+i);
	}
	FILE *fd = fopen("poly.dat","w");
	double (*f) (double);
	f=fn;
	printPolynomialApproxError(fd,c,n,f,a,b,k);
	fclose(fd);
	return 0;
}
