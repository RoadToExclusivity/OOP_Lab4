#pragma once

class CPerson
{
public:
	CPerson(const std::string name, unsigned age, unsigned height, unsigned weight, bool isMale);
	virtual ~CPerson();

	bool IsMale() const;
	unsigned GetAge() const;
	unsigned GetHeight() const;
	unsigned GetWeight() const;
	std::string GetName() const;

	void SetAge(unsigned age);
	void SetHeight(unsigned height);
	void SetWeight(unsigned weight);
	void SetName(const std::string &name);

private:
	bool m_isMale;

	unsigned m_age;
	unsigned m_height;
	unsigned m_weight;

	std::string m_name;
};

