#include "splitmerge.h"
#include <stdio.h>

static int taille_buf;
int nb_noeud=0;


/* TME 8 exercice 1.3 */
static gboolean moy_niv_gris(GNode *noeud, unsigned char *buf){
	region *r = noeud -> data;
	nb_noeud++;
	int x,y;
	for(y=r->iy; y<r->iy+r->y; y++){
		for(x=r->ix; x<r->ix+r->x; x++){
			buf[x + y*taille_buf] = r->mu;
		}
	}
	return 0;
}

int split_segment( GNode *qt, unsigned char *buf, int dimx) {
	taille_buf=dimx;
	g_node_traverse( qt, G_PRE_ORDER, G_TRAVERSE_LEAVES,
		   -1, (GNodeTraverseFunc) moy_niv_gris, buf);
	return nb_noeud;
}



/* TME 9 exercice 7 */
void merge_segment( GSList *regions, unsigned char *buf, int dimx) {
  GSList* reg,*regnext;
  region* rnext;
  int x,y;
	for(reg=regions; reg; reg=reg->next){
		region* r=reg->data;
		
		for(regnext=r->merged; regnext; regnext=regnext->next){
			rnext=regnext->data;
			
			for(y=rnext->iy; y<rnext->iy+rnext->y; y++){
				for(x=rnext->ix; x<rnext->ix+rnext->x; x++){
					buf[x + y*dimx] = r->mu;
				}
			}
		}
	
	}
}

