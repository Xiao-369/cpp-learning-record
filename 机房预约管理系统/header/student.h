#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include "identity.h"
#include "globalFile.h"
#include "computerRoom.h"
#include "orderFile.h"
class Student :public Identity
{
public:
	void showMyOrder();
	//构造函数
	Student();
	Student(int stuId,std::string name,std::string pwd);
	//操作菜单
	void operMenu();
	//申请预约
	void applyReserve();
	//查看我的预约
	void showMyReserve();
	//查看所有预约
	void showAllReserve();
	//取消预约
	void cancelReserve();
	//初始化容器
	void initVector();
	int m_StuId;
	//机房信息
	std::vector<ComputerRoom> vCom;
	//存放自己预约记录的编号
	std::vector<int> vIndex;
};