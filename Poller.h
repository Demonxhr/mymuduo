#pragma once

#include "noncopyable.h"
#include "Timestamp.h"

#include <vector>
#include <unordered_map>

class Channel;
class EventLoop;
// muduo库中多路事件分发器的核心io复用模块
class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop *loop);

    //虚析构  在子类析构时 可能会调用父类的析构函数导致自己资源无法释放
    //用虚析构 子类在析构时会检查虚表，调用自己的虚构函数
    virtual ~Poller() = default;

    // 给所有io复用保留同一的接口
    virtual Timestamp poll(int timeoutMs,ChannelList *activeChannels) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;

    // 判断参数channel是否在当前Poller当中
    bool hasChannel(Channel *channel) const;

    // eventloop可以通过该接口获取默认的io复用的具体实现
    static Poller* newDefaultPoller(EventLoop *loop);
protected:
    // map的key：sockfd(int) value：sockfd所属的channel通道类型
    using ChannelMap = std::unordered_map<int,Channel*>;
    ChannelMap channels_;
private:
    // 定义Poller所属事件循环EventLoop
    EventLoop *ownerLoop_;    
};