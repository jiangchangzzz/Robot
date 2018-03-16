#pragma once

#include <vector>

#include <TopoDS_Shape.hxx>
#include <Standard_Handle.hxx>
#include <AIS_InteractiveContext.hxx>

#include "../Model/Robot.h"
#include "Translate.h"

class RobotShape
{
public:
	RobotShape();
	~RobotShape();

public:
	void display(const Handle(AIS_InteractiveContext)& ic);

	void init(const Robot &robot);

	TopoDS_Shape base;
	std::vector<TopoDS_Shape> links;
};

