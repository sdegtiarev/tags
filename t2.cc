#include <stdint.h>
#include <tuple>
#include <iostream>
#include <typeinfo>

template<typename T> struct func_traits;

template<typename R, typename...Arg>
struct func_traits<R(*)(Arg...)>
{
    enum { arity = sizeof...(Arg) };

    typedef R result;
    template <size_t i> struct arg {
        typedef typename std::tuple_element<i, std::tuple<Arg...>>::type type;
    };
};






// template<typename FN>
// void detect(FN f)
// {
//     //typedef typename std::enable_if<std::is_function<FN>::value,int>::type itype;
//     typedef func_traits<FN> fn;
//     std::cout
//         <<typeid(typename fn::result).name()
//         <<"("<<fn::arity<<")\n";
// }
template<typename FN>
void detect(FN f)
{
    typedef func_traits<FN> fn;
    std::cout<<typeid(typename fn::result).name()<<"(";
    if(fn::arity > 0)
        std::cout<<typeid(typename fn::template arg<0>::type).name();
    if(fn::arity > 1)
        std::cout<<", "<<typeid(typename fn::template arg<1>::type).name();
  //   if(fn::arity > 2)
        // std::cout<<", "<<typeid(typename fn::template arg<2>::type).name();
    std::cout<<")\n";
}

double fn(int,long) {}


int main()
{
	int x,y;
	auto lambda = [x,&y](int i,int) { return long(i*10); };
	typedef func_traits<decltype(fn)> traits;
	//detect(lambda);
	
	detect(fn);

    return 0;
}