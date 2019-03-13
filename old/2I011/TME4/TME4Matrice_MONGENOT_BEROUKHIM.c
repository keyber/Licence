#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double *allocateVector(unsigned int m){
	double* v=calloc(m,sizeof(double));
	if(v==NULL)
		exit(1);
	int i;	
	for (i=0;i<m;i++)
		v[i]=0;
	return v;
}

double *allocateMatrix(unsigned int m, unsigned int n){
	double* mat=calloc(m*n,sizeof(double));
	if(mat==NULL)
		exit(1);
	int i;	
	for (i=0;i<m*n;i++)
		mat[i]=0;
	return mat;
}

void freeVector(double *v){
	free(v);
}

void freeMatrix(double *A){
	free(A);
}

void copyVector(double *v, double *u, unsigned int m){
	int i;
	for (i=0;i<m;i++){
		v[i]=u[i];
	}
}

void copyMatrix(double *B, double *A, unsigned int m, unsigned int n){
	int i;
	for (i=0;i<m*n;i++){
		B[i]=A[i];
	}
}

void elementVector(double *v, unsigned int k, unsigned int m){
	int i;
	for (i=0;i<m;i++)
		v[i]=0;
	if (k<m)
		v[k]=1;
}
			
void identityMatrix(double *A, unsigned int m, unsigned int n){
	int i;
	for (i=0;i<m*n;i++)
		A[i]=0;
	for(i=0;i<fmin(m,n)-1;i++)
		A[i*n+i]=1;
}

double randomValue(){
	return (float)(rand())/RAND_MAX*2-1;
}

void randomVector(double *v, unsigned int m){
	int i;
	for (i=0;i<m;i++)
		v[i]=randomValue();
}

void randomMatrice(double *A, unsigned int m, unsigned int n){
	int i;
	for (i=0;i<m*n;i++)
		A[i]=(float)(rand())/RAND_MAX/2-.25;
	for(i=0;i<fmin(m,n)-1;i++)
		A[i*n+i]=(float)(rand())/RAND_MAX/2+.75;
}

void readVector(double *v, unsigned int m){
	int i;
	for (i=0;i<m;i++)
		if(!scanf("%lf",v+i))
			exit(1);
}

void readMatrix(double *A, unsigned int m, unsigned int n){
	int i;
	for (i=0;i<m*n;i++)
		if(!scanf("%lf",A+i))
			exit(1);
}

void printMatrix(double *v, unsigned int m, unsigned int n){
	unsigned int i,j;
	for (i=0;i<m;i++){
		for (j=0;j<n;j++)
			printf("%lf		",v[i*n+j]);//printf("%+1.18e 	",v[i]);
		printf("\n");
	}
}


void printMatrix(double *v, unsigned int m, unsigned int n){
	int i;
	for (i=0;i<n;i++){
		for (i=0;i<m;i++)
			printf("%+1.18e 	",v[i]);
		printf("\n");
	}
}

double maximumAbsVector(double *v, unsigned int m){
	double max=0;
	int i;
	for (i=0;i<m;i++)
		max=fmax(max,fabs(v[i]));
	return max;
}

double maximumAbsMatrix(double *v, unsigned int m, unsigned int n){
	double max=0;
	int i;
	for (i=0;i<n*m;i++)
		max=fmax(max,fabs(v[i]));
	return max;
}

void setMatrixColumn(double *A, double *v, unsigned int k, unsigned int m, unsigned int n){
	//vecteur taille m
	int i;
	for (i=0;i<m;i++)
		A[k+n*i]=v[i];
}

void setMatrixRow(double *A, double *v, unsigned int k, unsigned int m, unsigned int n){
	//vecteur taille n
	int i;
	for (i=0;i<n;i++)
		A[k*n+i]=v[i];
}

void scaleVector(double alpha, double *v, unsigned int n){
	int i;
	for (i=0;i<n;i++)
		v[i]*=alpha;
}

void scaleMatrix(double alpha, double *A, unsigned int m, unsigned int n){
	int i;
	for (i=0;i<m*n;i++)
		A[i]*=alpha;
}
void addVector(double *w, double *u, double *v, unsigned int m){
	int i;
	for (i=0;i<m*n;i++)
		w[i]=u[i]+v[i];
}


int main(){
	srand(time(NULL));
	return 0;
}
















