#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <set>
using namespace std;

ifstream src; // input source file

vector<string> result; // extract tokens
bool process;

set<string> keywords({
    "int", "char", "float", "double", "long", "unsigned",
    "include", "define", "void",
    "main", "argc", "argv", "return",
});

set<char> symbols({
    '+', '-', '*', '/', ',', '.', ';', '"', '\'',
    '(', ')', '<', '>', '[', ']', '{', '}', '-', '#'
});

char tk; // current token

void extract() {
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
              || (ptk == '-' && tk == '>')
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

void write_result(const char *fname) {
    ofstream out(fname, ios::out);
    if (!out.is_open()) {
        printf("open out file %s failed\n", fname);
        exit(-1);
    }
    for (vector<string>::iterator it = result.begin();
        it != result.end(); ++it) {
        out << *it << endl;
    }
    out.close();
}

int main(int argc, char *argv[]) {
    string fin, fout;
    process = true;
    --argc, ++argv;
    if (argc > 0) fin.assign(argv[0]);
    else          fin.assign("/in");
    if (argc > 1) fout.assign(argv[1]);
    else          fout.assign("/tokens");

    src.open(fin.c_str(), ios::in);
    if (!src.is_open()) {
         printf("open source file %s failed\n", fin.c_str());
         exit(-1);
    }

    while (!src.eof()) {
        extract();
    }

    write_result(fout.c_str());
    src.close();
    return 0;
}
