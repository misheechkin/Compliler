#ifndef TEXTPATTERNMATCHER_H
#define TEXTPATTERNMATCHER_H

#include <QString>
#include <QList>
#include <QRegularExpression>

class TextPatternMatcher {
public:
    struct MatchResult {
        QString type;     // Тип совпадения (год, имя, широта)
        int position;     // Позиция в тексте
        QString value;    // Найденное значение
    };

    TextPatternMatcher();
    QList<MatchResult> processText(const QString& text) const;
    QString formatResults(const QList<MatchResult>& results) const;

private:
    QList<QPair<QString, QRegularExpression>> patterns;
};

#endif // TEXTPATTERNMATCHER_H
