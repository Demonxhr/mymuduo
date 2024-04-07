#pragma once

#include <iostream>
#include <string>

class Timestamp
{
public:
    Timestamp();
    //防止类构造函数的隐式转换  如Timestamp aa = 1会隐式调用Timestamp(int64_t microSecondsSinceEpoch)进行构造
    //加上explicit可以避免
    explicit Timestamp(int64_t microSecondsSinceEpoch);
    static Timestamp now();
    std::string toString() const;   //不改变其他类变量
private:
    int64_t microSecondsSinceEpoch_;
};