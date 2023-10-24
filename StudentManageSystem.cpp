#include<iostream>
#include"StudentManagerSystem.h"
#include <conio.h>

int main()
{
  


    ReadData(); //载入存储数据

    while (1)
    {

        welcome(); //输出欢迎界面

        char ch = _getch(); //输入需要的功能

        switch (ch)
        {

        case '1': //输入学生姓名、班级
        {
            input_1();
            break;
        }

        case '2': //按学期、班级录入学生成绩
        {
            input_2();
            break;
        }

        case '3': //修改学生成绩
        {
            ModifyStudentScore();
            break;
        }

        case '4': //按班级平均分对学生成绩排序
        {
            SortScore();
            break;
        }

        case '5': //按班级输出学生的成绩单
        {
            PrintScore_1();
            break;
        }

        case '6': //按科目输出不及格学生的成绩单
        {
            PrintScore_2();
            break;
        }

        case '7': //查询并输出学生成绩单
        {
            SearchStudentScore();
            break;
        }

        case '8': //退出系统并保存
        {
            SaveData();
            return 0;
        }

        default: //输入有误
        {
            printf("输入有误!请重新输入!\n");
            system("pause");
            system("cls");
            break;
        }
        }
    }
    return 0;
}

