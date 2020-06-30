#include "stdafx.h"
#include "FlowComparator.h"

int FlowComparator::compare(Flow * f1, Flow* f2)
{
	if (f1->key.src.ip > f2->key.src.ip) {
		return 1;
	}
	else if(f1->key.src.ip < f2->key.src.ip){
		return -1;
	}
	else {
		return 0;
	}
}
