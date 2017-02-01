# Graphics/Math Toolkit (GMTK) 
### Also known as GMath

GMTK is a C++ library that provides efficient and flexible math utility for the purpose of graphics programming, game programming, and fields with similar requirements. The toolkit boasts matrix and vector classes which are templated by value type and by dimension. The entire library is defined in header files, and math code is implemented generically in a manner which allows for efficient runtime calculations. The entire library is free-to-use under the terms of the MIT License.

### Features
- [x] Angles
- [x] Half-Precision Floating Point Numbers
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
  - [ ] Eigenvector and Eigenvalue
- [x] Vectors
  - [x] Dimension-Templated
  - [x] Type-Templated
  - [x] Dot and Cross Product
  - [x] All GLSL Vector Operations
- [x] Generic Quaternions
  - [x] Type-Templated
  - [x] Quaternion SLERP
  - [x] Axis-Angle Representation
  - [x] 3D Vector Transformation
  - [x] Matrix Conversion
- [ ] Generic Scene Graph
- [ ] Simple General OpenGL Classes
- [ ] Tensors (pending)

### License

GMTK uses the following version of the MIT License:

Copyright (c) 2016 Dan Yeomans

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

### Code Sample

``` c++
// define a 3d float vector
// synonymous with gmtk::vec3 and gmtk::vec3f
gmtk::vec<float, 3> vecA;

// initialize a 3d float matrix
gmtk::mat3 matA(1, 0, 1,
		2, 4, 0,
		3, 5, 6);

// initialize a 3d float matrix as the inverse of matA
gmtk::mat3 matB = gmtk::inverse(matA);

// retrieve the first column of matB as a 3d vector and store it in vecA
vecA = matB[0];

// initialize sclA the first column, last row of matA
float sclA = matA[0][2];

// define a perspective transformation matrix (openGL)
gmtk::mat4::perspective(
		gmtk::Degrees(90), // y-axis field of view, in degrees (gmtk::Angle)
		16 / (float)9, // aspect ratio
		0.01, // near clipping range for z-axis
		10000 // far clipping range for z-axis
		);

// constructs a column-major 3d float matrix from rows, using 3d float vectors
gmtk::mat3::fromrows(
		gmtk::vec3(0, 1, 2), 
		gmtk::vec3(3, 4, 5), 
		gmtk::vec3(4, 5, 6)
		);

gmtk::M_PI; // pi constant
```
