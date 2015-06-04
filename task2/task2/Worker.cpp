#include "stdafx.h"
#include "Worker.h"
#include "Company.h"

using namespace std;

CWorker::CWorker(const std::string name, std::string post, const std::shared_ptr<CCompany> &company,
	unsigned age, unsigned height, unsigned weight, bool isMale)
	:CPerson(name, age, height, weight, isMale), m_post(post), m_company(company)
{
}

string CWorker::GetPost() const
{
	return m_post;
}

shared_ptr<CCompany> CWorker::GetCompany() const
{
	return m_company.lock();
}

void CWorker::SetPost(string newPost)
{
	m_post = newPost;
}

void CWorker::SetCompany(const weak_ptr<const CCompany> &company)
{
	m_company = company;
}