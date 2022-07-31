/********************************************************************************
** Form generated from reading UI file 'timer.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMER_H
#define UI_TIMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Timer
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *start_timer;
    QLabel *clock;
    QSpacerItem *horizontalSpacer;
    QTableView *view;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *write_down;
    QPushButton *remove;

    void setupUi(QWidget *Timer)
    {
        if (Timer->objectName().isEmpty())
            Timer->setObjectName(QString::fromUtf8("Timer"));
        Timer->resize(388, 728);
        verticalLayout_2 = new QVBoxLayout(Timer);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        start_timer = new QPushButton(Timer);
        start_timer->setObjectName(QString::fromUtf8("start_timer"));

        horizontalLayout->addWidget(start_timer);

        clock = new QLabel(Timer);
        clock->setObjectName(QString::fromUtf8("clock"));
        QFont font;
        font.setPointSize(17);
        font.setBold(true);
        font.setWeight(75);
        clock->setFont(font);
        clock->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(clock);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        view = new QTableView(Timer);
        view->setObjectName(QString::fromUtf8("view"));
        view->setAlternatingRowColors(true);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->setShowGrid(false);
        view->setGridStyle(Qt::SolidLine);
        view->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(view);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        write_down = new QPushButton(Timer);
        write_down->setObjectName(QString::fromUtf8("write_down"));

        horizontalLayout_2->addWidget(write_down);

        remove = new QPushButton(Timer);
        remove->setObjectName(QString::fromUtf8("remove"));

        horizontalLayout_2->addWidget(remove);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Timer);

        QMetaObject::connectSlotsByName(Timer);
    } // setupUi

    void retranslateUi(QWidget *Timer)
    {
        Timer->setWindowTitle(QCoreApplication::translate("Timer", "Form", nullptr));
        start_timer->setText(QCoreApplication::translate("Timer", "Spustit stopky", nullptr));
        clock->setText(QCoreApplication::translate("Timer", "0:00.00", nullptr));
        write_down->setText(QCoreApplication::translate("Timer", "Zapsat (Mezern\303\255k)", nullptr));
        remove->setText(QCoreApplication::translate("Timer", "Smazat (Delete)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Timer: public Ui_Timer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMER_H
