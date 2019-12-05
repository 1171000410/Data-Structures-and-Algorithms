package strategy;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import crossing.Ladder;
import crossing.CrossingSimulator;

public class LadderStrategy2 implements Strategy {

	@Override
	public Ladder chooseLadder(String direction) {
		for (Ladder l : CrossingSimulator.ladderList) {
			if (l.getLeftCrossing() == 0 && l.getRightCrossing() == 0) { //������û�к���ֱ�ӷ���
				return l;
			}
		}

		Map<Integer, Ladder> priorityMap = new HashMap<Integer, Ladder>();
		int monkeyQuantities, point = 0, nearest = CrossingSimulator.h;
		for (Ladder l : CrossingSimulator.ladderList) {
			if ((l.getLeftCrossing() == 0 && direction.startsWith("R"))
					|| ((l.getRightCrossing() == 0 && direction.startsWith("L")))) { //û�ж�����еĺ���

				monkeyQuantities = l.getLeftCrossing() + l.getRightCrossing();
				for (int i = 0; i < CrossingSimulator.h; i++) {
					if (l.getPedals()[i] == 1) {
						nearest = i;
					}
				}
				point = nearest - 2 * monkeyQuantities; //���ݹ�ϵ�Լ�����Ȩֵ
				priorityMap.put(point, l);

			}
		}

		if (priorityMap.keySet().size() == 0) {
			return null;
		}
		int maxPoint = Collections.max(priorityMap.keySet());
		if (maxPoint < -3) {
			return null;
		}
		return priorityMap.get(maxPoint);

	}
}
