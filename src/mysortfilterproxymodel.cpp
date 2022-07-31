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

#include "mysortfilterproxymodel.h"
#include <QDebug>

#include "mycategories.h"

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void MySortFilterProxyModel::addFilter(int column, const QVariant &val)
{
    filters.insert(column, val);
    invalidateFilter();
}

void MySortFilterProxyModel::remFilter(int column)
{
    filters.remove(column);
    invalidateFilter();
}


//void MySortFilterProxyModel::filterChanged(int column, const QString& pattern)
//{
//    if (filters.contains(column)) {
//        if (pattern.isEmpty()) {
//            filters.remove(column);
//        } else {
//            filters[column] = pattern;
//        }
//    } else {
//        if (!pattern.isEmpty()) {
//            filters.insert(column, pattern);
//        }
//    }
//    
//    invalidateFilter();
//    qDebug() << column << ", " << pattern;
//}


//bool MySortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
//{
//    QModelIndex index;
//    QMap<int, QString>::const_iterator it;
//    QString pattern;
//    QString data;
//    
//    bool accept = true;
//    for (it = filters.constBegin(); it != filters.constEnd(); ++it){
//        index = sourceModel()->index(source_row, it.key(), source_parent);
//        pattern = it.value();
//        data = sourceModel()->data(index).toString();
//        
//        if (pattern[0] == '=') {
//            if (QString::compare(data, pattern.remove(0, 1)) != 0)
//                accept = false;
//        } else {
//            if (!data.contains(pattern))
//                accept = false;
//        }
//    }
//    
//    return accept;
//}

bool MySortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    QModelIndex index;
    QMap<int, QVariant>::const_iterator it;
    QVariant data;
    QVariant val;
    
    bool accept = true;
    for (it = filters.constBegin(); it != filters.constEnd(); ++it){
        index = sourceModel()->index(source_row, it.key(), source_parent);
        val = it.value();
        data = sourceModel()->data(index);
        
        if (val.canConvert<MyCategory>()){
            if (val.value<MyCategory>() == data.value<MyCategory>()){
                // Do nothing
            } else {
                accept = false;
            }
        } else {
            // Do nothing
        }
    }
    
    // A trick to hide deleted rows
    data = sourceModel()->headerData(source_row, Qt::Vertical, Qt::DisplayRole);
    if (QString::compare(data.toString(), "!") == 0) {
        accept = false;
    }
    
    return accept;
}

bool MySortFilterProxyModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
    
    //if (QString::compare(leftData.typeName(), "MyCategory") == 0){
    if (leftData.canConvert<MyCategory>()) {
        MyCategory left = leftData.value<MyCategory>();
        MyCategory right = rightData.value<MyCategory>();
        
        return left < right;
    } else {
        return QSortFilterProxyModel::lessThan(left, right);
    }
}

