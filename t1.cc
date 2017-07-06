#include <stdint.h>
#include <tuple>
#include <iostream>
#include <typeinfo>

template <typename T>
struct lambda_traits
: public lambda_traits<decltype(&T::operator())>
{};

template <typename C, typename R, typename...Args>
struct lambda_traits<R(C::*)(Args...) const>
{
    enum { arity = sizeof...(Args) };

    using result=R;
    template <size_t i> struct arg {
        using type=typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
};

template <typename T> struct function_traits;

template <typename R, typename...Args>
struct function_traits<R(*)(Args...)>
{
    enum { arity = sizeof...(Args) };

    using result=R;
    template <size_t i> struct arg {
        using type=typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
};


template<typename T, bool =std::is_function<typename std::remove_pointer<T>::type>::value> struct func_traits;

template<typename R, typename...Arg>
struct func_traits<R(*)(Arg...),true> : function_traits<R(*)(Arg...)>
{};

template<typename T>
struct func_traits<T,false> : lambda_traits<T>
{};





template<typename FN>
void detect(FN f)
{
    using fn=func_traits<FN>;
    std::cout
     	<<typeid(typename fn::result).name()
    	<<"{"<<fn::arity<<"} ("
        <<typeid(typename fn::template arg<0>::type).name()
        <<", "
        <<typeid(typename fn::template arg<1>::type).name()
        <<")\n";

}

int fn(int,long) {}


int main()
{
    detect([](int i,char) { return long(); });
	detect(fn);

    return 0;
}