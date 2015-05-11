#include "stdafx.h"
#include "Worker.h"
#include "Company.h"

using namespace std;

CCompany::CCompany(const string &name, const string &email)
	:CEstablishment(name), m_email(email)
{
}

set<shared_ptr<CWorker>> CCompany::GetWorkersList() const
{
	set<shared_ptr<CPerson>> persons = GetPersonsList();
	set<shared_ptr<CWorker>> workers;
	for (auto &person : persons)
	{
		workers.insert(dynamic_pointer_cast<CWorker>(person));
	}

	return workers;
}

bool CCompany::AddWorker(const shared_ptr<CWorker> &worker)
{
	if (!worker->GetCompany())
	{
		worker->SetCompany(shared_from_this());
		AddPerson(worker);
		return true;
	}

	return false;
}

bool CCompany::RemoveWorker(const shared_ptr<CWorker> &worker)
{
	if (RemovePerson(worker))
	{
		worker->SetCompany(shared_ptr<CCompany>());
		return true;
	}

	return false;
}

std::string CCompany::GetEmail() const
{
	return m_email;
}

void CCompany::ChangeEmail(const std::string &newEmail)
{
	m_email = newEmail;
}