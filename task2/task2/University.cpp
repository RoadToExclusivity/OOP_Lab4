#include "stdafx.h"
#include "Student.h"
#include "University.h"

using namespace std;

CUniversity::CUniversity(const string &name)
	:m_name(name)
{
}

CUniversity::~CUniversity()
{
}

string CUniversity::GetName() const
{
	return m_name;
}

set<shared_ptr<CStudent>> CUniversity::GetStudentsList() const
{
	return m_students;
}

bool CUniversity::AddStudent(const shared_ptr<CStudent> &student)
{
	if (!student->GetUniversity())
	{
		student->SetUniversity(shared_from_this());
		m_students.insert(student);
		return true;
	}

	return false;
}

bool CUniversity::RemoveStudent(const shared_ptr<CStudent> &student)
{
	if (m_students.erase(student))
	{
		student->SetUniversity(shared_ptr<CUniversity>());
		return true;
	}

	return false;
}

void CUniversity::SetNewName(const string &newName)
{
	m_name = newName;
}