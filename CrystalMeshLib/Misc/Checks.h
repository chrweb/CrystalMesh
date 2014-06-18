/*
 * Checks.h
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */
#pragma once

namespace CrystalMesh{

	void UNREACHABLE(void);

	void MUST_BE(bool const condition);


	template<typename T>
	bool const notNullptr(T const * aPtr) { return aPtr != nullptr; };

}





