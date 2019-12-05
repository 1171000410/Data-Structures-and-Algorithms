/* Copyright (c) 2015-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P1.graph;

import java.util.ArrayList;
import java.util.Collections;
//import java.util.Collection;
//import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
//import java.util.stream.Collector;
//import java.util.stream.Collectors;
//import java.util.stream.Collectors;

//import javax.swing.text.StyledEditorKit.BoldAction;

/**
 * An implementation of Graph.
 * 
 * <p>
 * PS2 instructions: you MUST use the provided rep.
 */
public class ConcreteEdgesGraph<L> implements Graph<L> {

	private final Set<L> vertices = new HashSet<>();
	private final List<Edge<L>> edges = new ArrayList<>();

	// Abstraction function:
	// ͨ����graph�бߺ͵�ĳ���
	// �ߵ����а�����source,target,weight
	// ������ı�
	// ��������ͼ
	//
	// Representation invariant:
	// ������������������ѧ��ϵ
	// n���㣬��๹��n*(n-1)/2�������
	//
	// Safety from rep exposure:
	// �ڿɲ���������£����еı���������Ϊprivate , final
	// ����ͱ���mutable����, ��˶ദʹ�ã�����ʽ����
	// ʹ��Collections.unmodifiableSet�ȷ���

	// TODO constructor

	// TODO checkRep


	public ConcreteEdgesGraph() {
	}

	/*checkRep ������n*(n-1)/2 �����Ƴ����ٶ���*/
	private void checkRep() {
//    	int minVertices = 0;
//    	if(edges.size() == 0) {
//    		minVertices = 0;
//    	}else {
//    		minVertices = (int)(Math.ceil(Math.sqrt(2*edges.size() + 0.25) + 0.5));
//    	}
//    	assert vertices.size() >= minVertices;

		int maxEdges = 0;
		if (vertices.size() == 0) {
			maxEdges = 0;
		} else {
			maxEdges = vertices.size() * (vertices.size() - 1) / 2;
		}
		assert edges.size() <= maxEdges;

	}

	@Override
	public boolean add(L vertex) {
		return vertices.add(vertex);
	}

	/**
	 * My method findEdge ��Ϊ���ҵ�list�Ƿ����һ��ָ���ı� �ñߵ�source��target�����봫��Ĳ������
	 * 
	 * @param source which is to be compared with
	 * @param target which is to be compared with
	 * @return index of the edge -1 if the edge is not found
	 */
	private int findEdge(L source, L target) {
		for (int i = 0; i < edges.size(); i++) {
			Edge<L> one = edges.get(i);
			if (one.getSource().equals(source) && one.getTarget().equals(target)) {
				return i; // �ҵ��˷�����list��λ��
			}
		}
		return -1; // û�ҵ�����-1
	}

	@Override
	public int set(L source, L target, int weight) {
		assert weight >= 0;
		int index = findEdge(source, target);
		int pre_weight = 0;
		Edge<L> edge = new Edge<L>(source, target, weight);
		Edge<L> pre_edge;

		if (weight > 0) {
			if (index < 0) { // û�ҵ��ñ�
				add(source);
				add(target);
				edges.add(edge);
			} else {
				pre_edge = edges.set(index, edge); // ����Ԫ��,��������ǰ��Ԫ��
				pre_weight = pre_edge.getWeight();
			}
		} else if (weight == 0 && index >= 0) { // ɾ��
			pre_edge = edges.remove(index);
			pre_weight = pre_edge.getWeight();
		}
		checkRep();
		return pre_weight;

	}

	@Override
	public boolean remove(L vertex) {
		if (!vertices().contains(vertex)) {
			return false;
		}
		for (int i = 0; i < edges.size(); i++) { // ɾ����õ���صı�
			if (edges.get(i).getSource().equals(vertex) || edges.get(i).getTarget().equals(vertex)) {
				edges.remove(edges.get(i));
			}
		}
		vertices.remove(vertex); // ɾ���õ�
		checkRep();
		return true;
	}

