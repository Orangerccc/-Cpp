/*** 
 * @Author: zqc
 * @Date: 2022-05-31 20:37:22
 * @LastEditTime: 2022-05-31 21:23:53
 * @LastEditors: zqc
 * @Description: zqc's file configuration
 * @FilePath: \vscpp\HeiMa\include\v1-teacher.h
 * @version: 1.0
 */
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include"v1-identity.h"

class Teacher: public Identity
{
public:
    Teacher();

    Teacher(int empid, string name, string pwd);

    virtual void openMenu();

    void showAllorder();

    void validOrder();

    int m_Empid;

};