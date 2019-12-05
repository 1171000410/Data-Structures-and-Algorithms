package circularorbit;

import applications.MyOrbitScenes;
import centralobject.Nucleus;
import exception.DependencyException;
import exception.GrammarException;
import exception.LabelException;
import exception.MyException;
import fileoutput.WriteStrategy;

import java.util.HashSet;
import java.util.Set;
import java.util.logging.Level;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import physicalobject.Electron;

import track.Track;

public class AtomStructure extends WithoutPosition<Nucleus, Electron> implements 
    CircularOrbit<Nucleus, Electron> {

  // Abstraction function:
  // represents AtomStructure inherited from WithoutPosition<Nucleus, Electron>
  // Central object is Nucleus and the orbital object is Electron
  // Representation invariant:
  // trackSet is not empty
  private Set<Integer> trackSet = new HashSet<Integer>();  //��������Ƿ��ظ�
  
  private void checkRep() {
    assert trackSet.size() > 0;
  }

  /** Constructor.*/
  public AtomStructure() {
  }

  /** Get name of AtomStructure.*/
  @Override
  public String getSystemName() {
    return "AtomStructure";
  }

  /** Read file and create AtomStructure. */
  @Override
  public void readFile(String fileStr) {

      String regex = "\\s+";
      String newFlieStr = fileStr.replaceAll(regex, ""); // ȥ���ո�

      String[] args = { "(ElementName::)(=\\D*)", "(NumberOfTracks)(\\D*)(\\d+)", 
          "(\\d+)(/)(\\d+)" };

      Integer numOfTracks = 0;
      for (int i = 0; i < args.length; i++) {
        Pattern pattern = Pattern.compile(args[i]); // ����������ʽ
        Matcher mentioned = pattern.matcher(newFlieStr); // ƥ��������ʽ

        boolean just = mentioned.find(); // ��������һ����־�����һ��find���

        if (just && i == 0) {
          String match = new String(mentioned.group(2).toString());
          match = match.substring(1);
          String del = "NumberOfTracks::=";
          String[] ii = match.split(del);
          match = ii[0];
          char[] nucleusChar = match.toCharArray();

          try {
            if (nucleusChar.length != 2) {
              throw new GrammarException(":����Ԫ����ĸ������ȷ! Wrong:" + nucleusChar.length);
            }
          } catch (MyException e) {
            getExceptionsList().add(e.getExpMsg());
            MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
          }

          if (nucleusChar.length >= 2) {
            try {
              if (Character.isLowerCase(nucleusChar[0])) {
                throw new GrammarException(":����Ԫ����ĸ��һλӦ��д! Wrong:" + nucleusChar[0]);
              }
            } catch (MyException e) {
              getExceptionsList().add(e.getExpMsg());
              MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
            }

            try {
              if (Character.isUpperCase(nucleusChar[1])) {
                throw new GrammarException(":����Ԫ����ĸ�ڶ�λӦСд! Wrong:" + nucleusChar[1]);
              }
            } catch (MyException e) {
              getExceptionsList().add(e.getExpMsg());
              MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
            }
          }
          Nucleus nucleus = new Nucleus(match);
          addCenterObject(nucleus);
        }

        if (just && i == 1) {
          numOfTracks = new Integer(mentioned.group(3));

          try {
            if (numOfTracks <= 0) {
              throw new GrammarException(":�����Ŀ�����Ϲ淶! Wrong:" + numOfTracks);
            }
          } catch (MyException e) {
            getExceptionsList().add(e.getExpMsg());
            MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
          }

          for (int j = 0; j < numOfTracks; j++) {
            Track t = new Track(i);
            addTrack(t);
          }
        }

        if (just && i == 2) {
          int trackCounter = 0;
          do {
            Integer trackNumber = new Integer(mentioned.group(1)); // ������
            Integer numOfElectron = new Integer(mentioned.group(3)); // ���������
            trackCounter++;

            try {
              if (trackSet.contains(trackNumber)) {
                throw new LabelException(":������ѳ���! Wrong:" + trackNumber);
              }
              trackSet.add(trackNumber);
            } catch (LabelException e) {
              getExceptionsList().add(e.getExpMsg());
              MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
            }

            try {
              if (trackNumber > numOfTracks) {
                throw new GrammarException(":����Ŵ��ڹ����! Wrong:�����" + trackNumber);
              }
              Track t = getTracks().get(trackNumber - 1);

              for (int k = 0; k < numOfElectron; k++) {
                Electron e = new Electron("electron");
                addTrackObject(t, e);
              }
            } catch (MyException e) {
              getExceptionsList().add(e.getExpMsg());
              MyOrbitScenes.log.log(Level.SEVERE,e.getExpMsg());
            }

            try {
              if (trackCounter == 1 && numOfElectron > 2) {
                throw new DependencyException(":��һ�������������ܴ���2! Wrong:" + numOfElectron);
              }
            } catch (MyException e) {
              getExceptionsList().add(e.getExpMsg());
              MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
            }

          } while (mentioned.find());

          try {
            if (trackCounter != numOfTracks) {
              throw new DependencyException(":�������������ϵ����ȷ!");
            }
          } catch (MyException e) {
            getExceptionsList().add(e.getExpMsg());
            MyOrbitScenes.log.log(Level.SEVERE, e.getExpMsg());
          }
        }

      }
      checkRep();

  }
  
  
  @Override
  public void write(WriteStrategy writeStrategy) {

  }
  

}
