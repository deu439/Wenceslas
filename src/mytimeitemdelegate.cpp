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

#include "mytimeitemdelegate.h"

#include <QPainter>
#include <QDebug>
#include <QLineEdit>
#include <math.h>


MyTimeItemDelegate::MyTimeItemDelegate(QObject *parent)
: QItemDelegate(parent)
{

}

QWidget *MyTimeItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);
    editor->setText("0:00.0");

    return editor;
}

void MyTimeItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    uint ms = index.model()->data(index, Qt::EditRole).toUInt();

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(formatTime(ms));
}

void MyTimeItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
    QString text = lineEdit->text();
    
    bool ok;
    uint ms = parseTime(text, &ok);
    
    // Modify model only if we are able to parse the input
    if (ok) {
        model->setData(index, ms, Qt::EditRole);
    }
}


QString MyTimeItemDelegate::formatTime(uint ms) const
{
    uint mins = ms / 60000;
    float sec = (float)(ms - mins*60000) / 1000;
    //QString formatted;
    //formatted.sprintf("%d:%05.2f", mins, sec);
    QString formatted = QString::asprintf("%d:%05.2f", mins, sec);
    return formatted;
}

uint MyTimeItemDelegate::parseTime(const QString& str, bool *ok) const
{
    QStringList str_split = str.split(":");
    if (str_split.size() != 2) {
        *ok = false;
        return 0;
    }
    uint ms = str_split[0].toUInt(ok) * 60000;
    if (!*ok) return 0;
    ms += round(str_split[1].toFloat(ok) * 1000);
    if (!*ok) return 0;
    
    return ms;
}

void MyTimeItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(index.data().canConvert<uint>()) {
        uint ms = qvariant_cast<uint>(index.data());
        QRect text_rect = option.rect;
        QString time = formatTime(ms);
        
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
        
        // Print time
        painter->setPen(fg);
        painter->drawText(text_rect, option.displayAlignment, time);
        
        // Restore painter state
        painter->restore();
        
    } else {
        QItemDelegate::paint(painter, option, index);
    }
}
