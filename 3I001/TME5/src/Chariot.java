/*
 * Léonie THIRIAT
 */
import java.util.ArrayList;

public class Chariot {
	private int poidsMax, nombreMax;
	private ArrayList<AleaObjet> contenu=new ArrayList<AleaObjet>();

	boolean chargeurVide=false;
	public ArrayList<AleaObjet> getContenu() {
		return contenu;
	}

	public Chariot(int poidsMax, int nombreMax) {
		this.poidsMax = poidsMax;
		this.nombreMax = nombreMax;
	}

	public boolean add(AleaObjet aleaObjet) {
		if(contenu.size()>=nombreMax){
			System.out.println(this+" refus taille "+aleaObjet);
			return false;
		}
		if(poidsTot()+aleaObjet.getPoids()>poidsMax){
			System.out.println(this+" refus poids "+aleaObjet);
			return false;
		}
		System.out.println(this+" ajout "+aleaObjet);
		contenu.add(aleaObjet);
		return true;
	}

	public int poidsTot(){
		int s=0;
		for(AleaObjet o : contenu)
			s+=o.getPoids();
		return s;
	}

	public AleaObjet remove(){
		System.out.println(this+" remove "+contenu.get(0));
		return contenu.remove(0);
	}

	@Override
	public String toString() {
		return "Chariot taille ="+contenu.size()+" poids tot="+poidsTot();
	}
	
	public void setChargeurVide(){
		chargeurVide=true;
	}
}
