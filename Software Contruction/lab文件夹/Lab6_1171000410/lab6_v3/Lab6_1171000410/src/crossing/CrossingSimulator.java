package crossing;

import java.awt.Font;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.logging.FileHandler;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.JFrame;
import javax.swing.JScrollPane;

import crossing.MyFormatter;
//import strategy.LadderStrategy1;
import strategy.LadderStrategy2;
import strategy.Strategy;

public class CrossingSimulator {
	public static int h; //length of ladders
	public static int n; //quantity of ladders
	public static ArrayList<Monkey> monkeyList = new ArrayList<Monkey>(); //list to store monkeys
	public static ArrayList<Ladder> ladderList = new ArrayList<Ladder>(); //list to store ladders
	public static final Logger log = Logger.getLogger(CrossingSimulator.class.getSimpleName());
	public static double extraTime = 0; //time spent on GUI and log

    // Abstraction function:
    //   represents a simulator to produce and start monkeys in the ladders
	//   record logs and extra time
    // Representation invariant:
    //   h is initialized to 20 and immutable
	//   1 < n < 10
	//   2 < monkeyList.size() < 1000
    //   1 < ladderList.size() < 10
	//   log is not null
	//   extratime > 0
    // Safety from rep exposure:
    //   monkeyList and ladderList are mutable lists, so operation make defensive
    //   copies and use immutable views to avoid sharing the rep
    //   as for a mutable type, operations use defensive copies 
    //   h and log is final
	
	public static void main(String[] args) {
		try {
			// �ļ�������
			FileHandler fileHandler = new FileHandler("log/monkeysLog.log");
			fileHandler.setFormatter(new MyFormatter());
			log.setUseParentHandlers(false); // ��logger��Ϣ���ڿ���̨���
			log.addHandler(fileHandler);

			BufferedReader reader = null;
			reader = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("��������ӹ��������ļ�·��:");
			// txt/Competition_1.txt
			String filename = reader.readLine();
			
			//GUI
			JFrame f = new JFrame("Go ! Go ! Monkeys !");
			ConsoleTextArea consoleTextArea = null;
			try {
				consoleTextArea = new ConsoleTextArea();
			} catch (IOException e) {
				System.err.println("���ܴ���LoopedStreams��" + e);
				System.exit(1);
			}
			consoleTextArea.setFont(new Font("Consolas", Font.BOLD, 32)); //��������
			f.getContentPane().add(new JScrollPane(consoleTextArea), java.awt.BorderLayout.CENTER);
			f.setBounds(50, 50, 1500, 950);
			f.setVisible(true);
			f.addWindowListener(new java.awt.event.WindowAdapter() {
				@Override
				public void windowClosing(java.awt.event.WindowEvent evt) {
					System.exit(0);
				}
			});

			File file = new File(filename);
			readFile(file);
			fileHandler.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	private static void readFile(File file) {

		try {
			BufferedReader bf = new BufferedReader(new FileReader(file));
			String s = null;
			String str[];
			// �ȶ���n��h
			s = bf.readLine();
			str = s.split("=");
			n = Integer.parseInt(str[1]);
			s = bf.readLine();
			str = s.split("=");
			h = Integer.parseInt(str[1]);

			for (int i = 0; i < n; i++) { //new ladders
				Ladder l = new Ladder(i + 1);
				ladderList.add(l);
			}

			String p = "(\\w+)=<(.+)>";
			while ((s = bf.readLine()) != null) { // ʹ��readLine������һ�ζ�һ��
				Pattern pattern = Pattern.compile(p); // ����������ʽ
				Matcher mentioned = pattern.matcher(s); // ƥ��������ʽ
				if (mentioned.find()) {
					String[] args = mentioned.group(2).split(",");
					Monkey m = new Monkey(Integer.parseInt(args[0]), Integer.parseInt(args[1]), args[2],
							Integer.parseInt(args[3]));
					monkeyList.add(m);
				}

			}
			bf.close(); //�����ļ���ȡ	

		} catch (IOException e) {
			System.out.println("�ļ���ȡ����!");
		}

		int t = 0; //�������ӵļ��ʱ��
		int k = 0; //һ�β������ٺ���
		for (Monkey m : monkeyList) {
			if (m.getProduceTimer() != 0) {
				t = m.getProduceTimer();
				break;
			}
			k++;
		}

		System.out.println("Parameter configuration:");
		System.out.println("Number of ladders     n = " + n);
		System.out.println("Intervals             t = " + t);
		System.out.println("number of monkeys     N = " + monkeyList.size());
		System.out.println("monkeys per second    k = " + k);
		System.out.println("\n\n");
		System.out.println("                                     Ladder\n");
		System.out.println("Left Side                                               " + "  Right Side");
		
		double startTime = System.currentTimeMillis();
		Strategy ls = new LadderStrategy2();
		try {
			final int times = monkeyList.size() / k; //�����Ĵ���
			for (int i = 0; i < times; i++) {
				for (int j = k * i; j < k * (i + 1); j++) {
					monkeyList.get(j).setLadderStategy(ls);
					monkeyList.get(j).start();
				}

				Thread.sleep(t * 1000); //�����ʱ��
			}

			if (monkeyList.size() % k != 0) {
				for (int m = k * times; m < monkeyList.size(); m++) {
					monkeyList.get(m).setLadderStategy(ls);
					monkeyList.get(m).start();
				}
			}

			for (int i = 0; i < monkeyList.size(); i++) {
				monkeyList.get(i).join(); //�ȴ��ӽ��̽���
			}
			
			double finishTime = System.currentTimeMillis();
			double totalTime = finishTime - startTime - extraTime;
			System.out.println("finishTime - startTime:" + (finishTime - startTime) + "ms");
			System.out.println("extraTime:"+extraTime+"ms");
			System.out.println("totalTime:"+totalTime+"ms");
			System.out.println("Throughput rate:   " + monkeyList.size() * 1000 / totalTime);

			//���㹫ƽ��
			double fairness = 0;
			for (int i = 0; i < monkeyList.size(); i++) {
				for (int j = i + 1; j < monkeyList.size(); j++) {
					if ((monkeyList.get(i).getProduceTimer()
							- monkeyList.get(j).getProduceTimer())
							* (monkeyList.get(i).getNow()
									- monkeyList.get(j).getNow()) >= 0) {
						fairness++;
					} else {
						fairness--;
					}
				}
			}
			double res = 2 * fairness / monkeyList.size() / (monkeyList.size() - 1);
			System.out.println("Fairness:           " + res);
			
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
