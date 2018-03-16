#include "RobotShape.h"

#include <AIS_Shape.hxx>

RobotShape::RobotShape()
{
}


RobotShape::~RobotShape()
{
}

void RobotShape::display(const Handle(AIS_InteractiveContext)& ic)
{
	ic->Display(new AIS_Shape(base), false);

	for (const TopoDS_Shape &link : links)
	{
		ic->Display(new AIS_Shape(link), false);
	}
	
	ic->UpdateCurrentViewer();
}

void RobotShape::init(const Robot & robot)
{
	Translate translate(nullptr);
	Handle(TopTools_HSequenceOfShape) baseShapes=translate.importModel(QString::fromStdString(robot.base.path));
	if (!baseShapes.IsNull())
	{
		base = baseShapes->First();
	}

	links.clear();
	for (const auto &link : robot.links)
	{
		Handle(TopTools_HSequenceOfShape) shapes = translate.importModel(QString::fromStdString(link.path));
		if (!shapes.IsNull())
		{
			links.push_back(shapes->First());
		}
	}
}
