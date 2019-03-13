/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */

public class Loco implements Runnable{

	private SegAccueil sAccueil;
	private SegTournant sTournant;
	private PoolHangars pHangars;
	private int id;
	public Loco(SegAccueil sAccueil, SegTournant sTournant, PoolHangars pHangars) {
		this.sAccueil = sAccueil;
		this.sTournant = sTournant;
		this.pHangars = pHangars;
		id=nb++;
	}

	private static int nb=1;

	@Override
	public void run() {
		try {
			System.out.println(this +"0");
			sAccueil.reserver();//monte sur sAccueil
			System.out.println(this +"1");
			sTournant.appeler(0);//
			System.out.println(this +"2");
			sTournant.attendrePositionOK();
			System.out.println(this +"3");
			sTournant.entrer(id);
			System.out.println(this +"4");
			sAccueil.liberer();
			System.out.println(this +"5");
			sTournant.attendrePositionOK();
			System.out.println(this +"6");
			pHangars.getHangar(sTournant.getPosition()).entrer(id);
			System.out.println(this +"7");
			sTournant.sortir(id);
			System.out.println(this +"8");
			System.out.println("\n"+pHangars+"\n\n");
		}
		catch(InterruptedException e) {
			System.out.println("Loco " + id + " interrompue (ne devrait pas arriver)");
		}
	}

	@Override
	public String toString() {
		return "loco"+id+" étape ";
	}
}
