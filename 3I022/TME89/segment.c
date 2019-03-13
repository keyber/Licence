#include "splitmerge.h"
#include <stdio.h>


typedef struct {
	unsigned char *buf;
	int dimx;
	int nb_reg;
} buf_dimx;

static gboolean remplit_bloc( GNode *noeud, gpointer gp) {
  region *r = noeud -> data;

  buf_dimx *b = (buf_dimx *)gp;

  int i, j;
  for (j = r->iy; j < r->y + r->iy ; ++j) {
	  for (i = r->ix; i < r->x + r->ix; ++i) {
		  (b->buf)[i + j * b->dimx] = r->mu;
	  }
  }
  
  b->nb_reg++;
  return 0;
}



/* TME 8 exercice 1.3 */
int split_segment( GNode *qt, unsigned char *buf, int dimx) {
	buf_dimx b = {buf,dimx, 0};
	g_node_traverse( qt, G_PRE_ORDER, G_TRAVERSE_LEAVES,
			   -1, (GNodeTraverseFunc) remplit_bloc, &b);
  return b.nb_reg;
}



/* TME 9 exercice 7 */
void merge_segment( GSList *regions, unsigned char *buf, int dimx) {
  GSList *reg;
  GSList *regnext;
  int x,y;
	for(reg= regions; reg; reg = reg->next){
		region* r = reg->data;
		
		for(regnext= r->merged; regnext; regnext = regnext->next){
			region *rnext = regnext->data;
			
			for(y= rnext->iy; y < rnext->iy + rnext->y; y++){
				for(x= rnext->ix; x < rnext->ix + rnext->x; x++){
					buf[x + y*dimx] = r->mu;
				}
			}
		}
	}
}

