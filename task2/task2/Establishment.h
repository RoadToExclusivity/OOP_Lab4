#pragma once
#include "Person.h"

class CEstablishment
{
public:
	CEstablishment(const std::string &name);

	std::string GetName() const;
	void SetNewName(const std::string &newName);

protected:
	std::set<std::shared_ptr<CPerson>> GetPersonsList() const;
	void AddPerson(const std::shared_ptr<CPerson> &person);
	bool RemovePerson(const std::shared_ptr<CPerson> &person);

private:
	std::string m_name;
	std::set<std::shared_ptr<CPerson>> m_persons;
};

