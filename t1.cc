#include <stdint.h>
#include <tuple>
#include <iostream>
#include <typeinfo>

template <typename T>
struct lambda_traits
: public lambda_traits<decltype(&T::operator())>
{};

template <typename ClassType, typename ReturnType, typename...Args>
struct lambda_traits<ReturnType(ClassType::*)(Args...) const>
{
    enum { arity = sizeof...(Args) };

    typedef ReturnType result;
    template <size_t i> struct arg {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};

template <typename T> struct function_traits;

template <typename ReturnType, typename...Args>
struct function_traits<ReturnType(*)(Args...)>
{
    enum { arity = sizeof...(Args) };

    typedef ReturnType result;
    template <size_t i> struct arg {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};


//template<typename T, bool =std::is_function<T>::value> struct func_traits;

template<typename R, typename...Arg>
struct func_traits<R(*)(Arg...),true> : function_traits<R(*)(Arg...)>
{};

template<typename T>
struct func_traits<T,false> : lambda_traits<T>
{};




template<typename FN>
void detect(FN f)
{
    typedef func_traits<FN> fn;
    std::cout
     	<<typeid(typename fn::result).name()
    	<<"("<<fn::arity<<")\n";

}

int fn(int,long) {}


int main()
{
	int x,y;
    auto lambda = [x,&y](int i,int) { return long(i*10); };
    typedef lambda_traits<decltype(fn)> traits;



    detect(lambda);
	detect(fn);

    return 0;
}