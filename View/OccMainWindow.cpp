#pragma execution_character_set("utf-8")

#include "OccMainWindow.h"
#include "OccView.h"

#include <QToolBar>
#include <QTreeView>
#include <QMessageBox>
#include <QDockWidget>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSplitter>

#include <gp_Circ.hxx>
#include <gp_Elips.hxx>
#include <gp_Pln.hxx>

#include <gp_Lin2d.hxx>

#include <Geom_ConicalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_CylindricalSurface.hxx>

#include <GCE2d_MakeSegment.hxx>

#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TColgp_Array1OfPnt2d.hxx>

#include <BRepLib.hxx>

#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>

#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>

#include <AIS_Shape.hxx>

#include "../Model/Robot.h"
#include "Translate.h"
#include "JsonReader.h"
#include "RobotParaDialog.h"

OccMainWindow::OccMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	test();
	createCenter();
	createActions();
	createMenus();
	createToolBars();

	resize(1000, 700);
}

OccMainWindow::~OccMainWindow()
{

}

void OccMainWindow::createCenter()
{
	myOccView = new OccView(this);
	treeView = new QTreeView(this);

	QSplitter *splitter = new QSplitter();
	splitter->addWidget(treeView);
	splitter->addWidget(myOccView);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 15);

	setCentralWidget(splitter);
}

