### Description:

Library of matrix solvers and equation root solvers written for cs417 - Numerical Methods.
Everything is written in C++, primarily for performance reasons, but this is *not* a sparse matrix implementation, so memory requirements have to be considered when using/testing.

##### Included matrix solvers:

- Jacobi iterative method
- Gauss-Seidel method (without relaxing)
- Gauss-Seidel with successive over-relaxation (or under-relaxation, constant is user-specified)
- Gaussian elimination
- LU decomposition

##### Root solvers:

- bisection method
- Regula-falsi (false position) method
- Newton-Raphson method

##### Notes:

- Refactoring this code is on my to-do list. Specifically, I wrote a whole command-line interface to allow access to these methods because I thought it was a requirement for the class. In reality, the CLI was just a pain and extra work that was totally unnecessary for the assignments or the class. I want to remove the CLI, but create a good augmented matrix class/object that will allow access to all the library methods in an easy and compact way.
- Similarly, there were some *compromises* made on the interface with the root solvers. Would be nice to get rid of that CLI as well. 

### Build instructions: 

Currently, the following are options:

- `make` or `make all` will compile both the test/debugging and regular executables
- `make debug` will produce only the executable for the Google Test suite
- `make release` will produce only the regular program executables
- `make clean` should remove most added files and cruft from either build. It will likely leave behind user-created data files.