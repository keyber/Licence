import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CordeQ3 {

	int cpt;
	Position sens;

	Semaphore sLock = new Semaphore(1);
	Semaphore sCond = new Semaphore(0);
	Semaphore sCondKong = new Semaphore(0);
	int sCompteur;

	boolean kongPresent;

	public void acceder(Position position) throws InterruptedException {
		sLock.acquire();
		

		try{
			while(cpt!=0 && sens!=position || cpt>=5 || kongPresent){
				sWait();
			}

			if(cpt==0)//inutile
				sens=position;

			cpt++;
		}
		finally {
			sLock.release();
		}
	}

	public void lacher(Position position) throws InterruptedException {
		sLock.acquire();
		try{
			cpt--;
			if(cpt==0){
				sens=null;//inutile
			}
			sSignalAll();
		}
		finally {
			sLock.release();
		}
	}

	public void accederKong() throws InterruptedException{
		sLock.acquire();
		try{
			while(cpt!=0){
				sWaitKong();
			}
			cpt++;
			kongPresent=true;
		}
		finally {
			sLock.release();
		}
	}
	
	public void lacherKong() throws InterruptedException{
		sLock.acquire();
		try{
			sSignalAllKong();
			cpt--;
			kongPresent=false;
		}
		finally {
			sLock.release();
		}
	}

	private void sSignalAll() {
		for (int i = 0; i < cpt; i++) {			
			sCond.release();
		}
	}

	private void sWait() throws InterruptedException{
		sCompteur++;
		sLock.release();//relache
		sCond.acquire();//wait
		sLock.acquire();//reprend
		sCompteur--;
	}

	private void sWaitKong() throws InterruptedException{
		sCompteur++;
		sLock.release();//relache
		sCondKong.acquire();//wait
		sLock.acquire();//reprend
		sCompteur--;
	}

	private void sSignalAllKong() {
		for (int i = 0; i < cpt; i++) {			
			sCondKong.release();
		}
	}

}
