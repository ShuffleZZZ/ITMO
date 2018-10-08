#include <iostream>
#include <iomanip>

#include "Report.h"


Report::Report()
{
	setZero();
	mName = "";
}

Report::Report(const std::string name) : mName(name)
{
	setZero();
}

void Report::setZero() 
{
	mAverage = 0;
	mAdmissionNumber = 0;
	for(int i = 0; i < MARKS_AMOUNT; ++i)
	{	
		mMarks[i] = 0;
	}
}

void Report::readInfo(const short admissionNumber, const std::string name,
				      const float marks[MARKS_AMOUNT]) throw (OverflowException)
{
	if (name.size() > NAME_SIZE || admissionNumber >= FIVE_DIGITS)
	{
		throw OverflowException();
		return;
	}
	mName = name;
	mAdmissionNumber = admissionNumber;
	for (int i = 0; i < MARKS_AMOUNT; ++i)
	{
		mMarks[i] = marks[i];
	}
	mAverage = getAvg();
}

void Report::displayInfo() const
{
	std::cout << "AdmissionNumber: " << std::setw(ADM_NUM_SIZE)
	          << std::setfill('0') << mAdmissionNumber << '\n'
	          << "Name: " << mName << '\n'
	          << "Marks:";
	for (int i = 0; i < MARKS_AMOUNT; ++i)
	{
		std::cout << ' ' << mMarks[i];
	}
	std::cout << "\nAverage: " << mAverage << '\n';
}

float Report::getAvg() 
{
	float sum = 0.0;
	for (int i = 0; i < MARKS_AMOUNT; ++i)
	{
		sum += mMarks[i];
	}
	return sum / MARKS_AMOUNT;
}


int main() {
	Report C;
	std::string name;
	short admissionNumber;
	float marks[MARKS_AMOUNT];
	
	std::cin >> name >> admissionNumber;
	for (int i = 0; i < MARKS_AMOUNT; ++i)
	{
		std::cin >> marks[i];
	}
	//C.displayInfo();
	
	try 
	{
		C.readInfo(admissionNumber, name, marks);
	} 
	catch (OverflowException& e)
	{
		std::cout << "overflow, enter valid data\n";
		return 0;
	}
	C.displayInfo();
}
