/*BEROUKHIM THIRIAT*/
public class Restaurant {
	int tables  = 10;
	//Semaphore tables = new Semaphore(10);
	static int numRes;
	
	public synchronized int reserver(GroupeClients g){
		final int nbTable = (g.nbPers+1)/2;
		if(tables/*.availablePermits()*/<nbTable)
			return -1;
		tables-=nbTable;
		
		System.out.println(tables+ " tables restantes");
		
		return numRes++;
	}
}