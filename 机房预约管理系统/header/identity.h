#pragma once
#include<string>
class Identity
{
public:
	virtual void operMenu() = 0;
	std::string m_Name;
	std::string m_Pwd;
};