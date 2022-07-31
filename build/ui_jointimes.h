/********************************************************************************
** Form generated from reading UI file 'jointimes.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINTIMES_H
#define UI_JOINTIMES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JoinTimes
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QPushButton *correct;
    QLabel *label;
    QSpinBox *mins;
    QDoubleSpinBox *sec;
    QTableView *table_view;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *zeny_min;
    QSpinBox *muzi_min;
    QLabel *label_4;
    QDoubleSpinBox *muzi_sec;
    QDoubleSpinBox *zeny_sec;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *muzi_add;
    QPushButton *zeny_add;
    QPushButton *muzi_sub;
    QPushButton *zeny_sub;
    QHBoxLayout *horizontalLayout;
    QPushButton *csv;
    QPushButton *html;

    void setupUi(QWidget *JoinTimes)
    {
        if (JoinTimes->objectName().isEmpty())
            JoinTimes->setObjectName(QString::fromUtf8("JoinTimes"));
        JoinTimes->resize(578, 830);
        verticalLayout = new QVBoxLayout(JoinTimes);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox = new QComboBox(JoinTimes);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 3, 1, 1);

        correct = new QPushButton(JoinTimes);
        correct->setObjectName(QString::fromUtf8("correct"));

        gridLayout->addWidget(correct, 0, 4, 1, 1);

        label = new QLabel(JoinTimes);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(5, 16777215));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        mins = new QSpinBox(JoinTimes);
        mins->setObjectName(QString::fromUtf8("mins"));
        mins->setMaximumSize(QSize(70, 16777215));
        mins->setMaximum(9999);

        gridLayout->addWidget(mins, 0, 0, 1, 1);

        sec = new QDoubleSpinBox(JoinTimes);
        sec->setObjectName(QString::fromUtf8("sec"));
        sec->setMaximumSize(QSize(70, 16777215));
        sec->setMaximum(59.990000000000002);

        gridLayout->addWidget(sec, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        table_view = new QTableView(JoinTimes);
        table_view->setObjectName(QString::fromUtf8("table_view"));
        table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_view->setAlternatingRowColors(true);
        table_view->setSelectionMode(QAbstractItemView::SingleSelection);
        table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_view->setShowGrid(false);
        table_view->setSortingEnabled(false);

        verticalLayout->addWidget(table_view);

        groupBox = new QGroupBox(JoinTimes);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        zeny_min = new QSpinBox(groupBox);
        zeny_min->setObjectName(QString::fromUtf8("zeny_min"));
        zeny_min->setMinimumSize(QSize(60, 0));
        zeny_min->setMaximum(9999);

        gridLayout_2->addWidget(zeny_min, 1, 1, 1, 1);

        muzi_min = new QSpinBox(groupBox);
        muzi_min->setObjectName(QString::fromUtf8("muzi_min"));
        muzi_min->setMinimumSize(QSize(60, 0));
        muzi_min->setMaximum(9999);

        gridLayout_2->addWidget(muzi_min, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(5, 16777215));

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        muzi_sec = new QDoubleSpinBox(groupBox);
        muzi_sec->setObjectName(QString::fromUtf8("muzi_sec"));
        muzi_sec->setMinimumSize(QSize(60, 0));
        muzi_sec->setMaximum(60.990000000000002);

        gridLayout_2->addWidget(muzi_sec, 0, 3, 1, 1);

        zeny_sec = new QDoubleSpinBox(groupBox);
        zeny_sec->setObjectName(QString::fromUtf8("zeny_sec"));
        zeny_sec->setMinimumSize(QSize(60, 0));
        zeny_sec->setMaximum(60.990000000000002);

        gridLayout_2->addWidget(zeny_sec, 1, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(5, 16777215));

        gridLayout_2->addWidget(label_5, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 6, 2, 1);

        muzi_add = new QPushButton(groupBox);
        muzi_add->setObjectName(QString::fromUtf8("muzi_add"));

        gridLayout_2->addWidget(muzi_add, 0, 4, 1, 1);

        zeny_add = new QPushButton(groupBox);
        zeny_add->setObjectName(QString::fromUtf8("zeny_add"));

        gridLayout_2->addWidget(zeny_add, 1, 4, 1, 1);

        muzi_sub = new QPushButton(groupBox);
        muzi_sub->setObjectName(QString::fromUtf8("muzi_sub"));

        gridLayout_2->addWidget(muzi_sub, 0, 5, 1, 1);

        zeny_sub = new QPushButton(groupBox);
        zeny_sub->setObjectName(QString::fromUtf8("zeny_sub"));

        gridLayout_2->addWidget(zeny_sub, 1, 5, 1, 1);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        csv = new QPushButton(JoinTimes);
        csv->setObjectName(QString::fromUtf8("csv"));

        horizontalLayout->addWidget(csv);

        html = new QPushButton(JoinTimes);
        html->setObjectName(QString::fromUtf8("html"));

        horizontalLayout->addWidget(html);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(JoinTimes);

        QMetaObject::connectSlotsByName(JoinTimes);
    } // setupUi

    void retranslateUi(QWidget *JoinTimes)
    {
        JoinTimes->setWindowTitle(QCoreApplication::translate("JoinTimes", "Form", nullptr));
        correct->setText(QCoreApplication::translate("JoinTimes", "Opravit", nullptr));
        label->setText(QCoreApplication::translate("JoinTimes", ":", nullptr));
        groupBox->setTitle(QCoreApplication::translate("JoinTimes", "Offsety", nullptr));
        label_2->setText(QCoreApplication::translate("JoinTimes", "Offset mu\305\276i:", nullptr));
        label_3->setText(QCoreApplication::translate("JoinTimes", "Offset \305\276eny:", nullptr));
        label_4->setText(QCoreApplication::translate("JoinTimes", ":", nullptr));
        label_5->setText(QCoreApplication::translate("JoinTimes", ":", nullptr));
        muzi_add->setText(QCoreApplication::translate("JoinTimes", "P\305\231i\304\215\303\255st", nullptr));
        zeny_add->setText(QCoreApplication::translate("JoinTimes", "P\305\231i\304\215\303\255st", nullptr));
        muzi_sub->setText(QCoreApplication::translate("JoinTimes", "Ode\304\215\303\255st", nullptr));
        zeny_sub->setText(QCoreApplication::translate("JoinTimes", "Ode\304\215\303\255st", nullptr));
        csv->setText(QCoreApplication::translate("JoinTimes", "Export CSV", nullptr));
        html->setText(QCoreApplication::translate("JoinTimes", "Export HTML", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JoinTimes: public Ui_JoinTimes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINTIMES_H
