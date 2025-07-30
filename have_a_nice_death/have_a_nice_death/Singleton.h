#pragma once

// �̱����� ����� �ʹٸ� ��ӹ޾Ƽ� ���
template<typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		// 1) �� �Ҵ�
		//if (_instance == nullptr)
		//{
		//	_instance = new T();
		//}
		//return _instance;

		// 2) static ���� : ������
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
	// �����ڿ� �Ҹ��ڸ� protected�� �����Ͽ� �ܺο��� ���� ����/������ ����
	Singleton() = default;
	virtual ~Singleton() = default;

	// ���� �� �̵� ����
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	virtual void Destroy() {}

private:
	//static T* _instance;	// �� �������ε� ��ӱ����� �̱��� ���� ����
	static T _instance;	// �� �������ε� ��ӱ����� �̱��� ���� ����
};

// ���� ��� �ʱ�ȭ
//template<typename T>
//T* Singleton<T>::_instance = nullptr;

// ���� ��� ����
template<typename T>
T Singleton<T>::_instance;