//
// Created by Tijs Hoeijmakers on 01/12/2021.
//

#include "Tokenizer.h"

#include <iostream>

namespace parser_space {

    void Token::debugPrint() const {
        std::cout << "(tokentype: " << tokenTypeToString[this->mType] << ", text: " << this->mText << ")";
    }

    std::vector<Token> Tokenizer::parse(const std::string &modalFormula) {
        std::vector<Token> tokens;
        Token currentToken;

        for (int i = 0; i < modalFormula.length(); i++) {
            const char &currCh = modalFormula[i];
            char d = modalFormula[i];

            switch (currCh) {
                case '%':
                    while(modalFormula[i] != '\n') {
                        i++;
                    }
                    break;
                case 't':
                    if (currentToken.mType == WHITESPACE) {
                        if (modalFormula.substr(i, 4) == "true") {
                            currentToken.mType = TRUE_LITERAL;
                            endtoken(currentToken, tokens);
                            i += 3;
                        } else {
                            currentToken.mType = ACTION_LABEL;
                            currentToken.mText.append(1, currCh);
                        }

                    } else if (currentToken.mType == ACTION_LABEL) {
                        currentToken.mText.append(1, currCh);
                    } else {
                        throw std::runtime_error("t found in inappropriate context");
                    }
                    break;

                case 'f':
                    if (currentToken.mType == WHITESPACE) {
                        if (modalFormula.substr(i,  5) == "false") {
                            currentToken.mType = FALSE_LITERAL;
                            endtoken(currentToken, tokens);
                            i += 4;
                        } else {
                            currentToken.mType = ACTION_LABEL;
                            currentToken.mText.append(1, currCh);
                        }

                    } else if (currentToken.mType == ACTION_LABEL) {
                        currentToken.mText.append(1, currCh);
                    } else {
                        throw std::runtime_error("f found in inappropriate context");
                    }
                    break;
                case 'm':
                    if (currentToken.mType == WHITESPACE) {
                        if (modalFormula.substr(i,  2) == "mu") {
                            currentToken.mType = MU_LITERAL;
                            endtoken(currentToken, tokens);
                            i += 1;
                        } else {
                            currentToken.mType = ACTION_LABEL;
                            currentToken.mText.append(1, currCh);
                        }

                    } else if (currentToken.mType == ACTION_LABEL) {
                        currentToken.mText.append(1, currCh);
                    } else {
                        throw std::runtime_error("m found in inappropriate context");
                    }
                    break;
                case 'n':
                    if (currentToken.mType == WHITESPACE) {
                        if (modalFormula.substr(i,  2) == "nu") {
                            currentToken.mType = NU_LITERAL;
                            endtoken(currentToken, tokens);
                            i += 1;
                        } else {
                            currentToken.mType = ACTION_LABEL;
                            currentToken.mText.append(1, currCh);
                        }

                    } else if (currentToken.mType == ACTION_LABEL) {
                        currentToken.mText.append(1, currCh);
                    } else {
                        throw std::runtime_error("m found in inappropriate context");
                    }
                    break;

                case 'A' ... 'Z':
                    currentToken.mType = RECURSION_VARIABLE;
                    currentToken.mText = currCh;
                    endtoken(currentToken, tokens);
                    break;
                case 'a' ... 'e':
                case 'g' ... 'l':
                case 'o' ... 's':
                case 'u' ... 'z':
                case 0 ... 9:
                    currentToken.mType = ACTION_LABEL;
                    currentToken.mText.append(1, currCh);
                    break;

                case '(':
                    currentToken.mType = LEFT_ROUND_BRACKET;
                    endtoken(currentToken, tokens);
                    break;
                case ')':
                    currentToken.mType = RIGHT_ROUND_BRACKET;
                    endtoken(currentToken, tokens);
                    break;
                case '[':
                    currentToken.mType = LEFT_BOX_BRACKET;
                    endtoken(currentToken, tokens);
                    break;
                case ']':
                    endtoken(currentToken, tokens);
                    currentToken.mType = RIGHT_BOX_BRACKET;
                    endtoken(currentToken, tokens);
                    break;
                case '<':
                    currentToken.mType = LEFT_DIAMOND_BRACKET;
                    endtoken(currentToken, tokens);
                    break;
                case '>':
                    endtoken(currentToken, tokens);
                    currentToken.mType = RIGHT_DIAMOND_BRACKET;
                    endtoken(currentToken, tokens);
                    break;
                case '&':
                    if (modalFormula.substr(i, 2) == "&&") {
                        currentToken.mType = AND_OPERATOR;
                        endtoken(currentToken, tokens);
                        i++;
                    } else {
                        throw std::runtime_error("a single & is found...");
                    }
                    break;
                case '|':
                    if (modalFormula.substr(i, 2) == "||") {
                        currentToken.mType = OR_OPERATOR;
                        endtoken(currentToken, tokens);
                        i++;
                    } else {
                        throw std::runtime_error("a single | is found...");
                    }
                    break;
                default:
                    break;
            }


        }
        return tokens;

    }

    void Tokenizer::endtoken(Token &token, std::vector<Token> &tokens) {
        if (token.mType != WHITESPACE) {
            tokens.push_back(token);
        }
        token.mType = WHITESPACE;
        token.mText.erase();
    }

}