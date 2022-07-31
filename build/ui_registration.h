/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QListView *listView;
    QWidget *formWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *name;
    QLabel *label_2;
    QLineEdit *surname;
    QLabel *label_3;
    QLineEdit *location;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *id;
    QLabel *label_7;
    QSpinBox *age;
    QRadioButton *man;
    QRadioButton *woman;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QLabel *category;
    QPushButton *synchronize;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *create;
    QPushButton *correct;
    QPushButton *remove;
    QTableView *data_view;

    void setupUi(QWidget *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QString::fromUtf8("Registration"));
        Registration->resize(696, 502);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Registration->sizePolicy().hasHeightForWidth());
        Registration->setSizePolicy(sizePolicy);
        Registration->setMinimumSize(QSize(0, 0));
        Registration->setBaseSize(QSize(800, 800));
        verticalLayout_2 = new QVBoxLayout(Registration);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listView = new QListView(Registration);
        listView->setObjectName(QString::fromUtf8("listView"));
        sizePolicy.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy);
        listView->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(listView, 0, 1, 1, 1);

        formWidget = new QWidget(Registration);
        formWidget->setObjectName(QString::fromUtf8("formWidget"));
        sizePolicy.setHeightForWidth(formWidget->sizePolicy().hasHeightForWidth());
        formWidget->setSizePolicy(sizePolicy);
        formWidget->setMaximumSize(QSize(16777215, 16777215));
        formLayout = new QFormLayout(formWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMinimumSize);
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label = new QLabel(formWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        name = new QLineEdit(formWidget);
        name->setObjectName(QString::fromUtf8("name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, name);

        label_2 = new QLabel(formWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        surname = new QLineEdit(formWidget);
        surname->setObjectName(QString::fromUtf8("surname"));

        formLayout->setWidget(1, QFormLayout::FieldRole, surname);

        label_3 = new QLabel(formWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        location = new QLineEdit(formWidget);
        location->setObjectName(QString::fromUtf8("location"));

        formLayout->setWidget(2, QFormLayout::FieldRole, location);

        label_4 = new QLabel(formWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        id = new QSpinBox(formWidget);
        id->setObjectName(QString::fromUtf8("id"));
        id->setMaximum(9999);

        horizontalLayout_2->addWidget(id);

        label_7 = new QLabel(formWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        age = new QSpinBox(formWidget);
        age->setObjectName(QString::fromUtf8("age"));
        age->setMinimum(1);

        horizontalLayout_2->addWidget(age);

        man = new QRadioButton(formWidget);
        man->setObjectName(QString::fromUtf8("man"));
        man->setChecked(true);

        horizontalLayout_2->addWidget(man);

        woman = new QRadioButton(formWidget);
        woman->setObjectName(QString::fromUtf8("woman"));

        horizontalLayout_2->addWidget(woman);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout_2);

        label_5 = new QLabel(formWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        category = new QLabel(formWidget);
        category->setObjectName(QString::fromUtf8("category"));

        formLayout->setWidget(4, QFormLayout::FieldRole, category);


        gridLayout->addWidget(formWidget, 0, 0, 1, 1);

        synchronize = new QPushButton(Registration);
        synchronize->setObjectName(QString::fromUtf8("synchronize"));
        synchronize->setEnabled(false);

        gridLayout->addWidget(synchronize, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        create = new QPushButton(Registration);
        create->setObjectName(QString::fromUtf8("create"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(create->sizePolicy().hasHeightForWidth());
        create->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(create);

        correct = new QPushButton(Registration);
        correct->setObjectName(QString::fromUtf8("correct"));
        sizePolicy1.setHeightForWidth(correct->sizePolicy().hasHeightForWidth());
        correct->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(correct);

        remove = new QPushButton(Registration);
        remove->setObjectName(QString::fromUtf8("remove"));
        sizePolicy1.setHeightForWidth(remove->sizePolicy().hasHeightForWidth());
        remove->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(remove);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        data_view = new QTableView(Registration);
        data_view->setObjectName(QString::fromUtf8("data_view"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(data_view->sizePolicy().hasHeightForWidth());
        data_view->setSizePolicy(sizePolicy2);
        data_view->setMinimumSize(QSize(600, 200));
        data_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        data_view->setAlternatingRowColors(true);
        data_view->setSelectionMode(QAbstractItemView::SingleSelection);
        data_view->setSelectionBehavior(QAbstractItemView::SelectRows);
        data_view->setIconSize(QSize(0, 0));
        data_view->setShowGrid(false);
        data_view->setSortingEnabled(true);
        data_view->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(data_view);

        QWidget::setTabOrder(name, surname);
        QWidget::setTabOrder(surname, location);
        QWidget::setTabOrder(location, id);
        QWidget::setTabOrder(id, age);
        QWidget::setTabOrder(age, man);
        QWidget::setTabOrder(man, woman);
        QWidget::setTabOrder(woman, create);
        QWidget::setTabOrder(create, correct);
        QWidget::setTabOrder(correct, remove);
        QWidget::setTabOrder(remove, data_view);
        QWidget::setTabOrder(data_view, listView);
        QWidget::setTabOrder(listView, synchronize);

        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QWidget *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Form", nullptr));
        label->setText(QCoreApplication::translate("Registration", "Jm\303\251no:", nullptr));
        label_2->setText(QCoreApplication::translate("Registration", "P\305\231\303\255jmen\303\255:", nullptr));
        label_3->setText(QCoreApplication::translate("Registration", "Bydli\305\241t\304\233:", nullptr));
        label_4->setText(QCoreApplication::translate("Registration", "ID:", nullptr));
        label_7->setText(QCoreApplication::translate("Registration", "V\304\233k:", nullptr));
        man->setText(QCoreApplication::translate("Registration", "Mu\305\276", nullptr));
        woman->setText(QCoreApplication::translate("Registration", "\305\275ena", nullptr));
        label_5->setText(QCoreApplication::translate("Registration", "Kategorie:", nullptr));
        category->setText(QCoreApplication::translate("Registration", "-", nullptr));
        synchronize->setText(QCoreApplication::translate("Registration", "Sychronizovat", nullptr));
        create->setText(QCoreApplication::translate("Registration", "Vytvo\305\231it (Enter)", nullptr));
#if QT_CONFIG(shortcut)
        create->setShortcut(QCoreApplication::translate("Registration", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        correct->setText(QCoreApplication::translate("Registration", "Opravit", nullptr));
        remove->setText(QCoreApplication::translate("Registration", "Smazat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
