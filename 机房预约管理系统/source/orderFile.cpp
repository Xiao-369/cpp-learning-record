#include "../header/orderFile.h"
#include "../header/student.h"
OrderFile::OrderFile()
{
	loadFile();
}
OrderFile::OrderFile(int date,Student* stu, int interval,int roomId, int status):OrderFile()
{
	this->m_date = date;
	this->m_interval = interval;
	this->m_stu = stu;
	this->m_roomId = roomId;
	this->m_status = status;
}
//写入文件
void OrderFile::writeFile()
{
	std::ofstream ofs;
	ofs.open(ORDER_FILE, std::ios::out | std::ios::app);
	ofs << "date:" << m_date << " ";
	ofs << "interval:" << m_interval << " ";
	ofs << "stuId:" << m_stu->m_StuId << " ";
	ofs << "stuName:" << m_stu->m_Name << " ";
	ofs << "roomId:" << m_roomId << " ";
	ofs << "status:" << m_status << std::endl;

}
//分割数据 返回队组
std::pair<std::string,std::string> splitData(std::string data)
{
	std::string key;
	std::string value;
	int pos = data.find(":");
	key = data.substr(0, pos);
	value = data.substr(pos + 1, data.size());
	return std::make_pair(key, value);
}
//初始化容器
void OrderFile::loadFile()
{
	std::ifstream ifs;
	ifs.open(ORDER_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "order文件不存在！" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::string date;
	std::string interval;
	std::string stuId;
	std::string stuName;
	std::string roomId;
	std::string status;
	int flag = true;
	std::map<std::string, std::string> temp;
	int index = 0;
	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		flag = false;
		temp.insert(splitData(date));
		temp.insert(splitData(interval));
		temp.insert(splitData(stuId));
		temp.insert(splitData(stuName));
		temp.insert(splitData(roomId));
		temp.insert(splitData(status));

		m_orderFile.insert({index++, temp});
		temp.clear();
	}
	ifs.close();
	if (flag)
	{
		std::cout << "没有预约记录！" << std::endl;
	}
}
//更新文件
void OrderFile::updateFile()
{
	std::ofstream ofs;
	ofs.open(ORDER_FILE, std::ios::trunc);
	if (this->m_orderFile.size() == 0)
	{
		return;
	}
	for (int i = 0;i < this->m_orderFile.size();i++)
	{
		ofs << "date:" << this->m_orderFile[i]["date"] << " ";
		ofs << "interval:" << this->m_orderFile[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderFile[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderFile[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderFile[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderFile[i]["status"] << std::endl;
	}
}
