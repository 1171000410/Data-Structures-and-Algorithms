package P2;

public class Person {
	private String name;
	public Person (String name) {
		this.name = name;
	}
	public String getName() {   
		return this.name;
	}
	public boolean nameSameWith(String name) {   //ȷ�������Ƿ��ظ�
		if(this.name.equals(name)) {
			return true;
		}
		else
			return false;
	}

}
