#include "include/threadhandle.h"

#include <QtCore/qthread.h>

ThreadHandle::ThreadHandle()
{
    initfist = false;
}

ThreadHandle::~ThreadHandle() //停止所有线程，并释放资源
{
    QThread * tmp;
    for (auto it = threadSize.begin(); it != threadSize.end(); ++it)
    {
        tmp = it.key();
        tmp->exit();
        tmp->wait(2000);
        delete tmp;
    }
}

ThreadHandle & ThreadHandle::getClass()
{
    //静态变量  该类维护的一个唯一对象
    static ThreadHandle th;
    return th;
}

QThread *ThreadHandle::getThread()
{
    if (!initfist)
    {
        initThreadType(THREADSIZE,10);
    }
    if (type == THREADSIZE)
        return findThreadSize();
    else
        return findHandleSize();
}

void ThreadHandle::removeThread(QThread * thread)
{
    auto t = threadSize.find(thread);
    if (t != threadSize.end())
    {
        t.value() --;
        if (type == HANDLESIZE && t.value() == 0 && threadSize.size() > 1)
        {
            //TODO  修改
            threadSize.remove(thread);
            thread->exit();            
            thread->wait(2000);
            delete thread;
        }
    }
}

void ThreadHandle::initThreadType(ThreadType type, unsigned int max)
{
    if (!initfist)
    {
        this->type = type;
        this->size = max;
        if (this->size == 0)
        {
            if(type == THREADSIZE)
                this->size = 10;  //固定10个线程的线程池
            else
                this->size = 100;
        }

        if (type == THREADSIZE)
            initThreadSize();
        else
        {
            //先建立64个线程
            for (int i = 0; i < 4; ++i)
            {
                QThread * tmp = new QThread;                
                threadSize.insert(tmp, 0);
                tmp->start();
            }
           
        }
    }
    initfist = true;
}

void ThreadHandle::initThreadSize() //建立好线程并启动，
{
    QThread * tmp;
    for (unsigned int i = 0; i < size;++i)
    {
        tmp = new QThread;

        threadSize.insert(tmp,0);       
        tmp->start();
    }
}

QThread * ThreadHandle::findHandleSize() //查找到线程里的连接数小于最大值就返回查找到的，找不到就新建一个线程
{
    for (auto it  = threadSize.begin();it != threadSize.end() ;++it)
    {
        if (it.value() < size)
        {
            //TODO 修改
            if (it.value() == 0)
            {
                it.key()->start();
            }
            ++it.value() ;
            return it.key();
        }
    }
    QThread * tmp = new QThread;

    threadSize.insert(tmp,1);
    tmp->start();
    return tmp;
}

QThread *ThreadHandle::findThreadSize() //遍历查找所有线程中连接数最小的那个，返回
{
    auto it = threadSize.begin();
    auto ite = threadSize.begin();
    for (++it ; it != threadSize.end(); ++it)
    {
        if (it.value() < ite.value())
        {
            ite = it;
        }
    }
    ite.value() ++;
    return ite.key();
}

void ThreadHandle::clear()//清空计数退出，线程不释放
{
    for (auto it  = threadSize.begin();it != threadSize.end() ;++it)
    {
        it.value()  = 0;        
    }
}
