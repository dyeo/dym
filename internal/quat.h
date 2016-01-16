#ifndef _GMTK_QUAT_H_
#define _GMTK_QUAT_H_

//

#include "..\util.h"
#include <math.h>
#include <ostream>

//

//! Unrolls a component-wise vector manipulation for generic implementation
#define GMTK_QUAT_LOOP(oper) GMTK_UNROLL_LOOP(i,4,oper)

//

#define GMTK_QUAT_OPERATOR(oper) { Quat<T> res; GMTK_QUAT_LOOP(res[i] = oper); return res; }

//

#define GMTK_QUAT_REF_OPERATOR(oper) { GMTK_QUAT_LOOP(oper); return *this; }

//

namespace GMTK_NAMESPACE
{
	//! quaternion class
	template< typename T = float >
	struct Quat
	{////

		union
		{
			struct { T data[4]; };
			struct { T w, x, y, z; };
		};

		//

		 

	};////

	typedef Quat<> quat;
	typedef Quat<double> quatd;
	typedef Quat<int> quati;
	typedef Quat<unsigned> quatui;

}

#endif//_GMTK_QUAT_H_