#pragma once

#include <string>
#include <vector>

#include "Export.h"
#include "Base.h"
#include "Link.h"

class MODEL_API Robot
{
public:
	Robot();
	~Robot();

public:
	std::string name;      //机器人名称
	double velocity=0.0;       //速度
	double acceleration=0.0;   //加速度

	double jointVelocity=0.0;   //关节速度
	double jointAcceleration=0.0;   //关节加速度

	Base base;   //基座
	std::vector<Link> links;   //连杆
};

