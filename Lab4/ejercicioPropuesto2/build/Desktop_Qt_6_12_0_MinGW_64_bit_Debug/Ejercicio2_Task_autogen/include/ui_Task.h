/********************************************************************************
** Form generated from reading UI file 'task.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_H
#define UI_TASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Task
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *Mitext;
    QCheckBox *checkbox;

    void setupUi(QWidget *Task)
    {
        if (Task->objectName().isEmpty())
            Task->setObjectName("Task");
        Task->resize(400, 300);
        horizontalLayout = new QHBoxLayout(Task);
        horizontalLayout->setObjectName("horizontalLayout");
        Mitext = new QLineEdit(Task);
        Mitext->setObjectName("Mitext");

        horizontalLayout->addWidget(Mitext);

        checkbox = new QCheckBox(Task);
        checkbox->setObjectName("checkbox");

        horizontalLayout->addWidget(checkbox);


        retranslateUi(Task);

        QMetaObject::connectSlotsByName(Task);
    } // setupUi

    void retranslateUi(QWidget *Task)
    {
        Task->setWindowTitle(QCoreApplication::translate("Task", "Form", nullptr));
        checkbox->setText(QCoreApplication::translate("Task", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Task: public Ui_Task {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_H
