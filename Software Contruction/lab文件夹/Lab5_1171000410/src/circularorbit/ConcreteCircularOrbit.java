package circularorbit;

import java.util.ArrayList;
import java.util.List;

import fileoutput.WriteStrategy;
import relation.EeIntimacyMap;
import relation.LeIntimacyMap;
import track.Track;

public class ConcreteCircularOrbit<L, E> implements CircularOrbit<L, E> {

	private L centralObj; // ��������
	private List<Track> tracks = new ArrayList<Track>(); // ���
	private ArrayList<ArrayList<E>> t2e = new ArrayList<ArrayList<E>>(); // �������ڹ��
	private LeIntimacyMap<L, E> l2e = new LeIntimacyMap<L, E>(); // ����ӳ��������
	private EeIntimacyMap<E> e2e = new EeIntimacyMap<E>(); // ���������ӳ��
	private ArrayList<String> exceptionsList = new ArrayList<String>(); // �洢�쳣�ļ���

	// Abstraction function:
	// represents a multi-track system where objects are in orbit
	// central objects and orbital objects are mapped
	// and there is a mapping between orbital objects.
	// Representation invariant:
	// centralObj is the central object of the system if it isn't null
	// tracks is the list of tracks
	// E2E is mapping between orbital objects
	// T2E is track and object mapping
	// L2E is central object and orbit objects mapping
	// the size of T2E is same with L2E
	// centralObj isn't null
	// Safety from rep exposure:
	// All fields are private and final
	// tracks , T2E , L2E , E2E are mutable types, so operations use defensive
	// copies and
	// immutable wrappers to avoid sharing the rep's objects to clients

	private void checkRep() {
		assert tracks.size() == t2e.size();
	}

	@Override
	public ArrayList<String> getExceptionsList() {
		return exceptionsList;
	}

	@Override
	public L getCentralObject() {
		checkRep();
		return centralObj;
	}

	@Override
	public List<Track> getTracks() {
		return tracks;
	}

	@Override
	public Track findTrack(double r) {
		assert r >= 0;
		for (Track t : tracks) {
			if (t == null) {
				break;
			}
			if (t.getRadius() == r) {
				assert t != null;
				return t;
			}
		}
		return null;
	}

	@Override
	public String getSystemName() {
		return "ConcreteCircularOrbit";
	}

	@Override
	public LeIntimacyMap<L, E> getL2E() {
		return l2e;
	}

	@Override
	public EeIntimacyMap<E> getE2E() {
		return e2e;
	}

	@Override
	public ArrayList<ArrayList<E>> getT2E() {
		return t2e;
	}

	@Override
	public void addTrack(Track track) {
		assert track != null;
		tracks.add(track);

		ArrayList<E> objs = new ArrayList<E>(); // ��ӹ������
		t2e.add(objs);
		checkRep();
	}

	@Override
	public void removeTrack(Track t) {
		assert t != null;
		int i = 0;
		for (i = 0; i < tracks.size(); i++) { // ���track�����
			if (tracks.get(i).equals(t)) {
				tracks.remove(t);
				break;
			}
		}

		int oldSize = tracks.size();
		ArrayList<E> list = t2e.get(i);

		for (E trackObj : list) {
			l2e.remove(centralObj, trackObj); // ɾ����������͹�������ӳ��

			for (int j = 0; j < t2e.size(); j++) {
				ArrayList<E> trackObjList = t2e.get(j); // ������������
				for (E target : trackObjList) {
					e2e.remove(trackObj, target); // ֻҪ�ҵ��߾�ɾ����ӳ��
					e2e.remove(target, trackObj);

				}
			}
		}

		t2e.remove(i); // ɾ�����
//		try{
//			Thread.sleep(10000);
//			}catch(Exception e){
//			System.exit(0);//�˳�����
//			}
		assert tracks.size() - 1 == oldSize;
		checkRep();
	}

	@Override
	public void addCenterObject(L c) {
		centralObj = c;
	}

	@Override
	public void addTrackObject(Track track, E obj) {
		assert track != null;
		assert obj != null;
		int i = 0;
		for (i = 0; i < tracks.size(); i++) { // ���track�����
			if (tracks.get(i).equals(track)) {
				break;
			}
		}

		ArrayList<E> list = t2e.get(i);
		int oldSize = list.size();
		list.add(obj);
		assert oldSize + 1 == list.size();
	}

	@Override
	public void removeTrackObject(Track track, E obj) {
		assert track != null;
		assert obj != null;
		int i = 0;
		for (i = 0; i < tracks.size(); i++) { // ���track�����
			if (tracks.get(i).equals(track)) {
				break;
			}
		}

		ArrayList<E> list = t2e.get(i);
		if (list.contains(obj)) {
			list.remove(obj);
		} else {
			System.out.println("��������ڸ����壡");
		}
	}

	@Override
	public void addCenterTrackObjectsRelation(L c, E obj, float intimacy) {
		assert intimacy > 0 && intimacy <= 1;
		l2e.put(c, obj, intimacy);

	}

	@Override
	public void addTrackObjectsRelation(E obj1, E obj2, float intimacy) {
		assert intimacy > 0;
		e2e.put(obj1, obj2, intimacy);

	}

	@Override
	public void removeCenterTrackObjectsRelation(L c, E obj) {
		l2e.remove(c, obj);
	}

	@Override
	public void removeTrackObjectsRelation(E obj1, E obj2) {
		e2e.remove(obj1, obj2);
	}

	@Override
	public ArrayList<E> getTrackObject(Track track) {
		assert track != null;
		int i = 0;
		for (i = 0; i < tracks.size(); i++) { // ���track�����
			if (tracks.get(i).equals(track)) {
				break;
			}
		}

		ArrayList<E> list = t2e.get(i);
		assert list != null;
		return list;
	}

	@Override
	public void readFile(String file) {
	}

	@Override
	public int printException() {
		if (exceptionsList.size() == 0) {
			return 0;
		} else {
			System.out.println("�ļ���ȡ���������쳣:");
			for (String s : exceptionsList) {
				System.out.println(s);
			}
			return 1;
		}
	}

	@Override
	public void write(WriteStrategy writeStrategy) {
	}

}
