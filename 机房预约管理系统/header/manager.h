#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include "identity.h"
#include "globalFile.h"
#include "teacher.h"
#include "student.h"
#include "computerRoom.h"
class Manager :public Identity
{
public:
	Manager();
	Manager(std::string name,std::string pwd);
	//添加账号
	void addAccount();
	//查看账号
	void showAccount();
	//查看机房
	void showComputerRoom();
	//清空预约
	void cleanReserve();
	//操作菜单
	void operMenu();

	//初始化容器
	void initVector();
	//检查账号是否重复
	bool checkRepeate(int id,int type);
	//存放学生账号容器
	std::vector<Student> vStu;
	std::vector<Teacher> vTea;
	//机房信息
	std::vector<ComputerRoom> vCom;
};