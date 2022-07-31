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

#ifndef WENCESLASII_H
#define WENCESLASII_H

#include <QMainWindow>
#include <QSettings>
#include <QMap>
#include <QDataWidgetMapper>
#include <QTimer>
#include <QElapsedTimer>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QListWidgetItem>

#include "mytablemodelii.h"
#include "mycategories.h"
#include "spinboxdelegate.h"
#include "mysortfilterproxymodel.h"
#include "evaltablemodel.h"

namespace Ui {
    class WenceslasII;
}

struct ConflictDesc
{
    int id;
    enum ConflictType {NoRec, MultRecs, NoTime, IncTimes, LowTime} type;
};
Q_DECLARE_METATYPE(ConflictDesc)


//class NotEditableDelegate : public QItemDelegate
//{
//    Q_OBJECT
//    
//public:
//    explicit NotEditableDelegate(QObject *parent = 0)
//        : QItemDelegate(parent)
//    {}
//
//protected:
//    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
//    { return false; }
//    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
//    { return Q_NULLPTR; }
//
//};

class WenceslasII : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * Default constructor
     */
    explicit WenceslasII(QWidget *parent = nullptr);
    
    /**
     * Destructor
     */
    ~WenceslasII();
    
    /** 
     * Returns time in ms parsed from a string
     */
    uint parseTime(const QString &str, bool *ok);
    QString formatTime(uint time);
    
private:
    bool loadSettings();
    void enableButtons();
    void setupRegTable();
    void setupTimeTable();
    void setupEvalTable();
    void timeTableEdit();
    bool eventFilter(QObject *o, QEvent* e);
    QStringList recToStringList(const QSqlRecord &rec);
    QString recToHTML(const QSqlRecord& rec);
    void exportCSV(bool order = false);
    void exportHTML(bool order = false);
    QModelIndex findItem(QAbstractTableModel *model, int col, QVariant val);
    
    Ui::WenceslasII *ui;
    
    // Global settings
    QString path;
    QString op_name;
    int tol = 1000; // Default is 1 second
    
    // Registration table
    MyTableModel *regModel = NULL;
    MySortFilterProxyModel *regSortProxy = NULL;
    QDataWidgetMapper *mapper = NULL;
    
    // Time table
    QSqlTableModel *timeModel = NULL;
    MySortFilterProxyModel *timeSortProxy = NULL;
    QTimer timer;
    QElapsedTimer elapsed_timer;
    uint last_ms = 0;
    
    // Eval table
    EvalTableModel *evalModel = NULL;
    MySortFilterProxyModel *evalSortProxy;
    
private slots:
    void openFile();
    void newFile();
    void importFile();
    void actionExportCSV();
    void actionExportCSV1();
    void actionExportHTML();
    void actionExportHTML1();
    
    void createRecord();
    void removeRecord();
    void correctRecord();
    void regOriginalOrder();
    void timeOriginalOrder();
    void evalOriginalOrder();
    void startTimer();
    void clearTimer();
    void updateClock();
    void recordTime();
    void removeTime();
    void editing_finished(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
    void evaluate();
    void tabChanged(int index);
    void conflictActivated(QListWidgetItem *item);
    //void clearRegFiltersClicked();
    //void clearTimeFiltersClicked();
    //void clearEvalFiltersClicked();
    void evalCategoryIndexChanged(int index);

signals:
    //void setRegFilter(int column, const QString &pattern);
    //void clearRegFilters();
    //void setTimeFilter(int column, const QString &pattern);
    //void clearTimeFilters();
    //void setEvalFilter(int column, const QString &pattern);
    //void clearEvalFilters();
};

#endif // WENCESLASII_H
