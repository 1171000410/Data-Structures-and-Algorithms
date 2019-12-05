package apis;

import java.util.ArrayList;

public class Difference {
  private final int tracksNumDifference; //�����Ŀ����
  private ArrayList<Integer> specificTracksNumDifference = 
                      new ArrayList<Integer>(); //�ض����������Ŀ����
  private ArrayList<String> objectsDifference = new ArrayList<String>(); //���������

  // Abstraction function:
  //   represents difference between two orbit systems
  // Representation invariant:
  //  tracksNumDifference is difference in the number of tracks
  //  specificTracksNumDifference is difference in the number of specific orbital objects
  //  objectsDifference is Orbital object gap
  //    specificTracksNumDifference.size() == objectsDifference.size()
  // Safety from rep exposure:
  //   All fields are private
  //   int is a primitive type so guaranteed immutable

  /**Constructor.*/
  public Difference(int a, ArrayList<Integer> b, ArrayList<String> c) {
    this.tracksNumDifference = a;
    this.specificTracksNumDifference = b;
    this.objectsDifference = c;
  }

  private void checkRep() {
    assert specificTracksNumDifference.size() == objectsDifference.size();
  }

  /**
   * Print difference another orbit systems.
   */
  public void printOtherDifference() {
    System.out.println("��������죺" + tracksNumDifference);
    for (int i = 1; i <= specificTracksNumDifference.size(); i++) {
      System.out.printf("���%d�������������죺%d�� ������죺%s\n", i, 
          specificTracksNumDifference.get(i - 1),
          objectsDifference.get(i - 1));
    }
    checkRep();
  }

  /**
   * Print difference between two AtomStructrues.
   */
  public void printAtomStructrueDifference() {
    System.out.println("��������죺" + tracksNumDifference);
    for (int i = 1; i <= specificTracksNumDifference.size(); i++) {
      System.out.printf("���%d�������������죺%d\n", i, specificTracksNumDifference.get(i - 1));
    }
  }

}
