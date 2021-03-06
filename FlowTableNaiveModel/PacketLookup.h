#pragma once

#include "uniform.h"
#include "HashTable.h"
#include "SCBF.h"
#include "FlowTable.h"

#include <list>
#include <fstream>

using namespace std;

//掩码数组参数
static const USHORT MASK_NUM_ROOT = 4;
static const USHORT MASK_NUM = MASK_NUM_ROOT * MASK_NUM_ROOT;
static const USHORT MASK_PROTO = 0xff;
static const USHORT MASK_PORT = 0x8000;

//掩码数组
static const UINT MASK_LIST[] = { 0xff000000,0xfff00000,0xffff0000,0xffffff00 };

/* 用户配置信息 */
typedef struct UserConfig
{
	list<CString> fileList;
	CString resultPath;
	UINT	uiHashLen;	//流表哈希长度
	ULONG	cbfCountersLen;		//CBF计数器数组长度
	ULONG	scbfCountersLen;	//SCBF计数器数组长度
	ULONG	scbfInitCapacity;	//SCBF初始计数器数组极限容量
	ULONG	benignPktNum;		//良性包占比
	ULONG	attackPktNum;		//恶意包占比
	ULONG	attackStartTime;	//攻击开始时间
	ULONG	attackEndTime;		//攻击结束时间
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
	ULONG	GetFlowNum(FlowTable **);

protected:
	list<ifstream *> m_fileStream;		//TRACE文件流
	SCBF * filter2017[MASK_NUM], * filter2019[MASK_NUM];
	HashTable * m_tableNaive[MASK_NUM], * m_tableCBF[MASK_NUM];	
	FlowTable * m_tableSCBF[MASK_NUM];

	ULONG m_ulLookupNum,m_ulLookupLenNaive,m_ulLookupLenSCBF,m_ulLookupLenCBF;
	ULONG m_ulProbeNumNaive, m_ulProbeNumSCBF, m_ulProbeNumCBF;

	ULONG m_ulCBFFindNum,m_ulSCBFFindNum,m_ulCBFErrorNum,m_ulSCBFErrorNum;
};

