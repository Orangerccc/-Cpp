/*** 
 * @Author: zqc
 * @Date: 2022-06-01 16:51:41
 * @LastEditTime: 2022-06-01 20:04:47
 * @LastEditors: zqc
 * @Description: zqc's file configuration
 * @FilePath: \vscpp\HeiMa\lib\v1-order.cpp
 * @version: 1.0
 */
#include"v1-order.h"
#include"v1-globalFile.h"
#include<iostream>
#include<fstream>
using namespace std;

void dealstr(string str, map<string,string> &m)
{
    string key, value;
    int pos = str.find(':');
    if(pos != -1)
    {
        key = str.substr(0, pos);
        value = str.substr(pos + 1);
        m.insert(make_pair(key,value));
    }
}
order::order()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);
    string date, interval, stuId, stuName, room, status;

    this->m_Size = 0;

    while(ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> room && ifs >> status)
    {
        // cout << date << endl;
        // cout << interval << endl;
        // cout <<  stuId  << endl;
        // cout << stuName << endl;
        // cout << room << endl;
        // cout << status << endl;
        // cout << endl;
        map<string,string> m;
        dealstr(date, m);
        dealstr(interval, m);
        dealstr(stuId, m);
        dealstr(stuName, m);
        dealstr(room, m);
        dealstr(status, m);
        
        this->m_order_Data.insert(make_pair(this->m_Size, m));
        this->m_Size++;
    }
    ifs.close();

    // for(auto it = this->m_order_Data.begin(); it != this->m_order_Data.end(); it++)
    // {
    //     cout << it->first << endl;
    //     for(auto itor = it->second.begin(); itor != it->second.end(); itor ++)
    //     {
    //         cout << itor->first << " " << itor->second << endl;
    //     }
    // }
}

void order::updateorder()
{
    if(this->m_Size == 0) return;

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::trunc);

    for(int i = 0; i < this->m_Size ; i++)
    {
        ofs << "date:" << this->m_order_Data[i]["date"] << " ";
        ofs << "interval:" << this->m_order_Data[i]["interval"] << " ";
        ofs << "stuId:" << this->m_order_Data[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_order_Data[i]["stuName"] << " ";
        ofs << "room:" << this->m_order_Data[i]["room"] << " ";
        ofs << "status:" << this->m_order_Data[i]["status"] << endl;
    }
}
