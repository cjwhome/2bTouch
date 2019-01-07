/********************************************************************************
** Form generated from reading UI file 'graphsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHSETTINGSDIALOG_H
#define UI_GRAPHSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_GraphSettingsDialog
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyButton;
    QGroupBox *selectBox;
    QGridLayout *gridLayout;
    QCheckBox *autoscaleYcheckbox;
    QCheckBox *autoscaleXcheckbox;

    void setupUi(QDialog *GraphSettingsDialog)
    {
        if (GraphSettingsDialog->objectName().isEmpty())
            GraphSettingsDialog->setObjectName(QStringLiteral("GraphSettingsDialog"));
        GraphSettingsDialog->resize(174, 140);
        gridLayout_3 = new QGridLayout(GraphSettingsDialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(96, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        applyButton = new QPushButton(GraphSettingsDialog);
        applyButton->setObjectName(QStringLiteral("applyButton"));

        horizontalLayout->addWidget(applyButton);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 2);

        selectBox = new QGroupBox(GraphSettingsDialog);
        selectBox->setObjectName(QStringLiteral("selectBox"));
        gridLayout = new QGridLayout(selectBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        autoscaleYcheckbox = new QCheckBox(selectBox);
        autoscaleYcheckbox->setObjectName(QStringLiteral("autoscaleYcheckbox"));

        gridLayout->addWidget(autoscaleYcheckbox, 0, 0, 1, 1);

        autoscaleXcheckbox = new QCheckBox(selectBox);
        autoscaleXcheckbox->setObjectName(QStringLiteral("autoscaleXcheckbox"));

        gridLayout->addWidget(autoscaleXcheckbox, 1, 0, 1, 1);


        gridLayout_3->addWidget(selectBox, 0, 0, 1, 1);


        retranslateUi(GraphSettingsDialog);

        QMetaObject::connectSlotsByName(GraphSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *GraphSettingsDialog)
    {
        GraphSettingsDialog->setWindowTitle(QApplication::translate("GraphSettingsDialog", "Settings", 0));
        applyButton->setText(QApplication::translate("GraphSettingsDialog", "Apply", 0));
        selectBox->setTitle(QApplication::translate("GraphSettingsDialog", "Select Axis Scaling", 0));
        autoscaleYcheckbox->setText(QApplication::translate("GraphSettingsDialog", "Autoscale Y", 0));
        autoscaleXcheckbox->setText(QApplication::translate("GraphSettingsDialog", "Autoscale X", 0));
    } // retranslateUi

};

namespace Ui {
    class GraphSettingsDialog: public Ui_GraphSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHSETTINGSDIALOG_H
