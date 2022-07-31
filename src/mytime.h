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

#ifndef MYTIME_H
#define MYTIME_H

#include <QTime>

/**
 * @todo write docs
 */
class MyTime : QTime
{
    MyTime(QObject *parent);
    static fromMs(uint ms);
};

#endif // MYTIME_H
