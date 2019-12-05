package P3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class MyChessAndGoGame {
	public Game game = new Game();  //�½���Ϸ
	public String player1Name;  //���1����
	public String player2Name;  //���2���� 
	public ArrayList<Player> players = new ArrayList<Player>(); //�������

	/**Print menu for selection*/
	public void menu() {
		System.out.println("1.��������(Χ��)");
		System.out.println("2.����(Χ��)");
		System.out.println("3.�ƶ�����(��������)");
		System.out.println("4.����(��������)");
		System.out.println("5.��ѯĳ��λ�õ�ռ�����");
		System.out.println("6.�鿴����");
		System.out.println("7.����������ҷֱ��������ϵ���������");
		System.out.println("8.����");
		System.out.println("9.end");
	}

	public void myMain() throws Exception {
		BufferedReader reader = null;

		try {
			reader = new BufferedReader(new InputStreamReader(System.in));

			while (true) { // ֱ���õ���ȷ������
				System.out.println("��������Ϸ����:(chess or go)");
				String input = reader.readLine();
				if (input.equals("chess") || input.equals("go")) {
					game.setGameName(input);
					break;
				} else {
					System.out.println("������Ϸ���ʹ�������������");
				}
			}

			System.out.println("������player1������:");
			player1Name = reader.readLine();
			System.out.println("������player2������:");
			player2Name = reader.readLine();

			if (game.getGameName().equals("chess")) {
				game.initByChess(player1Name, player2Name);
			} else {
				game.initByGo(player1Name, player2Name);
			}
			players.add(game.getGamePlayer1());
			players.add(game.getGamePlayer2());

			System.out.println("��Ϸ��ʼ��");

			int turn = 0;
			while (true) {
				System.out.printf("\n�ֵ�%sִ�У�\n", players.get(turn).getPlayerName());
				menu();
				String choice = reader.readLine();
				String line = "";
				String[] items;
				boolean flag = false;
				
				if((game.getGameName().equals("chess") && (choice.equals("1")||choice.equals("1")))||
					(game.getGameName().equals("go") && (choice.equals("3")||choice.equals("4")))) {
					System.out.println("�����������Ӧ����Ĳ�����");
					continue;
				}
				
				switch (choice) {
				case "1":  //��������(Χ��)
					System.out.println("���������룺������ ������ ������");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�

					if (items.length != 3) {
						System.out.println("��������밴�����������룺");
						continue;
					} else {
						try {
							String pieceName = items[0];
							int positionX = Integer.valueOf(items[1]); // StringתΪInteger
							int positionY = Integer.valueOf(items[2]);
							Position position = new Position(positionX, positionY);

							Player player = players.get(turn);
							Piece piece = player.getPiece(pieceName);
							
							if (piece == null) {
								System.out.println("δ�ҵ��ɷ��õĸ����ӣ��밴�����������룺");
								continue;
							}

							game.putPiece(player, piece, position);

							turn = (turn + 1) % 2;

							System.out.println("Successful placement !");
						} catch (Exception e) {
							System.out.println("��׽�쳣������������");
							continue;
						}
					}
					break;

				case "2":  //����(Χ��)
					System.out.println("��������Ҫ����������꣺");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�

					if (items.length != 2) {
						System.out.println("��������밴�����������룺");
						continue;
					} else {
						try {
							int x = Integer.valueOf(items[0]);
							int y = Integer.valueOf(items[1]);

							Position position = new Position(x, y);

							Player player = players.get(turn);

							game.removePiece(player, position);

							turn = (turn + 1) % 2;
							System.out.println("Successful removal !");
						} catch (Exception e) {
							System.out.println("��׽�쳣������������");
							continue;
						}
					}
					break;

				case "3":  //�ƶ�����(��������)
					System.out.println("��������Ҫ�ƶ��ĵ������Ŀ�ĵ����꣺");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�

					if (items.length != 4) {
						System.out.println("��������밴�����������룺");
						continue;
					} else {
						try {
							int oldX = Integer.valueOf(items[0]);
							int oldY = Integer.valueOf(items[1]);
							int newX = Integer.valueOf(items[2]);
							int newY = Integer.valueOf(items[3]);
							Position oldPosition = new Position(oldX, oldY);
							Position newPosition = new Position(newX, newY);

							Player player = players.get(turn);

							game.movePiece(player, oldPosition, newPosition);

							turn = (turn + 1) % 2;
							System.out.println("Successful movement !");
						} catch (Exception e) {
							System.out.println("��׽�쳣������������");
							continue;
						}
					}
					break;

				case "4":  //4.����(��������)
					System.out.println("�������ƶ���������ͱ����������꣺");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�

					if (items.length != 4) {
						System.out.println("��������밴�����������룺");
						continue;
					} else {
						try {
							int x1 = Integer.valueOf(items[0]);
							int y1 = Integer.valueOf(items[1]);
							int x2 = Integer.valueOf(items[2]);
							int y2 = Integer.valueOf(items[3]);
							Position oldPosition = new Position(x1, y1);
							Position newPosition = new Position(x2, y2);

							Player player = players.get(turn);

							game.eatPiece(player, oldPosition, newPosition);

							turn = (turn + 1) % 2;
							System.out.println("Successful eating !");
						} catch (Exception e) {
							System.out.println("��׽�쳣������������");
							continue;
						}
					}
					break;

				case "5":
					System.out.println("���������ѯ���꣺");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�

					if (items.length != 2) {
						System.out.println("��������밴�����������룺");
					} else {
						try {
							int x1 = Integer.valueOf(items[0]);
							int y1 = Integer.valueOf(items[1]);

							Position position = new Position(x1, y1);

							Piece piece = game.getOccupationOfPosition(position);
							if (piece == null || piece.getPieceState() != 1) {
								System.out.println("��λ�ÿ���");
							} else {
								if (players.get(0).judgeOwnPiece(piece)) {
									System.out.println("������:" + players.get(0).getPlayerName());
								} else {
									System.out.println("������:" + players.get(1).getPlayerName());
								}
								System.out.println("����:" + piece.getPieceName());
							}
							System.out.println("��ѯ�ɹ��������ѡ��ִ�У�");
						} catch (Exception e) {
							System.out.println("��׽�쳣������������");
							continue;
						}
					}
					continue;

				case "6":
					System.out.println("�������£�");
					game.printBoard();
					System.out.println("�����ѡ��ִ�У�");
					continue;

				case "7":
					System.out.printf("���%s����������Ϊ%d\n", players.get(0).getPlayerName(),
							players.get(0).countQuantityOfPieceInBoard());
					System.out.printf("���%s����������Ϊ%d\n", players.get(1).getPlayerName(),
							players.get(1).countQuantityOfPieceInBoard());
					System.out.println("��ѯ�ɹ��������ѡ��ִ�У�");
					continue;

//				case "8":  //�鿴�����ʷ
//					Player player1 = players.get(0);
//					Player player2 = players.get(1);
//					System.out.println(player1.getPlayerName() + "������ʷ���£�");
//					System.out.println(player1.getHistory());
//					System.out.println(player2.getPlayerName() + "������ʷ���£�");
//					System.out.println(player2.getHistory());
//					System.out.println("��ѯ�ɹ��������ѡ��ִ�У�");
//					continue;

				case "8":
					System.out.println("������");
					turn = (turn + 1) % 2;
					break;

				case "9":
					System.out.println("--------Game over!--------");
					Player player1 = players.get(0);
					Player player2 = players.get(1);
					System.out.println(player1.getPlayerName() + "������ʷ���£�");
					System.out.println(player1.getHistory());
					System.out.println(player2.getPlayerName() + "������ʷ���£�");
					System.out.println(player2.getHistory());
					flag = true;
					break;

				default:
					System.out.println("����ѡ��������������룡");
					break;
				}
				if (flag) { // ѡ��10���˳�ѭ��
					break;
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}finally {
			reader.close();
		}
		
	}

	public static void main(String[] args) throws Exception {
		MyChessAndGoGame newGame = new MyChessAndGoGame();
		newGame.myMain();
	}

}
