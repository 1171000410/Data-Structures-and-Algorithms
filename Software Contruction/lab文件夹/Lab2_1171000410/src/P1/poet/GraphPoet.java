/* Copyright (c) 2015-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P1.poet;

import java.io.BufferedReader;
//import java.awt.List;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;

import P1.graph.Graph;

/**
 * A graph-based poetry generator.
 * 
 * <p>GraphPoet is initialized with a corpus of text, which it uses to derive a
 * word affinity graph.
 * Vertices in the graph are words. Words are defined as non-empty
 * case-insensitive strings of non-space non-newline characters. They are
 * delimited in the corpus by spaces, newlines, or the ends of the file.
 * Edges in the graph count adjacencies: the number of times "w1" is followed by
 * "w2" in the corpus is the weight of the edge from w1 to w2.
 * 
 * <p>For example, given this corpus:
 * <pre>    Hello, HELLO, hello, goodbye!    </pre>
 * <p>the graph would contain two edges:
 * <ul><li> ("hello,") -> ("hello,")   with weight 2
 *     <li> ("hello,") -> ("goodbye!") with weight 1 </ul>
 * <p>where the vertices represent case-insensitive {@code "hello,"} and
 * {@code "goodbye!"}.
 * 
 * <p>Given an input string, GraphPoet generates a poem by attempting to
 * insert a bridge word between every adjacent pair of words in the input.
 * The bridge word between input words "w1" and "w2" will be some "b" such that
 * w1 -> b -> w2 is a two-edge-long path with maximum-weight weight among all
 * the two-edge-long paths from w1 to w2 in the affinity graph.
 * If there are no such paths, no bridge word is inserted.
 * In the output poem, input words retain their original case, while bridge
 * words are lower case. The whitespace between every word in the poem is a
 * single space.
 * 
 * <p>For example, given this corpus:
 * <pre>    This is a test of the Mugar Omni Theater sound system.    </pre>
 * <p>on this input:
 * <pre>    Test the system.    </pre>
 * <p>the output poem would be:
 * <pre>    Test of the system.    </pre>
 * 
 * <p>PS2 instructions: this is a required ADT class, and you MUST NOT weaken
 * the required specifications. However, you MAY strengthen the specifications
 * and you MAY add additional methods.
 * You MUST use Graph in your rep, but otherwise the implementation of this
 * class is up to you.
 */
public class GraphPoet {
    
    private final Graph<String> graph = Graph.empty();   //����ͼ
    private final List<String> words = new ArrayList<String>();  //�ı��ĵ���
    // Abstraction function:
    // ��������ı�������ȡ��Ϊ����
    // ��������ͼ
    // ת��Ϊpoem
    //
    // Representation invariant:
    // ������ı�words��Ϊ��
    // ����ͼ��Ϊnull
    //
    // Safety from rep exposure:
    // ����fields����private final
    // ����ʽ���
    
    /**
     * Create a new poet with the graph from corpus (as described above).
     * 
     * @param corpus text file from which to derive the poet's affinity graph
     * @throws IOException if the corpus file cannot be found or read
     */
    public GraphPoet(File corpus) throws IOException {
        try(Scanner in = new Scanner(new BufferedReader(new FileReader(corpus)))){ //���ļ���ȡ����
        	while(in.hasNext()) {
        		words.add(in.next().toLowerCase()); //��Сд������
        	}
        }

        for(int i = 0 ;i < words.size() -1;i++) {  //������ת��Ϊͼ
        	String source = words.get(i);
        	String target = words.get(i+1);
        	graph.add(source);
        	
        	int pre_weight = graph.set(source, target, 1);
        	graph.set(source, target, pre_weight + 1);
        }
    }
    
    // TODO checkRep
    public void checkRep() {
    	assert graph != null;
    	assert words != null;
    }
    
    /**
     * Generate a poem.
     * 
     * @param input string from which to create the poem
     * @return poem (as described above)
     */
    public String poem(String input) {
        String[] newWords = input.split("\\s");  //�ո�س����еȿհ׷�
        StringBuilder poem = new StringBuilder(input);  //Ϊ�˷�������Ч�����ַ���
        
        for(int i = 0 ; i < newWords.length -1; i++) {
        	Map<String, Integer> sources = new HashMap<String, Integer>();
        	Map<String, Integer> targets = new HashMap<String, Integer>();
        	targets = graph.targets(newWords[i].toLowerCase());
        	sources = graph.sources(newWords[i+1].toLowerCase());
        	
        	List<String> bridges = new ArrayList<String>();
        	
        	for(String s1 : targets.keySet()) {  //ǰһ����targets�ͺ�һ��sources�н���
        		for(String s2 : sources.keySet()) {
        			if(s1.equals(s2)) {
        				bridges.add(s1);
        			}
        		}
        	}
        	
        	if(!bridges.isEmpty()) {
        		Random r = new Random();
        		int n = r.nextInt(bridges.size()); //����[0,bridges.size())�����int
        	
        		String selectedBridge = bridges.get(n);
        		
        		poem.insert(poem.indexOf(newWords[i+1]), selectedBridge + " "); //����bridge
        	}
        }
        checkRep();
        return poem.toString();
    }
    
    // TODO toString()
    @Override
    public String toString() {
    	return graph.toString();
    }
}
