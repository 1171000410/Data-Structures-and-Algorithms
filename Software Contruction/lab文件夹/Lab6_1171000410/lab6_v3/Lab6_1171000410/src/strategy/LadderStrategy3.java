package strategy;

import crossing.Ladder;
import crossing.CrossingSimulator;

public class LadderStrategy3 implements Strategy {
	
	// ������û�ж�����еĺ���
	// ����������ͬ����еĺ�����������5��
	
	@Override
	public Ladder chooseLadder(String direction) {
		for (Ladder l : CrossingSimulator.ladderList) {
			if ((l.getLeftCrossing() == 0 && direction.startsWith("R") && l.getRightCrossing() <= 5)
					|| ((l.getRightCrossing() == 0 && direction.startsWith("L") && l.getLeftCrossing() <= 5))) {
				//û�ж�����еĺ���,����������ͬ����еĺ���������5��					
				return l;
			}
		}
		return null;
	}
}
