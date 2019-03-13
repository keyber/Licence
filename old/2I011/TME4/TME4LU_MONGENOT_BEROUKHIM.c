#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double *allocateVector(unsigned int m){
	double* vec=calloc(m,sizeof(double));
	if(vec==NULL){
		printf("malloc\n");
		exit(1);
	}
	return vec;
}
double *allocateMatrix(unsigned int m){
	double* mat=calloc(m*m,sizeof(double));
	if(mat==NULL){
		printf("malloc\n");
		exit(1);
	}
	return mat;
}

void copyMatrix(double *B, double *A, unsigned int m){
	int i;
	for (i=0;i<m*m;i++){
		B[i]=A[i];
	}
}

void randomMatrix(double *A, unsigned int m){
	unsigned int i;
	for (i=0;i<m*m;i++)
		A[i]=(double)(rand())/RAND_MAX/2-.25;
	for(i=0;i<m;i++)
		A[i*m+i]=(double)(rand())/RAND_MAX/2+.75;
}

void printMatrix(double *v, unsigned int m){
	unsigned int i,j;
	for (i=0;i<m;i++){
		for (j=0;j<m;j++)
			printf("%lf		",v[i*m+j]);//printf("%+1.18e 	",v[i]);
		printf("\n");
	}
	printf("\n");
}


void readMatrix(double *A, unsigned int m){
	printf("rentrer matrice %u\n",m);
	unsigned int i;
	for (i=0;i<m*m;i++)
		if(!scanf("%lf",A+i))
			exit(1);
}


void matrixMatrixProduct(double *C, double *A,double *B, unsigned int m, unsigned int n, unsigned int p){
	//A m*n
	//B n*p
	unsigned int i,j,k;
	for (i=0;i<m;i++){		//m lignes de A
		for (j=0;j<p;j++){	//p colonnes de B
			C[i*p+j]=0;		//C matrice m*p
			for (k=0;k<n;k++)
				C[i*p+j]+=(A[i*n+k]*B[k*p+j]);//somme des Aik Bkj
		}
	}
}

/*
void scaleMatrix(double alpha, double *A, unsigned int m){
	unsigned int i;
	for (i=0;i<m*n;i++)
		A[i]*=alpha;
}
*/
void addMatrix(double *C, double *A, double *B, unsigned int m){
	unsigned int i;
	for (i=0;i<m*m;i++)
		C[i]=A[i]+B[i];
}
void subMatrix(double *C, double *A, double *B, unsigned int m){
	unsigned int i;
	for (i=0;i<m*m;i++)
		C[i]=A[i]-B[i];
}

/*
double maximumAbsMatrix(double *v, unsigned int m){
	double max=0;
	int i;
	for (i=0;i<m*m;i++)
		max=fmax(max,fabs(v[i]));
	return max;
}
*/
void luDecomposition(double *A, unsigned int n){
	unsigned int i,j,k;
	double q;
	for (i=0;i<n-1;i++){					//i pivots A[i*n+i] (i<n-1 rien à faire pour le dernier)
		for (j=i+1;j<n;j++){				//j colonnes sous le pivot (j>i)
			q=(A[n*j+i]/=A[i*(n+1)]);	//stocke coef sous le pivot (et dans q)
			for (k=i+1;k<n;k++){			//change les coefs de la ligne j à droite de i (k>i)
				A[j*n+k]-=q*A[i*n+k];		//Lj -= q*Li
			}
			printMatrix(A,n);
		}
	}
}

void solveTriangularLower(double *x, double *A, double * b, unsigned int n){
	unsigned int i,j;
	for (i=0;i<n;i++){	
		x[i]=b[i];
		for (j=0;j<i;j++){
			x[i]-=A[n*i+j]*x[j];
		}
	 }
}

void solveTriangularUpper(double *x, double *A, double * b, unsigned int n){
	unsigned int i,j;
	for (i=n-1; i+1>0; i--){	
		x[i]=b[i];
		for (j=i+1;j<n;j++){
			x[i]-=A[n*i+j]*x[j];
		}
		x[i]/=A[i*n+i];
	 }
}

void finalSolveSystemLU(double *x, double *A, double *b, double *scratch, unsigned int n){
	/*Ax=b
	 *<=> LUx=b
	 *<=> Ly=b (Y=Ux=scratch)
	 */
	 
	 solveTriangularLower(scratch,A,b,n);
	 solveTriangularUpper(x,A,scratch,n);
	 
 }
 
void SolveSystemLU(double *x, double *A, double *b, unsigned int n){
	 double* B =allocateMatrix(n);
	 double* scratch=allocateVector(n);
	 copyMatrix(B,A,n);
	 printMatrix(A,n);
	 printf("\n");
	 printMatrix(B,n);
	 printf("\n");
	 luDecomposition(B,n);
	 printf("\n");
	 printMatrix(B,n);
	 printf("\n");
	 finalSolveSystemLU(x,B,b,scratch,n);
	 printf("\n");
	 printMatrix(B,n);
	 printf("\n");
	 free(B);
	 free(scratch);
 }
 
 
int main(){
	srand(time(NULL));
	unsigned int n=4,i;
	//double *A=allocateMatrix(n);
	double A[]={2.0,3,1,5,6,13,5,19,2,19,10,23,4,10,11,31};
	//double *B=allocateMatrix(n);
	//readMatrix(A,n);
	luDecomposition(A,n);
	double x[4];
	double b[]={1.0,3,3,4};
	SolveSystemLU(x,A,b,n);
	for (i=0;i<n;i++){
		printf("%lf\n",x[i]);
	}
	
	//printMatrix(A,n);
	//randomMatrix(B,n);
	//free(A);
	//free(B);
	return 0;
}
