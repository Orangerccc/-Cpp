/*** 
 * @Author: zqc
 * @Date: 2022-05-31 20:41:37
 * @LastEditTime: 2022-06-01 15:23:41
 * @LastEditors: zqc
 * @Description: zqc's file configuration
 * @FilePath: \vscpp\HeiMa\include\v1-manage.h
 * @version: 1.0
 */
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"v1-identity.h"
#include"v1-student.h"
#include"v1-teacher.h"
#include"v1-computer.h"
class Manage: public Identity
{
public:
    Manage();
    Manage(string name, string pwd);

    virtual void openMenu();

    void addPerson();

    void showPerson();

    void showComputer();

    void cleanFile();
    // 初始化容器
    void initVector();
    //检测重复
    bool checkRepeat(int id, int type);
    vector<Student> vStu;
    vector<Teacher> vTea;
    vector<computer> vCom;
};