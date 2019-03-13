//BEROUKHIM Keyvan 3506789
public class Perroquet implements Runnable{

	private Synchroniseur2 sync;
	private String prenom;
	private boolean reveille=false;

	public Perroquet(Synchroniseur2 sync, String prenom) {
		this.sync = sync;
		this.prenom = prenom;
	}

	@Override
	public void run() {
		try{
			sync.enregistrer(this);
			System.out.println(prenom+" avant barriere");
			sync.barriere();
			//affichage peut peut etre decale
			System.out.println(prenom+" après barriere");

			while(true){
				attendre();//attend qu'on le reveille

				System.out.println(prenom);

				Thread.sleep((int)((Math.random()*3+1)*1000));

				synchronized (this) {		
					reveille=false;//se rendort
				}

				sync.reveillerUnPerroquet();
			}
		}
		catch(InterruptedException e){
			System.out.println(prenom+ " interrompu");
		}


	}

	private void attendre() throws InterruptedException{
		while(!reveille){
			synchronized (this) {
				this.wait();
			}
		}
	}
	public void reveiller(){
		synchronized (this) {
			reveille=true;
			this.notifyAll();
		}
	}

}
