#pragma once
#pragma once
#include<sstream>
#include <vector>
#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
//������ʵ�ֵ���һ����little_c������
/*a. �����Ե�һ���������ҽ���һ����ṹ��ɣ��ÿ��а��������֣���ѡ���������ͱ����ִ����䡣���������������������ִ��������ڱ�������̣�������ʹ����Щ�������洢�ڲ����ݺͼ�������

b. ������֧�������������ͣ����ͺͲ����͡���������ռ4���ֽڣ�������ռ1���ֽڡ��������ݵĳ����������������������ݵĳ����� true �� false ��

c. ��������֧�� +��-��*��/ �����������㣬������Ϊ����ֵ���������ݿ���>��>=...��������ϵ�������ϣ�������Ϊ������ֵ��

d. ����������֧�� || ��&& ���������߼����㣬������Ϊ����������

e. ���͵ı����ͳ��������������������ϳ��������ʽ����ֵΪ�������������͵ı����ͳ����������߼��������ɳɲ������ʽ����ֵΪ�����������������ʽ���Լ��Ϲ�ϵ�����������������ʽ��

f. ���������������ʽ�����������ͱ�����ֵ�����������Ͳ������ʽ�������ڲ����ͱ�����ֵ�����߲����ݣ��ķ���ʹ�ò�ͬ�ĸ�ֵ�������ʾ���𣩡�

g. ��������������ȼ��ͽ�Ϲ������C�����﷨��⡣

h. ����������еĿ��������޶�Ϊ1�������ͱ���������Ӧ��������֮ǰ��ֵ��

i. �����Բ�֧�����顢�ṹ�塢ָ��ȸ����������͡�

j. �����Բ������ӳ���ṹ��Ҳ��֧�ֹ��̵��á�

k. �������м򵥵�I/O���ܣ�ʹ��readָ���ܹ��Ӽ��̶���1����������ʹ��writeָ��������Ļ��ӡ���1����������*/
/*�ķ����壺
PROG        ��    {  DECLS  STMTS  }
DECLS       ��    DECLS  DECL    |   empty
DECL         ��    int  NAMES  ;  |  bool  NAMES  ;
NAMES     ��    NAMES ,  NAME  |  NAME
NAME       ��    id
STMTS    ��    STMTS  STMT  |   STMT
STMT      ��    id  =  EXPR ;    |   id := BOOL ;
STMT      ��    if  id   then  STMT
STMT      ��    if   id   then  STMT  else STMT
STMT      ��    while   id  do  STMT
STMT      ��    {  STMTS   STMT  }
STMT      ��    read  id  ;
STMT      ��    write  id  ;
EXPR    ��    EXPR  ADD  TERM  |  TERM
ADD     ��    + | -
TERM    ��    TERM  MUL NEGA  |  NEGA
MUL     ��    * | /
NEGA   ��    FACTOR  |  - FACTOR
FACTOR��    (  EXPR ) |  id  |  number
BOOL    ��    BOOL  ||  JOIN    |    JOIN
JOIN     ��    JOIN   &&   NOT  |   NOT
NOT      ��    REL   |  ! REL
REL       ��    EXPR   ROP  EXPR
ROP      ��     >  |  >=  |  <  |  <=  |  ==  |   !=*/

