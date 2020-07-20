#include <iostream>

template <typename T>
class verray			// vector + array
{
public:
	verray (size_t size = 16);
	verray (const verray &other);
	verray (verray &&other);
	~verray ();

	verray &operator= (const verray &other)&;
	verray &operator= (verray &&other)&;

	void display () const;

	void CopyBuff (const verray &other);

private:
	T *data;
	size_t size;
};



template <typename T>
verray<T>::verray (size_t size) : size (size), data (new T[size]) {}



template <typename T>
verray<T>::verray (const verray<T> &other) : size (other.size), data (new T[size])
{
	CopyBuff (other);
}



template <typename T>
verray<T>::verray (verray<T> &&other) : size (other.size), data (other.data)
{
	other.data = nullptr;
	other.size = 0;
}



template <typename T>
verray<T>::~verray ()
{
	delete[] data;
}



template <typename T>
verray<T> &verray<T>::operator= (const verray<T> &other)&
{
	if (this == other) return *this;

	if (size > other.size)
	{
		size = other.size;
		CopyBuff (other);
	}
	else
	{
		delete[] data;
		size = other.size;
		data = new T[size];
		CopyBuff (other);
	}

	return *this;
}



template <typename T>
verray<T> &verray<T>::operator= (verray<T> &&other)&
{
	if (this == other) return *this;

	delete[] data;
	size = other.size;
	data = other.data;
	other.size = 0;
	other.data = nullptr;

	return *this;
}



template <typename T>
void verray<T>::display () const
{
	for (size_t i = 0; i < size; ++i) std::cout << data[i];
}



template <typename T>
void verray<T>::CopyBuff (const verray<T> &other)
{
	for (size_t i = 0; i < other.size; ++i) data[i] = other.data[i];
}



//=================
// Test
//=================
int main ()
{
	verray<int> ver_1 (28);
	ver_1.display ();
	return 0;
}