void OccMainWindow::createActions(void)
{
	newAction = new QAction(tr("�½�����վ"), this);
	newAction->setShortcut(tr("Ctrl+N"));
	newAction->setIcon(QIcon(":/Resources/new.png"));
	newAction->setStatusTip(tr("�½�����վ"));
	connect(newAction, SIGNAL(triggered()), this, SLOT(newProject()));

	openAction = new QAction(tr("�򿪹���վ"), this);
	openAction->setShortcut(tr("Ctrl+O"));
	openAction->setIcon(QIcon(":/Resources/open.png"));
	openAction->setStatusTip(tr("�򿪹���վ"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openProject()));

	saveAction = new QAction(tr("����"), this);
	saveAction->setShortcut(tr("Ctrl+S"));
	saveAction->setIcon(QIcon(":/Resources/save.png"));
	saveAction->setStatusTip(tr("����"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveProject()));

	saveAsAction = new QAction(tr("���Ϊ..."), this);
	saveAsAction->setShortcut(tr("Ctrl+A"));
	saveAsAction->setIcon(QIcon(":/Resources/saveAs.png"));
	saveAsAction->setStatusTip(tr("���Ϊ..."));
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsProject()));

	closeAction = new QAction(tr("�رչ���վ"), this);
	closeAction->setShortcut(tr("Ctrl+C"));
	closeAction->setIcon(QIcon(":/Resources/close.png"));
	closeAction->setStatusTip(tr("�رչ���վ"));
	connect(closeAction, SIGNAL(triggered()), this, SLOT(closeProject()));

	importAction = new QAction(tr("����"), this);
	importAction->setShortcut(tr("Ctrl+I"));
	importAction->setIcon(QIcon(":/Resources/import.png"));
	importAction->setStatusTip(tr("����"));
	connect(importAction, SIGNAL(triggered()), this, SLOT(importModel()));

	exportAction = new QAction(tr("����"), this);
	exportAction->setShortcut(tr("Ctrl+X"));
	exportAction->setIcon(QIcon(":/Resources/export.png"));
	exportAction->setStatusTip(tr("����"));
	connect(exportAction, SIGNAL(triggered()), this, SLOT(exportModel()));

	exitAction = new QAction(tr("�˳�"), this);
	exitAction->setShortcut(tr("Ctrl+E"));
	exitAction->setIcon(QIcon(":/Resources/exit.png"));
	exitAction->setStatusTip(tr("�˳�"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

	robotParaAction = new QAction(tr("�����˲���"), this);
	robotParaAction->setIcon(QIcon(":/Resources/robot.png"));
	robotParaAction->setStatusTip(tr("�����˲���"));
	connect(robotParaAction, SIGNAL(triggered()), this, SLOT(robotPara()));

	makeBoxAction = new QAction(tr("Box"), this);
	makeBoxAction->setIcon(QIcon(":/Resources/makeBox.png"));
	makeBoxAction->setStatusTip(tr("Box"));
	connect(makeBoxAction, SIGNAL(triggered()), this, SLOT(makeBox()));

	makeConeAction = new QAction(tr("Cone"), this);
	makeConeAction->setIcon(QIcon(":/Resources/makeCone.png"));
	makeConeAction->setStatusTip(tr("Cone"));
	connect(makeConeAction, SIGNAL(triggered()), this, SLOT(makeCone()));

	makeSphereAction = new QAction(tr("Sphere"), this);
	makeSphereAction->setIcon(QIcon(":/Resources/makeSphere.png"));
	makeSphereAction->setStatusTip(tr("Sphere"));
	connect(makeSphereAction, SIGNAL(triggered()), this, SLOT(makeSphere()));

	makeCylinderAction = new QAction(tr("Cylinder"), this);
	makeCylinderAction->setIcon(QIcon(":/Resources/makeCylinder.png"));
	makeCylinderAction->setStatusTip(tr("Cylinder"));
	connect(makeCylinderAction, SIGNAL(triggered()), this, SLOT(makeCylinder()));

	makeTorusAction = new QAction(tr("Torus"), this);
	makeTorusAction->setIcon(QIcon(":/Resources/makeTorus.png"));
	makeTorusAction->setStatusTip(tr("Torus"));
	connect(makeTorusAction, SIGNAL(triggered()), this, SLOT(makeTorus()));

	aboutAction = new QAction(tr("����"), this);
	aboutAction->setIcon(QIcon(":/Resources/about.png"));
	aboutAction->setStatusTip(tr("����"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void OccMainWindow::createMenus(void)
{
	fileMenu = menuBar()->addMenu(tr("�ļ�(&F)"));
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	recentMenu=fileMenu->addMenu(tr("����򿪵�"));
	int fileNum = recentFiles.size();
	for (int i = fileNum - 1; i >= std::max(0, fileNum - 3); i--)
	{
		QAction *recentFileAction = new QAction(QString::fromStdString(recentFiles[i]), this);
		recentMenu->addAction(recentFileAction);
	}
	fileMenu->addSeparator();

	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addSeparator();

	fileMenu->addAction(closeAction);
	fileMenu->addSeparator();

	fileMenu->addAction(importAction);
	fileMenu->addAction(exportAction);
	fileMenu->addSeparator();

	fileMenu->addAction(exitAction);

	editMenu = menuBar()->addMenu(tr("�༭(&E)"));
	editMenu->addAction(robotParaAction);

	exampleMenu = menuBar()->addMenu(tr("ʾ��(&P)"));
	exampleMenu->addAction(makeBoxAction);
	exampleMenu->addAction(makeConeAction);
	exampleMenu->addAction(makeSphereAction);
	exampleMenu->addAction(makeCylinderAction);
	exampleMenu->addAction(makeTorusAction);

	helpMenu = menuBar()->addMenu(tr("����(&H)"));
	helpMenu->addAction(aboutAction);
}

void OccMainWindow::createToolBars(void)
{
}

//void OccMainWindow::createActions(void)
//{
//	myExitAction = new QAction(tr("Exit"), this);
//	myExitAction->setShortcut(tr("Ctrl+Q"));
//	myExitAction->setIcon(QIcon(":/Resources/close.png"));
//	myExitAction->setStatusTip(tr("Exit the application"));
//	connect(myExitAction, SIGNAL(triggered()), this, SLOT(close()));
//
//	myViewZoomAction = new QAction(tr("Zoom"), this);
//	myViewZoomAction->setIcon(QIcon(":/Resources/Zoom.png"));
//	myViewZoomAction->setStatusTip(tr("Zoom the view"));
//	connect(myViewZoomAction, SIGNAL(triggered()), myOccView, SLOT(zoom()));
//
//	myViewPanAction = new QAction(tr("Pan"), this);
//	myViewPanAction->setIcon(QIcon(":/Resources/Pan.png"));
//	myViewPanAction->setStatusTip(tr("Pan the view"));
//	connect(myViewPanAction, SIGNAL(triggered()), myOccView, SLOT(pan()));
//
//	myViewRotateAction = new QAction(tr("Rotate"), this);
//	myViewRotateAction->setIcon(QIcon(":/Resources/Rotate.png"));
//	myViewRotateAction->setStatusTip(tr("Rotate the view"));
//	connect(myViewRotateAction, SIGNAL(triggered()), myOccView, SLOT(rotate()));
//
//	myViewResetAction = new QAction(tr("Reset"), this);
//	myViewResetAction->setIcon(QIcon(":/Resources/Home.png"));
//	myViewResetAction->setStatusTip(tr("Reset the view"));
//	connect(myViewResetAction, SIGNAL(triggered()), myOccView, SLOT(reset()));
//
//	myViewFitallAction = new QAction(tr("Fit All"), this);
//	myViewFitallAction->setIcon(QIcon(":/Resources/FitAll.png"));
//	myViewFitallAction->setStatusTip(tr("Fit all "));
//	connect(myViewFitallAction, SIGNAL(triggered()), myOccView, SLOT(fitAll()));
//
//	myMakeBoxAction = new QAction(tr("Box"), this);
//	myMakeBoxAction->setIcon(QIcon(":/Resources/box.png"));
//	myMakeBoxAction->setStatusTip(tr("Make a box"));
//	connect(myMakeBoxAction, SIGNAL(triggered()), this, SLOT(makeBox()));
//
//	myMakeConeAction = new QAction(tr("Cone"), this);
//	myMakeConeAction->setIcon(QIcon(":/Resources/cone.png"));
//	myMakeConeAction->setStatusTip(tr("Make a cone"));
//	connect(myMakeConeAction, SIGNAL(triggered()), this, SLOT(makeCone()));
//
//	myMakeSphereAction = new QAction(tr("Sphere"), this);
//	myMakeSphereAction->setStatusTip(tr("Make a sphere"));
//	myMakeSphereAction->setIcon(QIcon(":/Resources/sphere.png"));
//	connect(myMakeSphereAction, SIGNAL(triggered()), this, SLOT(makeSphere()));
//
//	myMakeCylinderAction = new QAction(tr("Cylinder"), this);
//	myMakeCylinderAction->setStatusTip(tr("Make a cylinder"));
//	myMakeCylinderAction->setIcon(QIcon(":/Resources/cylinder.png"));
//	connect(myMakeCylinderAction, SIGNAL(triggered()), this, SLOT(makeCylinder()));
//
//	myMakeTorusAction = new QAction(tr("Torus"), this);
//	myMakeTorusAction->setStatusTip(tr("Make a torus"));
//	myMakeTorusAction->setIcon(QIcon(":/Resources/torus.png"));
//	connect(myMakeTorusAction, SIGNAL(triggered()), this, SLOT(makeTorus()));
//
//	myFilletAction = new QAction(tr("Fillet"), this);
//	myFilletAction->setIcon(QIcon(":/Resources/fillet.png"));
//	myFilletAction->setStatusTip(tr("Test Fillet algorithm"));
//	connect(myFilletAction, SIGNAL(triggered()), this, SLOT(makeFillet()));
//
//	myChamferAction = new QAction(tr("Chamfer"), this);
//	myChamferAction->setIcon(QIcon(":/Resources/chamfer.png"));
//	myChamferAction->setStatusTip(tr("Test chamfer algorithm"));
//	connect(myChamferAction, SIGNAL(triggered()), this, SLOT(makeChamfer()));
//
//	myExtrudeAction = new QAction(tr("Extrude"), this);
//	myExtrudeAction->setIcon(QIcon(":/Resources/extrude.png"));
//	myExtrudeAction->setStatusTip(tr("Test extrude algorithm"));
//	connect(myExtrudeAction, SIGNAL(triggered()), this, SLOT(makeExtrude()));
//
//	myRevolveAction = new QAction(tr("Revolve"), this);
//	myRevolveAction->setIcon(QIcon(":/Resources/revolve.png"));
//	myRevolveAction->setStatusTip(tr("Test revol algorithm"));
//	connect(myRevolveAction, SIGNAL(triggered()), this, SLOT(makeRevol()));
//
//	myLoftAction = new QAction(tr("Loft"), this);
//	myLoftAction->setIcon(QIcon(":/Resources/loft.png"));
//	myLoftAction->setStatusTip(tr("Test loft algorithm"));
//	connect(myLoftAction, SIGNAL(triggered()), this, SLOT(makeLoft()));
//
//	myCutAction = new QAction(tr("Cut"), this);
//	myCutAction->setIcon(QIcon(":/Resources/cut.png"));
//	myCutAction->setStatusTip(tr("Boolean operation cut"));
//	connect(myCutAction, SIGNAL(triggered()), this, SLOT(testCut()));
//
//	myFuseAction = new QAction(tr("Fuse"), this);
//	myFuseAction->setIcon(QIcon(":/Resources/fuse.png"));
//	myFuseAction->setStatusTip(tr("Boolean operation fuse"));
//	connect(myFuseAction, SIGNAL(triggered()), this, SLOT(testFuse()));
//
//	myCommonAction = new QAction(tr("Common"), this);
//	myCommonAction->setIcon(QIcon(":/Resources/common.png"));
//	myCommonAction->setStatusTip(tr("Boolean operation common"));
//	connect(myCommonAction, SIGNAL(triggered()), this, SLOT(testCommon()));
//
//	myHelixAction = new QAction(tr("Helix"), this);
//	myHelixAction->setIcon(QIcon(":/Resources/helix.png"));
//	myHelixAction->setStatusTip(tr("Make helix shapes"));
//	connect(myHelixAction, SIGNAL(triggered()), this, SLOT(testHelix()));
//
//	myAboutAction = new QAction(tr("About"), this);
//	myAboutAction->setStatusTip(tr("About the application"));
//	myAboutAction->setIcon(QIcon(":/Resources/lamp.png"));
//	connect(myAboutAction, SIGNAL(triggered()), this, SLOT(about()));
//}
//
//void OccMainWindow::createMenus(void)
//{
//	myFileMenu = menuBar()->addMenu(tr("&File"));
//	myFileMenu->addAction(myExitAction);
//
//	myViewMenu = menuBar()->addMenu(tr("&View"));
//	myViewMenu->addAction(myViewZoomAction);
//	myViewMenu->addAction(myViewPanAction);
//	myViewMenu->addAction(myViewRotateAction);
//	myViewMenu->addSeparator();
//	myViewMenu->addAction(myViewResetAction);
//	myViewMenu->addAction(myViewFitallAction);
//
//	myPrimitiveMenu = menuBar()->addMenu(tr("&Primitive"));
//	myPrimitiveMenu->addAction(myMakeBoxAction);
//	myPrimitiveMenu->addAction(myMakeConeAction);
//	myPrimitiveMenu->addAction(myMakeSphereAction);
//	myPrimitiveMenu->addAction(myMakeCylinderAction);
//	myPrimitiveMenu->addAction(myMakeTorusAction);
//
//	myModelingMenu = menuBar()->addMenu(tr("&Modeling"));
//	myModelingMenu->addAction(myFilletAction);
//	myModelingMenu->addAction(myChamferAction);
//	myModelingMenu->addAction(myExtrudeAction);
//	myModelingMenu->addAction(myRevolveAction);
//	myModelingMenu->addAction(myLoftAction);
//	myModelingMenu->addSeparator();
//	myModelingMenu->addAction(myCutAction);
//	myModelingMenu->addAction(myFuseAction);
//	myModelingMenu->addAction(myCommonAction);
//	myModelingMenu->addSeparator();
//	myModelingMenu->addAction(myHelixAction);
//
//	myHelpMenu = menuBar()->addMenu(tr("&Help"));
//	myHelpMenu->addAction(myAboutAction);
//}
//
//void OccMainWindow::createToolBars(void)
//{
//	myNavigateToolBar = addToolBar(tr("&Navigate"));
//	myNavigateToolBar->addAction(myViewZoomAction);
//	myNavigateToolBar->addAction(myViewPanAction);
//	myNavigateToolBar->addAction(myViewRotateAction);
//
//	myViewToolBar = addToolBar(tr("&View"));
//	myViewToolBar->addAction(myViewResetAction);
//	myViewToolBar->addAction(myViewFitallAction);
//
//	myPrimitiveToolBar = addToolBar(tr("&Primitive"));
//	myPrimitiveToolBar->addAction(myMakeBoxAction);
//	myPrimitiveToolBar->addAction(myMakeConeAction);
//	myPrimitiveToolBar->addAction(myMakeSphereAction);
//	myPrimitiveToolBar->addAction(myMakeCylinderAction);
//	myPrimitiveToolBar->addAction(myMakeTorusAction);
//
//	myModelingToolBar = addToolBar(tr("&Modeling"));
//	myModelingToolBar->addAction(myFilletAction);
//	myModelingToolBar->addAction(myChamferAction);
//	myModelingToolBar->addAction(myExtrudeAction);
//	myModelingToolBar->addAction(myRevolveAction);
//	myModelingToolBar->addAction(myLoftAction);
//	myModelingToolBar->addSeparator();
//	myModelingToolBar->addAction(myCutAction);
//	myModelingToolBar->addAction(myFuseAction);
//	myModelingToolBar->addAction(myCommonAction);
//	myModelingToolBar->addSeparator();
//	myModelingToolBar->addAction(myHelixAction);
//
//	myHelpToolBar = addToolBar(tr("Help"));
//	myHelpToolBar->addAction(myAboutAction);
//}

void OccMainWindow::about()
{
	QMessageBox::about(this, tr("About RobotX"),
		tr("<h2>RobotX 1.0</h2>"
			"<p>Copyright &copy; 2018"
			"<p>RobotX is a demo applicaton about Robot."));
}

void OccMainWindow::makeBox()
{
	TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(3.0, 4.0, 5.0).Shape();
	Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);

	anAisBox->SetColor(Quantity_NOC_AZURE);

	myOccView->getContext()->Display(anAisBox, Standard_True);
}

void OccMainWindow::makeCone()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(0.0, 10.0, 0.0));

	TopoDS_Shape aTopoReducer = BRepPrimAPI_MakeCone(anAxis, 3.0, 1.5, 5.0).Shape();
	Handle(AIS_Shape) anAisReducer = new AIS_Shape(aTopoReducer);

	anAisReducer->SetColor(Quantity_NOC_BISQUE);

	anAxis.SetLocation(gp_Pnt(8.0, 10.0, 0.0));
	TopoDS_Shape aTopoCone = BRepPrimAPI_MakeCone(anAxis, 3.0, 0.0, 5.0).Shape();
	Handle(AIS_Shape) anAisCone = new AIS_Shape(aTopoCone);

	anAisCone->SetColor(Quantity_NOC_CHOCOLATE);

	myOccView->getContext()->Display(anAisReducer, Standard_True);
	myOccView->getContext()->Display(anAisCone, Standard_True);
}

void OccMainWindow::makeSphere()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(0.0, 20.0, 0.0));

	TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 3.0).Shape();
	Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);

	anAisSphere->SetColor(Quantity_NOC_BLUE1);

	myOccView->getContext()->Display(anAisSphere, Standard_True);
}

