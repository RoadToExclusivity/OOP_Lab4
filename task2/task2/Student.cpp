#include "stdafx.h"
#include "Student.h"
#include "University.h"

using namespace std;

CStudent::CStudent(const string &name, unsigned yearOfStudy, const shared_ptr<CUniversity> &university,
				unsigned age, unsigned height, unsigned weight, bool isMale)
				:CPerson(name, age, height, weight, isMale), m_university(university)
{
	if (yearOfStudy >= MIN_YEAR && yearOfStudy <= MAX_YEAR)
	{
		m_year = yearOfStudy;
	}
	else
	{
		m_year = MIN_YEAR;
	}
}

unsigned CStudent::GetStudyYear() const
{
	return m_year;
}

shared_ptr<CUniversity> CStudent::GetUniversity() const
{
	return m_university.lock();
}

void CStudent::SetStudyYear(unsigned year)
{
	if (year >= MIN_YEAR && year <= MAX_YEAR)
	{
		m_year = year;
	}
}

void CStudent::SetUniversity(const weak_ptr<const CUniversity> &university)
{
	m_university = university;
}