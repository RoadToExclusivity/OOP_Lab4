#include "stdafx.h"
#include "Person.h"

using namespace std;

CPerson::CPerson(const string name, unsigned age, unsigned height, unsigned weight, bool isMale)
	:m_name(name), m_age(age), m_height(height), m_weight(weight), m_isMale(isMale)
{
}

CPerson::~CPerson()
{
}

bool CPerson::IsMale() const
{
	return m_isMale;
}

unsigned CPerson::GetAge() const
{
	return m_age;
}

unsigned CPerson::GetHeight() const
{
	return m_height;
}

unsigned CPerson::GetWeight() const
{
	return m_weight;
}

std::string CPerson::GetName() const
{
	return m_name;
}

void CPerson::SetAge(unsigned age)
{
	if (age > m_age)
	{
		m_age = age;
	}
}

void CPerson::SetHeight(unsigned height)
{
	if (height > m_height)
	{
		m_height = height;
	}
}

void CPerson::SetWeight(unsigned weight)
{
	m_weight = weight;
}

void CPerson::SetName(const string &name)
{
	m_name = name;
}