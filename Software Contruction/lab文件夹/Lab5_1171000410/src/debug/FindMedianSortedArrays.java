package debug;

/**
 * Given two ordered integer arrays nums1 and nums2, with size m and n
 * Find out the median (double) of the two arrays.
 * You may suppose nums1 and nums2 cannot be null at the same time.
 *
 * <p>Example 1:
 * nums1 = [1, 3]
 * nums2 = [2]
 * The output would be 2.0
  
 * Example 2:
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 * The output would be 2.5

 * Example 3:
 * nums1 = [1, 1, 1]
 * nums2 = [5, 6, 7]
 * The output would be 3.0

 * Example 4:
 * nums1 = [1, 1]
 * nums2 = [1, 2, 3]
 * The output would be 1.0
 */

public class FindMedianSortedArrays {

  /**findMedianSortedArrays.*/
  public double findMedianSortedArrays(int[] aa, int[] bb) {
    int m = aa.length;
    int n = bb.length;
    if (m > n) { //��������,Ϊ�˱�֤m<=n
      int[] temp = aa;
      aa = bb;
      bb = temp;
      int tmp = m;
      m = n;
      n = tmp;
    }
    //�޸�1��halfLen = (m + n + 1) / 2
    //�޸�ԭ�򣺱�֤m+nΪ������ʱ����λ������ߵ�part
    int imin = 0;
    int imax = m;
    int halfLen = (m + n + 1) / 2;
    while (imin <= imax) {
      int i = (imin + imax + 1) / 2;
      int j = halfLen - i;
      if (i < imax && bb[j - 1] > aa[i]) {
        imin = i + 1; //i̫С
      } else if (i > imin && aa[i - 1] > bb[j]) {
        imax = i - 1; //i̫��
      } else { //i��С�պ�����Ŀ��
        int maxLeft = 0;
        if (i == 0) { //�ٽ�
          maxLeft = bb[j - 1];
        } else if (j == 0) { //�ٽ�
          maxLeft = aa[i - 1];
        } else {
          maxLeft = Math.max(aa[i - 1], bb[j - 1]); //�������
        }

        //�޸�2��(m + n) % 2 != 0
        //�޸�ԭ�򣺴�ʱΪm+nΪ����������������������
        if ((m + n) % 2 != 0) {
          return maxLeft;
        }
        int minRight = 0;
        if (i == m) { //�ٽ�
          minRight = bb[j];
        } else if (j == n) { //�ٽ�
          minRight = aa[i];
        } else {
          minRight = Math.min(bb[j], aa[i]); //�ұ���С��
        }
        return (maxLeft + minRight) / 2.0; //m+nΪż��ʱ
      }
    }
    return 0.0;
  }

}
