package applications;

import circularorbit.CircularOrbit;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.util.ArrayList;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.WindowConstants;

import physicalobject.Electron;

public class CircularOrbitHelper2 {

  private static int numOfTracks; // �����Ŀ
  private static ArrayList<Integer> numOfTrackObjects = new ArrayList<Integer>(); // 
  private static ArrayList<ArrayList<Electron>> T2E = 
      new ArrayList<ArrayList<Electron>>(); // �������ڹ��
  private static final double DEG_TO_RAD = Math.PI / 180; // ���� * this constant = ����

  // Abstraction function:
  //   represents a tool for drawing a static graphs
  // Representation invariant:
  //  numOfTracks is number of tracks
  //  numOfTrackObjects is number of objects per track
  //  T2E is track and object mapping
  //  DEG_TO_RAD is a constant that converts an angle to radians
  //     numOfTracks is > 0 
  // Safety from rep exposure:
  //   All fields are private
  //   int is a primitive type so guaranteed immutable

  /**
   * Get data from a multi-track system.
   * Create components, draw graphics
   * @param c label of the orbit system
   */
  @SuppressWarnings("unchecked")
  public static void visualizes(@SuppressWarnings("rawtypes") CircularOrbit c) {
    numOfTracks = c.getT2E().size();
    T2E = c.getT2E();
    for (int i = 0; i < numOfTracks; i++) {
      numOfTrackObjects.add(i, T2E.get(i).size());
    }

    /*
     * �� AWT ���¼������߳��д������ں����, ȷ���̰߳�ȫ, �� ������������ơ��¼���Ӧ ��Ҫ����ͬһ�̡߳�
     */
    EventQueue.invokeLater(new Runnable() {
      @Override
      public void run() {
        // �������ڶ���
        MyFrame frame = new MyFrame();
        // ��ʾ����
        frame.setVisible(true);
      }
    });
  }

  /**
   * MyFrame class, inherited from JFrame.
   */
  @SuppressWarnings("serial")
  public static class MyFrame extends JFrame {

    public static final String TITLE = "Javaͼ�λ���";

    public static final int WIDTH = 1500;
    public static final int HEIGHT = 1000;

    public MyFrame() {
      super();
      initFrame();
    }

    private void initFrame() {
      // ���� ���ڱ��� �� ���ڴ�С
      setTitle(TITLE);
      setSize(WIDTH, HEIGHT);

      // ���ô��ڹرհ�ť��Ĭ�ϲ���(����ر�ʱ�˳�����)
      setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

      // �Ѵ���λ�����õ���Ļ������
      setLocationRelativeTo(null);

      // ���ô��ڵ��������
      MyPanel panel = new MyPanel(this);
      setContentPane(panel);
    }

  }

  /**
   * MyPanel class inherited from JPanel.
   */
  @SuppressWarnings("serial")
  public static class MyPanel extends JPanel {
    private MyFrame frame;

    public MyPanel(MyFrame frame) {
      super();
      this.frame = frame;
    }

    /**
     * ������������: ���� JPanel ������һ�θ÷�����������, ֮��������ݸı���Ҫ���»���.
     *  �ɵ��� updateUI() ��������
     * ϵͳ�ٴε��ø÷������Ƹ��� JPanel �����ݡ�
     */
    @Override
    protected void paintComponent(Graphics g) {
      super.paintComponent(g);
      // Բ�� / ����
      drawArc(g);
    }

    /**
     * Բ�� / ����.
     */
    private void drawArc(Graphics g) {
      frame.setTitle("AtomStructure");
      Graphics2D g2d = (Graphics2D) g.create();

      g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
      g2d.setColor(Color.BLUE);

      // 1.���ƶ��ͬ��Բ:Բ������(400,400)
      for (int i = 0; i < numOfTracks; i++) {
        g2d.drawArc(350 - i * 50, 350 - i * 50, 100 + i * 100, 100 + i * 100, 0, 360);
        for (int j = 0; j < numOfTrackObjects.get(i); j++) {
          int radius = 50 + i * 50; // �뾶
          double x = 400 + radius * Math.cos((numOfTrackObjects.get(i) + 10) * j * DEG_TO_RAD);
          double y = 400 + radius * Math.sin((numOfTrackObjects.get(i) + 10) * j * DEG_TO_RAD);

          int objX = (int) x;
          int objY = (int) y;

          g2d.fillArc(objX - 5, objY - 5, 10, 10, 0, 360); // ���������
        }
      }

      // 2. ���һ������
      g2d.setColor(Color.RED);
      g2d.fillArc(380, 380, 40, 40, 0, 360);

      g2d.dispose();
    }
  }
}
