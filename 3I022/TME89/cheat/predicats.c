#include "splitmerge.h"

/* tme 8 */
int predsplit( region *r, float threshold) {

  /* à compléter pour répondre à la question 1.1 */
  return r->var > threshold;
} 

/* tme 9 */
int predmerge( region *a, region *b, float thresh) {

  /* à compléter pour répondre à la question 2.1  */
  	float mu, var;
  	int n, na, nb;
  	na=a->x*a->y;
  	nb=b->x*b->y;
  	n=na+nb;
  	mu=(na*a->mu+nb*b->mu)/n;
  	var=(na*a->var+nb*b->var+na*a->mu*a->mu+nb*b->mu*b->mu)/n-mu*mu;
  	
  	if(var<thresh){
  		a->n=n;
  		a->mu=mu;
  		a->var=var;
  		return 1;
  	}
  	return 0;
}
