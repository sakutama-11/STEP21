#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;
const long long INF = numeric_limits<long long>::max();

struct Token {
    string type;
    double number;
};

struct Node {
    int key;
    Token token;
    Node *parent, *left, *right;
};

void read_number(string &line, int &index, Token &token) {
    double number = 0;
    while (index < line.length() && line[index] >= '0' && line[index] <= '9') {
        int n = line[index] - '0';
        number = number * 10 + (double)n;
        index++;
    }
    if (index < line.length() && line[index] == '.') {
        index++;
        double decimal = 0.1;
        while (index < line.length() && line[index] >= '0' && line[index] <= '9') {
            int n = line[index] - '0';
            number += n * decimal;
            decimal /= 10;
            index++;
        }
    }
    token.type = "NUMBER";
    token.number = number;
    return; 
}

void set_plus(string &line, int &index, Token &token) {
    token.type = "PLUS";
    token.number = 0;
    index++;
    return;
}


void set_minus(string &line, int &index, Token &token) {
    token.type = "MINUS";
    token.number = 0;
    index++;
    return;
}


void set_times(string &line, int &index, Token &token) {
    token.type = "TIMES";
    token.number = 0;
    index++;
    return;
}


void set_divider(string &line, int &index, Token &token) {
    token.type = "DIVIDER";
    token.number = 0;
    index++;
    return;
}


void set_open(string &line, int &index, Token &token) {
    token.type = "OPEN";
    token.number = 0;
    index++;
    return;
}


void set_close(string &line, int &index, Token &token) {
    token.type = "CLOSE";
    token.number = 0;
    index++;
    return;
}

vector<Token> tokenize(string line) {
    vector<Token> tokens;
    int index = 0;
    while (index < line.length()) {
        Token token;
        if (line[index] >= '0' && line[index] <= '9')
            read_number(line, index, token);
        else if (line[index] == '+') set_plus(line, index, token);
        else if (line[index] == '-') set_minus(line, index, token);
        else if (line[index] == '*') set_times(line, index, token);
        else if (line[index] == '/') set_divider(line, index, token);
        else if (line[index] == '(') set_open(line, index, token);
        else if (line[index] == ')') set_close(line, index, token);
        else {
            cout << "Invalid character found: " + line[index] << endl;
            exit(1);
        }
        tokens.push_back(token);
    }
    return tokens;
}

Node make_tree(vector<Token> tokens, int &index) {
    Node n;
    Node *root;
    Node *np;
    while (index <= tokens.size()) {
        Token token = tokens.at(index);
        switch (token.type) {
            case "OPEN":
                index++;
                make_tree(tokens, index);
                // numberと同じ処理
                break;
            case "CLOSE":
                index++;
                return root;
            case "PLUS":
            case "MINUS":
                add_plus_minus(root, np);
                index++;
                break;
            case "TIMES":
            case "DIVIDER":
                add_times_divider(root, np);
                index++;
                break;
            case "NUMBER":
                add_number(root, np, tokens.at(index).number);
                index++;
                break;
        }
    }
    return *root;
}

int main()
{
    string line = "(3*4.2/2+5)-((14-3)/3-2)";
    vector<Token> tokens = tokenize(line);
    make_tree(tokens, 0);
    return 0;
}