using namespace std;
enum Token {
    IDENTIFIER,            //��ʶ��
    NUMBER,             //������
    BOOL,               //��������
    KEYWORD,            //�ؼ���
    OPERATOR,           //�����
    SEPARATOR,          //�ָ���
    INVALID_TOKEN,     //��Ч��
};
class lexical_analyzer {
public:
    lexical_analyzer(const string& input_file_name, const string& output_file_name);
    ~lexical_analyzer();
    std::vector<pair<string, string>> result_to_token(const string& ifn);
    bool analyze();
private:
    unordered_map<string, Token> keyword_map = {
        {"int",KEYWORD},
        {"bool",KEYWORD},
        {"if",KEYWORD},
        {"then",KEYWORD},
        {"while",KEYWORD},
        {"do",KEYWORD},
        {"read",KEYWORD},
        {"write",KEYWORD},
        {"else",KEYWORD},
    };
    unordered_map<string, Token> operator_map = {
        {"+", OPERATOR},
        {"-", OPERATOR},
        {"*", OPERATOR},
        {"/", OPERATOR},
        {"||", OPERATOR},
        {"&&", OPERATOR},
        {"!", OPERATOR},
        {">=", OPERATOR},
        {">", OPERATOR},
        {"<=", OPERATOR},
        {"<", OPERATOR},
        {"==", OPERATOR},
        {":=", OPERATOR},
        {"=", OPERATOR},
    };
    unordered_map<string, Token> separator_map = {
        {"(", SEPARATOR},
        {")", SEPARATOR},
        {"{", SEPARATOR},
        {"}", SEPARATOR},
        {",", SEPARATOR},
        {";", SEPARATOR},
    };
    unordered_map<string, Token> bool_map = {
        {"true",BOOL},
        {"false",BOOL},
    };
    Token get_keyword(const string& str);    //�ж��Ƿ��ǹؼ���
    Token get_operator(const string& str);   //�ж��Ƿ��������
    Token get_separator(const string& str);  //�ж��Ƿ��Ƿָ���
    Token get_number(const string& str);    //�ж��Ƿ�����������
    Token get_bool(const string& str);      //�ж��Ƿ����ַ�����
    Token get_explanatorynote(const string& str); //�ж��Ƿ���ע��
    void write_token(Token token, const string& word);
    string in;
    string out;
    ifstream input_file;
    ofstream output_file;
    string find_operator(const string& str, int i);
    string find_bool(const string& str, int i);
    string find_separator(const string& str, int i);
    int findNthCharLine(const std::string& filename, int n, string& result);
};
lexical_analyzer::lexical_analyzer(const string& input_file_name, const string& output_file_name) {
    input_file.open(input_file_name);
    output_file.open(output_file_name);
    in = input_file_name;
    out = input_file_name;
}
lexical_analyzer::~lexical_analyzer() {
    input_file.close();
    output_file.close();
}
Token lexical_analyzer::get_keyword(const string& str) {
    auto it = keyword_map.find(str);
    if (it != keyword_map.end()) {
        return it->second;
    }
    return IDENTIFIER;
}
Token lexical_analyzer::get_bool(const string& str) {
    auto it = bool_map.find(str);
    if (it != bool_map.end()) {
        return it->second;
    }
    return IDENTIFIER;
}
Token lexical_analyzer::get_operator(const string& str) {
    auto it = operator_map.find(str);
    if (it != operator_map.end()) {
        return it->second;
    }
    return INVALID_TOKEN;
}
Token lexical_analyzer::get_separator(const string& str) {
    auto it = separator_map.find(str);
    if (it != separator_map.end()) {
        return it->second;
    }
    return INVALID_TOKEN;
}
Token lexical_analyzer::get_number(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return INVALID_TOKEN;
        }
    }
    return NUMBER;
}
void lexical_analyzer::write_token(Token token, const string& word) {
    switch (token) {
        /*enum Token {
    IDENTIFIER,            //��ʶ��
    NUMBER,             //������
    BOOL,               //��������
    KEYWORD,            //�ؼ���
    OPERATOR,           //�����
    SEPARATOR,          //�ָ���
    INVALID_TOKEN,     //��Ч��
};*/
    case BOOL:
        output_file << "BL " << word << endl;
        break;
    case KEYWORD:
        output_file << "KW " << word << endl;
        break;
    case IDENTIFIER:
        output_file << "ID " << word << endl;
        break;
    case NUMBER:
        output_file << "NU " << word << endl;
        break;
    case OPERATOR:
        output_file << "OP " << word << endl;
        break;
    case SEPARATOR:
        output_file << "SP " << word << endl;
        break;
    default:
        break;
    }
}
void CreatNext_E(string p, int next[]) {
    int lenP = p.size();
    int i = 0, j = -1;
    next[0] = -1;
    while (i < lenP - 1) {
        if (j < 0 || p[i] == p[j]) {
            i++;
            j++;
            next[i] = p[i] == p[j] ? next[j] : j;  //�˾��������˸Ľ�
        }
        else {
            j = next[j];
        }
    }
}
int KMP_find_string_in_string(string t, string p, int current) {
    int lenT = t.size();
    int lenP = p.size();
    int* next = new int[lenP];
    //CreatNext(p, next);
    CreatNext_E(p, next);
    int i, j;
    for (i = current; i <= lenT - lenP; ) {
        for (j = 0; j < lenP; ++j) {
            if (t[i + j] != p[j]) {
                i += j - next[j];
                break;
            }
        }
        if (j == lenP) {
            return i;
        }
    }
    return -1;
}
int BF_find_string_in_string(string t, string p, int current) {
    int lenT = t.size();
    int lenP = p.size();
    int i, j;
    for (i = current; i <= lenT - lenP; ++i) {
        for (j = 0; j < lenP; ++j) {
            if (t[i + j] != p[j]) {
                break;
            }
        }
        if (j == lenP) {
            return i;
        }
    }
    return -1;
}
string lexical_analyzer::find_operator(const string& str, int i) {
    int flag = 0;
    unordered_map<string, Token>::iterator iter;
    for (iter = operator_map.begin(); iter != operator_map.end(); iter++)
    {
        flag = 0;
        flag = KMP_find_string_in_string(str, iter->first, i);
        if (flag == i) { return iter->first; }
    }
    return "";
}
string lexical_analyzer::find_bool(const string& str, int i) {
    int flag = 0;
    unordered_map<string, Token>::iterator iter;
    for (iter = bool_map.begin(); iter != bool_map.end(); iter++)
    {
        flag = 0;
        flag = KMP_find_string_in_string(str, iter->first, i);
        if (flag == i) { return iter->first; }
    }
    return "";
}
string lexical_analyzer::find_separator(const string& str, int i) {
    int flag = 0;
    unordered_map<string, Token>::iterator iter;
    for (iter = separator_map.begin(); iter != separator_map.end(); iter++)
    {
        flag = 0;
        flag = KMP_find_string_in_string(str, iter->first, i);
        if (flag == i) { return iter->first; }
    }
    return "";
}
std::vector<pair<string, string>> lexical_analyzer::result_to_token(const string& ifn) {
    vector<pair<string, string>> result;
    ifstream input(ifn);
    pair<string, string> current;
    input >> current.first;
    input >> current.second;
    while (!input.eof()) {
        result.push_back(current);
        input >> current.first;
        input >> current.second;
    }
    return result;
}
int lexical_analyzer::findNthCharLine(const std::string& filename, int n, string& result) {
    using namespace std;
    ifstream file(filename);  // ���ļ�
    if (!file) {
        cerr << "�޷����ļ�: " << filename << std::endl;  // ����޷����ļ������������Ϣ
        return -1;
    }
    int lineNumber = 0;
    int charCount = 0;
    string line;
    bool inMultilineComment = false;  // ����Ƿ��ڶ���ע����
    while (std::getline(file, line)) {  // ���ж�ȡ�ļ�
        charCount += line.size() + 1;
        lineNumber++;  // �кŵ���
        if (charCount > n)break;
    }
    if (charCount < n) {
        std::cerr << "�ļ����ַ��������� " << n << std::endl;  // ����ļ��е��ַ����������� n�����������Ϣ
        return -1;
    }
    return lineNumber;
}

