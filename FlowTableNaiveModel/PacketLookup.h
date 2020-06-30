#pragma once

#include "uniform.h"
#include "HashTable.h"
#include "SCBF.h"

#include <list>
#include <fstream>

using namespace std;

//�����������
static const USHORT MASK_NUM_ROOT = 4;
static const USHORT MASK_NUM = MASK_NUM_ROOT * MASK_NUM_ROOT;
static const USHORT MASK_PROTO = 0xff;
static const USHORT MASK_PORT = 0x8000;

//��������
static const UINT MASK_LIST[] = { 0xff000000,0xfff00000,0xffff0000,0xffffff00 };

/* �û�������Ϣ */
typedef struct UserConfig
{
	list<CString> fileList;
	CString resultPath;
	UINT	uiHashLen;	//�����ϣ����
	ULONG	cbfCountersLen;		//CBF���������鳤��
	ULONG	scbfCountersLen;	//SCBF���������鳤��
	ULONG	scbfInitCapacity;	//SCBF��ʼ���������鼫������
	ULONG	benignPktNum;		//���԰�ռ��
	ULONG	attackPktNum;		//�����ռ��
	ULONG	attackStartTime;	//������ʼʱ��
	ULONG	attackEndTime;		//��������ʱ��
	UserConfig() : uiHashLen(0)
	{

	}
	~UserConfig()
	{

	}
}UserConfig, *pUserConfig;

class PacketLookup
{
public:
	PacketLookup(const UserConfig &);
	virtual ~PacketLookup();

	void LookupTestProc(const UserConfig &);

protected:
	bool Initialize(const UserConfig &);
	bool GetPacket(Packet &);
	bool GetPacket(Packet &, ULONG,ULONG);
	bool GetNormalPacket(Packet &);		
	bool GetAttackPacket(Packet &);
	bool ReadPacket(ifstream &, Packet &);

	bool MaskProbeNaive(const Packet &);
	bool MaskProbeCBF(const Packet &);
	bool MaskProbeSCBF(const Packet &);

	const FlowID CalcFlowID(UCHAR, const EndID &, const EndID &);
	Flow*	NewFlow(const Packet &, const FlowID &);
	Flow *	NewSCFlow(const Packet &, const FlowID &);
	UINT	GetIpMask(UINT ip);
	bool	UpdateFlow(Flow *, const Packet &, const FlowID &);
	bool	WriteResult(bool, const UserConfig &);
	ULONG	GetFlowNum(HashTable **);

protected:
	list<ifstream *> m_fileStream;		//TRACE�ļ���
	SCBF * filter2017[MASK_NUM], * filter2019[MASK_NUM];
	HashTable * m_tableNaive[MASK_NUM], * m_tableCBF[MASK_NUM],* m_tableSCBF[MASK_NUM];	

	ULONG m_ulLookupNum,m_ulLookupLenNaive,m_ulLookupLenSCBF,m_ulLookupLenCBF;
	ULONG m_ulProbeNumNaive, m_ulProbeNumSCBF, m_ulProbeNumCBF;

	ULONG m_ulCBFFindNum,m_ulSCBFFindNum,m_ulCBFErrorNum,m_ulSCBFErrorNum;
};

