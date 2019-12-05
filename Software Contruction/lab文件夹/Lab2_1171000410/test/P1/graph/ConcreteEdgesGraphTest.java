/* Copyright (c) 2015-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P1.graph;

import static org.junit.Assert.*;

import org.junit.Test;

/**
 * Tests for ConcreteEdgesGraph.
 * 
 * This class runs the GraphInstanceTest tests against ConcreteEdgesGraph, as
 * well as tests for that particular implementation.
 * 
 * Tests against the Graph spec should be in GraphInstanceTest.
 */
public class ConcreteEdgesGraphTest extends GraphInstanceTest {

	/*
	 * Provide a ConcreteEdgesGraph for tests in GraphInstanceTest.
	 */
	@Override
	public Graph<String> emptyInstance() {
		return new ConcreteEdgesGraph<>();
	}

	/*
	 * Testing ConcreteEdgesGraph...
	 */

	// Testing strategy for ConcreteEdgesGraph.toString()
	// ��GraphΪ�յ�ʱ��
	// ��Graph��Ϊ�յ�ʱ��
	// ƥ��string���ж��Ƿ����

	// TODO tests for ConcreteEdgesGraph.toString()
	@Test
	public void testToString() {
		Graph<String> graph = emptyInstance();

		/* ���Կ�Graph */
		assertEquals("Expected an empty graph", "This is An Empty Graph", graph.toString());

		final String vertex1 = "v1";
		final String vertex2 = "v2";
		final String vertex3 = "v3";
		final int weight = 1;
		graph.set(vertex1, vertex2, weight);
		graph.set(vertex2, vertex3, weight);
		assertEquals("Expected string of graph", "v1->v2:1" + "\n" + "v2->v3:1" + "\n", graph.toString());
	}

	/*
	 * Testing Edge...
	 */

	// Testing strategy for Edge
	// ����ʵ�ֵĹ������ƶ���Ӧ��test
	//
	// ����getSource()����:
	// �����ض�edge
	// ����source
	// �ж��Ƿ�ƥ��
	//
	// ����getTarget()����:
	// �����ض�edge
	// ����target
	// �ж��Ƿ�ƥ��
	//
	// ����getWeight()����:
	// �����ض�edge
	// ����weight
	// �ж��Ƿ�ƥ��
	//
	// ����Edge���toString()������
	// ����ָ���ı�
	// �ж��ַ����Ƿ���ָ���ַ������
	//
	// ����equals()������
	// ���ö�����
	// ��ȣ����Լ�����������
	// ���ȣ�source,target,weight���ڲ����
	//
	// ����hashCode()������
	// ��ȣ�this��that���
	// ����ȣ�this��that�����
	//
	// TODO tests for operations of Edge

	@Test
	public void testGetSource() {
		final String vertex1 = "v1";
		final String vertex2 = "v2";
		final int weight = 1;

		Edge<String> edge = new Edge<>(vertex1, vertex2, weight);
		assertEquals("Expected source of an edge", vertex1, edge.getSource());
	}

	@Test
	public void testGetTarget() {
		final String vertex1 = "v1";
		final String vertex2 = "v2";
		final int weight = 1;
//		final int weight2 = -1;
//		try {
//			Edge<String> edge2 = new Edge<>(vertex1, vertex2, weight2);
//		} catch (AssertionError e) {
//		}

		Edge<String> edge = new Edge<>(vertex1, vertex2, weight);
		assertEquals("Expected source of an edge", vertex2, edge.getTarget());
	}

	@Test
	public void testGetWeight() {
		final String vertex1 = "v1";
		final String vertex2 = "v2";
		final int weight = 1;

		Edge<String> edge = new Edge<>(vertex1, vertex2, weight);
		assertEquals("Expected source of an edge", weight, edge.getWeight());
	}

	@Test
	public void testEdgeToString() {
		final String vertex1 = "v1";
		final String vertex2 = "v2";
		final int weight = 1;

		Edge<String> edge = new Edge<>(vertex1, vertex2, weight);
		assertEquals("Expected string of an edge", "v1->v2:1", edge.toString());
	}

	@Test
	public void testEquals() {
		final String vertex1 = "v1";
		final String vertex2 = "v2";
		final String vertex3 = "v3";
		final int weight1 = 1;
		final int weight2 = 2;

		Edge<String> edge1 = new Edge<>(vertex1, vertex2, weight1);
		Edge<String> edge2 = new Edge<>(vertex1, vertex2, weight1);
		Edge<String> edge3 = new Edge<>(vertex3, vertex2, weight1);
		Edge<String> edge4 = new Edge<>(vertex1, vertex3, weight1);
		Edge<String> edge5 = new Edge<>(vertex1, vertex2, weight2);

		/* ����� */
		assertTrue("Expected the same edge", edge1.equals(edge1));
		assertTrue("Expected equal edges", edge1.equals(edge2));

		/* source,target,weight�ֱ���� */
		assertFalse("Expected unequal edges", edge1.equals(edge3));
		assertFalse("Expected unequal edges", edge1.equals(edge4));
		assertFalse("Expected unequal edges", edge1.equals(edge5));
	}

	@Test
	public void testHashCode() {
		final String vertex1 = "v1";
		final String vertex2 = "v2";
		final String vertex3 = "v3";
		final int weight1 = 1;
		final int weight2 = 2;

		Edge<String> edge1 = new Edge<>(vertex1, vertex2, weight1);
		Edge<String> edge2 = new Edge<>(vertex1, vertex2, weight1);
		Edge<String> edge3 = new Edge<>(vertex1, vertex3, weight2);

		assertEquals("Expected equal hashcode", edge1.hashCode(), edge2.hashCode());
		assertNotEquals("Expected unequal hashcode", edge1.hashCode(), edge3.hashCode());
	}

}
