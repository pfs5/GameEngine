#pragma once
template <class T>
class WeakPtr
{
public:
	WeakPtr():
		_object{nullptr}
	{
	}

	WeakPtr(T* objectPtr):
		_object{objectPtr}
	{
	}

	~WeakPtr()
	{
		delete _object;
	}

	T* Get() const
	{
		return _object;
	}

	bool IsValid() const
	{
		return _object != nullptr;
	}

	T* operator->() const
	{
		return _object;
	}

	WeakPtr& operator=(T* const other)
	{
		if (_object != nullptr)
		{
			delete _object;
		}

		_object = other;

		return *this;
	}

private:
	T * _object;
};
