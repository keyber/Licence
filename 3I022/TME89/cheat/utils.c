#include "splitmerge.h"
#include <stdio.h>

static gboolean print_region( GNode *noeud) {
  region *r = noeud -> data;

  printf( "region (%d,%d,%d,%d) : %g %g\n",
	  r->ix, r->iy, r->x, r->y, r->mu, r->var);
  return 0;
}

/* Parcours préfixé de l'arbre 4-aire et
 * impression, pour chaque noeud visité, des
 * coordonnées et statistiques de la région.
 */

void split_print_regions( GNode *quadtree) {
  g_node_traverse( quadtree, G_PRE_ORDER, G_TRAVERSE_LEAVES,
		   -1, (GNodeTraverseFunc) print_region, NULL);
}


static  
gboolean process( GNode *node, void *data) {
  * (GSList **) data = g_slist_prepend( * (GSList **) data, node->data);
  ((region*) node->data)->merged = NULL;
  return 0;
}


/* Parcours préfixé de l'arbre 4-aire et construction 
 * d'une liste chaînée des noeuds. */

GSList *merge_list_regions( GNode *qt) {
  GSList *regions = NULL;
  g_node_traverse( qt, G_PRE_ORDER, G_TRAVERSE_LEAVES, -1,
		   (GNodeTraverseFunc) process, &regions);
  return regions;
}

