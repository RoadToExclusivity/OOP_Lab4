#include "stdafx.h"
#include "Student.h"
#include "University.h"

using namespace std;

CUniversity::CUniversity(const string &name)
	:CEstablishment(name)
{
}

set<shared_ptr<CStudent>> CUniversity::GetStudentsList() const
{
	set<shared_ptr<CPerson>> persons = GetPersonsList();
	set<shared_ptr<CStudent>> students;
	for (auto &person : persons)
	{
		students.insert(dynamic_pointer_cast<CStudent>(person));
	}

	return students;
}

bool CUniversity::AddStudent(const shared_ptr<CStudent> &student)
{
	if (!student->GetUniversity() || student->GetUniversity()->GetName() == GetName())
	{
		student->SetUniversity(shared_from_this());
		AddPerson(student);
		return true;
	}

	return false;
}

bool CUniversity::RemoveStudent(const shared_ptr<CStudent> &student)
{
	if (RemovePerson(student))
	{
		student->SetUniversity(shared_ptr<CUniversity>());
		return true;
	}

	return false;
}