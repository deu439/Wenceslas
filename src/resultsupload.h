#ifndef RESULTSUPLOAD_H
#define RESULTSUPLOAD_H

#include <QObject>
#include <QString>
#include <QUrl>

// Builds the results CSV and pushes it to the race website upload endpoint.
class ResultsUpload
{
public:
    struct Row {
        int number;
        QString name;
        unsigned ms;
        QString category;
    };

    static QString buildCsv(const QList<Row> &rows);
    static bool upload(const QUrl &url, int year, const QString &csv,
                       const QString &token, QString &messageOut);
};

#endif // RESULTSUPLOAD_H
