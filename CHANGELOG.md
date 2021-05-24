# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [v0.3.0] - 2020-05-24
## Added 
- sbm_destroy_wrapped to free a wrapped bytemat.
- clang -fsanitize=address,undefined linking.
## Fixed
- all: Macros had trailing semicolons.
- sbm_destroy: Setting freed pointers to NULL.
- sb_len: Arithmetic on void pointer.
- sbm_max: Local variables row and col were overwriting the parameters of the same name.
- test_sbm_gsum: Was filling the wrong bytemat.
### Removed
- sb_fill from saru_buf.

## [v0.2.0] - 2020-05-14
### Added
- API documentation detailing usage and examples.
- Utility functions for saru_bytemat including:
    - sbm_putxy
    - SBM_WRAP, a macro around sbm_wrap
- Utility functions for saru_buf including:
    - sb_strcpy
    - sb_memcpy
### Fixed
- sbm_subinjective was looking at the wrong array indices.
### Changed
- All existing api functions for const correctness.
### Removed
- SB_FOREACH macro for saru_buf.

## [v0.1.0] - 2021-05-11
### Added
- The first working release of this library containing the following tested data structures:
    - saru_buf
    - saru_bytemat
- Usage instructions for including this library in projects built with the Meson build system.
- A working meson .wrap file.
