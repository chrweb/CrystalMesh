/*
 * Checks.cpp
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */

#include "Checks.h" 
#include <iostream>

namespace Toolbox{

	void proceedOnViolation(char const * apFilenName, int aLineNumber, char const * aExpression){
		std::cout << "Violation in" << apFilenName << "\t Line " << aLineNumber << "\t Expression" << aExpression <<std::endl;
	}
        
        void terminate(char const * apFilenName, int aLineNumber){
             std::cout << "Ran into UNREACHABLE " << apFilenName << "\t Line " << aLineNumber << "\t Expression" <<std::endl;
            __builtin_unreachable();
        }
        
        void terminateOnViolation(char const * apFilenName, int aLineNumber, char const * aExpression){
            std::cout << "Violation in" << apFilenName << "\t Line " << aLineNumber << "\t Expression" << aExpression <<std::endl;
            __builtin_trap();
                    
        }


}




