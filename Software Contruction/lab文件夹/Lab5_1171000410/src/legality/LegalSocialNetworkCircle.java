package legality;

import apis.CircularOrbitapis;
import centralobject.CentralUser;
import circularorbit.CircularOrbit;
import java.util.ArrayList;
import physicalobject.Friend;


public class LegalSocialNetworkCircle {

  // Abstraction function:
  //  represents security check on SocialNetworkCircle 

  /**judgeLegality.*/
  public int judgeLegality(CircularOrbit<CentralUser, Friend> c) {
    int min = 10000;

    for (int i = 1; i < c.getT2E().size(); i++) {
      ArrayList<Friend> list = c.getT2E().get(i);
      for (Friend f : list) {
        CircularOrbitapis<CentralUser, Friend> h = new CircularOrbitapis<CentralUser, Friend>();
        int d = 0;
        int counter = 0;
        for (Friend f2 : c.getT2E().get(0)) {
          d = h.getLogicalDistance(c, f, f2);
          if (d > 0 && d < min) {
            min = d;
          }
          if (d < 0) { //���һ�����ĳ����û��ϵcounter�ͼ�һ
            counter++;
          }

        }
        if (counter == c.getT2E().get(0).size()) { //���һ�����ÿ���˶�û��ϵ
          System.out.println("�������û�����ͨ���˲�Ӧ�����ڹ��ϵͳ�У�");
          return 0;
        }

        if ((i + 1) != (min + 1)) {
          //    System.out.println("���ĵ�͹������������");
          //    System.out.println("����Ĺ���û���"+f.getName());
          //    System.out.println("���۾���" + (i+1));
          //    System.out.println("ʵ�ʾ���" + (d+1));
          //    return 0;
        }

      }
    }
    return 1;

  }
}
