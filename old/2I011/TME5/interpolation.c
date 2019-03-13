

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


void evaluateFonction(double* y, double (*f) (double), double* x, unsigned int n){
	unsigned int i;
	for (i=0; i<n; i++){
		y[i]=f(x[i]);
	}
}

	
void equidistantPoints(double* x, double a, double b, unsigned int n){
	unsigned int i;
	for (i=0; i<n; i++){
		x[i]=a+i*(b-a)/(n-1);	
	}
}

void interpolatePoints(double* c, double* x, double *y, unsigned int n){
	double V[n*n],xi[n];
	unsigned int i;
	for (i=0; i<n; i++){
		xi[i]=x[i];
		V[n*i]=1;
	}
	for (i=0; i<n; i++){
		xi[i]*=x[i];
		V[n*i]=xi[i];
	}
	SolveSystemLU(c,V,y,n)
}
	
