#ifndef ANALYZER_H
#define ANALYZER_H

#include <QString>
#include <QVector>
#include <QString>
#include <QMap>
#include <QRegularExpression>

class Analyzer
{
public:

    struct Lexeme {
        int code;
        QString type;
        QString value;
        long unsigned startPos;
        long unsigned endPos;

    };

    static QVector<Lexeme> analyze(const QString& text);
    Analyzer() {}

private:
    static bool isletter(unsigned char c);
};

#endif // ANALYZER_H
