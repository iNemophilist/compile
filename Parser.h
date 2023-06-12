#pragma once
/*��������
FIRST����
FIRST(PROG) = { {,}
FIRST(DECLS) = { int, bool, �� }
FIRST(DECLS') = { int, bool, �� }
FIRST(DECL) = { int, bool }
FIRST(NAMES) = { id }
FIRST(NAMES') = { ,, �� }
FIRST(NAME) = { id }
FIRST(STMTS) = { id, if, while, {, read, write, �� }
FIRST(STMTS') = { id, if, while, {, read, write, �� }
FIRST(STMT) = { id, if, while, {, read, write }
FIRST(ELSESTMT) = { else, �� }
FIRST(EXPR) = { id, number, (, -, }
FIRST(ADD') = { +, -, �� }
FIRST(ADD) = { +, - }
FIRST(TERM) = { id, number, (, -, }
FIRST(MUL') = { *, /, �� }
FIRST(MUL) = { *, / }
FIRST(NEGA) = { id, number, (, -, }
FIRST(FACTOR) = { id, number, ( }
FIRST(BOOL) = { id, number, (, !, -, }
FIRST(BOOL') = { ||, �� }
FIRST(JOIN) = { id, number, (, !, -, }
FIRST(JOIN') = { &&, �� }
FIRST(NOT) = { id, number, (, !, -, }
FIRST(REL) = { id, number, (, -, }
FIRST(ROP) = { >, >=, <, <=, ==, != }


FOLLOW����
FOLLOW(PROG) = {$}
FOLLOW(DECLS) = FOLLOW(DECLS') = {id, if, while, {, read, write, $}
FOLLOW(DECL) = {int, bool, id, if, while, {, read, write, $}
FOLLOW(NAMES) = FOLLOW(NAMES') = {;}
FOLLOW(NAME) = {,, ;}
FOLLOW(STMTS) = FOLLOW(STMTS') = {id, if, while, {, read, write, }, $}
FOLLOW(STMT) = {id, if, while, {, read, write, }, $}
FOLLOW(ELSESTMT) = {id, if, while, {, read, write, }, $}
FOLLOW(EXPR) = {), ;, >, >=, <, <=, ==, !=}
FOLLOW(ADD') = FOLLOW(ADD) = {), ;, >, >=, <, <=, ==, !=}
FOLLOW(TERM) = {+, -, ), ;, >, >=, <, <=, ==, !=}
FOLLOW(MUL') = FOLLOW(MUL) = {+, -, ), ;, >, >=, <, <=, ==, !=}
FOLLOW(NEGA) = {*, /, +, -, ), ;, >, >=, <, <=, ==, !=}
FOLLOW(FACTOR) = {*, /, +, -, ), ;, >, >=, <, <=, ==, !=}
FOLLOW(BOOL) = FOLLOW(BOOL') = {;, }
FOLLOW(JOIN) = FOLLOW(JOIN') = {||, ;, }
FOLLOW(NOT) = {&&, ||, ;, }
FOLLOW(REL) = {&&, ||, ;, }
FOLLOW(ROP) = {id, number, (, -, }

SELECT��:
SELECT(PROG �� { DECLS STMTS }) = { { }
SELECT(DECLS �� DECL DECLS') = { int, bool }
SELECT(DECLS �� empty) = { id, if, while, {, read, write, $ }
SELECT(DECLS' �� DECL DECLS') = { int, bool }
SELECT(DECLS' �� empty) = { id, if, while, {, read, write, $ }
SELECT(DECL �� int NAMES ;) = { int }
SELECT(DECL �� bool NAMES ;) = { bool }
SELECT(NAMES �� NAME NAMES') = { id }
SELECT(NAMES' �� , NAME NAMES') = { , }
SELECT(NAMES' �� empty) = { ; }
SELECT(NAME �� id) = { id }
SELECT(STMTS �� STMT STMTS') = { id, if, while, {, read, write }
SELECT(STMTS �� empty) = { }, $ }
SELECT(STMTS' �� STMT STMTS') = { id, if, while, {, read, write }
SELECT(STMTS' �� empty) = { }, $ }

SELECT(STMT �� id STMT')={id}
SELECT(STMT ��  = EXPR;)={=}
SELECT(STMT �� := BOOL;)={:=}

SELECT(STMT �� if id then STMT ELSESTMT) = { if }
SELECT(ELSESTMT �� else STMT) = { else }
SELECT(ELSESTMT �� empty) = { id, if, while, {, read, write, }, $ }

SELECT(STMT �� while id do STMT) = { while }
SELECT(STMT �� { STMTS }) = { { }
SELECT(STMT �� read id ;) = { read }
SELECT(STMT �� write id ;) = { write }

SELECT(EXPR �� TERM ADD') = { id, number, (, - }
SELECT(ADD' �� ADD TERM ADD') = { +, - }
SELECT(ADD' �� empty) = { ), ;, >, >=, <, <=, ==, != }
SELECT(ADD �� +) = { + }
SELECT(ADD �� -) = { - }
SELECT(TERM �� NEGA MUL') = { id, number, (, - }
SELECT(MUL' �� MUL NEGA MUL') = { *, / }
SELECT(MUL' �� empty) = { +, -, ), ;, >, >=, <, <=, ==, != }
SELECT(MUL �� *) = { * }
SELECT(MUL �� /) = { / }
SELECT(NEGA �� FACTOR) = { id, number, ( }
SELECT(NEGA �� - FACTOR) = { - }
SELECT(FACTOR �� ( EXPR )) = { ( }
SELECT(FACTOR �� id) = { id }
SELECT(FACTOR �� number) = { number }
SELECT(BOOL �� JOIN BOOL') = { id, number, (, !, - }
SELECT(BOOL' �� || JOIN BOOL') = { || }
SELECT(BOOL' �� empty) = { ;, } }
SELECT(JOIN �� NOT JOIN') = { id, number, (, !, - }
SELECT(JOIN' �� && NOT JOIN') = { && }
SELECT(JOIN' �� empty) = { ;, ||, } }
SELECT(NOT �� REL) = { id, number, (, - }
SELECT(NOT �� ! REL) = { ! }
SELECT(REL �� EXPR ROP EXPR) = { id, number, (, - }
SELECT(ROP �� >) = { > }
SELECT(ROP �� >=) = { >= }
SELECT(ROP �� <) = { < }
SELECT(ROP �� <=) = { <= }
SELECT(ROP �� ==) = { == }
SELECT(ROP �� !=) = { != }
*/
/*�������ҵĴ���*/
#include "lexical_analyzer.h"
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <vector>
#include<stack>
using namespace std;
struct TreeNode {
    pair<string, string> val;
    TreeNode* N1;
    TreeNode* N2;
    TreeNode* N3;
    TreeNode* N4;
    TreeNode* N5;
    TreeNode* N6;
    TreeNode(pair<string, string> x) : val(x), N1(nullptr), N2(nullptr), N3(nullptr), N4(nullptr), N5(nullptr), N6(nullptr) {}
};
//�﷨��ģ�鼰��ز���
class tree {
public:
    tree();
    ~tree();
    TreeNode* getroot() {
        return root;
    }
    bool add_node(TreeNode* current, pair<string, string> data, TreeNode*& NowInsert);//��current�������һ���ӽڵ㡣�������ҵ�˳��������ˣ�����false.
    string serialize(TreeNode* root);               // ��ת��Ϊ�ַ���
    TreeNode* NewNode(pair<string, string>);       //����һ���µ����ڵ�
    TreeNode* deserialize(string data);  // �ַ���ת��Ϊ��
    bool isEndNode(TreeNode* cur);
private:
    TreeNode* root;
    TreeNode* deserializeHelper(const vector<pair<string, string>>& vals, int& pos);//�ַ���ת��Ϊ���ĸ�������
};
bool tree::isEndNode(TreeNode* cur) {
    if (cur->N1 == NULL)return true;
    else
        return false;
}
tree::tree() {
    root = nullptr;
}
tree::~tree() {
    root = nullptr;
}

