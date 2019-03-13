/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */

public class SegAccueil {
	//Loco occupant;
	private boolean occupe=false;

	public void reserver() throws InterruptedException {
		synchronized (this) {
			while(occupe){
				wait();
			}
		occupe=true;
		}
	}

	public void liberer() {
		occupe=false;
		synchronized (this) {
			this.notifyAll();			
		}
	}
}
