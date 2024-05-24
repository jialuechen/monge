# Monge: Optimal Transport Toolkit for Model Calibration
It is very common that we face iliquidity positions when infering default probability, calibrating stochastic models or building volatifiy surface, which means we need find a way to fill the gaps in the sparse market data. This library a lightweight implementation of "Instant Transport Maps on 2D Grids" to help us handle the iliquidity problems during model calibration.

It currently supports L2-optimal maps from an arbitrary density defined on a uniform 2D grid (aka an image) to a square with uniform density.
Inverse maps and maps between pairs of arbitrary images are then recovered through numerical inversion and composition resulting in density preserving but approximately optimal maps.

## Installation

This code uses [Eigen](https://eigen.tuxfamily.org), Surface_mesh, and CImg that are already included in the repo/archive.
It is however highly recommended to install [SuiteSparse/Cholmod](http://faculty.cse.tamu.edu/davis/suitesparse.html) for higher performance, and libpng/libjpg for image IO.

All you need is to clone the repo, configure a build directory with cmake, and then build.
For instance:

````
$ git clone https://github.com/jialuechen/monge.git
$ cd monge
$ mkdir build
$ cd build
$ cmake ..
$ make -j 8
````

## Examples

#### sampling

```
$ ./stippling -in ../data/julia.png
```
![stippling](https://raw.githubusercontent.com/ggael/otmap/master/data/sampling_julia.png "stippling")

