//
// Created by Tijs Hoeijmakers on 01/12/2021.
//

#ifndef MODALMUCHECKER_TOKENIZER_H
#define MODALMUCHECKER_TOKENIZER_H

#include <string>
#include <vector>

namespace parser_space {

    enum TokenType {
        WHITESPACE,
        TRUE_LITERAL,
        FALSE_LITERAL,
        RECURSION_VARIABLE,
        LEFT_ROUND_BRACKET,
        RIGHT_ROUND_BRACKET,
        LEFT_BOX_BRACKET,
        RIGHT_BOX_BRACKET,
        LEFT_DIAMOND_BRACKET,
        RIGHT_DIAMOND_BRACKET,
        MU_LITERAL,
        NU_LITERAL,
        AND_OPERATOR,
        OR_OPERATOR,
        ACTION_LABEL,
    };

    static const char* tokenTypeToString[] = {
            "WHITESPACE",
            "TRUE_LITERAL",
            "FALSE_LITERAL",
            "RECURSION_VARIABLE",
            "LEFT_ROUND_BRACKET",
            "RIGHT_ROUND_BRACKET",
            "LEFT_BOX_BRACKET",
            "RIGHT_BOX_BRACKET",
            "LEFT_DIAMOND_BRACKET",
            "RIGHT_DIAMOND_BRACKET",
            "MU_LITERAL",
            "NU_LITERAL",
            "AND_OPERATOR",
            "OR_OPERATOR",
            "ACTION_LABEL"
    };

    class Token {
    public:
        enum TokenType mType{WHITESPACE};
        std::string mText;

        void debugPrint() const;
    };

    class Tokenizer {
    public:
        std::vector<Token> parse(const std::string& modalFormula);

    private:
        void endtoken(Token& token, std::vector<Token>& tokens);

    };

}
#endif //MODALMUCHECKER_TOKENIZER_H
