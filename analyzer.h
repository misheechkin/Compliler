#ifndef ANALYZER_H
#define ANALYZER_H

#include <QString>
#include <QVector>
#include <QString>
#include <QMap>
#include <QRegularExpression>

enum StateID {
    START,
    KEYWORD,
    OPEN_BRACKET,
    KEY_TYPE,
    COMMA,
    VALUE_TYPE,
    CLOSE_BRACKET,
    VAR_NAME,
    END,
};


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
    QVector<QString> syntax(QVector<Lexeme>& lexemes);
    static QVector<Lexeme> analyze(const QString& text);
    Analyzer() : state(START)
    {}

private:
    StateID state;
    static bool isletter(unsigned char c);
};

#endif // ANALYZER_H
