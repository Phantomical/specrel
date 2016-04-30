#pragma once

template<typename vTy>
struct ptr_ref
{
public:
	typedef vTy value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;

	ptr_ref() = default;
	ptr_ref(pointer vptr) :
		ptr(vptr)
	{

	}

	ptr_ref& operator =(const ptr_ref& o)
	{
		ptr = o.ptr;
		return *this;
	}
	ptr_ref& operator =(pointer v)
	{
		ptr = v;
		return *this;
	}

	bool operator ==(const ptr_ref& ref) const
	{
		return ref.ptr == ptr;
	}
	bool operator !=(const ptr_ref& ref) const
	{
		return ref.ptr != ptr;
	}
	bool operator ==(const_pointer vptr) const
	{
		return ptr == vptr;
	}
	bool operator !=(const_pointer vptr) const
	{
		return ptr != vptr;
	}

	operator bool() const
	{
		return ptr;
	}
	bool operator !() const
	{
		return !ptr;
	}

	pointer operator ->()
	{
		return ptr;
	}
	const_pointer operator ->() const
	{
		return ptr;
	}

	pointer get()
	{
		return ptr;
	}
	const_pointer get() const
	{
		return ptr;
	}

private:
	pointer ptr;
};
