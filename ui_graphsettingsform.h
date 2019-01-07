/********************************************************************************
** Form generated from reading UI file 'graphsettingsform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHSETTINGSFORM_H
#define UI_GRAPHSETTINGSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphSettingsForm
{
public:
    QGroupBox *selectBox;
    QGridLayout *gridLayout;
    QCheckBox *autoscaleYcheckbox;
    QCheckBox *autoscaleXcheckbox;
    QPushButton *applyButton;

    void setupUi(QWidget *GraphSettingsForm)
    {
        if (GraphSettingsForm->objectName().isEmpty())
            GraphSettingsForm->setObjectName(QStringLiteral("GraphSettingsForm"));
        GraphSettingsForm->resize(150, 175);
        GraphSettingsForm->setMinimumSize(QSize(150, 175));
        GraphSettingsForm->setMaximumSize(QSize(150, 175));
        selectBox = new QGroupBox(GraphSettingsForm);
        selectBox->setObjectName(QStringLiteral("selectBox"));
        selectBox->setGeometry(QRect(10, 10, 134, 114));
        gridLayout = new QGridLayout(selectBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        autoscaleYcheckbox = new QCheckBox(selectBox);
        autoscaleYcheckbox->setObjectName(QStringLiteral("autoscaleYcheckbox"));

        gridLayout->addWidget(autoscaleYcheckbox, 0, 0, 1, 1);

        autoscaleXcheckbox = new QCheckBox(selectBox);
        autoscaleXcheckbox->setObjectName(QStringLiteral("autoscaleXcheckbox"));

        gridLayout->addWidget(autoscaleXcheckbox, 1, 0, 1, 1);

        applyButton = new QPushButton(GraphSettingsForm);
        applyButton->setObjectName(QStringLiteral("applyButton"));
        applyButton->setGeometry(QRect(30, 130, 93, 28));

        retranslateUi(GraphSettingsForm);

        QMetaObject::connectSlotsByName(GraphSettingsForm);
    } // setupUi

    void retranslateUi(QWidget *GraphSettingsForm)
    {
        GraphSettingsForm->setWindowTitle(QApplication::translate("GraphSettingsForm", "Form", 0));
        selectBox->setTitle(QApplication::translate("GraphSettingsForm", "Select Axis Scaling", 0));
        autoscaleYcheckbox->setText(QApplication::translate("GraphSettingsForm", "Autoscale Y", 0));
        autoscaleXcheckbox->setText(QApplication::translate("GraphSettingsForm", "Autoscale X", 0));
        applyButton->setText(QApplication::translate("GraphSettingsForm", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class GraphSettingsForm: public Ui_GraphSettingsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHSETTINGSFORM_H
