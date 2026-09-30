#ifndef TIMETABLEMODEL_H
#define TIMETABLEMODEL_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QHash>

#include "evaltablemodel.h"

class TimeTableModel : public QSqlTableModel {
    Q_OBJECT
public:
    TimeTableModel(
        EvalTableModel *evalModel,
        QObject *parent = nullptr, 
        const QSqlDatabase &db = QSqlDatabase()
    );

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private slots:
    void rebuildMapping();

private:
    EvalTableModel *m_evalModel = nullptr;
    QHash<int, int> idToEvalModelRow;
};

#endif /* TIMETABLEMODEL_H */

