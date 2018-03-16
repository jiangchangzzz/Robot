#pragma once

#include <QDialog>
#include "ui_RobotParaDialog.h"

#include "../Model/Robot.h"

class RobotParaDialog : public QDialog
{
	Q_OBJECT

public:
	RobotParaDialog(QWidget *parent = Q_NULLPTR);
	~RobotParaDialog();

	void init(const Robot &robot);

private:
	void createKinematicsTable(const Robot &robot);

	Ui::RobotParaDialog ui;
};
