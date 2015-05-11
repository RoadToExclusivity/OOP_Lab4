#pragma once
#include "Worker.h"
#include "Establishment.h"

class CCompany : public CEstablishment, public std::enable_shared_from_this<CCompany>
{
public:
	CCompany(const std::string &name, const std::string &email);

	std::set<std::shared_ptr<CWorker>> GetWorkersList() const;
	bool AddWorker(const std::shared_ptr<CWorker> &worker);
	bool RemoveWorker(const std::shared_ptr<CWorker> &worker);

	std::string GetEmail() const;
	void ChangeEmail(const std::string &newEmail);

private:
	std::string m_email;
};

