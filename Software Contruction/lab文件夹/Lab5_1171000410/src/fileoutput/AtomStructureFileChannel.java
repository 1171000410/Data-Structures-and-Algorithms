package fileoutput;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.ArrayList;

import centralobject.Nucleus;
import circularorbit.CircularOrbit;
import physicalobject.Electron;

public class AtomStructureFileChannel implements WriteStrategy {
	@Override
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void writeFile(String fileName, CircularOrbit c) {
		FileOutputStream fos = null;
		File file = new File(fileName);
		try {
			fos = new FileOutputStream(file);
			FileChannel fc = fos.getChannel();

			// ����������
			ByteBuffer buf = ByteBuffer.allocate(1024);

			Nucleus n = (Nucleus) c.getCentralObject();
			int trackNum = c.getTracks().size();
			String a = "ElementName ::= " + n.getName() + "\n";
			String b = "NumberOfTracks ::= " + trackNum + "\n";
			String d = "NumberOfElectron ::= ";

			// ������װ�뻺����
			buf.put(a.getBytes());
			buf.put(b.getBytes());
			buf.put(d.getBytes());

			ArrayList<ArrayList<Electron>> t2e = c.getT2E();
			for (int i = 0; i < trackNum; i++) {
				a = (i + 1) + "/" + t2e.get(i).size() + ";";
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
