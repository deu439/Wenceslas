// evaltablemodel.cpp

#include <iostream>
#include <QList>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlField>
#include <QDebug>
#include <QSize>
#include <QPixmap>

#include "evaltablemodelii.h"

const int EvalTableModel::COLUMN_COUNT = COLUMN_COUNT_DEF;
const QString EvalTableModel::COLUMN_NAMES[COLUMN_COUNT_DEF] = {"ID", "Jméno", "Příjmení", "Bydliště", "Pohlaví", "Věk", "Kategorie", "Čas", "Pořadí", "Pořadí v kategorii"};

EvalTableModel::EvalTableModel(QObject *parent, MyCategories cats)
 : cats(cats)
{
}

int EvalTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return modelData.count();
}

int EvalTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COLUMN_COUNT;
}

QVariant EvalTableModel::data(const QModelIndex& index, int role) const
{
    QVariant item;
    int row = index.row();
    int col = index.column();
    int cid;

    if( row >= rowCount() ){
        qDebug() << "data(): Row index out of bounds" << Qt::endl;
        return QVariant();
    }
    
    if( col >= COLUMN_COUNT ){
        qDebug() << "data(): Column index out of bounds" << Qt::endl;
        return QVariant();
    }
    
    // Display role
    if( role == Qt::DisplayRole ){
        switch(col){
            case 4: // Woman
                if(modelData[row].value(4).toBool())
                    item = tr("žena");
                else
                    item = tr("muž");
                break;
                
            case 6: // Category
                {
                    // The category id is not really stored in the db, to avoid discrepancies 
                    // caused by different config files.
                    cid = modelData[row].value(6).toInt();
                    item.setValue(cats.byId(cid));
                }
                break;
                
            default: // Undefined
                item = modelData[row].value(col);
        }
    
    // Decoration role
     } else if (role == Qt::DecorationRole && col == 4) {
         if (modelData[row].value(4).toBool())
             item = QPixmap("female.png");
         else
             item = QPixmap("male.png");

    // Invalid
    } else {
        item = QVariant();
    }
    
    return item;
}

QVariant EvalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( orientation == Qt::Horizontal && section >= columnCount() ){
        qDebug() << "headerData(): Column index out of bounds" << Qt::endl;
        return QVariant();
    }
    QVariant item;
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole ){
        return QVariant(COLUMN_NAMES[section]);
    }
    
    return QVariant();
}

bool EvalTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row+count-1);
    for (int i = row; i < (row + count); i++) {
        modelData.insert(i, Record());
    }
    endInsertRows();
    
    return true;
}

bool EvalTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
    beginRemoveRows(parent, row, row+count-1);
    for (int i = row+count-1; i >= row; i--) {
        modelData.removeAt(i);
    }
    endRemoveRows();
    
    return true;
}


bool EvalTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int row = index.row();
    int col = index.column();

    if( row >= rowCount() || row < 0 ){
        qDebug() << "setData(): Row index out of bounds" << Qt::endl;
        return false;
    }
    
    if( col >= COLUMN_COUNT || col < 0){
        qDebug() << "setData(): Column index out of bounds" << Qt::endl;
        return false;
    }
    
    // Display role
    if( role == Qt::DisplayRole ){
        modelData[row].setValue(col, value);
    }
    
    return true;
}

EvalTableModel::Record EvalTableModel::record()
{
    Record rec;
    return rec;
}

EvalTableModel::Record EvalTableModel::record(int row)
{
    return modelData[row];
}


bool EvalTableModel::insertRecord(int row, const Record &rec)
{

    beginInsertRows(QModelIndex(), row, row);
    modelData.insert(row, rec);
    endInsertRows();
    
    return true;
}



//Qt::ItemFlags EvalTableModel::flags(const QModelIndex & index) const
//{
//    int col = index.column();
//    if (col < 8){
//        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
//    } else {
//        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
//    }
//}
