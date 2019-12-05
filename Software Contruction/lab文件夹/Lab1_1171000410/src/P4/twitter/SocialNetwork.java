/* Copyright (c) 2007-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P4.twitter;

//import java.nio.file.DirectoryStream.Filter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import P4.twitter.Extract;

/**
 * SocialNetwork provides methods that operate on a social network.
 * 
 * A social network is represented by a Map<String, Set<String>> where map[A] is
 * the set of people that person A follows on Twitter, and all people are
 * represented by their Twitter usernames. Users can't follow themselves. If A
 * doesn't follow anybody, then map[A] may be the empty set, or A may not even
 * exist as a key in the map; this is true even if A is followed by other people
 * in the network. Twitter usernames are not case sensitive, so "ernie" is the
 * same as "ERNie". A username should appear at most once as a key in the map or
 * in any given map[A] set.
 * 
 * DO NOT change the method signatures and specifications of these methods, but
 * you should implement their method bodies, and you may add new public or
 * private methods or classes if you like.
 */
public class SocialNetwork {

	/**
	 * Guess who might follow whom, from evidence found in tweets.
	 * 
	 * @param tweets a list of tweets providing the evidence, not modified by this
	 *               method.
	 * @return a social network (as defined above) in which Ernie follows Bert if
	 *         and only if there is evidence for it in the given list of tweets. One
	 *         kind of evidence that Ernie follows Bert is if Ernie
	 * @-mentions Bert in a tweet. This must be implemented. Other kinds of evidence
	 *            may be used at the implementor's discretion. All the Twitter
	 *            usernames in the returned social network must be either authors
	 *            or @-mentions in the list of tweets.
	 *            �ҵ�����tweets���������ߣ��ٴ��������ߵ�tweets���ҵ�����ע����
	 */
	public static Map<String, Set<String>> guessFollowsGraph(List<Tweet> tweets) {
		Map<String, Set<String>> map = new HashMap<String, Set<String>>();
		Set<String> authors = new HashSet<String>();
		for (int i = 0; i < tweets.size(); i++) {
			Tweet one = tweets.get(i);
			authors.add(one.getAuthor().toLowerCase()); // ���tweet���ߵ�Сд��
		}
		for (String auth : authors) { // ������������

			List<Tweet> texts = Filter.writtenBy(tweets, auth);
			Set<String> mentioned_users = Extract.getMentionedUsers(texts);
			map.put(auth, mentioned_users);
		}
		return map;
	}

	/**
	 * Find the people in a social network who have the greatest influence, in the
	 * sense that they have the most followers.
	 * 
	 * @param followsGraph a social network (as defined above)
	 * @return a list of all distinct Twitter usernames in followsGraph, in
	 *         descending order of follower count. usernames��������ע������
	 *         ��Ϊ��Ҫ�˺����ֵ�ӳ�䣬��˻��蹹��influenceMap
	 */
	public static List<String> influencers(Map<String, Set<String>> followsGraph) {
		Map<String, Integer> quantityMap = new HashMap<String, Integer>();
		List<String> influencers = new ArrayList<String>();
		Set<String> authors = followsGraph.keySet(); // key��������
		for (String auth : authors) {
			for (String mentioned : followsGraph.get(auth)) {
				if (quantityMap.containsKey(mentioned)) // �Ѱ���key���ټ�1
					quantityMap.put(mentioned, quantityMap.get(mentioned) + 1);
				else // δ����key�����
					quantityMap.put(mentioned, 1);
			}
		}
		for (String mentioned_user : quantityMap.keySet()) { // ��������
			int i = 0;
			while (i < influencers.size() && quantityMap.get(mentioned_user) < quantityMap.get(influencers.get(i))) {
				i++;
			}
			influencers.add(mentioned_user);
		}
		return influencers;
	}

	/*
	 * For Get smarter
	 */
	public static Map<String, Set<String>> MyguessFollowsGraph(List<Tweet> tweets) {
		Map<String, Set<String>> map = new HashMap<String, Set<String>>();
		ArrayList<String> authors = new ArrayList<String>();
		ArrayList<String> tags = new ArrayList<String>();
		Map<String, ArrayList<String>> authorMap = new HashMap<String, ArrayList<String>>();

		Pattern pattern = Pattern.compile("(#[A-Za-z]+)"); // ����������ʽ
		for (int i = 0; i < tweets.size(); i++) {
			String text = tweets.get(i).getText();
			Matcher tag = pattern.matcher(text); // ƥ��������ʽ
			while (tag.find()) {
				String match_tag = new String(tag.group());
				tags.add(match_tag);
			}
		}

		for (int i = 0; i < tags.size(); i++) {
			for (int j = 0; j < tweets.size(); j++) {
				String text = tweets.get(j).getText();
				Pattern one = Pattern.compile(tags.get(i));
				Matcher word = one.matcher(text); // ƥ��tags��ı��
				while (word.find()) {
					authors.add(tweets.get(j).getAuthor());
				}
			}
			authorMap.put(tags.get(i), authors);
		}

		for (String key : authorMap.keySet()) {  //�������б��
			ArrayList<String> new_authors = new ArrayList<String>();
			new_authors = authorMap.get(key);
			for (int k = 0; k < new_authors.size(); k++) {  //����values�������
				Set<String> ans = new HashSet<String>();
				for (int m = 0; m < new_authors.size(); m++) {
					ans.add(new_authors.get(m));   //values������߻����ע
				}
				map.put( new_authors.get(k), ans);
				ans = null;
			}
		}
		return map;
	}
}
