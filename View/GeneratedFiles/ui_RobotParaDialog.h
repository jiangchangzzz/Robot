/********************************************************************************
** Form generated from reading UI file 'RobotParaDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTPARADIALOG_H
#define UI_ROBOTPARADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RobotParaDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *velocityLabel;
    QDoubleSpinBox *velocityDoubleSpinBox;
    QLabel *accelerationLabel;
    QDoubleSpinBox *acceleratioDoubleSpinBox;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout_2;
    QLabel *jointVelocityLabel;
    QDoubleSpinBox *jointVelocityDoubleSpinBox;
    QLabel *jointAccelerationLabel;
    QDoubleSpinBox *jointAccelerationDoubleSpinBox;
    QSpacerItem *horizontalSpacer_2;
    QFormLayout *formLayout_3;
    QComboBox *checkLineEdit;
    QLabel *checkLabel;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTableView *kinematicsTableView;
    QGroupBox *groupBox_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RobotParaDialog)
    {
        if (RobotParaDialog->objectName().isEmpty())
            RobotParaDialog->setObjectName(QStringLiteral("RobotParaDialog"));
        RobotParaDialog->resize(690, 401);
        verticalLayout = new QVBoxLayout(RobotParaDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(RobotParaDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        nameLabel = new QLabel(groupBox);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(groupBox);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameLineEdit);

        velocityLabel = new QLabel(groupBox);
        velocityLabel->setObjectName(QStringLiteral("velocityLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, velocityLabel);

        velocityDoubleSpinBox = new QDoubleSpinBox(groupBox);
        velocityDoubleSpinBox->setObjectName(QStringLiteral("velocityDoubleSpinBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, velocityDoubleSpinBox);

        accelerationLabel = new QLabel(groupBox);
        accelerationLabel->setObjectName(QStringLiteral("accelerationLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, accelerationLabel);

        acceleratioDoubleSpinBox = new QDoubleSpinBox(groupBox);
        acceleratioDoubleSpinBox->setObjectName(QStringLiteral("acceleratioDoubleSpinBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, acceleratioDoubleSpinBox);


        gridLayout->addLayout(formLayout, 0, 0, 2, 1);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        jointVelocityLabel = new QLabel(groupBox);
        jointVelocityLabel->setObjectName(QStringLiteral("jointVelocityLabel"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, jointVelocityLabel);

        jointVelocityDoubleSpinBox = new QDoubleSpinBox(groupBox);
        jointVelocityDoubleSpinBox->setObjectName(QStringLiteral("jointVelocityDoubleSpinBox"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, jointVelocityDoubleSpinBox);

        jointAccelerationLabel = new QLabel(groupBox);
        jointAccelerationLabel->setObjectName(QStringLiteral("jointAccelerationLabel"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, jointAccelerationLabel);

        jointAccelerationDoubleSpinBox = new QDoubleSpinBox(groupBox);
        jointAccelerationDoubleSpinBox->setObjectName(QStringLiteral("jointAccelerationDoubleSpinBox"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, jointAccelerationDoubleSpinBox);


        gridLayout->addLayout(formLayout_2, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        checkLineEdit = new QComboBox(groupBox);
        checkLineEdit->setObjectName(QStringLiteral("checkLineEdit"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, checkLineEdit);

        checkLabel = new QLabel(groupBox);
        checkLabel->setObjectName(QStringLiteral("checkLabel"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, checkLabel);


        gridLayout->addLayout(formLayout_3, 1, 4, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(RobotParaDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        kinematicsTableView = new QTableView(groupBox_2);
        kinematicsTableView->setObjectName(QStringLiteral("kinematicsTableView"));

        gridLayout_2->addWidget(kinematicsTableView, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(RobotParaDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));

        verticalLayout->addWidget(groupBox_3);

        buttonBox = new QDialogButtonBox(RobotParaDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(RobotParaDialog);

        QMetaObject::connectSlotsByName(RobotParaDialog);
    } // setupUi

    void retranslateUi(QDialog *RobotParaDialog)
    {
        RobotParaDialog->setWindowTitle(QApplication::translate("RobotParaDialog", "\346\234\272\345\231\250\344\272\272\345\217\202\346\225\260", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("RobotParaDialog", "\345\237\272\346\234\254\345\217\202\346\225\260", Q_NULLPTR));
        nameLabel->setText(QApplication::translate("RobotParaDialog", "\346\234\272\345\231\250\344\272\272\345\220\215\347\247\260", Q_NULLPTR));
        velocityLabel->setText(QApplication::translate("RobotParaDialog", "\351\200\237\345\272\246(m/s)", Q_NULLPTR));
        accelerationLabel->setText(QApplication::translate("RobotParaDialog", "\345\212\240\351\200\237\345\272\246(m/s^2)", Q_NULLPTR));
        jointVelocityLabel->setText(QApplication::translate("RobotParaDialog", "\345\205\263\350\212\202\351\200\237\345\272\246(rad/s)", Q_NULLPTR));
        jointAccelerationLabel->setText(QApplication::translate("RobotParaDialog", "\345\205\263\350\212\202\345\212\240\351\200\237\345\272\246(rad/s^2)", Q_NULLPTR));
        checkLabel->setText(QApplication::translate("RobotParaDialog", "\346\267\273\345\212\240\346\240\241\345\207\206\346\250\241\345\274\217", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("RobotParaDialog", "\350\277\220\345\212\250\345\255\246\345\217\202\346\225\260", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("RobotParaDialog", "\345\212\250\345\212\233\345\255\246\345\217\202\346\225\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RobotParaDialog: public Ui_RobotParaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTPARADIALOG_H
