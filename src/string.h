#include <cstring>
#include<iostream>
#ifndef _MYSTRING_
#define _MYSTRING_

class String
{
    public:
    String(const char* cstr = 0);
    //三个特殊函数
    String(const String& str);  //拷贝构造
    String& operator = (const String& str);//拷贝构造 -> 左边清空 右边负值
    ~String();

    char* get_c_str() const {return m_data;} //传回指针
    private:
    char* m_data;
};  inline std::ostream& operator << (std::ostream& os, const String& str)
    {
        os<<str.get_c_str();
        return os;
    }    
    //构造函数
    inline String::String(const char* cstr)
    {
        if(cstr)
        {
            m_data = new char[strlen(cstr)+1];
            strcpy(m_data,cstr);
        }
        else{
            m_data = new char[1];
            *m_data = '\0';
        }
    }

    inline String::~String()
    {
        delete[] m_data;
    }

    inline String::String(const String& s)
    {
        m_data = new char[strlen(s.m_data)+1];
        strcpy(m_data,s.m_data); 
    }

    inline 
    String& String::operator=(const String& str)
    {
        if(this == &str){
            return *this; 
        }                     //检测自我负值 防止两指针指向同一地方 删除自我
        delete[] m_data;
        m_data = new char[strlen(str.m_data)+1];
        strcpy(m_data,str.m_data);
        return *this;
    } 
#endif