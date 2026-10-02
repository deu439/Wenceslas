/*
 * Copyright 2026 Jan Dorazil <deu439@gmail.com>
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

#include "statusled.h"

#include <QPainter>
#include <QRadialGradient>

StatusLed::StatusLed(QWidget *parent) : QWidget(parent), color(Qt::green), state(Off)
{
}

void StatusLed::setColor(const QColor &color)
{
    if (this->color != color) {
        this->color = color;
        update();
    }
}

void StatusLed::setState(State state)
{
    if (this->state != state) {
        this->state = state;
        update();
    }
}

QSize StatusLed::sizeHint() const
{
    return QSize(16, 16);
}

void StatusLed::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Largest centered circle that fits, leaving room for the outline
    qreal d = qMin(width(), height()) - 2;
    QRectF rect((width() - d) / 2, (height() - d) / 2, d, d);
    
    // An unlit LED is drawn as a dark shade of its color
    QColor base = state == On ? color : color.darker(300);
    
    // Highlight in the upper left gives the raised look
    QRadialGradient gradient(rect.center(), d / 2, rect.topLeft() + QPointF(d * 0.35, d * 0.35));
    gradient.setColorAt(0, base.lighter(state == On ? 180 : 130));
    gradient.setColorAt(1, base);
    
    painter.setPen(QPen(palette().color(QPalette::Mid), 1));
    painter.setBrush(gradient);
    painter.drawEllipse(rect);
}
