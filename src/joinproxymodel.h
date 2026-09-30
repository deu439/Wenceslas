#ifndef JOINPROXYMODEL_H
#define JOINPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QList>
#include <QVector>
#include <QHash>

class JoinProxyModel : public QIdentityProxyModel {
    Q_OBJECT
public:
    JoinProxyModel(QObject *parent);
    void setPrimaryModel(QAbstractTableModel *primaryModel, int idColumn);
    void setSecondaryModel(QAbstractTableModel *secondaryModel, int idColumn);
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;

private slots:
    void rebuildMapping();
    //void onPrimaryDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    //void onSecondaryDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

private:
    QAbstractItemModel *m_secondaryModel;
    int m_primaryIdCol;
    int m_secondaryIdCol;
    QHash<int, int> idToSecondaryRow;
    
};

#endif /* JOINPROXYMODEL_H */
