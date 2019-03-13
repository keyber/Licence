import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Corde {

	int cpt;
	Position sens;
	
	ReentrantLock l= new ReentrantLock();
	Condition accesOK = l.newCondition();
	
	public void acceder(Position position) throws InterruptedException {
		l.lock();
		System.out.println("1");
		try{
			while(cpt!=0 && sens!=position || cpt>=5){
				System.out.println(2);
				accesOK.await();
				System.out.println(3);
			}
			
			if(cpt==0)
				sens=position;
			
			cpt++;
		}
		finally {
			l.unlock();
		}
		
	}

	
	public void lacher(Position position) {
		System.out.println("aa");
		l.lock();
		System.out.println("bb");
		try{
			cpt--;
			if(cpt==0){
				sens=null;
			}
			accesOK.signalAll();
		}
		finally {
			l.unlock();
		}
	}
	
}