bool lexical_analyzer::analyze() {
    string input_string;
    string string_current;
    //����һ����
    while (!input_file.eof()) {
        getline(input_file, string_current);
        input_string += string_current + "\n";
    }
    string word;
    Token token = INVALID_TOKEN;
    int i = 0;
    while (i < input_string.size()) {
        char c = input_string[i];
        //�����ǰ������ǿ��ַ������Բ�����
        if (input_string[i] < 0 || input_string[i]>127) {
            string w;
            cout << "��" << findNthCharLine(in, i + 1, w) << "�У��ַ���\"" << word << "\"" << "����һ���Ƿ��ַ���";
            return false;
        }
        else if (isspace(c)) {
            i++;
            continue;
        }
        word.clear();
        token = INVALID_TOKEN;
        //�����ǰ�ַ���'/'���ж��Ƿ���ע��
        if (i < input_string.size() && input_string[i] == '/' && input_string[i + 1] == '/') {
            while (input_string[i] != '\n')i++;
            i++;
            continue;
        }
        if (i < input_string.size() && input_string[i] == '/' && input_string[i + 1] == '*') {
            while (i < input_string.size() && !(input_string[i] == '*' && input_string[i + 1] == '/'))
                i++;
            i += 2;
            continue;
        }
        if (find_bool(input_string, i) != "") {
            string c = find_bool(input_string, i);
            word += c;
            i += c.length();
            token = get_bool(c);
        }
        //�����ǰ�ַ�����ĸ
        else if (isalpha(c)) {
            //���Ϊ��ĸ�����־�ȫ������
            while (i < input_string.size() && isalnum(input_string[i])) {
                word += input_string[i];
                i++;
            }
            token = get_keyword(word);
            if (token == IDENTIFIER) {
                token = IDENTIFIER;
            }
        }
        else if (isdigit(c)) {
            while (i < input_string.size() && isdigit(input_string[i])) {
                word += input_string[i];
                i++;
                if (input_string[i] < 0 || input_string[i]>127) {
                    string a;
                    cout << "��" << findNthCharLine(in, i, a) << "��" << "���ִ�" << word << endl << "����һ���Ƿ��ַ�,��������﷨";
                    return false;
                }
            }
            token = get_number(word);
        }
        else if (find_operator(input_string, i) != "") {
            string c = find_operator(input_string, i);
            word += c;
            i += c.length();
            token = get_operator(c);
        }
        else if (find_separator(input_string, i) != "") {
            string c = find_separator(input_string, i);
            word += c;
            i += c.length();
            token = get_separator(c);
        }

        else {

            word += input_string[i];
            string a;
            cout << "��" << findNthCharLine(in, i, a) << "��" << "���ַ�: " << word << endl << "��һ���Ƿ��ַ�,��������﷨";
            return false;
            // ��Ч�ַ�
        }
        if (token != INVALID_TOKEN) {
            write_token(token, word);
        }
    }
    return true;

}
