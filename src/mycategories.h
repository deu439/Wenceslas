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

#ifndef MYCATEGORIES_H
#define MYCATEGORIES_H

#include <QList>
#include <QMetaType>

/**
 * Structure containing a single category
 */
class MyCategory
{
public:
    // Default constructor
    MyCategory() 
    : id(0), name(QString("None")), from(0), to(0), offset(0), woman(false)
    {};
    
    MyCategory(uint id, const QString &name, 
                uint from, uint to, uint offset, bool gen) 
    : id(id), name(name), from(from), to(to), offset(offset), woman(gen)
    {};
    
    // By default sort by id
    bool operator<(const MyCategory b) const
    {
        return id < b.id;
    };
    
    // Compare ids
    bool operator==(const MyCategory b) const
    {
        return id == b.id;
    };
    
    QString toString() const
    {
        return name;
    };
    
    uint id;
    QString name;
    uint from;
    uint to;
    uint offset;
    bool woman;
};

Q_DECLARE_METATYPE(MyCategory)

/**
 * Class that contains all categories
 */
class MyCategories : public QList<MyCategory>
{
public:
    /**
     * Add category
     */
    void addCategory(const MyCategory &cat);
    
    /**
     * Returns category name given age and gender
     */
    QString categoryName(uint age, bool woman) const;
    int categoryId(uint age, bool woman) const;
    MyCategory byAgeWoman(uint age, bool woman) const;
    MyCategory byId(uint id) const;
    
    //QList<MyCategory> cats;
};

#endif // MYCATEGORIES_H
