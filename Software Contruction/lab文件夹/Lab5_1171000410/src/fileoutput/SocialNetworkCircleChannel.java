package fileoutput;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.Set;

import centralobject.CentralUser;
import circularorbit.CircularOrbit;
import circularorbit.SocialNetworkCircle;
import physicalobject.Friend;
import relation.EeIntimacyMap;
import relation.LeIntimacyMap;

public class SocialNetworkCircleChannel implements WriteStrategy {
  @Override
  @SuppressWarnings({ "rawtypes", "unchecked" })
  public void writeFile(String fileName, CircularOrbit c) {
	FileOutputStream fos = null;
	File file = new File(fileName);
	try {
	  fos = new FileOutputStream(file);
	  FileChannel fc = fos.getChannel();

	  // ����������
	  ByteBuffer buf = ByteBuffer.allocate(0x300000);  //3M

	  CentralUser n = (CentralUser) c.getCentralObject();

	  String a;
	  a = "CentralUser ::= <" + n.getName() + "," + n.getAge() + "," + n.getGender() + ">\n\n";
	  buf.put(a.getBytes());

	  LeIntimacyMap<CentralUser, Friend> l2e = c.getL2E();
	  EeIntimacyMap<Friend> e2e = c.getE2E();

	  Set<String> fs = l2e.getValuesAndWeight(); //д��SocialTie
	  for (String s : fs) {
		a = "SocialTie ::= <" + s + ">" + "\n";
		if(buf.remaining() < 1024) {
		  buf.flip();
		  fc.write(buf);
		  buf.clear();
		}
		buf.put(a.getBytes());
	  }

	  Set<String> es = e2e.getEdgesString();
	  for (String e : es) {
		a = "SocialTie ::= <" + e + ">\n";
		if(buf.remaining() < 1024) {
		  buf.flip();
		  fc.write(buf);
		  buf.clear();
		}
		buf.put(a.getBytes());
	  }
	  buf.put(a.getBytes());

	  SocialNetworkCircle s = (SocialNetworkCircle) c;
	  Set<Friend> fSet = s.getFriends();
	  for (Friend f : fSet) {
		a = "Friend ::= <" + f.getName() + "," + f.getFriendAge() + "," + f.getFriendGender() + ">\n";
		if(buf.remaining() < 1024) {
		  buf.flip();
		  fc.write(buf);
		  buf.clear();
		}
		buf.put(a.getBytes());
	  }

	  // ��ת������(limit����Ϊposition,position����Ϊ0,mark����Ϊ-1)
	  buf.flip();

	  // ���������е�����д�뵽ͨ��
	  fc.write(buf);

	  // д�꽫��������ԭ(position����Ϊ0,limit����Ϊcapacity,mark����Ϊ-1)
	  buf.clear();
	} catch (Exception e) {
	  e.printStackTrace();
	} finally {
	  try {
		if (fos != null) {
		  fos.close();
		}
	  } catch (IOException e) {
		e.printStackTrace();
	  }
	}
  }
}
