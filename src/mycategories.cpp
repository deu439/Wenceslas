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

#include "mycategories.h"

void MyCategories::addCategory(const MyCategory& cat)
{
    this->append(cat);
}

QString MyCategories::categoryName(uint age, bool woman) const
{
    QList<MyCategory>::const_iterator it = this->begin();
    for (; it != this->end(); ++it){
        if (it->from <= age && it->to >= age && it->woman == woman){
            return it->name;
        }
    }
    
    return QString();
}

int MyCategories::categoryId(uint age, bool woman) const
{
    QList<MyCategory>::const_iterator it = this->begin();
    for (; it != this->end(); ++it){
        if (it->from <= age && it->to >= age && it->woman == woman){
            return it->id;
        }
    }
    
    return 0;
}

MyCategory MyCategories::byAgeWoman(uint age, bool woman) const
{
    QList<MyCategory>::const_iterator it = this->begin();
    for (; it != this->end(); ++it){
        if (it->from <= age && it->to >= age && it->woman == woman){
            return *it;
        }
    }
    
    return MyCategory();
}


MyCategory MyCategories::byId(uint id) const
{
    QList<MyCategory>::const_iterator it = this->begin();
    for (; it != this->end(); ++it){
        if (it->id == id){
            return *it;
        }
    }
    
    return MyCategory();
}
