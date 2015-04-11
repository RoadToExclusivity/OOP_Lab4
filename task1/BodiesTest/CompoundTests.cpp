#include "stdafx.h"
#include "../Bodies/Cylinder.h"
#include "../Bodies/Compound.h"
#include "../Bodies/Sphere.h"
#include "../Bodies/Parallelepiped.h"

using namespace std;

static const double EXPECTED_RADIUS_CYLINDER = 3.5;
static const double EXPECTED_RADIUS_SPHERE = 7.5;
static const double EXPECTED_DENSITY_CYLINDER = 7000;
static const double EXPECTED_DENSITY_SPHERE = 4000;
static const double EXPECTED_DENSITY_PARAL = 100;
static const double EXPECTED_WIDTH_PARAL = 10;
static const double EXPECTED_HEIGHT_PARAL = 4;
static const double EXPECTED_DEPTH_PARAL = 55;
static const double EXPECTED_HEIGHT_CYLINDER = 23;

struct CompoundFixture
{
	CCompound comp;
	CCylinder cyl;
	CSphere sphere;
	CParallelepiped p;

	CompoundFixture()
		:comp(), 
		cyl(EXPECTED_RADIUS_CYLINDER, EXPECTED_HEIGHT_CYLINDER, EXPECTED_DENSITY_CYLINDER),
		sphere(EXPECTED_RADIUS_SPHERE, EXPECTED_DENSITY_SPHERE),
		p(EXPECTED_WIDTH_PARAL, EXPECTED_HEIGHT_PARAL, EXPECTED_DEPTH_PARAL, EXPECTED_DENSITY_PARAL)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Compound, CompoundFixture)

BOOST_AUTO_TEST_CASE(AddOneElement)
{
	comp.AddBody(make_shared<CSphere>(sphere));
	BOOST_CHECK_EQUAL(comp.GetVolume(), sphere.GetVolume());
	BOOST_CHECK_EQUAL(comp.GetDensity(), sphere.GetDensity());
	BOOST_CHECK_EQUAL(comp.GetMass(), sphere.GetMass());
}

BOOST_AUTO_TEST_CASE(AddAllElements)
{
	comp.AddBody(make_shared<CSphere>(sphere));
	comp.AddBody(make_shared<CParallelepiped>(p));
	comp.AddBody(make_shared<CCylinder>(cyl));
	double mass = sphere.GetMass() + p.GetMass() + cyl.GetMass();
	double volume = sphere.GetVolume() + p.GetVolume() + cyl.GetVolume();
	BOOST_CHECK_EQUAL(comp.GetVolume(), volume);
	BOOST_CHECK_EQUAL(comp.GetDensity(), mass / volume);
	BOOST_CHECK_EQUAL(comp.GetMass(), mass);
}
BOOST_AUTO_TEST_SUITE_END()