#pragma once

#include <cmath>

const int NAME_SIZE = 20, ADM_NUM_SIZE = 4, MARKS_AMOUNT = 5,
		  FIVE_DIGITS = pow(10, ADM_NUM_SIZE);

class OverflowException : public std::exception {};

class Report {
	public:
		Report();
		Report(const std::string);
		
		void readInfo(const short, const std::string,
					  const float*) throw (OverflowException);
		void displayInfo() const;
		
	private:
		std::string mName;
		short mAdmissionNumber;
		float mAverage;
		float mMarks[MARKS_AMOUNT];
		
		float getAvg();
		
		void setZero();
};
