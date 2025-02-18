#include <cstdint>
#include <vector>

#include <doctest/doctest.h>

namespace spreadkernel {

// Spread kernel for 1d
// x: position of non-uniform points
// phi: strength of non-uniform points
// sigma: width of gaussian spread kernel
// r_c: distance from center of kernel, beyond which the kernel is truncated
// u: uniform grid of spreaded data
// h: grid spacing of uniform grid
template <typename Real>
void spread_kernel(const std::vector<Real> &x, const std::vector<Real> &phi, Real sigma, Real r_c,
                   std::vector<Real> &u, Real h = 1.0) {
    const int64_t M = x.size();
    const int64_t N = u.size();
}

// Spread kernel for 2d
// x: position of non-uniform points
// phi: strength of non-uniform points
// sigma: width of gaussian spread kernel
// r_c: distance from center of kernel, beyond which the kernel is truncated
// u: uniform grid of spreaded data
// N1: number of uniform points in x direction
// N2: number of uniform points in y direction
// h: grid spacing of uniform grid for both x and y direction
template <typename Real>
void spread_kernel(const std::vector<Real> &x, const std::vector<Real> &y, const std::vector<Real> &phi, Real sigma,
                   Real r_c, int N1, int N2, std::vector<Real> &u, Real h = 1.0) {
    const int64_t M = x.size();
}

} // namespace spreadkernel

// Some basic test cases. You can add more test cases if you want. This is just a simple
// example.
TEST_CASE_TEMPLATE("SPREADKERNEL 1d", Real, float, double) { CHECK(true); }

TEST_CASE_TEMPLATE("SPREADKERNEL 2d", Real, float, double) { CHECK(true); }
