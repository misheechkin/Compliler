#include "analyzer.h"


bool Analyzer::isletter(unsigned char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int Analyzer::netrazilation(QVector<Lexeme> &lexemes, int &j, int code, int nextcode, QVector<QString> &errors) {
    while(j < lexemes.size()) {
        if(lexemes[j].code == code) {
            return 1;
        } else if(lexemes[j].code == 6 && !nextcode) {
            switch (code) {
            case 1:
                errors.push_back("Ошибка! Отсутствует map");
                break;
            case 2:
                errors.push_back("Ошибка! Отсутствует тип данных ключа");
                break;
            case 3:
                errors.push_back("Ошибка! Отсутствует тип данных значения");
                break;
            case 7:
                errors.push_back("Ошибка! Отсутствует <");
                break;
            case 8:
                errors.push_back("Ошибка! Отсутствует >");
                break;
            case 9:
                errors.push_back("Ошибка! Отсутствует ;");
                break;
            case 10:
                errors.push_back("Ошибка! Отсутствует ,");
                break;
            }
            j++;
            continue;
        }
        break;
    }
    return 0;
}


QVector<QString> Analyzer::syntax(QVector<Lexeme> &lexemes) {
    QVector<QString> errors;
    int len = lexemes.size();
    int j = 0;
    for(int i = 0; i < 9; i++) {
        if(j >= len) {
            j = len - 1;
        }
        switch(state) {
        case START:
            if(lexemes[j].code != 1) {
                int end = j;
                int size = errors.size();
                int flag = netrazilation(lexemes, j, 1, 0, errors);
                if(lexemes[j].code != 7 && !flag) {
                    for(int temp = errors.size();size != temp; temp--){
                        errors.pop_back();
                        break;
                    }
                    j -= 1;
                }
                if(flag) {
                    j++;
                } else  {
                    if(errors.size() == size)
                    errors.push_back("Ошибка! Отсутствует ключевое слово map");
                }
            } else {
                j++;
            }
            state = KEYWORD;
            break;
        case KEYWORD:
            if(lexemes[j].code != 7) {
                int end = j;
                int size = errors.size();
                int flag = netrazilation(lexemes, j, 7, 0, errors);
                if(lexemes[j].code != 2 && !flag) {
                      for(int temp = errors.size();size != temp; temp--){
                          errors.pop_back();
                      }
                      j = end;
                }
                if(flag) {
                    j++;
                } else {
                     if(errors.size() == size)
                    errors.push_back("Ошибка! Отсутствует <");
                }
            } else {
                j++;
            }
            state = OPEN_BRACKET;
            break;
        case OPEN_BRACKET:
            if(lexemes[j].code != 2) {
                int end = j;
                int size = errors.size();
                int flag = netrazilation(lexemes, j, 2, 0, errors);
                if(lexemes[j].code != 10 && !flag) {
                    for(int temp = errors.size();size != temp; temp--){
                        errors.pop_back();
                    }
                    j = end;
                }
                if(flag) {
                    j++;
                } else {
                    if(errors.size() == size)
                        errors.push_back("Ошибка! Отсутствует тип ключа");
                }
            } else {
                j++;
            }
            state = KEY_TYPE;
            break;
        case KEY_TYPE:
            if(lexemes[j].code != 10) {
                int end = j;
                int size = errors.size();
                int flag = netrazilation(lexemes, j, 10, 0, errors);
                if(lexemes[j].code != 3 && !flag) {
                    for(int temp = errors.size();size != temp; temp--){
                        errors.pop_back();
                    }
                    j = end;
                }
                if(flag) {
                    j++;
                } else {
                    if(errors.size() == size)
                        errors.push_back("Ошибка! Отсутствует запятая");
                }
            } else {
                j++;
            }
            state = COMMA;
            break;
        case COMMA:
            if(lexemes[j].code != 3) {
                int end = j;
                int size = errors.size();
                int flag = netrazilation(lexemes, j, 3, 0, errors);
                if(lexemes[j].code != 8 && !flag) {
                    for(int temp = errors.size();size != temp; temp--){
                        errors.pop_back();
                    }
                    j = end;
                }
                if(flag) {
                    j++;
                } else {
                    if(errors.size() == size)
                        errors.push_back("Ошибка! Отсутствует тип значения");
                }
            } else {
                j++;
            }
            state = VALUE_TYPE;
            break;
        case VALUE_TYPE:
            if(lexemes[j].code != 8) {
                int end = j;
                int size = errors.size();
                int flag = netrazilation(lexemes, j, 8, 1, errors);
                if(lexemes[j].code != 6 && !flag) {
                    for(int temp = errors.size();size != temp; temp--){
                        errors.pop_back();
                    }
                    j = end;
                }
                if(flag) {
                    j++;
                } else {
                    if(errors.size() == size)
                        errors.push_back("Ошибка! Отсутствует >");
                }
            } else {
                j++;
            }
            state = CLOSE_BRACKET;
            break;
        case CLOSE_BRACKET:
            if(lexemes[j].code != 6) {
                int end = j;
                int size = errors.size();
                int flag = netrazilation(lexemes, j, 6, 1, errors);
                if(lexemes[j].code != 9 && !flag) {
                    for(int temp = errors.size();size != temp; temp--){
                        errors.pop_back();
                    }
                    j = end;
                }
                if(flag) {
                    j++;
                } else {
                    if(errors.size() == size)
                        errors.push_back("Ошибка! Отсутствует индефикатор");
                }
            } else {
                j++;
            }
            state = VAR_NAME;
            break;
        case VAR_NAME:
            if(lexemes[j].code != 9) {
                errors.push_back("Ошибка! Отсутствует ;");
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
    unsigned char h;
    int flag = 0;
    for (i = 0; i < text.length(); i++) {
        unsigned char c = static_cast<unsigned char>(text[i].toLatin1());
        end = i + 1;
        if(end < text.length())
            h = static_cast<unsigned char>(text[end].toLatin1());
        if(c <= 127 && (isletter(c) || isdigit(c))) {
            lexeme += text[i];
            start = (end - lexeme.length()) <= 0 ? 1 : end - lexeme.length() + 1;
            if("map" == lexeme && (h == '<' || h == ' ')){
                foreach (Lexeme lex, lexemes) {
                    if(lex.value == lexeme){
                        lexemes.push_back({6, "идентификатор", lexeme, start, i});
                        lexeme.clear();
                        flag = 1;
                        break;
                    }
                }
                if(flag){
                    flag = 0;
                    continue;
                }
                lexemes.push_back({1, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("int" == lexeme && (h == '>' || h == ',' || h == ' ')) {
                foreach (Lexeme lex, lexemes) {
                    if(lex.code == 2 || lex.code == 10) {
                        lexemes.push_back({3, "идентификатор", lexeme, start, i});
                        lexeme.clear();
                        flag = 1;
                        break;
                    }
                }
                if(flag){
                    flag = 0;
                    continue;
                }
                lexemes.push_back({2, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("string" == lexeme && (h == '>' || h == ',' || h == ' ')){
                foreach (Lexeme lex, lexemes) {
                    if(lex.code == 2 || lex.code == 10) {
                        lexemes.push_back({3, "идентификатор", lexeme, start, i});
                        lexeme.clear();
                        flag = 1;
                        break;
                    }
                }
                if(flag){
                    flag = 0;
                    continue;
                }
                lexemes.push_back({2, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("float" == lexeme && (h == '>' || h == ',' ||  h == ' ')){
                foreach (Lexeme lex, lexemes) {
                    if(lex.code == 2 || lex.code == 10) {
                        lexemes.push_back({3, "идентификатор", lexeme, start, i});
                        lexeme.clear();
                        flag = 1;
                        break;
                    }
                }
                if(flag){
                    flag = 0;
                    continue;
                }
                lexemes.push_back({2, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("double" == lexeme && (h == '>' || h == ',' || h == ' ')){
                foreach (Lexeme lex, lexemes) {
                    if(lex.code == 2 || lex.code == 10) {
                        lexemes.push_back({3, "идентификатор", lexeme, start, i});
                        lexeme.clear();
                        flag = 1;
                        break;
                    }
                }
                if(flag){
                    flag = 0;
                    continue;
                }
                lexemes.push_back({2, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
        } else {
            if(!lexeme.isEmpty() && (text[i] == '<' || text[i] == '>' ||  text[i] == ';' ||  text[i] == ',' ||
                                      text[i] == ' ' ||  text[i] == '\n' ||  text[i] == '\t')) {
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
