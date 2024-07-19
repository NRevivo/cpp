#include "Person.h"

Person::Person() : m_name(nullptr), m_id(0){}
Person::Person(const char* name, int id) : m_id(id)
{
    if (name)
    {
        m_name = new char[strlen(name) + 1];
        strcpy (m_name, name);
    }
    else
    {
        m_name = nullptr;
    }
     
}
Person::Person(const Person& other) : m_id(other.m_id) 
{
    if (other.m_name) 
    {
        m_name = new char[strlen(other.m_name) + 1];
        strcpy(m_name, other.m_name);
    } 
    else 
    {
        m_name = nullptr;
    }
}

Person::~Person() {
    delete[] m_name;
}

void Person::SetName(const char* newName) 
{
    delete[] m_name; 
    if (newName)
    {
        m_name = new char[strlen(newName) + 1];
        strcpy(m_name, newName);
    } 
    else 
    {
        m_name = nullptr;
    }
}

void Person::SetId(int newId)
{
    m_id = newId;
}

char* Person::GetName() const
{
    return m_name;
}

int Person::GetId() const
{
    return m_id;
}

