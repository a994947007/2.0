#pragma once
#include "uniform.h"
#include "Comparator.h"
class FlowComparator : public Comparator<Flow *>
{
public:
	int compare(Flow* f1, Flow* f2);
};

