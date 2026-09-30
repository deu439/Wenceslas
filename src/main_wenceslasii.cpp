#include <QApplication>
#include <QMetaType>

#include "wenceslasii.h"
#include "mycategories.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WenceslasII w;
    w.show();
    
    // Register custom type comparators converters
    qRegisterMetaType<MyCategory>("MyCategory");
    QMetaType::registerConverter(&MyCategory::toString);
    QMetaType::registerComparators<MyCategory>();
    
    return app.exec();
}

