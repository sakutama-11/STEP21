#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <initializer_list>

using namespace std;
const long long INF = numeric_limits<long long>::max();

enum type {
    NUMBER,
    OPEN,
    CLOSE,
    PLUS, 
    MINUS,
    TIMES,
    DIVIDER
};
struct Token {
    enum type type;
    double number;
};


struct Node {
    Token token;
    Node *parent, *left, *right;
};

double read_number(string &line, int &index) {
    double number = 0;
    while (index < line.length() && line[index] >= '0' && line[index] <= '9') {
        int n = line[index] - '0';
        number = number * 10 + (double) n;
        index++;
    }
    if (index < line.length() && line[index] == '.') {
        index++;
        double decimal = 0.1;
        while (index < line.length() && line[index] >= '0' && line[index] <= '9') {
            int n = line[index] - '0';
            number += (double) n * decimal;
            decimal /= 10.0;
            index++;
        }
    }
    return number; 
}

void set_number(Token &token, double num) {
    token.type = NUMBER;
    token.number = num;
    return;
}

void set_plus(string &line, int &index, Token &token) {
    token.type = PLUS;
    token.number = 0;
    index++;
    return;
}

void set_minus(string &line, int &index, Token &token) {
    token.type = MINUS;
    token.number = 0;
    index++;
    return;
}

void set_times(string &line, int &index, Token &token) {
    token.type = TIMES;
    token.number = 0;
    index++;
    return;
}

void set_divider(string &line, int &index, Token &token) {
    token.type = DIVIDER;
    token.number = 0;
    index++;
    return;
}

void set_open(string &line, int &index, Token &token) {
    token.type = OPEN;
    token.number = 0;
    index++;
    return;
}

void set_close(string &line, int &index, Token &token) {
    token.type = CLOSE;
    token.number = 0;
    index++;
    return;
}


vector<Token> tokenize(string line) {
    vector<Token> tokens;
    int index = 0;
    while (index < line.length()) {
        Token token;
        if (line[index] >= '0' && line[index] <= '9'){
            double number = read_number(line, index);
            set_number(token, number);
        }
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


void add_tree_left(Node* &root, Node* &np, Node* node) {
    root = node;
    np = node;
}

void add_node_left(Node* &root, Node* &np, Node* node, Token token) {
    node->token = token;
    root = node;
}

void add_tree_right(Node* &root, Node* &np, Node* node) {
    node->parent = np;
    np->right = node;
}


void add_node_right(Node* &root, Node* &np, Node* node, Token token) {
    node->token = token;
    node->parent = np;
    np->right = node;
}

void add_operator_top(Node* &root, Node* &np, Node* node, Token token) {
    node->token = token;
    node->left = root;
    root->parent = node;
    np = node;
    root = node;
}

void add_operator_right(Node* &root, Node* &np, Node* node, Token token) {
    node->token = token;
    node->parent = np;
    node->left = np->right;
    np->right = node;
    np = node;
}

Node* make_tree(vector<Token> &tokens, int &index, Node* start) {
    Node *root = start;
    Node *np = start;
    while (index < tokens.size()) {
        Token token = tokens.at(index);
        Node *new_node = new Node;
        switch (token.type) {
            case NUMBER:
                if (np == start) add_node_left(root, np, new_node, token);
                else add_node_right(root, np, new_node, token);
                index++;
                break;
            case OPEN:
                index++;
                if (np == start) add_tree_left(root, np, make_tree(tokens, index, start));
                else add_tree_right(root, np, make_tree(tokens, index, start));
                delete new_node;
                break;
            case CLOSE:
                delete new_node;
                index++;
                return root;
            case PLUS:
            case MINUS:
                add_operator_top(root, np, new_node, token);
                index++;
                break;
            case TIMES:
            case DIVIDER:
                if (np == start) add_operator_top(root, np, new_node, token);
                else add_operator_right(root, np, new_node, token);
                index++;
                break;
        }
    }
    return root;
}

double evaluate(Node *node, stack<Token> &stack) {
    cout << "evaluate" << endl;
    if (node == nullptr) {
        cout << "this is null" << endl;
        return 0;
    }
    cout << node <<endl;
    evaluate(node->left, stack);
    evaluate(node->right, stack);
    Token token = node->token;
    if (token.type == NUMBER) {
        cout << token.number << endl;
        stack.push(token);
    } else {
        cout << token.type << endl;
        Token b_token = stack.top();
        stack.pop();
        Token a_token = stack.top();
        stack.pop();
        Token new_token = {NUMBER, 0};
        double a = a_token.number;
        double b = b_token.number;
        switch (token.type) {
            case PLUS:                    
                new_token.number = a + b;
                stack.push(new_token);
                break;
            case MINUS:
                new_token.number = a - b;
                stack.push(new_token);
                break;
            case TIMES:
                new_token.number = a * b;
                stack.push(new_token);
                break;
            case DIVIDER:
                new_token.number = a / b;
                stack.push(new_token);
                break;
            }
    }
    return stack.top().number;
}

void test(string line, double answer) {
    vector<Token> tokens = tokenize(line);
    Node start;
    int index = 0;
    Node *root = make_tree(tokens, index, &start);
    cout << "tree was made"<< endl;
    stack<Token> s;
    double result = evaluate(root, s);
    if (fabs(answer - result) < 0.000000001) {
        cout << "PASS: ";
    } else {
        cout << "FAIL: " << line << "should be " << answer << " but, ";
    }
    cout << line << "=" << result << endl;
    return;
}

int main()
{
    test("1", 1);
    test("3+2", 5);
    test("3-2", 1);
    test("3*2", 6);
    test("3/2", 1.5);
    test("2.5+3.14", 5.64);
    test("1+2+3", 6);
    test("1*2*3", 6);
    test("1+2*3", 7);
    test("(1)", 1);
    test("((1))", 1);
    test("(1+2)*3", 9);
    test("3+2*(4+5)", 21);
    test("3+2*(4-5/2)", 6);
    test("(3*4.2/2+5)-((14-3)/3-2)", 9.633333333333);
    return 0;
}