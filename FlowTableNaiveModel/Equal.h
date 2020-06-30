#pragma once

//比较两个元素是否相等的接口
template <class T>
class Equal {
public:
	virtual bool equals(T t1, T t2) = 0;
};