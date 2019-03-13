/*
 * THIRIAT léonie 
 * BEROUKHIM Keyvan
 */

public class Salle {
	private final int nbRangs, nbPlaceParRang;
	private final int[][] placeLibre;
	public Salle(int nbRangs, int nbPlaceParRang) {
		super();
		this.nbRangs = nbRangs;
		this.nbPlaceParRang = nbPlaceParRang;

		placeLibre=new int[nbRangs][nbPlaceParRang];
	}


	private int nContiguesRangI(int n, int i){
		int j;
		int placeLibreContigues=0;
		for(j=0;j<nbPlaceParRang;j++){
			if(placeLibre[i][j]==0){
				placeLibreContigues++;
				if(placeLibreContigues>=n){
					return j-placeLibreContigues+1;
				}
			}
			else  {
				placeLibreContigues=0;
			}
		}
		return -1;
	}

	synchronized boolean reserverContigues(Groupe g){
		for (int i = 0; i < nbRangs; i++) {
			final int temp= nContiguesRangI(g.getNb(), i);

			if(temp!=-1){
				for(int j=temp;j<temp+g.getNb();j++){
					placeLibre[i][j] = g.getId();
				}
				System.out.println(g.getId()+ " Placés en groupe " + g.getNb());
				System.out.println("place prise "+placePrise());
				return true;
			}

		}
		System.out.println(g.getId()+ " Pas placés en groupe " + g.getNb());
		return false;
	}

	private boolean capaciteOK(int n){
		int cpt=0;
		for (int i = 0; i < nbRangs; i++)
			for (int j = 0; j < nbPlaceParRang; j++)
				if(placeLibre[i][j]==0)
					cpt++;
		return cpt>=n;
	}

	synchronized boolean reserver(Groupe g){
		if(!capaciteOK(g.getNb())){
			System.out.println(g.getId()+ " PAS PLACES " + g.getNb());
			return false;
		}

		int cpt=0;
		for (int i = 0; i < nbRangs; i++) {
			for (int j = 0; j < nbPlaceParRang; j++) {
				if(placeLibre[i][j]==0){
					placeLibre[i][j]=g.getId();
					cpt++;
					if(cpt==g.getNb()){
						System.out.println(g.getId()+ " Placés pas en groupe " + g.getNb());
						System.out.println("place prise "+placePrise());
						return true;
					}
				}
			}		
		}

		System.out.println("place prise "+placePrise());
		return true;
	}

	private int placePrise (){
		int cpt=0;
		for (int i = 0; i < nbRangs; i++)
			for (int j = 0; j < nbPlaceParRang; j++)
				if(placeLibre[i][j]!=0)
					cpt++;
		return cpt;
	}

	synchronized void annuler(Groupe g){
		for (int i = 0; i < nbRangs; i++) {
			for (int j = 0; j < nbPlaceParRang; j++) {
				if(placeLibre[i][j]==g.getId()){
					placeLibre[i][j]=0;
				}
			}
		}
		System.out.println(g.getId()+ " ANNULES " + g.getNb());
		System.out.println("place prise "+placePrise());
	}
}
