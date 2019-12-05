package P3;

public class Piece {
	private String pieceName; //��������
	private int pieceState;  //0δ���ã�1�ѷ��á�-1��remove
	private int pieceX;    //������
	private int pieceY;    //������
	
	// Abstraction function:
    //   Piece���������ϵ����� ��pieceName�������ӵ����ƣ�pieceState�������ӵķ���״̬��
	//   pieceX�������ӵĺ����꣬pieceY�������ӵ�������
    // Representation invariant:
    //   piece����ӳ��Ϊ��
    //
    // Safety from rep exposure:
    //   ����fields���� private and final
    //   ʹ��immutable��������
	
	/**Constructor*/
	public Piece(String name,int state, int x ,int y) {
		this.pieceName = name;
		this.pieceState = state;
		this.pieceX = x;
		this.pieceY = y;
	}
	
	/**Return this piece's name*/
	public String getPieceName() {
		return this.pieceName;
	}
	
	/**Return this piece's state*/
	public int getPieceState() {
		return this.pieceState;
	}
	
	/**Return this piece's abscissa*/
	public int getPieceX() {
		return this.pieceX;
	}
	
	/**Return this piece's ordinate*/
	public int getPieceY() {
		return this.pieceY;
	}
	
	/**
	 * Set this piece's name
	 * @param name which is to be set
	 */
	public void setPieceName(String name) {
		assert name != null;
		this.pieceName = name;
	}
	
	/**
	 * Set this piece's state
	 * @param state which is to be set
	 */
	public void setPieceState(int state) {
		this.pieceState = state;
	}
	
	/**
	 * Set this piece's abscissa
	 * @param x which is to be set
	 */
	public void setPieceX(int x) {
		this.pieceX = x;
	}
	
	/**
	 * Set this piece's ordinate
	 * @param y which is to be set
	 */
	public void setPieceY(int y) {
		this.pieceY = y;
	}
	
	/**
	 * Remove this piece from a board
	 * Set the state , abscissa and ordinate to -1
	 */
	public void remove() {
		this.setPieceState(-1);
		this.setPieceX(-1);
		this.setPieceY(-1);
	}
	
}