void OccMainWindow::makeCylinder()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(0.0, 30.0, 0.0));

	TopoDS_Shape aTopoCylinder = BRepPrimAPI_MakeCylinder(anAxis, 3.0, 5.0).Shape();
	Handle(AIS_Shape) anAisCylinder = new AIS_Shape(aTopoCylinder);

	anAisCylinder->SetColor(Quantity_NOC_RED);

	anAxis.SetLocation(gp_Pnt(8.0, 30.0, 0.0));
	TopoDS_Shape aTopoPie = BRepPrimAPI_MakeCylinder(anAxis, 3.0, 5.0, M_PI_2 * 3.0).Shape();
	Handle(AIS_Shape) anAisPie = new AIS_Shape(aTopoPie);

	anAisPie->SetColor(Quantity_NOC_TAN);

	myOccView->getContext()->Display(anAisCylinder, Standard_True);
	myOccView->getContext()->Display(anAisPie, Standard_True);
}

void OccMainWindow::makeTorus()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(0.0, 40.0, 0.0));

	TopoDS_Shape aTopoTorus = BRepPrimAPI_MakeTorus(anAxis, 3.0, 1.0).Shape();
	Handle(AIS_Shape) anAisTorus = new AIS_Shape(aTopoTorus);

	anAisTorus->SetColor(Quantity_NOC_YELLOW);

	anAxis.SetLocation(gp_Pnt(8.0, 40.0, 0.0));
	TopoDS_Shape aTopoElbow = BRepPrimAPI_MakeTorus(anAxis, 3.0, 1.0, M_PI_2).Shape();
	Handle(AIS_Shape) anAisElbow = new AIS_Shape(aTopoElbow);

	anAisElbow->SetColor(Quantity_NOC_THISTLE);

	myOccView->getContext()->Display(anAisTorus, Standard_True);
	myOccView->getContext()->Display(anAisElbow, Standard_True);
}

