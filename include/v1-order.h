/*** 
 * @Author: zqc
 * @Date: 2022-06-01 16:41:04
 * @LastEditTime: 2022-06-01 16:41:04
 * @LastEditors: zqc
 * @Description: zqc's file configuration
 * @FilePath: \vscpp\HeiMa\include\v1-order.h
 * @version: 1.0
 */
#pragma once
#include<iostream>
#include<map>
#include<string>
#include"v1-globalFile.h"
using namespace std;

class order
{
public:
    order();

    void updateorder();

    map<int, map<string, string>> m_order_Data;

    int m_Size; 
};


