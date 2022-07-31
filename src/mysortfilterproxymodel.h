/*
 * Copyright 2021 Jan Dorazil <jdorazil@intern.tuwien.ac.at>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QMap>

/**
 * @todo write docs
 */
class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    
public:
    /**
     * Default constructor
     */
    MySortFilterProxyModel(QObject *parent = 0);
    void addFilter(int column, const QVariant &val);
    void remFilter(int column);
    
//public slots:
//    void filterChanged(int column, const QString &pattern);
    
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    // column -> filter string mapping
    QMap<int, QVariant> filters;
};

#endif // MYSORTFILTERPROXYMODEL_H
