package applications;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

import centralObject.CentralUser;
import centralObject.Nucleus;
import centralObject.Stellar;
import circularOrbit.AtomStructure;
import circularOrbit.CircularOrbit;
import circularOrbit.SocialNetworkCircle;
import circularOrbit.StellarSystem;
import legality.Legal_SocialNetworkCircle;
import legality.Legal_StellarSystem;
import physicalObject.Electron;
import physicalObject.Friend;
import physicalObject.Planet;
import relation.EE_IntimacyMap;
import track.Track;
import APIS.*;

public class MyOrbitScenes {

	BufferedReader reader = null;

	public static void main(String[] args) {
		MyOrbitScenes newOrbit = new MyOrbitScenes();
		try {
			newOrbit.myMain();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void myMain() throws Exception {
//		BufferedReader reader = null;

		try {
			reader = new BufferedReader(new InputStreamReader(System.in));
			boolean flag = true;

			while (flag) {
				mainMenu();
				String choice = reader.readLine();
				switch (choice) {
				case "1":
					simulateAtomStrcture();
					flag = false;
					break;

				case "2":
					simulateStellarSystem();
					flag = false;
					break;

				case "3":
					simulateSocialNetwork();
					flag = false;
					break;

				default:
					System.out.println("����ѡ��������������룡");
				}

			}
			System.out.println("ģ�������");

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			reader.close();
		}
	}

	public void simulateAtomStrcture() {
		CircularOrbit<Nucleus, Electron> ast = new AtomStructure();
		String fileName = "txt/AtomicStructure.txt";
		File file = new File(fileName);
		ast.readFile(file);
		System.out.println("�Ѷ�ȡ�ļ�������ԭ�ӽṹģ�ͣ�");
		String line;
		String[] items;

		boolean flag = false;

		try {
			while (true) {
				menuAtomStrcture();
				String choice = reader.readLine();
				switch (choice) {
				case "1":
					CircularOrbitHelper2.visualizes(ast);

					break;
				case "2":
					System.out.println("��������Ҫ��ӵĹ���뾶");
					line = reader.readLine();
					Track t1 = new Track(Double.parseDouble(line));
					ast.addTrack(t1);
					System.out.println("�ѳɹ���Ӹù��");
					break;

				case "3":
					System.out.println("������ù������");
					line = reader.readLine();
					Track t2 = ast.getTracks().get(Integer.parseInt(line) - 1);
					Electron e = new Electron("electron");
					ast.addTrackObject(t2, e);
					System.out.println("�ѳɹ�Ϊ�ù����ӵ���");
					break;

				case "4":
					System.out.println("��������Ҫɾ���Ĺ������");
					line = reader.readLine();
					Track t3 = ast.getTracks().get(Integer.parseInt(line) - 1);
					ast.removeTrack(t3);
					System.out.println("�ѳɹ�ɾ���ù��");
					break;

				case "5":
					System.out.println("������ù������");
					line = reader.readLine();
					Track t4 = ast.getTracks().get(Integer.parseInt(line) - 1);

					ArrayList<Electron> list = ast.getTrackObject(t4);
					if (list.size() != 0) {
						list.remove(0);
						System.out.println("�ѳɹ��Ӹù��ɾ������");
					} else {
						System.out.println("�ù��Ϊ�գ�");
					}
					break;

				case "6":
					CircularOrbitAPIS<Nucleus, Electron> c1 = new CircularOrbitAPIS<Nucleus, Electron>();
					double entropy = c1.getObjectDistributionEntropy(ast);
					System.out.printf("��ԭ�ӽṹģ�͸��������ֲ�����ֵΪ %f\n", entropy);
					break;

				case "7":
					System.out.println("��ֱ�����ԭ�����Ŀ����������");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�
					int layer1 = Integer.valueOf(items[0]);
					int layer2 = Integer.valueOf(items[1]);

					Track t5 = ast.getTracks().get(layer1 - 1);
					ArrayList<Electron> list1 = ast.getTrackObject(t5);
					if (list1.size() != 0) {
						list1.remove(0);
					} else {
						System.out.println("ԭ�ù��Ϊ�գ�����������");
						break;
					}

					Track t6 = ast.getTracks().get(layer2 - 1);
					Electron e2 = new Electron("electron");
					ast.addTrackObject(t6, e2);
					System.out.println("�ѳɹ�ʵ�ֵ���ԾǨ��");

					break;

				case "8":
					AtomStructure a2 = new AtomStructure();
					String fileName2 = "txt/AtomicStructure2.txt";
					File file2 = new File(fileName2);
					a2.readFile(file2);
					
					CircularOrbitAPIS<Nucleus, Electron> c = new CircularOrbitAPIS<Nucleus, Electron>();
					c.getDifference(ast, a2);
					
					break;
					
				case "9":
					flag = true;
					break;

				default:
					System.out.println("����ѡ��������������룡");
					break;
				}
				if (flag) {
					break;
				}

			}

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void simulateStellarSystem() {
		CircularOrbit<Stellar, Planet> ste = new StellarSystem();
		String fileName = "txt/StellarSystem.txt";
		File file = new File(fileName);
		ste.readFile(file);
		System.out.println("�Ѷ�ȡ�ļ������������˶�ģ�ͣ�");
		Legal_StellarSystem myJudge = new Legal_StellarSystem();
		if(myJudge.judgeLegality(ste) == 0) {
			System.out.println("�����쳣��");
		}
		String line;
		String[] items;

		boolean flag = false;

		try {
			while (true) {
				menuStellarSystem();
				String choice = reader.readLine();
				switch (choice) {
				case "1":
					DrawMovingOrbit.visualizes(ste);

					break;
				case "2":
					System.out.println("��������Ҫ��ӵĹ���뾶");
					line = reader.readLine();
					Track t1 = new Track(translateData(line));
					ste.addTrack(t1);
					System.out.println("�ѳɹ���Ӹù��");
					break;

				case "3":
					System.out.println("������ù���뾶");
					line = reader.readLine();
					Track t2 = ste.findTrack(translateData(line));
					System.out.println("����������<����,��̬,��ɫ,���ǰ뾶,����뾶,��ת,�ٶ�,��ת����,��ʼλ�õĽǶ�>");

					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�

					Planet planet = new Planet(items[0], items[1], items[2], translateData(items[3]),
							translateData(items[4]), translateData(items[5]), items[6], translateData(items[7]));
					ste.addTrackObject(t2, planet);
					System.out.println("�ѳɹ�Ϊ�ù���������");
					break;

				case "4":
					System.out.println("��������Ҫɾ���Ĺ���뾶");
					line = reader.readLine();
					Track t3 = ste.findTrack(translateData(line));
					ste.removeTrack(t3);
					System.out.println("�ѳɹ�ɾ���ù��");
					break;

				case "5":
					System.out.println("������ù���뾶");
					line = reader.readLine();
					Track t4 = ste.findTrack(translateData(line));
					ArrayList<Planet> list = ste.getTrackObject(t4);

					System.out.println("������ɾ����������");
					String planetName = reader.readLine();

					int i;
					for (i = 0; i < list.size(); i++) {
						if (list.get(i).getName().equals(planetName)) {
							break;
						}
					}

					if (i < list.size()) {
						list.remove(i);
						System.out.println("�ѳɹ��ӹ��ɾ��������");
					} else {
						System.out.println("δ�ҵ������ǣ�");
					}
					break;

				case "6":
					CircularOrbitAPIS<Stellar, Planet> c2 = new CircularOrbitAPIS<Stellar, Planet>();
					double entropy = c2.getObjectDistributionEntropy(ste);
					System.out.printf("��ԭ�ӽṹģ�͸��������ֲ�����ֵΪ %f\n", entropy);
					break;

				case "7":
					System.out.println("�����뾭��������");
					String timeStr = reader.readLine();

					double time = Double.parseDouble(timeStr); // ����ʱ��(����)
					double cycle; // ����
					double turns; // Ȧ��
					double sitha; // �Ƕ�

					ArrayList<ArrayList<Planet>> T2E = ste.getT2E();
					for (int m = 0; m < T2E.size(); m++) {
						ArrayList<Planet> planetList = T2E.get(m);
						for (Planet p : planetList) {
							cycle = 2 * Math.PI * p.getTrackRadius() / p.getSpeed(); // ��
							cycle = cycle / (3600 * 24); // ��
							turns = time / cycle;

							if (p.getOrientation().equals("CCW")) { // ��ʱ���������
								sitha = (p.getSitha() + turns * 360) % 360;
							} else {
								sitha = (p.getSitha() - turns * 360) % 360;
								if (sitha < 0) {
									sitha += 360;
								}
							}
							System.out.printf("%f���%s�Ĺ���뾶Ϊ%f���Ƕ�Ϊ%f\n", time, p.getName(), p.getTrackRadius(), sitha);
						}

					}
					break;

				case "8":
					System.out.println("���������ǵ�����");
					String pName = reader.readLine();
					ArrayList<ArrayList<Planet>> T2E1 = ste.getT2E(); // �������ڹ��
					int a, b;
					for (a = 0; a < T2E1.size(); a++) {
						ArrayList<Planet> pList = T2E1.get(a);
						for (b = 0; b < pList.size(); b++) {
							if (pList.get(b).getName().equals(pName)) {
								System.out.printf("%s����ǵľ���Ϊ%fkm\n", pName, pList.get(b).getTrackRadius());
							}
						}
					}
					break;

				case "9":
					System.out.println("������ֱ������������ǵ�����");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�
					Planet p1 = null, p2 = null;

					ArrayList<ArrayList<Planet>> T2E2 = ste.getT2E(); // �������ڹ��
					for (a = 0; a < T2E2.size(); a++) {
						ArrayList<Planet> planetList = T2E2.get(a);
						for (b = 0; b < planetList.size(); b++) {
							if (planetList.get(b).getName().equals(items[0])) {
								p1 = planetList.get(b);
							}
							if (planetList.get(b).getName().equals(items[1])) {
								p2 = planetList.get(b);
							}
						}
					}

					CircularOrbitAPIS<Stellar, Planet> c3 = new CircularOrbitAPIS<Stellar, Planet>();
					double distance = c3.getPhysicalDistance(ste, p1, p2);
					System.out.printf("%s��%s֮����������Ϊ%fkm\n", items[0], items[1], distance);
					break;

				case "10":
					CircularOrbit<Stellar, Planet> ste2 = new StellarSystem();
					String fileName2 = "txt/StellarSystem2.txt";
					File file2 = new File(fileName2);
					ste2.readFile(file2);
					
					CircularOrbitAPIS<Stellar, Planet> c = new CircularOrbitAPIS<Stellar, Planet>();
					c.getDifference(ste, ste2);
					break;
					
				case "11":
					flag = true;
					break;
					
				default:
					System.out.println("����ѡ��������������룡");
					break;
				}
				if (flag) {
					break;
				}

			}

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void simulateSocialNetwork() {
		CircularOrbit<CentralUser, Friend> soc = new SocialNetworkCircle();
		String fileName = "txt/SocialNetworkCircle.txt";
		File file = new File(fileName);
		soc.readFile(file);
		System.out.println("�Ѷ�ȡ�ļ��������罻����ģ�ͣ�");
		Legal_SocialNetworkCircle myJudge = new Legal_SocialNetworkCircle();
		if(myJudge.judgeLegality(soc) == 0) {
			System.out.println("�����쳣��");
		}
		String line;
		String[] items;

		boolean flag = false;

		try {
			while (true) {
				menuSocialNetwork();
				String choice = reader.readLine();
				switch (choice) {
				case "1":
					CircularOrbitHelper.visualizes(soc);

					break;
				case "2":

					Track t2 = new Track(1);
					soc.addTrack(t2);
					System.out.println("���һ���չ��");
					break;

				case "3":
					System.out.println("�������û������������䣬�Ա�");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�
					Friend f1 = new Friend(items[0], Integer.parseInt(items[1]), items[2]);
					System.out.println("��������û��������û�SocialTie");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�
					soc.addCenterTrackObjectsRelation(soc.getCentralObject(), f1, Float.parseFloat(items[2]));
					ArrayList<ArrayList<Friend>> T2E = soc.getT2E();
					T2E.get(0).add(f1);
					System.out.println("��������û��������û�SocialTie");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�
					Friend f2 = new Friend("", 1, "F");
					for (int i = 0; i < T2E.size(); i++) {
						for (Friend f : T2E.get(i)) {
							if (f.getName().equals(items[1])) {
								f2 = f;
								break;
							}
						}
					}
					soc.addTrackObjectsRelation(f1, f2, Float.parseFloat(items[2]));
					break;

				case "4":
					System.out.println("��������Ҫɾ���Ĺ������");
					line = reader.readLine();
					Track t3 = soc.getTracks().get(Integer.parseInt(line) - 1);
					soc.removeTrack(t3);
					System.out.println("�ѳɹ�ɾ���ù��");
					break;

				case "5":
					System.out.println("������ɾ�����û���");
					String friendName = reader.readLine();

					Friend f3 = new Friend("", 1, "F");
					ArrayList<ArrayList<Friend>> T2E3 = soc.getT2E();
					int i, j = 0;
					for (i = 0; i < T2E3.size(); i++) {
						for (Friend f : T2E3.get(i)) {
							if (f.getName().equals(friendName)) {
								f3 = f;
								j = i;
								break;
							}
						}
					}

					T2E3.get(j).remove(f3);
					break;

				case "6":
					CircularOrbitAPIS<CentralUser, Friend> c3 = new CircularOrbitAPIS<CentralUser, Friend>();
					double entropy = c3.getObjectDistributionEntropy(soc);
					System.out.printf("���罻����ģ�͸��������ֲ�����ֵΪ %f\n", entropy);
					break;

				case "7":
					ArrayList<ArrayList<Friend>> T2E4 = soc.getT2E();
					for (int ii = 0; ii < T2E4.size(); ii++) {
						System.out.println("���" + (ii + 1) + "���û���");
						for (Friend f : T2E4.get(ii)) {
							System.out.println(f.getName());
						}
					}
					break;

				case "8":
					ArrayList<ArrayList<Friend>> T2E5 = soc.getT2E();
					System.out.println("���1�ĺ������£�");
					for (Friend f : T2E5.get(0)) {
						System.out.println(f.getName());
					}
					System.out.println("��ѡ����ѵ�����");
					String friendName1 = reader.readLine();

					Friend f4 = new Friend("", 1, "F");
					ArrayList<ArrayList<Friend>> T2E6 = soc.getT2E();
					int i1;
					for (i1 = 0; i1 < T2E6.size(); i1++) {
						for (Friend f : T2E6.get(i1)) {
							if (f.getName().equals(friendName1)) {
								f4 = f;
								break;
							}
						}
					}

					EE_IntimacyMap<Friend> E2E = soc.getE2E();

					int counter = E2E.getNumOfClosers(f4, 0.5);
					System.out.printf("%s����Ϣ��ɢ��Ϊ%d\n", friendName1, counter);
					break;

				case "9":
					System.out.println("��������Ҫ��ӵ�SocialTie");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�
					String name1 = items[0];
					String name2 = items[1];
					String intimacy = items[2];

					ArrayList<ArrayList<Friend>> T2E7 = soc.getT2E();
					Friend f10 = new Friend("", 1, "F");
					Friend f20 = new Friend("", 1, "F");

					if (name1.equals(soc.getCentralObject().getName())) {
						for (int q = 0; q < T2E7.size(); q++) {
							for (Friend f : T2E7.get(q)) {
								if (f.getName().equals(name2)) {
									f10 = f;
								}
							}
						}
						for(ArrayList<Friend> list : soc.getT2E()) { //��ԭ���ɾ��
							for(Friend friend : list)
								if(friend.equals(f10)) {
									list.remove(f10);
									break;
								}
						}
	
						soc.addCenterTrackObjectsRelation(soc.getCentralObject(), f10, Float.parseFloat(intimacy));
					}
					else if (name2.equals(soc.getCentralObject().getName())) {
						for (int q = 0; q < T2E7.size(); q++) {
							for (Friend f : T2E7.get(q)) {
								if (f.getName().equals(name1)) {
									f10 = f;
								}
							}
						}
						for(ArrayList<Friend> list : soc.getT2E()) { //��ԭ���ɾ��
							for(Friend friend : list)
								if(friend.equals(f10)) {
									list.remove(f10);
									break;
								}
						}
						
						soc.addCenterTrackObjectsRelation(soc.getCentralObject(), f10, Float.parseFloat(intimacy));
					}

					else {
						for (int q = 0; q < T2E7.size(); q++) {
							for (Friend f : T2E7.get(q)) {
								if (f.getName().equals(name1)) {
									f10 = f;
								}
								if (f.getName().equals(name2)) {
									f20 = f;
								}
							}
						}
						soc.addTrackObjectsRelation(f10, f20, Float.parseFloat(intimacy));
						
					}
					Set<Friend> friendSet = new HashSet<Friend>();
					for(ArrayList<Friend> list : soc.getT2E()) { //��ԭ���ɾ��
						for(Friend friend : list) {
							friendSet.add(friend);
						}
							
					}
					soc.getTracks().clear();   //��������Ϊ�����½�����
					soc.getT2E().clear();
					
					BuildRelation b = new BuildRelation();
					b.buildRelation(soc, friendSet);
					
					
					break;

		
				case "10":
					System.out.println("��������Ҫɾ���������ϵ");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�
					String n1 = items[0];
					String n2 = items[1];

					ArrayList<ArrayList<Friend>> T2E8 = soc.getT2E();
					Friend ff = new Friend("", 1, "F");
					Friend fr = new Friend("", 1, "F");

					if (n1.equals(soc.getCentralObject().getName())) {
						for (int q = 0; q < T2E8.size(); q++) {
							for (Friend f : T2E8.get(q)) {
								if (f.getName().equals(n2)) {
									ff = f;
								}
							}
						}

						soc.removeCenterTrackObjectsRelation(soc.getCentralObject(), ff);
					}
					else if (n2.equals(soc.getCentralObject().getName())) {
						for (int q = 0; q < T2E8.size(); q++) {
							for (Friend f : T2E8.get(q)) {
								if (f.getName().equals(n1)) {
									ff = f;
								}
							}
						}
						soc.removeCenterTrackObjectsRelation(soc.getCentralObject(), ff);
					}

					else {
						for (int q = 0; q < T2E8.size(); q++) {
							for (Friend f : T2E8.get(q)) {
								if (f.getName().equals(n1)) {
									ff = f;
								}
								if (f.getName().equals(n2)) {
									fr = f;
								}
							}
						}
						soc.removeTrackObjectsRelation(ff, fr);
					}

					Set<Friend> friendSet1 = new HashSet<Friend>();
					for(ArrayList<Friend> list : soc.getT2E()) { //��ԭ���ɾ��
						for(Friend friend : list) {
							friendSet1.add(friend);
						}
							
					}
					soc.getTracks().clear();   //��������Ϊ�����½�����
					soc.getT2E().clear();
					
					BuildRelation b1 = new BuildRelation();
					b1.buildRelation(soc, friendSet1);
					
					break;
					
				case "11":
					System.out.println("������ֱ����������û�������");
					line = reader.readLine();
					items = line.split("\\s"); // �ֿ��հ��ַ�
					Friend fr1 = null , fr2 = null;

					ArrayList<ArrayList<Friend>> T2E10 = soc.getT2E(); // �������ڹ��
					for (int a = 0; a < T2E10.size(); a++) {
						ArrayList<Friend> friendList = T2E10.get(a);
						for (int bb = 0; bb < friendList.size(); bb++) {
							if (friendList.get(bb).getName().equals(items[0])) {
								fr1 = friendList.get(bb);
							}
							if (friendList.get(bb).getName().equals(items[1])) {
								fr2 = friendList.get(bb);
							}
						}
					}

					CircularOrbitAPIS<CentralUser , Friend> c4 = new CircularOrbitAPIS<CentralUser , Friend>();
					int logicalDistance = c4.getLogicalDistance(soc, fr1, fr2);
					System.out.printf("�û�%s���û�%s֮����߼�����Ϊ%d\n", items[0], items[1], logicalDistance);
					break;
					
				case "12":	
					CircularOrbit<CentralUser, Friend> soc2 = new SocialNetworkCircle();
					String fileName2 = "txt/SocialNetworkCircle2.txt";
					File file2 = new File(fileName2);
					soc2.readFile(file2);
					
					CircularOrbitAPIS<CentralUser, Friend> c = new CircularOrbitAPIS<CentralUser, Friend>();
					c.getDifference(soc, soc2);
					break;
					
				case "13":
					flag = true;
					break;

				default:
					System.out.println("����ѡ��������������룡");
					break;
				}
				if (flag) {
					break;
				}
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	/** Print menu for selection */
	public void mainMenu() {
		System.out.println("������µľ���Ӧ����ѡ��һ�");
		System.out.println("1.AtmoStrcture");
		System.out.println("2.StellarSystem");
		System.out.println("3.SocialNetwork");
	}

	/** Print menu for AtmoStrcture */
	public void menuAtomStrcture() {
		System.out.println("������µľ��幦����ѡ��һ�");
		System.out.println("1.��GUI�Ͽ��ӻ�չʾԭ�ӽṹģ��");
		System.out.println("2.���ӹ��");
		System.out.println("3.���ض���������ӵ���");
		System.out.println("4.ɾ�����");
		System.out.println("5.���ض����ɾ������");
		System.out.println("6.����ԭ�ӽṹģ�͸��������ֲ�����ֵ");
		System.out.println("7.ģ�����ԾǨ");
		System.out.println("8.�Ƚ�����ԭ�ӽṹģ�͵Ĳ�ͬ");
		System.out.println("9.end");
	}

	/** Print menu for StellarSystem */
	public void menuStellarSystem() {
		System.out.println("������µľ��幦����ѡ��һ�");
		System.out.println("1.���ӻ�ģ�������˶�");
		System.out.println("2.���ӹ��");
		System.out.println("3.���ض��������������");
		System.out.println("4.ɾ�����");
		System.out.println("5.���ض����ɾ������");
		System.out.println("6.���������˶�ģ�͸��������ֲ�����ֵ");
		System.out.println("7.չʾ�ض�ʱ�����ǵ�λ��");
		System.out.println("8.���������ĳ���ǵ��������");
		System.out.println("9.�����������ǵ��������");
		System.out.println("10.�Ƚ����������˶�ģ�͵Ĳ�ͬ");
		System.out.println("11.end");
	}

	/** Print menu for AtmoStrcture */
	public void menuSocialNetwork() {
		System.out.println("������µľ��幦����ѡ��һ�");
		System.out.println("1.��GUI�Ͽ��ӻ�չʾ�罻����ģ��");
		System.out.println("2.���ӹ��");
		System.out.println("3.���ض�����������û�");
		System.out.println("4.ɾ�����");
		System.out.println("5.���ض����ɾ���û�");
		System.out.println("6.�����罻����ģ�͸��������ֲ�����ֵ");
		System.out.println("7.�ж�ÿ���û����ĸ�����ϵ�");
		System.out.println("8.����ĳ�����ڵ�һ������Ϻ��ѵ�\"��Ϣ��ɢ��\"");
		System.out.println("9.����һ���罻��ϵ");
		System.out.println("10.ɾ��һ���罻��ϵ");
		System.out.println("11.��������������û�֮����߼�����");
		System.out.println("12.�Ƚ������罻����ģ�͵Ĳ�ͬ");
		System.out.println("13.end");
	}

	/**
	 * Translate a data from string type to double
	 * Numbers greater than 10,000 according to scientific notation
	 * and Numbers less than 10000 are given directly
	 * @param s label of the number string
	 * @return double type of the number
	 */
	public double translateData(String s) {
		String[] str = s.split("e");
		if (str.length == 1) {
			return Double.parseDouble(s);
		} else {
			double a = Double.parseDouble(str[0]);
			int b = Integer.parseInt(str[1]);

			double ret = a * Math.pow(10, b);

			return ret;
		}
	}
}
