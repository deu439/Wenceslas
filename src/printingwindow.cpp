// SPDX-FileCopyrightText: 2026 Jan Dorazil <xdoraz04@stud.feec.vutbr.cz>
// SPDX-License-Identifier: Apache-2.0

#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QStringBuilder>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <poppler-form.h>

#include "printingwindow.h"
#include "ui_printingwindow.h"

PrintingWindow::PrintingWindow(const QList<QMap<QString, QString>> &fieldValues, QWidget* parent, int printResolution) :
    QWidget(parent),
    ui(new Ui::PrintingWindow),
    values(new QList<QMap<QString, QString>>(fieldValues)),
    doc(nullptr),
    resolution(printResolution)
{
    ui->setupUi(this);
    
    connect(ui->current, QOverload<int>::of(&QSpinBox::valueChanged), this, &PrintingWindow::changed);
    connect(ui->print, &QPushButton::clicked, this, &PrintingWindow::print);
    connect(ui->chooseTemplate, &QPushButton::clicked, this, &PrintingWindow::chooseTemplate);
    connect(ui->cancel, &QPushButton::clicked, this, &PrintingWindow::close);
    
    // Load the last used template, if any
    QSettings set("config.ini", QSettings::IniFormat);
    set.setIniCodec("UTF-8");
    QString path = set.value("settings/print_template").toString();
    if (!path.isEmpty() && !loadTemplate(path)) {
        qDebug() << "Unable to load the saved template " << path;
    }
}

PrintingWindow::~PrintingWindow() noexcept
{
    delete doc;
    delete values;
    delete ui;
}

void PrintingWindow::showEvent(QShowEvent* ev)
{
    QWidget::showEvent(ev);
    renderPreview(0);
    ui->total->setText("/ " % QString::number(values->length()));
    ui->current->setMaximum(values->length());
}

void PrintingWindow::fillForms(Poppler::Page* page, const QMap<QString, QString>& map)
{
    // Fill text fields
    QList<Poppler::FormField*> fields = page->formFields();
    for (Poppler::FormField *field : fields) {
        // Check if it's a text field and edit it
        if (field->type() == Poppler::FormField::FormText) {
            Poppler::FormFieldText *textField = static_cast<Poppler::FormFieldText*>(field);
            
            QString fieldName = textField->name();
            if (map.contains(fieldName)) {
                textField->setText(map[fieldName]);
            } else {
                qDebug() << "renderPreview(): Unknown field name " << fieldName << Qt::endl;
            }
        }
    }
}


void PrintingWindow::renderPreview(int index)
{
    if (doc == nullptr) return;
    
    if (index < 0 || index >= values->length()) {
        qDebug() << "renderPreview() Index out of bounds!" << Qt::endl;
        return;
    }
    
    // Fetch the record
    QMap<QString, QString> map = values->at(index);
    
    // Extract and fill first page
    Poppler::Page *page = doc->page(0);
    fillForms(page, map);
    
    // Render to image
    QImage img = page->renderToImage(resolution, resolution);
    if (!img.isNull()) {
        ui->preview->setPixmap(QPixmap::fromImage(img).scaled(ui->preview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    
    delete page;
}

void PrintingWindow::changed(int index)
{
    renderPreview(index-1);
}

bool PrintingWindow::loadTemplate(const QString &path)
{
    Poppler::Document *newDoc = Poppler::Document::load(path);
    if (newDoc == nullptr || newDoc->isLocked() || newDoc->numPages() < 1) {
        delete newDoc;
        return false;
    }
    
    delete doc;
    doc = newDoc;
    ui->templatePath->setText(path);
    ui->print->setEnabled(true);
    renderPreview(ui->current->value() - 1);
    return true;
}

void PrintingWindow::chooseTemplate()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Vyberte PDF šablonu..."),
                                                ui->templatePath->text(), tr("PDF dokument (*.pdf)"));
    
    // No file choosen
    if (path.isEmpty()) return;
    
    if (!loadTemplate(path)) {
        QString text = tr("Nepodařilo se načíst šablonu %1.").arg(path);
        QMessageBox::warning(this, tr("Chyba"), text);
        return;
    }
    
    // Remember the template for next time
    QSettings set("config.ini", QSettings::IniFormat);
    set.setIniCodec("UTF-8");
    set.setValue("settings/print_template", path);
}

void PrintingWindow::print()
{
    if (doc == nullptr) return;
    
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Rejected) return;

    QPainter painter;
    
    if (!painter.begin(&printer)) {
        QMessageBox::critical(this, "Error", "Could not start the print job.");
        return;
    }
    
    // Extract first page
    Poppler::Page *page = doc->page(0);
    
    // Iterate through records
    bool firstRecord = true;
    for (QMap<QString, QString> map : *values) {
        // Feed a new paper
        if (!firstRecord) {
            printer.newPage();
        }
        firstRecord = false;
        
        fillForms(page, map);
        
        // Render at the printer's native resolution for best quality
        QImage img = page->renderToImage(resolution, resolution);
                
        // Draw the image onto the current physical page
        painter.drawImage(printer.paperRect(), img);
    }
    
    painter.end();
    delete page;
}


