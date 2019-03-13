/*
 * THIRIAT léonie 
 * BEROUKHIM Keyvan
 */

public class Test {

	private final static int NB_GROUPE=40;
	public static void main(String[] args) {
		Salle s= new Salle(10, 20);
		
		for (int i = 0; i < NB_GROUPE; i++) {
			Thread t = new Thread(new Groupe((int)(Math.random()*NB_GROUPE+1), s));
			t.start();
		}
		

	}

}
