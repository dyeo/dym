# DYM Math Library

DYM (pronounced "dim") is a C++ library that provides efficient and flexible math utility for the purpose of graphics programming, game programming, and fields with similar requirements. The toolkit boasts matrix and vector classes which are templated by value type and by dimension. The entire library is defined in header files, and math code is implemented generically in a manner which allows for efficient runtime calculations. The entire library is free-to-use under the terms of the MIT License.

# How to Use

Simply add the `include/dym` folder to your project's includes, and `#include "dym/dym.h"`.

### Features
- [x] Unambiguous Angles
- [x] Unambiguous Percentages
- [x] Half-Precision Floating Point Numbers
  - [ ] Full specification
- [x] Matrices (Column-Major)
  - [x] Dimension-Templated
  - [x] Type-Templated
  - [x] Perspective/Orthographic Projections
  - [x] 2D, 3D, 3D Homogeneous Transformations
  - [x] Linear Algebra Operations
  - [x] Matrix Product
  - [x] Matrix-Vector Product
  - [x] All GLSL Matrix Operations
  - [x] Catmull-Rom and Bezier Matrices
  - [x] Row-Major Conversion
- [x] Vectors
  - [x] Dimension-Templated
  - [x] Type-Templated
  - [x] Dot and Cross Product
  - [x] All GLSL Vector Operations
  - [x] Vector Swizzling
- [x] Generic Quaternions
  - [x] Type-Templated
  - [x] Quaternion SLERP
  - [x] Axis-Angle Representation
  - [x] 3D Vector Transformation
  - [x] Matrix Conversion

### License

DYM uses the following version of the MIT License:

Copyright (c) 2015-2025 Dani Yeomans

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

### Code Sample

``` c++
#include <iostream>


// one header gets the entire library, no hassle!
// optionally disable custom literals by defining DYM_DISABLE_LITERALS before including
// optionally disable swizzling by defining DYM_DISABLE_SWIZZLING before including
#include "path/to/dym/dym.h"

int main()
{
	// define a 3d float vector
	// synonymous with dym::vec3, dym::vec3f, and dym::vec<3>
	dym::vec<3, float> vecA;

	// initialize a 3d float matrix
	// synonymous with dym::mat3 and dym::mat3f, and dym::mat<3>
	dym::mat<3, 3, float> matA(1, 0, 1,
				2, 4, 0,
				3, 5, 6);

	// initialize a 3d float matrix as the inverse of matA
	dym::mat3 matB = dym::inverse(matA);

	// initialize a homogeneous transformation matrix (rotation and position)
	dym::mat4 matH(dym::mat3::rotatex(1.5_rad), dym::vec3(1, 2, 3));

	// fast invert the homogeneous transformation matrix
	dym::mat4 imatH = dym::fastinverse(matH);

	// retrieve the first column of matB as a 3d vector and store it in vecA
	vecA = matB[0];

	// initialize sclA the first column, last row of matA
	float sclA = matA[0][2];

	// define a perspective transformation matrix (openGL)
	dym::mat4::perspective(
		90_deg, // y-axis field of view, in degrees (dym::ang)
		16 / (float)9, // aspect ratio
		0.01, // near clipping range for z-axis
		10000 // far clipping range for z-axis
	);

	// output our results
	std::cout << matA * matB << std::endl << std::endl
		<< matH * imatH << std::endl << std::endl
		<< 45_deg << std::endl;

	// constructs a column-major 3d float matrix from rows, using 3d float vectors
	dym::mat3::fromrows(
		dym::vec3(0, 1, 2),
		dym::vec3(3, 4, 5),
		dym::vec3(4, 5, 6)
	);

	// pi constant, change to d_pi for double precision
	// all commonly used constants supported
	dym::f_pi;
	
	// vector swizzling
	dym::vec4 vecS = { 0, 1, 2, 3 };
	dym::vec3 vecT = vecS.yzx;
	vecT.yzx = vecS.xyz;
}

```
