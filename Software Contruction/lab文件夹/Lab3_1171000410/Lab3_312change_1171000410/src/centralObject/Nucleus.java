package centralObject;

public class Nucleus extends CentralObject{
	
	private int p;   //������
	private int n;   //������
	
	/**Constructor*/
	public Nucleus(String name ,int p ,int n) {
		super(name);
		this.p = p;
		this.n = n;
	}	
	
	public int getP() {
		return p;
	}
	
	public int getN() {
		return n;
	}
	
}
