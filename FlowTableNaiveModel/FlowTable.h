#pragma once

#include "uniform.h"
#include "FlowRedBlackTree.h"
#include "FlowEqual.h"
#include "FlowComparator.h"
#include "SCBF.h"
#include <vector>

using namespace std;

class FlowTable
{
private:
	ULONG size;
	FlowEqual flowEqual;
	FlowComparator flowComparator;
	SCBF * scbf;

public:
	FlowTable(UINT,SCBF *);
	FlowTable();
	~FlowTable();

	ULONG find(const FlowID &,PFlow &);
	bool insert(Flow *);
	void free();

	ULONG getFlowNum();
	ULONG timeoutScan(Time);

	void setMask(const FlowID&);

protected:
	USHORT calcHash(const FlowID&);

protected:
	UINT HASH_LEN;
	vector<FlowRedBlackTree *> m_pHashTable;

public:
	FlowID mask;		//��ǰԪ���Ӧ������
	ULONG ulPktNum;		//��ǰԪ����ʴ���
	Time tLastPkt;		//���һ�η��������ʱ��
};

