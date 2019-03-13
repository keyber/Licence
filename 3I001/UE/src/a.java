import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.TreeSet;

public class a {
	static class Creneau{
		int jour, debut, fin;

		public Creneau(int jour, int debut, int fin) {
			this.jour = jour;
			this.debut = debut;
			this.fin = fin;
		}

		public static boolean gene(Creneau a, Creneau b) {
			if(a.jour != b.jour)
				return false;
			if(a.debut>=b.fin || a.fin<=b.debut)
				return false;
			return true;
		}
		
		@Override
		public String toString() {
			return " "+jour+" "+debut+" "+fin+" ";
		}
	}

	static class UE{
		int id;
		Creneau amphi;
		int TDChoisi;
		LinkedList<Creneau> TD = new LinkedList<Creneau>();
		LinkedList<Boolean> indicesDisponibles = new LinkedList<Boolean>();

		boolean prise, disponible=true;
		UE(int i){
			id=i;
		}

		public void add(int jour, int heure, int cat) {
			if(cat==0)
				amphi= new Creneau(jour, heure, heure+1);
			else {
				TD.add(new Creneau(jour, heure, heure+2));
				indicesDisponibles.add(true);
			}
		}

		public void prevenirCreneauPris(Creneau a) {
			if(Creneau.gene(a, amphi)) {
				disponible=false;
				return;
			}

			for (int i=0; i<TD.size(); i++) {
				if(indicesDisponibles.get(i)) {
					if(Creneau.gene(a, TD.get(i))) {
						indicesDisponibles.set(i, false);
					}
				}
			}

			for(boolean b : indicesDisponibles) {
				if(b)
					return;
			}
			disponible=false;
		}

		public void prendre(int indexTD) {
			prise=true;
			disponible=false;
			TDChoisi=indexTD;
			for(UE u:listeUE) {
				if(u!=this) {
					u.prevenirCreneauPris(amphi);
					u.prevenirCreneauPris(TD.get(TDChoisi));
				}
			}
		}

		LinkedList<Integer> getFreeIndexList() {
			LinkedList<Integer> l = new LinkedList<>();
			for(int i=0; i<indicesDisponibles.size();i++) {
				if(indicesDisponibles.get(i))
					l.add(i);
			}
			return l;
		}

		public void reset() {
			prise=false;
			disponible=true;
			for (int i = 0; i < indicesDisponibles.size(); i++) {
				indicesDisponibles.set(i, true);
			}
		}

		@Override
		public String toString() {

			return id+""/*+" "+amphi+" "+TDChoisi+" "+TD.get(TDChoisi)+"   "*/;
		}

		public void afficher() {
			StringBuilder s = new StringBuilder();
			s.append(toString());
			if(!disponible)
				s.append("nondispo");
			else {
			s.append(amphi.toString());
			for(int i=0; i<TD.size();i++) {
				if(indicesDisponibles.get(i))
					s.append(TD.get(i).toString());
			}
			}
			
			System.out.println(s);	
		}
		
		static Comparator<UE[]> comparator = new Comparator<UE[]>() {

			@Override
			public int compare(UE[] o1, UE[] o2) {
				for (int i = 0; i < o1.length; i++) {
					if(i==o2.length)
						return -1;
					final int dif = listeUE.indexOf(o1[i])-listeUE.indexOf(o2[i]);
					if(dif!=0)
						return dif;
				}
				return 0;
			}
		};
	}

	static LinkedList<UE> listeUE = new LinkedList<>();
	
	static int[] idUE = {26,5,8,20,22,24,12,2,10};
	
	public static void main(String[] args) {
		//for (int i : new int[]{2,5,8,10,12,17,18,19,20,21,22,24,25,26,27}) {
		for (int i : idUE) {
			creerMat(i);			
		}
		iniC();
		//kParmisN(0, 0);
		//System.out.println(s);
		/*
		int p=1;
		for (UE ue : listeUE) {
			int q=ue.TD.size();
			System.out.println(q);
			p*=q;
		}
		System.out.println(p);*/
		f(new UE[5], new int[5],0,0);
		Iterator<UE[]> it = tree.iterator();
		while (it.hasNext()) {
			UE[] tabU = it.next();
			System.out.println(tabU[0] + " "+tabU[1] + " "+tabU[2] + " "+tabU[3] + " "+tabU[4]);
		}
	}
	
