#include "Person.h"

Person::Person() : m_name(nullptr), m_id(0){}
Person::Person(const char* name, int id) : m_id(id)
{
   SetId(id);
   SetName(name);
     
}
Person::Person(const Person& other) : m_id(other.m_id) 
{
    SetId(other.GetId());
    SetName(other.GetName());
}

Person::~Person() {
    if (m_name != NULL)
    {
        delete[] m_name;
    }
}

void Person::SetName(const char* newName) 
{
    if (newName != NULL)
    {
        m_name = new char[strlen(newName) + 1];
        strcpy(m_name, newName);
    } 
}

void Person::SetId(int newId)
{
    if (newId > 0)
    {
        m_id = newId;
    }
}

char* Person::GetName() const
{
    return m_name;
}

int Person::GetId() const
{
    return m_id;
}

