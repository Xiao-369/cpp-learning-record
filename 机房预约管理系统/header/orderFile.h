#pragma once
#include<fstream>

#include<map>
#include "globalFile.h"

//头文件重复包含
class Student;
class OrderFile
{
public:
	OrderFile();
	OrderFile(int date,Student* stu, int interval, int roomId, int status);
	//写入文件
	void writeFile();
	//初始化容器
	void loadFile();
	//更新文件
	void updateFile();
	int m_date;
	int m_interval;
	Student* m_stu;
	int m_roomId;
	int m_status;
	//存放文件信息容器
	std::map<int,std::map<std::string,std::string>> m_orderFile;
};