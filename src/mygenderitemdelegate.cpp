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

#include "mygenderitemdelegate.h"
#include <QPainter>

MyGenderItemDelegate::MyGenderItemDelegate(QObject *parent)
: QStyledItemDelegate(parent), woman(QPixmap("female.png")), man(QPixmap("male.png"))
{
}

MyGenderItemDelegate::~MyGenderItemDelegate()
{
}


void MyGenderItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex& index) const
{
    if(index.data().canConvert<bool>()) {
        bool gen = qvariant_cast<bool>(index.data());
        QRect pix_rect = woman.rect();
        int offset = option.rect.height() / 2 - pix_rect.height() / 2;
        pix_rect.moveTopLeft(option.rect.topLeft() + QPoint(0, offset));
        
        QRect text_rect = option.rect;
        text_rect.setLeft(option.rect.left() + pix_rect.width() + 5);
        
        // Get background/text colors
        QColor bg = QColor();
        QColor fg = QColor();
        if (option.state & QStyle::State_Selected) {
            bg = option.palette.color(QPalette::Highlight);
            fg = option.palette.color(QPalette::HighlightedText);
        } else {
            bg = option.palette.color(QPalette::Base);
            fg = option.palette.color(QPalette::Text);
        }
        
        // Save painter state
        painter->save();
        
        // Paint background 
        painter->fillRect(option.rect, bg);
        
        // Paint the text & icon
        painter->setPen(fg);
        if(gen){
            painter->drawPixmap(pix_rect, woman);
            painter->drawText(text_rect, option.displayAlignment, tr("žena"));
        } else {
            painter->drawPixmap(pix_rect, man);
            painter->drawText(text_rect, option.displayAlignment, ("muž"));
        };
        
        // Restore painter state
        painter->restore();
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