	@Override
	public Set<L> vertices() {
		return Collections.unmodifiableSet(vertices); // immutable type
	}

	@Override
	public Map<L, Integer> sources(L target) {
		assert target != null;
		Map<L, Integer> map = new HashMap<L, Integer>();
		for (Edge<L> edge : edges) {
			if (edge.getTarget().equals(target)) {
				map.put(edge.getSource(), edge.getWeight());
			}
		}
		return map;
//		return edges.stream()
//				.filter(edge -> edge.getTarget().equals(target))
//				.collect(Collectors.toMap(Edge::getSource, Edge::getWeight));
	}

	@Override
	public Map<L, Integer> targets(L source) {
		assert source != null;
		Map<L, Integer> map = new HashMap<L, Integer>();
		for (Edge<L> edge : edges) {
			if (edge.getSource().equals(source)) {
				map.put(edge.getTarget(), edge.getWeight());
			}
		}
		return map;
//		return edges.stream()
//		.filter(edge -> edge.getSource().equals(source))
//		.collect(Collectors.toMap(Edge::getTarget, Edge::getWeight));
	}

	// TODO toString()

	@Override
	public String toString() {
		if (edges.isEmpty()) {
			return "This is An Empty Graph";
		}
		String stringGraph = "";
		for (int i = 0; i < edges.size(); i++) {
			stringGraph = stringGraph.concat(edges.get(i).toString() + "\n");
		}
		return stringGraph;
	}

}

/**
 * TODO specification Immutable. This class is internal to the rep of
 * ConcreteEdgesGraph.
 * 
 * <p>
 * PS2 instructions: the specification and implementation of this class is up to
 * you.
 */
class Edge <L>{

	// TODO fields
	private L source;
	private L target;
	private int weight;

	// Abstraction function:
	// �����˱�����߱ر��Ĳ���
	// source , target , ��Ȩֵweight
	//
	// Representation invariant:
	// source��target������null
	// weight >= 0
	//
	// Safety from rep exposure:
	// ����ʹ��private��final�������ڲ�����
	// ʹ��immutable��������
	//

	// TODO constructor
	public Edge(L source, L target, int weight) {
		this.source = source;
		this.target = target;
		this.weight = weight;
		checkRep();
	}

	// TODO checkRep
	public void checkRep() {
		assert source != null;
		assert target != null;
		assert weight >= 0;
	}
	// TODO methods

	// TODO toString()

	public L getSource() {
		return source;
	}

	public L getTarget() {
		return target;
	}

	public int getWeight() {
		return weight;
	}

	@Override
	public String toString() { // ���ǳ����toString����
		String s = this.getSource() + "->" + this.getTarget() + ":" + this.getWeight();
		return s;
	}

	/**
	 * �ж��������Ƿ���� ���ж��Ƿ���ͬһ����(�ڴ˷�������Ҫ) 
	 * ֮�����ж�һ�������Ƿ�����һ�������ʵ�� 
	 * ��������ж�source , target ,
	 * weight���Ƿ����
	 * 
	 * @param that edge to be compared
	 * @return true if they are the same edge ,else false
	 */
	@Override
	public boolean equals(Object that) { // ���ǳ����equals����
		if (that instanceof Edge) {
			if (getSource().equals(((Edge<?>) that).getSource()) && getTarget().equals(((Edge<?>) that).getTarget())
					&& getWeight() == (((Edge<?>) that).getWeight())) {
				return true;
			}
		}
		checkRep();
		return false;
	}

	/**
	 * ��дhashCode������
	 * 
	 * @return int hash address
	 */
	@Override
	public int hashCode() {
		int h = 1;
		h = 31 * h + getSource().hashCode();
		h = 31 * h + getTarget().hashCode();
		h = 31 * h + getWeight();
		return h;
	}

}
