// mytablemodel.cpp

#include <iostream>
#include <QList>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlField>
#include <QDebug>
#include <QSize>
#include <QPixmap>

#include "mytablemodelii.h"


MyTableModel::MyTableModel(QObject *parent, MyCategories cats, QSqlDatabase db)
 : QSqlTableModel(parent, db), cats(cats)
{
}

int MyTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 9;
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const
{
    QVariant item;
    int row = index.row();
    int col = index.column();

    if( row >= rowCount() ){
        qDebug() << "data(): Row index out of bounds" << Qt::endl;
        return QVariant();
    }
    
    if( col >= columnCount() ){
        qDebug() << "data(): Column index out of bounds" << Qt::endl;
        return QVariant();
    }
    
    // Display role
    if( role == Qt::DisplayRole ){
        switch(col){
            case 5: // Pohlaví
                if(QSqlTableModel::data(index, role).toBool())
                    item = tr("žena");
                else
                    item = tr("muž");
                break;
                
            case 8: // Kategorie
                {
                    // The cat id is not really stored in the db, to avoid discrepancies 
                    // caused by different config files.
                    uint age = QSqlTableModel::data(createIndex(row, 6), Qt::DisplayRole).toInt();
                    bool gen = QSqlTableModel::data(createIndex(row, 5), Qt::DisplayRole).toBool();
                    //QString name = cats.categoryName(age, gen);
                    item.setValue(cats.byAgeWoman(age, gen));
                }
                break;
            //case 7: // Operator
            //    item = QSqlTableModel::data(createIndex(row, 6), Qt::DisplayRole);
            //    break;
                
            default: // For others just call the base class method
                item = QSqlTableModel::data(index, role);
        }
        
    // Text alignment role    
    //} else if ( role == Qt::TextAlignmentRole ) {
    //    switch (col) {
    //        case 5:
    //            item = Qt::AlignHCenter + Qt::AlignVCenter;
    //            break;
    //        default:
    //            item = Qt::AlignLeft + Qt::AlignVCenter;
    //    }
    
    // Decoration role
     } else if (role == Qt::DecorationRole && col == 5) {
         if (QSqlTableModel::data(index, Qt::DisplayRole).toBool())
             item = QPixmap("female.png");
         else
             item = QPixmap("male.png");

    // Default
    } else {
        item = QSqlTableModel::data(index, role);
    }
    
    return item;
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( orientation == Qt::Horizontal && section >= columnCount() ){
        qDebug() << "headerData(): Column index out of bounds" << Qt::endl;
        return QVariant();
    }
    if( orientation == Qt::Horizontal ) {
        if( role == Qt::DisplayRole ){
            
                switch(section){
                    case 0:
                        return tr("Klíč");
                    case 1:
                        return tr("ID");
                    case 2:
                        return tr("Jméno");
                    case 3:    
                        return tr("Příjmení");
                    case 4:
                        return tr("Bydliště");
                    case 5:
                        return tr("Pohlaví");
                    case 6:
                        return tr("Věk");
                    case 7:
                        return tr("Operátor");
                    case 8:
                        return tr("Kategorie");
                    default:
                        return QSqlTableModel::headerData(section, orientation, role);
                }
        }
    }
    
    return QSqlTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags MyTableModel::flags(const QModelIndex & index) const
{
    int col = index.column();
    if (col < 8){
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    } else {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
}
