
struct counter
{
	size_t shared;
	size_t weak;

	counter () = delete;

	counter (size_t _shared, size_t _weak) : shared (_shared), weak (_weak) {}

	~counter () = default;
}



template <typename ValueType>
class weak_ptr
{
private:
	counter *count
	ValueType *pointer;

public:
	constexpr weak_ptr () noexcept :
		pointer (nullptr),
		count (new counter (1, 0))
	{}

	weak_ptr (const weak_ptr &other) noexcept :
		pointer (other.pointer),
		count (other.count)
	{ ++count->weak; }

	weak_ptr (weak_ptr &&other) noexcept :
		pointer (other.pointer),
		count (other.count)
	{
		other.pointer = nullptr;
		other.count = nullptr;
	}

	weak_ptr (const shared_ptr<ValueType> &init) noexcept :
		pointer (init.pointer),
		count (init.count)
	{ ++count->weak; }

	~weak_ptr ()
	{
		if (count->shared == 0 && count->weak == 0)
			delete count;
		else
			--count->weak;
	}

	weak_ptr &operator= (const weak_ptr &other)
	{
		if (this == &other)
			return *this;

		~weak_ptr ();
		pointer = other.pointer;
		count = other.count;
		++count->weak;
		return *this;
	}

	weak_ptr &operator= (weak_ptr &&other)
	{
		if (this == &other)
			return *this;

		~weak_ptr ();
		pointer = other.pointer;
		count = other.count;
		other.pointer = nullptr;
		other.count = nullptr;
		return *this;
	}

	bool expired () const
	{ return count->shared == 0; }

	shared_ptr<ValueType> lock () const noexcept
	{ return expired () ? shared_ptr () : shared_ptr (count, pointer); }
};