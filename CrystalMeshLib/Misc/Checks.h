/*
 * Checks.h
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */
#pragma once


namespace CrystalMesh{

	void UNREACHABLE(void);

	// a condition validated in DEBUG and RELEASE
	void MUST_BE(bool const condition);



	template<typename T>
	bool const notNullptr(T const * aPtr) { return aPtr != nullptr; };

	template<typename T>
	bool const isNullptr(T const * aPtr) { return aPtr == nullptr; };

}





