#include <QTextStream>
#include "file.h"
#include <QDebug>


bool File::open(QString filename) {
    if(filename.isEmpty()) {
        return false;
    }
    this->filename = filename;
    file = std::make_unique<QFile>(filename);
    return file->open(QFile::ReadOnly | QFile::Text);
}

void File::close() {
    if(file){
        file->close();
    }
}

bool File::save(QString text) {
    if(!file) {
        return false;
    }
    file->open(QFile::WriteOnly | QFile::Text);
    QTextStream out(file.get());
    out << text;
    close();
    return true;
}

bool File::saveAs(QString text, QString filename) {
    if(filename.isEmpty()) {
        return false;
    }
    file = std::make_unique<QFile>(filename);
    file->open(QFile::WriteOnly | QFile::Text);
    QTextStream out(file.get());
    out << text;
    close();
    return true;
}

File::~File(){
    close();
}

QString File::get_text(){
    QTextStream in(file.get());
    QString string = in.readAll();
    close();
    return string;
}
