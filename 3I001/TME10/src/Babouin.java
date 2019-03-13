public class Babouin implements Runnable{

	static int nb;
	int id=nb++;
	static Corde corde = new Corde();
	private Position position = Math.random()<.5?Position.SUD:Position.NORD;


	public void run() {
		try{/*
			if(Math.random()<.1){
				System.out.println(this.toString() + "(KONG) arrive");
				corde.accederKong();
				System.out.println(this.toString() + "(KONG) a pris la corde.");
				traverser();
				System.out.println(this.toString() + "(KONG) est arrive.");
				corde.lacherKong();
			}
			else{*/
				System.out.println(this.toString() + " arrive");
				corde.acceder(position);
				System.out.println(this.toString() + " a pris la corde.");
				traverser();
				System.out.println(this.toString() + " a traverse.");
				corde.lacher(position);
				System.out.println(this.toString() + " est arrive.");
			//}
		}
		catch(InterruptedException e) {
			System.out.println("Pb babouin !");
		}
	}

	private void traverser() throws InterruptedException {
		corde.acceder(position);
		System.out.println(this.toString() + " a accede.");
		
		Thread.sleep((int)(Math.random()*10));
		corde.lacher(position);
		position=position==Position.NORD?Position.SUD:Position.NORD;
	}
	
	@Override
	public String toString() {
		return id+" "+position;
	}
}
