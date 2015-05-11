#pragma once
#include "Person.h"

class CStudent : public CPerson
{
public:
	CStudent(const std::string &name, unsigned yearOfStudy, const std::shared_ptr<const CUniversity> &university,
			unsigned age, unsigned height, unsigned weight, bool isMale);

	unsigned GetStudyYear() const;
	std::shared_ptr<CUniversity> GetUniversity() const;

	void SetStudyYear(unsigned year);
	void SetUniversity(const std::weak_ptr<const CUniversity> &university);

private:
	const unsigned MIN_YEAR = 1;
	const unsigned MAX_YEAR = 5;

	unsigned m_year;
	std::weak_ptr<const CUniversity> m_university;
};

