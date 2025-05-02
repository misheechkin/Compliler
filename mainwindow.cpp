#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
    highlighter = std::make_unique<CppHighlighter>(ui->plainTextEdit->document());
    connect(ui->plainTextEdit,&QPlainTextEdit::textChanged,this,&MainWindow::documentModified);
    is_modified = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (is_modified) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Документ изменен", "Хотите сохранить изменения?",
                                    QMessageBox::Discard  | QMessageBox::Save  | QMessageBox::Cancel);
        if (reply == QMessageBox::Save) {
            on_menuSaveFIleIn_triggered();
            event->accept();
        } else if (reply == QMessageBox::Discard) {
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}


void MainWindow::on_menuCreateFile_triggered()
{
    ui->plainTextEdit->setReadOnly(false);
    ui->plainTextEdit->clear();
}


void MainWindow::on_menuOpenFile_triggered()
{
    ui->plainTextEdit->clear();
    if(!file.open(QFileDialog::getOpenFileName(nullptr, "Открыть файл", "/home", "Все файлы (*);;Текстовые файлы (*.txt)"))) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        ui->plainTextEdit->setReadOnly(true);
        return;
    }
    ui->plainTextEdit->setPlainText(file.get_text());
    if(ui->plainTextEdit->isReadOnly()) {
        ui->plainTextEdit->setReadOnly(false);
    }
}


void MainWindow::on_menuSaveFile_triggered()
{
    if(file.save(ui->plainTextEdit->toPlainText())) {
        QMessageBox::information(this,"Информация","Сохранение успешно");
        is_modified = false;
        return;
    }
    QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл (нужно выполнить сохранить как)");
}


void MainWindow::on_menuSaveFIleIn_triggered()
{
    if(file.saveAs(ui->plainTextEdit->toPlainText(),
                    QFileDialog::getSaveFileName(nullptr, "Сохранить как", "/home", "Все файлы (*);;Текстовые файлы (*.txt)"))) {
        QMessageBox::information(this,"Информация","Сохранение успешно");
        is_modified = false;
        return;
    }
    QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
}


void MainWindow::on_menuRepeat_triggered()
{
    ui->plainTextEdit->redo();
}


void MainWindow::on_menuCancel_triggered()
{
    ui->plainTextEdit->undo();
}


void MainWindow::on_menuQuit_triggered()
{
    MainWindow::close();
}


void MainWindow::on_menuCopy_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_menuCut_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_menuInsert_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_menuDelete_triggered()
{
    ui->plainTextEdit->textCursor().removeSelectedText();
}


void MainWindow::on_menuSelect_triggered()
{
    ui->plainTextEdit->selectAll();
}


void MainWindow::on_action_22_triggered()
{
    QMessageBox::information(this, "О программе", "Выпонил студент НГТУ \n Мишечкин Никита Евгеньвич \n группы АВТ - 214");
}


void MainWindow::on_action_21_triggered()
{
    QMessageBox::information(this,"Справка", "Инструкция по работе с программой "
"\n\nДля создания нового документа нажмите 'Создать' в меню 'Файл'\n\n"
"Для открытия существующего документа выберите 'Открыть'\n\n"
"Используйте 'Сохранить' для сохранения изменений \n\n"
"Для редактирования текста используйте функции 'Вырезать', 'Копировать', 'Вставить' и 'Удалить'\n\n"
"Вы можете отменить или повторить действия с помощью 'Отменить' и 'Повторить'\n\n"
"Для получения справки нажмите 'Справка' в меню\n");
}

void MainWindow::documentModified()
{
    is_modified = true;
}


void MainWindow::on_toolbarStart_triggered()
{
    QString input = ui->plainTextEdit->toPlainText().replace(" ", "");
    ui->textBrowser->clear();

    if (analyzer.analyze(input)) {
        ui->textBrowser->setText(
            "ПОЛИЗ: " + analyzer.getPoliz().join(" ") +
            "\nРезультат: " + QString::number(analyzer.getResult())
            );
    } else {
        ui->textBrowser->setText(analyzer.getErrors().join("\n"));
    }

}

