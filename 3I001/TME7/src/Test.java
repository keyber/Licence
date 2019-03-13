/*
 * léonie THIRIAT
 * keyvan BEROUKHIM
 */
import java.util.ArrayList;
import java.util.List;

public class Test {

	public static void main(String[] args) {
		List<Runnable> runnable = new ArrayList<Runnable>();
		EnsembleDonnee ens = new EnsembleDonnee();
		runnable.add(new Producteur(ens));
		runnable.add(new Producteur(ens));
		runnable.add(new Lecteur(ens));
		runnable.add(new Lecteur(ens));
		runnable.add(new Effaceur(ens));
		runnable.add(new Effaceur(ens));
		
		for (Runnable r : runnable){
			new Thread(r).start();
		}
	}

}
