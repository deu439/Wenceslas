#include "resultsupload.h"

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

QString ResultsUpload::buildCsv(const QList<Row> &rows)
{
    QStringList out;
    out << QStringLiteral("name,time,runningNumber,category");
    for (const Row &row : rows) {
        const QString name = QString(row.name).replace(QLatin1Char(','), QLatin1Char(' '));
        const QString category = QString(row.category).replace(QLatin1Char(','), QLatin1Char(' '));
        const unsigned mins = row.ms / 60000;
        const unsigned secRest = row.ms - mins * 60000;
        QString time = QString::asprintf("%u:%02u.%02u", mins, secRest / 1000, (secRest % 1000) / 10);
        out << QStringLiteral("%1,%2,%3,%4")
                   .arg(name, time)
                   .arg(row.number)
                   .arg(category);
    }
    return out.join(QLatin1Char('\n')) + QLatin1Char('\n');
}

bool ResultsUpload::upload(const QUrl &url, int year, const QString &csv,
                           const QString &token, QString &messageOut)
{
    QJsonObject body;
    body[QStringLiteral("year")] = year;
    body[QStringLiteral("csv")] = csv;

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    request.setRawHeader("Authorization",
                         "Bearer " + token.toUtf8());

    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.post(request, QJsonDocument(body).toJson(QJsonDocument::Compact));

    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);
    QObject::connect(&timer, &QTimer::timeout, reply, &QNetworkReply::abort);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start(15000);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        messageOut = QStringLiteral("Síťová chyba: %1").arg(reply->errorString());
        return false;
    }

    const QByteArray raw = reply->readAll();
    const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    const QJsonDocument doc = QJsonDocument::fromJson(raw);
    if (!doc.isObject()) {
        messageOut = QStringLiteral("Neplatná odpověď serveru (HTTP %1)").arg(status);
        return false;
    }

    const QJsonObject json = doc.object();
    if (json.value(QStringLiteral("success")).toBool()) {
        const int rows = json.value(QStringLiteral("rows")).toInt();
        const int y = json.value(QStringLiteral("year")).toInt();
        messageOut = QStringLiteral("Nahráno: %1 výsledků za ročník %2. Stránka se přegeneruje za 1–2 minuty.")
                         .arg(rows)
                         .arg(y);
        return true;
    }

    messageOut = QStringLiteral("HTTP %1: %2")
                     .arg(status)
                     .arg(json.value(QStringLiteral("error")).toString(QStringLiteral("neznámá chyba")));
    return false;
}
