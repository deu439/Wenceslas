/*
 * Copyright 2020 Jan Dorazil <deu439@gmail.com>
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

#ifndef NOTEDITABLEDELEGATE_H
#define NOTEDITABLEDELEGATE_H

#include <QItemDelegate>

class NotEditableDelegate : public QItemDelegate
{
    Q_OBJECT
    
public:
    explicit NotEditableDelegate(QObject *parent = 0);

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;

};

#endif  // NONEDITABLEDELEGATE_H