void OccMainWindow::makeFillet()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(0.0, 50.0, 0.0));

	TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
	BRepFilletAPI_MakeFillet MF(aTopoBox);

	// Add all the edges to fillet.
	for (TopExp_Explorer ex(aTopoBox, TopAbs_EDGE); ex.More(); ex.Next())
	{
		MF.Add(1.0, TopoDS::Edge(ex.Current()));
	}

	Handle(AIS_Shape) anAisShape = new AIS_Shape(MF.Shape());
	anAisShape->SetColor(Quantity_NOC_VIOLET);

	myOccView->getContext()->Display(anAisShape, Standard_True);
}

void OccMainWindow::makeChamfer()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(8.0, 50.0, 0.0));

	TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
	BRepFilletAPI_MakeChamfer MC(aTopoBox);
	TopTools_IndexedDataMapOfShapeListOfShape aEdgeFaceMap;

	TopExp::MapShapesAndAncestors(aTopoBox, TopAbs_EDGE, TopAbs_FACE, aEdgeFaceMap);

	for (Standard_Integer i = 1; i <= aEdgeFaceMap.Extent(); ++i)
	{
		TopoDS_Edge anEdge = TopoDS::Edge(aEdgeFaceMap.FindKey(i));
		TopoDS_Face aFace = TopoDS::Face(aEdgeFaceMap.FindFromIndex(i).First());

		MC.Add(0.6, 0.6, anEdge, aFace);
	}

	Handle(AIS_Shape) anAisShape = new AIS_Shape(MC.Shape());
	anAisShape->SetColor(Quantity_NOC_TOMATO);

	myOccView->getContext()->Display(anAisShape, Standard_True);
}

