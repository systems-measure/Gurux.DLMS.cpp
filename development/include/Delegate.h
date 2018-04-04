#pragma once

// URL SRC: https://habrahabr.ru/post/78299/

///////////////////////////////////////
// -- Argument
///////////////////////////////////////
class IArgument { public: virtual ~IArgument() {} };
template<class T> class Argument : public IArgument {
public:
	T arg;
	Argument(T t_arg) : arg(t_arg) {}
};
///////////////////////////////////////
// -- Conteiner
///////////////////////////////////////
class IConteiner { 
public: 
    virtual ~IConteiner(){}
    virtual void Call(IArgument* piarg) {}; 
};
template<class T, class K> class Conteiner : public IConteiner {};
template<class T, class A> class Conteiner<T, void (T::*)(A)> : public IConteiner {
	public:
		typedef void (T::*M)(A);

		T* t_class; M m_method;
	public:
		Conteiner(T* t, M m) : t_class(t), m_method(m) {}
		void Call(IArgument* piarg) {
			Argument<A>* parg = dynamic_cast<Argument<A>*>(piarg);
			//assert(parg);
			if (parg) (t_class->*m_method)(parg->arg);
		}
};

class Delegate{
private:
	IConteiner* m_conteiner;

public:
	Delegate() : m_conteiner(0) {}
	~Delegate() { if (m_conteiner) delete m_conteiner; }
	template<class T, class M> void Connect(T* t_class, M m_method) {
		if (m_conteiner) delete m_conteiner;

		m_conteiner = new Conteiner<T, M>(t_class, m_method);
	}
	template<class T>void operator()(T arg) {
		if (m_conteiner) {
            Argument<T> value_delegate{arg};
            
			m_conteiner->Call(&value_delegate);
		}
	}
};
