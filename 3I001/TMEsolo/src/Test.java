//BEROUKHIM Keyvan 3506789
import java.util.LinkedList;
import java.util.List;

public class Test {
	public static void main(String[] args) {
		Synchroniseur2 s = new Synchroniseur2();
		List<Thread> l = new LinkedList<Thread>();
		l.add(new Thread(new Perroquet(s, "Rico")));
		l.add(new Thread(new Perroquet(s, "Coco")));
		l.add(new Thread(new Perroquet(s, "Jaco")));

		//lance
		for (Thread t : l)
			t.start();

		try {
			s.reveilleRandom();//attend que tout le monde soit la puis en reveille un

			//attend
			Thread.sleep((int)((20 + Math.random()*10)*1000));

			//demande aux perroquets de s'arreter
			for (Thread t : l)
				t.interrupt();

			//attend qu'ils se soient arretes
			for (Thread t : l)
				t.join();

			//se termine en dernier
			System.out.println("fin main");

		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

}
