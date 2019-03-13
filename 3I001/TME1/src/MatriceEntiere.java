/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class MatriceEntiere {

	private final int lignes, colonnes;
	private final int[][] tab;
	public MatriceEntiere(int l, int c){
		lignes=l;
		colonnes=c;
		tab=new int[l][c];
	}
	public MatriceEntiere(File f){
		BufferedReader in = null;
		try {
			in = new BufferedReader(new FileReader(f));
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}
		Scanner s = new Scanner(in);
		
		//lit les deux première lignes
		lignes=s.nextInt();
		colonnes=s.nextInt();
		tab=new int[lignes][colonnes];
		
		//rempli ligne par ligne
		for (int i = 0; i < lignes; i++) {
			for (int j = 0; j < colonnes; j++) {
				tab[i][j]=s.nextInt();
			}
		}
		//ferme s
		s.close();

	}
	public int getElem(int i, int j){
		return tab[i][j];
	}
	public void setElem(int i, int j, int val){
		tab[i][j]=val;
	}

	@Override
	public String toString() {
		return "matrice "+lignes+", "+colonnes;
	}

	public void afficher(){
		for (int i = 0; i < lignes; i++) {
			for (int j = 0; j < colonnes; j++) {
				System.out.print(tab[i][j]+"\t");
			}
			System.out.println("");
		}
	}

	public void initZ(){
		for (int i = 0; i < lignes; i++) {
			for (int j = 0; j < colonnes; j++) {
				tab[i][j]=0;
			}
		}
	}
	public MatriceEntiere transpo(){
		MatriceEntiere t = new MatriceEntiere(colonnes, lignes);
		for (int i = 0; i < lignes; i++) {
			for (int j = 0; j < colonnes; j++) {
				t.tab[j][i]=tab[i][j];
			}
		}
		return t;
	}

	public MatriceEntiere somme(MatriceEntiere autre){
		if(lignes != autre.lignes || colonnes!=autre.colonnes)
			throw new TaillesNonConcordantesException();
		MatriceEntiere s = new MatriceEntiere(lignes, colonnes);
		for (int i = 0; i < lignes; i++) {
			for (int j = 0; j < colonnes; j++) {
				s.tab[i][j]=tab[i][j]+autre.tab[i][j];
			}
		}
		return s;
	}
	
	public MatriceEntiere produit(MatriceEntiere autre) throws TaillesNonConcordantesException{
		if(colonnes!=autre.lignes)
			throw new TaillesNonConcordantesException();
		MatriceEntiere p = new MatriceEntiere(lignes, autre.colonnes);
		for (int i = 0; i < p.lignes; i++) {
			for (int j = 0; j < p.colonnes; j++) {
				int s=0;
				for (int k = 0; k < colonnes; k++) {
					s+=tab[i][k]*autre.tab[k][j];
				}
				p.tab[i][j]=s;
			}
		}
		return p;
	}
	public static void main(String[] args) {
		File f = new File("donnees_somme1");
		MatriceEntiere m = new MatriceEntiere(f);
		f = new File("donnees_somme2");
		MatriceEntiere m2 = new MatriceEntiere(f);
		m.somme(m2).afficher();
		
		System.out.println();

		f = new File("donnees_produit1");
		m = new MatriceEntiere(f);
		f = new File("donnees_produit2");
		m2 = new MatriceEntiere(f);
		m.produit(m2).afficher();
	}

static class TaillesNonConcordantesException extends RuntimeException {

}

	
}
