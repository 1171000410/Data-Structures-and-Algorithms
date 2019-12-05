package legality;

import centralobject.Stellar;
import circularorbit.CircularOrbit;
import java.util.ArrayList;
import java.util.List;
import physicalobject.Planet;

import track.Track;

public class LegalStellarSystem {

  // Abstraction function:
  // represents security check on StellarSystem

  /**judgeLegality.*/
  public int judgeLegality(CircularOrbit<Stellar, Planet> c) {
    int flag = 1;
    if (c.getCentralObject() == null) {
      System.out.println("���ĵ�û�к���");
      flag = 0;
    }

    ArrayList<ArrayList<Planet>> t2e = c.getT2E();
    List<Track> tracks = c.getTracks();

    for (int i = 0; i < t2e.size(); i++) {
      if (t2e.get(i).size() == 0) {
        System.out.printf("���%dû������\n", i + 1);
        flag = 0;
      }
      if (t2e.get(i).size() > 1) {
        System.out.printf("���%d����һ������\n", i + 1);
        flag = 0;
      }
    }

    for (int i = 0; i < tracks.size(); i++) {
      for (int j = i + 1; j < tracks.size(); j++) {
        if (t2e.get(i).size() != 0 && t2e.get(j).size() != 0) {
          double trackDistance = tracks.get(j).getRadius() - tracks.get(i).getRadius();
          double planetRadiusSum = t2e.get(i).get(0).getPlanetRadius() 
              + t2e.get(j).get(0).getPlanetRadius();
          if (trackDistance < planetRadiusSum) {
//            System.out.println("���ڹ���İ뾶֮��С��������Ӧ���ǵİ뾶֮�ͣ�");
            flag = 0;
          }
        }
      }
    }
    return flag;
  }

}
