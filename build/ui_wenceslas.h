/********************************************************************************
** Form generated from reading UI file 'wenceslas.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WENCESLAS_H
#define UI_WENCESLAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Wenceslas
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *vyber;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout;
    QPushButton *fileOpen;
    QLineEdit *fileName;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_12;
    QLabel *dbHash;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *numCategories;
    QLabel *label_8;
    QLabel *numRunners;
    QLabel *label_10;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_4;
    QFormLayout *formLayout_3;
    QLabel *idRegLabel;
    QSpinBox *idReg;
    QSpacerItem *verticalSpacer;
    QWidget *reg;
    QGridLayout *gridLayout;
    QFrame *line;
    QTableView *seznam;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QListWidget *listWidget;
    QPushButton *synchronize;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QLineEdit *jmeno;
    QLabel *label_3;
    QLineEdit *bydliste;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QRadioButton *zena;
    QRadioButton *muz;
    QLabel *label_4;
    QSpinBox *vek;
    QLabel *kategorie;
    QLabel *label;
    QSpinBox *id;
    QHBoxLayout *horizontalLayout;
    QPushButton *vytvor;
    QPushButton *oprav;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *stop;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Wenceslas)
    {
        if (Wenceslas->objectName().isEmpty())
            Wenceslas->setObjectName(QString::fromUtf8("Wenceslas"));
        Wenceslas->resize(931, 546);
        Wenceslas->setMaximumSize(QSize(16777215, 16777215));
        centralWidget = new QWidget(Wenceslas);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        vyber = new QWidget();
        vyber->setObjectName(QString::fromUtf8("vyber"));
        verticalLayout_3 = new QVBoxLayout(vyber);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMinimumSize);
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        fileOpen = new QPushButton(vyber);
        fileOpen->setObjectName(QString::fromUtf8("fileOpen"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        fileOpen->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, fileOpen);

        fileName = new QLineEdit(vyber);
        fileName->setObjectName(QString::fromUtf8("fileName"));
        fileName->setMaximumSize(QSize(16777215, 16777215));
        fileName->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, fileName);


        verticalLayout_3->addLayout(formLayout);

        groupBox = new QGroupBox(vyber);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_12->setFont(font1);

        horizontalLayout_5->addWidget(label_12);

        dbHash = new QLabel(groupBox);
        dbHash->setObjectName(QString::fromUtf8("dbHash"));
        dbHash->setFont(font1);

        horizontalLayout_5->addWidget(dbHash);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        numCategories = new QLabel(groupBox);
        numCategories->setObjectName(QString::fromUtf8("numCategories"));

        horizontalLayout_4->addWidget(numCategories);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_4->addWidget(label_8);

        numRunners = new QLabel(groupBox);
        numRunners->setObjectName(QString::fromUtf8("numRunners"));

        horizontalLayout_4->addWidget(numRunners);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_4->addWidget(label_10);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_4->addWidget(label_11);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(groupBox);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        formLayout_3->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        idRegLabel = new QLabel(vyber);
        idRegLabel->setObjectName(QString::fromUtf8("idRegLabel"));
        idRegLabel->setFont(font);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, idRegLabel);

        idReg = new QSpinBox(vyber);
        idReg->setObjectName(QString::fromUtf8("idReg"));
        idReg->setMinimum(1);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, idReg);


        verticalLayout_3->addLayout(formLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget->addTab(vyber, QString());
        reg = new QWidget();
        reg->setObjectName(QString::fromUtf8("reg"));
        gridLayout = new QGridLayout(reg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        line = new QFrame(reg);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 4, 0, 1, 1);

        seznam = new QTableView(reg);
        seznam->setObjectName(QString::fromUtf8("seznam"));
        seznam->setAlternatingRowColors(true);
        seznam->setSelectionBehavior(QAbstractItemView::SelectRows);
        seznam->setSortingEnabled(true);
        seznam->horizontalHeader()->setCascadingSectionResizes(false);
        seznam->horizontalHeader()->setStretchLastSection(true);
        seznam->verticalHeader()->setVisible(false);

        gridLayout->addWidget(seznam, 5, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        listWidget = new QListWidget(reg);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_5->addWidget(listWidget);

        synchronize = new QPushButton(reg);
        synchronize->setObjectName(QString::fromUtf8("synchronize"));

        verticalLayout_5->addWidget(synchronize);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label_2 = new QLabel(reg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        jmeno = new QLineEdit(reg);
        jmeno->setObjectName(QString::fromUtf8("jmeno"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, jmeno);

        label_3 = new QLabel(reg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        bydliste = new QLineEdit(reg);
        bydliste->setObjectName(QString::fromUtf8("bydliste"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, bydliste);


        verticalLayout_2->addLayout(formLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        zena = new QRadioButton(reg);
        zena->setObjectName(QString::fromUtf8("zena"));

        horizontalLayout_3->addWidget(zena);

        muz = new QRadioButton(reg);
        muz->setObjectName(QString::fromUtf8("muz"));
        muz->setChecked(true);

        horizontalLayout_3->addWidget(muz);

        label_4 = new QLabel(reg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_4);

        vek = new QSpinBox(reg);
        vek->setObjectName(QString::fromUtf8("vek"));
        vek->setMaximum(120);

        horizontalLayout_3->addWidget(vek);

        kategorie = new QLabel(reg);
        kategorie->setObjectName(QString::fromUtf8("kategorie"));
        kategorie->setMinimumSize(QSize(200, 0));
        kategorie->setFont(font);
        kategorie->setFrameShape(QFrame::Box);
        kategorie->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(kategorie);

        label = new QLabel(reg);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label);

        id = new QSpinBox(reg);
        id->setObjectName(QString::fromUtf8("id"));
        id->setMaximum(999);

        horizontalLayout_3->addWidget(id);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        vytvor = new QPushButton(reg);
        vytvor->setObjectName(QString::fromUtf8("vytvor"));

        horizontalLayout->addWidget(vytvor);

        oprav = new QPushButton(reg);
        oprav->setObjectName(QString::fromUtf8("oprav"));

        horizontalLayout->addWidget(oprav);

        pushButton = new QPushButton(reg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(reg, QString());
        stop = new QWidget();
        stop->setObjectName(QString::fromUtf8("stop"));
        tabWidget->addTab(stop, QString());

        verticalLayout->addWidget(tabWidget);

        Wenceslas->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Wenceslas);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Wenceslas->setStatusBar(statusBar);

        retranslateUi(Wenceslas);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Wenceslas);
    } // setupUi

    void retranslateUi(QMainWindow *Wenceslas)
    {
        Wenceslas->setWindowTitle(QCoreApplication::translate("Wenceslas", "Wenceslas", nullptr));
        fileOpen->setText(QCoreApplication::translate("Wenceslas", "Vyberte soubor datab\303\241ze", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Wenceslas", "Parametry datab\303\241ze", nullptr));
        label_12->setText(QCoreApplication::translate("Wenceslas", "Hash datab\303\241ze:", nullptr));
#if QT_CONFIG(tooltip)
        dbHash->setToolTip(QCoreApplication::translate("Wenceslas", "<html><head/><body><p>P\305\231ed zah\303\241jen\303\255m registrace z\303\241vodn\303\255k\305\257 je vhodn\303\251 zkontrolovat alespo\305\210 n\304\233kolik po\304\215\303\241te\304\215n\303\255ch znak\305\257 tohoto hashe s ostatn\303\255mi registr\303\241tory. Pokud se u v\305\241ech tyto hashe neshoduj\303\255, z\305\231ejmn\304\233 ka\305\276d\303\275 pracuje s jinou v\303\275choz\303\255 datab\303\241z\303\255, co\305\276 m\305\257\305\276e zp\305\257sobit chyby p\305\231i vyhodnocen\303\255.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        dbHash->setText(QString());
        label_6->setText(QCoreApplication::translate("Wenceslas", "Po\304\215et kategori\303\255:", nullptr));
        numCategories->setText(QCoreApplication::translate("Wenceslas", "0", nullptr));
        label_8->setText(QCoreApplication::translate("Wenceslas", "Registrovan\303\255 b\304\233\305\276ci:", nullptr));
        numRunners->setText(QCoreApplication::translate("Wenceslas", "0", nullptr));
        label_10->setText(QCoreApplication::translate("Wenceslas", "Zaznamenan\303\251 \304\215asy:", nullptr));
        label_11->setText(QCoreApplication::translate("Wenceslas", "0", nullptr));
        idRegLabel->setText(QCoreApplication::translate("Wenceslas", "Zvolte unik\303\241tn\303\255 ID registr\303\241tora:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(vyber), QCoreApplication::translate("Wenceslas", "V\303\275b\304\233r datab\303\241ze", nullptr));
        synchronize->setText(QCoreApplication::translate("Wenceslas", "Synchronizovat", nullptr));
        label_2->setText(QCoreApplication::translate("Wenceslas", "Jm\303\251no:", nullptr));
        label_3->setText(QCoreApplication::translate("Wenceslas", "Bydli\305\241t\304\233:", nullptr));
        zena->setText(QCoreApplication::translate("Wenceslas", "\305\275ena", nullptr));
        muz->setText(QCoreApplication::translate("Wenceslas", "Mu\305\276", nullptr));
        label_4->setText(QCoreApplication::translate("Wenceslas", "V\304\233k:", nullptr));
        kategorie->setText(QString());
        label->setText(QCoreApplication::translate("Wenceslas", "ID:", nullptr));
        vytvor->setText(QCoreApplication::translate("Wenceslas", "Vytvo\305\231it z\303\241znam", nullptr));
        oprav->setText(QCoreApplication::translate("Wenceslas", "Opravit z\303\241znam", nullptr));
        pushButton->setText(QCoreApplication::translate("Wenceslas", "Vy\304\215istit formul\303\241\305\231", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(reg), QCoreApplication::translate("Wenceslas", "Registrace z\303\241vodn\303\255k\305\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(stop), QCoreApplication::translate("Wenceslas", "Stopov\303\241n\303\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Wenceslas: public Ui_Wenceslas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WENCESLAS_H
