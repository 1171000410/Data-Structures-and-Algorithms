package circularorbit;

import java.util.ArrayList;
import java.util.Iterator;

import track.Track;

public class WithoutPosition<L, E> extends ConcreteCircularOrbit<L, E> {

  // Abstraction function:
  //   represents system with no fixed position of the object

  /**
   * Migrate object from the current track to the track t.
   * @param object label of the current object
   * @param t label of the target track
   */
  public void transit(E object, Track t) {

    for (ArrayList<E> list : getT2E()) { //��ԭ���ɾ��
      for (Iterator<E> it = list.iterator(); it.hasNext();) { //����ʱɾ��
        E obj = it.next();
        if (obj.equals(object)) {
          list.remove(obj);
        }
      }
    }

    addTrackObject(t, object); //��ӵ��¹��
  }
}
