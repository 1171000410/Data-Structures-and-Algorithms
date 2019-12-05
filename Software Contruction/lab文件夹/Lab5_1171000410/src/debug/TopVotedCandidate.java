package debug;

/**
 * In an election, the i-th vote was cast for persons[i] at time times[i].
 * 
 * Now, we would like to implement the following query function:
 * TopVotedCandidate.q(int t) will return the number of the person that was
 * leading the election at time t.
 * 
 * Votes cast at time t will count towards our query. In the case of a tie, the
 * most recent vote (among tied candidates) wins.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: ["TopVotedCandidate","q","q","q","q","q","q"],
 * [[[0,1,1,0,0,1,0],[0,5,10,15,20,25,30]],[3],[12],[25],[15],[24],[8]]
 *  Output:
 * [null,0,1,1,0,0,1] 
 * 
 * Explanation: 
 * At time 3, the votes are [0], and 0 is leading. 
 * At time 12, the votes are [0,1,1], and 1 is leading. 
 * At time 25, the votes are [0,1,1,0,0,1], and 1 is leading (as ties go to the most recent
 * vote.) 
 * This continues for 3 more queries at time 15, 24, and 8.
 * 
 * 
 * Note:
 * 
 * 1 <= persons.length = times.length <= 5000 
 * 0 <= persons[i] <= persons.length
 * times is a strictly increasing array with all elements in [0, 10^9].
 * TopVotedCandidate.q is called at most 10000 times per test case.
 * TopVotedCandidate.q(int t) is always called with t >= times[0].
 *
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class TopVotedCandidate {
  List<List<Vote>> aa;

  @SuppressWarnings({ "unchecked", "rawtypes" })
  public TopVotedCandidate(int[] persons, int[] times) {
    aa = new ArrayList();
    Map<Integer, Integer> count = new HashMap(); //ĳ��ӳ���ѡƱ��
    for (int i = 0; i < persons.length; ++i) {
      int p = persons[i];
      int t = times[i];
      //�޸�1��int c = count.getOrDefault(p, 1);
      //�޸�ԭ��cΪp��ѡƱ������1
      int c = count.getOrDefault(p, 0) + 1;

      count.put(p, c);
      while (aa.size() <= c) {
        aa.add(new ArrayList<Vote>());
      }
      aa.get(c).add(new Vote(p, t));
    }
  }

  public int qq(int t) {
    int lo = 1;
    int hi = aa.size();
    while (lo < hi) {
      int mi = lo + (hi - lo) / 2;
      if (aa.get(mi).get(0).time <= t) {
        //�޸�2��mi+1
        //�޸�ԭ�򣺶��ַ�
        lo = mi + 1;
      } else {
        hi = mi;
      }
    }
    //�޸�3����lo��һ
    //�޸�ԭ��ʹ��i��Ӧlist��vote��time��<=t
    int i = lo - 1;

    lo = 0;
    hi = aa.get(i).size();
    while (lo < hi) {
      int mi = lo + (hi - lo) / 2;
      //�޸�4��<=
      //�޸�ԭ�򣺶��ַ�
      if (aa.get(i).get(mi).time <= t) {
        lo = mi + 1;
      } else {
        hi = mi;
      }
    }
    //�޸�5��lo-1
    //�޸�ԭ�򣺻��ʱ����ӽ���С��t��Ʊ
    int j = Math.max(lo - 1, 0);
    return aa.get(i).get(j).person;
  }
}