bool tree::add_node(TreeNode* current, pair<string, string> data, TreeNode*& NowInsert) {
    if (root == nullptr) {
        root = NewNode(data);
        return true;
    }
    if (current->N1 == nullptr) {
        current->N1 = NewNode(data);
        NowInsert = current->N1;
    }
    else if (current->N2 == nullptr) {
        current->N2 = NewNode(data);
        NowInsert = current->N2;
    }
    else if (current->N3 == nullptr) {
        current->N3 = NewNode(data);
        NowInsert = current->N3;
    }
    else if (current->N4 == nullptr) {
        current->N4 = NewNode(data);
        NowInsert = current->N4;
    }
    else if (current->N5 == nullptr) {
        current->N5 = NewNode(data);
        NowInsert = current->N5;
    }
    else if (current->N6 == nullptr) {
        current->N6 = NewNode(data);
        NowInsert = current->N6;
    }
    else
        return false;
    return true;
}
string tree::serialize(TreeNode* root) {
    if (root == nullptr) return "";
    stack<TreeNode*> s;
    s.push(root);
    string res = "";
    while (!s.empty()) {
        TreeNode* cur = s.top();
        s.pop();
        if (cur != nullptr) {
            res += (cur->val.first) + " ";
            res += (cur->val.second) + " ";
            s.push(cur->N6);
            s.push(cur->N5);
            s.push(cur->N4);
            s.push(cur->N3);
            s.push(cur->N2);
            s.push(cur->N1);
        }
        else {
            res += "#";
            res += " ";
        }
    }
    return res;
}
TreeNode* tree::deserialize(string data) {
    stringstream ss(data);
    pair<string, string> current_pair;
    vector<pair<string, string>> val;
    string current;
    while (ss >> current) {
        current_pair.first = current;
        if (current != "#")
            ss >> current;
        current_pair.second = current;
        val.push_back(current_pair);
    }
    int pos = 0;
    return deserializeHelper(val, pos);
}
TreeNode* tree::deserializeHelper(const vector<pair<string, string>>& vals, int& pos) {
    if (vals[pos].first == "#") {
        pos++;
        return nullptr;
    }
    TreeNode* node = new TreeNode(vals[pos++]);
    node->N1 = deserializeHelper(vals, pos);
    node->N2 = deserializeHelper(vals, pos);
    node->N3 = deserializeHelper(vals, pos);
    node->N4 = deserializeHelper(vals, pos);
    node->N5 = deserializeHelper(vals, pos);
    node->N6 = deserializeHelper(vals, pos);
    return node;
}
TreeNode* tree::NewNode(pair<string, string> data) {
    TreeNode* node = new TreeNode(data);
    return node;
}
// �﷨����ģ��
class Parser {
public:
    Parser(const string& InputFile, const string& middleFile, const string& OutputFile);
    ~Parser();
    void print();                                                                           //���Ԥ�������
    TreeNode* deserialize(const string& input);                                             //���л�����ļ��ķ����л��������л��Ƿ�ɹ�
    void serialize(const string& output, TreeNode* root);                                   //���л�����ļ��ķ����л�����ļ������л���ͨ�������л�����ļ��Ա�����֤���л��ͷ����л�����
    bool do_parser(const vector<pair<string, string>>& input, TreeNode*& result);          //�﷨��������
    bool do_and_write();                                                                  //�ʷ��������﷨���������н���������
private:
    bool isComment(const std::string& line, size_t& pos);                                 //��ǰ���Ƿ����ע��
    bool is_end_character(const string& a);                                               //��ǰ�ַ����Ƿ����ս��
    string in;                                                                          //�����ļ���
    string out;                                                                           //�﷨�����������ļ���
    string middle;                                                                        //�ʷ������������ļ���
    int findNthStringLine(const std::string& filename, int n, string& result);             //�ҵ���ǰ�ļ��е�i���ַ����ĺ����������﷨����������
    vector<vector<pair<vector<string>, vector<string>>>>LL1_t;                              //Ԥ�����������������ʾ��ͬ�ķ��ս����Ӧ��ÿ��״̬���ڶ��������ʾÿ��״̬�Ķ����䡣���������飬��ʾÿ��״̬�Ĳ���ʽ�Ҳ����ս�����Ϻ���Ӧselect�����ս�����    
    void init_LL1_able();
    bool do_parser_input_change(vector<pair<string, string>>& result, const vector<pair<string, string>>& input);      //����ʷ����������ʹ����ʺϽ����﷨����                                                
    int find_status(string a);                                   //��Ԥ����������ҵ���Ӧ�ķ��ս��
    string true_string(const string& a);                         //��ǰ�ַ�������ָ�����һ���ַ�������ǰ�ַ��������зָ����ÿո����                
    int judge_status(string a, int status);                         //��Ԥ��������У��ҵ���Ӧ�Ĳ���ʽ
};
TreeNode* Parser::deserialize(const string& input) {
    ifstream in(input);
    TreeNode* result;
    string current;
    string middle;
    middle.clear();
    while (in >> current) {
        middle += current + " ";
    }
    middle += '\0';
    tree t;
    result = t.deserialize(middle);
    return result;
}
void Parser::serialize(const string& output, TreeNode* root) {
    ofstream out(output);
    tree t;
    string middle;
    middle = t.serialize(root);
    out << middle;
}
bool Parser::isComment(const std::string& line, size_t& pos) {
    pos = line.find("//");
    if (pos != std::string::npos) {
        return true;
    }
    return false;
}
string Parser::true_string(const string& a) {
    string result;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == '(' || a[i] == ')' || a[i] == '{' || a[i] == '}' || a[i] == ',' || a[i] == ';') {
            result += " ";
            result += a[i];
            result += " ";
        }
        else {
            result += a[i];
        }

    }
    return result;
}
int Parser::findNthStringLine(const std::string& filename, int n, string& result) {
    using namespace std;
    ifstream file(filename);  // ���ļ�
    if (!file) {
        cerr << "�޷����ļ�: " << filename << std::endl;  // ����޷����ļ������������Ϣ
        return -1;
    }
    int lineNumber = 0;
    int stringCount = 0;
    string line;
    bool inMultilineComment = false;  // ����Ƿ��ڶ���ע����
    while (std::getline(file, line)) {  // ���ж�ȡ�ļ�
        lineNumber++;  // �кŵ���
        size_t commentPos;
        if (isComment(line, commentPos)) {  // �жϵ�ǰ���Ƿ�Ϊ����ע��
            line = line.substr(0, commentPos);  // ɾ��ע�Ͳ���
        }
        size_t multiCommentStart = line.find("/*");  // ���Ҷ���ע����ʼ��
        size_t multiCommentEnd = line.find("*/");  // ���Ҷ���ע�ͽ�����
        if (inMultilineComment) {  // ������ڶ���ע����
            if (multiCommentEnd != std::string::npos) {  // ����ҵ�����ע�ͽ�����
                inMultilineComment = false;  // ���ö���ע�ͱ��Ϊ false
                line = line.substr(multiCommentEnd + 2);  // ɾ��ע�Ͳ���
            }
            else {
                continue;  // ������ȡ��һ��
            }
        }
        else {
            if (multiCommentStart != std::string::npos) {  // ����ҵ�����ע����ʼ��
                inMultilineComment = true;  // ���ö���ע�ͱ��Ϊ true
                line = line.substr(0, multiCommentStart);  // ɾ��ע�Ͳ���
            }
        }
        if (line.empty()) {  // �����ǰ��Ϊ�գ���������
            continue;
        }
        line = true_string(line);
        std::istringstream iss(line);  // �����ַ������Դ���ǰ��
        std::string word;
        bool is_first = true;
        while (iss >> word) {  // ��ȡ��ǰ�е�ÿ���ַ���
            stringCount++;  // �ַ�����������
            if (stringCount == n - 1)result = word;
            if (stringCount == n && is_first) {  // ����ﵽĿ���ַ�������
                return lineNumber - 1;  // �����к�
            }
            if (stringCount == n && !is_first) {  // ����ﵽĿ���ַ�������
                return lineNumber;  // �����к�
            }
            if (is_first)
                is_first = false;
        }
    }

    std::cerr << "�ļ����ַ����������� " << n << std::endl;  // ����ļ��е��ַ����������� n�����������Ϣ
    return -1;
}
bool Parser::is_end_character(const string& a) {
    if (a == "int" || a == "bool" || a == "if" || a == "then" || a == "while" || a == "do" || a == "read" || a == "write" || a == "else" || a == "+" || a == "-" || a == "*" || a == "/" || a == "||" || a == "&&" || a == "!" || a == ">=" || a == ">" || a == "<=" || a == "<" || a == ":=" || a == "==" || a == "=" || a == "(" || a == ")" || a == "{" || a == "}" || a == ";" || a == "," || a == "number" || a == "id")
        return true;
    return false;
}
std::string readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}
Parser::Parser(const string& InputFile, const string& middleFile, const string& OutputFile) {
    in = InputFile;
    out = OutputFile;
    middle = middleFile;
    pair<vector<string>, vector<string>> current;
    vector<pair<vector<string>, vector<string>>> current1;
    //PROG
    current.first = { "{","DECLS","STMTS","}" };
    current.second = { "{" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //DECLS
    current.first = { "DECL","DECLS'" };
    current.second = { "int", "bool" };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { "id", "if", "while", "{", "read", "write", "$" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //DELCS'
    current.first = { "DECL","DECLS'" };
    current.second = { "int", "bool" };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { "id", "if", "while", "{", "read", "write", "$" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //DECL
    current.first = { "int","NAMES",";" };
    current.second = { "int" };
    current1.push_back(current);
    current.first = { "bool","NAMES",";" };
    current.second = { "bool" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //NAMES
    current.first = { "NAME","NAMES'" };
    current.second = { "id" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //NAMES'

    current.first = { ",","NAME","NAMES'" };
    current.second = { "," };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { ";" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //NAME
    current.first = { "id" };
    current.second = { "id" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //STMTS
    current.first = { "STMT","STMTS'" };
    current.second = { "id","if","while", "{", "read", "write" };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { "}", "$" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //STMTS'
    current.first = { "STMT","STMTS'" };
    current.second = { "id","if","while", "{", "read", "write" };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { "}", "$" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //STMT
    current.first = { "id","STMT'" };
    current.second = { "id" };
    current1.push_back(current);
    current.first = { "if","id","then","STMT","ELSESTMT" };
    current.second = { "if" };
    current1.push_back(current);
    current.first = { "while","id","do","STMT" };
    current.second = { "while" };
    current1.push_back(current);
    current.first = { "{","STMTS","}" };
    current.second = { "{" };
    current1.push_back(current);
    current.first = { "read","id",";" };
    current.second = { "read" };
    current1.push_back(current);
    current.first = { "write","id",";" };
    current.second = { "write" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //STMT'
    current.first = { "=","EXPR",";" };
    current.second = { "=" };
    current1.push_back(current);
    current.first = { ":=","BOOL",";" };
    current.second = { ":=" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //ELSESTMT
    current.first = { "else","STMT" };
    current.second = { "else" };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { "id","if","while","{","read","write","}","$" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //EXPR
    current.first = { "TERM","ADD'" };
    current.second = { "id","number","(","-" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //ADD'
    current.first = { "ADD","TERM","ADD'" };
    current.second = { "+","-" };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { ")",";",">",">=","<","<=","==","!=" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //ADD
    current.first = { "+" };
    current.second = { "+" };
    current1.push_back(current);
    current.first = { "-" };
    current.second = { "-" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //TERM
    current.first = { "NEGA","MUL'" };
    current.second = { "id","number","(","-" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //MUL'
    current.first = { "MUL","NEGA","MUL'" };
    current.second = { "*","/" };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { "+","-",")",";",">",">=","<","<=" ,"==" ,"!=" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //MUL
    current.first = { "*" };
    current.second = { "*" };
    current1.push_back(current);
    current.first = { "/" };
    current.second = { "/" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //NEGA
    current.first = { "FACTOR" };
    current.second = { "id","number", "(" };
    current1.push_back(current);
    current.first = { "-","FACTOR" };
    current.second = { "-" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //FACTOR
    current.first = { "(","EXPR",")" };
    current.second = { "(" };
    current1.push_back(current);
    current.first = { "id" };
    current.second = { "id" };
    current1.push_back(current);
    current.first = { "number" };
    current.second = { "number" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //BOOL
    current.first = { "JOIN","BOOL'" };
    current.second = { "id","number", "(", "!", "-" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //BOOL'
    current.first = { "||","JOIN","BOOL'" };
    current.second = { "||" };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { ";","}" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //JOIN
    current.first = { "NOT","JOIN'" };
    current.second = { "id","number", "(", "!", "-" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //JOIN'
    current.first = { "&&","NOT","JOIN'" };
    current.second = { "&&" };
    current1.push_back(current);
    current.first = { "empty" };
    current.second = { ";", "||" ,"}" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //NOT
    current.first = { "REL" };
    current.second = { "id","number","(","-" };
    current1.push_back(current);
    current.first = { "!","REL" };
    current.second = { "!" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //REL
    current.first = { "EXPR","ROP","EXPR" };
    current.second = { "id","number","(","-" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
    //ROP
    current.first = { ">" };
    current.second = { ">" };
    current1.push_back(current);
    current.first = { ">=" };
    current.second = { ">=" };
    current1.push_back(current);
    current.first = { "<" };
    current.second = { "<" };
    current1.push_back(current);
    current.first = { "<=" };
    current.second = { "<=" };
    current1.push_back(current);
    current.first = { "==" };
    current.second = { "==" };
    current1.push_back(current);
    current.first = { "!=" };
    current.second = { "!=" };
    current1.push_back(current);
    LL1_t.push_back(current1);
    current1.clear();
}
int status_find(const string a) {
    if (a == "PROG")return 1;
    else if (a == "DECLS")return 2;
    else if (a == "DECLS'")return 3;
    else if (a == "DECL")return 4;
    else if (a == "NAMES")return 5;
    else if (a == "NAMES'")return 6;
    else if (a == "NAME")return 7;
    else if (a == "STMTS")return 8;
    else if (a == "STMTS'")return 9;
    else if (a == "STMT")return 10;
    else if (a == "STMT'")return 11;
    else if (a == "ELSESTMT")return 12;
    else if (a == "EXPR")return 13;
    else if (a == "ADD'")return 14;
    else if (a == "ADD")return 15;
    else if (a == "TERM")return 16;
    else if (a == "MUL'")return 17;
    else if (a == "MUL")return 18;
    else if (a == "NEGA")return 19;
    else if (a == "FACTOR")return 20;
    else if (a == "BOOL")return 21;
    else if (a == "BOOL'")return 22;
    else if (a == "JOIN")return 23;
    else if (a == "JOIN'")return 24;
    else if (a == "NOT")return 25;
    else if (a == "REL")return 26;
    else if (a == "ROP")return 27;
    else return -1;

}
Parser::~Parser() {
}
void Parser::print() {
    for (int i = 0; i < LL1_t.size(); i++) {
        cout << i + 1 << endl;
        for (int j = 0; j < LL1_t[i].size(); j++) {
            for (int m = 0; m < LL1_t[i][j].first.size(); m++) {
                cout << LL1_t[i][j].first[m] << " ";
            }
            cout << "--------------------";
            for (int m = 0; m < LL1_t[i][j].second.size(); m++) {
                cout << LL1_t[i][j].second[m] << " ";
            }
            cout << endl;
        }
    }
}
int Parser::find_status(string a) {
    if (a == "PROG")return 1;
    else if (a == "DECLS")return 2;
    else if (a == "DECLS'")return 3;
    else if (a == "DECL")return 4;
    else if (a == "NAMES")return 5;
    else if (a == "NAMES'")return 6;
    else if (a == "NAME")return 7;
    else if (a == "STMTS")return 8;
    else if (a == "STMTS'")return 9;
    else if (a == "STMT")return 10;
    else if (a == "STMT'")return 11;
    else if (a == "ELSESTMT")return 12;
    else if (a == "EXPR")return 13;
    else if (a == "ADD'")return 14;
    else if (a == "ADD")return 15;
    else if (a == "TERM")return 16;
    else if (a == "MUL'")return 17;
    else if (a == "MUL")return 18;
    else if (a == "NEGA")return 19;
    else if (a == "FACTOR")return 20;
    else if (a == "BOOL")return 21;
    else if (a == "BOOL'")return 22;
    else if (a == "JOIN")return 23;
    else if (a == "JOIN'")return 24;
    else if (a == "NOT")return 25;
    else if (a == "REL")return 26;
    else if (a == "ROP")return 27;
    else return -1;
}
int Parser::judge_status(string a, int status) {
    for (int i = 0; i < LL1_t[status - 1].size(); i++) {
        for (int m = 0; m < LL1_t[status - 1][i].second.size(); m++) {
            if (LL1_t[status - 1][i].second[m] == a)return i;
        }
    }
    return -1;
}
bool Parser::do_parser_input_change(vector<pair<string, string>>& result, const vector<pair<string, string>>& input) {
    result.clear();
    for (int i = 0; i < input.size(); i++) {
        if (input[i].first == "BL")
            result.push_back({ "bool",input[i].second });
        else if (input[i].first == "KW")
            result.push_back({ input[i].second,input[i].second });
        else if (input[i].first == "ID")
            result.push_back({ "id",input[i].second });
        else if (input[i].first == "NU")
            result.push_back({ "number",input[i].second });
        else if (input[i].first == "OP")
            result.push_back({ input[i].second,input[i].second });
        else if (input[i].first == "SP")
            result.push_back({ input[i].second,input[i].second });
        else {
            return false;
        }
    }
    result.push_back({ "$","$" });
    return true;
}
bool Parser::do_parser(const vector<pair<string, string>>& input, TreeNode*& result) {
    tree t;
    stack<TreeNode*> stack_b;
    TreeNode* tree_node_current = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* tree_node_current1 = (TreeNode*)malloc(sizeof(TreeNode));
    vector<pair<string, string>> true_input;
    if (!do_parser_input_change(true_input, input))return false;   //�Դʷ�������������д���
    int judge_seperator[2] = { 0,0 };
    if (true_input[0].first != "{") {
        string error_string;
        int current_line = findNthStringLine(in, 1, error_string);
        cout << "��" << current_line << "��: " << endl;
        cout << "��ʼ���Ŵ��󣡴���Ӧ���� \"{\" Ϊ��ʼ���ţ������ʼ����Ϊ: " << true_input[0].first << endl;
        return false;
    }
    for (int i = 0; i < true_input.size(); i++) {
        if (true_input[i].first == "{")judge_seperator[0]++;
        else if (true_input[i].second == "}")judge_seperator[0]--;
        else if (true_input[i].second == "(")judge_seperator[1]++;
        else if (true_input[i].second == ")")judge_seperator[1]--;
    }
    if (judge_seperator[0] != 0 || judge_seperator[1] != 0) {
        if (judge_seperator[0] != 0)
            cout << "{}δ�õ�ƥ�䣬����ϸ�������﷨" << endl;
        if (judge_seperator[1] != 0)
            cout << "()δ�õ�ƥ�䣬����ϸ�������﷨" << endl;
        return false;
    }
    stack<TreeNode*> a;                   //�﷨���������ջ
    string current;                //��ǰ�﷨����ջ��ջ��Ԫ��
    int flag = 0;                  //�ʷ����������ָ��
    t.add_node(t.getroot(), { "PROG","PROG" }, tree_node_current1);   //�������ڵ�
    TreeNode* end_note = new TreeNode({ "$","$" });
    a.push(end_note);
    a.push(t.getroot());                //���ڵ���ջ
    int status;                          //��ǰ�ַ�����Ӧ״̬
    int number;                       //��ǰ�ַ�����Ӧ״̬�µĵڼ����
    while (flag < true_input.size()) {
        tree_node_current = a.top();        //ȡ��ջ��Ԫ��
        a.pop();
        current = tree_node_current->val.first;
        if (current == "empty") {
            t.add_node(tree_node_current, tree_node_current->val, tree_node_current1);
            continue;
        }
        else if (current == true_input[flag].first) {                //���ջ��Ԫ�����ս���ҷ��ϣ�ջ��Ԫ�س�ջ����������ƶ�һλ
            t.add_node(tree_node_current, { true_input[flag].first ,true_input[flag].second }, tree_node_current1);
            flag++;
            continue;
        }
        else if (current == "$" && true_input[flag].first != "$") {
            string error_string;
            int current_line = findNthStringLine(in, flag + 1, error_string);
            cout << "��" << current_line << "��: " << endl;
            cout << "����ĩβ����Ƿ��ַ���" << endl;
            while (flag < true_input.size() - 1)cout << true_input[flag++].second << " ";
            cout << endl;
            return false;
        }
        else if (is_end_character(current)) {                                        //�ս����ƥ��
            string error_string;
            int current_line = findNthStringLine(in, flag + 1, error_string);
            cout << "��" << current_line << "��: " << endl;
            cout << "�ַ���: " << error_string << endl << "��һ���޷�ƥ����ַ�������������﷨" << endl;
            return false;
        }
        status = find_status(current);
        number = judge_status(true_input[flag].first, status);
        if (number == -1) {
            string error_string;
            int current_line = findNthStringLine(in, flag + 1, error_string);
            cout << "��" << current_line << "��: " << endl;
            cout << "�ַ���: " << error_string << endl << "��һ���޷�ƥ����ַ�������������﷨" << endl;
            return false;
        }
        for (int i = 0; i < LL1_t[status - 1][number].first.size(); i++) {
            if (!t.add_node(tree_node_current, { LL1_t[status - 1][number].first[i],LL1_t[status - 1][number].first[i] }, tree_node_current1))return false;             //������ջ
            stack_b.push(tree_node_current1);
        }
        while (!stack_b.empty()) {
            a.push(stack_b.top());
            stack_b.pop();
        }
    }
    result = t.getroot();
    return true;
}
// �����д���ļ�
void writeFile(const std::string& fileName, const std::string& content) {
    std::ofstream file(fileName);
    file << content;
}


bool Parser::do_and_write() {
    ifstream input_string(in);
    if (!input_string.is_open()) {
        ofstream out(in);
        string path = __FILE__;
        string now_path = path.substr(0, path.size() - 6);
        cout << "δ����Դ�����ļ�������Ŀ¼: " << now_path << "�£�����test.txt�ļ�Ϊ�ǿ�!!!,����Դ���벻��Ϊ��!!!" << endl;
        input_string.close();
        return false;
    }
    char c;
    input_string >> c;
    if (input_string.eof()) {
        string path = __FILE__;
        string now_path = path.substr(0, path.size() - 6);
        cout << "δ����Դ�����ļ�������Ŀ¼: " << now_path << "�£�����test.txt�ļ�Ϊ�ǿ�!!!,����Դ���벻��Ϊ��!!!" << endl;
        input_string.close();
        return false;
    }
    input_string.close();
    lexical_analyzer a(in, middle);
    if (a.analyze()) {
        tree t;
        TreeNode* result = nullptr;
        vector<pair<string, string>> in_put;
        in_put = a.result_to_token(middle);
        if (do_parser(in_put, result)) {
            ofstream out__put(out);
            string result_string = t.serialize(result);
            out__put << result_string;
            out__put.close();
            cout << "�﷨��ȷ" << endl;
        }
        return true;
    }
    else
        return false;

}
/*
int��bool��if��then��while��do��read��write��else��+��-��*��/��||��&&��!��>=��>��<=��<��:=��==��=��(��)��{��}��;��,��number��id
   */
bool file_same(const string& file1, const string& file2) {
    ifstream input1(file1);
    ifstream input2(file2);
    string current1;
    string current2;
    bool result = true;
    while ((input1 >> current1) && (input2 >> current2))
        if (current1 != current2)
            result = false;
    return result;
}
