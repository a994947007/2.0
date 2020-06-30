#pragma once

#include "uniform.h"
#define H3_HASH_NUM 6

/*SCBF�������������ṹ*/
typedef struct SCNode {
	ULONG h3_row;			//��ӦH3���������
	ULONG limit_capacity;	//�������
	ULONG current_capacity;	//��ǰ����
	UCHAR * m_pCounters;	//�����������׵�ַ
	struct SCNode * next;
	SCNode(ULONG h3_row, ULONG limit_capacity) :h3_row(h3_row), limit_capacity(limit_capacity), current_capacity(0), next(NULL) {
		m_pCounters = new UCHAR[(ULONG)pow(2, h3_row)];
		memset(m_pCounters, 0, ((ULONG)pow(2, h3_row)) * sizeof(UCHAR));
	}
	~SCNode() {
		if (m_pCounters) delete m_pCounters;
	}
}SCNode, *PSCNode;

typedef struct SCFlow :public Flow {
	PSCNode pSCNode;
	SCFlow() :pSCNode(NULL) {}
}SCFlow;


class SCBF
{
protected:
	typedef struct H3_Matrix {
		ULONG col[32];
	}H3_Matrix;

protected:
	H3_Matrix h3_matrix[H3_HASH_NUM];
	SCNode * first_node;

public:
	SCBF(ULONG h3_row, ULONG limit_capacity);	//��һ��CBF��������������ϣ���������
	bool init_h3_matrix();					//��ʼ����ϣ��������
	bool filter_insert(SCFlow &);		//����һ������������
	bool filter_query(const FlowID &);		//���Ҽ������Ƿ���ڿ�ƥ�����ID
	bool filter_delete(const SCFlow &);		//��SCBF��ɾ����Ӧ����ID
	ULONG h3_function(const ULONG h3_row, const ULONG h3_hash, const int matrix_index);//h3��ϣ����
	SCNode * lookup_spare_scNode();			//������������ĿС����������Ľ��
	virtual ~SCBF();
};

