/*
 * THIRIAT léonie 
 * BEROUKHIM Keyvan
 */

public class Groupe implements Runnable {
	private static int nbGroupe=1;
	private final int id, nb;
	private final Salle salle;

	public Groupe(int nb,Salle salle) {
		super();
		this.id = nbGroupe++;
		this.nb = nb;
		this.salle = salle;
	}

	@Override
	public void run() {
		boolean reservation=false;
		if(!salle.reserverContigues(this)){//n'a pas réussi à les placer en groupe
			reservation=salle.reserver(this);
		}else{
			reservation=true;
		}
		
		Thread.yield();
		
		if(reservation && Math.random()<.25){
			salle.annuler(this);
		}
		
	}

	int getNb(){
		return nb;
	}
	int getId(){
		return id;
	}

}
