/*
 * Checks.cpp
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */

#include "Checks.h"

//#include  <verify.h>
#include <iostream>

namespace CrystalMesh{

	void UNREACHABLE(void){
		  __builtin_unreachable();
	}

	void MUST_BE(bool const condition){
		if ( ! condition )
			__builtin_trap();

	}

	void proceedOnViolation(char const * apFilenName, int aLineNumber, char const * aExpression){
		std::cout << "Violation " << apFilenName << "\t Line " << aLineNumber << "\t Expression" << aExpression <<std::endl;
	}

}




