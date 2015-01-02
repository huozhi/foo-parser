#include "lexical_analyser.h"

int main(int argc, char *argv[]) {
    LexicalAnalyser la;
    la.open_src(argv[1]);
    la.extract_all();
    la.print_result();
    return 0;
}
