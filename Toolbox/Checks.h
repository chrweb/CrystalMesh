/*
 * Checks.h
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */
#pragma once


namespace Toolbox{

	
	void terminateOnViolation(char const * apFilenName, int aLineNumber, char const * aExpression);

	void proceedOnViolation(char const * apFilenName, int aLineNumber, char const * aExpression);

        void terminate(char const * apFilenName, int aLineNumber);

	template<typename T>
	bool const notNullptr(T const * aPtr) { return aPtr != nullptr; };

	template<typename T>
	bool const isNullptr(T const * aPtr) { return aPtr == nullptr; };

}





#ifdef DEBUG
	#define  SHOULD_BE_INTERNAL(Expression)\
	if (!(Expression)) \
	{ \
		Toolbox::proceedOnViolation(__FILE__, __LINE__, #Expression); \
	}

#else
	// empty
	#define SHOULD_BE_INTERNAL(Expression)
#endif

#define SHOULD_BE(Expression)	SHOULD_BE_INTERNAL(Expression)

#define MUST_BE(Expression)\
if(!(Expression))\
{\
    Toolbox::terminateOnViolation(__FILE__, __LINE__, #Expression); \
}


#define UNREACHABLE Toolbox::terminate(__FILE__, __LINE__);
