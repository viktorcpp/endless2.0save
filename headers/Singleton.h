#pragma once

namespace endless
{
	template <typename T> class Singleton
	{
	public:

		/** Конструктор **/
		Singleton()
		{
			_instance = static_cast<T*>(this);
		}

		/* Возвращает указатель */
		static T* Ref()
		{
			return _instance;
		}

		virtual ~Singleton(){}

	protected:

		static T* _instance;

	}; // Singleton

} // endless

/*
class SomeClass : public Singleton<SomeClass>
template<> SomeClass* Singleton<SomeClass>::_instance = 0;
*/
