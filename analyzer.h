// analyzer.h
#ifndef ANALYZER_H
#define ANALYZER_H

#include <QObject>
#include <QVector>
#include <QStack>

class Analyzer : public QObject {
    Q_OBJECT
public:
    struct Token {
        enum Type { Number, Plus, Minus, Multiply, Divide, LParen, RParen, Invalid };
        Type type;
        QString value;
        int position;
    };

    explicit Analyzer(QObject *parent = nullptr);

    bool analyze(const QString& input);
    const QStringList& getPoliz() const { return poliz; }
    double getResult() const { return result; }
    const QStringList& getErrors() const { return errors; }

private:
    QVector<Token> tokens;
    QStringList poliz;
    QStringList errors;
    double result;
    int currentPos;

    void tokenize(const QString& input);
    bool parseExpression();
    bool parseA();
    bool parseT();
    bool parseB();
    bool parseO();
    void evaluatePOLIZ();
};

#endif // ANALYZER_H
