#pragma once

//�Ƚ�����Ԫ���Ƿ���ȵĽӿ�
template <class T>
class Equal {
public:
	virtual bool equals(T t1, T t2) = 0;
};