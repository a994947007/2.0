#pragma once
#include "Equal.h"
#include "uniform.h"


class FlowEqual : public Equal<Flow *>
{
public:
	//比较两条流是否相等
	bool equals(Flow *, Flow *);
};

