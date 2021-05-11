# libsaru-buf
A simple C library containing static buffer data structures:
* An unsigned bytes buffer
* An unsigned bytes matrix
* A generic-type buffer

This library is part of the "saru-" family of C libraries written in order to provide well-tested data structures for use in my own projects. Each library is built using the Meson build system for easy dependency managment, with an emphasis on simplicity and modularity.

## Usage

Using the Meson build system, create a saru-buf.wrap file in the subprojects directory of your project and paste the following into it:
```
[wrap-git]
directory = saru-buf.git
url = https://github.com/feydor/saru-buf
revision = master
```
or simply use the example saru-buf.wrap in the root of this repository.

## Development

To create a build directory, run:
```sh
meson build
```

You can then compile using:
```sh
ninja -C build
```

You can run the tests using:
```sh
meson test
```

