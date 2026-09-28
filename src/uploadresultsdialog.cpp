#include "uploadresultsdialog.h"
#include "resultsupload.h"

#include <QDate>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include <QVBoxLayout>

UploadResultsDialog::UploadResultsDialog(const QString &csv, int rows, int missingCategories, QWidget *parent)
    : QDialog(parent), m_csv(csv)
{
    setWindowTitle(tr("Odeslat výsledky na web"));
    setModal(true);
    setMinimumWidth(460);

    QSettings set(QStringLiteral("config.ini"), QSettings::IniFormat);
    set.setIniCodec("UTF-8");

    m_year = new QSpinBox(this);
    m_year->setRange(2000, 2100);
    m_year->setValue(QDate::currentDate().year());

    m_endpoint = new QLineEdit(this);
    m_endpoint->setText(set.value(QStringLiteral("upload/endpoint"),
                                  QStringLiteral("https://beh.farnostsj.cz/api/results-upload")).toString());

    m_token = new QLineEdit(this);
    m_token->setEchoMode(QLineEdit::Password);
    m_token->setText(set.value(QStringLiteral("upload/token")).toString());

    m_send = new QPushButton(tr("Odeslat"), this);
    m_send->setDefault(true);
    QPushButton *closeBtn = new QPushButton(tr("Zavřít"), this);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_send, &QPushButton::clicked, this, &UploadResultsDialog::onUpload);

    m_status = new QLabel(this);
    m_status->setWordWrap(true);

    auto *form = new QFormLayout;
    form->addRow(tr("Ročník:"), m_year);
    form->addRow(tr("Endpoint:"), m_endpoint);
    form->addRow(tr("Token:"), m_token);

    auto *buttons = new QHBoxLayout;
    buttons->addStretch(1);
    buttons->addWidget(m_send);
    buttons->addWidget(closeBtn);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(tr("Odeslat %1 výsledků vyhodnocení jako CSV na web.").arg(rows), this));
    if (missingCategories > 0) {
        QLabel *warn = new QLabel(tr("Pozor! %1 běžců nemá přiřazenou kategorii (v CSV bude None). Pravděpodobně chybí nebo je neplatný config.ini s kategoriemi.").arg(missingCategories), this);
        QPalette pal = warn->palette();
        pal.setColor(QPalette::WindowText, QColor(180, 0, 0));
        warn->setPalette(pal);
        warn->setWordWrap(true);
        layout->addWidget(warn);
    }
    layout->addLayout(form);
    layout->addWidget(m_status);
    layout->addLayout(buttons);
}

void UploadResultsDialog::onUpload()
{
    const QUrl url(m_endpoint->text().trimmed());
    const QString token = m_token->text().trimmed();
    if (!url.isValid() || token.isEmpty()) {
        m_status->setText(tr("Zkontrolujte endpoint a token."));
        return;
    }

    m_send->setEnabled(false);
    m_status->setText(tr("Odesílám…"));

    QString message;
    const bool ok = ResultsUpload::upload(url, m_year->value(), m_csv, token, message);
    m_status->setText(message);

    if (ok) {
        QSettings set(QStringLiteral("config.ini"), QSettings::IniFormat);
    set.setIniCodec("UTF-8");
        set.setValue(QStringLiteral("upload/endpoint"), m_endpoint->text().trimmed());
        set.setValue(QStringLiteral("upload/token"), token);
        m_send->setText(tr("Hotovo"));
    } else {
        m_send->setEnabled(true);
    }
}
