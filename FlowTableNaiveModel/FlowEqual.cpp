#include "stdafx.h"
#include "FlowEqual.h"


bool FlowEqual::equals( Flow * f1, Flow * f2)
{
	return f1->mask == f2->mask && f1->key == f2->key;
}
