#pragma once

#include <string>

#include "Export.h"
#include "JointType.h"

class MODEL_API Link
{
public:
	Link();
	~Link();

public:
	std::string path;

	JointType type=JointType::RotationalJoint;
	double alpha=0.0;
	double a=0.0;
	double theta=0.0;
	double d=0.0;

	double jointMin=0.0;
	double jointMax=0.0;
};

