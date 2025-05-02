// analyzer.cpp
#include "analyzer.h"
#include <QRegularExpression>

Analyzer::Analyzer(QObject *parent) : QObject(parent), currentPos(0), result(0) {}

bool Analyzer::analyze(const QString& input) {
    tokens.clear();
    poliz.clear();
    errors.clear();
    currentPos = 0;
    result = 0;

    tokenize(input);
    if (!errors.isEmpty()) return false;


    if (!parseExpression() || currentPos != tokens.size()) {
        if (errors.isEmpty()) errors << "Синтаксическая ошибка";
        return false;
    }


    evaluatePOLIZ();
    return true;
}

void Analyzer::tokenize(const QString& input) {
    int pos = 0;
    while (pos < input.length()) {
        QChar c = input[pos];
        if (c.isDigit() || c == '.') {
            QString num;
            while (pos < input.length() && (input[pos].isDigit() || input[pos] == '.')) {
                num += input[pos];
                pos++;
            }
            tokens.append({Token::Number, num, pos});
            continue;
        }

        Token::Type type = Token::Invalid;
        switch (c.toLatin1()) {
        case '+': type = Token::Plus; break;
        case '-': type = Token::Minus; break;
        case '*': type = Token::Multiply; break;
        case '/': type = Token::Divide; break;
        case '(': type = Token::LParen; break;
        case ')': type = Token::RParen; break;
        }

        if (type != Token::Invalid) {
            tokens.append({type, QString(c), pos});
            pos++;
        } else {
            errors << QString("Неизвестный символ '%1' на позиции %2").arg(c).arg(pos);
            pos++;
        }
    }
}


bool Analyzer::parseExpression() {
    return parseT() && parseA();
}
bool Analyzer::parseA() {
    if (currentPos >= tokens.size()) return true;

    Token t = tokens[currentPos];
    if (t.type == Token::Plus || t.type == Token::Minus) {
        currentPos++;
        if (!parseT()) {
            errors.append("Ожидалось выражение после оператора на позиции " + QString::number(t.position));
            return false;
        }
        poliz.append(t.value);
        return parseA();
    }
    return true;
}
bool Analyzer::parseT() {
    return parseO() && parseB();
}
bool Analyzer::parseB() {
    if (currentPos >= tokens.size()) return true;

    Token t = tokens[currentPos];
    if (t.type == Token::Multiply || t.type == Token::Divide) {
        currentPos++;
        if (!parseO()) {
            errors.append("Ожидалось выражение после оператора на позиции " + QString::number(t.position));
            return false;
        }
        poliz.append(t.value);
        return parseB();
    }
    return true;
}

bool Analyzer::parseO() {
    if (currentPos >= tokens.size()) {
        errors << "Ожидалось число или скобка";
        return false;
    }

    Token t = tokens[currentPos];
    if (t.type == Token::Number) {
        poliz.append(t.value);
        currentPos++;

        if (currentPos < tokens.size()) {
            Token next = tokens[currentPos];
            if (next.type == Token::Number || next.type == Token::LParen) {
                errors << QString("Пропущен оператор между '%1' и '%2' на позиции %3")
                              .arg(t.value, next.value).arg(next.position);
                return false;
            }
        }
        return true;
    } else if (t.type == Token::LParen) {
        currentPos++;
        if (!parseExpression()) return false;
        if (currentPos >= tokens.size() || tokens[currentPos].type != Token::RParen) {
            errors << QString("Ожидалась закрывающая скобка на позиции %1").arg(t.position);
            return false;
        }
        currentPos++;
        return true;
    }
    errors << QString("Ожидалось число или скобка на позиции %1").arg(t.position);
    return false;
}

void Analyzer::evaluatePOLIZ() {
    QStack<double> stack;
    for (const QString& token : poliz) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) {
                result = 0;
                return;
            }
            double b = stack.pop();
            double a = stack.pop();
            if (token == "+") stack.push(a + b);
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else if (token == "/") stack.push(a / b);
        } else {
            bool ok;
            double num = token.toDouble(&ok);
            if (ok) stack.push(num);
        }
    }
    result = stack.isEmpty() ? 0 : stack.top();
}
