#include "../header/manager.h"
//构造函数
Manager::Manager(){}
Manager::Manager(std::string name, std::string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();
}
//操作菜单
void Manager::operMenu()
{
	std::cout << "欢迎管理员" << this->m_Name << "登录！" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         1，添加账号                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         2，查看账号                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         3，查看机房                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         4，清空预约                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "=====         0，注销登录                    =====" << std::endl;
	std::cout << "=====                                        =====" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "请输入你的选择：";
}

//初始化容器
void Manager::initVector()
{
	//清空容器
	vStu.clear();
	vTea.clear();

	std::ifstream ifs;
	ifs.open(STUDENT_FILE, std::ios::in);
	Student stu;
	while (ifs >> stu.m_StuId && ifs >> stu.m_Name && ifs >> stu.m_Pwd)
	{
		vStu.push_back(stu);
	}
	//关闭文件
	ifs.close();
	std::cout << "当前学生数量：" << vStu.size() << std::endl;
	ifs.open(TEACHER_FILE, std::ios::in);
	Teacher tea;
	while (ifs >> tea.m_EmpId && ifs >> tea.m_Name && ifs >> tea.m_Pwd)
	{
		vTea.push_back(tea);
	}
	ifs.close();
	std::cout << "当前教师数量：" << vTea.size() << std::endl;

	ifs.open(COMPUTERROOM_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "机房文件信息不存在！" << std::endl;
		return;
	}
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();
}
//检查账号是否重复
bool Manager::checkRepeate(int id,int type)
{
	if (type == 1)
	{
		//检查学生
		for (std::vector<Student>::iterator it = vStu.begin();it != vStu.end();it++)
		{
			if (it->m_StuId == id)
			{
				return true;
			}
		}
	}
	else
	{
		//检查教师
		for (std::vector<Teacher>::iterator it = vTea.begin();it != vTea.end();it++)
		{
			if (it->m_EmpId == id)
			{
				return true;
			}
		}
	}
	return false;
}
//添加账号
void  Manager::addAccount()
{
	
	std::cout << "1，添加学生账号" << std::endl;
	std::cout << "2，添加教师账号" << std::endl;
	int select = 0;
	//接收输入的信息
	std::string idType;
	std::string nameType;
	std::string fileName;
	std::string errorType;
	int type;
	int id;
	std::string name;
	std::string pwd;
	std::cin >> select;

	if (select == 1)
	{
		//添加学生账号
		idType = "请输入学生编号：";
		nameType = "请输入学生姓名：";
		fileName = STUDENT_FILE;
		type = 1;
		errorType = "学号重复，请重新输入";
	}
	else
	{
		//添加教师账号
		idType = "请输入教师编号：";
		nameType = "请输入教师姓名：";
		fileName = TEACHER_FILE;
		type = 2;
		errorType = "职工号重复，请重新输入";
	}
	std::cout << idType;
	while (true)
	{
		std::cin >> id;
		bool ret = checkRepeate(id,type);
		if (!ret)
		{
			break;
		}
		std::cout << errorType << std::endl;
	}
	
	std::cout << nameType;
	std::cin >> name;
	std::cout << "请输入密码：";
	std::cin >> pwd;
	//将信息保存到文件
	std::ofstream ofs;
	ofs.open(fileName, std::ios::out | std::ios::app);
	ofs << id << " " << name << " " << pwd << " " << std::endl;
	std::cout << "添加成功！" << std::endl;
	ofs.close();
	system("pause");
	system("cls");
}
//查看账号
void  Manager::showAccount()
{
	std::cout << "1，查看学生账号" << std::endl;
	std::cout << "2，查看教师账号" << std::endl;
	int select;
	std::cout << "请输入你的选择：";
	std::cin >> select;
	if (select == 1)
	{
		//查看学生账号
		for (int i = 0;i < vStu.size();i++)
		{
			std::cout << i + 1 << "，" << vStu[i].m_StuId << " "
				<< vStu[i].m_Name << " " << vStu[i].m_Pwd << std::endl;
		}
	}
	else
	{
		//查看教师账号
		for (int i = 0;i < vTea.size();i++)
		{
			std::cout << i + 1 << "，" << vTea[i].m_EmpId << " "
				<< vTea[i].m_Name << " " << vTea[i].m_Pwd << std::endl;
		}
	}
	system("pause");
	system("cls");
}
//查看机房
void  Manager::showComputerRoom()
{
	for (std::vector<ComputerRoom>::iterator it = vCom.begin();it != vCom.end();it++)
	{
		std::cout << "机房编号：" << it->m_ComId << " 机房容量：" << it->m_MaxNum << std::endl;
	}
	system("pause");
	system("cls");
}
//清空预约
void  Manager::cleanReserve()
{
	std::ofstream ofs(ORDER_FILE, std::ios::trunc);
	ofs.close();
	std::cout << "预约全部清空！" << std::endl;
	system("pause");
	system("cls");
}