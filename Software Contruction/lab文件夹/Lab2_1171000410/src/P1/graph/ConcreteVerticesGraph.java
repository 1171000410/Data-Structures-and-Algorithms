/* Copyright (c) 2015-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P1.graph;

import java.util.ArrayList;
//import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
//import java.util.stream.Collectors;

/**
 * An implementation of Graph.
 * 
 * <p>
 * PS2 instructions: you MUST use the provided rep. û��������ʵ���ڵıߣ�ֻ�е�֮��Ķ�Ӧ��ϵ
 */
public class ConcreteVerticesGraph<L> implements Graph<L> {

	private final List<Vertex<L>> vertices = new ArrayList<>();

	// Abstraction function:
	// �������Ȩͼ����Ϊ�������
	// ��֮���ӳ���ϵΪ��
	// ����Ȩֵweight
	//
	// Representation invariant:
	// ÿ������ֻ�ܴ���һ��ʵ��
	// ��˶������vertices()�Ĵ�С���
	//
	// Safety from rep exposure:
	// ���������ܶ���Ϊprivate��final
	// ����ʽ���
	//
	// TODO constructor

	// TODO checkRep

	public ConcreteVerticesGraph() {
	}

	public void checkRep() {
		assert vertices().size() == vertices.size();
	}

	@Override
	public boolean add(L vertex) {
		if (vertices().contains(vertex)) {
			return false;
		} else {
			Vertex<L> v = new Vertex<>(vertex);
			vertices.add(v);
			return true;
		}
	}

	/**
	 * My method findVertex , �ҵ���Ӧstr��vertex���ڵ�λ��
	 * 
	 * @param str string of a vertex
	 * @return index of the vertex in vertices
	 */
	private int findVertex(L str) {
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices.get(i).getString().equals(str)) {
				return i;
			}
		}
		return -1;
	}

	@Override
	public int set(L source, L target, int weight) {
		assert weight >= 0;
		assert source != target;
		Vertex<L> vertexOfSource, vertexOfTarget;
		int index;

		if (vertices().contains(source)) {
			index = findVertex(source);
			vertexOfSource = vertices.get(index);
		} else { // ���string��Ӧ�ĵ㲻��list�У������µĵ㲢����ӽ�ȥ
			vertexOfSource = new Vertex<>(source);
			vertices.add(vertexOfSource);
		}

		if (vertices().contains(target)) {
			index = findVertex(target);
			vertexOfTarget = vertices.get(index);
		} else {
			vertexOfTarget = new Vertex<>(target);
			vertices.add(vertexOfTarget);
		}

		final int a1 = vertexOfSource.setTarget(target, weight); 
		final int a2 = vertexOfTarget.setSource(source, weight);
		assert a1 == a2;
		checkRep();
		return a1; // ����pre_weight
	}

	@Override
	public boolean remove(L vertex) {
		assert vertex != null;
		if (!vertices().contains(vertex)) {
			return false;
		}
		for(Vertex<L> one :vertices) {   //ɾ���������sources��targets
			if(one.getOneSources().containsKey(vertex)) {
				one.getOneSources().remove(vertex);
			}
			if(one.getOneTargets().containsKey(vertex)) {
				one.getOneTargets().remove(vertex);
			}
		}
//		for(Vertex one : vertices) {  //ɾ��û�����ӱߵĵ�
//			if(one.getOneSources().keySet().isEmpty() 
//					&& one.getOneTargets().keySet().isEmpty()) {
//				vertices().remove(one.getString());   //��set��ɾ��
//				vertices.remove(one);  //��list��ɾ��
//			}
//		}
		final int index = findVertex(vertex);
		vertices.remove(index);  
		return true;
	}

	@Override
	public Set<L> vertices() {
		Set<L> s = new HashSet<L>();
		for (Vertex<L> one : vertices) {
			s.add(one.getString());
		}
		return s;
	}

	@Override
	public Map<L, Integer> sources(L target) {
		assert target != null;
		int index = findVertex(target);
		if (index < 0) {
			return Collections.emptyMap();
		} else {
			return vertices.get(index).getOneSources();
		}
	}

	@Override
	public Map<L, Integer> targets(L source) {
		assert source != null;
		int index = findVertex(source);
		if (index < 0) {
			return Collections.emptyMap();
		} else {
			return vertices.get(index).getOneTargets();
		}
	}

	// TODO toString()
	@Override
	public String toString() {
		if (vertices.isEmpty()) {
			return "This is An Empty Graph";
		}
		String stringGraph = "";
		for (int i = 0; i < vertices.size(); i++) {
			if(vertices.get(i).toString() != "") {
			stringGraph = stringGraph.concat(vertices.get(i).toString()+"\n");
			}
		}
		return stringGraph;
	}

}

