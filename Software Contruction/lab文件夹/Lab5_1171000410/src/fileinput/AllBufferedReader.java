package fileinput;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class AllBufferedReader implements ReadStrategy {

	@Override
	public String readFile(File file) {
		StringBuffer buffer = new StringBuffer();
		try {
			long startTime = System.currentTimeMillis();
			BufferedReader bf = new BufferedReader(new FileReader(file));
			String s = null;
			while ((s = bf.readLine()) != null) { // ʹ��readLine������һ�ζ�һ��
				buffer.append(s.trim()+"\n");
			}
			bf.close(); //�����ļ���ȡ	
			long finishTime = System.currentTimeMillis();
            long totalTime = finishTime - startTime;
            System.out.println("BufferReader:" + totalTime + "ms");

		} catch (IOException e) {
			System.out.println("�ļ���ȡ����!");
		}
		
		String fileStr = buffer.toString();
		return fileStr;
	}

}
