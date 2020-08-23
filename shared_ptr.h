#include <iostream>

template <typename ValueType>
struct Helper
{
	ValueType *pointer;
	size_t count;
};



template <typename ValueType>
class shared_ptr
{
private:
	Helper<ValueType> *h;

public:
	shared_ptr () = default;

	shared_ptr (ValueType *ptr) : h (new Helper<ValueType>)
	{
		h->pointer = ptr;
		h->count = 1;
	}

	shared_ptr (const shared_ptr &other) : h (other.h)
	{ ++h->count; }

	shared_ptr &operator= (const shared_ptr &other)
	{
		if (this == &other)
			return *this;

		h = other.h;
		++h->count;

		return *this;
	}

	shared_ptr (shared_ptr &&other) : h (other.h)
	{ other.h = nullptr; }

	shared_ptr &operator= (shared_ptr &&other)
	{
		if (this == &other)
			return *this;

		h = other.h;
		other.h = nullptr;

		return *this;
	}

	~shared_ptr ()
	{
		if (h->count == 1)
		{
			delete h->pointer;
			delete h;
		}
		else
			h->count--;
	}


	ValueType &operator* () const noexcept
	{ return *h->pointer; }

	ValueType *operator-> () const noexcept
	{ return h->pointer; }

	size_t use_count ()
	{ return h->count; }
};



template <typename T, typename... Args>
shared_ptr<T> make_shared (Args &&... args)
{ return shared_ptr<T> (new T (std::forward<Args> (args)...)); }