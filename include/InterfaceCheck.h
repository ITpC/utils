/**
 * Interface check is copyrighted by Andrey Alexandrescu
 * See his book and loki library for license details.
 * This file is at no circumstances can have different license
 * as one stated by the copyright holder.
 *  
 * $Id: InterfaceCheck.h 56 2007-05-22 09:05:13Z Pavel Kraynyukhov $
 *  
 **/

#ifndef INTERFACECHECK_H_
#define INTERFACECHECK_H_

#include <Val2Type.h>

#define CheckRelationship(A,F,B)  F(A,B)
#define CheckCondition(A,F,B)  F(A,B)

/**
        Alexandrescu
        Modern Design C+++
**/

template <typename Super, typename Sub>
struct Similar
{
        typedef char            Subclass;
        
       	class  Superclass
        {
        	char dummy[2];
        };
        
        static Subclass  Test(Sub);
        static Superclass Test(...);
        static Super MakeSuper();

        enum{
                SameType=false ,
                canConvert=(
                        sizeof(Test(MakeSuper()))==sizeof(Subclass)
                )
        };
};

template <typename T>
struct Similar<T,T>
{
        enum{ SameType=1, canConvert=1};
};

#define SAME_OR_SUPER(T,U) \
        (Similar<const U*, const T*>::canConvert && \
                !Similar<const T*, const void*>::SameType)

#define interfaceof(T,U) \
        (SAME_OR_SUPER(T,U) && \
        !(Similar<const T*, const U*>::SameType) \
)

#define subclassof(T,U) interfaceof(U,T)

#define same_type_as(T,U) \
    (Similar<const U*, const T*>::canConvert && \
        Similar<const T,const U>::SameType) \


template <bool> struct CompileTimeChecker
{
        CompileTimeChecker(...);
};

template <> struct CompileTimeChecker<false> {};

#define STATIC_CHECKER3MSG(expr,msg1,msg2,msg3)\
{\
        class Error_##msg1##msg2##msg3{}; \
        (void)sizeof((CompileTimeChecker<( expr )>(Error_##msg1##msg2##msg3())));\
}


//  STATIC_CHECKER3MSG( CheckRelationship(T,interfaceof,T1) , T,_is_not_an_interface_of_,T1);
//	STATIC_CHECKER3MSG( CheckRelationship(T,subclassof,T1) , T,_is_not_a_subclass_of_,T1);


// me 

/**
 * @brief Compile Time evaluators of integers.
 * Use defined macros   like isGreaterThen and another for the evaluation.
 **/
template <int INT1, int INT2> struct Equal
{
    enum{
        SameValue=(INT1==INT2)
    };
};

template <int INT1, int INT2> struct NotEqual
{
    enum{
        NotSameValue=(INT1!=INT2)
    };
};

template <int INT1, int INT2> struct LessThen
{
    enum{ Less=(INT1<INT2) };
};

template <int INT1, int INT2> struct NotLessThen
{
    enum{ NotLess=(INT1>=INT2) };
};

template <int INT1, int INT2> struct GreaterThen
{
    enum{ Greater=(INT1>INT2) };
};


template <int INT1, int INT2> struct NotGreaterThen
{
    enum{ NotGreater=(INT1<=INT2) };
};


#define isGreaterThen(T,U)      GreaterThen<T,U>::Greater

#define isNotGreaterThen(T,U)   NotGreaterThen<T,U>::NotGreater

#define isLessThen(T,U)         LessThen<T,U>::Less

#define isNotLessThen(T,U)      NotLessThen<T,U>::NotLess)

#define isEqualTo(T,U)          Equal<T, U>::SameValue

#define isNotEqualTo(T,U)       NotEqual<T, U>::NotSameValue

// CheckCondition(a, isEqualTo , b)

#endif /*INTERFACECHECK_H_*/
