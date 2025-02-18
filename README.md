# Coding assessment: writing a "kernel spreader"
You're to implement a basic library that takes an arbitrary list of points and evaluates a
mathematical function mapping those points onto a grid. The problem will be outlined more
clearly, but first, some expected conduct.


## Rules
1. DO NOT FORK THIS LIBRARY OR OTHERWISE SHARE THE CODE PUBLICLY ON GITHUB. You are free to
   push it to your own private github repo. We wouldn't want other people stealing your hard
   work :)
2. Language model assistance is OK (and almost unavoidable nowadays), but blanketly trying to
   coerce ChatGPT into giving you the answer is not.
   * copilot auto-completion ✓ (with caution!)
   * "Write me a function that evaluates function x on grid y with inputs z" ⦻
3. Don't steal code. This exercise is to assess your ability to turn a simple mathematical
   specification into code. This problem has been solved before, and much better than I'm
   asking for here. If you come up with a fancy/fast way to solve it, you're actively
   encouraged to pursue that -- it's an open problem how to most efficiently do this -- but
   don't overdo it. Just have fun.


I largely have no clear way to enforce the above rules, but any project in this internship will
be use very "heavy" mathematical `c++` that GPT is, quite frankly, terrible at. It won't be a
pleasant internship if you need a language model to write `c++`.

All that seriousness aside, this is a basic coding assessment that I hope is engaging and
hopefully even fun!


## Problem specification
A common problem in analysis is that measurement points are not uniformly spaced, but many
analysis techniques require data on uniform grids (such as fast Fourier transforms --
FFTs). Therefore, the data must be mapped to a uniform grid via some transformation. One common
technique is to just "histogram" the data, i.e. just move the data to the nearest grid
point. This is often sufficient, but sometimes more sophisticated techniques are
required. 

Here, you'll be implementing a 'spreading' transformation, which basically smears the
input data across multiple nearby uniform grid points via some function. Depending on the problem,
different functions might perform better than others, but we'll just use a Gaussian here.

$$f(x) = \frac{1}{\sqrt{2 \pi \sigma^2}} \exp(-\frac{x^2}{2 \sigma^2})$$

We'll also have the assumption that beyond some cutoff distance $r_c$, our function evaluates
to 0. So $f$ is piecewise Gaussian on $[-r_c, r_c]$ and 0 otherwise.

Your job is to take an input list of $M$ points at positions $x_i$ and 'strengths' $\phi_i$,
and spread them to an output grid of width $N$. If $u_j$ represents the output value at index
$j$, $h$ is the spacing between uniform grid points, then formally

$$u_j = \sum_{i=0}^{M-1} \phi_i f(h \cdot j - x_i)$$.
    
<img src=img/drawing.jpg width=500px>

So you can write the implementation however you want, and write some appropriate tests to drive
it and ensure sensible results. The tests and implementation are entirely up to you. I've
provided an example interface and some basic test runners in `src/spreadkernel.cpp`.

Some simplifying assumptions, all of which you're free to relax if you handle them appropriately

1. Non-uniform points never fall near the boundary of the uniform grid, i.e. $|x_i - h \cdot j| < r_c$
2. $h$ is 1
3. The grid starts at 0, and therefore $0 < x_i < N - 1$

The project has a 2D version as well (any dimension really, though high dimensions and uniform
grids are not good friends). The underlying problem is essentially the same, but we do a
_tensor product_ evaluation of our function at each grid point.

$$u_{j,k} = \sum_{i=0}^{M-1} \phi_i f(h \cdot j - x_i) f(h \cdot k - y_i)$$

While not required for the assessment, the 2D version poses some unique performance problems
not apparent in the 1D version, so if you have time in your probably busy schedule, consider
adding it as well.


## Project layout
```
.
├── .clang-format          # Autoformatter specification for `c++`. Don't fret about it.
├── .gitignore             # Patterns to ignore to have a nice pretty git experience
├── CMakeLists.txt         # Build specification. No need to modify unless you want
├── img                    # Images for README
│   └── drawing.jpg        # My beautiful artwork
├── LICENSE                # Gotta license your work!
├── README.md              # These instructions
├── src                    # Source code lives here. No need to add new files unless you want
│   ├── doctest.cpp        # Don't modify. Necessary to build tests
│   └── spreadkernel.cpp   # MODIFY. Your implementation lives here.
└── test                   # Don't modify. Necessary to build tests
    └── run_tests.cpp      # Don't modify. Necessary to build tests
```


## Getting the project and building
This template should, as provided, make a working `c++` test program `run_tests` and
accompanying shared library `libspreadkernel.so`, if using linux. It should work on mac and
windows, though I haven't tested it. To build you need a working `c++` compiler and `cmake`
build system.

```bash
% git clone https://github.com/blackwer/kernel_spreading
% cd kernel_spreading
% mkdir build
% cmake ..
-- The CXX compiler identification is GNU 13.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /mnt/sw/nix/store/8m360i109zyjimv6rx1hvcdaikgpdwib-gcc-13.2.0/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (1.4s)
-- Generating done (0.9s)
-- Build files have been written to: /mnt/home/rblackwell/projects/scc/kernel_spreading/build
% make -j
[ 20%] Building CXX object CMakeFiles/spreadkernel.dir/src/spreadkernel.cpp.o
[ 40%] Building CXX object CMakeFiles/spreadkernel.dir/src/doctest.cpp.o
[ 60%] Linking CXX shared library libspreadkernel.so
[ 60%] Built target spreadkernel
[ 80%] Building CXX object CMakeFiles/run_tests.dir/test/run_tests.cpp.o
[100%] Linking CXX executable run_tests
[100%] Built target run_tests
% ctest
Test project /mnt/home/rblackwell/projects/scc/kernel_spreading/build
    Start 1: SPREADKERNEL 1d<float>
1/6 Test #1: SPREADKERNEL 1d<float> ...........   Passed    0.01 sec
    Start 2: SPREADKERNEL 1d<double>
2/6 Test #2: SPREADKERNEL 1d<double> ..........   Passed    0.01 sec
    Start 3: SPREADKERNEL 2d<float>
3/6 Test #3: SPREADKERNEL 2d<float> ...........   Passed    0.01 sec
    Start 4: SPREADKERNEL 2d<double>
4/6 Test #4: SPREADKERNEL 2d<double> ..........   Passed    0.01 sec
    Start 5: SPREADKERNEL 3d<float>
5/6 Test #5: SPREADKERNEL 3d<float> ...........   Passed    0.01 sec
    Start 6: SPREADKERNEL 3d<double>
6/6 Test #6: SPREADKERNEL 3d<double> ..........   Passed    0.01 sec

100% tests passed, 0 tests failed out of 6

Total Test time (real) =   0.06 sec
```

## If you can't get the project to build
Please try. You'll probably want a working developer environment for the internship anyways. On
windows, I recommend using `WSL`. On Mac you can install the `XCode` developer tools. You'll
need `cmake`, which you can install via `brew`. If you can't get it working, you can modify
`spreadkernel.cpp` to not use doctest, and just write a `main` function that drives it. This
should work so long as you have a functioning `c++` compiler somewhere.


## Extra things to consider for fun
* Are there ways to manipulate loop orders effectively?
* Can you exploit multi-core processors? How might you do so?
* Are there opportunities to exploit the "superscalar" nature of processors?
* What if you only need a few digits of accuracy for spreading?
* What if the points were ordered?
* Other optimizations? 
* How might you generalize this to work on other functions? Other grid spacing? Periodic boundary conditions? Grids with offsets in space?
* What if you were working on a GPU?
