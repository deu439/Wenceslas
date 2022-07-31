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

#include "evaltablemodel.h"

EvalTableModel::EvalTableModel(QObject *parent, MyCategories cats, QSqlDatabase db)
 : QSqlTableModel(parent, db), cats(cats)
{
}

//int EvalTableModel::columnCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    return 9;
//}

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
    
    if( col >= columnCount() ){
        qDebug() << "data(): Column index out of bounds" << Qt::endl;
        return QVariant();
    }
    
    // Display role
    if( role == Qt::DisplayRole ){
        switch(col){
            case 4: // Pohlaví
                if(QSqlTableModel::data(index, role).toBool())
                    item = tr("žena");
                else
                    item = tr("muž");
                break;
                
            case 6: // Kategorie
                {
                    // The cat id is not really stored in the db, to avoid discrepancies 
                    // caused by different config files.
                    //QString name = cats.categoryName(age, gen);
                    cid = QSqlTableModel::data(index, role).toInt();
                    item.setValue(cats.byId(cid));
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
     } else if (role == Qt::DecorationRole && col == 4) {
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

QVariant EvalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( orientation == Qt::Horizontal && section >= columnCount() ){
        qDebug() << "headerData(): Column index out of bounds" << Qt::endl;
        return QVariant();
    }
    if( orientation == Qt::Horizontal ) {
        if( role == Qt::DisplayRole ){
            
                switch(section){
                    case 0:
                        return tr("ID");
                    case 1:
                        return tr("Jméno");
                    case 2:    
                        return tr("Příjmení");
                    case 3:
                        return tr("Bydliště");
                    case 4:
                        return tr("Pohlaví");
                    case 5:
                        return tr("Věk");
                    case 6:
                        return tr("Kategorie");
                    case 7:
                        return tr("Čas");
                    case 8:
                        return tr("Pořadí");
                    case 9:
                        return tr("Pořadí v kategorii");
                    default:
                        return QSqlTableModel::headerData(section, orientation, role);
                }
        }
    }
    
    return QSqlTableModel::headerData(section, orientation, role);
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
