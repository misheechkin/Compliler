#include "analyzer.h"


bool Analyzer::isletter(unsigned char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int Analyzer::netrazilation(QVector<Lexeme> &lexemes,int j, int code, int nextcode, QVector<QString> &errors){
    while(j < lexemes.size()){
        if(lexemes[j].code == 6 && code != 6) {
            errors.push_back("Неверные символы " + lexemes[j].value);
        } else {
            return j;
        }
        j++;
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
                int size_errors = errors.size();
                j = netrazilation(lexemes, j, 1, 7, errors);
                if(lexemes[j].code == 1) {
                    j++;
                }
                if(errors.size() == size_errors) {
                    errors.push_back("Пропущенно map");
                }
            } else {
                j++;
            }
            state = KEYWORD;
            break;
        case KEYWORD:
            if(lexemes[j].code != 7) {
                int size_errors = errors.size();
                j = netrazilation(lexemes, j, 7, 3, errors);
                if(lexemes[j].code == 7) {
                    j++;
                }
                if(errors.size() == size_errors) {
                    errors.push_back("Пропущенно <");
                }
            } else {
                j++;
            }
            state = OPEN_BRACKET;
            break;
        case OPEN_BRACKET:
            if(lexemes[j].code < 2 || lexemes[j].code > 5) {
                int size_errors = errors.size();
                j = netrazilation(lexemes, j, 2, 10, errors);
                if(lexemes[j].code == 2 || lexemes[j].code == 3 || lexemes[j].code == 4
                    || lexemes[j].code == 5 ) {
                    j++;
                }
                if(errors.size() == size_errors) {
                    errors.push_back("Пропущен тип данных");
                }
            } else {
                j++;
            }
            state = KEY_TYPE;
            break;
        case KEY_TYPE:
            if(lexemes[j].code != 10) {
                int size_errors = errors.size();
                j = netrazilation(lexemes, j, 10, 2, errors);
                if(lexemes[j].code == 10) {
                    j++;
                }
                if(errors.size() == size_errors) {
                    errors.push_back("Пропущена ,");
                }
            } else {
                j++;
            }
            state = COMMA;
            break;
        case COMMA:
            if(lexemes[j].code < 2 || lexemes[j].code > 5) {
                int size_errors = errors.size();
                j = netrazilation(lexemes, j, 2, 8, errors);
                if(lexemes[j].code == 2 || lexemes[j].code == 3 || lexemes[j].code == 4
                    || lexemes[j].code == 5 ) {
                    j++;
                }
                if(errors.size() == size_errors) {
                    errors.push_back("Пропущен тип данных");
                }
            } else {
                j++;
            }
            state = VALUE_TYPE;
            break;
        case VALUE_TYPE:
            if(lexemes[j].code != 8) {
                int size_errors = errors.size();
                j = netrazilation(lexemes, j, 8, 6, errors);
                if(lexemes[j].code == 8) {
                    j++;
                }
                if(errors.size() == size_errors) {
                    errors.push_back("Пропущена >");
                }
            } else {
                j++;
            }
            state = CLOSE_BRACKET;
            break;
        case CLOSE_BRACKET:
            if(lexemes[j].code != 6) {

            } else {
                j++;
            }
            state = VAR_NAME;
            break;
        case VAR_NAME:
            if(lexemes[j].code != 9) {

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
                        continue;
                    }
                }
                lexemes.push_back({1, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("int" == lexeme && (h == '>' || h == ',' || h == ' ')) {
                foreach (Lexeme lex, lexemes) {
                    if(lex.value == lexeme){
                        lexemes.push_back({6, "идентификатор", lexeme, start, i});
                        lexeme.clear();
                        continue;
                    }
                }
                lexemes.push_back({2, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("string" == lexeme && (h == '>' || h == ',' || h == ' ')){
                foreach (Lexeme lex, lexemes) {
                    if(lex.value == lexeme){
                        lexemes.push_back({6, "идентификатор", lexeme, start, i});
                        lexeme.clear();
                        continue;
                    }
                }
                lexemes.push_back({3, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("float" == lexeme && (h == '>' || h == ',' ||  h == ' ')){
                foreach (Lexeme lex, lexemes) {
                    if(lex.value == lexeme){
                        lexemes.push_back({6, "идентификатор", lexeme, start, i});
                        lexeme.clear();
                        continue;
                    }
                }
                lexemes.push_back({4, "ключевое слово", lexeme, start, end});
                lexeme.clear();
            }
            else if("double" == lexeme && (h == '>' || h == ',' || h == ' ')){
                foreach (Lexeme lex, lexemes) {
                    if(lex.value == lexeme){
                        lexemes.push_back({6, "идентификатор", lexeme, start, i});
                        lexeme.clear();
                        continue;
                    }
                }
                lexemes.push_back({5, "ключевое слово", lexeme, start, end});
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
