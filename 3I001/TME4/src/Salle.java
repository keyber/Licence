/*
 * Léonie THIRIAT
 */
import java.util.ArrayList;

public class Salle {
	private int nbPlaceMax, nbCourant=0;//courant rempla�able par clients.size()
	private ArrayList<Client> clients;
	private ArrayList<Barbier> barbiers;

	public Salle(int nbPlaceMax) {
		super();
		this.nbPlaceMax = nbPlaceMax;
		this.clients = new ArrayList<>();
		this.barbiers = new ArrayList<>();
	}

	synchronized public boolean sallePleine(){
		return nbPlaceMax==nbCourant;
	}
	synchronized public boolean salleVide(){
		return 0==nbCourant;
	}

	synchronized public boolean AjouteClient(Client c){
		if(sallePleine())
			return false;

		final boolean salleEtaitVide = salleVide();

		c.setDansLaSalleDAttente(true);
		clients.add(c);
		nbCourant++;
		System.out.println("ajout "+c +" : "+nbCourant+"/"+nbPlaceMax);

		//r�veil les barbiers apr�s ajout c
		if(salleEtaitVide){
			System.out.println("r�veil des barbiers");
			this.notifyAll();
		}
		return true;
	}

	synchronized public void enleveClient(Client c){
		if(!clients.contains(c))
			throw new RuntimeException("On ne peut pas enlever quelqu'un qui n'est pas l� !");
		nbCourant--;
		c.setDansLaSalleDAttente(false);
		clients.remove(c);
		System.out.println(c+" va voir le barbier, une place se lib�re : "+nbCourant+"/"+nbPlaceMax);
	}

	synchronized public void addBarbier(Barbier b){
		barbiers.add(b);
	}

	public Client getFirst(){
		return clients.get(0);
	}

}
