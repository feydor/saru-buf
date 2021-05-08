# saru-buf
A simple C library containing buffer data structures:
* An unsigned bytes buffer
* A two-dimension unsigned bytes buffer

This library is part of the "saru-" family of C libraries written in order to provide well-tested data structures for use in my own projects. Each library is built using the Meson build system for easy dependency managment, with an emphasis on simplicity and modularity. 

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
