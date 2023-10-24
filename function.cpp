#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include"StudentManagerSystem.h"

LNode* HeadNode = NULL;//定义头节点
//欢迎界面输出
void welcome()

{

    printf("\t请选择操作\t\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("\t1.输入学生姓名，班级\t\n");
    printf("\n\t2.按学期，班级录入学生成绩\t\n");
    printf("\n\t3.修改学生成绩\t\n");
    printf("\n\t4.按班级平均分对学生成绩排序\t\n");
    printf("\n\t5.按班级输出学生的成绩单\t\n");
    printf("\n\t6.按科目输出不及格学生的成绩单\t\n");
    printf("\n\t7.查询学生成绩单\t\n");
    printf("\n\t8.保存并退出系统\t\n");
}

//输入学生姓名、班级
void input_1()
{
    LNode* newNode;
    newNode = (LNode*)malloc(sizeof(LNode));//创建一个新结点
    newNode->next = NULL;//初始化新结点

    if (HeadNode == NULL)
    {
        HeadNode = newNode;
    }
    else
    {
        newNode->next = HeadNode;
        HeadNode = newNode;

    } //头尾插法录入学生信息
    printf("\n请输入学生姓名\n");
    cin >> newNode->stu.name;
    printf("\n请输入学生班级\n");
    cin >> newNode->stu._class;
    printf("学生信息录入成功！\n");
    system("pause");
    system("cls");
}

//按学期、班级录入学生成绩
void input_2()
{
    int _term;
    int _Class;
    printf("请输入学期：\n");
    cin >> _term;
    printf("请输入班级：\n");
    cin >> _Class;
    LNode* p = HeadNode;
    while (p != NULL)
    {
        if (p->stu._class == _Class)
        {

            printf("\n请输入%s的语文成绩：\n", p->stu.name);
            cin >> p->stu.score[_term].chinese;
            printf("\n请输入%s的数学成绩：\n", p->stu.name);
            cin >> p->stu.score[_term].math;
            printf("\n请输入%s的英语成绩：\n", p->stu.name);
            cin >> p->stu.score[_term].english;
            p->stu.score[_term].average_score = ((p->stu.score[_term].chinese) + (p->stu.score[_term].math) + (p->stu.score[_term].english)) / 3;
            printf("\n信息录入完成！\n");
            p = p->next;
            system("pause");
            system("cls");
            welcome();
        }
        else
            p = p->next;
    }
    printf("\n班级成绩录入完成！\n");
    system("pause");
    system("cls");
}

//退出系统并保存数据
void SaveData()
{
    //打开文件
    FILE* fp = fopen("E:\\stuinfo.data", "w");

    if (fp == NULL)
    {

        printf("\n打开文件失败\n");
        return;
    }
    //遍历链表
    LNode* p = HeadNode;
    while (p != NULL)
    {

        fwrite(&p->stu, 1, sizeof(Student), fp);
        p = p->next;
    }

    //关闭文件
    fclose(fp);
    printf("\n保存成功!\n");
}

//读取学生数据
void ReadData()
{
    //打开文件

    FILE* fp = fopen("E:\\stuinfo.data", "r");
    if (fp == NULL)
    {


        return;
    }

    //读文件

    Student stu;
    while (fread(&stu, 1, sizeof(Student), fp))
    {
        LNode* newNode = (LNode*)malloc(sizeof(LNode));

        newNode->next = NULL;
        memcpy(newNode, &stu, sizeof(Student));
        //头插法
        if (HeadNode == NULL)
        {
            HeadNode = newNode;
        }
        else
        {
            newNode->next = HeadNode;
            HeadNode = newNode;
        }
    }
    //关闭文件

    fclose(fp);

    system("cls");
}

//查询并输出学生成绩单
void SearchStudentScore()
{
    LNode* p = SearchStudent();
    int Term;
    cout << "\n请输入学期：\n";
    cin >> Term;
    if (p != NULL)
    {
        printf("\n%s第%d学期的成绩单如下：\n\n", p->stu.name, Term);
        printf("\t语文\t数学\t英语\n");
        printf("\t%.1f\t%.1f\t%.1f\t\n\n", p->stu.score[Term].chinese, p->stu.score[Term].math, p->stu.score[Term].english);
        system("pause");
        system("cls");
    }
    else
    {
        printf("\n没有找到该学生信息！\n");
        system("pause");
        system("cls");
    }
}

//修改学生成绩
void ModifyStudentScore()
{

    LNode* p = SearchStudent(); //查找对应学生
    if (p != NULL)
    {
        int Term;
        cout << "\n请输入学期：\n";
        cin >> Term;
        printf("%s修改前成绩为：\n", p->stu.name);
        printf("\t\t\t语文\t数学\t英语\n\n");
        printf("\t\t\t%.1f\t%.1f\t%.1f\n\n", p->stu.score[Term].chinese, p->stu.score[Term].math, p->stu.score[Term].english);
        printf("\n请输入您要修改的成绩\n");
        printf("\n1.语文\n2.数学\n3.英语\n4.返回到主菜单\n");
        char _ch = _getch();
        switch (_ch)
        {
        case '1': //修改语文成绩
        {
            printf("请输入%s修改后的语文成绩：\n", p->stu.name);
            cin >> p->stu.score[Term].chinese;
            p->stu.score[Term].average_score = ((p->stu.score[Term].chinese) + (p->stu.score[Term].math) + (p->stu.score[Term].english)) / 3;
            printf("\n修改成功！\n");
            system("pause");
            system("cls");
            break;
        }

        case '2': //修改数学成绩
        {

            printf("请输入%s修改后的数学成绩：\n", p->stu.name);
            cin >> p->stu.score[Term].math;
            p->stu.score[Term].average_score = ((p->stu.score[Term].chinese) + (p->stu.score[Term].math) + (p->stu.score[Term].english)) / 3;
            printf("\n修改成功！\n");
            system("pause");
            system("cls");
            break;
        }

        case '3': //修改英语成绩
        {
            printf("请输入%s修改后的英语成绩：\n", p->stu.name);
            cin >> p->stu.score[Term].english;
            p->stu.score[Term].average_score = ((p->stu.score[Term].chinese) + (p->stu.score[Term].math) + (p->stu.score[Term].english)) / 3;
            printf("\n修改成功！\n");
            system("pause");
            system("cls");
            break;
        }
        case '4': //返回上一步
        {
            system("cls");
            break;
        }

        default: //输入有误
        {
            printf("\n输入信息有误！\n");
            system("pause");
            system("cls");
            break;
        }
        }
    }
    else
    {
        printf("\n输入信息有误！\n");
        system("pause");
        system("cls");
    }
}

//按班级平均分对学生成绩排序
void SortScore()
{
    int Term, _class;
    cout << "\n请输入学期：\n";
    cin >> Term;
    cout << "\n请输入班级：\n";
    cin >> _class;
    LNode* mylist = (LNode*)malloc(sizeof(LNode));
    mylist->next = HeadNode;
    //插入排序算法
    {

        if ((mylist->next == NULL) || (mylist->next->next == NULL))
        {
            return;
        }

        LNode* head, * p1, * prep1, * p2, * prep2, * temp;
        head = mylist;
        prep1 = head->next;
        p1 = prep1->next;
        // prep1和p1是否需要手动后移
        bool flag;

        while (p1 != NULL)
        {
            flag = true;
            temp = p1;
            //由于是单向链表，所以只能从头部开始检索
            for (prep2 = head, p2 = prep2->next; p2 != p1; prep2 = prep2->next, p2 = p2->next)
            {
                //发现第一个较大值
                if (p2->stu.score[Term].average_score < p1->stu.score[Term].average_score)
                {
                    p1 = p1->next;
                    prep1->next = p1;
                    prep2->next = temp;
                    temp->next = p2;
                    flag = false;
                    break;
                }
            }
            //手动后移prep1和p1
            if (flag)
            {
                prep1 = prep1->next;
                p1 = p1->next;
            }
        }
    }

    HeadNode = mylist->next;
    //输出成绩单
    {
        LNode* p = mylist->next;
        printf("\n排序后%d班第%d学期成绩单如下：\n\n", _class, Term);
        printf("\t\t\t姓名         \t语文\t数学\t英语\t平均分\n\n");
        while (p != NULL)
        {
            if (p->stu._class == _class)
            {
                printf("\t\t\t%-10s\t%.1f\t%.1f\t%.1f\t%.1f\n\n", p->stu.name, p->stu.score[Term].chinese, p->stu.score[Term].math, p->stu.score[Term].english, p->stu.score[Term].average_score);
            }
            p = p->next;
        }
    }
    system("pause");
    system("cls");
}

//按班级输出学生的成绩单
void PrintScore_1()
{
    LNode* p = HeadNode;
    int Term, class_;
    cout << "\n请输入学期：\n";
    cin >> Term;
    cout << "\n请输入班级：\n";
    cin >> class_;
    printf("\n第%d学期%d班的成绩单如下:\n\n", Term, class_);
    printf("\t\t\t姓名         \t语文\t数学\t英语\t平均分\n\n");
    while (p != NULL)
    {
        if (p->stu._class == class_)
        {
            printf("\t\t\t%-10s\t%.1f\t%.1f\t%.1f\t%.1f\n\n", p->stu.name, p->stu.score[Term].chinese, p->stu.score[Term].math, p->stu.score[Term].english, p->stu.score[Term].average_score);
            p = p->next;
        }
        else
            p = p->next;
    }

    system("pause");
    system("cls");
}

//按科目输出不及格学生的成绩单
void PrintScore_2()
{
    LNode* p = HeadNode;
    int Term;
    cout << "\n请输入学期：\n";
    cin >> Term;
    printf("\n请输入您要查看的科目\n");
    printf("\n1.语文\n2.数学\n3.英语\n4.返回到主菜单\n");
    char ch_ = _getch();
    switch (ch_)
    {
    case '1': //查看语文成绩
    {
        printf("\n第%d学期语文不及格成绩单如下：\n\n", Term);
        printf("\t\t\t姓名         \t成绩\n\n");
        while (p != NULL)
        {

            if (p->stu.score[Term].chinese < 60)
                printf("\t\t\t%-10s\t%.1f\n\n", p->stu.name, p->stu.score[Term].chinese);
            p = p->next;
        }

        break;
    }

    case '2': //查看数学成绩
    {
        printf("\n第%d学期数学不及格成绩单如下：\n\n", Term);
        printf("\t\t\t姓名         \t成绩\n\n");
        while (p != NULL)
        {

            if (p->stu.score[Term].math < 60)
                printf("\t\t\t%-10s\t%.1f\n\n", p->stu.name, p->stu.score[Term].math);
            p = p->next;
        }

        break;
    }

    case '3': //查看英语成绩
    {
        printf("\n第%d学期英语不及格成绩单如下：\n\n", Term);
        printf("\t\t\t姓名         \t成绩\n\n");
        while (p != NULL)
        {

            if (p->stu.score[Term].english < 60)
                printf("\t\t\t%-10s\t%.1f\n\n", p->stu.name, p->stu.score[Term].english);
            p = p->next;
        }

        break;
    }
    case '4': //返回上一步
    {
        system("cls");
        return;
    }

    default: //输入有误
    {
        printf("\n输入信息有误！\n");
        system("pause");
        system("cls");
        return;
    }
    }
    system("pause");
    system("cls");
}

//查找学生
LNode* SearchStudent()
{
    char SearchName[30];
    printf("\n请输入学生的姓名\n");
    cin >> SearchName;
    LNode* p = HeadNode;
    while (p != NULL)
    {
        if (!strcmp(SearchName, p->stu.name))
            return p;
        p = p->next;
    }

    return NULL;
}