/**
 * TODO specification Mutable. This class is internal to the rep of
 * ConcreteVerticesGraph.
 * 
 * <p>
 * PS2 instructions: the specification and implementation of this class is up to
 * you.
 */

class Vertex<L> {

	// TODO fields
	private L str;
	private Map<L, Integer> oneSources = new HashMap<L, Integer>();
	private Map<L, Integer> oneTargets = new HashMap<L, Integer>();
	
	// Abstraction function:
	// ������̻�ͼ�Ĺؼ�Ҫ��
	// ʹ��HashMap��ȡӳ���ϵ
	// keyΪ�õ��source��target , valueΪ�õ��weight
	//
	// Representation invariant:
	// ÿ�������source��target����������
	// HashMap�е�values���벻С��0
	//
	// Safety from rep exposure:
	// ����fields��private final
	// String��imutable����
	// �����Ա��

	// TODO constructor

	// TODO checkRep

	// TODO methods

	// TODO toString()

	/*���캯��*/
	public Vertex(L str) {
		this.str = str;
	}

	/* ��鲻��������֤�õ㲻�����Լ���source����target��weight��С��0*/
	public void checkRep() {
		assert !oneSources.keySet().contains(this.str);
		assert !oneTargets.keySet().contains(this.str);
		for(Integer v1 : oneSources.values()) {
			assert v1 >=0;
		}
		for(Integer v2 : oneSources.values()) {
			assert v2 >=0;
		}
		
		
	}

	public L getString() {
		return this.str;
	}

	public Map<L, Integer> getOneSources() {
		return this.oneSources;
	}

	public Map<L, Integer> getOneTargets() {
		return this.oneTargets;
	}

	/**
	 * ���õ��õ��source������ͬConcreteVerticesGraph��set����
	 * weight = 0 , source���� ���Ƴ�
	 * weight > 0 , source���� ������ 
	 * weight > 0 , source������ �����
	 * 
	 * @param source ,weight of an edge
	 * @return pre_weight of pre_edge
	 */
	public int setSource(L source, int weight) {
		assert source != null;
		assert source != this.str; // ���غ�
		assert weight >= 0;

		int pre_weight = 0;

		if (weight == 0 && this.oneSources.keySet().contains(source)) { // remove
			pre_weight = oneSources.remove(source);
		}
		if (weight > 0 && this.oneSources.keySet().contains(source)) { // update
			pre_weight = oneSources.put(source, weight);
		}
		if (weight > 0 && !this.oneSources.keySet().contains(source)) { // add
			oneSources.put(source, weight);
			pre_weight = 0;
		}
		checkRep();
		return pre_weight;
	}

	/**
	 * ���õ��õ��target������ͬConcreteVerticesGraph��set����
	 * weight = 0 , target���� ���Ƴ�
	 * weight > 0 , target���� ������ 
	 * weight > 0 , target������ �����
	 * 
	 * @param target ,weight of an edge
	 * @return pre_weight of pre_edge
	 */
	public int setTarget(L target, int weight) {
		assert target != null;
		assert target != this.str; // ���غ�
		assert weight >= 0;

		int pre_weight = 0;

		if (weight == 0 && this.oneTargets.keySet().contains(target)) { // remove
			pre_weight = oneTargets.remove(target);
		}
		if (weight > 0 && this.oneTargets.keySet().contains(target)) { // update
			pre_weight = oneTargets.put(target, weight);
		}
		if (weight > 0 && !this.oneTargets.keySet().contains(target)) { // add
			oneTargets.put(target, weight);
			pre_weight = 0;
		}
		checkRep();
		return pre_weight;
	}

	@Override
	public String toString() {
		String str = "";
		for (L s : this.oneTargets.keySet()) {
			str = str.concat(this.getString() + "->" + s + ":" + this.oneTargets.get(s));
		}
		return str;
	}
}
