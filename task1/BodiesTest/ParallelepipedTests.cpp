#include "stdafx.h"
#include "../Bodies/Parallelepiped.h"

static const double EXPECTED_WIDTH = 3.5;
static const double EXPECTED_HEIGHT = 4;
static const double EXPECTED_DEPTH = 5;
static const double EXPECTED_DENSITY = 5000;

struct ParallelepipedFixture
{
	CParallelepiped p;

	ParallelepipedFixture()
		:p(EXPECTED_WIDTH, EXPECTED_HEIGHT, EXPECTED_DEPTH, EXPECTED_DENSITY)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Parallelepiped, ParallelepipedFixture)

BOOST_AUTO_TEST_CASE(HasParameters)
{
	BOOST_CHECK_EQUAL(p.GetWidth(), EXPECTED_WIDTH);
	BOOST_CHECK_EQUAL(p.GetHeight(), EXPECTED_HEIGHT);
	BOOST_CHECK_EQUAL(p.GetDepth(), EXPECTED_DEPTH);
}

BOOST_AUTO_TEST_CASE(HasVolume)
{
	double EXPECTED_VOLUME = EXPECTED_WIDTH * EXPECTED_HEIGHT * EXPECTED_DEPTH;
	BOOST_CHECK_EQUAL(p.GetVolume(), EXPECTED_VOLUME);
	CBody &pAsBody = p;
	BOOST_CHECK_EQUAL(pAsBody.GetVolume(), EXPECTED_VOLUME);
}

BOOST_AUTO_TEST_CASE(HasDensity)
{
	BOOST_CHECK_EQUAL(p.GetDensity(), EXPECTED_DENSITY);
}

BOOST_AUTO_TEST_CASE(HasMass)
{
	BOOST_CHECK_EQUAL(p.GetMass(), EXPECTED_DENSITY * p.GetVolume());
}


BOOST_AUTO_TEST_SUITE_END()

