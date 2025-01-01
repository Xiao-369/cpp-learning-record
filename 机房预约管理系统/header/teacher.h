#pragma once
#include<iostream>
#include<vector>
#include "identity.h"
#include "orderFile.h"
class Teacher :public Identity
{
public:
	//构造函数
	Teacher();
	Teacher(int empId,std::string name,std::string pwd);
	//操作菜单
	void operMenu();
	//查看所有预约
	void showAllOrder();
	//审核预约
	void validOrder();
	int m_EmpId; //教师编号
	std::vector<int> m_vIndex;
};
