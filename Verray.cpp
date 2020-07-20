#include <iostream>

template <typename T>
class verray			// vector + array
{
public:
	verray (const size_t sz = 16);
	verray (const verray &other);
	verray (verray &&other);
	~verray ();

	verray &operator= (const verray &other)&;
	verray &operator= (verray &&other)&;

	T &operator[] (const size_t index);
	const T &operator[] (const size_t index) const;

	size_t size () const;

	void display () const;

	void CopyBuff (const verray &other);

private:
	T *data;
	size_t sz;
};



template <typename T>
verray<T>::verray (const size_t sz) : sz (sz), data (new T[sz]) {}



template <typename T>
verray<T>::verray (const verray<T> &other) : sz (other.sz), data (new T[sz])
{
	CopyBuff (other);
}



template <typename T>
verray<T>::verray (verray<T> &&other) : sz (other.sz), data (other.data)
{
	other.data = nullptr;
	other.sz = 0;
}



template <typename T>
verray<T>::~verray ()
{
	delete[] data;
}



template <typename T>
verray<T> &verray<T>::operator= (const verray<T> &other)&
{
	if (this == &other) return *this;

	if (sz > other.sz)
	{
		sz = other.sz;
		CopyBuff (other);
	}
	else
	{
		delete[] data;
		sz = other.sz;
		data = new T[sz];
		CopyBuff (other);
	}

	return *this;
}



template <typename T>
verray<T> &verray<T>::operator= (verray<T> &&other)&
{
	if (this == &other) return *this;

	delete[] data;
	sz = other.sz;
	data = other.data;
	other.sz = 0;
	other.data = nullptr;

	return *this;
}



template <typename T>
T &verray<T>::operator[] (const size_t index)
{
	return data[index];
}



template <typename T>
const T &verray<T>::operator[] (const size_t index) const
{
	return data[index];
}



template <typename T>
size_t verray<T>::size () const
{
	return sz;
}



template <typename T>
void verray<T>::display () const
{
	for (size_t i = 0; i < sz; ++i) std::cout << data[i] << ' ';
}



template <typename T>
void verray<T>::CopyBuff (const verray<T> &other)
{
	for (size_t i = 0; i < other.sz; ++i) data[i] = other.data[i];
}



//=================
// Test
//=================
int main ()
{
	// Test 1
	verray<int> ver_1 (28);

	std::cout << '\n';
	
	ver_1.display ();
	std::cout << '\n';

	ver_1[5] = 24;
	ver_1[0] = 6.1;

	ver_1.display ();
	std::cout << '\n';


	// Test 2
	const verray<int> ver_2;

	std::cout << '\n';
	
	ver_2.display ();
	std::cout << '\n';

	std::cout << "ver_2[5] = " << ver_2[5] << '\n';


	// Test 3
	ver_1 = ver_2;

	std::cout << '\n';
	
	ver_1.display ();
	std::cout << '\n';

	for (int i = 0; i < ver_1.size (); ++i) ver_1[i] = 14;

	ver_1[3] = 25;

	ver_1.display ();
	std::cout << '\n';

	return 0;
}