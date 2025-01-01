#include<iostream>
#include<fstream>
#include "../header/globalFile.h"
#include "../header/identity.h"
#include "../header/teacher.h"
#include "../header/manager.h"
#include "../header/student.h"
using namespace std;
void showMenu();

//教师界面
void teacherMenu(Identity*& parent)
{
	int select = 0;
	while (true)
	{
		parent->operMenu();
		cin >> select;
		Teacher* tea = (Teacher*)parent;
		switch (select)
		{
			case 1:
			{
				tea->showAllOrder();
				break;
			}
			case 2:
			{
				tea->validOrder();
				break;
			}
			default:
			{
				//注销登录
				delete parent;
				std::cout << "欢迎下次使用！" << std::endl;
				system("pause");
				system("cls");
				return;
			}
		}
	}
}
//学生界面
void studentMenu(Identity*& parent)
{
	int select = 0;
	while (true)
	{
		parent->operMenu();
		cin >> select;
		Student* stu = (Student*)parent;
		switch (select)
		{
			case 1:
			{
				stu->applyReserve();
				break;
			}
			case 2:
			{
				stu->showMyReserve();
				break;
			}
			case 3:
			{
				stu->showAllReserve();
				break;
			}
			case 4:
			{
				stu->cancelReserve();
				break;
			}
			default:
			{
				delete parent;
				std::cout << "欢迎下次使用！" << std::endl;
				system("pause");
				system("cls");
				return;
			}
		}
	}
}

//管理员界面
void ManagerMenu(Identity*& parent)
{
	int select = 0;
	while (true)
	{
		parent->operMenu();
		cin >> select;
		Manager* manager = (Manager*)parent;
		switch (select)
		{
			case 1:
			{
				//1，添加账号
				manager->addAccount();
				break;
			}
			case 2:
			{
				//2，查看账号
				manager->showAccount();
				break;
			}
			case 3:
			{
				//3，查看机房
				manager->showComputerRoom();
				break;
			}
			case 4:
			{
				//4，清空预约
				manager->cleanReserve();
				break;
			}
			default:
			{
				//0，注销登录
				delete parent;
				cout << "欢迎下次登录！" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
	}
}

//传入对应的身份文件和类型
void loginIn(string fileName, int type)
{
	Identity* parent = nullptr;
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	//接收用户输入
	int id;
	string name;
	string pwd;
	if (type == 1)
	{
		cout << "请输入学生编号：";

		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入教师编号：";
		cin >> id;
	}
	cout << "请输入姓名：";
	cin >> name;
	cout << "请输入密码：";
	cin >> pwd;
	switch (type)
	{
		case 1:
		{
			//学生验证
			int fId;
			string fName;
			string fPwd;
			while (ifs >> fId && ifs >> fName && ifs >> fPwd)
			{
				if (fId == id && fName == name && fPwd == pwd)
				{
					//验证成功
					cout << "学生认证成功！" << endl;

					
					system("pause");
					system("cls");
					//跳转到学生菜单
					parent = new Student(id, name, pwd);
					studentMenu(parent);
					return;
				}
			}
			break;
		}
		case 2:
		{
			//教师验证
			int fId;
			string fName;
			string fPwd;
			while (ifs >> fId && ifs >> fName && ifs >> fPwd)
			{
				if (fId == id && fName == name && fPwd == pwd)
				{
					//验证成功
					cout << "教师身份验证成功！" << endl;
					
					system("pause");
					system("cls");
					//跳转到教师界面
					parent = new Teacher(id, name, pwd);
					teacherMenu(parent);
					return;
				}
			}
			break;
		}
		case 3:
		{
			//管理员验证
			string fName;
			string fPwd;
			while (ifs >> fName && ifs >> fPwd)
			{
				if (fName == name && fPwd == pwd)
				{
					//验证成功
					cout << "管理员身份验证成功！" << endl;
					
					system("pause");
					system("cls");
					//跳转到管理员界面
					parent = new Manager(name, pwd);
					ManagerMenu(parent);
					return;
				}
			}
			break;
		}
	}
	//验证失败
	cout << "身份认证失败！" << endl;
	system("pause");
	system("cls");
}
int main()
{
	int select = 0;
	while (true)
	{
		showMenu();
		cin >> select;
		switch (select)
		{
			case 1:
			{
				//1， 学生登录
				loginIn(STUDENT_FILE, 1);
				break;
			}
			case 2:
			{
				//2， 教师登录
				loginIn(TEACHER_FILE, 2);
				break;
			}
			case 3:
			{
				//3， 管理员登录
				loginIn(ADMIN_FILE, 3);
				break;
			}
			default:
			{
				// 0，退出系统
				cout << "欢迎下次使用" << endl;
				return 0;
			}
				
		}
		
	}
	return 0;
}
void showMenu()
{
	cout << "===================欢迎来到机房管理系统=================" << endl;
	cout << "=====                                             ======" << endl;
	cout << "=====              1， 学生登录                   ======" << endl;
	cout << "=====                                             ======" << endl;
	cout << "=====              2， 教师登录                   ======" << endl;
	cout << "=====                                             ======" << endl;
	cout << "=====              3， 管理员登录                 ======" << endl;
	cout << "=====                                             ======" << endl;
	cout << "=====              0，退出系统                    ======" << endl;
	cout << "=====                                             ======" << endl;
	cout << "========================================================" << endl;
	cout << "请输入你的选择：";
}