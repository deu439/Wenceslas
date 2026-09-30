// SPDX-FileCopyrightText: 2026 Jan Dorazil <xdoraz04@stud.feec.vutbr.cz>
// SPDX-License-Identifier: Apache-2.0

#ifndef PRINTINGWINDOW_H
#define PRINTINGWINDOW_H

#include <QWidget>
#include <QString>
#include <poppler-qt5.h>

namespace Ui
{
    class PrintingWindow;
}

/**
 * @todo write docs
 */
class PrintingWindow : public QWidget
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    PrintingWindow(const QList< QMap< QString, QString > >& fieldValues, QWidget* parent = nullptr, int printResolution = 300);
    
    /**
     * Destructor
     */
    ~PrintingWindow();
    
    void showEvent(QShowEvent *ev);
    
private:
    void fillForms(Poppler::Page *page, const QMap<QString, QString> &map);
    void renderPreview(int index);
    bool loadTemplate(const QString &path);
    
    Ui::PrintingWindow *ui;
    QList<QMap<QString, QString>> *values;
    Poppler::Document *doc;
    int resolution;
    
private slots:
    void changed(int index);
    void chooseTemplate();
    void print();
};

#endif // PRINTINGWINDOW_H
