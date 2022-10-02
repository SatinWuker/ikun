#include<iostream>         // std::cout<<
#include<vector>           // std::vector<>
#include<algorithm>        // std::find()
#include "ikun.hpp"  // TT(token types), KEYWORDS[4]
using namespace std;

namespace lexer {

    class Token {   // Token(token, type)
        public:
            string token, type;
            Token(string tok = "", string typ = TT_MPT)
            : token(tok), type(typ) {}
    };


    inline bool is_int(const string &str) {
        string::const_iterator it = str.begin();
        while (it != str.end() && std::isdigit(*it)) ++it;
        return !str.empty() && it == str.end();
    }
    inline bool is_float(const string &str) {
        string::const_iterator it = str.begin();
        while (it != str.end() && (std::isdigit(*it) || *it == '.')) ++it;
        return !str.empty() && it == str.end();
    }
    inline bool is_op(string &str) {
        return std::find(OPERATORS, OPERATORS + 5, str) != OPERATORS + 5;
    }

    inline string get_type(string &str) {
        if (std::find(KEYWORDS, KEYWORDS + 6, str) != KEYWORDS + 6)
            return TT_KW;

        else if (str[0] == '\'' && str.back() == '\'')
            return TT_STR;
        else if (is_op(str))
            return TT_OP;
        else if (is_int(str) == 1)
            return TT_INT;
        else if (is_float(str) == 1) return TT_FLOAT;
        else return TT_ID;
    }

    vector<Token> tokenize(string &text){
        vector<Token> tokens;                  // return: tokens
        int quote_count;                            // count of the char '

        string lastchar;                       // variable to store the last token
        for (int i = 0; i < text.length(); i++) {
            if (text[i] == '#') break;
            if (text[i] == '\'') quote_count++;

            if ((text[i] == ' '||text[i] == '\n') && quote_count % 2 == 0)
            {
                tokens.push_back(Token(lastchar, get_type(lastchar)));
                lastchar.clear();

                if(text[i] == '\n')
                    tokens.push_back(Token("\n", TT_EOF));
            }
            else lastchar += text[i];
        }

        return tokens;

    }

}
