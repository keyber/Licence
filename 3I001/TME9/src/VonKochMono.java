import graphique.Fenetre;
import java.awt.Point;
import java.util.concurrent.Executors;

public class VonKochMono {
	private final static double LG_MIN = 8.0;
	Fenetre f;
	
	public VonKochMono (Fenetre f, Point a, Point b, Point c) {
		this.f = f;
		
		if(TestVonKoch.question==3){
		new Cote(f, b, a, Executors.newFixedThreadPool(1)).tracer();
		new Cote(f, a, c, Executors.newFixedThreadPool(1)).tracer();
		new Cote(f, c, b, Executors.newFixedThreadPool(1)).tracer();
		}
		else{
			new Cote(f, b, a).tracer();
			new Cote(f, a, c).tracer();
			new Cote(f, c, b).tracer();
		}
	}
}
