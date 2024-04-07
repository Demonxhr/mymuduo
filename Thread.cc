#include "Thread.h"
#include "CurrentThread.h"


#include <semaphore.h>


std::atomic_int Thread::numCreated_ ;

Thread::Thread(ThreadFunc func, const std::string &name)
    : started_(false)
    , joined_(false)
    , tid_(0)
    , func_(std::move(func))
    , name_(name)
{
    setDefaultName();
}

Thread::~Thread()
{
    if(started_ && !joined_)
    {
        thread_->detach();   //分离线程
    }
}

void Thread::start()
{
    started_ = true;
    sem_t sem;
    sem_init(&sem,false,0);
    // 开启线程
    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        // 获取线程tid
        tid_ = CurrentThread::tid();
        sem_post(&sem);
        func_();  //开启一个线程专门执行该线程函数
    }));

    // 这里必须等待获取完上面创建线程的tid
    sem_wait(&sem);
}

void Thread::join()
{
    joined_ = true;
    thread_->join();
}

void Thread::setDefaultName()
{
    int num = ++numCreated_;
    if(name_.empty())
    {
        char buf[32] = {0};
        sprintf(buf,"Thread%d",num);
        name_ = buf;
    }
}
