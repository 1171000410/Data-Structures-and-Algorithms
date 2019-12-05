/* Copyright (c) 2015-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P1.graph;

import static org.junit.Assert.*;

//import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import org.junit.Test;

/**
 * Tests for ConcreteVerticesGraph.
 * 
 * This class runs the GraphInstanceTest tests against ConcreteVerticesGraph, as
 * well as tests for that particular implementation.
 * 
 * Tests against the Graph spec should be in GraphInstanceTest.
 */
public class ConcreteVerticesGraphTest extends GraphInstanceTest {
    
    /*
     * Provide a ConcreteVerticesGraph for tests in GraphInstanceTest.
     */
    @Override public Graph<String> emptyInstance() {
        return new ConcreteVerticesGraph<>();
    }
    
    /*
     * Testing ConcreteVerticesGraph...
     */
    
    // Testing strategy for ConcreteVerticesGraph.toString()
    //
    //  ����toString()������
    //  ��GraphΪ�յ�ʱ��
	//  ��Graph��Ϊ�յ�ʱ��
    //  ƥ��string���ж��Ƿ����
        
    // TODO tests for ConcreteVerticesGraph.toString()
    @Test
    public void testToString() {
    	Graph<String> graph = emptyInstance();
    	
    	/*���Կ�Graph*/
    	assertEquals("Expected an empty graph", "This is An Empty Graph",graph.toString());
    	
    	final String vertex1 = "v1";
		final String vertex2 = "v2";
		final String vertex3 = "v3";
		final int weight = 1;
		graph.set(vertex1, vertex2, weight);
		graph.set(vertex2, vertex3, weight);
		assertEquals("Expected string of graph", "v1->v2:1"+"\n"+"v2->v3:1"+"\n",graph.toString());    	
    }
       
    /*
     * Testing Vertex...
     */
    
    // Testing strategy for Vertex
    // ����getString()������
    // �����ض�������ַ���
    // �жϸõ��ȡ�����ַ����������ַ����Ƿ����
    //
    // ����getOneSources()������
    // �����ض���
    // ���sourceΪ��
    // ���source��Ϊ�գ�sources������sources�ַ�
	// �ж��Ƿ����
	//    
	// ����getOneTargets()������
    // �����ض���
    // ���targetΪ��
    // ���target��Ϊ�գ�targets������targets�ַ�
	// �ж��Ƿ����   
	//    
	// ����setSource()������
	// �ֿ�����weight����� : 0 , > 0
	// weightΪ0���source�Ƿ�ɾ��
	// weight > 0 , �����Ƿ���ӻ����
	// ��������ߵ�Ȩֵ��仯
	// ����previous weight�Ĳ���
	//    
	// ����setTarget()������
	// �ֿ�����weight����� : 0 , > 0
	// weightΪ0���target�Ƿ�ɾ��
	// weight > 0 , �����Ƿ���ӻ����
	// ��������ߵ�Ȩֵ��仯
	// ����previous weight�Ĳ���   
	//    
    // ����Vertex��toStiring()����
    // ����source,target,weight
    // �ж�����ַ�����ָ���ַ����Ƿ����
    //  
    // TODO tests for operations of Vertex
    @Test 
    public void testGetString() {
    	Vertex<String> vertex = new Vertex<>("v1");
  
    	assertEquals("Expected source of an edge", "v1" , vertex.getString());
    }
    
    @Test
    public void testGetOneSources() {
    	final Vertex<String> vertex1 = new Vertex<>("v1");
    	final Vertex<String> vertex2 = new Vertex<>("v2");
    	final Vertex<String> vertex3 = new Vertex<>("v3");
    	final int weight = 1;
    	final int num = 2;
    	
    	Map<String, Integer> sources = new HashMap<String, Integer>();
    	
    	/*���Կ�sources*/
    	assertEquals("Expected empty source",Collections.emptyMap(),sources);
    	
    	vertex1.setSource(vertex2.getString(), weight);
    	vertex1.setSource(vertex3.getString(), weight);
    	
    	/*sources�а����ĵ㼰��������*/
    	assertTrue("Excepted contained sources",vertex1.getOneSources().containsKey(vertex2.getString()));
    	assertTrue("Excepted contained sources",vertex1.getOneSources().containsKey(vertex3.getString()));
    	assertEquals("Excepted number of sources", num , vertex1.getOneSources().keySet().size());
    }
    
