class String
{
private:

	char *str;
	unsigned int size;
	void reallocate (const unsigned int sz);
	void copy (const char *buff);

public:
	~String ();
	String (const unsigned int sz = 16);
	String (const String &other);
	String &operator= (const String &other) &;
	String (String &&other);
	String &operator= (String &&other) &;

	//String &operator+ (const String &other);
};


// Constructor from size
String::String (const unsigned int sz) : size (sz), str (new char[sz]) {}


// Destructor
String::~String ()
{
	delete[] str;
}


// Copy constructor
String::String (const String &other) : str (new char[other.size]), size (other.size)
{
	copy (other.str);
}


// Copy assignment
String &String::operator= (const String &other) &
{
	if (this != &str)
	{
		reallocate (other.size);
		copy (other.str);
	}
	return *this;
}


// Move constructor
String::String (String &&other)
{

}


// Move assignment
String &String::operator= (String &&other) &
{

}



void String::reallocate (const unsigned int sz)
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
	String str;
	return 0;
}