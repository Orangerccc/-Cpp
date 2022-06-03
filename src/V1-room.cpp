/*** 
 * @Author: zqc
 * @Date: 2022-05-31 20:17:59
 * @LastEditTime: 2022-06-01 20:34:47
 * @LastEditors: zqc
 * @Description: zqc's file configuration
 * @FilePath: \vscpp\HeiMa\src\V1-room.cpp
 * @version: 1.0
 */
#include<iostream>
#include"v1-globalFile.h"
#include"v1-identity.h"
#include"v1-student.h"
#include"v1-teacher.h"
#include"v1-manage.h"
#include<fstream>
#include<string>
using namespace std;

//管理员子菜单逻辑
void manageMenu(Identity *& manage)
{
    while(true)
    {
        //管理员菜单
        manage->openMenu();
        
        Manage* man = (Manage*) manage;
        int select = 0 ;
        cin >> select;
        if(select == 1)
        {
            cout << "添加账号" << endl;
            man->addPerson();
        }else if(select == 2)
        {
            cout << "查看账号" << endl;
            man->showPerson();
        }else if(select == 3)
        {
            cout << "查看机房" << endl;
            man->showComputer();
        }else if(select == 4)
        {
            cout << "清空预约" << endl;
            man->cleanFile();
        }else
        {
            delete manage;  //销毁堆区对象
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
//学生子菜单逻辑
void studentMenu(Identity *& student)
{
    while(true)
    {
        //学生菜单
        student->openMenu();
        
        Student* man = (Student*) student;
        int select = 0 ;
        cin >> select;
        if(select == 1)
        {
            cout << "申请预约" << endl;
            man->applyorder();
        }else if(select == 2)
        {
            cout << "查看我的预约" << endl;
            man->showMyorder();
        }else if(select == 3)
        {
            cout << "查看所有预约" << endl;
            man->showAllorder();
        }else if(select == 4)
        {
            cout << "取消预约" << endl;
            man->cancelorder();
        }else
        {
            delete student;  //销毁堆区对象
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//教师子菜单逻辑
void teacherMenu(Identity *& teacher)
{
    while(true)
    {
        //学生菜单
        teacher->openMenu();
        
        Teacher* man = (Teacher*) teacher;
        int select = 0 ;
        cin >> select;
        if(select == 1)
        {
            cout << "查看所有预约" << endl;
            man->showAllorder();
        }else if(select == 2)
        {
            cout << "审核预约" << endl;
            man->validOrder();
        }else
        {
            delete teacher;  //销毁堆区对象
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

void LoginIn(string fileName, int type)
{
    Identity *person = NULL;
    ifstream ifs;
    ifs.open(fileName, ios::in);

    //文件不存在
    if(!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }
    //准备接受用户信息
    int id = 0;
    string name , pwd;
    if(type == 1)
    {
        cout << "请输入你的学号" << endl;
        cin >> id;
    }else if(type == 2)
    {
        cout << "请输入你的职工号" << endl;
        cin >> id;
    }
    cout << "请输入用户名：" << endl;
    cin >> name;
    cout << "请输入密码：" << endl;
    cin >> pwd;

    if(type == 1)
    { //学生验证登陆
        int fId; string fName, fPwd;
        while(ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if(id == fId && name == fName && fPwd == pwd)
            {
                cout << "学生验证登陆成功" << endl;
                system("pause");
                system("cls");
                person = new Student(id, name ,pwd);
                //进入学生操作子菜单
                studentMenu(person);
                
                return ;
            }
        }
    }else if(type == 2)
    { //教师验证登陆
        int fId; string fName, fPwd;
        while(ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if(id == fId && name == fName && fPwd == pwd)
            {
                cout << "教师验证登陆成功" << endl;
                system("pause");
                system("cls");
                person = new Teacher(id, name ,pwd);
                
                //进入教师操作子菜单
                teacherMenu(person);
                return ;
            }
        }
    }else if(type == 3)
    {//管理员验证登陆
        string fName, fPwd;
        while(ifs >> fName && ifs >> fPwd)
        {
            if(name == fName && fPwd == pwd)
            {
                cout << "管理员验证登陆成功" << endl;
                system("pause");
                system("cls");
                person = new Manage(name ,pwd);
                manageMenu(person); 
                //进入管理员操作子菜单
                
                return ;
            }
        }
    }
    cout << "验证登陆失败" << endl;
    system("pause");
    system("cls");
    return;
}


int main()
{
    while(true)
    {
        int select = 0;
        cout << "========== 欢迎来到机房预约系统 =============="  << endl;
        cout << endl << "请输入您的身份 " << endl;
        cout <<"\t\t ------------------------------\n";
        cout <<"\t\t|                             |\n";
        cout <<"\t\t|         1.学生代表          |\n";
        cout <<"\t\t|                             |\n";
        cout <<"\t\t|         2.老师              |\n";
        cout <<"\t\t|                             |\n";
        cout <<"\t\t|         3.管理员            |\n";
        cout <<"\t\t|                             |\n";
        cout <<"\t\t|         0.退出              |\n";
        cout <<"\t\t ------------------------------\n";
        cin >> select;
        switch(select)
        {
            case 1:
                LoginIn(STUDENT_FILE, 1);
                break;
            case 2:
                LoginIn(TEACHER_FILE, 2);
                break;
            case 3:
                LoginIn(ADMIN_FILE, 3);
                break;
            case 0:
                cout << "欢迎下一次使用" << endl;
                system("pause");
                return 0;
                break;
            default:
                cout <<"输入有误,请重新选择！ " << endl;
                system("pause");
                system("cls");
                break;
        }
    }
    return 0;
}