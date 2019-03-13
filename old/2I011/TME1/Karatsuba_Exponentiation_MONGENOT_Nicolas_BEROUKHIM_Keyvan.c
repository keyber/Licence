#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

unsigned int factorielle(unsigned int n){
    int i;
    int fact=1;
    if(n==0)
        return(1);
    for(i=1; i<=n; i++)
        fact=i*fact;
    return fact;
}

void conversionVersBinaire(unsigned int r[64], uint64_t n){
    int i;
    for(i=0; i<64; i++){
        r[i]=n&1;
        n=n>>1;
    }
}

int bits1(uint64_t n){
    int i;
    int s=0;
    for(i=0; i<64; i++){
        s+=((n>>i)&1);
    }
    return s;
}

int cpt=0;
uint64_t multiplication1Bit(uint64_t a, uint64_t b){
    cpt++;
    return a&b;
}

uint64_t multiplicationNaive(uint64_t a, uint64_t b){
    int i;
    int j;
    uint64_t s=0;
    for(i=0; i<64; i++){
        for(j=0; j<64; j++){
            s+=(multiplication1Bit((a>>i)&1,(b>>j)&1))<<(i+j);
        }
    }
    return s;
}

uint64_t multiplicationKaratsuba(uint64_t x, uint64_t y,int k){
    if(x == 0 || y == 0)
        return 0;
    if(k==1)
        return multiplication1Bit(x, y);
    uint64_t a,b,c,d,D,E,T,U,V;
    int Sa=1,Sb=1;
    int t1=k/2;
    int t2=k-t1;
    a=(x<<(64-t1))>>(64-t1);	//garde les t1 chiffres à d
    b=x>>t1;	//détruit les t1 à droite donc garde t2 chiffres (déplacés à d)
    c=(y<<(64-t1))>>(64-t1);	//garde les t1 chiffres à d
    d=y>>t1;	//shift à d
    if (a>=b)
        D=a-b;
    else{
        D=b-a;
        Sa=-1;
    }
    if (c>=d){
        E=c-d;
        Sb=-1;
    }
    else
        E=d-c;
    T=multiplicationKaratsuba(b,d,t2);
    U=multiplicationKaratsuba(a,c,t1);
    V=multiplicationKaratsuba(D,E,t2);
    V=(Sa*Sb)*V+T+U;
    return(T<<k)+(V<<(k/2))+U;
}

uint64_t expGDRec(uint64_t n, unsigned int k){

    if(k==0)
        return 1;
    if (k==1)
        return n;
    if(k%2==0)
        return expGDRec(n*n,k/2);
    return n*expGDRec(n*n,k/2);
}
uint64_t expDGRec(uint64_t n, unsigned int k){
    if(k==0)
        return 1;
    if (k==1)
        return n;
    if(k%2==0){
        uint64_t a = expDGRec(n,k/2);
        return a*a;
    }
    uint64_t a = expDGRec(n,k/2);
    return n*a*a;
}

uint64_t expGDIt(uint64_t n, uint64_t k){
    int bin [64];
    conversionVersBinaire(bin,k);
    uint64_t res=1;
	k--;
    while(k+1){//s'arrête pour k=-1 (+ 2^32)
        res=res*res;
        if(bin[k])
            res=res*n;
        k--;
    }
    return res;
}

uint64_t expDGIt(uint64_t n, unsigned int k){
    uint64_t res=1;
    while(k){
        if(k%2==1)
            res=res*n;
        n=n*n;
        k=k/2;
    }
    return res;
}


int main(){
    int i;
	//PREMIERES FONCTIONS
    /*
	printf("%d\n",factorielle(10));
	unsigned int tab[64];
	conversionVersBinaire(tab,1111);
	for(i=0;i<64;i++)
		printf("%d",tab[63-i]);
	printf("\n");
	printf("%d\n", bits1(1111));
	printf("%d\n", multiplicationNaive(2,3));*/

    //KARATSUBA

	srand48(time(NULL));
	uint64_t a;
	uint64_t b;
	for(i=0;i<100;i++){
		a =lrand48();
		b =lrand48();
		if(a*b!=multiplicationKaratsuba(a,b,64)){
			printf("%lu	%lu	%lu	%lu\n",a,b,a*b,multiplicationKaratsuba(a,b,64));
			return 1;
		}
	}
	printf("%d appels a multiplication1bit\n",cpt);

    //EXPONENTIATION
    for(a=0; a<100; a++)
        for(b=0; b<10; b++){
			uint64_t pow=expGDRec(a,b);
			if(expGDIt(a,b)!=pow)
				printf("%lu^%lu donne %lu\n",a,b, expGDIt(a,b));
			if(expDGIt(a,b)!=pow)
				printf("%lu^%lu donne %lu\n",a,b, expDGIt(a,b));

        }
	return 0;
}






