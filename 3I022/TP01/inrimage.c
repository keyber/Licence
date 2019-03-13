/*
  BEROUKHIM Keyvan 3506789
*/

#include <inrimage/image.h>
#include <stdlib.h>
#include <stdio.h>

static char version[]="1.00";
static char usage[]="[input][output][-sb seuilbas][-sh seuilhaut][-e][-h fileHisto]";
static char detail[]="etire, seuille cree histogramme (dans cet ordre)";
  
void histogramme (int his [256], unsigned char *buf, int size){
  int i;
  
  for (i = 0; i < 256; ++i) {
    his[i] = 0;;
  }
  
  for (i = 0; i < size; ++i) {
    his[buf[i]]++;
  }
}

int diff_int (int a, int b){
  return a>b?a-b:b-a;
}

int min(int a, int b){
  return a<b?a:b;
}

int max(int a, int b){
  return a>b?a:b;
}

/*
 * table indexée par ancienne couleur contient nouvelle couleur
 * calcule nouvel histogramme sans parcourir toute l'image
 */
void etire (int table[256], int his[256]){
  int imin=0;
  while (imin<256 && his[imin]==0) imin++;

  if(imin == 256){
    fprintf(stderr, "hist nul\n");
    return;
  }

  int imax=255;
  while (his[imax]==0) imax--;

  float facteur_dilatation = ((float)255) /  (imax - imin);

  int i=0;
  for (; i <= imin; ++i)
    table[i] = 0;
  for (; i < imax; ++i)
    table[i] = (int)((i-imin)*facteur_dilatation);
  for (; i < 256; ++i)
    table[i] = 255;


  int hOld[256];
  for (i = imin; i <= imax; ++i)
    hOld[i] = his[i];

  for (i = 0; i < 256; ++i)
    his[i] = 0;

  for (i = imin; i <= imax; ++i)
    his[table[i]] = hOld[i];
}

void applique (unsigned char* src, unsigned char* dst, int size, int table[256]){
  int i;
  for (i = 0; i < size; ++i) {
    dst[i]=table[src[i]];
  }
}


void seuille(unsigned char* src, unsigned char* dst, int size, unsigned char min, unsigned char max){
  int i;
  for (i = 0; i < size; ++i) {
    dst[i] = (src[i]<min)? 0 : (src[i]>max)? 255 : src[i];
  }
}

int main( int argc, char **argv) {
  char fname[256];
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  int sb = 0, sh=255, i, j;
  int boolEtire=0;
  char *fileHisto = NULL;

  /* Initialisation */
  inr_init( argc, argv, version, usage, detail);

  /* Lecture des options */
  igetopt1( "-sb", "%d", &sb);
  igetopt1( "-sh", "%d", &sh);
  boolEtire=igetopt0("-e");
  igetopt1("-h", "%s", &fileHisto);
  infileopt( fname);
  
  /* Ouverture et lecture des images */
  nf = image_(fname, "e", "", lfmt);

  /* verification du format */
  if( !(TYPE == FIXE && BSIZE==1))
    imerror( 6, "codage non conforme\n");

  /* allocation memoire adequat */
  buf = (unsigned char*)i_malloc(NDIMX * NDIMY*sizeof(unsigned char));

  /* lecture image */
  c_lect(nf, NDIMY, buf);

  /* fermeture image */
  fermnf_(&nf);

  /* Traitement */
  //etire
  if(boolEtire){
    int his [256];
    histogramme(his, buf, NDIMX*NDIMY);

    int table [256];
    etire(table, his);

    applique(buf, buf, NDIMX*NDIMY, table);
  }
  
  //seuille
  if(sb!=0 || sh!=255)
    seuille(buf,buf,NDIMX*NDIMY,sb,sh);

  //cree histogramme
  printf("%s\n", &fileHisto);
  if(fileHisto != NULL){
    int his [256];
    histogramme(his, buf, NDIMX*NDIMY);
    
    FILE *fichier = fopen(fileHisto, "w");
    if (fichier == NULL) {
      fprintf(stderr, "erreur ouverture fichier\n");
    }
    
    int i;
    for (i = 0; i < 256; ++i) {
      fprintf(fichier, "%d %d\n", i, his[i]);
    }
    
    fclose(fichier);
    
  }
  
  /* Ecriture de l'image */
  outfileopt( fname);
  nf = image_(fname, "c", "", lfmt);
  c_ecr( nf, NDIMY, buf);
  fermnf_( &nf);
  
  i_Free( (void*)&buf);
  return 0;
}
