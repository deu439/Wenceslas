/*
 * Copyright 2020 Jan Dorazil <deu439@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "wenceslasii.h"
#include "ui_wenceslasii.h"
#include "mygenderitemdelegate.h"
#include "mytimeitemdelegate.h"
#include "filtertableheader.h"
#include "noteditabledelegate.h"
#include "uploadresultsdialog.h"
#include "resultsupload.h"

#include <QDebug>
#include <QStringBuilder>
#include <math.h>
#include <algorithm>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QKeyEvent>
#include <QListWidgetItem>
#include <QMap>
#include <QComboBox>
#include <QDateTime>
#include <QItemDelegate>

// Global variable keeping all the categories
MyCategories cats;

struct {
    bool operator()(EvalTableModel::Record a, EvalTableModel::Record b) const
    { 
        return a.value(7).toInt() < b.value(7).toInt();
    }
} ByOrder;


struct {
    bool operator()(EvalTableModel::Record a, EvalTableModel::Record b) const
    { 
        
        // Find category id and time of a and b
        int id_a = a.value(6).toInt();
        int time_a = a.value(7).toInt();
        int id_b = b.value(6).toInt();
        int time_b = b.value(7).toInt();
        
        if (id_a < id_b) return true;
        if (id_b < id_a) return false;
        
        // a=b for primary condition, go to secondary
        if (time_a < time_b) return true;
        if (time_b < time_a) return false;
        
        return false;
    }
} ByOrderAndCategory;


struct {
    bool operator()(int a, int b) const { return a > b; }
} descInt;


// Mapper delegate that does not consume the Esc key, so it can reach the clear button shortcut
class NoEscapeDelegate : public QItemDelegate
{
public:
    using QItemDelegate::QItemDelegate;

protected:
    bool eventFilter(QObject *o, QEvent *e) override
    {
        if (e->type() == QEvent::ShortcutOverride || e->type() == QEvent::KeyPress) {
            if (static_cast<QKeyEvent *>(e)->key() == Qt::Key_Escape) return false;
        }
        return QItemDelegate::eventFilter(o, e);
    }
};


WenceslasII::WenceslasII(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::WenceslasII),
    timer(parent)
{
    ui->setupUi(this);
    
    // Setup main menu
    connect(ui->actionOpen, &QAction::triggered, this, &WenceslasII::openFile);
    connect(ui->actionNew, &QAction::triggered, this, &WenceslasII::newFile);
    connect(ui->actionImport, &QAction::triggered, this, &WenceslasII::importFile);
    connect(ui->actionExportCSV, &QAction::triggered, this, &WenceslasII::actionExportCSV);
    connect(ui->actionExportCSV1, &QAction::triggered, this, &WenceslasII::actionExportCSV1);
    connect(ui->actionExportCSV2, &QAction::triggered, this, &WenceslasII::actionExportCSV2);
    connect(ui->actionExportCSV3, &QAction::triggered, this, &WenceslasII::actionExportCSV3);
    connect(ui->actionExportHTML, &QAction::triggered, this, &WenceslasII::actionExportHTML);
    connect(ui->actionExportHTML1, &QAction::triggered, this, &WenceslasII::actionExportHTML1);
    connect(ui->actionExportHTML2, &QAction::triggered, this, &WenceslasII::actionExportHTML2);
    connect(ui->actionExportHTML3, &QAction::triggered, this, &WenceslasII::actionExportHTML3);
    connect(ui->actionPrint, &QAction::triggered, this, &WenceslasII::actionPrint);
    connect(ui->actionPrintSelection, &QAction::triggered, this, &WenceslasII::actionPrintSelection);
    
    // Upload evaluation results to the website (beh.farnostsj.cz)
    uploadAction = new QAction(tr("Odeslat výsledky na web…"), this);
    uploadAction->setEnabled(false);
    ui->menuResults->addSeparator();
    ui->menuResults->addAction(uploadAction);
    connect(uploadAction, &QAction::triggered, this, &WenceslasII::uploadResults);
    
    // Setup buttons
    connect(ui->create, &QPushButton::clicked, this, &WenceslasII::createRecord);
    connect(ui->clear, &QPushButton::clicked, this, &WenceslasII::clearRecord);
    connect(ui->remove, &QPushButton::clicked, this, &WenceslasII::removeRecord);
    connect(ui->correct, &QPushButton::clicked, this, &WenceslasII::correctRecord);
    connect(ui->start_timer, &QPushButton::clicked, this, &WenceslasII::startTimer);
    connect(ui->clear_timer, &QPushButton::clicked, this, &WenceslasII::clearTimer);
    connect(ui->restore_timer, &QPushButton::clicked, this, &WenceslasII::restoreTimer);
    connect(ui->record_time, &QPushButton::clicked, this, &WenceslasII::recordTime);
    connect(ui->remove_time, &QPushButton::clicked, this, &WenceslasII::removeTime);
    connect(ui->reg_original_order, &QPushButton::clicked, this, &WenceslasII::regOriginalOrder);
    connect(ui->eval, &QPushButton::clicked, this, &WenceslasII::evaluate);
    connect(ui->time_eval, &QPushButton::clicked, this, &WenceslasII::evaluate);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &WenceslasII::tabChanged);
    tabChanged(ui->tabWidget->currentIndex()); // The initial tab emits no currentChanged
    //connect(ui->reg_clear_filters, &QPushButton::clicked, this, &WenceslasII::clearRegFilters);
    connect(ui->time_original_order, &QPushButton::clicked, this, &WenceslasII::timeOriginalOrder);
    //connect(ui->time_clear_filters, &QPushButton::clicked, this, &WenceslasII::clearTimeFilters);
    connect(ui->eval_original_order, &QPushButton::clicked, this, &WenceslasII::evalOriginalOrder);
    //connect(ui->eval_clear_filters, &QPushButton::clicked, this, &WenceslasII::clearEvalFilters);
    connect(ui->gender, QOverload<bool>::of(&QPushButton::toggled), this, &WenceslasII::genderToggled);
    
    // Setup signals
    connect(&timer, &QTimer::timeout, this, &WenceslasII::updateClock);
    
    // Setup automatic evaluation
    evalTimer.setInterval(5000);
    connect(&evalTimer, &QTimer::timeout, this, &WenceslasII::evaluate);
    connect(ui->auto_eval, &QCheckBox::toggled, this, &WenceslasII::autoEvalToggled);
    // Keep the checkbox copies in both tabs in sync (setChecked emits nothing if unchanged)
    connect(ui->auto_eval, &QCheckBox::toggled, ui->time_auto_eval, &QCheckBox::setChecked);
    connect(ui->time_auto_eval, &QCheckBox::toggled, ui->auto_eval, &QCheckBox::setChecked);
    
    loadSettings();
    loadNames();
    
    // Sort the categories first
    std::sort(cats.begin(), cats.end());
        
    MyCategories::ConstIterator it;
    QVariant val;
    
    ui->evalCategoryCombo->addItem("Všechny kategorie", QVariant());
    for (it=cats.begin(); it != cats.end(); ++it) {
        val.setValue(*it);
        ui->evalCategoryCombo->addItem(it->toString(), val);
    }
    connect(ui->evalCategoryCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &WenceslasII::evalCategoryIndexChanged);
    
    // EvalTable requires no SQL database - it is fully in memory
    setupEvalTable();
    
}

WenceslasII::~WenceslasII()
{
    delete ui;
    delete printPreview;
}

uint WenceslasII::parseTime(const QString& str, bool *ok)
{
    QStringList str_split = str.split(":");
    if (str_split.size() != 2) {
        *ok = false;
        return 0;
    }
    uint ms = str_split[0].toUInt(ok) * 60000;
    if (!*ok) return 0;
    ms += round(str_split[1].toFloat(ok) * 1000);
    if (!*ok) return 0;
    
    return ms;
}

QString WenceslasII::formatTime(uint ms)
{
    uint mins = ms / 60000;
    float sec = (float)(ms - mins*60000) / 1000;
    QString formatted = QString::asprintf("%d:%05.2f", mins, sec);
    //formatted.sprintf("%d:%05.2f", mins, sec);
    return formatted;
}

bool WenceslasII::loadSettings()
{
    QVariant val;
    QSettings set("config.ini", QSettings::IniFormat);
    set.setIniCodec("UTF-8");
    
    // Load operator name
    set.beginGroup("settings");
    op_name = set.value("operator").toString();
    qDebug() << "Operator name: " << op_name;
    bool ret = false;
    tol = parseTime(set.value("tol").toString(), &ret);
    if (!ret){
        qDebug() << "Cannot parse tolerance of time differences";
    }
    qDebug() << "Acceptable difference between time records: " << tol;
    set.endGroup();
    
    // Load categories
    set.beginGroup("category");
    QStringList cat = set.childGroups();
    QStringList::const_iterator it2 = cat.cbegin();
    for (; it2 != cat.cend(); ++it2){
        set.beginGroup(*it2);
        // Get group id
        bool ok;
        uint id = it2->toUInt(&ok);
        if (!ok) { 
            qDebug() << "Invalid group id!";
            break;
        }
        // Get group name
        QString name = set.value("name").toString();
        if (name == QString()) {
            qDebug() << "Group name not specified!";
            break;
        }
        // Get group age
        QVariant age = set.value("age");
        QStringList age_split = age.toString().split("-");
        if (age_split.size() != 2) {
            qDebug() << "Invalid age specified!";
            break;
        }
        bool ook;
        uint from = age_split[0].toUInt(&ok);
        uint to = age_split[1].toUInt(&ook);
        if (!ok || !ook){
            qDebug() << "Invalid age specified!";
            break;
        }
        
        uint offset = parseTime(set.value("offset", "0:0.0").toString(), &ok);
        if (!ok) {
            qDebug() << "Invalid format of offset!";
            break;
        }
        
        bool woman = set.value("woman").toUInt(&ok); 
        if (!ok) {
            qDebug() << "Invalid gender specified!";
            break;
        }
        
        qDebug() << "New category: " << id << ", " << name << ", " << from
                 << ", " << to << ", " << offset << ", " << woman;
        MyCategory ncat(id, name, from, to, offset, woman);
        cats.addCategory(ncat);
        set.endGroup();
    }
    set.endGroup();
    
    return true;
}

void WenceslasII::loadNames()
{
    QFile file(":/OpenData_-_seznam_jmen_k_2026-06-30.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the list of names!";
        return;
    }
    
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream.readLine(); // Skip header
    
    // A name may be listed several times with different genders
    while (!stream.atEnd()) {
        QStringList cols = stream.readLine().trimmed().split(',');
        if (cols.size() != 2) continue;
        
        int flag;
        if (cols[0] == "MUZ") flag = NameMan;
        else if (cols[0] == "ZENA") flag = NameWoman;
        else flag = NameNeutral;
        
        nameGenders[cols[1].toUpper()] |= flag;
    }
    qDebug() << "Loaded" << nameGenders.size() << "first names";
}

static bool askSaveAnyway(QWidget *parent, const QString &title, const QString &text)
// Ask whether to save a record despite a warning. Returns true if the user wants to save it.
{
    QMessageBox box(QMessageBox::Question, title, text, QMessageBox::NoButton, parent);
    QPushButton *save = box.addButton(QObject::tr("Přesto uložit"), QMessageBox::AcceptRole);
    QPushButton *change = box.addButton(QObject::tr("Změnit"), QMessageBox::RejectRole);
    box.setDefaultButton(change);
    box.exec();
    return box.clickedButton() == save;
}

bool WenceslasII::checkRecord(int key)
// Check the data in the registration forms. Returns false if the user wants to change them.
// key is the key of the record being corrected, or -1 for a new record.
{
    // Check whether the ID is already used by another record
    QSqlQuery query(QSqlDatabase::database("primary"));
    query.prepare("SELECT COUNT(*) FROM runners WHERE id = ? AND key != ?");
    query.addBindValue(ui->id->value());
    query.addBindValue(key);
    if (!query.exec() || !query.next()) {
        qDebug() << "Unable to check the ID!";
        qDebug() << query.lastError();
    } else if (query.value(0).toInt() > 0) {
        if (!askSaveAnyway(this, tr("Duplicitní ID"),
                           tr("ID %1 již v databázi existuje.").arg(ui->id->value()))) {
            ui->id->setFocus();
            ui->id->selectAll();
            return false;
        }
    }
    
    // Check the gender against the list of names, try the first of multiple names if not found
    QString name = ui->name->text().trimmed().toUpper();
    int gender = nameGenders.value(name, 0);
    if (gender == 0) {
        gender = nameGenders.value(name.section(' ', 0, 0), 0);
    }
    
    bool woman = ui->gender->isChecked();
    QString text;
    if (woman && gender == NameMan) {
        text = tr("Jméno %1 je mužské, ale je zvoleno pohlaví žena.");
    } else if (!woman && gender == NameWoman) {
        text = tr("Jméno %1 je ženské, ale je zvoleno pohlaví muž.");
    }
    if (!text.isEmpty()) {
        if (!askSaveAnyway(this, tr("Nesoulad pohlaví"), text.arg(ui->name->text().trimmed()))) {
            ui->gender->setFocus();
            return false;
        }
    }
    
    return true;
}

void WenceslasII::enableButtons()
{
    // Registration tab
    ui->create->setEnabled(true);
    ui->clear->setEnabled(true);
    ui->correct->setEnabled(true);
    ui->remove->setEnabled(true);
    ui->reg_original_order->setEnabled(true);
    
    // Time tab
    ui->time_eval->setEnabled(true);
    ui->time_auto_eval->setEnabled(true);
    ui->restore_timer->setEnabled(true);
    ui->record_time->setEnabled(true);
    ui->remove_time->setEnabled(true);
    ui->time_original_order->setEnabled(true);
    
    // Eval table
    ui->eval->setEnabled(true);
    ui->auto_eval->setEnabled(true);
    ui->eval_original_order->setEnabled(true);

    // Enable all actions
    ui->actionImport->setEnabled(true);
    ui->actionExportCSV->setEnabled(true);
    ui->actionExportCSV1->setEnabled(true);
    ui->actionExportCSV2->setEnabled(true);
    ui->actionExportCSV3->setEnabled(true);
    ui->actionExportHTML->setEnabled(true);
    ui->actionExportHTML1->setEnabled(true);
    ui->actionExportHTML2->setEnabled(true);
    ui->actionExportHTML3->setEnabled(true);
    if (uploadAction) uploadAction->setEnabled(true);
}

void WenceslasII::setupRegTable()
{
    QSqlDatabase db = QSqlDatabase::database("primary");
    
    // ====
    // Create table model 
    if (regModel != NULL) delete regModel;
    regModel = new MyTableModel(this, cats, db);
    regModel->setTable("runners");
    regModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    
    
    // Select data from database
    bool ret = regModel->select();
    if (!ret) {
        QMessageBox::warning(this, tr("Chyba"), tr("Nepodařilo se načíst databázi, "
        "zřejmně má špatný formát."));
        return;
    }
    
    // FIX: fix bug with loading large databases
    while (regModel->canFetchMore()){
        regModel->fetchMore();
    }
    
    // Any change of the runners makes the evaluation outdated
    connect(regModel, &QAbstractItemModel::dataChanged, this, &WenceslasII::markEvalOutdated);
    connect(regModel, &QAbstractItemModel::rowsInserted, this, &WenceslasII::markEvalOutdated);
    connect(regModel, &QAbstractItemModel::rowsRemoved, this, &WenceslasII::markEvalOutdated);
    connect(regModel, &QAbstractItemModel::modelReset, this, &WenceslasII::markEvalOutdated);
    markEvalOutdated();
    
    // ====
    // Create sorting proxy
    regSortProxy = new MySortFilterProxyModel(regModel);
    regSortProxy->setSourceModel(regModel);
    
    // Connect signals
    connect(regSortProxy, &MyTableModel::rowsInserted, this, &WenceslasII::regDimensionChanged);
    connect(regSortProxy, &MyTableModel::rowsRemoved, this, &WenceslasII::regDimensionChanged);
    
    //FilterTableHeader *header = new FilterTableHeader(ui->regTable);
    //ui->regTable->setHorizontalHeader(header);
    //header->setVisible(true);
    //header->generateFilters(9, 1);
    
    // Connect filter change signal to the proxy
    //connect(header, &FilterTableHeader::filterChanged, regSortProxy, &MySortFilterProxyModel::filterChanged);
    //connect(this, &WenceslasII::setRegFilter, header, &FilterTableHeader::setFilter);
    //connect(this, &WenceslasII::clearRegFilters, header, &FilterTableHeader::clearFilters);
    
    // =====
    // Setup table view
    ui->regTable->setModel(regSortProxy);
    ui->regTable->setSortingEnabled(true);
    ui->regTable->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    ui->regTable->hideColumn(0);
    ui->regTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->regTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->regTable->setItemDelegateForColumn(5, new MyGenderItemDelegate);
    ui->regTable->setColumnWidth(1, 40);
    ui->regTable->setColumnWidth(2, 80);
    ui->regTable->setColumnWidth(3, 80);
    ui->regTable->setColumnWidth(4, 120);
    ui->regTable->setColumnWidth(5, 80);
    ui->regTable->setColumnWidth(6, 40);
    ui->regTable->setColumnWidth(7, 80);
    ui->regTable->setColumnWidth(8, 200);
    
    // ====
    // Connect forms to the model
    mapper = new QDataWidgetMapper(regModel);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setItemDelegate(new NoEscapeDelegate(mapper));
    mapper->setModel(regSortProxy);
    mapper->addMapping(ui->name, 2);
    mapper->addMapping(ui->surname, 3);
    mapper->addMapping(ui->address, 4);
    mapper->addMapping(ui->id, 1);
    mapper->addMapping(ui->age, 6);
    mapper->addMapping(ui->gender, 5, "checked");
    
    connect(ui->regTable->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            mapper,
            &QDataWidgetMapper::setCurrentModelIndex);
    
    // Update the row counter !! regSortProxy hides 'deleted' rows!!
    ui->reg_count->setText(QString::number(regSortProxy->rowCount()));
}

void WenceslasII::setupTimeTable()
{
    QSqlDatabase db = QSqlDatabase::database("primary");
    
    // ====
    // Create table model 
    if (timeModel != NULL) delete timeModel;
    timeModel = new QSqlTableModel(this, db);
    timeModel->setTable("times");
    bool ret = timeModel->select();
    if (!ret) {
        QMessageBox::warning(this, tr("Chyba"), tr("Nepodařilo se načíst databázi, "
        "zřejmně má špatný formát."));
        return;
    }
    
    // Fix bug with sorting 
    while (timeModel->canFetchMore()){
        timeModel->fetchMore();
    }
    timeModel->setHeaderData(1, Qt::Horizontal, "ID");
    
    // Any change of the times makes the evaluation outdated
    connect(timeModel, &QAbstractItemModel::dataChanged, this, &WenceslasII::markEvalOutdated);
    connect(timeModel, &QAbstractItemModel::rowsInserted, this, &WenceslasII::markEvalOutdated);
    connect(timeModel, &QAbstractItemModel::rowsRemoved, this, &WenceslasII::markEvalOutdated);
    connect(timeModel, &QAbstractItemModel::modelReset, this, &WenceslasII::markEvalOutdated);
    markEvalOutdated();
    timeModel->setHeaderData(2, Qt::Horizontal, "Čas");
    timeModel->setHeaderData(3, Qt::Horizontal, "Operátor");
    
    joinTimeEvalProxy = new JoinProxyModel(timeModel);
    joinTimeEvalProxy->setPrimaryModel(timeModel, 1);
    joinTimeEvalProxy->setSecondaryModel(evalModel, 0);
    
    // ====
    // Create sorting proxy
    //timeSortProxy = new MySortFilterProxyModel(timeModel);
    //timeSortProxy->setSourceModel(timeModel);
    timeSortProxy = new MySortFilterProxyModel(joinTimeEvalProxy);
    timeSortProxy->setSourceModel(joinTimeEvalProxy);
    //timeSortProxy->addFilter(3, op_name); // FIXME
    timeSortProxy->setFilterFixedString(op_name);
    timeSortProxy->setFilterKeyColumn(3);
    
    // Connect signals
    connect(timeSortProxy, &MyTableModel::rowsInserted, this, &WenceslasII::timeDimensionChanged);
    connect(timeSortProxy, &MyTableModel::rowsRemoved, this, &WenceslasII::timeDimensionChanged);
    
    //FilterTableHeader *header = new FilterTableHeader(ui->timeTable);
    //ui->timeTable->setHorizontalHeader(header);
    //header->setVisible(true);
    //header->generateFilters(4, 1);
    
    // Connect filter change signal to the proxy
    //connect(header, &FilterTableHeader::filterChanged, timeSortProxy, &MySortFilterProxyModel::filterChanged);
    //connect(this, &WenceslasII::setTimeFilter, header, &FilterTableHeader::setFilter);
    //connect(this, &WenceslasII::clearTimeFilters, header, &FilterTableHeader::clearFilters);
    
    // ====
    // Setup table view
    ui->timeTable->setModel(timeSortProxy);
    ui->timeTable->setSortingEnabled(true);
    ui->timeTable->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
    ui->timeTable->hideColumn(0);
    SpinBoxDelegate *idDelegate = new SpinBoxDelegate(timeModel);
    ui->timeTable->setItemDelegateForColumn(1, idDelegate);
    MyTimeItemDelegate *timeDelegate = new MyTimeItemDelegate(timeModel);
    ui->timeTable->setItemDelegateForColumn(2, timeDelegate);
    NotEditableDelegate *opDelegate = new NotEditableDelegate(timeModel);
    ui->timeTable->setItemDelegateForColumn(3, opDelegate);
    ui->timeTable->setColumnWidth(1, 40);
    ui->timeTable->setColumnWidth(2, 80);
    ui->timeTable->setColumnWidth(3, 80);
    // Hide the joined evaluation columns duplicating the time record ("ID" and "Čas")
    int joinOffset = timeModel->columnCount();
    ui->timeTable->hideColumn(joinOffset + 0);
    ui->timeTable->hideColumn(joinOffset + 7);
    ui->timeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->timeTable->verticalHeader()->setVisible(false);
    
    connect(idDelegate, SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)), 
            this, SLOT(editing_finished(QWidget*,QAbstractItemDelegate::EndEditHint)));
    connect(timeDelegate, SIGNAL(closeEditor(QWidget*,QAbstractItemDelegate::EndEditHint)), 
            this, SLOT(editing_finished(QWidget*,QAbstractItemDelegate::EndEditHint)));
    

    // Update the row counter !! timeSortProxy hides 'deleted' rows!!
    ui->time_count->setText(QString::number(timeSortProxy->rowCount()));
}

void WenceslasII::setupEvalTable()
{
    // ====
    // Setup table model
    if (evalModel != NULL) delete evalModel;
    evalModel = new EvalTableModel(this, cats);
    // ====
    // Create sorting proxy
    evalSortProxy = new MySortFilterProxyModel(this);
    evalSortProxy->setSourceModel(evalModel);
    
    // ====
    // Setup table view
    ui->evalTable->setModel(evalSortProxy);
    ui->evalTable->setSortingEnabled(true);
    ui->evalTable->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
    MyTimeItemDelegate *timeDelegate = new MyTimeItemDelegate(evalModel);
    ui->evalTable->setItemDelegateForColumn(7, timeDelegate);
    ui->evalTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->evalTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->evalTable->setColumnWidth(0, 40);
    ui->evalTable->setColumnWidth(1, 80);
    ui->evalTable->setColumnWidth(2, 80);
    ui->evalTable->setColumnWidth(3, 120);
    ui->evalTable->setColumnWidth(4, 80);
    ui->evalTable->setColumnWidth(5, 40);
    ui->evalTable->setColumnWidth(6, 120);
    ui->evalTable->setColumnWidth(7, 70);
    ui->evalTable->setColumnWidth(8, 40);
    ui->evalTable->setColumnWidth(8, 40);
    
    // ====
    connect(ui->evalList, &QListWidget::itemDoubleClicked, this, &WenceslasII::conflictActivated);
}

void WenceslasII::timeTableEdit()
{
    if (timeModel == NULL || timeSortProxy == NULL){
        qDebug() << "time model or proxy is NULL!";
        return;
    }
    
    // Interactive mode active only it timer is running
    if (elapsed_timer.isValid()) {
        QModelIndex index, mapped;
        for(int row = timeModel->rowCount() - 1; row >= 0; row--){
            index = timeModel->index(row, 1);
            mapped = timeSortProxy->mapFromSource(joinTimeEvalProxy->mapFromSource(index));
            qDebug() << "Mapped index:" << index.data();
            
            if (index.data().isNull()){
                ui->timeTable->setFocus();
                ui->timeTable->setCurrentIndex(mapped);
                ui->timeTable->edit(mapped);
                break;
            }
        }
    }
}

bool WenceslasII::eventFilter(QObject* o, QEvent* e)
{
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *k = static_cast<QKeyEvent *>(e);
        switch (k->key()){
            case Qt::Key_Space:
                recordTime();
                break;
            //case Qt::Key_Delete:
            //    removeTime();
            //    break;
            default:
                return false;
            
        }
        return true;
    }
    
    return false;
}

QStringList WenceslasII::recToStringList(const EvalTableModel::Record &rec)
// Converts QSqlRecord from "results" table to list of strings
{
    QStringList list;
    int col;
    bool woman;
    uint ms;
    int catId;
    MyCategory category;
    
    for (col = 0; col < rec.count(); col++){
        switch (col) {
            case 4:
                woman = rec.value(col).toBool();
                if (woman)
                    list.append(tr("\"žena\""));
                else
                    list.append(tr("\"muž\""));
                break;
                
            case 6:
                catId = rec.value(col).toInt();
                category = cats.byId(catId);
                list.append(QString("\"%1\"").arg(category.toString()));
                break;
                    
            case 7:
                ms = rec.value(col).toInt();
                list.append(QString("\"%1\"").arg(formatTime(ms)));
                break;
                
            default:
                list.append(QString("\"%1\"").arg(rec.value(col).toString()));
        }
    }
    
    return list;
}

QString WenceslasII::recToHTML(const EvalTableModel::Record &rec)
// Converts QSqlRecord from "results" table to a HTML code
{
    QString name = rec.value(1).toString();
    QString surname = rec.value(2).toString();
    uint time = rec.value(7).toInt();
    QString stime = formatTime(time);
    int id = rec.value(0).toInt();
    
    return QString("<li>%1 %2 (%3) [%4]</li>").arg(name).arg(surname).arg(stime).arg(id);
}

void WenceslasII::extractRecs(QList<EvalTableModel::Record> &list, bool order, bool selection)
{
    if (selection) {
        // Get selection model and check if there is something selected
        QItemSelectionModel *selection_model = ui->evalTable->selectionModel();
        if (!selection_model->hasSelection()) return;
        
        // Get the selected row indices
        QModelIndexList indices = selection_model->selectedRows();
        
        QModelIndex mapped;
        int i;
        for (i = 0; i < indices.count(); i++) {
            mapped = evalSortProxy->mapToSource(indices.at(i));
            list.append(evalModel->record(mapped.row()));
        }
    } else {
        int row;
        for (row=0; row < evalModel->rowCount(); row++){
            list.append(evalModel->record(row));
        }
    }
    
    // Sort records by order
    if (order) {
        std::sort(list.begin(), list.end(), ByOrderAndCategory);
    } else {
        std::sort(list.begin(), list.end(), ByOrder);
    }
}

void WenceslasII::exportCSV(bool order, bool selection)
{
    qDebug() << "Export CSV";
    
    path = QFileDialog::getSaveFileName(this, tr("Vyberte název a cestu nového CSV souboru..."),
                           "",
                           tr("CSV soubor (*.csv)"));
    
    // No file choosen
    if( path.isEmpty() ) return;
        
    // Open output file
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString text = tr("Nepodařilo se otevřít soubor %1 pro zápis.").arg(path);
        QMessageBox::warning(this, tr("Chyba"), text);
        return;
    }
    QTextStream stream(&file);
    
    // Populate records by selected or all rows
    QList<EvalTableModel::Record> records;
    extractRecs(records, order, selection);
    
    // First write the header
    int col;
    EvalTableModel::Record first = records.at(0);
    for (col = 0; col < first.count() - 1; col++){
        stream << first.fieldName(col) << ",";
    }
    stream << first.fieldName(col) << Qt::endl;
    
    // Now write the content
    QList<EvalTableModel::Record>::const_iterator it;
    QStringList str;
    for (it = records.constBegin(); it != records.constEnd(); ++it){
        str = recToStringList(*it);
        for (col = 0; col < str.size() - 1; col++){
            stream << str.at(col) << ",";
        }
        stream << str.at(col) << Qt::endl;
    }
    
    stream.flush();
    file.close();
}

void WenceslasII::exportHTML(bool order, bool selection)
{
    
    qDebug() << "Export HTML";
    
    path = QFileDialog::getSaveFileName(this, tr("Vyberte název a cestu nového HTML souboru..."),
                           "",
                           tr("HTML soubor (*.html)"));
    
    // No file choosen
    if( path.isEmpty() ) return;
        
    // Open output file
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString text = tr("Nepodařilo se otevřít soubor %1 pro zápis.").arg(path);
        QMessageBox::warning(this, tr("Chyba"), text);
        return;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    // This works in QT6:
    //stream.setEncoding(QStringConverter::Utf8);

    // Populate records by selected or all rows
    QList<EvalTableModel::Record> records;
    extractRecs(records, order, selection);
    
    // Print results per category
    QList<EvalTableModel::Record>::const_iterator it;
    if (order) {
        int current_cid = records.constBegin()->value(6).toInt();
        MyCategory current_cat = cats.byId(current_cid);
        MyCategory tmp;
        
        stream << "<html>" << Qt::endl;
        stream << "<h3>" << current_cat.name << "</h3>" << Qt::endl;
        stream << "<ol>" << Qt::endl;
        
        for (it = records.constBegin(); it != records.constEnd(); ++it){
            tmp = cats.byId(it->value(6).toInt());
            
            if (current_cat == tmp) {
                stream << recToHTML(*it) << Qt::endl;
            } else {
                current_cat = tmp;
                stream << "</ol>";
                stream << "<h3>" << current_cat.name << "</h3>" << Qt::endl;
                stream << "<ol>" << Qt::endl;
                stream << recToHTML(*it) << Qt::endl;
            }
        }
        stream << "</ol>" << Qt::endl << "</html>" << Qt::endl;
        
    // Print results sorted by order
    } else {
        stream << "<html>" << Qt::endl << "<ol>" << Qt::endl;
        for (it = records.constBegin(); it != records.constEnd(); ++it){
            stream << recToHTML(*it) << Qt::endl;
        }
        stream << "</ol>" << Qt::endl << "</html>" << Qt::endl;
    }
    
    // Now write the content
    stream.flush();
    file.close();
}

void WenceslasII::print(bool order, bool selection)
{
    // Populate records by selected or all rows
    QList<EvalTableModel::Record> records;
    extractRecs(records, order, selection);
    
    if (records.length() > 0) {
        // Convert records to list of maps
        QList<QMap<QString, QString>> values;
        for (EvalTableModel::Record rec : records) {
            QMap<QString, QString> map;
            QString namesurname = rec.value(1).toString() % " " % rec.value(2).toString();
            map.insert("namesurname", namesurname);
            map.insert("name", rec.value(1).toString());
            map.insert("surname", rec.value(2).toString());
            map.insert("category", cats.byId(rec.value(6).toInt()).toString());
            map.insert("time", formatTime(rec.value(7).toUInt()));
            values.append(map);
        }
        
        delete printPreview;
        printPreview = new PrintingWindow(values);
        printPreview->show();
    }
}


QModelIndex WenceslasII::findItem(QAbstractTableModel* model, int col, QVariant val)
// Search model for row whose column col has a specified value. Return the corresponding model index.
{
    int row;
    QModelIndex index;
    for (row = 0; row < model->rowCount(); row++) {
        index = model->index(row, col);
        if (index.data(Qt::DisplayRole) == val) {
            return index;
        };
    }
    
    return QModelIndex();
}


void WenceslasII::openFile()
{
    qDebug() << "Open file";
    
    path =
        QFileDialog::getOpenFileName(this, tr("Vyberte SQLite databázi k otevření..."), 
                                     "", tr("SQLite databáze (*.sqlite)"));

    // No file choosen
    if( path.isEmpty() ) return;
    
    // Open the database file & create default database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "primary");
    db.setDatabaseName(path);
    
    if( db.open() != true){
        QString text = tr("Nepodařilo se otevřít databázi %1.").arg(path);
        QMessageBox::warning(this, tr("Chyba"), text);
        return;
    } else {
        // Older databases may lack the timer table
        if (!createTimerTable()) {
            QString text = tr("Nepodařilo se vytvořit tabulku stopek v databázi %1").arg(path);
            QMessageBox::warning(this, tr("Chyba"), text);
        }
        
        // Setup table for registration
        setupRegTable();
        
        // Setup table for time
        setupTimeTable();
        
        // Show status bar message
        QString text = tr("Otevřen soubor %1").arg(path);
        ui->statusbar->showMessage(text);
        
        // Show file name in title
        text = tr("Wenceslas II - %1").arg(path);
        this->setWindowTitle(text);
        
        // Enable all the needed buttons
        enableButtons();
    }
}

void WenceslasII::newFile()
{
    qDebug() << "New file";
    
    path = QFileDialog::getSaveFileName(this, tr("Vyberte název a cestu nové SQLite databáze..."),
                           "",
                           tr("SQLite databáze (*.sqlite)"));
    
    // No file choosen
    if( path.isEmpty() ) return;
    
    // Open the database file & create a default database
    // FIXME: Close existing db ??
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "primary");
    db.setDatabaseName(path);
    
    if( db.open() != true){
        QString text = tr("Nepodařilo se otevřít databázi %1.").arg(path);
        QMessageBox::warning(this, tr("Chyba"), text);
        return;
        
    // Create the required tables
    } else {
        bool ret = true;
        QSqlQuery query(db);
        query.prepare("CREATE TABLE 'results' ("
            "'id' INTEGER UNIQUE,"
            "'first_name' TEXT,"
            "'surname' TEXT,"
            "'address' TEXT,"
            "'woman' INTEGER,"
            "'age'	INTEGER,"
            "'category'	INTEGER,"
            "'time' INTEGER,"
            "'order' INTEGER,"
            "'order_category' INTEGER,"
            "PRIMARY KEY('id'))");
        ret = ret && query.exec();
        
        query.prepare("CREATE TABLE 'runners' ("
            "'key' INTEGER UNIQUE,"
            "'id' INTEGER,"
            "'first_name' TEXT,"
            "'surname' TEXT,"
            "'address' TEXT,"
            "'woman' INTEGER,"
            "'age' INTEGER,"
            "'operator' TEXT,"
            "PRIMARY KEY('key' AUTOINCREMENT))");
        ret = ret && query.exec();
        
        query.prepare("CREATE TABLE 'times' ("
            "'key' INTEGER UNIQUE,"
            "'id' INTEGER,"
            "'time' INTEGER,"
            "'operator' TEXT,"
            "PRIMARY KEY('key' AUTOINCREMENT))");
        ret = ret && query.exec();
        
        ret = ret && createTimerTable();
        
        if (ret == false) {
            qDebug() << "Unable to initialize the database!";
            qDebug() << query.lastError();
            
            QString text = tr("Nepodařilo se inicializovat databázi %1").arg(path);
            QMessageBox::warning(this, tr("Chyba"), text);
            return;
        }
        
        // Setup table for registration
        setupRegTable();
        
        // Setup table for time
        setupTimeTable();

        // Show status bar message
        QString text = tr("Otevřen soubor %1").arg(path);
        ui->statusbar->showMessage(text);
        
        // Show file name in title
        text = tr("Wenceslas II - %1").arg(path);
        this->setWindowTitle(text);
        
        // Enable all the needed buttons
        enableButtons();
    }
}

void WenceslasII::importFile()
{
    qDebug() << "Import file";
    
    if (regModel == NULL || timeModel == NULL) {
        qDebug() << "Registration or time model is NULL!";
        return;
    }
    
    path =
        QFileDialog::getOpenFileName(this, tr("Vyberte SQLite databázi k importu..."), 
                                     "", tr("SQLite databáze (*.sqlite)"));

    // No file choosen
    if( path.isEmpty() ) return;
    
     // Open the database file
    QSqlDatabase secondary = QSqlDatabase::addDatabase("QSQLITE", "secondary");
    secondary.setDatabaseName(path);
    
    if( secondary.open() != true){
        QString text = tr("Nepodařilo se otevřít databázi %1").arg(path);
        QMessageBox::warning(this, tr("Chyba"), text);
        return;
    } else {
        // FIXME: do not create duplicates
        
        // Import records from table "runners"
        bool ret;
        QSqlQuery query(secondary);
        query.prepare("SELECT id, first_name, surname, address, woman, age, operator FROM runners");
        ret = query.exec();
        
        if (ret == false) {
            qDebug() << "SELECT failed on table 'runners'";
            qDebug() << query.lastError();
            
            QString text = tr("SELECT příkaz selhal. Importovaná databáze je zřejmně poškozena.");
            QMessageBox::warning(this, tr("Chyba"), text);
            return;
        }
        
        
        while (query.next()) {
            QSqlRecord rec = regModel->record();
            rec.setGenerated("key", false);     // Generate primary key automatically
            rec.setValue("id", query.value(0));
            rec.setValue("first_name", query.value(1));
            rec.setValue("surname", query.value(2));
            rec.setValue("address", query.value(3));
            rec.setValue("woman", query.value(4));
            rec.setValue("age", query.value(5));
            rec.setValue("operator", query.value(6));
            
            ret = regModel->insertRecord(-1, rec);
            if (!ret) {
                qDebug() << "Unable to insert record:";
                qDebug() << regModel->lastError();
            }
        }
        
        // Import records from table "runners"
        query.prepare("SELECT id, time, operator FROM times");
        ret = query.exec();   // FIXME: check whether this fails
        if (ret == false) {
            qDebug() << "SELECT failed on table 'runners'";
            qDebug() << query.lastError();
            
            QString text = tr("SELECT příkaz selhal. Importovaná databáze je zřejmně poškozena.");
            QMessageBox::warning(this, tr("Chyba"), text);
            return;
        }
        
        while (query.next()) {
            QSqlRecord rec = timeModel->record();
            rec.setGenerated("key", false);
            rec.setValue("id", query.value(0));
            rec.setValue("time", query.value(1));
            rec.setValue("operator", query.value(2));
            
            ret = timeModel->insertRecord(-1, rec);
            if (!ret) {
                qDebug() << "Unable to insert record:";
                qDebug() << regModel->lastError();
            }
        }
        
        // Cleanup
        secondary.close();
    }
}

void WenceslasII::actionExportCSV()
{
    // Export all records in order
    exportCSV(false, false);
}

void WenceslasII::actionExportCSV1()
{
    // Export all records by category
    exportCSV(true, false);
}

void WenceslasII::actionExportCSV2()
{
    // Export selected records by order
    exportCSV(false, true);
}

void WenceslasII::actionExportCSV3()
{
    // Export selected records by category
    exportCSV(true, true);
}

void WenceslasII::actionExportHTML()
{
    // Export all records in order
    exportHTML(false, false);
}

void WenceslasII::actionExportHTML1()
{
    // Export all records by category
    exportHTML(true, false);
}

void WenceslasII::actionExportHTML2()
{
    // Export selected records by order
    exportHTML(false, true);
}

void WenceslasII::actionExportHTML3()
{
    // Export selected records by category
    exportHTML(true, true);
}

void WenceslasII::uploadResults()
{
    if (evalModel == NULL || evalModel->rowCount() == 0) {
        QMessageBox::warning(this, tr("Žádná data"),
            tr("Vyhodnocení je prázdné — nejprve spusťte vyhodnocení všech závodníků."));
        return;
    }
    
    QList<EvalTableModel::Record> records;
    int row;
    for (row = 0; row < evalModel->rowCount(); row++) {
        records.append(evalModel->record(row));
    }
    std::sort(records.begin(), records.end(), ByOrder);
    
    int missing = 0;
    QList<ResultsUpload::Row> rows;
    rows.reserve(records.size());
    for (const EvalTableModel::Record &rec : records) {
        const MyCategory category = cats.byId(rec.value(6).toInt());
        if (category.toString().isEmpty() || category.toString() == QStringLiteral("None")) {
            missing++;
        }
        rows.append({
            rec.value(0).toInt(),
            rec.value(1).toString() + QLatin1Char(' ') + rec.value(2).toString(),
            rec.value(7).toUInt(),
            category.toString(),
        });
    }
    
    UploadResultsDialog dlg(ResultsUpload::buildCsv(rows), rows.size(), missing, this);
    dlg.exec();
}

void WenceslasII::actionPrint()
{
    print(true, false);
}

void WenceslasII::actionPrintSelection()
{
    print(true, true);
}


void WenceslasII::createRecord()
{
    if (regModel == NULL) {
        qDebug() << "Registration model is null!";
        return;
    }
    
    if (!checkRecord(-1)) return;
    
    QSqlRecord rec = regModel->record();
    rec.setGenerated("key", false);
    rec.setValue("id", ui->id->value());
    rec.setValue("first_name", ui->name->text());
    rec.setValue("surname", ui->surname->text());
    rec.setValue("address", ui->address->text());
    rec.setValue("woman", ui->gender->isChecked());
    rec.setValue("age", ui->age->value());
    rec.setValue("operator", op_name);
    
    // Create new record
    int row = regModel->rowCount();
    bool ret = regModel->insertRecord(row, rec);
    if (ret == false) {
        qDebug() << "Unable to insert record:";
        qDebug() << regModel->lastError();
        
        QString text = tr("Záznam se nepodařilo vytvořit. Databáze může být poškozena.");
        QMessageBox::warning(this, tr("Chyba"), text);
    }
    
    // Select the new record
    QModelIndex index = regModel->index(row, 1);
    QModelIndex mapped = regSortProxy->mapFromSource(index);
    ui->regTable->selectRow(mapped.row());
    ui->regTable->scrollTo(mapped, QAbstractItemView::EnsureVisible);
}


void WenceslasII::clearRecord()
{
    // Unselect the current row so that correct has no record to overwrite
    ui->regTable->setCurrentIndex(QModelIndex());
    ui->regTable->clearSelection();
    
    // Clear the data in forms
    ui->name->clear();
    ui->surname->clear();
    ui->address->clear();
    ui->id->setValue(ui->id->minimum());
    ui->age->setValue(ui->age->minimum());
    ui->gender->setChecked(false);
    ui->gender->setFocus();
}


void WenceslasII::removeRecord()
{
    if (regModel == NULL || regSortProxy == NULL) {
        qDebug() << "Registration model or sort proxy is NULL!";
        return;
    }

    // Get selection model and check if there is something selected
    QItemSelectionModel *selection_model = ui->regTable->selectionModel();
    if (!selection_model->hasSelection()) return;
    
    // Get the selected row indices
    QModelIndexList indices = selection_model->selectedRows();
    
    // Ask user whether he really wants to delete the record
    QMessageBox::StandardButton reply;
    reply =  QMessageBox::question(this, tr("Smazat záznamy běžců"), 
                                    tr("Opravdu chcete nenávratně smazat %1 vybraných záznamů?").arg(indices.count()),
                                    QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Clear current selection
        ui->regTable->setCurrentIndex(QModelIndex());
        
        // Get all rows to be removed
        QList<int> rows;
        QModelIndex mapped;
        int i;
        for (i = 0; i < indices.count(); i++) {
            mapped = regSortProxy->mapToSource(indices.at(i));
            rows.append(mapped.row());
        }
        
        // Sort in descending order to avoid issue with changing row numbers
        std::sort(rows.begin(), rows.end(), descInt);
        
        // Remove the rows
        for (i=0; i < rows.count(); i++) {
            regModel->removeRow(rows[i]);
            qDebug() << rows[i];
        }
        
        // Clear data from forms
        mapper->revert();
    }
}

void WenceslasII::correctRecord()
{
    if (regModel == NULL || mapper == NULL) {
        qDebug() << "Registration model or mapper is null!";
        return;
    }
    
    // Correct only a row selected by the user
    if (!ui->regTable->selectionModel()->hasSelection()) return;
    
    int key = regSortProxy->index(mapper->currentIndex(), 0).data().toInt();
    if (!checkRecord(key)) return;
    
    bool ret = mapper->submit();
    if (ret == false) {
        qDebug() << "Data mapper submit failed!";
        
        QString text = tr("Záznam se nepodařilo opravit. Databáze může být poškozena.");
        QMessageBox::warning(this, tr("Chyba"), text);
    }

    
    // Needed to render the header correctly
    //FilterTableHeader *header = (FilterTableHeader *)ui->regTable->horizontalHeader();
    //header->adjustPositions();
}

void WenceslasII::regOriginalOrder()
{
    ui->regTable->sortByColumn(0, Qt::SortOrder::AscendingOrder);
}

void WenceslasII::timeOriginalOrder()
{
    ui->timeTable->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
}

void WenceslasII::evalOriginalOrder()
{
    ui->evalTable->sortByColumn(-1, Qt::SortOrder::AscendingOrder);
}

void WenceslasII::startTimer()
{
    if (timer.isActive()) {
        QMessageBox::StandardButton reply;
        reply =  QMessageBox::question(this, "Zastavit stopky", 
                                       "Opravdu chcete zastavit stopky?",
                                       QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // Enable clear button and change label
            ui->clear_timer->setEnabled(true);
            ui->start_timer->setText("Start");
            
            // Stop timer
            last_ms = last_ms + elapsed_timer.elapsed();
            elapsed_timer.invalidate();
            timer.stop();
        }
    } else {
        // Disable clear button and change label
        ui->clear_timer->setEnabled(false);
        ui->start_timer->setText("Stop");
        
        // Start timer
        elapsed_timer.start();
        timer.start(10);
        saveStartTime();
    }
}

void WenceslasII::clearTimer()
{
    last_ms = 0;
    updateClock();
}

bool WenceslasII::createTimerTable()
{
    // Single-row table with the wall-clock time (ms since epoch) at which the stopwatch reads zero
    QSqlQuery query(QSqlDatabase::database("primary"));
    bool ret = query.exec("CREATE TABLE IF NOT EXISTS 'timer' ("
        "'id' INTEGER PRIMARY KEY CHECK (id = 0),"
        "'start' INTEGER)");
    if (!ret) {
        qDebug() << "Unable to create the timer table!";
        qDebug() << query.lastError();
    }
    return ret;
}

void WenceslasII::saveStartTime()
{
    QSqlDatabase db = QSqlDatabase::database("primary", false);
    if (!db.isOpen()) return;
    
    // Subtract the time already on the clock, in case the timer is resumed after a stop
    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO 'timer' ('id', 'start') VALUES (0, ?)");
    query.addBindValue(QDateTime::currentMSecsSinceEpoch() - last_ms);
    if (!query.exec()) {
        qDebug() << "Unable to save timer start!";
        qDebug() << query.lastError();
    }
}

void WenceslasII::restoreTimer()
{
    QSqlQuery query(QSqlDatabase::database("primary"));
    if (!query.exec("SELECT start FROM 'timer' WHERE id = 0") || !query.next()) {
        QString text = tr("V databázi není uložen čas startu stopek.");
        QMessageBox::warning(this, tr("Chyba"), text);
        return;
    }
    
    last_ms = QDateTime::currentMSecsSinceEpoch() - query.value(0).toLongLong();
    
    // Disable clear button and change label
    ui->clear_timer->setEnabled(false);
    ui->start_timer->setText("Stop");
    
    // Start timer
    elapsed_timer.start();
    timer.start(10);
}

void WenceslasII::updateClock()
{
    uint ms;
    if (elapsed_timer.isValid()) {
        ms = last_ms + elapsed_timer.elapsed();
    } else {
        ms = last_ms;
    }
        
    ui->clock->setText(formatTime(ms));
}

void WenceslasII::recordTime()
{
    if (timeModel == NULL){
        qDebug() << "Time model is NULL!";
        return;
    }
    
    QSqlRecord rec = timeModel->record();
    uint ms;
    rec.setGenerated("key", false);
    if (elapsed_timer.isValid()){
        ms = last_ms + elapsed_timer.elapsed();
    } else {
        ms = last_ms;
    }
    rec.setValue("time", ms);
    rec.setValue("operator", op_name);
    
    qDebug() << rec;
    
    // Create new record
    int row = timeModel->rowCount();
    bool ret = timeModel->insertRecord(row, rec);
    if (!ret) {
        qDebug() << "Unable to insert record at row " << row;
        qDebug() << timeModel->lastError();
        
        QString text = tr("Nepodařilo se vložit záznam. Databáze může být poškozena.");
        QMessageBox::warning(this, tr("Chyba"), text);
    }
    
    // Scroll to the new record
    QModelIndex index = timeModel->index(row, 1);
    QModelIndex mapped = timeSortProxy->mapFromSource(joinTimeEvalProxy->mapFromSource(index));
    //ui->regTable->selectRow(mapped.row());
    ui->timeTable->scrollTo(mapped);
    
    // Choose next item for editing if any
    timeTableEdit();
}

void WenceslasII::removeTime()
{
    if (timeModel == NULL || timeSortProxy == NULL) {
        qDebug() << "Time model or proxy is NULL!";
        return;
    }
    
    // Get selection model and check if there is something selected
    QItemSelectionModel *selection_model = ui->timeTable->selectionModel();
    if (!selection_model->hasSelection()) return;
    
    // Get the selected row indices
    QModelIndexList indices = selection_model->selectedRows();
    
    // Ask user whether he really wants to delete the record
    QMessageBox::StandardButton reply;
    reply =  QMessageBox::question(this, tr("Smazat záznamy času"), 
                                    tr("Opravdu chcete nenávratně smazat %1 vybraných záznamů?").arg(indices.count()),
                                    QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Get all rows to be removed
        QList<int> rows;
        QModelIndex mapped;
        int i;
        for (i = 0; i < indices.count(); i++) {
            mapped = timeSortProxy->mapToSource(indices.at(i));
            rows.append(mapped.row());
        }
        
        // Sort in descending order to avoid issue with changing row numbers
        std::sort(rows.begin(), rows.end(), descInt);
        
        // Remove the rows
        for (i=0; i < rows.count(); i++) {
            timeModel->removeRow(rows[i]);
            qDebug() << rows[i];
        }
        
        // Choose next item for editing
        timeTableEdit();
    }
    // else: do nothing
}


void WenceslasII::editing_finished(QWidget* editor, QAbstractItemDelegate::EndEditHint hint)
{
    // Choose next item for editing
    timeTableEdit();
    
    qDebug() << "Editing finished";
}

void WenceslasII::evaluate()
{
    if (evalModel == NULL) {
        qDebug() << "Evaluation model is NULL!";
        return;
    }
    
    // Get primary database handle & check that it is opened
    QSqlDatabase primary = QSqlDatabase::database("primary");
    if (!primary.isOpen()) return;
    
    // Clear the conflict list
    ui->evalList->clear();
    
    // Create a complete list of ids ========
    QSet<int> ids;
    QSqlQuery query(primary);
    bool ret;
    
    // Iterate through runners
    query.prepare("SELECT id FROM runners");
    ret = query.exec();
    if (!ret) {
        qDebug() << "Eval runners failed query!";
        qDebug() << query.lastError();
        evalFailed = true;
        updateEvalIndicators();
        return;
    }
    
    QVariant val;
    while (query.next()) {
        val = query.value(0);
        if (!val.isNull()) ids.insert(val.toInt());
    }
    
    // Iterate through times
    query.prepare("SELECT id FROM times");
    ret = query.exec();
    if (!ret) {
        qDebug() << "Eval times failed query!";
        qDebug() << query.lastError();
        evalFailed = true;
        updateEvalIndicators();
        return;
    }
    
    while (query.next()) {
        val = query.value(0);
        if (!val.isNull()) ids.insert(val.toInt());
    }
    
    // Find complete information for each id =========
    QList<EvalTableModel::Record> records;
    bool failed = false;
    bool insert_record;
    MyCategory currentCategory;
    QSet<int>::const_iterator it;
    for(it = ids.constBegin(); it != ids.constEnd(); ++it){
        EvalTableModel::Record rec = evalModel->record();
        insert_record = true;
        
        // Find info about the runner ====
        query.prepare("SELECT first_name, surname, address, woman, age, operator FROM runners WHERE id=?");
        query.addBindValue(*it);
        ret = query.exec();
        if (!ret) {
            qDebug() << "Find runner info failed query!";
            qDebug() << query.lastError();
            failed = true;
            continue;
        }
        
        // Count the records`
        int count = 0;
        while (query.next()){
            count += 1;
        }
        
        // No Record exists for the id
        if (count == 0){
            QListWidgetItem *conflict = new QListWidgetItem(ui->evalList);
            ConflictDesc desc = {.id = *it, .type = ConflictDesc::NoRec};
            QVariant var;
            var.setValue(desc);
            conflict->setData(Qt::UserRole, var);  // Store the id
            conflict->setText(tr("Pro ID %1 neexistuje záznam s osobními informacemi běžce!").arg(*it));
            conflict->setIcon(style()->standardIcon(QStyle::SP_MessageBoxWarning));
            ui->evalList->addItem(conflict);
            
            // Do not insert the record to the eval table
            insert_record = false;
            
        // Multiple records exists for the id
        } else if(count > 1){
            QListWidgetItem *conflict = new QListWidgetItem(ui->evalList);
            ConflictDesc desc = {.id = *it, .type = ConflictDesc::MultRecs};
            QVariant var;
            var.setValue(desc);
            conflict->setData(Qt::UserRole, var);  // Store the id
            conflict->setText(tr("Pro ID %1 existuje více záznamů s osobními informacemi!").arg(*it)); 
            conflict->setIcon(style()->standardIcon(QStyle::SP_MessageBoxWarning));
            ui->evalList->addItem(conflict);
            
            // Do not insert the record to the eval table
            insert_record = false;
        
        // There is a unique record for the id
        } else {
            query.first();
            rec.setValue(0, *it);
            rec.setValue(1, query.value(0));
            rec.setValue(2, query.value(1));
            rec.setValue(3, query.value(2));
            rec.setValue(4, query.value(3));
            rec.setValue(5, query.value(4));
            
            // Store the category so that we can use it while evaluating the time
            currentCategory = cats.byAgeWoman(query.value(4).toInt(), query.value(3).toBool());
            rec.setValue(6, currentCategory.id);
        }
        
        // Find the corresponding time ====
        query.prepare("SELECT time FROM times WHERE id=?");
        query.addBindValue(*it);
        ret = query.exec();
        if (!ret) {
            qDebug() << "Find times failed query!";
            qDebug() << query.lastError();
            failed = true;
            continue;
        }
        
        count = 0;
        int mintime = INT_MAX;
        int maxtime = 0;
        while(query.next()){
            int time = query.value(0).toInt();
            mintime = std::min(time, mintime);
            maxtime = std::max(time, maxtime);
            count += 1;
        }
        
        // There is no record for the id
        if (count == 0){
            QListWidgetItem *conflict = new QListWidgetItem(ui->evalList);
            ConflictDesc desc = {.id = *it, .type = ConflictDesc::NoTime};
            QVariant var;
            var.setValue(desc);
            conflict->setData(Qt::UserRole, var);  // Store the id
            conflict->setText(tr("Pro ID %1 neexistuje záznam času!").arg(*it));
            conflict->setIcon(style()->standardIcon(QStyle::SP_MessageBoxWarning));
            ui->evalList->addItem(conflict);
            
            // Do not insert the record into the eval table
            insert_record = false;
            
        // Recorded times are inconsistent
        } else if((maxtime - mintime) > tol) {
            QListWidgetItem *conflict = new QListWidgetItem(ui->evalList);
            ConflictDesc desc = {.id = *it, .type = ConflictDesc::IncTimes};
            QVariant var;
            var.setValue(desc);
            conflict->setData(Qt::UserRole, var);  // Store the id
            conflict->setText(tr("Pro ID %1 nesouhlasí záznamy času!").arg(*it)); 
            conflict->setIcon(style()->standardIcon(QStyle::SP_MessageBoxWarning));
            ui->evalList->addItem(conflict);
            
            // Do not insert the record into the eval table
            insert_record = false;
            
        // Minimum of the recorded times is smaller than the offset
        } else if(insert_record == true && mintime < currentCategory.offset){
            QListWidgetItem *conflict = new QListWidgetItem(ui->evalList);
            ConflictDesc desc = {.id = *it, .type = ConflictDesc::LowTime};
            QVariant var;
            var.setValue(desc);
            conflict->setData(Qt::UserRole, var);  // Store the id
            QString tstr = formatTime(mintime);
            QString ostr = formatTime(currentCategory.offset);
            conflict->setText(tr("Pro ID %1 je nejnižší zaznamenaný čas %2 menší než offset %3 "
                                 "dané kategorie.").arg(*it).arg(tstr).arg(ostr)); 
            conflict->setIcon(style()->standardIcon(QStyle::SP_MessageBoxWarning));
            ui->evalList->addItem(conflict);
            
            // Do not insert the record into the eval table
            insert_record = false;
            
        // The recorded times are consistent
        } else {
            ret = query.first();
            if (!ret) qDebug() << "Failed to get first record!";
            // TODO: average the times??
            // Subtract the offset
            rec.setValue(7, query.value(0).toInt() - currentCategory.offset);
        }
        
        // Insert the record into the eval table if all is right
        if (insert_record) {
            records.append(rec);
        }
    }
    
    // Assign order in category
    std::sort(records.begin(), records.end(), ByOrderAndCategory);
    
    QList<EvalTableModel::Record>::iterator it1;
    int cid;
    QMap<int, int> order_category;
    for (it1=records.begin(); it1 != records.end(); ++it1){
        // determine category id
        cid = it1->value(6).toInt();
        
        // Increment the corresponding order in set
        if (order_category.contains(cid)) {
            order_category[cid] += 1;
        } else {
            order_category.insert(cid, 1);
        }
        
        it1->setValue(9, order_category[cid]);
    }
    
    // Assign overall order
    std::sort(records.begin(), records.end(), ByOrder);
    
    int order = 1;
    for (it1=records.begin(); it1 != records.end(); ++it1){
        it1->setValue(8, order);
        order++;
    }
    
    // Replace the results at once
    evalModel->setRecords(records);
    
    evalTime = QTime::currentTime();
    evalFailed = failed;
    evalOutdated = false;
    updateEvalIndicators();
}

void WenceslasII::autoEvalToggled(bool checked)
{
    if (checked) {
        evaluate();
        evalTimer.start();
    } else {
        evalTimer.stop();
    }
}

void WenceslasII::markEvalOutdated()
{
    evalOutdated = true;
    updateEvalIndicators();
}

void WenceslasII::updateEvalIndicators()
{
    // The indicators exist in both the time and the evaluation tab
    auto setLeds = [](std::initializer_list<KLed*> leds, const QColor &color, bool on, const QString &tip) {
        for (KLed *led : leds) {
            led->setColor(color);
            led->setState(on ? KLed::On : KLed::Off);
            led->setToolTip(tip);
        }
    };
    
    // Up-to-date indicator, the details are shown in the tooltip
    QString timeStr = evalTime.toString("HH:mm:ss");
    auto status = {ui->eval_status, ui->time_eval_status};
    if (evalFailed) {
        setLeds(status, Qt::red, true, tr("Vyhodnocení selhalo"));
    } else if (evalTime.isNull()) {
        setLeds(status, Qt::green, false, tr("Nevyhodnoceno"));
    } else if (evalOutdated) {
        setLeds(status, QColor(255, 165, 0), true, tr("Výsledky neaktuální (vyhodnoceno %1)").arg(timeStr));
    } else {
        setLeds(status, Qt::green, true, tr("Výsledky aktuální (vyhodnoceno %1)").arg(timeStr));
    }
    
    // Conflicts indicator
    int conflicts = ui->evalList->count();
    auto errors = {ui->eval_errors, ui->time_eval_errors};
    if (evalTime.isNull()) {
        setLeds(errors, Qt::green, false, tr("Nevyhodnoceno"));
    } else if (conflicts > 0) {
        setLeds(errors, Qt::red, true, tr("Konflikty: %1").arg(conflicts));
    } else {
        setLeds(errors, Qt::green, true, tr("Bez konfliktů"));
    }
}


void WenceslasII::tabChanged(int index)
{
    // Install event filter if in time measuring tab
    if(index == 1){
        QCoreApplication::instance()->installEventFilter(this);
    } else {
        QCoreApplication::instance()->removeEventFilter(this);
    }
}

void WenceslasII::conflictActivated(QListWidgetItem *item)
{
    QVariant data = item->data(Qt::UserRole);
    ConflictDesc desc = data.value<ConflictDesc>();
    
    if (desc.type == ConflictDesc::MultRecs) {
        //emit setRegFilter(1, QString("=%1").arg(desc.id));
        ui->tabWidget->setCurrentIndex(0);
        ui->regTable->sortByColumn(1, Qt::AscendingOrder);
        ui->regTable->setFocus();
        
        QModelIndex index = findItem(regModel, 1, QVariant::fromValue(desc.id));
        QModelIndex mapped = regSortProxy->mapFromSource(index);
        qDebug() << mapped.row();
        ui->regTable->selectRow(mapped.row());
        
    } else if (desc.type == ConflictDesc::NoRec){
        ui->tabWidget->setCurrentIndex(0);
        mapper->revert();
        ui->id->setValue(desc.id);
        ui->name->setFocus();
        
    } else if (desc.type == ConflictDesc::IncTimes){
        ui->tabWidget->setCurrentIndex(1);
        ui->timeTable->sortByColumn(1, Qt::AscendingOrder);
        ui->timeTable->setFocus();

        QModelIndex index = findItem(timeModel, 1, QVariant::fromValue(desc.id));
        QModelIndex mapped = timeSortProxy->mapFromSource(joinTimeEvalProxy->mapFromSource(index));
        ui->timeTable->selectRow(mapped.row());
        
    } else if (desc.type == ConflictDesc::NoTime){
        ui->tabWidget->setCurrentIndex(1);
        ui->timeTable->setFocus();
        
    } else if (desc.type == ConflictDesc::LowTime){
        ui->tabWidget->setCurrentIndex(1);
        ui->timeTable->sortByColumn(1, Qt::AscendingOrder);
        ui->timeTable->setFocus();
        
        QModelIndex index = findItem(timeModel, 1, QVariant::fromValue(desc.id));
        QModelIndex mapped = timeSortProxy->mapFromSource(joinTimeEvalProxy->mapFromSource(index));
        ui->timeTable->selectRow(mapped.row());
        
    } else {
        qDebug() << "Unknown conflict type!";
    }
}

void WenceslasII::evalCategoryIndexChanged(int index)
{
    if (evalSortProxy == NULL) {
        qDebug() << "Evaluation proxy is NULL";
        return;
    }
    
    QVariant data = ui->evalCategoryCombo->itemData(index, Qt::UserRole);
    if (data.isNull()) {
        evalSortProxy->remFilter(6);
    } else {
        evalSortProxy->addFilter(6, data);
    }
}

void WenceslasII::genderToggled(bool checked)
{
    if (checked) {
        ui->gender->setText(tr("žena"));
    } else {
        ui->gender->setText(tr("muž"));
    }
}


void WenceslasII::regDimensionChanged(const QModelIndex& parent, int first, int last)
{
    // Update the row counter !! regSortProxy hides 'deleted' rows!!
    ui->reg_count->setText(QString::number(regSortProxy->rowCount()));
}

void WenceslasII::timeDimensionChanged(const QModelIndex& parent, int first, int last)
{
    // Update the row counter !! timeSortProxy hides 'deleted' rows!!
    ui->time_count->setText(QString::number(timeSortProxy->rowCount()));
}


//void WenceslasII::clearRegFiltersClicked()
//{
//    emit clearRegFilters();
//}
//
//void WenceslasII::clearTimeFiltersClicked()
//{
//    emit clearTimeFilters();
//}
//
//void WenceslasII::clearEvalFiltersClicked()
//{
//    emit clearEvalFilters();
//}
