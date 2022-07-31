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

#ifndef MYGENDERITEMDELEGATE_H
#define MYGENDERITEMDELEGATE_H

#include <QStyledItemDelegate>

/**
 * Translates 1->woman, 0->man + includes a pictogram
 * This is done in a delegate class instead of data model so that its reusable.
 */
class MyGenderItemDelegate : public QStyledItemDelegate
{
public:
    MyGenderItemDelegate(QObject *parent = 0);
    ~MyGenderItemDelegate();
    
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex & index) const override;
               
private:
    QPixmap woman;
    QPixmap man;
};

#endif // MYGENDERITEMDELEGATE_H
