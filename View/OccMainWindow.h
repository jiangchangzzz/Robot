#pragma once

#include "ui_occQt.h"

#include <string>
#include <vector>

#include <AIS_InteractiveContext.hxx>

#include "../Model/Robot.h"
#include "RobotShape.h"

class OccView;

//! Qt main window which include OpenCASCADE for its central widget.
class OccMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	//! constructor/destructor.
	OccMainWindow(QWidget *parent = 0);
	~OccMainWindow();

protected:
	void createCenter();

	//! create all the actions.
	void createActions(void);

	//! create all the menus.
	void createMenus(void);

	//! create the toolbar.
	void createToolBars(void);

	private slots:
	//! show about box.
	void about(void);

	//! make box test.
	void makeBox(void);

	//! make cone test.
	void makeCone(void);

	//! make sphere test.
	void makeSphere(void);

	//! make cylinder test.
	void makeCylinder(void);

	//! make torus test.
	void makeTorus(void);

	//! fillet test.
	void makeFillet(void);

	//! chamfer test.
	void makeChamfer(void);

	//! test extrude algorithm.
	void makeExtrude(void);

	//! test revol algorithm.
	void makeRevol(void);

	//! test loft algorithm.
	void makeLoft(void);

	//! test boolean operation cut.
	void testCut(void);

	//! test boolean operation fuse.
	void testFuse(void);

	//! test boolean operation common.
	void testCommon(void);

	//! test helix shapes.
	void testHelix(void);

	void newProject();

	void openProject();

	void saveProject();

	void saveAsProject();

	void closeProject();

	void importModel();

	void exportModel();

	void exit();

	void robotPara();

private:
	Ui::OccQt ui;

	//! make cylindrical helix.
	void makeCylindricalHelix(void);

	//! make conical helix.
	void makeConicalHelix(void);

	//! make toroidal helix.
	void makeToroidalHelix(void);

	void test();

private:
	bool loadModel(const QString &fileName);

	bool loadProject(const QString &fileName);

	//! the exit action.
	QAction* myExitAction;

	//! the actions for the view: pan, reset, fitall.
	QAction* myViewZoomAction;
	QAction* myViewPanAction;
	QAction* myViewRotateAction;
	QAction* myViewResetAction;
	QAction* myViewFitallAction;

	//! the actions to test the OpenCASCADE modeling algorithms.
	QAction* myMakeBoxAction;
	QAction* myMakeConeAction;
	QAction* myMakeSphereAction;
	QAction* myMakeCylinderAction;
	QAction* myMakeTorusAction;

	//! make a fillet box.
	QAction* myFilletAction;
	QAction* myChamferAction;
	QAction* myExtrudeAction;
	QAction* myRevolveAction;
	QAction* myLoftAction;

	//! boolean operations.
	QAction* myCutAction;
	QAction* myFuseAction;
	QAction* myCommonAction;

	//! helix shapes.
	QAction* myHelixAction;

	//! show the about info action.
	QAction* myAboutAction;

	//! the menus of the application.
	QMenu* myFileMenu;
	QMenu* myViewMenu;
	QMenu* myPrimitiveMenu;
	QMenu* myModelingMenu;
	QMenu* myHelpMenu;

	//! the toolbars of the application.
	QToolBar* myViewToolBar;
	QToolBar* myNavigateToolBar;
	QToolBar* myPrimitiveToolBar;
	QToolBar* myModelingToolBar;
	QToolBar* myHelpToolBar;

	// wrapped the widget for occ.
	OccView* myOccView;
	QTreeView *treeView;

	//menus
	QMenu *fileMenu;
	QMenu *recentMenu;
	QMenu *editMenu;
	QMenu *exampleMenu;
	QMenu *helpMenu;

	//file
	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAsAction;
	QAction *closeAction;
	QAction *importAction;
	QAction *exportAction;
	QAction *exitAction;

	//edit
	QAction *robotParaAction;

	//example
	QAction *makeBoxAction;
	QAction *makeConeAction;
	QAction *makeSphereAction;
	QAction *makeCylinderAction;
	QAction *makeTorusAction;

	//help
	QAction *aboutAction;

	//data
	std::vector<std::string> recentFiles;
	Robot robot;
	RobotShape robotShape;
};