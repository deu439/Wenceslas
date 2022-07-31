/********************************************************************************
** Form generated from reading UI file 'choosedatabase.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEDATABASE_H
#define UI_CHOOSEDATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseDatabase
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QPushButton *open_file;
    QLineEdit *show_file;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLabel *n_cat;
    QLabel *label_5;
    QLabel *n_run;
    QLabel *label_7;
    QLabel *hash;
    QLabel *label;
    QLabel *op;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ChooseDatabase)
    {
        if (ChooseDatabase->objectName().isEmpty())
            ChooseDatabase->setObjectName(QString::fromUtf8("ChooseDatabase"));
        ChooseDatabase->resize(495, 213);
        verticalLayout = new QVBoxLayout(ChooseDatabase);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        open_file = new QPushButton(ChooseDatabase);
        open_file->setObjectName(QString::fromUtf8("open_file"));

        formLayout->setWidget(0, QFormLayout::LabelRole, open_file);

        show_file = new QLineEdit(ChooseDatabase);
        show_file->setObjectName(QString::fromUtf8("show_file"));
        show_file->setEnabled(true);
        show_file->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, show_file);


        verticalLayout->addLayout(formLayout);

        groupBox = new QGroupBox(ChooseDatabase);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        n_cat = new QLabel(groupBox);
        n_cat->setObjectName(QString::fromUtf8("n_cat"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, n_cat);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        n_run = new QLabel(groupBox);
        n_run->setObjectName(QString::fromUtf8("n_run"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, n_run);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_7);

        hash = new QLabel(groupBox);
        hash->setObjectName(QString::fromUtf8("hash"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, hash);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        op = new QLabel(groupBox);
        op->setObjectName(QString::fromUtf8("op"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, op);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(ChooseDatabase);

        QMetaObject::connectSlotsByName(ChooseDatabase);
    } // setupUi

    void retranslateUi(QWidget *ChooseDatabase)
    {
        ChooseDatabase->setWindowTitle(QCoreApplication::translate("ChooseDatabase", "Form", nullptr));
        open_file->setText(QCoreApplication::translate("ChooseDatabase", "Zvolte soubor datab\303\241ze", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ChooseDatabase", "Zkontrolujte \303\272daje o datab\303\241zi", nullptr));
        label_3->setText(QCoreApplication::translate("ChooseDatabase", "Po\304\215et kategori\303\255:", nullptr));
        n_cat->setText(QCoreApplication::translate("ChooseDatabase", "0", nullptr));
        label_5->setText(QCoreApplication::translate("ChooseDatabase", "Po\304\215et b\304\233\305\276c\305\257:", nullptr));
        n_run->setText(QCoreApplication::translate("ChooseDatabase", "0", nullptr));
        label_7->setText(QCoreApplication::translate("ChooseDatabase", "Hash datab\303\241ze:", nullptr));
#if QT_CONFIG(tooltip)
        hash->setToolTip(QCoreApplication::translate("ChooseDatabase", "<html><head/><body><p>Hash po\304\215\303\241te\304\215n\303\255 datab\303\241ze se mus\303\255 shodovat mezi v\305\241emi po\304\215\303\255ta\304\215i.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        hash->setText(QString());
        label->setText(QCoreApplication::translate("ChooseDatabase", "Oper\303\241tor:", nullptr));
        op->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChooseDatabase: public Ui_ChooseDatabase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEDATABASE_H
