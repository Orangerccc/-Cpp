/*** 
 * @Author: zqc
 * @Date: 2022-05-31 20:31:19
 * @LastEditTime: 2022-06-01 16:15:05
 * @LastEditors: zqc
 * @Description: zqc's file configuration
 * @FilePath: \vscpp\HeiMa\include\v1-student.h
 * @version: 1.0
 */
#pragma once
#include<iostream>
#include<string>
#include"v1-identity.h"
#include"v1-computer.h"
#include<vector>

class Student: public Identity
{
public:
    Student();
    Student(int id, string name , string pwd);

    virtual void openMenu();

    void applyorder();

    void showMyorder();

    void showAllorder();

    void cancelorder();

    int m_Id;

    vector<computer> vCom;
};