#ifndef PROSPECT_SINGLETON
#define PROSPECT_SINGLETON

namespace Prospect {

    template <class T>
    class Singleton
    {
    public:
	static T& Instance() {
	    static T instance;
	    return instance;
	}

    private:
	Singleton(){}
	~Singleton(){}
	Singleton(Singleton const&){}
	Singleton& operator=(Singleton const&){}
    };
}

#endif
