#pragma once
template<class T> class Singleton
{
public:
	Singleton()
	{
		spSingleton = static_cast<T*>(this);
	}

	virtual ~Singleton()
	{
		spSingleton = nullptr;
	}

	static T& Get() {
		return *spSingleton;
	}

private:
	static T* spSingleton;
	Singleton(Singleton const&) = delete;
	void operator=(Singleton const&) = delete;
};

template<typename T> T* Singleton<T>::spSingleton = 0;