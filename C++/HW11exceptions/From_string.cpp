#include <iostream>
#include <sstream>
#include <exception>
#include <typeinfo>

class bad_from_string : public std::exception
{
	public:
    explicit bad_from_string(const std::string& string = "")
	: mMessage(string) {}
	
    const char* what() const noexcept override
	{
        return mMessage.data();
	}
    
	private:
	    std::string mMessage;
};


template <typename T>
T from_string(const std::string& s)
{
	if (s.empty())
	{
		throw bad_from_string("Empty string given");
	}
	T out;
    std::istringstream stream(s);
    
    stream >> std::noskipws >> out; 
    if (stream.fail() || stream.peek() != EOF)
    {
    	throw bad_from_string(("Failed to convert " + s + " to " 
								+ typeid(T).name()).data());
    }
    
	return out;
}


template <typename T>
void check(T& result, const std::string& string)
{
	try
	{
		result = from_string <T>(string);
		std::cout << result << " converted to " << typeid(T).name() << '\n';
	} catch (const bad_from_string& e)
	{
		std::cerr << e.what() << '\n';
	}
}

int main()
{
	std::string s1("123");
	int a1;
	check <int>(a1, s1); // a1 = 123
	double b1;
	check <double>(b1, s1); // b1 = 123.0
	std::string c1;
	check <std::string>(c1, s1); // c1 = "123"
	
	std::string s2("12.3");
	int a2;
	check <int>(a2, s2); // exception
	double b2;
	check <double>(b2, s2); // b2 = 12.3
	std::string c2;
	check <std::string>(c2, s2); // c2 = "12.3"
	
	std::string s3("abc"); //0x1.47ae147ae147bp-7
	int a3;
	check <int>(a3, s3); // exception
	double b3;
	check <double>(b3, s3); // exception
	std::string c3;
	check <std::string>(c3, s3); // c3 = "abc"
}
