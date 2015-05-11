#pragma once
#include "Student.h"
#include "Establishment.h"

class CUniversity : public CEstablishment, public std::enable_shared_from_this<CUniversity>
{
public:
	CUniversity(const std::string &name);

	std::set<std::shared_ptr<CStudent>> GetStudentsList() const;
	bool AddStudent(const std::shared_ptr<CStudent> &student);
	bool RemoveStudent(const std::shared_ptr<CStudent> &student);
};