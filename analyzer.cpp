#include "analyzer.h"


bool Analyzer::isletter(unsigned char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

QVector<QString> Analyzer::syntax(QVector<Lexeme> &lexemes) {
    QVector<QString> errors;
    int len = lexemes.size();
    if(len > 8) {

    }
    int j = 0;
    for(int i = 0; i < 9; i++) {
        if(j >= len) {
            j = len - 1;
        }
        switch(state) {
        case START:
            if(lexemes[j].code != 1) {
                if(lexemes[j].code == 6) {
                    for(j++; j < len; j++) {
                        if(lexemes[j].code != 6)
                            break;
                    }
                    errors.push_back("Ожидалось ключевое слово map");
                } else {
                    errors.push_back("Отсутвует ключевое слово map");
                }
            } else {
                j++;
                if(lexemes[j].code == 6) {
                    errors.push_back("Неожиданные символы '" + lexemes[j].value + "' Ожидалось ключевое слово map");
                    j++;
                }
            }
            state = KEYWORD;
            break;
        case KEYWORD:
            if(lexemes[j].code != 7) {
                if(lexemes[j].code == 6) {
                    j++;
                }
                errors.push_back("Ошибка нет оператора '<' ");
            } else {
                j++;
            }
            state = OPEN_BRACKET;
            break;
        case OPEN_BRACKET:
            if(lexemes[j].code < 2 || lexemes[j].code > 5) {
                QString type;
                if(lexemes[j].code == 6) {
                    for(; j < len; j++) {
                        if(lexemes[j].code != 6)
                            break;
                         type += lexemes[j].value;
                    }
                    errors.push_back("Ожидалось ключевое слово типа данных " + type);
                } else {
                    errors.push_back("Отсутвует ключевом слово 'типа данных'");
                }
            } else {
                j++;
                if(lexemes[j].code == 6) {
                    errors.push_back("Неожиданные символы '" + lexemes[j].value + "' Ожидалось ключевое слово " + lexemes[j - 1].value);
                    j++;
                }
            }
            state = KEY_TYPE;
            break;
        case KEY_TYPE:
            if(lexemes[j].code != 10) {
                if(lexemes[j].code == 6) {
                    j++;
                }
                errors.push_back("Нет ,");
            } else {
                j++;
            }
            state = COMMA;
            break;
        case COMMA:
            if(lexemes[j].code < 2 || lexemes[j].code > 5) {
                QString type;
                if(lexemes[j].code == 6) {
                    for(; j < len; j++) {
                        if(lexemes[j].code != 6)
                            break;
                        type += lexemes[j].value;
                    }
                    errors.push_back("Ожидалось ключевое слово типа данных " + type);
                } else {
                    errors.push_back("Ожидалось ключевое слово типа данных");
                }
            } else {
                j++;
                if(lexemes[j].code == 6) {
                    errors.push_back("Неожиданные символы '" + lexemes[j].value + "' Ожидалось ключевое слово " + lexemes[j - 1].value);
                    j++;
                }
            }
            state = VALUE_TYPE;
            break;
        case VALUE_TYPE:
            if(lexemes[j].code != 8) {
                if(lexemes[j].code == 6) {
                    j++;
                }
                errors.push_back("Ошибка нет оператора '>' ");
            } else {
                j++;
            }
            state = CLOSE_BRACKET;
            break;
        case CLOSE_BRACKET:
            if(lexemes[j].code != 6) {
                errors.push_back("Ошибка нет индефикатора");
            } else {
                j++;
            }
            state = VAR_NAME;
            break;
        case VAR_NAME:
            if(lexemes[j].code != 9) {
                if(lexemes[j].code == 6) {
                    j++;
                }
                errors.push_back("Ошибка нет оператора конца");
            } else {
                j++;
            }
            state = END;
            break;
        case END:
            state = START;
            break;
        }
    }
    return errors;
}


QVector<Analyzer::Lexeme> Analyzer::analyze(const QString& text) {
    QVector<Lexeme> lexemes;
    QString lexeme, lexeme_error;
    uint start = 0, end = 0;
    uint i;
    for (i = 0; i < text.length(); i++) {
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
                lexemes.push_back({4, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("double" == lexeme){
                lexemes.push_back({5, "ключевое слово", lexeme, start, end});
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
                //lexemes.push_back({11, "недопустимый символы", lexeme_error, start, end});
                lexeme_error.clear();
                break;
            }
        }
    }
    if(!lexeme.isEmpty()) {
        start = i - lexeme.length() <= 0 ? 1 : end - lexeme.length();
        lexemes.push_back({6, "идентификатор", lexeme, start, i});
        lexeme.clear();
    }
    return lexemes;
}

