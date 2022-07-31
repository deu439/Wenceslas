// mytablemodel.h
#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QList>

#include "mycategories.h"

/*
 * Custom model is required to add additional column for the category.
 */

class MyTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    /*
     * The standard functions
     */
    MyTableModel(QObject *parent, MyCategories cats, QSqlDatabase db = QSqlDatabase());
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex & /*index*/) const override;
    
    MyCategories cats;
};

#endif /* MYTABLEMODEL_H */

