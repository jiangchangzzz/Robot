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
	std::string name;      //����������
	double velocity=0.0;       //�ٶ�
	double acceleration=0.0;   //���ٶ�

	double jointVelocity=0.0;   //�ؽ��ٶ�
	double jointAcceleration=0.0;   //�ؽڼ��ٶ�

	Base base;   //����
	std::vector<Link> links;   //����
};

