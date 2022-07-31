// mytablemodel.h
#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QList>

//#include "myrequest.h"

class EvalTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    typedef struct MyCategory{
        // Constructor
        MyCategory(uint id, const QString &name, 
                    uint from, uint to, uint offset, bool zena) 
        : id(id), name(name), from(from), to(to), offset(offset), gen(gen)
        {};
        
        // By default sort by id
        bool operator<(const MyCategory &b)
        {
            return id < b.id;
        }
        
        // Data
        uint id;
        QString name;
        uint from;
        uint to;
        uint offset;
        bool zena;
    } MyCategory;
    
    /*
     * The standard functions
     */
    EvalTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    //Qt::ItemFlags flags(const QModelIndex & /*index*/) const;
    
    bool select();
    
    /*
     * Determines the category ID based on age and gender
     */
    int idKategorie(int vek, bool zena, QString *popis = NULL);
    
    /*
     * Returns the category name using its ID
     */
    bool popisKategorie(unsigned int id, QString &popis) const;
    
private:
    QList<MyCategory> categories;
};

#endif /* MYTABLEMODEL_H */

