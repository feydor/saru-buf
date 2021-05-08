project(
  'saru-buf', 'c',
  version : '0.0.1',
)

sources = [
 'src/ucharbuf.c' 
]

inc = include_directories('inc')

libsaru_buf = library(
  'saru-buf',
  sources,
  include_directories : inc,
  install : true,
)

#libsaru_buf_dep = declare_dependency(
#  include_directories : inc,
#  link_with : libsaru_NAME,
#)

pkg = import('pkgconfig')
pkg.generate(
  libraries: libsaru_buf,
  subdirs: 'include',
  version: meson.project_version(),
  name: 'libsaru-buf',
  filebase: 'saru-buf',
  description: 'A simple C library containing buffer data structures. A module of the "saru-" family of libraries.',
)

# For each public header in "inc/":
install_headers('inc/ucharbuf.h', subdir : 'saru-buf')
