#ifndef UPLOADRESULTSDIALOG_H
#define UPLOADRESULTSDIALOG_H

#include <QDialog>
#include <QString>

class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;

class UploadResultsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UploadResultsDialog(const QString &csv, int rows, int missingCategories, QWidget *parent = nullptr);

private slots:
    void onUpload();

private:
    QString m_csv;
    QSpinBox *m_year;
    QLineEdit *m_endpoint;
    QLineEdit *m_token;
    QPushButton *m_send;
    QLabel *m_status;
};

#endif // UPLOADRESULTSDIALOG_H
