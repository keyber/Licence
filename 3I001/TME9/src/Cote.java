import graphique.Fenetre;
import java.awt.Point;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
public class Cote{
	private final static double LG_MIN = 8.0;
	private final Fenetre f;
	private final Point m, n;

	private static ExecutorService e = Executors.newFixedThreadPool(5);
	private ExecutorService mExecutorService;
	

	public Cote (Fenetre f, Point m, Point n, ExecutorService e) {
		this.f = f;
		this.m = m;
		this.n = n;
		this.mExecutorService=e;
	}
	public Cote (Fenetre f, Point m, Point n) {
		this.f = f;
		this.m = m;
		this.n = n;
	}

	public void tracer () {
		if(TestVonKoch.question==2){
			new Thread(new Runnable() {

				@Override
				public void run() {
					final double xa, ya, xb, yb, xc, yc;
					if( Segment.longueur(m, n) > LG_MIN ) {
						xa = (2*m.x + n.x) / 3.0;
						xc = (m.x + 2*n.x) / 3.0;
						ya = (2*m.y + n.y) / 3.0;
						yc = (m.y + 2*n.y) / 3.0;
						xb = xa + ( xc - xa - (Math.sqrt(3.0)*(yc - ya)) ) / 2.0;
						yb = ya + ( yc - ya + (Math.sqrt(3.0)*(xc - xa)) ) / 2.0;
						Point a =new Point();
						a.setLocation(xa, ya);
						Point b = new Point();
						b.setLocation(xb, yb);
						Point c =new Point();
						c.setLocation(xc, yc);
						new Cote(f, m, a).tracer();
						new Cote(f, a, b).tracer();
						new Cote(f, b, c).tracer();
						new Cote(f, c, n).tracer();
					}
					else
					{
						Segment.tracer(f, m, n);
					}
				}
			}).start();
		}
		else if(TestVonKoch.question==3){
			mExecutorService.execute(new Runnable() {

				@Override
				public void run() {
					final double xa, ya, xb, yb, xc, yc;
					if( Segment.longueur(m, n) > LG_MIN ) {
						xa = (2*m.x + n.x) / 3.0;
						xc = (m.x + 2*n.x) / 3.0;
						ya = (2*m.y + n.y) / 3.0;
						yc = (m.y + 2*n.y) / 3.0;
						xb = xa + ( xc - xa - (Math.sqrt(3.0)*(yc - ya)) ) / 2.0;
						yb = ya + ( yc - ya + (Math.sqrt(3.0)*(xc - xa)) ) / 2.0;
						Point a =new Point();
						a.setLocation(xa, ya);
						Point b = new Point();
						b.setLocation(xb, yb);
						Point c =new Point();
						c.setLocation(xc, yc);
						new Cote(f, m, a, mExecutorService).tracer();
						new Cote(f, a, b, mExecutorService).tracer();
						new Cote(f, b, c, mExecutorService).tracer();
						new Cote(f, c, n, mExecutorService).tracer();
					}
					else
					{
						Segment.tracer(f, m, n);
					}
				}
			
		});
		}
		else if(TestVonKoch.question==4){
			e.execute(new Runnable() {

				@Override
				public void run() {
					final double xa, ya, xb, yb, xc, yc;
					if( Segment.longueur(m, n) > LG_MIN ) {
						xa = (2*m.x + n.x) / 3.0;
						xc = (m.x + 2*n.x) / 3.0;
						ya = (2*m.y + n.y) / 3.0;
						yc = (m.y + 2*n.y) / 3.0;
						xb = xa + ( xc - xa - (Math.sqrt(3.0)*(yc - ya)) ) / 2.0;
						yb = ya + ( yc - ya + (Math.sqrt(3.0)*(xc - xa)) ) / 2.0;
						Point a =new Point();
						a.setLocation(xa, ya);
						Point b = new Point();
						b.setLocation(xb, yb);
						Point c =new Point();
						c.setLocation(xc, yc);
						new Cote(f, m, a, e).tracer();
						new Cote(f, a, b, e).tracer();
						new Cote(f, b, c, e).tracer();
						new Cote(f, c, n, e).tracer();
					}
					else
					{
						Segment.tracer(f, m, n);
					}
				}
			
		});
		}
		else{

			final double xa, ya, xb, yb, xc, yc;
			if( Segment.longueur(m, n) > LG_MIN ) {
				xa = (2*m.x + n.x) / 3.0;
				xc = (m.x + 2*n.x) / 3.0;
				ya = (2*m.y + n.y) / 3.0;
				yc = (m.y + 2*n.y) / 3.0;
				xb = xa + ( xc - xa - (Math.sqrt(3.0)*(yc - ya)) ) / 2.0;
				yb = ya + ( yc - ya + (Math.sqrt(3.0)*(xc - xa)) ) / 2.0;
				Point a =new Point();
				a.setLocation(xa, ya);
				Point b = new Point();
				b.setLocation(xb, yb);
				Point c =new Point();
				c.setLocation(xc, yc);
				new Cote(f, m, a).tracer();
				new Cote(f, a, b).tracer();
				new Cote(f, b, c).tracer();
				new Cote(f, c, n).tracer();
			}
			else
			{
				Segment.tracer(f, m, n);
			}
		}
	}
}

