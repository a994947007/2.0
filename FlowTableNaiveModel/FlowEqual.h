#pragma once
#include "Equal.h"
#include "uniform.h"


class FlowEqual : public Equal<Flow *>
{
public:
	//�Ƚ��������Ƿ����
	bool equals(Flow *, Flow *);
};

