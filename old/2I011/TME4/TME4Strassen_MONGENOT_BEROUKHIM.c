#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double *allocateMatrix(unsigned int m){
	double* mat=calloc(m*m,sizeof(double));
	if(mat==NULL){
		printf("malloc\n");
		exit(1);
	}
	return mat;
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
/*

void readMatrix(double *A, unsigned int m, unsigned int n){
	printf("rentrer matrice %u * %u\n",m,n);
	unsigned int i;
	for (i=0;i<m*n;i++)
		if(!scanf("%lf",A+i))
			exit(1);
}
*/

void splitMatrix(double *B, double *C, double *D, double *E, double *A, unsigned int m, unsigned int n, unsigned int p, unsigned int q){
	unsigned int i;
	for(i=0;i<p*q;i++)
		B[i]=A[i/q*n+i%q];
	for(i=0;i<p*(n-q);i++)			//comme B(en remplacant q le nb de col de B par n-q nb de C)   plus shift de q   (q colonnes)
		C[i]=A[i/(n-q)*n+i%(n-q)+q];
	for(i=0;i<(m-p)*q;i++)			//														  plus shift de p*n (p lignes)
		D[i]=A[i/q*n+i%q+p*n];
	for(i=0;i<(m-p)*(n-q);i++)		//														  plus shift de p*n (p lignes) + q
		E[i]=A[i/(n-q)*n+i%(n-q)+p*n + q];

}


void composeMatrix(double *A, double *B, double *C, double *D, double *E, unsigned int m, unsigned int n, unsigned int p, unsigned int q){
	//comme split avec les affectations inversées.
	unsigned int i;
	for(i=0;i<p*q;i++)
		A[i/q*n+i%q]=B[i];
	for(i=0;i<p*(n-q);i++)
		A[i/(n-q)*n+i%(n-q)+q]=C[i];
	for(i=0;i<(m-p)*q;i++)
		A[i/q*n+i%q+p*n]=D[i];
	for(i=0;i<(m-p)*(n-q);i++)
		A[i/(n-q)*n+i%(n-q)+p*n + q]=E[i];
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


void strassen(double *C, double *A, double *B, unsigned int k){
	if(k<3)
		return matrixMatrixProduct(C,A,B,1<<k,1<<k,1<<k);
	k--;
	unsigned int p=1<<k;
	double *a11=allocateMatrix(p);
	double *a12=allocateMatrix(p);
	double *a21=allocateMatrix(p);
	double *a22=allocateMatrix(p);
	double *b11=allocateMatrix(p);
	double *b12=allocateMatrix(p);
	double *b21=allocateMatrix(p);
	double *b22=allocateMatrix(p);

	splitMatrix(a11,a12,a21,a22,A,p*2,p*2,p,p);
	splitMatrix(b11,b12,b21,b22,B,p*2,p*2,p,p);

	double *m1=allocateMatrix(p);
	double *m2=allocateMatrix(p);
	double *m3=allocateMatrix(p);
	double *m4=allocateMatrix(p);
	double *m5=allocateMatrix(p);
	double *m6=allocateMatrix(p);
	double *m7=allocateMatrix(p);

	//on se sert de m3 et m4 comme variables temporaires

	//1
	addMatrix(m3,a11,a22,p);
	addMatrix(m4,b11,b22,p);
	strassen(m1,m3,m4,k);

	//2
	addMatrix(m3,a21,a22,p);
	strassen(m2,m3,b11,k);

	//5
	addMatrix(m3,a11,a12,p);
	strassen(m5,m3,b22,k);

	//6
	subMatrix(m3,a21,a11,p);
	addMatrix(m4,b11,b12,p);
	strassen(m6,m3,m4,k);

	//7
	subMatrix(m3,a12,a22,p);
	addMatrix(m4,b21,b22,p);
	strassen(m7,m3,m4,k);

	//3
	subMatrix(m4,b12,b22,p);
	strassen(m3,a11,m4,k);

	//4
	subMatrix(a11,b21,b11,p);//on ne se sert plus des valeurs contenues dans a11 donc on s'en sert comme variable temporaire
	strassen(m4,a22,a11,k);

	//on met les 4 blocs de AB dans aij
	addMatrix(a12,m3,m5,p);

	addMatrix(a21,m2,m4,p);

	addMatrix(a11,m1,m4,p);
	subMatrix(a11,a11,m5,p);
	addMatrix(a11,a11,m7,p);

	subMatrix(a22,m1,m2,p);
	addMatrix(a22,a22,m3,p);
	addMatrix(a22,a22,m6,p);

	composeMatrix(C,a11,a12,a21,a22,p*2,p*2,p,p);
	free(a11);
	free(a12);
	free(a21);
	free(a22);
	free(b11);
	free(b12);
	free(b21);
	free(b22);
	free(m1);
	free(m2);
	free(m3);
	free(m4);
	free(m5);
	free(m6);
	free(m7);
}

double maximumAbsMatrix(double *v, unsigned int m){
	double max=0;
	int i;
	for (i=0;i<m*m;i++)
		max=fmax(max,fabs(v[i]));
	return max;
}

int main(){
	/*
	k=10 : matrices 1024*1024
	11s pour Strassen compléxité 1024^2.8 ~= 10^8 (sans compter cst)
	35s pour product  compléxité 2^30     ~= 10^9 (sans compter cst)
	*/
	srand(time(NULL));
	unsigned int k=8, p=1<<k;
	double *A=allocateMatrix(p);
	double *B=allocateMatrix(p);
	double *P=allocateMatrix(p);
	double *S=allocateMatrix(p);
	randomMatrix(A,p);
	randomMatrix(B,p);
	matrixMatrixProduct(P,A,B,p,p,p);
	strassen(S,A,B,k);
	subMatrix(A,P,S,p);
	printf("max(abs(diff(Strassen,Product))) = %+1.6e",maximumAbsMatrix(A,p));
	free(A);
	free(B);
	free(P);
	free(S);
	return 0;
}
