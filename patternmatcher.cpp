#include "patternmatcher.h"
#include <algorithm>

TextPatternMatcher::TextPatternMatcher() {
    patterns = {
        //{"Год", QRegularExpression(R"(201[1-8])")},
        {"Имя", QRegularExpression(R"(@[A-Za-z0-9]{2,14})")},
        //{"Широта", QRegularExpression(R"(-?(90(\.0+)?|([1-8][0-9]|[0-9])(\.\d+)?))")}
    };

    for (auto& pattern : patterns) {
        if (!pattern.second.isValid()) {
            qWarning("Ошибка в регулярном выражении '%s': %s",
                     qUtf8Printable(pattern.first),
                     qUtf8Printable(pattern.second.errorString()));
        }
    }
}

QList<TextPatternMatcher::MatchResult> TextPatternMatcher::processText(const QString& text) const {
    QList<MatchResult> results;

    for (const auto& pattern : patterns) {
        QRegularExpressionMatchIterator iter = pattern.second.globalMatch(text);
        while (iter.hasNext()) {
            QRegularExpressionMatch match = iter.next();
            results.append({pattern.first, match.capturedStart(), match.captured()});
        }
    }

    std::sort(results.begin(), results.end(), [](const MatchResult& a, const MatchResult& b) {
        return a.position < b.position;
    });

    return results;
}

QString TextPatternMatcher::formatResults(const QList<MatchResult>& results) const {
    QString output;
    for (const auto& result : results) {
        output += QString("%1: Позиция %2 — %3<br>")
                      .arg(result.type)
                      .arg(result.position)
                      .arg(result.value.toHtmlEscaped());
    }
    return output;
}
