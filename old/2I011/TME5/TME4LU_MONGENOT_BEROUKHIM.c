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
    if(mat==NULL)
    {
        printf("malloc\n");
        exit(1);
    }
    return mat;
}

void copyMatrix(double *B,const double *A, unsigned int m){
    unsigned int i;
    for (i=0; i<m*m; i++){
        B[i]=A[i];
    }
}

void randomMatrix(double *A, unsigned int m){
    unsigned int i;
    for (i=0; i<m*m; i++)
        A[i]=(double)(rand())/RAND_MAX/2-.25;
    for(i=0; i<m; i++)
        A[i*m+i]=(double)(rand())/RAND_MAX/2+.75;
}

void printMatrix(const double *v, unsigned int m){
    unsigned int i,j;
    for (i=0; i<m; i++){
        for (j=0; j<m; j++)
            printf("%lf		",v[i*m+j]);//printf("%+1.18e 	",v[i]);
        printf("\n");
    }
    printf("\n");
}


void readMatrix(double *A, unsigned int m){
    printf("rentrer matrice %u\n",m);
    unsigned int i;
    for (i=0; i<m*m; i++)
        if(!scanf("%lf",A+i))
            exit(1);
}


void identityMatrix(double *A, unsigned int n){
	unsigned int i;
	for (i=0;i<n*n;i++)
		A[i]=0;
	for(i=0;i<n;i++)
		A[i*n+i]=1;
}



void matrixMatrixProduct(double *C,const double *A,const double *B, unsigned int m, unsigned int n, unsigned int p){
    //A m*n
    //B n*p
    unsigned int i,j,k;
    for (i=0; i<m; i++){ 		//m lignes de A
        for (j=0; j<p; j++){ 	//p colonnes de B
            C[i*p+j]=0;		//C matrice m*p
            for (k=0; k<n; k++)
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
void addMatrix(double *C,double *A,double *B, unsigned int m){
    unsigned int i;
    for (i=0; i<m*m; i++)
        C[i]=A[i]+B[i];
}
void subMatrix(double *C,double *A,double *B, unsigned int m){
    unsigned int i;
    for (i=0; i<m*m; i++)
        C[i]=A[i]-B[i];
}


double maximumAbsMatrix(double *v, unsigned int m){
	double max=0;
	unsigned int i;
	for (i=0;i<m*m;i++)
		max=fmax(max,fabs(v[i]));
	return max;
}

void luDecomposition(double *A, unsigned int n){
    unsigned int i,j,k;
    double q;
    for (i=0; i<n-1; i++){					//i pivots A[i*n+i] (i<n-1 rien à faire pour le dernier)
        for (j=i+1; j<n; j++){				//j colonnes sous le pivot (j>i)
            q=(A[n*j+i]/=A[i*(n+1)]);	//stocke coef sous le pivot (et dans q)
            for (k=i+1; k<n; k++)			//change les coefs de la ligne j à droite de i (k>i)
                A[j*n+k]-=q*A[i*n+k];		//Lj -= q*Li
        }
    }
}

void solveTriangularLower(double *x,const double *A,const double * b, unsigned int n){
    unsigned int i,j;
    for (i=0; i<n; i++){
        x[i]=b[i];
        for (j=0; j<i; j++)
            x[i]-=A[n*i+j]*x[j];
    }
}

void solveTriangularUpper(double *x,const double *A,const double * b, unsigned int n){
    unsigned int i,j;
    for (i=n-1; i+1>0; i--){
        x[i]=b[i];
        for (j=i+1; j<n; j++)
            x[i]-=A[n*i+j]*x[j];
        x[i]/=A[i*n+i];
    }
}

void finalSolveSystemLU(double *x,const double *A,const double *b, double *scratch, unsigned int n){
    /*Ax=b
     *<=> LUx=b
     *<=> Ly=b (Y=Ux=scratch)
     */
    solveTriangularLower(scratch,A,b,n);//y tq Ly=b
    solveTriangularUpper(x,A,scratch,n);//x tq Ux=y
}

void SolveSystemLU(double *x,const double *A,const double *b, unsigned int n){
    double* B =allocateMatrix(n);
    double* scratch=allocateVector(n);
    copyMatrix(B,A,n);
    luDecomposition(B,n);
    finalSolveSystemLU(x,B,b,scratch,n);
    free(B);
    free(scratch);
}


void elementVector(double *v, unsigned int k, unsigned int n){
	unsigned int i;
	for (i=0;i<n;i++)
		v[i]=0;
	if (k<n)
		v[k]=1;
}

void setMatrixColumn(double *A, double *v, unsigned int k, unsigned int n){
	unsigned int i;
	for(i=0;i<n;i++)
		A[n*i+k]=v[i];
}

void invertMatrix(double *B,const double *A, unsigned int n){
    double* C = allocateMatrix(n);
    double* x = allocateVector(n);
    double* b = allocateVector(n);
    copyMatrix(C,A,n);
    luDecomposition(C,n);
    unsigned int i;
    for(i=0; i<n; i++){
		elementVector(b,i,n);
		SolveSystemLU(x,A,b,n);
		setMatrixColumn(B,x,i,n);
    }
    free(x);
    free(b);
    free(C);
}

double matrixDeterminantLU(const double *A,unsigned int n){
    double det = 1;
    unsigned int i;
    for(i=0; i<n; i++)
        det*=A[i*n+i];
    return det;
}

double matrixDeterminant(const double *A,unsigned int n){
    double* B =allocateMatrix(n);
    double* scratch=allocateVector(n);
    copyMatrix(B,A,n);
    luDecomposition(B,n);
    double det=matrixDeterminantLU(B,n);
    free(B);
    free(scratch);
    return det;
}

int main(){
    srand(time(NULL));
    unsigned int n=4;
    double *A=allocateMatrix(n);
    double *B=allocateMatrix(n);
    double *C=allocateMatrix(n);
    //pour A random
    randomMatrix(A,n);
    //calcul son inverse B (test décomposition LU par la même occasion)
	invertMatrix(B,A,n);
	//det(A) * det(A^-1) = 1 donc la différence doit être nulle
	printf("l'erreur sur le det de matrices inverse est de %1.3e\n",fabs(matrixDeterminant(A,n)*matrixDeterminant(B,n)-1));
	//C = A*B = Id
	matrixMatrixProduct(C,A,B,n,n,n);
	//Donc C-Id doit être la matrice nulle
	identityMatrix(A,n);
	subMatrix(C,C,A,n);
	printf("l'erreur sur le produit de deux matrices inverses est de %1.3e\n",maximumAbsMatrix(C,n));

    free(A);
    free(B);
    free(C);
	/*
	double A[]= {2.0,3,1,5,6,13,5,19,2,19,10,23,4,10,11,31};
	double *B=allocateMatrix(n);
	double x[4];
    double b[]= {1.0,3,3,4};
    SolveSystemLU(x,A,b,n);
    unsigned int i;
    for (i=0; i<n; i++)
        printf("%lf\n",x[i]);
	printf("det : %lf\n",matrixDeterminant(A,n));
	*/

    return 0;
}
