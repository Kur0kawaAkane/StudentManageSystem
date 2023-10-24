#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

typedef struct term
{
    double chinese;//语文成绩
    double math;//数学成绩	
    double english;//英语成绩
    double average_score; //平均成绩

} termscore; //每学期成绩信息




typedef struct Student 
{
    char name[30];//姓名
    int _class;//班级
    termscore score[10];//成绩信息

} Student;//学生信息结点


typedef struct Node 
{
    Student stu;
    struct Node* next;                
} LNode;//定义链表结点类型

void welcome();//欢迎界面输出
void input_1();//输入学生姓名、班级
void input_2();//按学期、班级录入学生成绩
void SaveData();//退出系统并保存
void ReadData();//读取学生数据
LNode* SearchStudent(); //查找学生
void SearchStudentScore();//查询并输出学生成绩单
void ModifyStudentScore();////修改学生成绩
void SortScore();//按班级平均分对学生成绩排序
void PrintScore_1();//按班级输出学生的成绩单
void PrintScore_2();//按科目输出不及格学生的成绩单
