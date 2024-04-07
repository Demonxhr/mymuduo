#pragma once

#include "noncopyable.h"
//为什么用前置声明 而是包含头文件
//因为handleEvent(Timestamp receiveTime)下面这个成员函数需要确定Timestamp的大小
//EventLoop可以是因为下面只用到了指针，指针大小不变
#include "Timestamp.h"   

#include <functional>
#include <memory>

//头文件前置声明,源文件中该类的放头文件
class EventLoop;

/*
channel理解为通道  封装了sockfd和其感兴趣的event ，如EPOLLIN,EPOLLOUT事件
*/

class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop,int fd);
    ~Channel();
    
    // fd得到poller通知以后，处理事件的函数，调用相应的回调
    void handleEvent(Timestamp receiveTime);

    // 设置回调对象  cb是个左值是一个函数对象有内存空间，用std::move将其转为右值，把空间给readCallback_
    void setReadCallback(ReadEventCallback cb) {readCallback_ = std::move(cb);}
    void setWriteCallback(EventCallback cb) {writeCallback_ = std::move(cb);}
    void setCloseCallback(EventCallback cb) {closeCallback_ = std::move(cb);}
    void setErrorCallback(EventCallback cb) {errorCallback_ = std::move(cb);}

    // 防止当channel被手动remove掉时，还在执行回调操作
    void tie(const std::shared_ptr<void>&);

    int fd() const {return fd_;}
    int events() const {return events_;}
    int set_revents(int revt) { revents_ = revt;}


    // 设置fd相应的事件状态
    void enableReading() { events_ |=kReadEvent; update();}
    void disableReading() { events_ &= ~kReadEvent; update();}
    void enableWriting() { events_ |= kWriteEvent; update();}
    void disableWriting(){ events_ &= ~kWriteEvent; update();}
    void disableAll() { events_ = kNoneEvent; update();}

    //返回fd当前的事件状态
    bool isNoneEvent() const { return events_ == kNoneEvent;}
    bool isWriting() const { return events_ & kWriteEvent;}
    bool isReading() const { return events_ & kReadEvent;}

    int index() { return index_;}
    void set_index(int idx) { index_ = idx;}

    // one loop per thread
    EventLoop* ownerLoop() { return loop_;}
    void remove();

private:

    void update();
    void handleEventWithGuard(Timestamp receiveTime);

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;     //事件循环
    const int fd_;        //fd，Pooler监听的对象
    int events_;          //注册fd感兴趣的事件
    int revents_;         //poller返回的具体发生的事件
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;

    // 因为channel通道里面能够获知fd最终发生的具体事件revents，
    // 所以它负责调用具体事件的回调操作
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;

};