#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _ratio{
	int64_t num;
	int64_t den;
}ratio;

int64_t gcd (int64_t a, int64_t b){
  int c;
  while (a != 0) {
     c = a; a = b%a;  b = c;
  }
  return b;
}
int64_t lcm(int64_t a,int64_t b){
	return a*b/gcd(a,b);
}

ratio createRatio(int64_t a, int64_t b){
	if(b==0){
		printf("/0\n");
		exit(1);
	}
	int64_t g=gcd(a,b);
	ratio r;
	r.num = a/g;
	r.den = b/g;
	return r;
}

ratio addRatio(ratio a, ratio b){
	//écriture avec dénominateur commun
	int64_t l = lcm(a.den,b.den);
	a.num=a.num*l/a.den;
	b.num=b.num*l/b.den;
	//somme
	return createRatio(a.num+b.num,l);
}
ratio subRatio(ratio a, ratio b){
	//écriture avec dénominateur commun
	int64_t l = lcm(a.den,b.den);
	a.num=a.num*l/a.den;
	b.num=b.num*l/b.den;
	//diff
	return createRatio(a.num-b.num,l);
}

ratio mulRatio(ratio a, ratio b){
	return createRatio(a.num*b.num,a.den*b.den);
}
ratio divRatio(ratio a, ratio b){
	//inverse num et den
	return createRatio(a.num*b.den,a.den*b.num);
}
double approxRatio(ratio a){
	return (double)(a.num)/a.den;
}
void printRatio(ratio a){
	printf("%ld/%ld = %lf\n",a.num,a.den,approxRatio(a));
}

unsigned int factorielle(unsigned int n){
	unsigned int res=1;
	for (; n>0; n--) {
		res = res * n;
	}
	return res;
}

ratio computeS(unsigned int n){
	ratio res;
	res.num=0;
	res.den=1;
	unsigned int i;
	for(i=1;i<=n;i++){
		res=addRatio(res,createRatio(1,factorielle(i)));
	}
	return res;
}

ratio computeA(unsigned int n){
	ratio an;
	an.num=11;
	an.den=2;
	if(n==0)
		return an;
	ratio an1;
	an1.num=61;
	an1.den=11;
	if(n==1)
		return an1;
	ratio an2;
	unsigned int i;
	for(i=2;i<=n;i++){
		an2=subRatio(createRatio(111,1), divRatio(subRatio(createRatio(1130,1),divRatio(createRatio(3000,1),an)),an1));
		an=an1;
		an1=an2;
	}
	return an2;
}


int main (){/*
	ratio r1=createRatio(1,2);
	ratio r2=createRatio(1,2);
	printRatio(addRatio(r1,r2));
	printRatio(subRatio(r1,r2));
	printRatio(mulRatio(r1,r2));
	printRatio(divRatio(r1,r2));*/
	int i;
	for(i=0;i<=20;i++){
		printRatio(computeA(i));
	}
	return 0;
}
