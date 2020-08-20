#include <iostream>

template <typename ValueType, typename Deleter = std::default_delete<ValueType>>
class unique_ptr
{
private:
	ValueType *pointer;

public:
	unique_ptr () : pointer (nullptr) {}
	explicit unique_ptr (ValueType *ptr) : pointer (ptr) {}

	unique_ptr            (const unique_ptr &other) = delete;
	unique_ptr &operator= (const unique_ptr &other) = delete;

	unique_ptr (unique_ptr &&other) noexcept : pointer (other.pointer)
	{ other.pointer = nullptr; }

	unique_ptr &operator= (unique_ptr &&other)
	{
		~unique_ptr ();

		pointer = other.pointer;
		other.pointer = nullptr;
	}

	~unique_ptr ()
	{
		Deleter deleter;
		deleter (pointer);
	}

	ValueType &operator* () const noexcept
	{ return *pointer; }

	ValueType &operator-> () const noexcept
	{ return pointer; }
};