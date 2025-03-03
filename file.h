#ifndef FILE_H
#define FILE_H

#include <memory>
#include <QFile>
#include <QString>

class File
{
public:
    File() = default;
    ~File();
    bool open(QString filename);
    QString get_text();
    bool save(QString text);
    bool saveAs(QString text, QString filename);
private:
    void close();
    std::unique_ptr<QFile> file;
    QString filename;
};

#endif // FILE_H
