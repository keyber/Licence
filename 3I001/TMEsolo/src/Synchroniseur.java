//BEROUKHIM Keyvan 3506789
public class Synchroniseur {

	private Perroquet tab[] = new Perroquet[3];
	private int index=0;

	public void enregistrer(Perroquet p){
		synchronized (this) {
			
			for (int i = 0; i < tab.length; i++) {
				
				if(tab[i]==null){
					tab[i]=p;
					
					if(i==tab.length-1)
						this.notifyAll();
					
					return;
				}
			}
		}
	}

	public void barriere() throws InterruptedException{
		synchronized (this) {
			while(tab[tab.length-1]==null){
				this.wait();
			}

		}
	}

	public void reveillerUnPerroquet() {
		int index2;//permet de relacher synchronized sans perdre la valeur
		
		synchronized (this) {
			index = (index+1)%tab.length;
			index2=index;
		}
		
		tab[index2].reveiller();			
	}
	
	public void reveilleRandom() throws InterruptedException{
		barriere();
		
		int index2;
		
		synchronized (this) {
			index = (int)(Math.random()*3);
			index2=index;
		}
		
		tab[index2].reveiller();	
	}
}
