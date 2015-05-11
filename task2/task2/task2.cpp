#include "stdafx.h"
#include "Student.h"
#include "University.h"

using namespace std;

bool IsUniversityAlreadyExist(const set<shared_ptr<const CUniversity>> &universities, const string &name)
{
	bool hasName = false;
	for (auto &university : universities)
	{
		if (university->GetName() == name)
		{
			hasName = true;
			break;
		}
	}

	return hasName;
}

void PrintUniversities(const set<shared_ptr<const CUniversity>> &universities)
{
	for (auto &university : universities)
	{
		cout << university->GetName() << endl;
	}
}

void PrintStudentInfo(const shared_ptr<const CStudent> &student)
{
	cout << "Name: " << student->GetName() << endl;
	cout << (student->IsMale() ? "Male" : "Female") << endl;
	cout << "Age: " << student->GetAge() << endl;
	cout << "Height: " << student->GetHeight() << endl;
	cout << "Weight: " << student->GetHeight() << endl;
	cout << "Study year: " << student->GetStudyYear() << endl;
	cout << "University name: " << student->GetUniversity()->GetName() << endl;
}

bool ChangeUniversityName(const set<shared_ptr<const CUniversity>> &universities, const shared_ptr<CUniversity> &university, 
							const string &newName)
{
	if (!IsUniversityAlreadyExist(universities, newName))
	{
		university->SetNewName(newName);
		return true;
	}

	return false;
}

bool DeleteUniversity(set<shared_ptr<const CUniversity>> &universities, shared_ptr<CUniversity> &university)
{
	if (universities.erase(university))
	{
		for (auto &student : university->GetStudentsList())
		{
			university->RemoveStudent(student);
		}

		return true;
	}

	return false;
}

void PrintStudents(const shared_ptr<const CUniversity> &university)
{
	for (auto &student : university->GetStudentsList())
	{
		PrintStudentInfo(student);
	}
}

bool AddUniversity(set<shared_ptr<const CUniversity>> &universities, const string &name)
{
	if (!IsUniversityAlreadyExist(universities, name))
	{
		auto universityPtr = make_shared<const CUniversity>(name);
		universities.insert(universityPtr);

		return true;
	}

	return false;
}

void PrintStudents(const set<shared_ptr<const CStudent>> &students)
{
	for(auto &student : students)
	{
		PrintStudentInfo(student);
	}
}

void ChangeAge(const set<shared_ptr<const CStudent>> &students, shared_ptr<CStudent> &student, unsigned age)
{
	student->SetAge(age);
}

void Changeheight(const set<shared_ptr<const CStudent>> &students, shared_ptr<CStudent> &student, unsigned height)
{
	student->SetHeight(height);
}

void ChangeYear(const set<shared_ptr<const CStudent>> &students, shared_ptr<CStudent> &student, unsigned year)
{
	student->SetStudyYear(year);
}

void AddStudent(set<shared_ptr<const CStudent>> &students, const string &name, unsigned yearOfStudy, 
	const shared_ptr<const CUniversity> &university,
	unsigned age, unsigned height, unsigned weight, bool isMale)
{
	shared_ptr<CStudent> student = make_shared<CStudent>(CStudent(name, yearOfStudy, university, age, height, weight, isMale));
	students.insert(student);
}

void DeleteStudent(set<shared_ptr<const CStudent>> &students, const shared_ptr<CStudent> &student)
{
	if (students.erase(student))
	{
		if (student->GetUniversity() != nullptr)
		{
			student->GetUniversity()->RemoveStudent(student);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

