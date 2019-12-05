package APIS;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

import circularOrbit.CircularOrbit;
import physicalObject.Friend;
import physicalObject.Planet;
import relation.EE_IntimacyMap;

public class CircularOrbitAPIS<L, E> {

	// Abstraction function:
	//  represent a series of common calculations can be performed on it
    //  Based on the specific multi-track structure 
	//  constructed by the three applications selected
	
	/**
	 * Calculating the entropy of the distribution of objects on each orbit in a
	 * multi-track system
	 * 
	 * @param c label of a multi-track system
	 * @return entropy of the system
	 */
	@SuppressWarnings("rawtypes")
	public double getObjectDistributionEntropy(CircularOrbit c) {

		@SuppressWarnings("unchecked")
		ArrayList<ArrayList<E>> T2E = c.getT2E(); // ����ϵ�����

		double entropy = 0; // ��ֵ
		double sum = 0; // �����������
		double p = 0;

		for (int i = 0; i < T2E.size(); i++) {
			sum += T2E.get(i).size();   //��������������
		}
		
		for (int i = 0; i < T2E.size(); i++) {
			p = T2E.get(i).size() / sum;
			entropy -= p * Math.log(p);
		}

		return entropy;
	}

	/**
	 * Get logical distance of two objects in the orbit system
	 * @param c label of specific track type
	 * @param e1 label of one object
	 * @param e2 label of another object
	 * @return int value of logical distance
	 */
	@SuppressWarnings("rawtypes")
	public int getLogicalDistance(CircularOrbit c, E e1, E e2) {

		@SuppressWarnings("unchecked")
		EE_IntimacyMap<E> E2E = c.getE2E();

		E now = e1, friend = e1;
		int i = 0, distance = 0;
		Queue<E> queue = new LinkedList<E>();
		ArrayList<E> visited = new ArrayList<E>();
		if (e1 == e2) {
			return distance;
		}
		queue.add(now);
		visited.add(now);
		while (!queue.isEmpty()) {
			now = queue.poll();
			distance++;
			while (i < E2E.getAdjacentObjects(now).size()) {
				friend = E2E.getAdjacentObjects(now).get(i);
				if (friend == e2) { // �ҵ��˼����ص�ǰ�ľ���
					return distance;
				}
				if (!visited.contains(friend)) {
					queue.add(friend);
					visited.add(friend);
				}
				i++;
			}
			i = 0;
		}
		return -1; // �Ҳ���˵��P1��P2û��ϵ

	}

	/**
	 * Get physical distance of two objects in the orbit system
	 * Method only for the stellar system
	 * @param c label of specific track type
	 * @param e1 label of one object
	 * @param e2 label of another object
	 * @return double value of logical distance
	 */
	@SuppressWarnings("rawtypes")
	public double getPhysicalDistance(CircularOrbit c, E e1, E e2) {

		Planet p1 = (Planet) e1;
		Planet p2 = (Planet) e2;

		double sitha1 = p1.getSitha();
		double sitha2 = p2.getSitha();

		double x1 = p1.getTrackRadius() * Math.sin(sitha1);
		double y1 = p1.getTrackRadius() * Math.cos(sitha1);
		double x2 = p2.getTrackRadius() * Math.sin(sitha2);
		double y2 = p2.getTrackRadius() * Math.cos(sitha2);

		double distance = Math.sqrt(Math.abs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));

