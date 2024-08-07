#include "Account.h"
//defult constructor
Account::Account() : m_transactionList(nullptr) , m_numberOfTransaction(0), m_persons(nullptr), 
                    m_totalPersons(0), m_accountNumber(0), m_balance(0.0){}

//constructor with persons arrey and balance
Account::Account( Person** persons, int count, double balance ) : m_transactionList(nullptr) , m_numberOfTransaction(0), 
                    m_totalPersons(count), m_accountNumber(0), m_balance(balance) 
{
        SetPersons(persons, count);
        int sum = 0;
        for (int i = 0; i < GetTotalPersons(); i++)
        {
                sum+= persons[i]->GetId();
        }
        SetAccountNumber(persons[0]->GetId() / 100);
}

// constructor with one person and balance
Account::Account( const Person& person, double balance ) : m_transactionList(nullptr) , m_numberOfTransaction(0),  
                    m_totalPersons(1), m_accountNumber(0), m_balance(balance)
{
        Person** temp = new Person* [1];
        temp[0] = new Person(person);
        SetPersons(temp, 1);
        delete[] temp;
        SetBalance(balance);
        SetAccountNumber(person.GetId() / 100);


}

// cpy constructor
Account::Account( const Account& other ) 
{
        SetBalance(other.GetBalance());
        SetAccountNumber(other.GetAccountNumber());
        SetPersons(other.GetPersons(), other.GetTotalPersons());
        SetTransactions(other.m_transactionList, other.m_numberOfTransaction);       

}

Account::~Account()
{
        delete[]m_transactionList;
        if (GetTotalPersons() != 0)
                delete[]m_persons;      
}


void Account::SetPersons(Person** persons, int count){
        m_totalPersons = count;
        m_persons = new Person * [count];
        for (int i = 0; i < count; i++) {
                m_persons[i] = new Person(persons[i]->GetName(), persons[i]->GetId());
        }
        
}

void Account::SetAccountNumber(int number){
        m_accountNumber = number;
}

void Account::SetBalance( double balance ){
        m_balance = balance;
}

void Account::SetTransactions( Transaction** newTransaction, int count ){
        int cnt = GetNumOfTransactions();
        m_numberOfTransaction = count;
        int i;
        m_transactionList = new Transaction * [count];
                for (i = 0; i < count; i++) {
                        if (i < cnt && count>1)
                                m_transactionList[i] = new Transaction(newTransaction[i]->GetSource(), newTransaction[i]->GetDes(), newTransaction[i]->GetAmount(), newTransaction[i]->GetDate());
                        else
                                m_transactionList[i] = new Transaction(NULL, NULL, 0, NULL);
                }
}

Transaction** Account::GetTransactions(){
        return m_transactionList;
}
int Account::GetNumOfTransactions(){
        return m_numberOfTransaction;
}
Person** Account::GetPersons() const{
        return m_persons;
}
int Account::GetTotalPersons()const{
        return m_totalPersons;
}
int Account::GetAccountNumber() const{
        return m_accountNumber;
}
double Account::GetBalance() const{
        return m_balance;
 }


void Account::Withdraw( double amount, const char* date ){
        SetTransactions(GetTransactions(), GetNumOfTransactions() + 1);
        if (GetTransactions() != NULL) {
	        GetTransactions()[GetNumOfTransactions() - 1]->SetDate(date);
	        GetTransactions()[GetNumOfTransactions() - 1]->SetAmount(amount);
        }       
        SetBalance(GetBalance() - amount);
}
void Account::Deposit( double amount, const char* date ){
        SetTransactions(GetTransactions(), GetNumOfTransactions() + 1);
        if (GetTransactions() != NULL){
                GetTransactions()[GetNumOfTransactions() - 1]->SetDate(date);
	        GetTransactions()[GetNumOfTransactions() - 1]->SetAmount(amount);     
        }
        SetBalance(GetBalance() + amount);
}
void Account::AddPerson( const Person& newPerson, double amount ){
        Person** newPersons = new Person*[m_totalPersons + 1];
        for (int i = 0; i < m_totalPersons; ++i ){
                newPersons[i] = m_persons[i];
        }
        newPersons[m_totalPersons] = new Person(newPerson);
        m_totalPersons++;
        m_balance+=amount;

}
void Account::DeletePerson( const Person& oldPerson ){
        for (int i = 0; i < GetTotalPersons(); i++) {
	        if (GetPersons()[i]->GetId() == oldPerson.GetId()) {
		        if ((i == 0) && (GetTotalPersons() == 1)) {
		        	delete[]m_persons;
		        	m_totalPersons = 0;
		        }
		        else {
			        delete m_persons[i];
			        m_totalPersons--;
			        i--;
		        }
	        }
        }
}
void Account::AddTransaction( const Transaction& newTransaction ){
        newTransaction.GetDes()->SetTransactions(newTransaction.GetDes()->GetTransactions(), newTransaction.GetDes()->GetNumOfTransactions() + 1);
        newTransaction.GetDes()->GetTransactions()[newTransaction.GetDes()->GetNumOfTransactions() - 1] = new Transaction(newTransaction);
        newTransaction.GetDes()->SetBalance(newTransaction.GetAmount() + newTransaction.GetDes()->GetBalance());
                 if (newTransaction.GetDes() != newTransaction.GetSource()) {
                          newTransaction.GetSource()->SetTransactions(newTransaction.GetSource()->GetTransactions(), newTransaction.GetSource()->GetNumOfTransactions() + 1);
                         newTransaction.GetSource()->GetTransactions()[newTransaction.GetSource()->GetNumOfTransactions() - 1] = new Transaction(newTransaction);
                          newTransaction.GetSource()->SetBalance(newTransaction.GetSource()->GetBalance() - newTransaction.GetAmount());
                 }
}       

void Account::clearTransactions(){
        if(m_transactionList != nullptr)
        {
                delete[] m_transactionList;
        }
}
void Account::clearPersons(){
        if (GetTotalPersons() != 0)
        {
                delete[] m_persons;
        }
        

}