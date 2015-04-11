#include "stdafx.h"
#include "../Bodies/Cone.h"

static const double EXPECTED_RADIUS = 10;
static const double EXPECTED_HEIGHT = 2.23;
static const double EXPECTED_DENSITY = 7777;

struct ConeFixture
{
	CCone cone;

	ConeFixture()
		:cone(EXPECTED_RADIUS, EXPECTED_HEIGHT, EXPECTED_DENSITY)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Cone, ConeFixture)

BOOST_AUTO_TEST_CASE(HasRadius)
{
	BOOST_CHECK_EQUAL(cone.GetRadius(), EXPECTED_RADIUS);
	BOOST_CHECK_EQUAL(cone.GetHeight(), EXPECTED_HEIGHT);
}

BOOST_AUTO_TEST_CASE(HasVolume)
{
	const double EXPECTED_VOLUME = M_PI / 3 * pow(EXPECTED_RADIUS, 2) * EXPECTED_HEIGHT;
	BOOST_CHECK_EQUAL(cone.GetVolume(), EXPECTED_VOLUME);
	CBody &coneAsBody = cone;
	BOOST_CHECK_EQUAL(coneAsBody.GetVolume(), EXPECTED_VOLUME);
}

BOOST_AUTO_TEST_CASE(HasDensity)
{
	BOOST_CHECK_EQUAL(cone.GetDensity(), EXPECTED_DENSITY);
}

BOOST_AUTO_TEST_CASE(HasMass)
{
	BOOST_CHECK_EQUAL(cone.GetMass(), EXPECTED_DENSITY * cone.GetVolume());
}

BOOST_AUTO_TEST_SUITE_END()

