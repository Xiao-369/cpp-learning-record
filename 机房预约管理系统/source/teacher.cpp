#include "../header/teacher.h"

//构造函数
Teacher::Teacher(){}
Teacher::Teacher(int empId, std::string name, std::string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}
//操作菜单
void Teacher::operMenu()
{
	std::cout << "欢迎教师" << this->m_Name << "登录！" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         1，查看所有预约                =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         2，审核预约                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         0，注销登录                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "请输入你的选择：";
}
//查看所有预约
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_orderFile.size() == 0)
	{
		std::cout << "当前没有预约记录！" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_orderFile.size();i++)
	{
		std::cout << i + 1 << "，";
		std::cout << "预约时间：周" << of.m_orderFile[i]["date"] << "\t";
		std::cout << "预约时间段：" << (of.m_orderFile[i]["interval"]=="1" ?"上午":"下午") << "\t";
		std::cout << "学生编号：" << of.m_orderFile[i]["stuId"] << "\t";
		std::cout << "学生姓名:" << of.m_orderFile[i]["stuName"] << "\t";
		std::cout << "机房编号：" << of.m_orderFile[i]["roomId"] << "\t";
		std::string status = "状态：";
		if (of.m_orderFile[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderFile[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderFile[i]["status"] == "-1")
		{
			status += "预约失败";
		}
		else
		{
			status += "取消预约";
		}
		std::cout << status << std::endl;
	}
	system("pause");
	system("cls");
}
//审核预约
void Teacher::validOrder()
{
	this->m_vIndex.clear();
	OrderFile of;
	int index = 1;
	int flag = true;
	for (int i = 0;i < of.m_orderFile.size();i++)
	{
		if (of.m_orderFile[i]["status"] == "1")
		{
			flag = false;
			this->m_vIndex.push_back(i);
			std::cout << index++ << "，";
			std::cout << "预约时间：周" << of.m_orderFile[i]["date"] << "\t";
			std::cout << "预约时间段：" << (of.m_orderFile[i]["interval"] == "1" ? "上午" : "下午") << "\t";
			std::cout << "学生编号：" << of.m_orderFile[i]["stuId"] << "\t";
			std::cout << "学生姓名:" << of.m_orderFile[i]["stuName"] << "\t";
			std::cout << "机房编号：" << of.m_orderFile[i]["roomId"] << "\t";
			std::cout << "审核中" << std::endl;
		}
	}
	if (flag)
	{
		std::cout << "当前没有预约记录！" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "请选择你要操作的编号：";
	int choice;
	std::cin >> choice;

	std::cout << "1，审核通过" << std::endl;
	std::cout << "2，审核不通过" << std::endl;
	std::cout << "请输入你的选择：";
	int select;
	std::cin >> select;
	if (select == 1)
	{
		of.m_orderFile[this->m_vIndex[choice - 1]]["status"] = "2";
	}
	else
	{
		of.m_orderFile[this->m_vIndex[choice - 1]]["status"] = "-1";

	}
	std::cout << "操作成功！" << std::endl;
	of.updateFile();
	system("pause");
	system("cls");
}