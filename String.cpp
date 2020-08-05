#include <iostream>

class String
{
private:

	char *str;
	size_t size;
	void reallocate (const size_t sz);
	void copy (const char *buff);

public:
	~String ();
	String (const size_t sz = 16);
	String (const char *sym_arr, size_t sz);
	String (const String &other);
	String &operator= (const String &other) &;
	String (String &&other);
	String &operator= (String &&other) &;

	//String &operator+ (const String &other);
	char &operator[] (size_t pos);
	const char &operator[] (size_t pos) const;
};


// Destructor
String::~String ()
{
	delete[] str;
}


// Constructor from size
String::String (const size_t sz) : size (sz), str (new char[sz]) {}


// Constructor from raw string
String::String (const char *sym_arr, size_t sz) : String (size)
{
	copy (sym_arr);
}


// Copy constructor
String::String (const String &other) : String (other.str, other.size) {}


// Copy assignment
String &String::operator= (const String &other) &
{
	if (this != &other)
	{
		reallocate (other.size);
		copy (other.str);
	}
	return *this;
}


// Move constructor
String::String (String &&other) : str (other.str), size (other.size)
{
	other.str = nullptr;
	other.size = 0;
}


// Move assignment
String &String::operator= (String &&other) &
{
	if (this != &other)
	{
		delete[] str;
		str = other.str;
		size = other.size;
		other.str = nullptr;
		other.size = 0;
	}
	return *this;
}



char &String::operator[] (size_t pos)
{
	return *(str + pos);
}



const char &String::operator[] (size_t pos) const
{
	return *(str + pos);
}



void String::reallocate (const size_t sz)
{
	if (size < sz)
	{
		delete[] str;
		str = new char[sz];
	}
	size = sz;
}



void String::copy (const char *buff)
{
	for (int i = 0; i < size; ++i)
	{
		str[i] = buff[i];
	}
}



int main ()
{
	String str_1;
	String str_2 = str_1;


	return 0;
}