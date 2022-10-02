#include<time.h>
#include<fstream>
#include<string>
#include "lexer.cpp"
using namespace std;

vector<vector<lexer::Token>> maketokens(const char* fname) {
    string line;
    vector<vector<lexer::Token>> content;
    ifstream file(fname);

    while (getline(file, line)) {
        content.push_back(lexer::tokenize(line));
    }
    file.close();

    return content;
}

void showlist(vector<lexer::Token> list){
    cout<<"["<<list[0].token;
    for(int i = 1; i < list.size(); i++){
        cout<<", "<<list[i].token;
    }
    cout<<"]";
}

int main(int argc, char *argv[]){
    // read file + make tokens
    auto tokens = maketokens(argv[1]);

    for (auto a: tokens){
        showlist(a);
    }

}
