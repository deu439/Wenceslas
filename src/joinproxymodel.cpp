#include <QHash>
#include <QDebug>

#include "joinproxymodel.h"

JoinProxyModel::JoinProxyModel(QObject *parent)
    : QIdentityProxyModel(parent)
{
}

void JoinProxyModel::setPrimaryModel(QAbstractTableModel* primaryModel, int idColumn)
{
    m_primaryIdCol = idColumn;
    setSourceModel(primaryModel);
}

void JoinProxyModel::setSecondaryModel(QAbstractTableModel* secondaryModel, int idColumn)
{
    m_secondaryIdCol = idColumn;
    m_secondaryModel = secondaryModel;
    
    // Monitor the Secondary Model (Custom Table)
    connect(m_secondaryModel, &QAbstractItemModel::modelReset, this, &JoinProxyModel::rebuildMapping);
    connect(m_secondaryModel, &QAbstractItemModel::rowsInserted, this, &JoinProxyModel::rebuildMapping);
    connect(m_secondaryModel, &QAbstractItemModel::rowsRemoved, this, &JoinProxyModel::rebuildMapping);
    connect(m_secondaryModel, &QAbstractItemModel::dataChanged, this, &JoinProxyModel::rebuildMapping);

    rebuildMapping();
}


int JoinProxyModel::columnCount(const QModelIndex &parent) const {
    return QIdentityProxyModel::columnCount(parent) + m_secondaryModel->columnCount();
}

void JoinProxyModel::rebuildMapping() {
    if (!m_secondaryModel) return;
    
    qDebug() << "rebuildingMapping()" << Qt::endl;

    // Only the joined columns change, so avoid a reset which would close open editors
    idToSecondaryRow.clear();
    
    int sRows = m_secondaryModel->rowCount();
    for (int r = 0; r < sRows; ++r) {
        QVariant id = m_secondaryModel->index(r, m_secondaryIdCol).data();
        if (id.isValid()) {
            idToSecondaryRow.insert(id.toInt(), r);
        }
    }
    
    int rows = rowCount();
    int pCols = QIdentityProxyModel::columnCount();
    if (rows > 0 && columnCount() > pCols) {
        emit dataChanged(index(0, pCols, QModelIndex()), index(rows - 1, columnCount() - 1, QModelIndex()));
    }
}

QVariant JoinProxyModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int col = index.column();
    qDebug() << "data() " << "row " << row << "col " << col << Qt::endl;
    
    int pCols = QIdentityProxyModel::columnCount();
    
    if (col < pCols) {
        return QIdentityProxyModel::data(index, role);
    } else {
        int id = QIdentityProxyModel::index(row, m_primaryIdCol).data(Qt::DisplayRole).toInt();
        int sRow = idToSecondaryRow.value(id, -1);
        if (sRow >= 0) {
            return m_secondaryModel->index(sRow, col - pCols).data(role);
        }
    }
    
    return QVariant();
}

QVariant JoinProxyModel::headerData(int section, Qt::Orientation orientation, int role) const {
    
    if (orientation == Qt::Horizontal) {
        qDebug() << "headerData() " << section << Qt::endl;
        
        int pCols = QIdentityProxyModel::columnCount();
        
        if (section < pCols) {
            return QIdentityProxyModel::headerData(section, orientation, role);
        } else {
            QVariant hd = m_secondaryModel->headerData(section - pCols, orientation, role);
            qDebug() << "headerData(): " << hd << Qt::endl;
            return hd;
        }
    }
    return QIdentityProxyModel::headerData(section, orientation, role);
}


Qt::ItemFlags JoinProxyModel::flags(const QModelIndex &index) const {
    qDebug() << "flags()" << Qt::endl;
    int row = index.row();
    int col = index.column();
    
    int pCols = QIdentityProxyModel::columnCount();
    
    // Delegate flag checking to the underlying model that owns the column
    if (col < pCols) {
        return QIdentityProxyModel::flags(index);
    } else {
        int id = QIdentityProxyModel::index(row, m_primaryIdCol).data(Qt::DisplayRole).toInt();
        int sRow = idToSecondaryRow.value(id, -1);
        if (sRow >= 0) {
            return m_secondaryModel->index(sRow, col - pCols).flags();
        }
    }

    return QIdentityProxyModel::flags(index);
}

bool JoinProxyModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    qDebug() << "setData()" << Qt::endl;
    
    int row = index.row();
    int col = index.column();
    
    int pCols = QIdentityProxyModel::columnCount();
    
    bool success = false;

    // Route the edit request directly to the responsible source model
    if (col < pCols) {
        QModelIndex primaryIdx = QIdentityProxyModel::index(row, col);
        success = QIdentityProxyModel::setData(primaryIdx, value, role);
    } else {
        int id = QIdentityProxyModel::index(row, m_primaryIdCol).data(Qt::DisplayRole).toInt();
        int sRow = idToSecondaryRow.value(id, -1);
        QModelIndex secondaryIdx = m_secondaryModel->index(sRow, col - pCols);
        success = m_secondaryModel->setData(secondaryIdx, value, role);
    }

    if (success) {
        emit dataChanged(index, index, {role});
    }
    return success;
}

QModelIndex JoinProxyModel::index(int row, int column, const QModelIndex &parent) const {
    // Since this is a flat table join, we don't support tree structures (valid parents)
    if (parent.isValid()) {
        return QModelIndex();
    }

    // Safety check: ensure requested row/col are within our proxy's total size
    if (row < 0 || row >= rowCount() || column < 0 || column >= columnCount()) {
        return QModelIndex();
    }

    // Create a proxy index pointing to THIS model
    return createIndex(row, column);
}

//void JoinProxyModel::onPrimaryDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
//    // If the actual ID column changed, we have to rebuild the relational map entirely
//    if (topLeft.column() <= m_primaryIdCol && m_primaryIdCol <= bottomRight.column()) {
//        rebuildMapping();
//        return;
//    }
//    // Otherwise, forward data notifications seamlessly to the view
//    emit dataChanged(this->index(topLeft.row(), topLeft.column()), 
//                     this->index(bottomRight.row(), bottomRight.column()), roles);
//}
//
//void JoinProxyModel::onSecondaryDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
//    if (topLeft.column() <= m_secondaryIdCol && m_secondaryIdCol <= bottomRight.column()) {
//        rebuildMapping();
//        return;
//    }
//
//    int pCols = m_primaryModel ? m_primaryModel->columnCount() : 0;
//    
//    // Find every proxy row pointing to the modified secondary data slice and alert the view
//    for (int i = 0; i < m_mapping.size(); ++i) {
//        int sRow = m_mapping[i].secondaryRow;
//        if (sRow >= topLeft.row() && sRow <= bottomRight.row()) {
//            emit dataChanged(this->index(i, pCols + topLeft.column()), 
//                             this->index(i, pCols + bottomRight.column()), roles);
//        }
//    }
//}
