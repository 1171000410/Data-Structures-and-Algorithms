package P3;

public class Position {
	private int x;  //������
	private int y;  //������
	
	// Abstraction function:
    //   Position���������������ϵ�λ�ã�x����λ�õĺ����꣬y����λ�õ�������
    // Representation invariant:
    //   position����ӳ��Ϊ��
    //
    // Safety from rep exposure:
    //   ����fields���� private and final
    //   ʹ��immutable��������
	
	/**Constructor*/
	public Position(int positionX, int positionY) {
		this.x = positionX;
		this.y = positionY;	
	}

	/**Return this position's abscissa*/
	public int getX() {
		return this.x;
	}
	
	/**Return this position's ordinate*/
	public int getY() {
		return this.y;
	}
	
	/**
	 * Judge whether two positions are equal
	 * @param that position
	 * @return true if the two positions are equal; or false
	 */
	@Override
	public boolean equals(Object that) {  //�ж�����λ���Ƿ����
		if(that instanceof Position) {
			if(this.getX() == ((Position)that).getX() && this.getY() == ((Position)that).getY()) {
				return true;
			}
		}
		return false;
	}
}
