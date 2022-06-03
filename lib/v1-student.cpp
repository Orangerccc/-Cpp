/*** 
 * @Author: zqc
 * @Date: 2022-05-31 20:34:27
 * @LastEditTime: 2022-06-01 20:39:33
 * @LastEditors: zqc
 * @Description: zqc's file configuration
 * @FilePath: \vscpp\HeiMa\lib\v1-student.cpp
 * @version: 1.0
 */
#include<iostream>
#include<fstream>
using namespace std;
#include"v1-student.h"
#include"v1-globalFile.h"
#include"v1-order.h"
    Student::Student()
    {

    }
    Student::Student(int id, string name , string pwd)
    {
        this->m_Id = id;
        this->m_Name = name;
        this->m_Pwd = pwd;

        //初始化机房信息
        ifstream ifs;
        ifs.open(COMPUTER_FILE,ios::in);
        if(!ifs.is_open())
        {
            cout << "学生处读取机房信息失败！" << endl;
            return;
        }
        computer c;
        while(ifs >> c.m_comid && ifs >> c.m_maxnum)
        {
            vCom.push_back(c);
        }

        ifs.close();
    }

    void Student::openMenu()
    {
        cout << "欢迎学生:" << this->m_Name << "登陆！" << endl;
        cout <<"\t\t------------------------\n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      1.申请预约        \n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      2.查看我的预约     \n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      3.查看所有预约     \n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      4.取消预约         \n";
        cout <<"\t\t                        \n";
        cout <<"\t\t      0.注销登陆         \n";
        cout <<"\t\t------------------------\n";
        cout <<"请选择您的操作:" << endl;
    }

    void Student::applyorder() //申请预约
    {
        cout << "机房开放时间周一至周五" << endl;
        cout << "请输入申请预约时间" << endl;
        cout << "1. 周一" << endl;
        cout << "2. 周二" << endl;
        cout << "3. 周三" << endl;
        cout << "4. 周四" << endl;
        cout << "5. 周五" << endl;
        int date = 0, interval = 0, room = 0;

        while (true)
        {
            cin >> date;
            if(date >= 1 && date <= 5)
            {
                break;
            }
            cout << "输入日期有误,请重新输入！" << endl;
        }

        cout << "请输入申请预约时间段" << endl;
        cout << "1. 上午" << endl;
        cout << "2. 下午" << endl;

        while (true)
        {
            cin >> interval;
            if(interval >= 1 && interval <= 2)
            {
                break;
            }
            cout << "输入时间段有误,请重新输入！" << endl;
        }

        cout << "请选择机房:" << endl;
        for(int i = 0; i < vCom.size(); i++)
        {
            cout << vCom[i].m_comid << " 号机房容量为： "   << vCom[i].m_maxnum << endl;
        }
        while(true)
        {
            cin >> room;
            if(room >= 1 && room <= vCom.size())
            {
                break;
            }
            cout << "输入机房号有误,请重新输入！" << endl;
        }

        cout << "预约成功,等待审核!" << endl;
        ofstream ofs;

        ofs.open(ORDER_FILE, ios::out | ios::app);

        ofs << "date:" << date << " ";
        ofs << "interval:" << interval << " ";
        ofs << "stuId:" << this->m_Id << " ";
        ofs << "stuName:" << this->m_Name << " ";
        ofs << "room:" << room << " ";
        ofs << "status:" << 1 << endl;

        ofs.close();

        system("pause");
        system("cls");
    }

    void Student::showMyorder()
    {
        order of;
        if(of.m_Size == 0)
        {
            cout << "无预约记录" << endl;
            system("pause");
            system("cls");
            return;
        }

        for(int i = 0;i < of.m_Size; i++)
        {
            if(stoi(of.m_order_Data[i]["stuId"]) == this->m_Id)
            {
                cout << "预约时间: 周" << of.m_order_Data[i]["date"];
                cout << " 时段: " << (of.m_order_Data[i]["interval"] == "1"? "上午": "下午");
                cout <<" 机房 " << of.m_order_Data[i]["room"];
                cout <<" 学号 " << of.m_order_Data[i]["stuId"];
                cout <<" 姓名 " << of.m_order_Data[i]["stuName"];
                string status = " 状态： ";
                if(of.m_order_Data[i]["status"] == "1")
                {
                    status += "审核中";
                }else if(of.m_order_Data[i]["status"] == "2")
                {
                    status += "预约成功";
                }else if(of.m_order_Data[i]["status"] == "-1")
                {
                    status += "预约失败";
                }else
                {
                    status += "预约已取消";
                }
                cout << status << endl;
            }
        }
        system("pause");
        system("cls");
    }

    void Student::showAllorder()
    {
        order of;
        if(of.m_Size == 0)
        {
            cout << "无预约记录" << endl;
            system("pause");
            system("cls");
            return;
        }

        for(int i = 0;i < of.m_Size; i++)
        {
            cout << "预约时间: 周" << of.m_order_Data[i]["date"];
            cout << " 时段: " << (of.m_order_Data[i]["interval"] == "1"? "上午": "下午");
            cout <<" 机房 " << of.m_order_Data[i]["room"];
            string status = " 状态： ";
            if(of.m_order_Data[i]["status"] == "1")
            {
                status += "审核中";
            }else if(of.m_order_Data[i]["status"] == "2")
            {
                status += "预约成功";
            }else if(of.m_order_Data[i]["status"] == "-1")
            {
                status += "预约失败";
            }else
            {
                status += "预约已取消";
            }
            cout << status << endl;
        }
        system("pause");
        system("cls");
    }

    void Student::cancelorder()
    {
        order of;
        if(of.m_Size == 0)
        {
            cout << "无预约记录" << endl;
            system("pause");
            system("cls");
            return;
        }

        cout << "已经审核成功或者正在审核中的预约可以被取消 " << endl;

        vector<int> v;
        int index = 1;

        for(int i = 0;i < of.m_Size; i++)
        {
            if(stoi(of.m_order_Data[i]["stuId"]) == this->m_Id)
            {
                if(of.m_order_Data[i]["status"] == "1" || of.m_order_Data[i]["status"]  == "2")
                {
                    v.push_back(i);
                    cout << index++ << "、 ";
                    cout << "预约时间：周" << of.m_order_Data[i]["date"];
                    cout << " 时段 "  << (of.m_order_Data[i]["interval"] == "1"? "上午":"下午");

                    cout <<" 机房 " << of.m_order_Data[i]["room"];
                    string status = " 状态: "; //
                    if(of.m_order_Data[i]["status"] == "1")
                    {
                        status += "审核中";
                    }else if(of.m_order_Data[i]["status"] == "2")
                    {
                        status += "预约成功";
                    }
                    cout << status << endl;
                }
            }
        }

        cout << "请输入取消的记录, 0代表返回" << endl;
        int select = 0;
        while(true)
        {
            cin >> select;

            if(select >= 0 && select <= v.size())
            {
                if(select == 0) break;
                else
                {
                    of.m_order_Data[v[select - 1]] ["status"] = "0";
                    of.updateorder();
                    cout << "已取消预约" << endl;
                    break;
                }
            }
            cout << "输入有误,请重新输入" << endl;
        } 
        system("pause");
        system("cls");
    }