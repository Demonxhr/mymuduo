#pragma once

//妙啊

class noncopyable
{
public:
    //删除拷贝构造，让后面继承的子类不能拷贝构造
    //子类构造是先调用父类的构造函数,再调用自己的构造函数
    //拷贝构造一样
    noncopyable(const noncopyable&) =delete;
    noncopyable& operator=(const noncopyable&) = delete;
//protected 不能被外部访问，但可以被子类继承，private不能被子类继承。
//所以可以子类可以正常构造
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};