void OccMainWindow::makeExtrude()
{
	// prism a vertex result is an edge.
	TopoDS_Vertex aVertex = BRepBuilderAPI_MakeVertex(gp_Pnt(0.0, 60.0, 0.0));
	TopoDS_Shape aPrismVertex = BRepPrimAPI_MakePrism(aVertex, gp_Vec(0.0, 0.0, 5.0));
	Handle(AIS_Shape) anAisPrismVertex = new AIS_Shape(aPrismVertex);

	// prism an edge result is a face.
	TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(gp_Pnt(5.0, 60.0, 0.0), gp_Pnt(10.0, 60.0, 0.0));
	TopoDS_Shape aPrismEdge = BRepPrimAPI_MakePrism(anEdge, gp_Vec(0.0, 0.0, 5.0));
	Handle(AIS_Shape) anAisPrismEdge = new AIS_Shape(aPrismEdge);

	// prism a wire result is a shell.
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(16.0, 60.0, 0.0));

	TopoDS_Edge aCircleEdge = BRepBuilderAPI_MakeEdge(gp_Circ(anAxis, 3.0));
	TopoDS_Wire aCircleWire = BRepBuilderAPI_MakeWire(aCircleEdge);
	TopoDS_Shape aPrismCircle = BRepPrimAPI_MakePrism(aCircleWire, gp_Vec(0.0, 0.0, 5.0));
	Handle(AIS_Shape) anAisPrismCircle = new AIS_Shape(aPrismCircle);

	// prism a face or a shell result is a solid.
	anAxis.SetLocation(gp_Pnt(24.0, 60.0, 0.0));
	TopoDS_Edge aEllipseEdge = BRepBuilderAPI_MakeEdge(gp_Elips(anAxis, 3.0, 2.0));
	TopoDS_Wire aEllipseWire = BRepBuilderAPI_MakeWire(aEllipseEdge);
	TopoDS_Face aEllipseFace = BRepBuilderAPI_MakeFace(gp_Pln(gp::XOY()), aEllipseWire);
	TopoDS_Shape aPrismEllipse = BRepPrimAPI_MakePrism(aEllipseFace, gp_Vec(0.0, 0.0, 5.0));
	Handle(AIS_Shape) anAisPrismEllipse = new AIS_Shape(aPrismEllipse);

	anAisPrismVertex->SetColor(Quantity_NOC_PAPAYAWHIP);
	anAisPrismEdge->SetColor(Quantity_NOC_PEACHPUFF);
	anAisPrismCircle->SetColor(Quantity_NOC_PERU);
	anAisPrismEllipse->SetColor(Quantity_NOC_PINK);

	myOccView->getContext()->Display(anAisPrismVertex, Standard_True);
	myOccView->getContext()->Display(anAisPrismEdge, Standard_True);
	myOccView->getContext()->Display(anAisPrismCircle, Standard_True);
	myOccView->getContext()->Display(anAisPrismEllipse, Standard_True);
}

void OccMainWindow::makeRevol()
{
	gp_Ax1 anAxis;

	// revol a vertex result is an edge.
	anAxis.SetLocation(gp_Pnt(0.0, 70.0, 0.0));
	TopoDS_Vertex aVertex = BRepBuilderAPI_MakeVertex(gp_Pnt(2.0, 70.0, 0.0));
	TopoDS_Shape aRevolVertex = BRepPrimAPI_MakeRevol(aVertex, anAxis);
	Handle(AIS_Shape) anAisRevolVertex = new AIS_Shape(aRevolVertex);

	// revol an edge result is a face.
	anAxis.SetLocation(gp_Pnt(8.0, 70.0, 0.0));
	TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(gp_Pnt(6.0, 70.0, 0.0), gp_Pnt(6.0, 70.0, 5.0));
	TopoDS_Shape aRevolEdge = BRepPrimAPI_MakeRevol(anEdge, anAxis);
	Handle(AIS_Shape) anAisRevolEdge = new AIS_Shape(aRevolEdge);

	// revol a wire result is a shell.
	anAxis.SetLocation(gp_Pnt(20.0, 70.0, 0.0));
	anAxis.SetDirection(gp::DY());

	TopoDS_Edge aCircleEdge = BRepBuilderAPI_MakeEdge(gp_Circ(gp_Ax2(gp_Pnt(15.0, 70.0, 0.0), gp::DZ()), 1.5));
	TopoDS_Wire aCircleWire = BRepBuilderAPI_MakeWire(aCircleEdge);
	TopoDS_Shape aRevolCircle = BRepPrimAPI_MakeRevol(aCircleWire, anAxis, M_PI_2);
	Handle(AIS_Shape) anAisRevolCircle = new AIS_Shape(aRevolCircle);

	// revol a face result is a solid.
	anAxis.SetLocation(gp_Pnt(30.0, 70.0, 0.0));
	anAxis.SetDirection(gp::DY());

	TopoDS_Edge aEllipseEdge = BRepBuilderAPI_MakeEdge(gp_Elips(gp_Ax2(gp_Pnt(25.0, 70.0, 0.0), gp::DZ()), 3.0, 2.0));
	TopoDS_Wire aEllipseWire = BRepBuilderAPI_MakeWire(aEllipseEdge);
	TopoDS_Face aEllipseFace = BRepBuilderAPI_MakeFace(gp_Pln(gp::XOY()), aEllipseWire);
	TopoDS_Shape aRevolEllipse = BRepPrimAPI_MakeRevol(aEllipseFace, anAxis, M_PI_4);
	Handle(AIS_Shape) anAisRevolEllipse = new AIS_Shape(aRevolEllipse);

	anAisRevolVertex->SetColor(Quantity_NOC_LIMEGREEN);
	anAisRevolEdge->SetColor(Quantity_NOC_LINEN);
	anAisRevolCircle->SetColor(Quantity_NOC_MAGENTA1);
	anAisRevolEllipse->SetColor(Quantity_NOC_MAROON);

	myOccView->getContext()->Display(anAisRevolVertex, Standard_True);
	myOccView->getContext()->Display(anAisRevolEdge, Standard_True);
	myOccView->getContext()->Display(anAisRevolCircle, Standard_True);
	myOccView->getContext()->Display(anAisRevolEllipse, Standard_True);
}

