#include "lexical_analyser.h"

/**
 * contructor
 */
LexicalAnalyser::LexicalAnalyser(): process(true) { }


/**
 * utilities
 */

void LexicalAnalyser::extract() {
    if (process) tk = src.get();
    if (isdigit(tk)) {
        string val = string(1, tk);
        while (isdigit(tk = src.get())) {
            val.push_back(tk);
        }
        process = false;
        result.push_back(val);
    }
    else if (isalpha(tk)) {
        string var = string(1, tk);
        while (isalpha(tk = src.get())) {
            var.push_back(tk);
        }
        process = false;
        result.push_back(var);
    }
    if (symbols.count(tk)) {
        string sym = string(1, tk);
        int ptk = tk;
        while (isspace(tk = src.get()));
        if (symbols.count(tk)) {
            if ( (ptk == '>' && tk == '>')
              || (ptk == '(' && tk == ')')
              || (ptk == '{' && tk == '}')
              || (ptk == '[' && tk == ']')) {
                sym.push_back(tk);
            }
            process = true;
        }
        else {
            process = false;
        }
        result.push_back(sym);
    }
    if (isspace(tk)) {
        process = true;
    }
}



/**
 * exposed interface
 */

void LexicalAnalyser::open_src(const char *from) {
    src.open(from, ios::in);
    if (!src.is_open()) {
         printf("open source file %s failed\n", from);
         exit(-1);
    }
}

void LexicalAnalyser::extract_all() {
    while (!src.eof()) {
        extract();
    }
    src.close();
}

void LexicalAnalyser::print_result(ostream &out) {
    for (vector<string>::iterator it = result.begin();
        it != result.end(); ++it) {
        out << *it << endl;
    }
}

void LexicalAnalyser::write_result(const char *dist) {
    ofstream out(dist, ios::out);
    if (!out.is_open()) {
        printf("open out file %s failed\n", dist);
        exit(-1);
    }
    print_result(out);
    out.close();
}

const set<string> LexicalAnalyser::keywords ({
    "if", "while", "elif", "else", "yield", "True", "False",
    "import", "from", "and", "or", "xor", "break", "continue",
    "in", "for", "as", "del", "def", "return", "lambda",
    "try", "except", "raise", "assert", "is", "not"
});

const set<char> LexicalAnalyser::symbols ({
    '+', '-', '*', '/', ',', '.', '"', '\'', '#', ':',
    '(', ')', '<', '>', '[', ']', '{', '}', '-', '='
});
