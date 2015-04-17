#pragma once
#include "Student.h"

class CUniversity : public std::enable_shared_from_this<CUniversity>
{
public:
	CUniversity(const std::string &name);
	~CUniversity();
	
	std::string GetName() const;
	std::set<std::shared_ptr<CStudent>> GetStudentsList() const;
	bool AddStudent(const std::shared_ptr<CStudent> &student);
	bool RemoveStudent(const std::shared_ptr<CStudent> &student);
	void SetNewName(const std::string &newName);

private:
	std::string m_name;
	std::set<std::shared_ptr<CStudent>> m_students;
};

