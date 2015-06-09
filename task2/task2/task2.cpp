#include "stdafx.h"
#include "Student.h"
#include "University.h"
#include "Company.h"
#include "Worker.h"

using namespace std;

const string UNIVERSITY_FILE_NAME = "universities.txt";
const string STUDENT_FILE_NAME = "students.txt";
const string COMPANY_FILE_NAME = "comapnies.txt";
const string WORKER_FILE_NAME = "workers.txt";

bool IsUniversityAlreadyExist(const set<shared_ptr<CUniversity>> &universities, const string &name)
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

void PrintUniversities(const set<shared_ptr<CUniversity>> &universities)
{
	size_t i = 1;
	for (auto &university : universities)
	{
		cout << i++ << ")" << endl;
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

bool ChangeUniversityName(const set<shared_ptr<CUniversity>> &universities, const shared_ptr<CUniversity> &university, 
							const string &newName)
{
	if (!IsUniversityAlreadyExist(universities, newName))
	{
		university->SetNewName(newName);
		return true;
	}

	return false;
}

bool DeleteStudent(set<shared_ptr<CStudent>> &students, shared_ptr<CStudent> &student)
{
	if (students.erase(student))
	{
		if (student->GetUniversity() != nullptr)
		{
			student->GetUniversity()->RemoveStudent(student);
		}
		student = nullptr;

		return true;
	}

	return false;
}

bool DeleteUniversity(set<shared_ptr<CUniversity>> &universities, set<shared_ptr<CStudent>> &students, 
						shared_ptr<CUniversity> &university)
{
	if (universities.erase(university))
	{
		for (auto student : university->GetStudentsList())
		{
			university->RemoveStudent(student);
			DeleteStudent(students, student);
		}

		university = nullptr;

		return true;
	}

	return false;
}

void PrintStudents(const shared_ptr<const CUniversity> &university)
{
	size_t i = 1;
	for (auto &student : university->GetStudentsList())
	{
		cout << i++ << ")" << endl;
		PrintStudentInfo(student);
	}
}

bool AddUniversity(set<shared_ptr<CUniversity>> &universities, const string &name)
{
	if (!IsUniversityAlreadyExist(universities, name))
	{
		auto universityPtr = make_shared<CUniversity>(name);
		universities.insert(universityPtr);

		return true;
	}

	return false;
}

void PrintStudents(const set<shared_ptr<CStudent>> &students)
{
	size_t i = 1;
	for(auto &student : students)
	{
		cout << i++ << ")" << endl;
		PrintStudentInfo(student);
	}
}

void ChangeAge(shared_ptr<CStudent> &student, unsigned age)
{
	student->SetAge(age);
}

void ChangeHeight( shared_ptr<CStudent> &student, unsigned height)
{
	student->SetHeight(height);
}

void ChangeYear(shared_ptr<CStudent> &student, unsigned year)
{
	student->SetStudyYear(year);
}

void AddStudent(set<shared_ptr<CStudent>> &students, shared_ptr<CStudent> &student)
{
	students.insert(student);
	student->GetUniversity()->AddStudent(student);
}

set<shared_ptr<CUniversity>> LoadUniversities()
{
	set<shared_ptr<CUniversity>> res;

	ifstream fin(UNIVERSITY_FILE_NAME);
	string name;
	while (getline(fin, name))
	{
		auto university = make_shared<CUniversity>(name);
		res.insert(university);
	}

	return res;
}

void SaveUniversities(const set<shared_ptr<CUniversity>> &universities)
{
	ofstream fout(UNIVERSITY_FILE_NAME);

	for (auto &curUniversity : universities)
	{
		fout << curUniversity->GetName() << endl;
	}
}

set<shared_ptr<CStudent>> LoadStudents(const set<shared_ptr<CUniversity>> &universities)
{
	set<shared_ptr<CStudent>> res;

	ifstream fin(STUDENT_FILE_NAME);
	string name, age, height, yearOfStudy, weight, male, universityName;
	while (getline(fin, name))
	{
		getline(fin, age);
		getline(fin, height);
		getline(fin, weight);
		getline(fin, yearOfStudy);
		getline(fin, male);
		getline(fin, universityName);

		shared_ptr<CUniversity> university;
		for (auto &curUniversity : universities)
		{
			if (curUniversity->GetName() == universityName)
			{
				university = curUniversity;
				break;
			}
		}

		unsigned curAge = strtoul(age.c_str(), NULL, 10), curHeight = strtoul(height.c_str(), NULL, 10), curWeight = strtoul(weight.c_str(), NULL, 10), curYear = strtoul(yearOfStudy.c_str(), NULL, 10);
		bool isMale = (male == "Male");

		auto student = make_shared<CStudent>(name, curYear, university, curAge, curHeight, curWeight, isMale);
		university->AddStudent(student);
		res.insert(student);
	}
	
	return res;
}

void SaveStudents(const set<shared_ptr<CStudent>> &students)
{
	ofstream fout(STUDENT_FILE_NAME);

	for (auto &curStudent : students)
	{
		fout << curStudent->GetName() << endl << curStudent->GetAge() << endl << curStudent->GetHeight() << endl << curStudent->GetWeight() << endl;
		fout << curStudent->GetStudyYear() << endl << curStudent->IsMale() << endl << curStudent->GetUniversity()->GetName() << endl;
	}
}

string GetUniversityInfo()
{
	string res;
	cout << "Input university name : ";
	getline(cin, res);

	return res;
}

string GetStudentInfo()
{
	string res;
	cout << "Input student's name : ";
	getline(cin, res);

	return res;
}

shared_ptr<CUniversity> GetUniversity(const set<shared_ptr<CUniversity>> &universities, const string &name)
{
	for (auto &it : universities)
	{
		if (it->GetName() == name)
		{
			return it;
		}
	}

	return nullptr;
}

void GetChangeableStudent(unsigned &age, unsigned &height, unsigned &weight, unsigned &year)
{
	string sAge;
	cout << "Input student's age : ";
	getline(cin, sAge);
	age = atoi(sAge.c_str());

	string sHeight;
	cout << "Input student's height : ";
	getline(cin, sHeight);
	height = atoi(sHeight.c_str());

	string sWeight;
	cout << "Input student's weight : ";
	getline(cin, sWeight);
	weight = atoi(sWeight.c_str());

	string sYear;
	cout << "Input student's year of study : ";
	getline(cin, sYear);
	year = atoi(sYear.c_str());
}

shared_ptr<CStudent> GetNewStudent(const set<shared_ptr<CUniversity>> &universities)
{
	string name;
	cout << "Input student's name : ";
	getline(cin, name);

	unsigned age, height, weight, year;
	GetChangeableStudent(age, height, weight, year);

	string sMale;
	cout << "Is male ?";
	getline(cin, sMale);
	bool male = sMale == "Y";
	
	auto university = GetUniversity(universities, GetUniversityInfo());

	return make_shared<CStudent>(name, year, university, age, height, weight, male);
}

shared_ptr<CStudent> GetStudent(const set <shared_ptr<CStudent>> &students, const string &name)
{
	for (auto &it : students)
	{
		if (it->GetName() == name)
		{
			return it;
		}
	}

	return nullptr;
}

bool IsCompanyAlreadyExist(const set<shared_ptr<CCompany>> &companies, const string &name)
{
	bool hasName = false;
	for (auto &company : companies)
	{
		if (company->GetName() == name)
		{
			hasName = true;
			break;
		}
	}

	return hasName;
}

void PrintCompanies(const set<shared_ptr<CCompany>> &companies)
{
	size_t i = 1;
	for (auto &company : companies)
	{
		cout << i++ << ")" << endl;
		cout << company->GetName() << endl;
		cout << company->GetEmail() << endl;
	}
}

void PrintWorkerInfo(const shared_ptr<const CWorker> &worker)
{
	cout << "Name: " << worker->GetName() << endl;
	cout << (worker->IsMale() ? "Male" : "Female") << endl;
	cout << "Age: " << worker->GetAge() << endl;
	cout << "Height: " << worker->GetHeight() << endl;
	cout << "Weight: " << worker->GetHeight() << endl;
	cout << "Post: " << worker->GetPost() << endl;
	cout << "Company name: " << worker->GetCompany()->GetName() << endl;
}

bool ChangeCompanyName(const set<shared_ptr<CCompany>> &companies, const shared_ptr<CCompany> &company,
	const string &newName)
{
	if (!IsCompanyAlreadyExist(companies, newName))
	{
		company->SetNewName(newName);
		return true;
	}

	return false;
}

bool DeleteWorker(set<shared_ptr<CWorker>> &workers, shared_ptr<CWorker> &worker)
{
	if (workers.erase(worker))
	{
		if (worker->GetCompany() != nullptr)
		{
			worker->GetCompany()->RemoveWorker(worker);
		}
		worker = nullptr;

		return true;
	}

	return false;
}

bool DeleteCompany(set<shared_ptr<CCompany>> &companies, set<shared_ptr<CWorker>> &workers, 
					shared_ptr<CCompany> &company)
{
	if (companies.erase(company))
	{
		for (auto worker : company->GetWorkersList())
		{
			company->RemoveWorker(worker);
			DeleteWorker(workers, worker);
		}

		company = nullptr;

		return true;
	}

	return false;
}

void PrintWorkers(const shared_ptr<const CCompany> &company)
{
	size_t i = 1;
	for (auto &worker : company->GetWorkersList())
	{
		cout << i++ << ")" << endl;
		PrintWorkerInfo(worker);
	}
}

bool AddCompany(set<shared_ptr<CCompany>> &companies, const string &name, const string &email)
{
	if (!IsCompanyAlreadyExist(companies, name))
	{
		auto companyPtr = make_shared<CCompany>(name, email);
		companies.insert(companyPtr);

		return true;
	}

	return false;
}

void PrintWorkers(const set<shared_ptr<CWorker>> &workers)
{
	size_t i = 1;
	for (auto &worker : workers)
	{
		cout << i++ << ")" << endl;
		PrintWorkerInfo(worker);
	}
}

void ChangeAge(shared_ptr<CWorker> &worker, unsigned age)
{
	worker->SetAge(age);
}

void ChangeHeight(shared_ptr<CWorker> &worker, unsigned height)
{
	worker->SetHeight(height);
}

void ChangePost(shared_ptr<CWorker> &worker, const string &post)
{
	worker->SetPost(post);
}

void AddWorker(set<shared_ptr<CWorker>> &workers, shared_ptr<CWorker> &worker)
{
	workers.insert(worker);
	worker->GetCompany()->AddWorker(worker);
}

set<shared_ptr<CCompany>> LoadCompanies()
{
	set<shared_ptr<CCompany>> res;

	ifstream fin(COMPANY_FILE_NAME);
	string name, email;
	while (getline(fin, name) && getline(fin, email))
	{
		auto company = make_shared<CCompany>(name, email);
		res.insert(company);
	}

	return res;
}

void SaveCompanies(const set<shared_ptr<CCompany>> &companies)
{
	ofstream fout(COMPANY_FILE_NAME);

	for (auto &company : companies)
	{
		fout << company->GetName() << endl;
		fout << company->GetEmail() << endl;
	}
}

set<shared_ptr<CWorker>> LoadWorkers(const set<shared_ptr<CCompany>> &companies)
{
	set<shared_ptr<CWorker>> res;

	ifstream fin(WORKER_FILE_NAME);
	string name, age, height, weight, male, companyName, post;
	while (getline(fin, name))
	{
		getline(fin, age);
		getline(fin, height);
		getline(fin, weight);
		getline(fin, male);
		getline(fin, companyName);
		getline(fin, post);

		shared_ptr<CCompany> company;
		for (auto &curCompany : companies)
		{
			if (curCompany->GetName() == companyName)
			{
				company = curCompany;
				break;
			}
		}

		unsigned curAge = strtoul(age.c_str(), NULL, 10), curHeight = strtoul(height.c_str(), NULL, 10), curWeight = strtoul(weight.c_str(), NULL, 10);
		bool isMale = (male == "Male");

		auto worker = make_shared<CWorker>(name, post, company, curAge, curHeight, curWeight, isMale);
		company->AddWorker(worker);
		res.insert(worker);
	}

	return res;
}

void SaveWorkers(const set<shared_ptr<CWorker>> &workers)
{
	ofstream fout(WORKER_FILE_NAME);

	for (auto &worker : workers)
	{
		fout << worker->GetName() << endl << worker->GetAge() << endl << worker->GetHeight() << endl << worker->GetWeight() << endl;
		fout << worker->IsMale() << endl << worker->GetCompany()->GetName() << endl << worker->GetPost() << endl;
	}
}

string GetCompanyName()
{
	string res;
	cout << "Input company name : ";
	getline(cin, res);

	return res;
}

string GetCompanyEmail()
{
	string res;
	cout << "Input company email : ";
	getline(cin, res);

	return res;
}

string GetWorkerInfo()
{
	string res;
	cout << "Input worker's name : ";
	getline(cin, res);

	return res;
}

shared_ptr<CCompany> GetCompany(const set<shared_ptr<CCompany>> &companies, const string &name)
{
	for (auto &it : companies)
	{
		if (it->GetName() == name)
		{
			return it;
		}
	}

	return nullptr;
}

void GetChangeableWorker(unsigned &age, unsigned &height, unsigned &weight, string &post)
{
	string sAge;
	cout << "Input worker's age : ";
	getline(cin, sAge);
	age = atoi(sAge.c_str());

	string sHeight;
	cout << "Input worker's height : ";
	getline(cin, sHeight);
	height = atoi(sHeight.c_str());

	string sWeight;
	cout << "Input worker's weight : ";
	getline(cin, sWeight);
	weight = atoi(sWeight.c_str());

	cout << "Input worker's post : ";
	getline(cin, post);
}

shared_ptr<CWorker> GetNewWorker(const set<shared_ptr<CCompany>> &companies)
{
	string name;
	cout << "Input worker's name : ";
	getline(cin, name);

	unsigned age, height, weight;
	string post;
	GetChangeableWorker(age, height, weight, post);

	string sMale;
	cout << "Is male ?";
	getline(cin, sMale);
	bool male = sMale == "Y";

	auto company = GetCompany(companies, GetCompanyName());

	return make_shared<CWorker>(name, post, company, age, height, weight, male);
}

shared_ptr<CWorker> GetWorker(const set <shared_ptr<CWorker>> &workers, const string &name)
{
	for (auto &it : workers)
	{
		if (it->GetName() == name)
		{
			return it;
		}
	}

	return nullptr;
}

void PrintMainActions()
{
	cout << "1. Add university" << endl;
	cout << "2. Delete university" << endl;
	cout << "3. Add student" << endl;
	cout << "4. Delete student" << endl;
	cout << "5. Change university" << endl;
	cout << "6. Change student" << endl;
	cout << "7. Change student's university" << endl;
	cout << "8. Print universities" << endl;
	cout << "9. Print students from university" << endl;
	cout << "10. Print students" << endl << endl;
	cout << "11. Add company" << endl;
	cout << "12. Delete company" << endl;
	cout << "13. Add worker" << endl;
	cout << "14. Delete worker" << endl;
	cout << "15. Change company" << endl;
	cout << "16. Change worker" << endl;
	cout << "17. Change worker's company" << endl;
	cout << "18. Print companies" << endl;
	cout << "19. Print workers from company" << endl;
	cout << "20. Print workers" << endl;
	cout << "Q. Exit" << endl;
}

void MainActions(set<shared_ptr<CUniversity>> &universities, set<shared_ptr<CStudent>> &students,
				set<shared_ptr<CCompany>> &companies, set<shared_ptr<CWorker>> &workers)
{
	string choice = "";
	PrintMainActions();
	while (choice != "Q")
	{
		getline(cin, choice);

		int c = atoi(choice.c_str());
		switch (c)
		{
			case 1:
				if (AddUniversity(universities, GetUniversityInfo()))
				{
					cout << "University has added";
				}
				else
				{
					cout << "Error adding university";
				}
				cout << endl;
				break;
			case 2:
				if (auto a = GetUniversity(universities, GetUniversityInfo()))
				{
					if (DeleteUniversity(universities, students, a))
					{
						cout << "Deleted";
					}
					else
					{
						cout << "Error deleting";
					}
					cout << endl;
				}
				break;
			case 3:
				if (auto s = GetNewStudent(universities))
				{
					if (s->GetUniversity())
					{
						AddStudent(students, s);
						cout << "Student has added";
					}
					else
					{
						cout << "Error adding";
					}
					cout << endl;
				}
				break;
			case 4:
			{
				if (auto a = GetStudent(students, GetStudentInfo()))
				{
					if (DeleteStudent(students, a))
					{
						cout << "Deleted";
					}
					else
					{
						cout << "Error deleting";
					}
					cout << endl;
				}
				break;
			}
			case 5:
			{
				string universityInfo = GetUniversityInfo();
				if (auto a = GetUniversity(universities, universityInfo))
				{
					string newName = GetUniversityInfo();
					a->SetNewName(newName);
					cout << "Name has changed";
				}
				else
				{
					cout << "Error changing name";
				}
				cout << endl;
				break;
			}
			case 6:
			{
				if (auto s = GetStudent(students, GetStudentInfo()))
				{
					unsigned age, height, weight, year;
					GetChangeableStudent(age, height, weight, year);
					s->SetAge(age);
					s->SetHeight(height);
					s->SetStudyYear(year);
					s->SetWeight(weight);
					cout << "Changed";
				}
				else
				{
					cout << "No such student";
				}
				cout << endl;
				break;
			}
			case 7:
			{
				if (auto a = GetStudent(students, GetStudentInfo()))
				{
					if (auto u = GetUniversity(universities, GetUniversityInfo()))
					{
						a->GetUniversity()->RemoveStudent(a);
						u->AddStudent(a);
						cout << "Changed";
					}
					else
					{
						cout << "No such university";
					}
				}
				else
				{
					cout << "No such student";
				}
				cout << endl;
				break;
			}
			case 8: PrintUniversities(universities); break;
			case 9:
			{
				if (auto a = GetUniversity(universities, GetUniversityInfo()))
				{
					PrintStudents(a);
				}
				else
				{
					cout << "No matches" << endl;
				}
				break;
			}
			case 10: PrintStudents(students); break;
			case 11:
				if (AddCompany(companies, GetCompanyName(), GetCompanyEmail()))
				{
					cout << "Company has added";
				}
				else
				{
					cout << "Error adding company";
				}
				cout << endl;
				break;
			case 12:
				if (auto a = GetCompany(companies, GetCompanyName()))
				{
					if (DeleteCompany(companies, workers, a))
					{
						cout << "Deleted";
					}
					else
					{
						cout << "Error deleting";
					}
					cout << endl;
				}
				break;
			case 13:
				if (auto w = GetNewWorker(companies))
				{
					if (w->GetCompany())
					{
						AddWorker(workers, w);
						cout << "Worker has added";
					}
					else
					{
						cout << "Error adding";
					}
					cout << endl;
				}
				break;
			case 14:
			{
				if (auto a = GetWorker(workers, GetWorkerInfo()))
				{
					if (DeleteWorker(workers, a))
					{
						cout << "Deleted";
					}
					else
					{
						cout << "Error deleting";
					}
					cout << endl;
				}
				break;
			}
			case 15:
			{
				string companyName = GetCompanyName();
				if (auto a = GetCompany(companies, companyName))
				{
					string newName = GetCompanyName();
					string newMail = GetCompanyEmail();
					a->SetNewName(newName);
					a->ChangeEmail(newMail);
					cout << "Name has changed";
				}
				else
				{
					cout << "Error changing name";
				}
				cout << endl;
				break;
			}
			case 16:
			{
				if (auto w = GetWorker(workers, GetWorkerInfo()))
				{
					unsigned age, height, weight;
					string post;
					GetChangeableWorker(age, height, weight, post);
					w->SetAge(age);
					w->SetHeight(height);
					w->SetPost(post);
					w->SetWeight(weight);
					cout << "Changed";
				}
				else
				{
					cout << "No such student";
				}
				cout << endl;
				break;
			}
			case 17:
			{
				if (auto w = GetWorker(workers, GetWorkerInfo()))
				{
					if (auto c = GetCompany(companies, GetCompanyName()))
					{
						w->GetCompany()->RemoveWorker(w);
						c->AddWorker(w);
						cout << "Changed";
					}
					else
					{
						cout << "No such university";
					}
				}
				else
				{
					cout << "No such student";
				}
				cout << endl;
				break;
			}
			case 18: PrintCompanies(companies); break;
			case 19:
			{
				if (auto a = GetCompany(companies, GetCompanyName()))
				{
					PrintWorkers(a);
				}
				else
				{
					cout << "No matches" << endl;
				}
				break;
			}
			case 20: PrintWorkers(workers); break;
		default:
			break;
		}

		PrintMainActions();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	auto universities = LoadUniversities();
	auto students = LoadStudents(universities);
	auto companies = LoadCompanies();
	auto workers = LoadWorkers(companies);
	MainActions(universities, students, companies, workers);

	SaveUniversities(universities);
	SaveStudents(students);
	SaveCompanies(companies);
	SaveWorkers(workers);

	return 0;
}