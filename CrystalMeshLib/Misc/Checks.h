/*
 * Checks.h
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */
#pragma once


namespace Mathbox{

	void UNREACHABLE(void);

	// a condition validated in DEBUG and RELEASE
	void MUST_BE(bool const condition);

	void terminateOnViolation(char const * apFilenName, int aLineNumber, char const * aExpression);

	void proceedOnViolation(char const * apFilenName, int aLineNumber, char const * aExpression);


	template<typename T>
	bool const notNullptr(T const * aPtr) { return aPtr != nullptr; };

	template<typename T>
	bool const isNullptr(T const * aPtr) { return aPtr == nullptr; };

}





#ifdef DEBUG
	#define  SHOULD_BE_INTERNAL(Expression)\
	if (!(Expression)) \
	{ \
		Mathbox::proceedOnViolation(__FILE__, __LINE__, #Expression); \
	}

#else
	// empty
	#define SHOULD_BE_INTERNAL(Expression)
#endif


//#define SHOULD_BE_INTERNAL(Expression)
#define SHOULD_BE(Expression)	SHOULD_BE_INTERNAL(Expression)





