/*** 
 * @Author: zqc
 * @Date: 2022-05-31 20:28:48
 * @LastEditTime: 2022-05-31 21:09:14
 * @LastEditors: zqc
 * @Description: zqc's file configuration
 * @FilePath: \vscpp\HeiMa\include\v1-identity.h
 * @version: 1.0
 */
#pragma once
#include<iostream>
#include<string>
using namespace std;

class Identity
{
public:
    virtual void openMenu() = 0;
    string m_Name;
    string m_Pwd;
};