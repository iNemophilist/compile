#pragma once
#include"Parser.h"
#include <iostream>
#include <string>
#include <fstream>
#include<vector>
#include<utility>
using namespace std;
ofstream outputFile;
ifstream inputFile;
void processPROG(TreeNode* node);
void processPROG(TreeNode* node);
void processDECLS(TreeNode* node);
void processDECLS_(TreeNode* node);
void processDECL(TreeNode* node);
vector<string> processNAMES(TreeNode* node);
vector<string> processNAMES_(TreeNode* node);
void processSTMTS(TreeNode* node);
void processSTMTS_(TreeNode* node);
void processSTMT(TreeNode* node);
void processSTMT_(TreeNode* root, string varName);
void processIfStmt(TreeNode* node);
void processELSESTMT(TreeNode* node);
void processWhileStmt(TreeNode* node);
void processReadStmt(TreeNode* node);
void processWriteStmt(TreeNode* node);
void processEXPR(TreeNode* node);
void processADD_(TreeNode* node);
void processTERM(TreeNode* node);
void processMUL_(TreeNode* node);
void processNEGA(TreeNode* node);
void processFACTOR(TreeNode* node);
void processBOOL(TreeNode* node);
void processBOOL_(TreeNode* node);
void processJOIN(TreeNode* node);
void processJOIN_(TreeNode* node);
void processNOT(TreeNode* node);
void processREL(TreeNode* node);
//������ű�
vector<pair<pair<string,string>,int>>symboltable;
int label_id = 0;
int getlabel_id() {
    return label_id++;
}
void emit(string instruction) {
    outputFile << "\t" << instruction << endl;
}
void int_stack_init() {
    emit("#intջ��ʼ��,t8Ϊintջָ��");
    emit("la $t8, int_stack");
    emit("addiu $t8, $t8, 508");
}
//t1��ջ
void int_stack_push() {
    emit("#t1��ջ");
    emit("addiu $t8, $t8, -4");
    emit("sw $t1, 0($t8)");
}
//int��ջ
void int_stack_pop_1() {
    emit("#��ջ��t1");
    emit("lw $t1, 0($t8)");
    emit("addiu $t8, $t8, 4");
}
void int_stack_pop_1_2() {
    emit("#��ջ��t1��t2");
    emit("lw $t1, 0($t8)");
    emit("addiu $t8, $t8, 4");
    emit("lw $t2, 0($t8)");
    emit("addiu $t8, $t8, 4");
}
void bool_stack_init() {
    emit("#boolջ��ʼ��");
    emit("la $t9, bool_stack");
    emit("addiu $t9, $t9, 127");
}
void bool_stack_push_1() {
    emit("#t1��ջ");
    emit("addiu $t9, $t9, -1");
    emit("sb $t1, 0($t9)");
}
void bool_stack_pop_1() {
    emit("#��ջ��t1");
    emit("lb $t1, 0($t9)");
    emit("addiu $t9, $t9, 1");
}
void bool_stack_pop_1_2() {
    emit("#��ջ��t1��t2");
    emit("lb $t1, 0($t9)");
    emit("addiu $t9, $t9, 1");
    emit("lb $t2, 0($t9)");
    emit("addiu $t9, $t9, 1");
}
void processPROG(TreeNode* node) {
    outputFile.open("final_result.txt");
    if (node->val.first == "PROG") {
        // ���������Ŀ�ͷ����
        emit(".data");
        emit("input_stack:.space 1024");
        emit("input_buffer: .word 0");
        emit("int_stack:  .word 128");
        emit("bool_stack:  .byte 128 ");
        emit(".text\n");
        emit(".globl main\n");
        emit("main:");
        //��ʼ��ջ
        emit("#��ʼ��ջ");
        int_stack_init();
        bool_stack_init();
        // ����DECLS��STMTS�ڵ�
        if (node->N2 != nullptr) processDECLS(node->N2);
        if (node->N3 != nullptr) processSTMTS(node->N3);
        // ���������Ľ�β����
        emit("li $v0, 10\n");
        emit("syscall\n");

    }
    outputFile.close();
    inputFile.open("final_result.txt");
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();
    outputFile.open("final_result.txt");
    for (int i = 0; i < 5; i++) {
        emit(lines[i]);
    }
    for (int i = 0; i < symboltable.size(); i++) {
        if (symboltable[i].first.second == "int")
            emit("\t"+symboltable[i].first.first + ": .word 0");
        else
            emit("\t"+symboltable[i].first.first + ": .byte 0");
    }
    for (int i = 5; i < lines.size(); i++) {
        emit(lines[i]);
    }
    outputFile.close();
}   
    void processDECLS(TreeNode * node) {
        if (node == nullptr) {
            return; // ����ڵ�Ϊ�գ���ֱ�ӷ���
        }
        // �����Ϊ�գ������һ��DECL�ڵ�
        processDECL(node->N1);
        // ���������DECLS'�ڵ�
        processDECLS_(node->N2);
    }

    void processDECLS_(TreeNode * node) {
        if ((node == nullptr)||node->N1->val.first=="empty") {
            return; // ����ڵ�Ϊ�գ���ֱ�ӷ���
        }
        // �����Ϊ�գ�����DECL�ڵ�
        processDECL(node->N1);
        // ���������DECLS'�ڵ�
        processDECLS_(node->N2);
    }
    void processDECL(TreeNode* node) {
        if (node == nullptr) {
            return; // ����ڵ�Ϊ�գ���ֱ�ӷ���
        }
        // ��node��val��ȡ����
        string type = node->N1->val.first;
        // ����NAMES�ڵ㣬�����ر������б�
        vector<string> varNames = processNAMES(node->N2);
        pair<string, string> cur;
        // ����ÿ������������ӵ����ű���
        for (const string& varName : varNames) {
            // �ڷ��ű�����ӱ�����������
            cur.first = varName;
            cur.second = type;
            symboltable.push_back(make_pair(cur,-1));

        }
    }
    vector<string> processNAMES(TreeNode* node) {
        vector<string> varNames;
        if (node == nullptr) {
            return varNames;
        }

        // ����NAME�ڵ�
        string varName = node->N1->N1->N1->val .second;
        varNames.push_back(varName);

        // �ݹ鴦��NAMES'�ڵ�
        vector<string> otherNames = processNAMES_(node->N2);
        varNames.insert(varNames.end(), otherNames.begin(), otherNames.end());
        return varNames;
    }

    vector<string> processNAMES_(TreeNode* node) {
        vector<string> varNames;
        if (node == nullptr|| node->N1->val.first == "empty") {
            return varNames;
        }
        // ����NAME�ڵ�
        string varName = node->N2->N1->N1->val.second;
        varNames.push_back(varName);
        // �ݹ鴦��NAMES'�ڵ�
        vector<string> otherNames = processNAMES_(node->N3);
        varNames.insert(varNames.end(), otherNames.begin(), otherNames.end());
        return varNames;
    }
    void processSTMTS(TreeNode* node) {
        if (node == nullptr || node->N1->val.first == "empty") {
            return;
        }
        // ����STMT�ڵ�
        processSTMT(node->N1);
        // �ݹ鴦��STMTS'�ڵ�
        processSTMTS_(node->N2);
    }

    void processSTMTS_(TreeNode* node) {
        if (node == nullptr || node->N1->val.first == "empty") {
            return;
        }
        // ����STMT�ڵ�
        processSTMT(node->N1);
        // �ݹ鴦��STMTS'�ڵ�
        processSTMTS_(node->N2);
    }
    void processSTMT(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        if (node->N1->val.first == "id") {  // ���ݽڵ���ӽڵ��������ض���ʶ���жϽڵ�����
            // id STMT'
            string varName = node->N1->N1->val.second; // ��ȡ������
            processSTMT_(node->N2, varName);
        }
        else if (node->N1->val.first == "if") {
            // if id then STMT ELSESTMT
            processIfStmt(node);
        }
        else if (node->N1->val.first == "while") {
            // while id do STMT
            processWhileStmt(node);
        }
        else if (node->N1->val.first == "read") {
            // read id ;
            processReadStmt(node);
        }
        else if (node->N1->val.first == "write") {
            // write id ;
            processWriteStmt(node);
        }
        else if (node->N1->val.first == "{") {
            // { STMTS }
            processSTMTS(node->N2);
        }
    }
        void processSTMT_(TreeNode* root, string varName) {
            if (root->N1->val.first == "=") {
                processEXPR(root->N2);
                emit("# ��ջ��Ԫ��д��");
                int_stack_pop_1();
                emit("la $t2, "+ varName);   
                emit("sw $t1, 0($t2)");    
               }
            else if (root->N1->val.first == ":=") {
                processBOOL(root->N2);
                emit("# ��ջ��Ԫ��д��");
                bool_stack_pop_1();
                emit("la $t2, " + varName);
                emit("sb $t1, 0($t2)");
            }
            return;
    }
        void processIfStmt(TreeNode* node) {
            string label_else = "else_" + std::to_string(label_id); // ���else����
            string label_end = "endif_" + std::to_string(label_id); // ���if-else������
            label_id++; // ���±�ǩ���
            // �������������ص�$t0�Ĵ���
            string id_type;
            string id_name = node->N2->N1->val.second;
            for (int i = 0; i < symboltable.size(); i++) {
                if (symboltable[i].first.first == id_name) {
                    id_type = symboltable[i].first.second;
                    break;
                }
            }
            if(id_type=="int")
            emit("lw $t0, " + id_name);
            else
                emit("lb $t0, " + id_name);
            // ����������ת��else�������if����
            emit("beqz $t0, " + label_else); // �������Ϊ�٣�����ת��else����
            processSTMT(node->N4); // ����if����Ĵ���
            emit("j " + label_end); // ��������ת��if-else������
            emit(label_else + ":"); // ����else����ı�ǩ
            processELSESTMT(node->N5); // �������else��䣬����Ҫ������ת��if�������Ĵ���
            emit(label_end + ":"); // ����if-else�������ı�ǩ
        }

        void processELSESTMT(TreeNode* node) {
            if (node == nullptr || node->N1->val.first == "empty")
                return;
            else
                processSTMT(node->N2);
        }
        void processWhileStmt(TreeNode* node) {
            std::string loopLabel = "loop" + std::to_string(label_id); // ѭ����ʼλ�õı�ǩ
            std::string endLoopLabel = "endloop" + std::to_string(label_id); // ѭ������λ�õı�ǩ
            label_id++; // ���±�ǩ���
            // ����ѭ���������ֵĴ���
            string id_type;
            string id_name = node->N2->N1->val.second;
            for (int i = 0; i < symboltable.size(); i++) {
                if (symboltable[i].first.first == id_name) {
                    id_type = symboltable[i].first.second;
                    break;
                }
            }
            emit(loopLabel + ":"); // ����ѭ����ʼλ�õı�ǩ
            // ����ѭ�������жϲ��ֵĴ���
            if (id_type == "int")
                emit("lw $t0, " + id_name);
            else
                emit("lb $t0, " + id_name);
            emit("beqz $t0, " + endLoopLabel); // �������Ϊ�٣�������ѭ��
            // ����ѭ���岿�ֵĴ���
            processSTMT(node->N4);
            emit("j " + loopLabel); // ����ѭ����ʼλ��
            emit(endLoopLabel + ":"); // ����ѭ������λ�õı�ǩ
        }

        void processReadStmt(TreeNode* node) {
            string id_name = node->N2->N1->val.second;
            string id_type;

            for (int i = 0; i < symboltable.size(); i++) {
                if (symboltable[i].first.first == id_name) {
                    id_type = symboltable[i].first.second;
                }
            }

            // ��ʼ�������������� buffer ��һ���Ѿ������˿ռ���ַ�����
            emit("# ����");
            emit("la $t0, input_stack");
            emit("addiu $t0, $t0, 1024");
            emit("sw $t0, input_buffer");

            if (id_type == "int") {
                // ϵͳ����5���ڶ�ȡһ������
                emit("li $v0, 5");
                emit("syscall");
                emit("sw $v0, " + id_name); // ����ȡ���������浽������
            }
            else {
                // ϵͳ����8���ڶ�ȡһ���ַ���
                emit("li $v0, 8");
                emit("syscall");
                string set_true = "set_true" + std::to_string(label_id);
                string end_set = "end_set" + std::to_string(label_id);
                string set_false = "set_false" + std::to_string(label_id);
                label_id++;
                // ����ַ��������ַ��Ƿ�Ϊ't'��'T'
                emit("lb $t0, 0($a0)"); // ��ȡ��һ���ַ�
                emit("li $t1, 't'"); // �� 't' ���뵽 $t1 �Ĵ���
                emit("li $t2, 'T'"); // �� 'T' ���뵽 $t2 �Ĵ���
                emit("beq $t0, $t1, "+set_true); // ����ַ����� 't'����ת�� set_true ��ǩ
                emit("beq $t0, $t2, "+set_true); // ����ַ����� 'T'����ת�� set_true ��ǩ
                emit("j "+set_false); // ����ַ��Ȳ����� 't' Ҳ������ 'T'����ת�� set_false ��ǩ
                emit(set_true+":"); // set_true ��ǩ
                emit("li $t0, 1"); // ����ַ�����"true"�����ñ���Ϊ1
                emit("j "+end_set); // ��ת�� end_set ��ǩ
                emit(set_false+":"); // set_false ��ǩ
                emit("li $t0, 0"); // ����ַ�������"true"�����ñ���Ϊ0
                emit(end_set+":"); // end_set ��ǩ
                emit("sw $t0, " + id_name); // ��������浽������
            }
        }
        void processWriteStmt(TreeNode* node) {
            string id_type;
            string id_name = node->N2->N1->val.second;
            //���ҷ��ű���ȷ������
            emit("# ��ӡ");
            for (int i = 0; i < symboltable.size(); i++) {
                if (symboltable[i].first.first == id_name) {
                    id_type = symboltable[i].first.second;
                    break;
                }
            }
            // ������ر������Ĵ��� $t0 ��
            if(id_type=="int")
            emit("lw $t0, " + id_name);
            else
                emit("lb $t0, " + id_name);
            // ����������Ͳ���ֵ�Ĵ���ʽ����������ͬ���������������������֡�
            if (id_type == "int") {
                emit("li $v0, 1"); // ϵͳ���ô���1��ʾ��ӡ����
                emit("move $a0, $t0"); // �ƶ����ǵ������� $a0
                emit("syscall"); // ����ϵͳ����
            }
            else if (id_type == "bool") {
                // ����ֵ���Ա�ʾΪ����0��1��Ҳ����ʹ��ĳ�ִ�ӡ����ֵ�ķ�������
                emit("li $v0, 1"); // ϵͳ���ô���1��ʾ��ӡ����
                emit("move $a0, $t0"); // �ƶ����ǵĲ���ֵ�� $a0
                emit("syscall"); // ����ϵͳ����
            }
        }
        // ������ʽ
        void processEXPR(TreeNode* node) {
            processTERM(node->N1); // ����TERM
            processADD_(node->N2); // ����ADD'
        }

        // ����ADD'���ʽ����Ӧ�ڷ��ս�� ADD' �� ADD TERM ADD'
        // ADD' �� empty
        void processADD_(TreeNode* node) {
            if (node== nullptr||node->N1->val.first=="empty") {
                // ��� ADD' �� empty, �򲻽����κβ���
                return;
            }
            // ���� TERM
            processTERM(node->N2);
            // ��ջ��������Ԫ�س�ջ�������㣬�������ѹ��ջ��
            emit("# ����ȡ����ջ��");
            int_stack_pop_1_2();
            if (node->N1->N1->val.second == "+") {
                emit("# �ӷ�");
                emit("addu $t1, $t1, $t2");
            }
            else {
                emit("# ����");
                emit("subu $t1, $t2, $t1");
            }
            int_stack_push();
            // �������� ADD'
            processADD_(node->N3);
        }

        // ����TERM����Ӧ�ڷ��ս�� TERM �� NEGA MUL'
        void processTERM(TreeNode* node) {
            processNEGA(node->N1); // ����NEGA
            processMUL_(node->N2); // ����MUL'
        }

        // ����MUL'���ʽ����Ӧ�ڷ��ս�� MUL' �� MUL NEGA MUL'
        // MUL' �� empty
        void processMUL_(TreeNode* node) {
            if (node== nullptr||node->N1->val.first=="empty") {
                // ��� MUL' �� empty, �򲻽����κβ���
                return;
            }
            // ���� NEGA
            processNEGA(node->N2);
            // ��ջ��������Ԫ�س�ջ�������㣬�������ѹ��ջ��
            int_stack_pop_1_2();
            if (node->N1->N1->val.second == "*") {
                emit("# �˷�");
                emit("mul $t1, $t1, $t2");
            }
            else {
                emit("# ����");
                emit("div $t1, $t2, $t1");
            }
            emit("# ��ջ��Ԫ��д��");
            int_stack_push();
            // �������� MUL'
            processMUL_(node->N3);
        }


        // ����NEGA����Ӧ�ڷ��ս�� NEGA �� FACTOR
        // NEGA �� - FACTOR
        void processNEGA(TreeNode* node) {
            // Step 1: Process FACTOR
            if (node->N1->val.second == "-") {
                processFACTOR(node->N2); // ���� FACTOR
            }
            else {
                processFACTOR(node->N1); // ���� FACTOR
            }

                        
            // Step 3: If necessary, negate
            if (node->N1->val.second == "-") {
                // Step 2: Int_buffer ��ջ�� $t1
                int_stack_pop_1();
                emit("# ȡ��");
                emit("negu $t1, $t1"); // If it's a negative number, negate the value in $t1
                // Step 4: Push the result back to the Int_num stack
                emit("# д��");
                int_stack_push();
            }
        }


        // ����FACTOR����Ӧ�ڷ��ս�� FACTOR �� ( EXPR )
        // FACTOR �� id
        // FACTOR �� number
        void processFACTOR(TreeNode* node) {
            if (node->N1->val.second == "(") {
                processEXPR(node->N2); // ���FACTOR��һ�����ű��ʽ������EXPR
            }
            else if (node->N1->val.first == "id") {
                string id_name = node->N1->N1->val.second;
                string id_type;

                // Search symbol table
                for (int i = 0; i < symboltable.size(); i++) {
                    if (symboltable[i].first.first == id_name) {
                        id_type = symboltable[i].first.second;
                        break; // Once found, break the loop
                    }
                }
            // Load the address of the top of the stack into $t0
                string cur_num;
                if (id_type == "int") {
                    emit("lw $t1, " + id_name);
                    int_stack_push();
                    }
                    else {
                        emit("lb $t1, " + id_name);
                        bool_stack_push_1();
                    }
                }
         
            else {
                string num_val = node->N1->N1->val.second;
                emit("li $t1, " + num_val);
                int_stack_push();
            }
        }
        // ����BOOL����Ӧ�ڷ��ս�� BOOL �� JOIN BOOL'
        void processBOOL(TreeNode* node) {
            processJOIN(node->N1); // ����JOIN
            processBOOL_(node->N2); // ����BOOL'
        }

        // ����BOOL'���ʽ����Ӧ�ڷ��ս�� BOOL' �� || JOIN BOOL'
        // BOOL' �� empty
        void processBOOL_(TreeNode* node) {
            if (node== nullptr||node->N1->val.first=="empty") {
                return; // �����ǰ�ڵ�Ϊ�գ��򷵻�
            }
            processJOIN(node->N2); // ����JOIN
            processBOOL_(node->N3); // �ݹ鴦��BOOL'
            bool_stack_pop_1_2();
            emit("andi $t1, $t1, 1");
            emit("or $t1, $t1, $t2"); // ִ���߼������
            bool_stack_push_1();
        }

        // ����JOIN����Ӧ�ڷ��ս�� JOIN �� NOT JOIN'
        void processJOIN(TreeNode* node) {
            if (node == nullptr)return;
            processNOT(node->N1); // ����NOT
            processJOIN_(node->N2); // ����JOIN'
        }

        // ����JOIN'���ʽ����Ӧ�ڷ��ս�� JOIN' �� && NOT JOIN'
        // JOIN' �� empty
        void processJOIN_(TreeNode* node) {
            if (node== nullptr||node->N1->val.first=="empty") {
                return; // �����ǰ�ڵ�Ϊ�գ��򷵻�
            }
            processNOT(node->N2); // ����NOT
            processJOIN_(node->N3); // �ݹ鴦��JOIN'
            bool_stack_pop_1_2();
            emit("andi $t1, $t1, 1");
            emit("and $t1, $t1, $t2"); // ִ���߼������
            bool_stack_push_1();
        }

        // ����NOT����Ӧ�ڷ��ս�� NOT �� REL
        // NOT �� ! REL
        void processNOT(TreeNode* node) {
            if (node->N1->val.second == "!") {
                processREL(node->N2); // ����REL
                bool_stack_pop_1();
                emit("andi $t1, $t1, 1");
                emit("xori $t1, $t1, 1"); // ������߼��ǲ������ԼĴ���t0ִ��ȡ������
                bool_stack_push_1();
            }
            else {
                processREL(node->N1); // ����REL
            }
        }

        // ����REL����Ӧ�ڷ��ս�� REL �� EXPR ROP EXPR
        void processREL(TreeNode* node) {
            processEXPR(node->N1); // ����EXPR
            processEXPR(node->N3); // ������һ��EXPR
            int_stack_pop_1_2();
            string operation = node->N2->N1->val.second;
            // ���������������Ӧ�Ļ��ָ��
            if (operation == ">") {
                emit("sgt $t1, $t2, $t1"); // ��Ӧ > ����
            }
            else if (operation == ">=") {
                emit("sge $t1, $t2, $t1"); // ��Ӧ >= ����
            }
            else if (operation == "<") {
                emit("slt $t1, $t2, $t1"); // ��Ӧ < ����
            }
            else if (operation == "<=") {
                emit("sle $t1, $t2, $t1"); // ��Ӧ <= ����
            }
            else if (operation == "==") {
                emit("seq $t1, $t2, $t1"); // ��Ӧ == ����
            }
            else if (operation == "!=") {
                emit("sne $t1, $t2, $t1"); // ��Ӧ != ����
            }
            bool_stack_push_1();
        }






    



