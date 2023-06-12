#include"lexical_analyzer.h"
#include"Parser.h"
#include"getx86.h"
int main() {
    string a = "test.txt";                      //Դ����
    string b = "result.txt";   //�ʷ��������
    string e = "result_parser.txt";             //�﷨�������
    string test = "test_parser_result.txt";     //�����﷨����������¹�����֮���ٽ������л��Ľ��
    Parser d(a, b, e);
    if (d.do_and_write()) { 
        TreeNode* root = d.deserialize(e);//�����л�������
        d.serialize(test, root);                    //���л������л����
        if (file_same(e, test))
            cout << "�����л��ɹ�" << endl;                 //�ж��������л�����Ƿ�һ��
        else
            cout << "�����л�ʧ��" << endl;
        processPROG(root);
    }

    return 0;
}

