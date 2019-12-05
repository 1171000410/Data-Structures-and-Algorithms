package circularorbit;

import applications.MyOrbitScenes;
import centralobject.Stellar;
import exception.DependencyException;
import exception.GrammarException;
import exception.LabelException;
import exception.NumberException;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;
import java.util.logging.Level;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import physicalobject.Planet;

import track.Track;

public class StellarSystem extends WithPosition<Stellar, Planet> 
    implements CircularOrbit<Stellar, Planet> {

  // Abstraction function:
  // represents StellarSystem inherited from WithPosition<Stellar, Planet>
  // Central object is Stellar and the orbital object is Planet
  // Representation invariant:
  // labelSet is not empty

  
  /** Constructor. */
  public StellarSystem() {
  }

  /** Get name of StellarSystem. */
  @Override
  public String getSystemName() {
    return "StellarSystem";
  }

  /** Read file and create StellarSystem. */
  @Override
  public void readFile(String fileStr) {
	  Set<String> labelSet = new HashSet<String>(); //�洢�ѳ������Ƶ�set
      String[] line = fileStr.split("\n");
      int counter = line.length;
      int lineIndex = 0;
      String p = "(\\w+) ::= <(.+)>";

      while (lineIndex < counter) {
        try {
          Pattern pattern = Pattern.compile(p); // ����������ʽ
          Matcher mentioned = pattern.matcher(line[lineIndex]); // ƥ��������ʽ

          if (mentioned.find()) {

            String[] args = mentioned.group(2).split("[,]");
            if (args.length == 3) {
              Stellar stellar = new Stellar(args[0], translateData(args[1]), 
                  translateData(args[2]));
              addCenterObject(stellar);
              if (labelSet.contains(args[0])) {
                throw new LabelException(":���������ѳ���! Wrong:" + args[0]);
              }
              labelSet.add(args[0]);

              if (args[0].split("\\s").length > 1) {
                throw new LabelException(":�������Ʋ���Label����! Wrong:" + args[0]);
              }
            } else if (args.length == 8) {

              final Planet planet = new Planet(args[0], args[1], args[2], 
                  translateData(args[3]), translateData(args[4]),
                  translateData(args[5]), args[6], Double.parseDouble(args[7]));
              if (translateData(args[3]) > translateData(args[4])) {
                throw new DependencyException(":���ǰ뾶���ܴ��ڹ���뾶! Wrong:����" + args[0]);
              }

              if (labelSet.contains(args[0])) {
                throw new LabelException(":���������ѳ���! Wrong:" + args[0]);
              }
              labelSet.add(args[0]);

              char[] orientationChar = planet.getOrientation().toCharArray();
              for (int i = 0; i < orientationChar.length; i++) {
                if (Character.isLowerCase(orientationChar[i])) {
                  throw new GrammarException(":���Ƿ���ʹ����Сд��ĸ! Wrong:" 
                + planet.getOrientation());
                }
              }
              setObjectSitha(planet, Double.parseDouble(args[7]));

              Track track = new Track(translateData(args[4]));
              addTrack(track);
              addTrackObject(track, planet);
            } else {
              throw new NumberException(":��Ϣ�ķ�����������ȷ! Wrong:" + args.length);
            }
            
            args = null;
          }
        } catch (NumberException e) {
          MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
          getExceptionsList().add(e.getExpMsg());
        } catch (GrammarException e) {
          MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
          getExceptionsList().add(e.getExpMsg());
        } catch (LabelException e) {
          MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
          getExceptionsList().add(e.getExpMsg());
        } catch (DependencyException e) {
          MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
          getExceptionsList().add(e.getExpMsg());
        }

        // �Թ���뾶��������
        for (int i = 0; i < getTracks().size(); i++) {

          for (int j = i + 1; j < getTracks().size(); j++) {
            if (getTracks().get(i).getRadius() > getTracks().get(j).getRadius()) {
              Track e = getTracks().get(i); // �м���� ���������
              getTracks().set(i, getTracks().get(j));
              getTracks().set(j, e);

              ArrayList<Planet> list = getT2E().get(i); // �м�����������������
              getT2E().set(i, getT2E().get(j));
              getT2E().set(j, list);
            }
          }

        }
        lineIndex ++;
        
      }

      labelSet.clear();
      System.gc();
  }

  /**
   * Translate a data from string type to double Numbers greater than 10,000.
   * according to scientific notation and Numbers less than 10000 are given
   * directly
   * 
   * @param s label of the number string
   * @return double type of the number
   */

  public double translateData(String s) throws NumberException {
    assert s != null;
    String[] str = s.split("[e E]");
    if (str.length == 1) {
      if (Double.parseDouble(s) > 10000) {
        throw new NumberException(":δ�ÿ�ѧ������ Wrong:" + Double.parseDouble(s));
      }
      return Double.parseDouble(s);
    } else {
      double a = Double.parseDouble(str[0]);
      int b = Integer.parseInt(str[1]);

      if ((int) a > 9 || (int) a < 1) {
        throw new NumberException(":e֮ǰ�����ֵ��������ֱ�����1��9��Χ�� Wrong:" + a);
      }
      if (b <= 3) {
        throw new NumberException(":e֮�������ֻ���Ǵ���3�������� Wrong:" + b);
      }

      double ret = a * Math.pow(10, b);
      return ret;
    }
  }

}
