#include "timetablemodel.h"

TimeTableModel::TimeTableModel(
    EvalTableModel* evalModel, QObject* parent, const QSqlDatabase& db
) : QSqlTableModel(parent, db), m_evalModel(evalModel) 
{
    rebuildMapping();
}


int TimeTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return QSqlTableModel::columnCount() + m_evalModel->columnCount();
}

QVariant TimeTableModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int col = index.column();
    
    if (col < columnCount()) {
        return QSqlTableModel::index(row, col).data(role);
    } else {
        int id = QSqlTableModel::index(row, 1).data(Qt::DisplayRole).toInt();
        return m_evalModel->index(idToEvalModelRow[id], col - columnCount()).data(role);
    }
    
    return QVariant();
}

Qt::ItemFlags TimeTableModel::flags(const QModelIndex& index) const
{
    int row = index.row();
    int col = index.column();
    if (col < columnCount()) {
        return QSqlTableModel::index(row, col).flags();
    } else {
        return m_evalModel->index(row, col - columnCount()).flags();
    }
}

QVariant TimeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QSqlTableModel::headerData(section, orientation, role);
}

void TimeTableModel::rebuildMapping()
{
    beginResetModel();
    
    idToEvalModelRow.clear();
    
    int sRows = m_evalModel->rowCount();
    for (int r = 0; r < sRows; ++r) {
        QVariant id = m_evalModel->index(r, 0).data();
        if (id.isValid()) {
            idToEvalModelRow.insert(id.toInt(), r);
        }
    }
    
    endResetModel();
}

bool TimeTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return QSqlTableModel::setData(index, value, role);
}





