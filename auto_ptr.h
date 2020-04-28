#ifndef AUTO_PTR_H_INCLUDED
#define AUTO_PTR_H_INCLUDED
/*****
Auto_ptr�࣬һ��ָ��ֻ�ܱ�һ�������Ķ����йܣ����������ڴ��ʱ��������
���Խ�ָ���йܸ��������ʵ�ֶ�̬��������Լ��ڴ�ļ�ʱ����
*****/
namespace mystl
{
template<typename T>
class Auto_ptr
{

private:
    T* m_ptr;       //ʵ�ʵ�ָ��
public:
    //���캯��1������һ��T����ָ��
    explicit Auto_ptr(T* p=nullptr):m_ptr(p){}
    //���캯��2������һ��T���͵�Auto_ptr
    Auto_ptr(Auto_ptr& p):m_ptr(p.release()){}
    //���캯��3������һ����ͬ���͵�Auto_ptr
    template<typename U>
    Auto_ptr(Auto_ptr<U>& p):m_ptr(p.release()){}
    //����
    ~Auto_ptr(){delete m_ptr;}

    //���ظ�ֵ�����
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
    //��ȡָ��ָ����ڴ�
    T& operator*()const{return *m_ptr;}
    //ָ����T��ָ��
    T* operator->()const{return m_ptr;}
    //���ָ��
    inline T* get_ptr()const{return m_ptr;}


    //�ͷ�ָ���й�Ȩ��
    T* release()
    {
        T* temp=m_ptr;
        m_ptr=nullptr;
        return temp;
    }
    //����ָ�룬�ͷ�ԭ���й���auto_ptr�ϵ�ָ��ָ����ڴ�
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