void OccMainWindow::makeLoft()
{
	// bottom wire.
	TopoDS_Edge aCircleEdge = BRepBuilderAPI_MakeEdge(gp_Circ(gp_Ax2(gp_Pnt(0.0, 80.0, 0.0), gp::DZ()), 1.5));
	TopoDS_Wire aCircleWire = BRepBuilderAPI_MakeWire(aCircleEdge);

	// top wire.
	BRepBuilderAPI_MakePolygon aPolygon;
	aPolygon.Add(gp_Pnt(-3.0, 77.0, 6.0));
	aPolygon.Add(gp_Pnt(3.0, 77.0, 6.0));
	aPolygon.Add(gp_Pnt(3.0, 83.0, 6.0));
	aPolygon.Add(gp_Pnt(-3.0, 83.0, 6.0));
	aPolygon.Close();

	BRepOffsetAPI_ThruSections aShellGenerator;
	BRepOffsetAPI_ThruSections aSolidGenerator(true);

	aShellGenerator.AddWire(aCircleWire);
	aShellGenerator.AddWire(aPolygon.Wire());

	aSolidGenerator.AddWire(aCircleWire);
	aSolidGenerator.AddWire(aPolygon.Wire());

	// translate the solid.
	gp_Trsf aTrsf;
	aTrsf.SetTranslation(gp_Vec(18.0, 0.0, 0.0));
	BRepBuilderAPI_Transform aTransform(aSolidGenerator.Shape(), aTrsf);

	Handle(AIS_Shape) anAisShell = new AIS_Shape(aShellGenerator.Shape());
	Handle(AIS_Shape) anAisSolid = new AIS_Shape(aTransform.Shape());

	anAisShell->SetColor(Quantity_NOC_OLIVEDRAB);
	anAisSolid->SetColor(Quantity_NOC_PEACHPUFF);

	myOccView->getContext()->Display(anAisShell, Standard_True);
	myOccView->getContext()->Display(anAisSolid, Standard_True);
}

void OccMainWindow::testCut()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(0.0, 90.0, 0.0));

	TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
	TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 2.5).Shape();
	TopoDS_Shape aCuttedShape1 = BRepAlgoAPI_Cut(aTopoBox, aTopoSphere);
	TopoDS_Shape aCuttedShape2 = BRepAlgoAPI_Cut(aTopoSphere, aTopoBox);

	gp_Trsf aTrsf;
	aTrsf.SetTranslation(gp_Vec(8.0, 0.0, 0.0));
	BRepBuilderAPI_Transform aTransform1(aCuttedShape1, aTrsf);

	aTrsf.SetTranslation(gp_Vec(16.0, 0.0, 0.0));
	BRepBuilderAPI_Transform aTransform2(aCuttedShape2, aTrsf);

	Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);
	Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);
	Handle(AIS_Shape) anAisCuttedShape1 = new AIS_Shape(aTransform1.Shape());
	Handle(AIS_Shape) anAisCuttedShape2 = new AIS_Shape(aTransform2.Shape());

	anAisBox->SetColor(Quantity_NOC_SPRINGGREEN);
	anAisSphere->SetColor(Quantity_NOC_STEELBLUE);
	anAisCuttedShape1->SetColor(Quantity_NOC_TAN);
	anAisCuttedShape2->SetColor(Quantity_NOC_SALMON);

	myOccView->getContext()->Display(anAisBox, Standard_True);
	myOccView->getContext()->Display(anAisSphere, Standard_True);
	myOccView->getContext()->Display(anAisCuttedShape1, Standard_True);
	myOccView->getContext()->Display(anAisCuttedShape2, Standard_True);
}

void OccMainWindow::testFuse()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(0.0, 100.0, 0.0));

	TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
	TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 2.5).Shape();
	TopoDS_Shape aFusedShape = BRepAlgoAPI_Fuse(aTopoBox, aTopoSphere);

	gp_Trsf aTrsf;
	aTrsf.SetTranslation(gp_Vec(8.0, 0.0, 0.0));
	BRepBuilderAPI_Transform aTransform(aFusedShape, aTrsf);

	Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);
	Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);
	Handle(AIS_Shape) anAisFusedShape = new AIS_Shape(aTransform.Shape());

	anAisBox->SetColor(Quantity_NOC_SPRINGGREEN);
	anAisSphere->SetColor(Quantity_NOC_STEELBLUE);
	anAisFusedShape->SetColor(Quantity_NOC_ROSYBROWN);

	myOccView->getContext()->Display(anAisBox, Standard_True);
	myOccView->getContext()->Display(anAisSphere, Standard_True);
	myOccView->getContext()->Display(anAisFusedShape, Standard_True);
}

