#include "analyzer.h"


bool Analyzer::isletter(unsigned char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

QVector<Analyzer::Lexeme> Analyzer::analyze(const QString& text) {
    QVector<Lexeme> lexemes;
    QString lexeme, lexeme_error;
    uint start = 0, end = 0;
    for (uint i = 0; i < text.length(); i++) {
        unsigned char c = static_cast<unsigned char>(text[i].toLatin1());
        end = i + 1;
        if(c <= 127 && (isletter(c) || isdigit(c))) {
            lexeme += text[i];
            start = (end - lexeme.length()) <= 0 ? 1 : end - lexeme.length() + 1;
            if("map" == lexeme){
                lexemes.push_back({1, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("int" == lexeme){
                lexemes.push_back({2, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("string" == lexeme){
                lexemes.push_back({3, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("float" == lexeme){
                lexemes.push_back({3, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("double" == lexeme){
                lexemes.push_back({3, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
        } else {
            if(!lexeme.isEmpty()) {
                start = i - lexeme.length() <= 0 ? 1 : end - lexeme.length();
                lexemes.push_back({6, "идентификатор", lexeme, start, i});
                lexeme.clear();
            }
            lexeme += text[i];
            switch (c) {
            case '<':
                lexemes.push_back({7, "оператор <", lexeme, end, end});
                lexeme.clear();
                break;
            case '>':
                lexemes.push_back({8, "оператор >", lexeme, end, end});
                lexeme.clear();
                break;
            case ';':
                lexemes.push_back({9, "оператор конца", lexeme, end, end});
                lexeme.clear();
                break;
            case ',':
                lexemes.push_back({10, "оператор ,", lexeme, end, end});
                lexeme.clear();
                break;
            case ' ':
                lexeme.clear();
                break;
            case '\n':
                lexeme.clear();
                break;
            case '\t':
                lexeme.clear();
                break;
            default:
                lexeme_error += lexeme;
                lexeme.clear();
                if((i + 1) < text.length() && text[i + 1].toLatin1() == 0){
                    break;
                }
                start = (end  - lexeme_error.length()) <= 0 ? 1 : end - lexeme_error.length() + 1;
                lexemes.push_back({11, "недопустимый символы", lexeme_error, start, end});
                lexeme_error.clear();
                break;
            }
        }
    }
    return lexemes;
}

