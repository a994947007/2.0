#pragma once
template<typename E>

//�ⲿ�Ƚ��������ڱȽ�Ԫ�صĴ�С
class Comparator
{
public:
	virtual int compare(E e1,E e2) = 0;
};