void OccMainWindow::testCommon()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(0.0, 110.0, 0.0));

	TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(anAxis, 3.0, 4.0, 5.0).Shape();
	TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 2.5).Shape();
	TopoDS_Shape aCommonShape = BRepAlgoAPI_Common(aTopoBox, aTopoSphere);

	gp_Trsf aTrsf;
	aTrsf.SetTranslation(gp_Vec(8.0, 0.0, 0.0));
	BRepBuilderAPI_Transform aTransform(aCommonShape, aTrsf);

	Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);
	Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);
	Handle(AIS_Shape) anAisCommonShape = new AIS_Shape(aTransform.Shape());

	anAisBox->SetColor(Quantity_NOC_SPRINGGREEN);
	anAisSphere->SetColor(Quantity_NOC_STEELBLUE);
	anAisCommonShape->SetColor(Quantity_NOC_ROYALBLUE);

	myOccView->getContext()->Display(anAisBox, Standard_True);
	myOccView->getContext()->Display(anAisSphere, Standard_True);
	myOccView->getContext()->Display(anAisCommonShape, Standard_True);
}

void OccMainWindow::testHelix()
{
	makeCylindricalHelix();

	makeConicalHelix();

	makeToroidalHelix();
}

void OccMainWindow::newProject()
{
	qDebug("new");
}

void OccMainWindow::openProject()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("�򿪹���վ"), ".", tr("����վ(*.rob)"));
	loadProject(fileName);
}

void OccMainWindow::saveProject()
{
	qDebug("save");
}

void OccMainWindow::saveAsProject()
{
	qDebug("saveAs");
}

void OccMainWindow::closeProject()
{
	qDebug("close");
}

void OccMainWindow::importModel()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("����ģ��"), ".", tr("STEP(*.STEP)"));
	if (!loadModel(fileName))
	{
		QMessageBox::warning(this, tr("����"), tr("����ģ���ļ�ʧ��"), QMessageBox::Ok);
	}
}

void OccMainWindow::exportModel()
{
	qDebug("export");
}

void OccMainWindow::exit()
{
	qDebug("exit");
}

void OccMainWindow::robotPara()
{
	RobotParaDialog Dialog;
	Dialog.init(robot);
	Dialog.exec();
}

void OccMainWindow::makeCylindricalHelix()
{
	Standard_Real aRadius = 3.0;
	Standard_Real aPitch = 1.0;

	// the pcurve is a 2d line in the parametric space.
	gp_Lin2d aLine2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(aRadius, aPitch));

	Handle(Geom2d_TrimmedCurve) aSegment = GCE2d_MakeSegment(aLine2d, 0.0, M_PI * 2.0).Value();

	Handle(Geom_CylindricalSurface) aCylinder = new Geom_CylindricalSurface(gp::XOY(), aRadius);

	TopoDS_Edge aHelixEdge = BRepBuilderAPI_MakeEdge(aSegment, aCylinder, 0.0, 6.0 * M_PI).Edge();

	gp_Trsf aTrsf;
	aTrsf.SetTranslation(gp_Vec(0.0, 120.0, 0.0));
	BRepBuilderAPI_Transform aTransform(aHelixEdge, aTrsf);

	Handle(AIS_Shape) anAisHelixCurve = new AIS_Shape(aTransform.Shape());

	myOccView->getContext()->Display(anAisHelixCurve, Standard_True);

	// sweep a circle profile along the helix curve.
	// there is no curve3d in the pcurve edge, so approx one.
	BRepLib::BuildCurve3d(aHelixEdge);

	gp_Ax2 anAxis;
	anAxis.SetDirection(gp_Dir(0.0, 4.0, 1.0));
	anAxis.SetLocation(gp_Pnt(aRadius, 0.0, 0.0));

	gp_Circ aProfileCircle(anAxis, 0.3);

	TopoDS_Edge aProfileEdge = BRepBuilderAPI_MakeEdge(aProfileCircle).Edge();
	TopoDS_Wire aProfileWire = BRepBuilderAPI_MakeWire(aProfileEdge).Wire();
	TopoDS_Face aProfileFace = BRepBuilderAPI_MakeFace(aProfileWire).Face();

	TopoDS_Wire aHelixWire = BRepBuilderAPI_MakeWire(aHelixEdge).Wire();

	BRepOffsetAPI_MakePipe aPipeMaker(aHelixWire, aProfileFace);

	if (aPipeMaker.IsDone())
	{
		aTrsf.SetTranslation(gp_Vec(8.0, 120.0, 0.0));
		BRepBuilderAPI_Transform aPipeTransform(aPipeMaker.Shape(), aTrsf);

		Handle(AIS_Shape) anAisPipe = new AIS_Shape(aPipeTransform.Shape());
		anAisPipe->SetColor(Quantity_NOC_CORAL);
		myOccView->getContext()->Display(anAisPipe, Standard_True);
	}
}

