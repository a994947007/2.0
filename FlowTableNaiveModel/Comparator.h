#pragma once
template<typename E>

//外部比较器，用于比较元素的大小
class Comparator
{
public:
	virtual int compare(E e1,E e2) = 0;
};