	static int[] nbGroupe = new int[] {2,2,1,1,2,3,6,4};
	static int[] nbGroupeDesUEChoisies = new int[5];
	static int s=0;
	
	static void kParmisN(int indexMin, int profondeur) {
		if(profondeur==nbGroupeDesUEChoisies.length) {
			int p=1;
			for (int nb:nbGroupeDesUEChoisies) {
				p*=nb;
			}
			s+=p;
			return;
		}
		for (int i = indexMin; i < nbGroupe.length; i++) {
			nbGroupeDesUEChoisies[profondeur]=nbGroupe[i];
			kParmisN(i+1, profondeur+1);
		}
	}

 
	static TreeSet<UE[]> tree = new TreeSet<>(UE.comparator);

	static void f(UE[] liste, int[] listeI, int indMin, int profondeur){
		if(profondeur==5) {
			tree.add(liste.clone());
			return;
		}

		for (int i=indMin; i<listeUE.size(); i++) {
			UE u = listeUE.get(i);
			if(u.disponible) {
				for(int index : u.getFreeIndexList()) {
					u.prendre(index);
					liste[profondeur]=u;
					listeI[profondeur]=index;
					f(liste, listeI, i+1, profondeur+1);
					reset(liste, listeI, profondeur);
				}
			}
		}
	}



	private static void reset(UE[] liste, int[]listeI, int profondeur) {
		for(UE u : listeUE) {
			u.reset();
		}

		for(int i = 0; i<profondeur; i++) {
			liste[i].prendre(listeI[i]);
		}

	}


	static void iniC(){
		creneau(5, 0, 0, 0);
		creneau(8, 0, 1, 0);
		creneau(10, 0, 2, 0);
		creneau(26, 0, 3, 0);
		creneau(2, 1, 0, 0);
		creneau(18,1,1,0);
		creneau(24, 2, 1, 0);
		creneau(27,2,2,0);
		creneau(17,3,0,0);
		creneau(19,3,1,0);
		creneau(25,3,2,0);
		creneau(21, 3, 3, 0);
		creneau(12, 4, 1, 0);
		creneau(22, 4, 2, 0);
		creneau(20, 4, 3, 0);

		
		creneau(10, 0, 0);
		//creneau(24, 0, 0);
		
		creneau(24, 0, 1);
		
		creneau(2, 0, 2);
		
		//creneau(10, 0, 3);
		creneau(20, 0, 3);
		
		
		
		//creneau(25,1,1);
		//creneau(17,1,1);
		
		creneau(8, 1, 2);
		
		//creneau(26, 1, 3);
		creneau(18, 1, 3);
		creneau(22, 1, 3);
		
		
		
		//creneau(12, 2, 0);
		creneau(17,2,0);
		creneau(2, 2, 0);
		
		creneau(17,2,2);
		creneau(26, 2, 2);
		creneau(10, 2, 2);
		creneau(5, 2, 2);
		
		creneau(21, 2, 3);
		creneau(24, 2, 3);
		
		
		
		//creneau(12, 3, 0);
		
		//creneau(2, 3, 1);
		creneau(10, 3, 1);
		
		creneau(27,3,2);
		
		creneau(19,3,3);
		//creneau(17,3,3);
		//creneau(2,3,3);
		
		
		
		//creneau(8, 4, 0);
		creneau(2, 4, 0);
		
		//creneau(12,4, 2);
		creneau(27,4, 2);
		creneau(2, 4, 2);
		//creneau(5, 4, 2);
	}

	static void creerMat(int i){
		listeUE.add(new UE(i));
	}

	static void creneau(int ue, int jour,int heure){
		creneau(ue, jour, heure, 1);
	}

	static void creneau(int ue, int jour,int heure, int cat){
		for (UE u : listeUE){
			if (u.id==ue){
				u.add(jour,heure,cat);
				return;
			}
		}
	}

}