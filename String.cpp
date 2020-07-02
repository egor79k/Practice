class String
{
private:

	char *str;
	unsigned int size;

public:
	String (const unsigned int sz = 16);
	~String ();
	String (const String &str);
	String &operator= (const String &str);
	String &operator+ (const String &str);
};



String::String (const unsigned int sz) : size (sz)
{
	str = new char[sz];
}



String::~String ()
{
	delete[] str;
}



String::String (const String &str)
{

}



int main ()
{
	String str;
	return 0;
}