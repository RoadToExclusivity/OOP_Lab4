#pragma once
#include "Person.h"

class CWorker : public CPerson
{
public:
	CWorker(const std::string name, std::string post, const std::shared_ptr<const CCompany> &company,
		unsigned age, unsigned height, unsigned weight, bool isMale);
	
	std::string GetPost() const;
	std::shared_ptr<const CCompany> GetCompany() const;

	void SetPost(std::string newPost);
	void SetCompany(const std::weak_ptr<const CCompany> &company);

private:
	std::string m_post;
	std::weak_ptr<const CCompany> m_company;
};

