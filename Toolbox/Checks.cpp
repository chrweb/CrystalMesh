/*
 * Checks.cpp
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */

#include "Checks.h" 
#include <iostream>
#include <exception>
#include <sstream>
#include <iosfwd>


namespace {
    using  namespace std;
    class ExceptionMUST_BE: public exception{
    private:
        string mMsg;
    public:
        
    
        ExceptionMUST_BE(string const & aMsg): mMsg(aMsg){
        
        }
        
        virtual const char* what() const throw(){
            return mMsg.c_str();
        }
    };
    

}


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
        
        void throwOnViolation(char const * apFilenName, int aLineNumber, char const * aExpression){
            std::ostringstream  oss;
            oss  << apFilenName << "\t Line " << aLineNumber << "\t Expression" << aExpression;
            throw ExceptionMUST_BE(oss.str());
            return;
        }
      


}




