#include "stdafx.h"
#include "Person.h"
#include "Establishment.h"

using namespace std;

CEstablishment::CEstablishment(const string &name)
	:m_name(name)
{
}

string CEstablishment::GetName() const
{
	return m_name;
}

set<shared_ptr<CPerson>> CEstablishment::GetPersonsList() const
{
	return m_persons;
}

void CEstablishment::AddPerson(const shared_ptr<CPerson> &person)
{
	m_persons.insert(person);
}

bool CEstablishment::RemovePerson(const shared_ptr<CPerson> &person)
{
	if (m_persons.erase(person))
	{
		return true;
	}

	return false;
}

void CEstablishment::SetNewName(const string &newName)
{
	m_name = newName;
}
