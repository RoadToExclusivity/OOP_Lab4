#include "stdafx.h"
#include "../task2/Student.h"
#include "../task2/University.h"

using namespace std;

const string NAME = "STUDENT POLITEHA";
const int STUDY_YEAR = 2, AGE = 12, HEIGHT = 190, WEIGHT = 50;

struct StudentFixture
{
	CStudent student;

	StudentFixture()
		:student(NAME, STUDY_YEAR, nullptr, AGE, HEIGHT, WEIGHT, true)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(StudentText, StudentFixture)

BOOST_AUTO_TEST_CASE(StudentDefaultParams)
{
	BOOST_CHECK_EQUAL(student.GetAge(), AGE);
	BOOST_CHECK_EQUAL(student.GetHeight(), HEIGHT);
	BOOST_CHECK_EQUAL(student.GetWeight(), WEIGHT);
	BOOST_CHECK_EQUAL(student.GetStudyYear(), STUDY_YEAR);
	BOOST_CHECK_EQUAL(student.GetName(), NAME);
	BOOST_CHECK_EQUAL(student.IsMale(), true);
}

BOOST_AUTO_TEST_CASE(StudentWithChangedParams)
{
	shared_ptr<CUniversity> pgtu = make_shared<CUniversity>("PGTU");
	shared_ptr<CStudent> stPtr = make_shared<CStudent>(student);
	BOOST_CHECK_EQUAL(pgtu->AddStudent(stPtr), true);

	stPtr->SetAge(AGE + 10);
	stPtr->SetHeight(HEIGHT + 10);
	stPtr->SetName(NAME + "2");
	stPtr->SetWeight(WEIGHT + 10);

	BOOST_CHECK_EQUAL(stPtr->GetAge(), AGE + 10);
	BOOST_CHECK_EQUAL(stPtr->GetHeight(), HEIGHT + 10);
	BOOST_CHECK_EQUAL(stPtr->GetWeight(), WEIGHT + 10);
	BOOST_CHECK_EQUAL(stPtr->GetStudyYear(), STUDY_YEAR);
	BOOST_CHECK_EQUAL(stPtr->GetName(), NAME + "2");
	BOOST_CHECK_EQUAL(stPtr->IsMale(), true);
	BOOST_CHECK_EQUAL(stPtr->GetUniversity(), pgtu);
}

BOOST_AUTO_TEST_SUITE_END()