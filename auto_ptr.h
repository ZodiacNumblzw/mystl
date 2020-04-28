#ifndef AUTO_PTR_H_INCLUDED
#define AUTO_PTR_H_INCLUDED
/*****
Auto_ptr类，一个指针只能被一个这样的对象托管，否则清理内存的时候会出问题
可以将指针托管给这个对象，实现动态分配对象以及内存的及时清理
*****/
namespace mystl
{
template<typename T>
class Auto_ptr
{

private:
    T* m_ptr;       //实际的指针
public:
    //构造函数1：传入一个T类型指针
    explicit Auto_ptr(T* p=nullptr):m_ptr(p){}
    //构造函数2：传入一个T类型的Auto_ptr
    Auto_ptr(Auto_ptr& p):m_ptr(p.release()){}
    //构造函数3：传入一个不同类型的Auto_ptr
    template<typename U>
    Auto_ptr(Auto_ptr<U>& p):m_ptr(p.release()){}
    //析构
    ~Auto_ptr(){delete m_ptr;}

    //重载赋值运算符
    Auto_ptr& operator=(Auto_ptr& p)
    {
        if(this!=&p)
        {
            delete m_ptr;
            m_ptr=p.release();
        }
        return *this;
    }
    template<typename U>
    Auto_ptr& operator=(Auto_ptr<U>& p)
    {
        if(this!=&p)
        {
            delete m_ptr;
            m_ptr=p.release();
        }
        return *this;
    }

public:
    //获取指针指向的内存
    T& operator*()const{return *m_ptr;}
    //指向类T的指针
    T* operator->()const{return m_ptr;}
    //获得指针
    inline T* get_ptr()const{return m_ptr;}


    //释放指针托管权限
    T* release()
    {
        T* temp=m_ptr;
        m_ptr=nullptr;
        return temp;
    }
    //重置指针，释放原来托管在auto_ptr上的指针指向的内存
    void reset(T* p=nullptr)
    {
        if(m_ptr!=p)
        {
            delete m_ptr;
            m_ptr=p;
        }
    }
};

}

#endif // AUTO_PTR_H_INCLUDED