/**
* make conical helix, it is the same as the cylindrical helix,
* the only different is the surface.
*/
void OccMainWindow::makeConicalHelix()
{
	Standard_Real aRadius = 3.0;
	Standard_Real aPitch = 1.0;

	// the pcurve is a 2d line in the parametric space.
	gp_Lin2d aLine2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(aRadius, aPitch));

	Handle(Geom2d_TrimmedCurve) aSegment = GCE2d_MakeSegment(aLine2d, 0.0, M_PI * 2.0).Value();

	Handle(Geom_ConicalSurface) aCylinder = new Geom_ConicalSurface(gp::XOY(), M_PI / 6.0, aRadius);

	TopoDS_Edge aHelixEdge = BRepBuilderAPI_MakeEdge(aSegment, aCylinder, 0.0, 6.0 * M_PI).Edge();

	gp_Trsf aTrsf;
	aTrsf.SetTranslation(gp_Vec(18.0, 120.0, 0.0));
	BRepBuilderAPI_Transform aTransform(aHelixEdge, aTrsf);

	Handle(AIS_Shape) anAisHelixCurve = new AIS_Shape(aTransform.Shape());

	myOccView->getContext()->Display(anAisHelixCurve, Standard_True);

	// sweep a circle profile along the helix curve.
	// there is no curve3d in the pcurve edge, so approx one.
	BRepLib::BuildCurve3d(aHelixEdge);

	gp_Ax2 anAxis;
	anAxis.SetDirection(gp_Dir(0.0, 4.0, 1.0));
	anAxis.SetLocation(gp_Pnt(aRadius, 0.0, 0.0));

	gp_Circ aProfileCircle(anAxis, 0.3);

	TopoDS_Edge aProfileEdge = BRepBuilderAPI_MakeEdge(aProfileCircle).Edge();
	TopoDS_Wire aProfileWire = BRepBuilderAPI_MakeWire(aProfileEdge).Wire();
	TopoDS_Face aProfileFace = BRepBuilderAPI_MakeFace(aProfileWire).Face();

	TopoDS_Wire aHelixWire = BRepBuilderAPI_MakeWire(aHelixEdge).Wire();

	BRepOffsetAPI_MakePipe aPipeMaker(aHelixWire, aProfileFace);

	if (aPipeMaker.IsDone())
	{
		aTrsf.SetTranslation(gp_Vec(28.0, 120.0, 0.0));
		BRepBuilderAPI_Transform aPipeTransform(aPipeMaker.Shape(), aTrsf);

		Handle(AIS_Shape) anAisPipe = new AIS_Shape(aPipeTransform.Shape());
		anAisPipe->SetColor(Quantity_NOC_DARKGOLDENROD);
		myOccView->getContext()->Display(anAisPipe, Standard_True);
	}
}

void OccMainWindow::makeToroidalHelix()
{
	Standard_Real aRadius = 1.0;
	Standard_Real aSlope = 0.05;

	// the pcurve is a 2d line in the parametric space.
	gp_Lin2d aLine2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(aSlope, 1.0));

	Handle(Geom2d_TrimmedCurve) aSegment = GCE2d_MakeSegment(aLine2d, 0.0, M_PI * 2.0).Value();

	Handle(Geom_ToroidalSurface) aCylinder = new Geom_ToroidalSurface(gp::XOY(), aRadius * 5.0, aRadius);

	TopoDS_Edge aHelixEdge = BRepBuilderAPI_MakeEdge(aSegment, aCylinder, 0.0, 2.0 * M_PI / aSlope).Edge();

	gp_Trsf aTrsf;
	aTrsf.SetTranslation(gp_Vec(45.0, 120.0, 0.0));
	BRepBuilderAPI_Transform aTransform(aHelixEdge, aTrsf);

	Handle(AIS_Shape) anAisHelixCurve = new AIS_Shape(aTransform.Shape());

	myOccView->getContext()->Display(anAisHelixCurve, Standard_True);

	// sweep a circle profile along the helix curve.
	// there is no curve3d in the pcurve edge, so approx one.
	BRepLib::BuildCurve3d(aHelixEdge);

	gp_Ax2 anAxis;
	anAxis.SetDirection(gp_Dir(0.0, 0.0, 1.0));
	anAxis.SetLocation(gp_Pnt(aRadius * 6.0, 0.0, 0.0));

	gp_Circ aProfileCircle(anAxis, 0.3);

	TopoDS_Edge aProfileEdge = BRepBuilderAPI_MakeEdge(aProfileCircle).Edge();
	TopoDS_Wire aProfileWire = BRepBuilderAPI_MakeWire(aProfileEdge).Wire();
	TopoDS_Face aProfileFace = BRepBuilderAPI_MakeFace(aProfileWire).Face();

	TopoDS_Wire aHelixWire = BRepBuilderAPI_MakeWire(aHelixEdge).Wire();

	BRepOffsetAPI_MakePipe aPipeMaker(aHelixWire, aProfileFace);

	if (aPipeMaker.IsDone())
	{
		aTrsf.SetTranslation(gp_Vec(60.0, 120.0, 0.0));
		BRepBuilderAPI_Transform aPipeTransform(aPipeMaker.Shape(), aTrsf);

		Handle(AIS_Shape) anAisPipe = new AIS_Shape(aPipeTransform.Shape());
		anAisPipe->SetColor(Quantity_NOC_CORNSILK1);
		myOccView->getContext()->Display(anAisPipe, Standard_True);
	}
}

void OccMainWindow::test()
{
	recentFiles.push_back("red");
	recentFiles.push_back("blue");

	Robot robot;
}

bool OccMainWindow::loadModel(const QString & fileName)
{
	if (fileName.isEmpty())
	{
		return false;
	}

	Translate translate(this);
	Handle(AIS_InteractiveContext) context = myOccView->getContext();
	return translate.importModel(Translate::FormatSTEP, fileName, context);
}

bool OccMainWindow::loadProject(const QString & fileName)
{
	if (fileName.isEmpty())
	{
		return false;
	}
	
	QFile file;
	file.setFileName(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}
	QString content = file.readAll();
	file.close();

	if (!JsonReader::parse(content.toStdString(), robot))
	{
		return false;
	}

	robotShape.init(robot);
	Handle(AIS_InteractiveContext) context = myOccView->getContext();
	robotShape.display(context);

	return true;
}
