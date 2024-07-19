#include "Account.h"

Account::Account() : m_transactionList(nullptr) , m_numberOfTransaction(0), m_persons(nullptr), 
                    m_totalPersons(0), m_accountNumber(0), m_balance(0.0){}

Account::Account( Person** persons, int count, double balance ) : m_transactionList(nullptr) , m_numberOfTransaction(0), 
                    m_totalPersons(1), m_accountNumber(0), m_balance(balance) 
{
m_persons = new Person* [count];
for (int i = 0; i < count; ++i) 
{
        m_persons[i] = new Person(*persons[i]);
}
}