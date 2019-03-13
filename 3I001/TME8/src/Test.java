
public class Test {

	public static final int NB_CLIENT=5;
	
	public static void main(String[] args) {
		Serveur s = new Serveur();
		Thread ts = new Thread(s);
		ts.start();

		Thread[] tc = new Thread[NB_CLIENT];
		for (int i = 0; i < tc.length; i++)
			(tc[i] = new Thread(new Client(s))) .start();
		
		try {
			for (int i = 0; i < tc.length; i++)
				tc[i].join();
		}
		catch(InterruptedException e){
			e.printStackTrace();
		}
		
		ts.interrupt();
		
	}
}
