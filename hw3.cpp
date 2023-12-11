//add try catch

#include <iostream>

struct DayExceptionError
{
	int day;

};

struct MonthExceptionError
{
	int month;

};

struct YearExceptionError
{
	int year;

};



class Date
{
private:
	int day;
	int month;
	int year;

public:

	Date(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
		int MaxDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		{
			MaxDay[1] = 29;
		}
		else
		{
			MaxDay[1] = 28;
		}


		if (y < 0)
		{
			throw YearExceptionError(y);
		}

		if (m < 1 || m > 12)
		{
			throw MonthExceptionError(m);
		}

		if (d < 1 || d>MaxDay[m - 1])
		{
			throw DayExceptionError(d);
		}

		
	}
	Date() = default;
	int GetDays() const;
	int GetMonths() const;
	int GetYears() const;
	
	Date(int d) :Date(d, 1, 1) 
	{
		int MaxDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (day < 1 || day>MaxDay[month-1])
		{
			throw DayExceptionError(day);
		}
		
	}

	//leap year
	bool isLeapYear()
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			std::cout << "Leap year!" << "\n";
			return true;

		}
		else
		{
			std::cout << "Isn't Leap year!" << "\n";
			return false;
		}
	}


	//operator overloading +=
	Date& operator+= (int d)
	{
		day += d;
		Date(day, month, year);
		return *this;
	}

	//operator overloading +
	Date operator+ (int d) const
	{
		return Date(day + d, month, year);
	}

	//add days
	void AddDays(int d)
	{
		day += d;
		Date(day, month, year);
	}

	//operator overloading -
	Date operator- (int d) const
	{
		return Date(day - d, month, year);
	}

	//subtract days
	void Subtract(int d)
	{
		day -= d;
		Date(day, month, year);
	}

};



int Date::GetDays() const
{
	return day;
}
int Date::GetMonths() const
{
	return month;
}
int Date::GetYears() const
{
	return year;
}




//operator overloading <<
std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.GetDays() << ":" << date.GetMonths() << ":" << date.GetYears();
	return out;
}

//operator overloading >>
std::istream& operator>>(std::istream& in, Date& date)
{
	std::cin.exceptions(std::istream::failbit);
	int d;
	int m;
	int y;
	char ch;
	in >> d >> ch;
	in >> m >> ch;
	in >> y >> ch;
	date = Date(d, m, y);
	return in;

}


int main()
{
	try
	{
		Date date(-1, 12, 2008);


	}
	catch (const DayExceptionError& ex)
	{
		std::cerr << "Error!\nIncorrect day: " << ex.day << std::endl;
		return 1;
	}
	catch (const MonthExceptionError& ex)
	{
		std::cerr << "Error!\nIncorrect month: " << ex.month << std::endl;
		return 2;
	}
	catch (const YearExceptionError& ex)
	{
		std::cerr << "Error!\nIncorrect year: " << ex.year << std::endl;
		return 3;
	}
	catch (const std::istream::failure& ex)
	{
		std::cerr << "Failed to read date " << ex.what() << "\n";
		return 4;
	}
	catch (...)
	{
		std::cerr << "Other failure " << "\n";
		return 5;
	}
	

	return 0;
}
