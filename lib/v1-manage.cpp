/*** 
 * @Author: zqc
 * @Date: 2022-05-31 20:43:45
 * @LastEditTime: 2022-06-01 15:41:52
 * @LastEditors: zqc
 * @Description: zqc's file configuration
 * @FilePath: \vscpp\HeiMa\lib\v1-manage.cpp
 * @version: 1.0
 */
#include<iostream>
#include<fstream>
using namespace std;
#include"v1-manage.h"
#include"v1-student.h"
#include"v1-teacher.h"
#include"v1-globalFile.h"
#include"v1-computer.h"
#include<algorithm>

    Manage::Manage()
    {

    }
    Manage::Manage(string name, string pwd)
    {
        this->m_Name = name;
        this->m_Pwd = pwd;

        this->initVector();

        //获取机房信息
        ifstream ifs;
        ifs.open(COMPUTER_FILE, ios::in);
        computer c;
        while(ifs >> c.m_comid && ifs >> c.m_maxnum)
        {
            vCom.push_back(c);
        }
        cout << "当前机房数量为：" << vCom.size() << endl;
        ifs.close();
    }

    void Manage::openMenu()
    {
        cout << "欢迎管理员:" << this->m_Name << "登陆！" << endl;
        cout <<"\t\t------------------------\n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      1.添加账号         \n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      2.查看账号         \n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      3.查看机房         \n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      4.清空预约         \n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      0.注销登陆         \n";
        cout <<"\t\t------------------------\n";
        cout <<"请选择您的操作:" << endl;
    }

    void Manage::addPerson()
    {
        cout << "请输入添加账号的类型" << endl;
        cout << "1、添加学生" << endl;
        cout << "2、添加老师" << endl;

        string fileName;
        string tip, repeattip;
        ofstream ofs;
        
        int select = 0;
        cin >> select;

        if(select == 1)
        {
            fileName = STUDENT_FILE;
            tip = "请输入学号:";
            repeattip = "学号重复,请重新输入";
        }else
        {
            fileName = TEACHER_FILE;
            tip = "请输入教师编号:";
            repeattip = "职工号重复,请重新输入";
        }
        ofs.open(fileName, ios::out| ios::app);
        int id;
        string name;
        string pwd;

        cout << tip << endl;
        while(true)
        {
            cin >> id;
        
            bool ret = checkRepeat(id, select);
            if(ret) cout << repeattip << endl;
            else break;
        }
        cout << "请输入姓名:" << endl;
        cin >> name;

        cout << "请输入密码:" << endl;
        cin >> pwd;

        ofs << id << " "  << name << " " <<pwd << endl;
        cout << "添加成功" << endl;
        system("pause");
        system("cls");
        ofs.close(); 
        //重新调用文件中的所有内容获取
        this->initVector();
    }

    void printStudent(Student &s)
    {
        cout << "学号：" << s.m_Id <<" "<< "姓名：" <<s.m_Name <<" "<< "密码" << s.m_Pwd << endl;
    }
    void printTeacher(Teacher &t)
    {
        cout << "职工号：" << t.m_Empid <<" " << "姓名：" <<t.m_Name <<" " << "密码" << t.m_Pwd << endl;
    }

    void Manage::showPerson()
    {
        cout <<"请选择查看哪类人员信息：" << endl;
        cout <<"查看学生请按1" << endl;
        cout <<"查看教师请按2" << endl;

        int select = 0;
        cin >> select;

        if(select == 1)
        {
            cout << "所有学生信息如下：" << endl;
            for_each(vStu.begin(), vStu.end(), printStudent);
        }else
        {
            cout << "所有教师信息如下：" << endl;
            for_each(vTea.begin(), vTea.end(), printTeacher);
        }
        system("pause");
        system("cls");   
    }

    void Manage::showComputer()
    {
        cout << "机房信息如下：" << endl;
        for(vector<computer>::iterator it = vCom.begin(); it != vCom.end(); it++)
        {
            cout <<"机房编号："  << it->m_comid << " 机器最大容量 " << it->m_maxnum << endl;
        }
        system("pause");
        system("cls");
    }

    void Manage::cleanFile()
    {
        ofstream ofs;
        ofs.open(ORDER_FILE, ios::trunc);

        cout << "预约清除成功!" << endl;
        system("pause");
        system("cls");
    }

    void Manage::initVector()
    {
        ifstream ifs;
        ifs.open(STUDENT_FILE, ios::in);

        if(!ifs.is_open())
        {   
            cout <<"打开学生文件失败" << endl;
            return;
        }

        this->vStu.clear();
        this->vTea.clear();

        Student s;
        while(ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
        {
            vStu.push_back(s);
        }
        // cout << "当前学生数量为:" << vStu.size() << endl; //测试

        ifs.open(TEACHER_FILE, ios:: in);
        if(!ifs.is_open())
        {   
            cout <<"打开教师文件失败" << endl;
            return;
        }
        Teacher t;
        while(ifs >> t.m_Empid && ifs >> t.m_Name && ifs >> t.m_Pwd)
        {
            vTea.push_back(t);
        }
        // cout << "当前教师数量为:" << vTea.size() << endl; //测试

        ifs.close();
    }

    bool Manage::checkRepeat(int id , int type)
    {
        if(type == 1)
        {
            for(vector<Student>::iterator it = vStu.begin(); it  != vStu.end(); it ++)
            {
                if(id == it->m_Id) return true;
            }
        }else
        {
            for(vector<Teacher>::iterator it = vTea.begin(); it  != vTea.end(); it ++)
            {
                if(id == it->m_Empid) return true;
            }
        }
        return false;
    }