    @Test
    public void testGetOneTargets() {
    	final Vertex<String> vertex1 = new Vertex<>("v1");
    	final Vertex<String> vertex2 = new Vertex<>("v2");
    	final Vertex<String> vertex3 = new Vertex<>("v3");
    	final int weight = 1;
    	final int num = 2;
    	
    	Map<String, Integer> targets = new HashMap<String, Integer>();
    	
    	/*���Կ�sources*/
    	assertEquals("Excepted empty source",Collections.emptyMap(),targets);
    	
    	vertex1.setTarget(vertex2.getString(), weight);
    	vertex1.setTarget(vertex3.getString(), weight);
    	
    	/*targets�а����ĵ㼰��������*/
    	assertTrue("Expected contained targets",vertex1.getOneTargets().containsKey(vertex2.getString()));
    	assertTrue("Expected contained targets",vertex1.getOneTargets().containsKey(vertex3.getString()));
    	assertEquals("Expected number of targets", num , vertex1.getOneTargets().keySet().size());
    }
    
    @Test
    public void testSetSource() {
    	final Vertex<String> vertex1 = new Vertex<>("v1");
    	final Vertex<String> vertex2 = new Vertex<>("v2");
    	final Vertex<String> vertex3 = new Vertex<>("v3");
//    	final Vertex vertex4 = new Vertex("v4");
    	
    	final int weight = 1;
    	final int weight2 = 2;
    	final int weight0 = 0;
    	final int num = 2;
    	final int num2 = 1;
    	
    	assertNotEquals("Expected not a null string", null,vertex1.getString());
    	assertNotEquals("Expected not the same string", vertex2.getString(),vertex1.getString());
    	
    	/*add*/
    	final int pre_weight = vertex1.setSource(vertex2.getString(), weight);
    	assertEquals("Expected no previous weight", weight0, pre_weight);
    	
    	vertex1.setSource(vertex3.getString(), weight);
//    	vertex4.setSource(vertex3.getString(), weight);
	
//    	assertEquals("Expected correctly previous weight", weight, pre_weight);
    	assertEquals("Expected number of sources", num , vertex1.getOneSources().keySet().size());
    	assertTrue("Excepted contained sources",vertex1.getOneSources().containsKey(vertex2.getString()));
    	assertTrue("Excepted contained sources",vertex1.getOneSources().containsKey(vertex3.getString()));
    	
    	/*update*/
    	vertex1.setSource(vertex2.getString(), weight2);
    	assertEquals("Expected an updated weight",(Integer)weight2,vertex1.getOneSources().get(vertex2.getString()));
    	
    	/*remove*/
    	vertex1.setSource(vertex2.getString(),weight0);
    	assertEquals("Expected a decrese of quantity", num2,vertex1.getOneSources().keySet().size());
    	assertFalse("Expected removement of a source",vertex1.getOneSources().containsKey(vertex2.getString()));	
    }
    
    @Test
    public void testSetTarget() {
    	final Vertex<String> vertex1 = new Vertex<>("v1");
    	final Vertex<String> vertex2 = new Vertex<>("v2");
    	final Vertex<String> vertex3 = new Vertex<>("v3");
    	final int weight = 1;
    	final int weight2 = 2;
    	final int weight0 = 0;
    	final int num = 2;
    	final int num2 = 1;
    	
    	assertNotEquals("Expected not a null string", null,vertex1.getString());
    	assertNotEquals("Expected not the same string", vertex2.getString(),vertex1.getString());
    	
    	/*add���Ҳ���pre_weight*/
    	final int pre_weight = vertex1.setTarget(vertex2.getString(), weight);
    	assertEquals("Expected no previous weight", weight0, pre_weight);
    	
    	vertex1.setTarget(vertex3.getString(), weight);
//    	assertEquals("Expected correctly previous weight", weight, pre_weight);
    	
    	assertEquals("Expected number of sources", num , vertex1.getOneTargets().keySet().size());
    	assertTrue("Excepted contained sources",vertex1.getOneTargets().containsKey(vertex2.getString()));
    	assertTrue("Excepted contained sources",vertex1.getOneTargets().containsKey(vertex3.getString()));
    	
    	/*update*/
    	vertex1.setTarget(vertex2.getString(), weight2);
    	assertEquals("Expected an updated weight",(Integer)weight2,vertex1.getOneTargets().get(vertex2.getString()));
    	
    	/*remove*/
    	vertex1.setTarget(vertex2.getString(),weight0);
    	assertEquals("Expected a decrese of quantity", num2,vertex1.getOneTargets().keySet().size());
    	assertFalse("Expected removement of a source",vertex1.getOneTargets().containsKey(vertex2.getString()));	
    }
    
    @Test
    public void testVertexToString() {
    	final Vertex<String> vertex1 = new Vertex<>("v1");
    	final Vertex<String> vertex2 = new Vertex<>("v2");
    	final int weight = 1;
    	
    	vertex1.setTarget(vertex2.getString(), weight);
    	assertEquals("Expected string of an edge", "v1->v2:1",vertex1.toString());
    }
    
    
    
}
