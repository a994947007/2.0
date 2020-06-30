#include "stdafx.h"
#include "HashFunctions.h"
#include "FlowTable.h"

FlowTable::FlowTable(UINT uiLen,SCBF * scbf) :HASH_LEN(uiLen), ulPktNum(0), tLastPkt(0, 0),scbf(scbf)
{
	for (ULONG i = 0; i < HASH_LEN; i++)
	{
		FlowRedBlackTree * p = new FlowRedBlackTree(&flowComparator,&flowEqual,scbf);
		if (NULL == p)
		{
			break;
		}
		m_pHashTable.push_back(p);
	}
}

FlowTable::FlowTable()
{
	this->tLastPkt = Time(0);
	this->ulPktNum = 0;
}

FlowTable::~FlowTable()
{
	free();
	for (ULONG i = 0; i < HASH_LEN; i++)
	{
		delete m_pHashTable[i];
		m_pHashTable[i] = NULL;
	}
}

ULONG FlowTable::find(const FlowID& fid, PFlow & pNode)
{
	FlowID key = (FlowID)fid & mask;
	USHORT usPos = calcHash(key);
	Flow temp;
	temp.key = key;
	temp.mask = mask;
	ULONG len = m_pHashTable[usPos]->find(&temp, pNode);
	return len;
}

bool FlowTable::insert(Flow * flow)
{
	USHORT  usPos = calcHash(flow->key);
	m_pHashTable[usPos]->add(flow);
	return true;
}

void FlowTable::free()
{
	for (UINT i = 0; i < HASH_LEN; i++)
	{
		m_pHashTable[i]->clear();
	}
}

ULONG FlowTable::getSize()
{
	ULONG size = 0;
	for (UINT i = 0; i < HASH_LEN; i++)
	{
		size += m_pHashTable[i]->getSize();
	}
	return size;
}

ULONG FlowTable::timeoutScan(Time t)
{
	ULONG len = 0;
	for (UINT i = 0; i < HASH_LEN; i++)
	{
		len += m_pHashTable[i]->timeoutScan(t);
	}
	return len;
}

void FlowTable::setMask(const FlowID& mask)
{
	this->mask = mask;
}

USHORT FlowTable::calcHash(const FlowID & key)
{
	UCHAR buf[FID_LEN];
	((FlowID*)&key)->ToData(buf);
	return XOR16(buf, FID_LEN) % HASH_LEN;
}
