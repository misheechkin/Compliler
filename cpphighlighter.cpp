#include "cpphighlighter.h"

CppHighlighter::CppHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
    // Формат для ключевых слов
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\breturn\\b"
                    << "\\bif\\b" << "\\belse\\b" << "\\bfor\\b" << "\\bwhile\\b"
                    << "\\bdo\\b" << "\\bswitch\\b" << "\\bcase\\b" << "\\bbreak\\b"
                    << "\\bcontinue\\b" << "\\bgoto\\b" << "\\btrue\\b" << "\\bfalse\\b";

    // Добавляем контейнеры STL
    keywordPatterns << "\\bmap\\b" << "\\bunordered_map\\b" << "\\bvector\\b"
                    << "\\bset\\b" << "\\bunordered_set\\b" << "\\blist\\b"
                    << "\\bdeque\\b" << "\\bqueue\\b" << "\\bstack\\b"
                    << "\\bpriority_queue\\b" << "\\barray\\b" << "\\bstring\\b";

    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Формат для классов
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    HighlightingRule classRule;
    classRule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    classRule.format = classFormat;
    highlightingRules.append(classRule);

    // Формат для функций
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    HighlightingRule functionRule;
    functionRule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    functionRule.format = functionFormat;
    highlightingRules.append(functionRule);

    // Формат для однострочных комментариев
    singleLineCommentFormat.setForeground(Qt::red);
    HighlightingRule singleLineCommentRule;
    singleLineCommentRule.pattern = QRegularExpression("//[^\n]*");
    singleLineCommentRule.format = singleLineCommentFormat;
    highlightingRules.append(singleLineCommentRule);

    // Формат для многострочных комментариев
    multiLineCommentFormat.setForeground(Qt::red);
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");

    // Формат для строк
    quotationFormat.setForeground(Qt::darkGreen);
    HighlightingRule quotationRule;
    quotationRule.pattern = QRegularExpression("\".*\"");
    quotationRule.format = quotationFormat;
    highlightingRules.append(quotationRule);

    // Формат для чисел (десятичные, шестнадцатеричные, восьмеричные, вещественные)
    numberFormat.setForeground(Qt::darkCyan);
    HighlightingRule numberRule;
    numberRule.pattern = QRegularExpression("\\b\\d+(\\.\\d+)?([eE][+-]?\\d+)?\\b|\\b0[xX][0-9a-fA-F]+\\b|\\b0[0-7]+\\b");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);

    // Формат для директив препроцессора и макросов
    preprocessorFormat.setForeground(Qt::darkYellow);
    HighlightingRule preprocessorRule;
    preprocessorRule.pattern = QRegularExpression("#[a-zA-Z]+");
    preprocessorRule.format = preprocessorFormat;
    highlightingRules.append(preprocessorRule);
}

void CppHighlighter::highlightBlock(const QString &text) {
    // Применяем правила подсветки
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // Подсветка многострочных комментариев
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;

        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + match.capturedLength();
        }

        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
