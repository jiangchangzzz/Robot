#include "RobotParaDialog.h"

#include <QStandardItemModel>

RobotParaDialog::RobotParaDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

RobotParaDialog::~RobotParaDialog()
{
}

void RobotParaDialog::init(const Robot & robot)
{
	ui.nameLineEdit->setText(QString::fromStdString(robot.name));
	ui.velocityDoubleSpinBox->setValue(robot.velocity);
	ui.acceleratioDoubleSpinBox->setValue(robot.acceleration);
	
	ui.jointVelocityDoubleSpinBox->setValue(robot.jointVelocity);
	ui.jointAccelerationDoubleSpinBox->setValue(robot.jointAcceleration);

	createKinematicsTable(robot);
}

void RobotParaDialog::createKinematicsTable(const Robot &robot)
{
	QStandardItemModel *model=new QStandardItemModel(robot.links.size(), 6, this);
	const std::vector<Link> &links = robot.links;
	for (int i = 0; i < links.size(); i++)
	{
		QStandardItem *item;

		item = new QStandardItem(links[i].jointMin);
		model->setItem(i, 0, item);

		item = new QStandardItem(links[i].jointMax);
		model->setItem(i, 1, item);
	}
	ui.kinematicsTableView->setModel(model);
}


