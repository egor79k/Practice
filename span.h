template <typename T>
class span
{
private:
	T *start = nullptr;
	size_t size = 0;

public:
	span () noexcept = default;
	span (const span &other) noexcept = default;
	span &operator= (const span &other) noexcept = default;
	~span () noexcept = default;

	span (T *ptr, size_t sz) : start (ptr), size (sz)
	{
		if (sz < 0) throw std::out_of_range ("size < 0");
	}

	const T &operator[] (size_t index) const {return *(start + index);}
	const T &operator() (size_t index) const {return *(start + index);}

	const T &front () const {return *start;}
	const T &back  () const {return *(start + size);}
	const T *data  () const {return start;}

	const bool empty   () const {return size == 0;}
	const size_t size_ () const {return size;}
	const size_t size_bytes () const {return size * sizeof (T);}

	const span first (size_t sz) const
	{
		if (sz > size) throw std::out_of_range ("new_size > size");
		return span (start, sz);
	}

	const span last (size_t sz) const
	{
		if (sz > size) throw std::out_of_range ("new_size > size");
		return span (start + size - sz, sz);
	}

	const span subspan (size_t from, size_t sz) const
	{
		if (from + sz > size) throw std::out_of_range ("wrong subspan args");
		return span (start + from, sz);
	}
};