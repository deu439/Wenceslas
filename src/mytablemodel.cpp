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

#include "mytablemodel.h"
#include "operators.h"

EvalTableModel::EvalTableModel(QObject *parent, QSqlDatabase db)
 : QSqlTableModel(parent, db)
{
}

QVariant EvalTableModel::data(const QModelIndex& index, int role) const
{
    QVariant item;
    int row = index.row();
    int col = index.column();

    if( row >= rowCount() ){
        qDebug() << "data(): Row index out of bounds" << endl;
        return QVariant();
    }
    
    if( col >= columnCount() ){
        qDebug() << "data(): Column index out of bounds" << endl;
        return QVariant();
    }
    
    QString kat = QString();
    Operators *op = Operators::getInstance();
    int op_id;
    
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
                // When invalid QString() is returned
                popisKategorie(QSqlTableModel::data(index, role).toInt(), kat);
                item = kat;
                break;
                
            case 7: // Zapsal
                op_id = QSqlTableModel::data(index, role).toInt();
                item = op->byId(op_id);
                break;
                
            default: // For others just call the base class method
                item = QSqlTableModel::data(index, role);
        }
        
    // Text alignment role    
    } else if ( role == Qt::TextAlignmentRole ) {
        switch (col) {
            case 5:
                item = Qt::AlignHCenter + Qt::AlignVCenter;
                break;
            default:
                item = Qt::AlignLeft + Qt::AlignVCenter;
        }
    
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
        qDebug() << "headerData(): Column index out of bounds" << endl;
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
                        return tr("Zapsal");
                    default: // Shouldn't happen
                        qDebug() << "headerData(): Something went wrong" << endl;
                        return QVariant();
                }
        }
    }
    
    return QSqlTableModel::headerData(section, orientation, role);
}

/*
Qt::ItemFlags MyTableModel::flags(const QModelIndex & index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
*/

int EvalTableModel::idKategorie(int vek, bool zena, QString *popis)
{
    int ret = -1; // Return -1 in case of error
    QList<MyCategory>::const_iterator it;
    for (it = categories.cbegin(); it != categories.cend(); ++it) {
        if (it->zena == zena && it->od <= vek && it->_do >= vek) {
            ret = it->id_kategorie;
            if( popis != NULL )
                *popis = it->popis;
            break;
        }
    }
    
    return ret;
}

bool EvalTableModel::popisKategorie(unsigned int id, QString &popis) const
{
    bool ret = false; // In case of error
    QList<MyCategory>::const_iterator it;
    for (it = categories.cbegin(); it != categories.cend(); ++it) {
        if (it->id_kategorie == id) {
            popis = it->popis;
            ret = true;
            break;
        }
    }
    
    return ret;
}
