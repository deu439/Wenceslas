/********************************************************************************
** Form generated from reading UI file 'wenceslasii.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WENCESLASII_H
#define UI_WENCESLASII_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WenceslasII
{
public:
    QAction *actionOpen;
    QAction *actionNew;
    QAction *actionImport;
    QAction *actionExportCSV;
    QAction *actionExportHTML;
    QAction *actionExportCSV1;
    QAction *actionExportHTML1;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_6;
    QTabWidget *tabWidget;
    QWidget *select_db;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *formWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *name;
    QLabel *label_2;
    QLineEdit *surname;
    QLabel *label_3;
    QLineEdit *address;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *id;
    QLabel *label_7;
    QSpinBox *age;
    QCheckBox *woman;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *create;
    QPushButton *correct;
    QPushButton *remove;
    QTableView *regTable;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *reg_original_order;
    QSpacerItem *horizontalSpacer_4;
    QWidget *capture_time;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QTableView *timeTable;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *clock;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *start_timer;
    QPushButton *clear_timer;
    QPushButton *record_time;
    QPushButton *remove_time;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *time_original_order;
    QSpacerItem *horizontalSpacer_5;
    QWidget *evaluate;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *eval;
    QSpacerItem *horizontalSpacer_3;
    QListWidget *evalList;
    QTableView *evalTable;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *eval_original_order;
    QComboBox *categoryComboBox;
    QSpacerItem *horizontalSpacer_6;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuResults;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WenceslasII)
    {
        if (WenceslasII->objectName().isEmpty())
            WenceslasII->setObjectName(QString::fromUtf8("WenceslasII"));
        WenceslasII->resize(812, 797);
        actionOpen = new QAction(WenceslasII);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionNew = new QAction(WenceslasII);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionImport = new QAction(WenceslasII);
        actionImport->setObjectName(QString::fromUtf8("actionImport"));
        actionImport->setEnabled(false);
        actionExportCSV = new QAction(WenceslasII);
        actionExportCSV->setObjectName(QString::fromUtf8("actionExportCSV"));
        actionExportCSV->setEnabled(false);
        actionExportHTML = new QAction(WenceslasII);
        actionExportHTML->setObjectName(QString::fromUtf8("actionExportHTML"));
        actionExportHTML->setEnabled(false);
        actionExportCSV1 = new QAction(WenceslasII);
        actionExportCSV1->setObjectName(QString::fromUtf8("actionExportCSV1"));
        actionExportCSV1->setEnabled(false);
        actionExportHTML1 = new QAction(WenceslasII);
        actionExportHTML1->setObjectName(QString::fromUtf8("actionExportHTML1"));
        actionExportHTML1->setEnabled(false);
        centralwidget = new QWidget(WenceslasII);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_6 = new QHBoxLayout(centralwidget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetNoConstraint);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(800, 0));
        tabWidget->setMaximumSize(QSize(800, 16777215));
        select_db = new QWidget();
        select_db->setObjectName(QString::fromUtf8("select_db"));
        verticalLayout_2 = new QVBoxLayout(select_db);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        formWidget = new QWidget(select_db);
        formWidget->setObjectName(QString::fromUtf8("formWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
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
        name->setMaximumSize(QSize(200, 16777215));
        name->setClearButtonEnabled(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, name);

        label_2 = new QLabel(formWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        surname = new QLineEdit(formWidget);
        surname->setObjectName(QString::fromUtf8("surname"));
        surname->setMaximumSize(QSize(200, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, surname);

        label_3 = new QLabel(formWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        address = new QLineEdit(formWidget);
        address->setObjectName(QString::fromUtf8("address"));
        address->setMaximumSize(QSize(300, 16777215));

        formLayout->setWidget(2, QFormLayout::FieldRole, address);

        label_4 = new QLabel(formWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        id = new QSpinBox(formWidget);
        id->setObjectName(QString::fromUtf8("id"));
        id->setMinimum(1);
        id->setMaximum(9999);

        horizontalLayout_2->addWidget(id);

        label_7 = new QLabel(formWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        age = new QSpinBox(formWidget);
        age->setObjectName(QString::fromUtf8("age"));
        age->setMinimum(0);
        age->setMaximum(120);
        age->setValue(0);

        horizontalLayout_2->addWidget(age);

        woman = new QCheckBox(formWidget);
        woman->setObjectName(QString::fromUtf8("woman"));
        woman->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(woman);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout_2);


        verticalLayout_4->addWidget(formWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        create = new QPushButton(select_db);
        create->setObjectName(QString::fromUtf8("create"));
        create->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(create->sizePolicy().hasHeightForWidth());
        create->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(create);

        correct = new QPushButton(select_db);
        correct->setObjectName(QString::fromUtf8("correct"));
        correct->setEnabled(false);
        sizePolicy1.setHeightForWidth(correct->sizePolicy().hasHeightForWidth());
        correct->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(correct);

        remove = new QPushButton(select_db);
        remove->setObjectName(QString::fromUtf8("remove"));
        remove->setEnabled(false);
        sizePolicy1.setHeightForWidth(remove->sizePolicy().hasHeightForWidth());
        remove->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(remove);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout_4);

        regTable = new QTableView(select_db);
        regTable->setObjectName(QString::fromUtf8("regTable"));
        regTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        regTable->setAutoScroll(true);
        regTable->setAlternatingRowColors(false);
        regTable->setSelectionMode(QAbstractItemView::SingleSelection);
        regTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        regTable->setTextElideMode(Qt::ElideRight);
        regTable->setShowGrid(false);
        regTable->horizontalHeader()->setMinimumSectionSize(30);
        regTable->horizontalHeader()->setStretchLastSection(true);
        regTable->verticalHeader()->setVisible(false);
        regTable->verticalHeader()->setStretchLastSection(false);

        verticalLayout_2->addWidget(regTable);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        reg_original_order = new QPushButton(select_db);
        reg_original_order->setObjectName(QString::fromUtf8("reg_original_order"));
        reg_original_order->setEnabled(false);

        horizontalLayout_7->addWidget(reg_original_order);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_7);

        tabWidget->addTab(select_db, QString());
        capture_time = new QWidget();
        capture_time->setObjectName(QString::fromUtf8("capture_time"));
        verticalLayout_3 = new QVBoxLayout(capture_time);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        timeTable = new QTableView(capture_time);
        timeTable->setObjectName(QString::fromUtf8("timeTable"));
        timeTable->setAlternatingRowColors(false);
        timeTable->setSelectionMode(QAbstractItemView::SingleSelection);
        timeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        timeTable->setShowGrid(false);
        timeTable->setGridStyle(Qt::SolidLine);
        timeTable->horizontalHeader()->setStretchLastSection(true);
        timeTable->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(timeTable);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        clock = new QLabel(capture_time);
        clock->setObjectName(QString::fromUtf8("clock"));
        QFont font;
        font.setPointSize(32);
        font.setBold(true);
        font.setWeight(75);
        clock->setFont(font);
        clock->setText(QString::fromUtf8("0:00.00"));
        clock->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(clock);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        start_timer = new QPushButton(capture_time);
        start_timer->setObjectName(QString::fromUtf8("start_timer"));

        horizontalLayout_10->addWidget(start_timer);

        clear_timer = new QPushButton(capture_time);
        clear_timer->setObjectName(QString::fromUtf8("clear_timer"));

        horizontalLayout_10->addWidget(clear_timer);


        verticalLayout_6->addLayout(horizontalLayout_10);

        record_time = new QPushButton(capture_time);
        record_time->setObjectName(QString::fromUtf8("record_time"));
        record_time->setEnabled(false);

        verticalLayout_6->addWidget(record_time);

        remove_time = new QPushButton(capture_time);
        remove_time->setObjectName(QString::fromUtf8("remove_time"));
        remove_time->setEnabled(false);

        verticalLayout_6->addWidget(remove_time);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_6->addItem(horizontalSpacer_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_6);


        horizontalLayout->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        time_original_order = new QPushButton(capture_time);
        time_original_order->setObjectName(QString::fromUtf8("time_original_order"));
        time_original_order->setEnabled(false);

        horizontalLayout_8->addWidget(time_original_order);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_8);

        tabWidget->addTab(capture_time, QString());
        evaluate = new QWidget();
        evaluate->setObjectName(QString::fromUtf8("evaluate"));
        verticalLayout_5 = new QVBoxLayout(evaluate);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        eval = new QPushButton(evaluate);
        eval->setObjectName(QString::fromUtf8("eval"));
        eval->setEnabled(false);

        horizontalLayout_5->addWidget(eval);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout_5);

        evalList = new QListWidget(evaluate);
        evalList->setObjectName(QString::fromUtf8("evalList"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(evalList->sizePolicy().hasHeightForWidth());
        evalList->setSizePolicy(sizePolicy2);

        verticalLayout_5->addWidget(evalList);

        evalTable = new QTableView(evaluate);
        evalTable->setObjectName(QString::fromUtf8("evalTable"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(2);
        sizePolicy3.setHeightForWidth(evalTable->sizePolicy().hasHeightForWidth());
        evalTable->setSizePolicy(sizePolicy3);
        evalTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        evalTable->setAlternatingRowColors(false);
        evalTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        evalTable->setShowGrid(false);
        evalTable->horizontalHeader()->setStretchLastSection(true);
        evalTable->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(evalTable);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        eval_original_order = new QPushButton(evaluate);
        eval_original_order->setObjectName(QString::fromUtf8("eval_original_order"));
        eval_original_order->setEnabled(false);

        horizontalLayout_9->addWidget(eval_original_order);

        categoryComboBox = new QComboBox(evaluate);
        categoryComboBox->setObjectName(QString::fromUtf8("categoryComboBox"));

        horizontalLayout_9->addWidget(categoryComboBox);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);


        verticalLayout_5->addLayout(horizontalLayout_9);

        tabWidget->addTab(evaluate, QString());

        horizontalLayout_6->addWidget(tabWidget);

        WenceslasII->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WenceslasII);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 812, 30));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuResults = new QMenu(menubar);
        menuResults->setObjectName(QString::fromUtf8("menuResults"));
        WenceslasII->setMenuBar(menubar);
        statusbar = new QStatusBar(WenceslasII);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WenceslasII->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuResults->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionNew);
        menuFile->addAction(actionImport);
        menuResults->addAction(actionExportCSV);
        menuResults->addAction(actionExportCSV1);
        menuResults->addAction(actionExportHTML);
        menuResults->addAction(actionExportHTML1);

        retranslateUi(WenceslasII);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WenceslasII);
    } // setupUi

    void retranslateUi(QMainWindow *WenceslasII)
    {
        WenceslasII->setWindowTitle(QCoreApplication::translate("WenceslasII", "Wenceslas II", nullptr));
        actionOpen->setText(QCoreApplication::translate("WenceslasII", "Otev\305\231\303\255t datab\303\241zi", nullptr));
        actionNew->setText(QCoreApplication::translate("WenceslasII", "Nov\303\241 datab\303\241ze", nullptr));
        actionImport->setText(QCoreApplication::translate("WenceslasII", "Importovat datab\303\241zi", nullptr));
        actionExportCSV->setText(QCoreApplication::translate("WenceslasII", "Exportovat do CSV (v po\305\231ad\303\255)", nullptr));
        actionExportHTML->setText(QCoreApplication::translate("WenceslasII", "Exportovat do HTML (v po\305\231ad\303\255)", nullptr));
        actionExportCSV1->setText(QCoreApplication::translate("WenceslasII", "Exportovat do CSV (dle kategorie)", nullptr));
        actionExportHTML1->setText(QCoreApplication::translate("WenceslasII", "Exportovat do HTML (dle kategorie)", nullptr));
        label->setText(QCoreApplication::translate("WenceslasII", "Jm\303\251no:", nullptr));
        label_2->setText(QCoreApplication::translate("WenceslasII", "P\305\231\303\255jmen\303\255:", nullptr));
        label_3->setText(QCoreApplication::translate("WenceslasII", "Bydli\305\241t\304\233:", nullptr));
        label_4->setText(QCoreApplication::translate("WenceslasII", "ID:", nullptr));
        label_7->setText(QCoreApplication::translate("WenceslasII", "V\304\233k:", nullptr));
        woman->setText(QCoreApplication::translate("WenceslasII", "\305\275ena", nullptr));
        create->setText(QCoreApplication::translate("WenceslasII", "Vytvo\305\231it (Enter)", nullptr));
#if QT_CONFIG(shortcut)
        create->setShortcut(QCoreApplication::translate("WenceslasII", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        correct->setText(QCoreApplication::translate("WenceslasII", "Opravit", nullptr));
        remove->setText(QCoreApplication::translate("WenceslasII", "Smazat", nullptr));
        reg_original_order->setText(QCoreApplication::translate("WenceslasII", "P\305\257vodn\303\255 po\305\231ad\303\255", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(select_db), QCoreApplication::translate("WenceslasII", "Registrace", nullptr));
        start_timer->setText(QCoreApplication::translate("WenceslasII", "Spustit stopky", nullptr));
        clear_timer->setText(QCoreApplication::translate("WenceslasII", "Vynulovat stopky", nullptr));
        record_time->setText(QCoreApplication::translate("WenceslasII", "Zapsat (Mezern\303\255k)", nullptr));
        remove_time->setText(QCoreApplication::translate("WenceslasII", "Smazat", nullptr));
        time_original_order->setText(QCoreApplication::translate("WenceslasII", "P\305\257vodn\303\255 po\305\231ad\303\255", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(capture_time), QCoreApplication::translate("WenceslasII", "Stopov\303\241n\303\255", nullptr));
        eval->setText(QCoreApplication::translate("WenceslasII", "Vyhodnotit", nullptr));
        eval_original_order->setText(QCoreApplication::translate("WenceslasII", "P\305\257vodn\303\255 po\305\231ad\303\255", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(evaluate), QCoreApplication::translate("WenceslasII", "Vyhodnocen\303\255", nullptr));
        menuFile->setTitle(QCoreApplication::translate("WenceslasII", "Soubor", nullptr));
        menuResults->setTitle(QCoreApplication::translate("WenceslasII", "V\303\275sledky", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WenceslasII: public Ui_WenceslasII {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WENCESLASII_H
