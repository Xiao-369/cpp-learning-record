#include "../header/student.h"

//构造函数
Student::Student(){}
Student::Student(int stuId, std::string name, std::string pwd)
{
	this->m_StuId = stuId;
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();
	std::ifstream ifs;
	ifs.open(COMPUTERROOM_FILE, std::ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();
}
//操作菜单
void Student::operMenu()
{
	std::cout << "欢迎学生" << this->m_Name << "登录！" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         1，申请预约                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         2，查看我的预约                =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         3，查看所有预约                =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         4，取消预约                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         0，注销登录                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "请输入你的选择：";
}

//申请预约
void Student::applyReserve()
{
	int date; //时间
	int interval; // 时间段
	int room;//机房编号
	std::cout << "机房开放预约时间为星期一到星期五" << std::endl;
	std::cout << "请输入申请预约时间：" << std::endl;
	std::cout << "1，周一" << std::endl;
	std::cout << "2，周二" << std::endl;
	std::cout << "3，周三" << std::endl;
	std::cout << "4，周四" << std::endl;
	std::cout << "5，周五" << std::endl;
	while (true)
	{
		std::cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		std::cout << "输入有误！请重新输入" << std::endl;
	}
	std::cout << "请输入申请预约时间段：" << std::endl;
	std::cout << "1，上午" << std::endl;
	std::cout << "2，下午" << std::endl;
	while (true)
	{
		std::cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		std::cout << "输入有误！请重新输入" << std::endl;
	}
	std::cout << "请选择机房" << std::endl;
	for (int i = 0;i < vCom.size();i++)
	{
		std::cout << vCom[i].m_ComId << "号机房容量：" << vCom[i].m_MaxNum << std::endl;
	}
	while (true)
	{
		std::cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		std::cout << "输入有误！请重新输入" << std::endl;
	}
	std::cout << "预约成功，审核中！" << std::endl;

	OrderFile of(date, this, interval, room, 1);
	of.writeFile();
	system("pause");
	system("cls");
}
//查看自己预约记录
void Student::showMyOrder()
{
	this->initVector();
	OrderFile of;
	int index = 1;
	for (int i = 0;i < of.m_orderFile.size();i++)
	{
		//过滤出自己的预约记录
		if (atoi(of.m_orderFile[i]["stuId"].c_str()) == this->m_StuId)
		{
			this->vIndex.push_back(i);
			std::cout << index++ << "，";
			std::cout << "预约日期：周" << of.m_orderFile[i]["date"] << "\t";
			std::cout << "预约时间段：" << of.m_orderFile[i]["interval"] << "\t";
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
	}
}
//查看我的预约
void Student::showMyReserve()
{
	showMyOrder();
	system("pause");
	system("cls");
}
//查看所有预约
void Student::showAllReserve()
{
	OrderFile of;
	int index = 1;
	for (std::map<int, std::map<std::string, std::string>>::iterator it = of.m_orderFile.begin();
		it != of.m_orderFile.end();it++)
	{
		std::cout << index++ << "，";
		std::cout << "预约日期：周" << it->second["date"] << "\t";
		std::cout << "预约时间段：" << it->second["interval"] << "\t";
		std::cout << "学生编号：" << it->second["stuId"] << "\t";
		std::cout << "学生姓名：" << it->second["stuName"] << "\t";
		std::cout << "机房编号：" << it->second["roomId"] << "\t";
		std::string status = "状态：";
		if (it->second["status"] == "1")
		{
			status += "审核中";
		}
		else if (it->second["status"] == "2")
		{
			status += "预约成功";
		}
		else if (it->second["status"] == "-1")
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
//取消预约
void Student::cancelReserve()
{

	OrderFile of;
	std::cout << "只能取消审核中或者预约成功的记录" << std::endl;
	showMyOrder();
	std::cout << "请输入你要取消记录的编号：";
	int select;
	
	while (true)
	{
		std::cin >> select;
		if (select > 0 || select < of.m_orderFile.size())
		{
			break;
		}
		std::cout << "编号有误！请重新输入" << std::endl;
	}
	of.m_orderFile[vIndex[select - 1]]["status"] = "0";
	std::cout << "取消成功！" << std::endl;
	of.updateFile();
	system("pause");
	system("cls");

}
//初始化容器
void Student::initVector()
{
	this->vIndex.clear();
}