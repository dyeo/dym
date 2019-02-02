#ifndef _GMTK_SWIZZLE3_H_
#define _GMTK_SWIZZLE3_H_

#include "../util.h"
#include "vec.h"

#define GMTK_SWZ3_UOP(op)															\
	V operator op () const															\
	{																				\
		V res(static_cast<T>(0));													\
		res[0] = op ((const T*)this)[a];											\
		res[1] = op ((const T*)this)[b];											\
		res[2] = op ((const T*)this)[c];											\
		return res;																	\
	}

#define GMTK_SWZ3_OP(op)															\
	template<int a2, int b2, int c2, typename V, typename T>						\
	V operator op (const swizzle3<a2, b2, c2, V, T> &s) const						\
	{																				\
		V res(static_cast<T>(0));													\
		res[0] = ((const T*)this)[a] op ((const T*)&s)[a2];							\
		res[1] = ((const T*)this)[b] op ((const T*)&s)[b2];							\
		res[2] = ((const T*)this)[c] op ((const T*)&s)[c2];							\
		return res;																	\
	}																				\
																					\
	V operator op (const T &v) const												\
	{																				\
		V res(static_cast<T>(0));													\
		res[0] = ((const T*)this)[a] op v;											\
		res[1] = ((const T*)this)[b] op v;											\
		res[2] = ((const T*)this)[c] op v;											\
		return res;																	\
	}																				\
																					\
	friend V operator op (const T &l, const swizzle3<a, b, c, V, T> &r)				\
	{																				\
		V res(static_cast<T>(0));													\
		res[0] = l op ((const T*)r)[a];												\
		res[1] = l op ((const T*)r)[b];												\
		res[2] = l op ((const T*)r)[c];												\
		return res;																	\
	}

#define GMTK_SWZ3_ROP(op)															\
	template<int a2, int b2, int c2, typename T>									\
	writable_type& operator op (const swizzle3<a2, b2, c2, V, T> &s)				\
	{																				\
		const T va2 = ((const T*)&s)[a2],											\
			    vb2 = ((const T*)&s)[b2],											\
			    vc2 = ((const T*)&s)[c2];											\
		((T*)this)[a] op va2; 														\
		((T*)this)[b] op vb2;														\
		((T*)this)[c] op vc2;														\
		return *this;																\
	}																				\
																					\
	writable_type& operator op (const V &s)											\
	{																				\
		((T*)this)[a] op s.data[0]; 												\
		((T*)this)[b] op s.data[1];													\
		((T*)this)[c] op s.data[2];													\
		return *this;																\
	}																				\
																					\
	template<int a2, int b2, int c2, typename T> 									\
	writable_type& operator op (const T &s)											\
	{																				\
		((const T*)&s)[a] op s; 													\
		((const T*)&s)[b] op s;														\
		((const T*)&s)[c] op s;														\
		return *this;																\
	}

//

namespace GMTK_NAMESPACE
{////

	template<int a, int b, int c, typename V, typename T>
	class swizzle3
	{
	public:

		static constexpr bool is_writable = (a != b);

		typedef typename std::conditional<is_writable, swizzle3<a, b, c, V, T>, struct operation_not_available>::type writable_type;

		inline T& operator[](const int i) {
			return ((T* const)this)[i];
		}

		inline const T& operator[](const int i) const {
			return ((T* const)this)[i];
		}

		GMTK_SWZ3_UOP(-)

			GMTK_SWZ3_ROP(= )

			GMTK_SWZ3_OP(*)
			GMTK_SWZ3_OP(/ )
			GMTK_SWZ3_OP(+)
			GMTK_SWZ3_OP(-)

			GMTK_SWZ3_ROP(*= )
			GMTK_SWZ3_ROP(/= )
			GMTK_SWZ3_ROP(+= )
			GMTK_SWZ3_ROP(-= )

	}; //! class swizzle3

	template <int a, int b, int c, typename V, typename T>
	inline std::ostream& operator<<(std::ostream& os, const swizzle3<a, b, c, V, T>& s)
	{
		os << "| " << s[a] << ' ' << s[b] << ' ' << s[c] << " |";
		return os;
	}

}////

//

#undef GMTK_SWZ3_UOP
#undef GMTK_SWZ3_OP
#undef GMTK_SWZ3_ROP

//

#endif //_GMTK_SWIZZLE3_H_
