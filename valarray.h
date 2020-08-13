

template <typename T>
class valarray
{
private:
	size_t sz;
	T *data;

public:
	valarray () : sz (0), data (nullptr) {}
	explicit valarray (size_t size) : sz (size), data (new T[size]) {}
	valarray (const T &val, size_t size);
	valarray (const T *vals, size_t size) : sz (size), data (vals) {}

	valarray (const valarray &other);
	valarray (valarray &&other) noexcept;

	valarray &operator= (const valarray &other);
	valarray &operator= (valarray &&other) noexcept;
	valarray &operator= (const T &val);

	~valarray ();
};



template <typename T>
valarray<T>::valarray (const T &val, size_t size) :
	sz (size),
	data ((T *) new char[size * sizeof (T)])
{
	for (size_t i = 0; i < sz; ++i)
		new (&data[i]) T (val);
}



template <typename T>
valarray<T>::~valarray ()
{
	delete[] data;
}



template <typename T>
valarray<T>::valarray (const valarray &other) :
	sz (other.sz),
	data ((T *) new char[other.sz * sizeof (T)])
{
	for (size_t i = 0; i < other.sz; ++i)
		new (&data[i]) T(other.data[i]);
}



