#pragma once

// 싱글톤을 만들고 싶다면 상속받아서 사용
template<typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		// 1) 힙 할당
		//if (_instance == nullptr)
		//{
		//	_instance = new T();
		//}
		//return _instance;

		// 2) static 변수 : 안정성
		return &_instance;
	}
	static void DestroyInstance()
	{
		//if (_instance != nullptr)
		//{
		//	delete _instance;
		//	_instance = nullptr;
		//}
	}

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	virtual void Destroy() {}

private:
	static T _instance;
};

template<typename T>
T Singleton<T>::_instance;