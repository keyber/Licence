#include "splitmerge.h"

/* tme 8 */
int predsplit( region *r, float threshold) {
    return r->var > threshold;
} 

/* tme 9 */
int predmerge( region *a, region *b, float thresh) {
  	int na=a->x*a->y;
  	int nb=b->x*b->y;
  	int n=na+nb;
  	float mu=(na*a->mu+nb*b->mu)/n;
  	float var=( na * a->var 
  	    + nb * b->var
  	    + na * a->mu * a->mu
  	    + nb * b->mu * b->mu)
  	    /n
  	    - mu * mu;
  	
  	if(var<thresh){
  		a->n=n;
  		a->mu=mu;
  		a->var=var;
  		return 1;
  	}
  	return 0;
}
