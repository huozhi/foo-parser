#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <set>
using namespace std;

#ifndef LEXICAL_ANALYSER_H_INCLUDED
#define LEXICAL_ANALYSER_H_INCLUDED

class LexicalAnalyser {
private:
    ifstream src; // input source file

    vector<string> result; // extract tokens
    bool process;
    char tk; // current token

    static const set<string> keywords;
    static const set<char> symbols;

private:
    /**
     * utilities
     */

    void extract();

public:
    /**
     * exposed interface
     */
    LexicalAnalyser();
    void open_src(const char *);
    void extract_all();
    void print_result(ostream & = cout);
    void write_result(const char *);
};



#endif // LEXICAL_ANALYSER_H_INCLUDED
