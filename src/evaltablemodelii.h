// evaltablemodel.h
#ifndef EVALTABLEMODEL_H
#define EVALTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QMap>

#include "mycategories.h"
#define COLUMN_COUNT_DEF 10

/*
 * Custom model is required to add additional column for the category.
 */
class EvalTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    static const int COLUMN_COUNT;
    static const QString COLUMN_NAMES[COLUMN_COUNT_DEF];
    
    class Record {
    public:
        Record() {};
        
        Record(const Record &other) 
        {
            *this = other;
        };

        Record &operator=(const Record &other)
        {
            for (int i = 0; i < COLUMN_COUNT_DEF; i++) {
                data[i] = other.value(i);
            }
            return *this;
        }; 
        
        QVariant value(int index) const
        {
            if (index < COLUMN_COUNT_DEF && index >= 0)
                return data[index];
            else
                return QVariant();
        }
        
        bool setValue(int index, const QVariant &value)
        {
            data[index] = value;
            return true;
        }
        
        QString fieldName(int index) const
        {
            if (index < COLUMN_COUNT_DEF && index >= 0)
                return COLUMN_NAMES[index];
            else
                return QString();
        }
        
        int count() const
        {
            return COLUMN_COUNT_DEF;
        }
        
    private:
        QVariant data[COLUMN_COUNT_DEF];
    };

    /*
     * The standard functions
     */
    EvalTableModel(QObject *parent, MyCategories cats);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex & parent) override;
    bool setData(const QModelIndex & index, const QVariant & value, int role) override;
    Record record();
    Record record(int row);
    bool insertRecord(int row, const Record &rec);
    //Qt::ItemFlags flags(const QModelIndex & /*index*/) const override;
    
    MyCategories cats;
    QList<Record> modelData;
    
    
};

#endif /* EVALTABLEMODEL_H */

