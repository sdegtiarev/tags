#include <stdint.h>
#include <tuple>
#include <iostream>
#include <typeinfo>



template<typename F> struct ftr;

template<typename R, typename...Arg>
struct ftr<R(*)(Arg...)>
{
	typedef R result;
 	enum { arity = sizeof...(Arg) };
	template <size_t i> struct arg {
 		typedef typename std::tuple_element<i, std::tuple<Arg...>>::type type;
 	};
};

template<typename FN>
void detect(FN f)
{
    typedef ftr<FN> fn;
    std::cout<<typeid(typename fn::result).name()<<"(";
    if(fn::arity > 0)
    	std::cout<<typeid(typename fn::template arg<0>::type).name();
    if(fn::arity > 1)
		std::cout<<", "<<typeid(typename fn::template arg<1>::type).name();
  //   if(fn::arity > 2)
		// std::cout<<", "<<typeid(typename fn::template arg<2>::type).name();
	std::cout<<")\n";
}


int fn(int,long) {};

int main()
{
	detect(fn);
}
