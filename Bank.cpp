#include "Bank.h"

Bank::Bank(): m_name(nullptr), m_account(nullptr), m_bankCode(0), m_numbeOfAccounts(0), m_totalBalance(0){}
Bank::Bank( const char* name, int code ): m_account(nullptr), m_bankCode(code), m_numbeOfAccounts(0), m_totalBalance(0){
    SetBankName(name);
}
Bank::~Bank(){
    delete[] m_account;
    delete[] m_name;
}

void Bank::SetBankName( const char* name ){
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);

}
void Bank::SetAccount( Account** account, int numbeOfAccounts ){
    m_numbeOfAccounts = numbeOfAccounts;
    m_account = new Account* [numbeOfAccounts];
    for (int i = 0; i < numbeOfAccounts; i++)
    {
        m_account[i] = new Account(account[i]->GetPersons(), account[i]->GetTotalPersons() ,account[i]->GetBalance());
        m_account[i]->SetAccountNumber(account[i]->GetAccountNumber());
        m_account[i]->SetTransactions(account[i]->GetTransactions(), account[i]->GetNumOfTransactions());
    }
    

}
void Bank::SetTotal( double total ){
    m_totalBalance = total;

}
void Bank::SetCode( int code ){
    m_bankCode = code;
}
const char* Bank::GetBankName() const{
    return m_name;

}
Account** Bank::GetAccounts() const{
    return m_account;
}
int Bank::GetNumberOfAccounts() const{
    return m_numbeOfAccounts;
}
double Bank::GetTotal() const{
    return m_totalBalance;
}
int	Bank::GetCode() const{
    return m_bankCode;
}

void Bank::AddAccount( const Account& account ){
    int flag = 1;
    int i, j;
    for (i = 0; i < GetNumberOfAccounts(); i++) {
        if (GetAccounts()[i]->GetAccountNumber() == account.GetAccountNumber()){
            flag = 0;
            break;
        }

    }
    if (flag) {//account doesnt exist
        Account** temp = new Account * [GetNumberOfAccounts() + 1];
        for ( j = 0; j < GetNumberOfAccounts(); j++) {
            temp[j] = new Account(GetAccounts()[j]->GetPersons(), GetAccounts()[j]->GetTotalPersons(), GetAccounts()[j]->GetBalance());
            temp[j]->SetTransactions(GetAccounts()[j]->GetTransactions(), GetAccounts()[j]->GetNumOfTransactions());
        }
        temp[j] = new Account(account);
        SetAccount(temp, j + 1);
        delete[]temp;
    }
    SetTotal(account.GetBalance() + GetTotal());

}
void Bank::AddAccount( const Person& per, double amount ){
    AddAccount(Account(per, amount));
    SetTotal(GetTotal() + amount);
}

// add person to exist account or create a new account for him
void Bank::AddPerson( const Person& newPerson, const Account& account, double amount ){
    for (int i = 0; i < GetNumberOfAccounts(); i++)
    {
        if (GetAccounts()[i]->GetAccountNumber() == account.GetAccountNumber())
        {
            for (int j = 0; j < GetAccounts()[i]->GetTotalPersons(); j++)
            {
                if (GetAccounts()[i]->GetPersons()[j]->GetId() != newPerson.GetId())
                {
                    m_account[i]->AddPerson(newPerson, amount);
                    SetTotal(GetTotal()+amount);
                }
                
            }
            
        }
        
    }
    
}
void Bank::DeleteAccount( const Account& account ){
        for (int i = 0; i < GetNumberOfAccounts(); i++)
        {
            if (GetAccounts()[i]->GetAccountNumber() == account.GetAccountNumber())
            {
                if (i == 0 && GetNumberOfAccounts() == 0)
                {
                    delete[] m_account;
                    m_numbeOfAccounts = 0;
                }
                else
                {
                    delete m_account[i];
                    m_numbeOfAccounts--;
                    i--;
                }
                
            }
            
        }
        SetTotal(GetTotal() + account.GetBalance());

}
void Bank::DeletePerson( const Person& p ){
    int j;
    for (int i = 0; i < GetNumberOfAccounts(); i++)
    {
        GetAccounts()[i]->DeletePerson(p);
        if (GetAccounts()[i]->GetTotalPersons() == 0)
        {
            SetTotal(GetTotal() - GetAccounts()[i]->GetBalance());
            for (j = i; j < GetNumberOfAccounts() - 1; j++) {
                m_account[j] = GetAccounts()[j + 1];
            }
            delete m_account[j];
            m_numbeOfAccounts--;
            i--;
        }
        
    }
    

}