		return distance;
	}

	/**Get the difference between two orbit system of the same type
	 * @param c1 label of one system
	 * @param c2 label of another system
	 * @return Differce label of two orbits' difference
	 */
	@SuppressWarnings("rawtypes")
	public Difference getDifference(CircularOrbit c1, CircularOrbit c2) {
		int tracksNumDifference; // �����Ŀ����
		ArrayList<Integer> specificTracksNumDifference = new ArrayList<Integer>(); // �ض������Ŀ����
		ArrayList<String> objectsDifference = new ArrayList<String>(); // ���������

		int diff, i;
		Difference d;

		@SuppressWarnings("unchecked")
		ArrayList<ArrayList<E>> T2E1 = c1.getT2E(); // ���1�ϵ�����
		@SuppressWarnings("unchecked")
		ArrayList<ArrayList<E>> T2E2 = c2.getT2E(); // ���2�ϵ�����

		if (c1.getSystemName() != c2.getSystemName()) {
			System.out.println("���󣡱���Ƚ�ͬ���͵Ĺ����");
		}

		if (c1.getSystemName() == "AtomStructure") {
			tracksNumDifference = T2E1.size() - T2E2.size();
			if (tracksNumDifference >= 0) { // ǰһ�����������
				for (i = 0; i < T2E2.size(); i++) {
					diff = T2E1.get(i).size() - T2E2.get(i).size();
					specificTracksNumDifference.add(diff);
				}
				for (i = T2E2.size(); i < T2E1.size(); i++) {
					diff = T2E1.get(i).size();
					specificTracksNumDifference.add(diff);
				}
			} else { // ��һ�����������
				for (i = 0; i < T2E1.size(); i++) {
					diff = T2E1.get(i).size() - T2E2.get(i).size();
					specificTracksNumDifference.add(diff);
				}
				for (i = T2E1.size(); i < T2E2.size(); i++) {
					diff = 0 - T2E2.get(i).size();
					specificTracksNumDifference.add(diff);
				}
			}

			d = new Difference(tracksNumDifference, specificTracksNumDifference, null);
			System.out.println("AtomStructure");
			d.printAtomStructrueDifference();

		}
		else if (c1.getSystemName() == "StellarSystem") {
			tracksNumDifference = T2E1.size() - T2E2.size();
			if (tracksNumDifference >= 0) { // ǰһ�����������
				String s = "";
				for (i = 0; i < T2E2.size(); i++) {
					diff = T2E1.get(i).size() - T2E2.get(i).size();
					specificTracksNumDifference.add(diff);
					Planet p1 = (Planet) (T2E1.get(i).get(0));
					Planet p2 = (Planet) (T2E1.get(i).get(0));
					if (p1.getName() == p2.getName()) {
						s = "��";
					} else {
						s = p1.getName() + "-" + p2.getName();
					}
					objectsDifference.add(s);
				}
				for (i = T2E2.size(); i < T2E1.size(); i++) {
					diff = T2E1.get(i).size();
					specificTracksNumDifference.add(diff);

					Planet p1 = (Planet) (T2E1.get(i).get(0));
					s = p1.getName() + "-��";

					objectsDifference.add(s);

				}
			} else { // ��һ�����������
				String s = "";
				for (i = 0; i < T2E1.size(); i++) {
					diff = T2E1.get(i).size() - T2E2.get(i).size();
					specificTracksNumDifference.add(diff);

					if (diff == 0) {
						s = "��";
					} else {
						Planet p1 = (Planet) (T2E1.get(i).get(0));
						Planet p2 = (Planet) (T2E1.get(i).get(0));

						s = p1.getName() + "-" + p2.getName();
					}
					objectsDifference.add(s);
					s = "";
				}
				for (i = T2E1.size(); i < T2E2.size(); i++) {
					diff = 0 - T2E2.get(i).size();
					specificTracksNumDifference.add(diff);

					Planet p2 = (Planet) (T2E2.get(i).get(0));
					s = "��-" + p2.getName();

					objectsDifference.add(s);
					s = "";
				}
			}
			d = new Difference(tracksNumDifference, specificTracksNumDifference, objectsDifference);
			System.out.println("StellarSystem");
			d.printOtherDifference();
		}

		else{   //"SocialNetworkCircle"
			tracksNumDifference = T2E1.size() - T2E2.size();
			if (tracksNumDifference >= 0) { // ǰһ�����������
				String s = "";
				String s1 = "";
				String s2 = "";
				for (i = 0; i < T2E1.size(); i++) {
					diff = T2E1.get(i).size() - T2E2.get(i).size();
					specificTracksNumDifference.add(diff);
					boolean flag1 = true;
					boolean flag2 = true;

					for (int j = 0; j < T2E1.get(i).size(); j++) { // �ҹ��2��û�еĹ��1����
						Friend p1 = (Friend) (T2E1.get(i).get(j));
						for (int k = 0; k < T2E2.get(i).size(); k++) {
							Friend p2 = (Friend) (T2E2.get(i).get(k));
							if (p1.getName().equals(p2.getName())) {
								flag1 = false;
								break; // �ڹ��2�ҵ���������ȵ����壬ֱ���˳�
							}
						}
						if (flag1) {
							s1 = s1.concat(p1.getName() + " ");
						}
						flag1 = true;
					}

					for (int j = 0; j < T2E2.get(i).size(); j++) { // �ҹ��1��û�еĹ��2����
						Friend p2 = (Friend) (T2E2.get(i).get(j));
						for (int k = 0; k < T2E1.get(i).size(); k++) {
							Friend p1 = (Friend) (T2E1.get(i).get(k));
							if (p1.getName().equals(p2.getName())) {
								flag2 = false;
								break; // �ڹ��2�ҵ���������ȵ����壬ֱ���˳�
							}
						}
						if (flag2) {
							s2 = s2.concat(p2.getName() + " ");
						}
						flag2 = true;
					}

					s = "{" + s1 + "}-{" + s2 + "}";
					objectsDifference.add(s);
					s = "";
					s1 = "";
					s2 = "";
				}

				for (i = T2E2.size(); i < T2E1.size(); i++) {
					diff = T2E1.get(i).size();
					specificTracksNumDifference.add(diff);

					for (int k = 0; k < T2E1.get(i).size(); k++) {
						Friend p1 = (Friend) (T2E2.get(i).get(k));
						s1 = s1.concat(p1.getName() + " ");

					}
					s = "{" + s1 + "}-��";

					objectsDifference.add(s);
					s = "";
					s1 = "";

				}

			} else { // ��һ�����������
				String s = "";
				String s1 = "";
				String s2 = "";
				for (i = 0; i < T2E1.size(); i++) {
					diff = T2E1.get(i).size() - T2E2.get(i).size();
					specificTracksNumDifference.add(diff);
					boolean flag1 = true;
					boolean flag2 = true;

					for (int j = 0; j < T2E1.get(i).size(); j++) { // �ҹ��2��û�еĹ��1����
						Friend p1 = (Friend) (T2E1.get(i).get(j));
						for (int k = 0; k < T2E2.get(i).size(); k++) {
							Friend p2 = (Friend) (T2E1.get(i).get(k));
							if (p1.getName() == p2.getName()) {
								flag1 = false;
								break; // �ڹ��2�ҵ���������ȵ����壬ֱ���˳�
							}
						}
						if (flag1) {
							s1 = s1.concat(p1.getName() + " ");
						}
						flag1 = true;
					}

					for (int j = 0; j < T2E1.get(i).size(); j++) { // �ҹ��1��û�еĹ��2����
						Friend p2 = (Friend) (T2E2.get(i).get(j));
						for (int k = 0; k < T2E1.get(i).size(); k++) {
							Friend p1 = (Friend) (T2E2.get(i).get(k));
							if (p1.getName() == p2.getName()) {
								flag2 = false;
								break; // �ڹ��2�ҵ���������ȵ����壬ֱ���˳�
							}
						}
						if (flag2) {
							s2 = s2.concat(p2.getName() + " ");
						}
						flag2 = true;
					}

					s = "{" + s1 + "}-{" + s2 + "}";
					objectsDifference.add(s);
					s = "";
					s1 = "";
					s2 = "";
				}

				for (i = T2E2.size(); i < T2E1.size(); i++) {
					diff = T2E1.get(i).size();
					specificTracksNumDifference.add(diff);

					for (int k = 0; k < T2E1.get(i).size(); k++) {
						Friend p1 = (Friend) (T2E2.get(i).get(k));
						s1 = s1.concat(p1.getName() + " ");

					}
					s = "{" + s1 + "}-��";

					objectsDifference.add(s);
					s = "";
					s1 = "";

				}
			}
			d = new Difference(tracksNumDifference, specificTracksNumDifference, objectsDifference);
			System.out.println("SocialNetworkCircle");
			d.printOtherDifference();
		}
		return d;
	}
}
