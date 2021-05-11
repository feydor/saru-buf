project(
  'saru-buf', 'c',
  version : '0.0.1',
)

sources = [
 'src/bytebuf.c',
 'src/buf.c'
]

inc = include_directories('inc')

libsaru_buf = library(
  'saru-buf',
  sources,
  include_directories : inc,
  install : true,
)

# dependency declaration for exporting as a meson subproject
libsaru_buf_dep = declare_dependency(
  include_directories : inc,
  link_with : libsaru_buf,
)

pkg = import('pkgconfig')
pkg.generate(
  libraries: libsaru_buf,
  subdirs: 'inc',
  version: meson.project_version(),
  name: 'libsaru-buf',
  filebase: 'saru-buf',
  description: 'A simple C library containing buffer data structures. A module of the "saru-" family of libraries.',
)

unity_dep = dependency(
  'Unity',
  fallback: ['Unity', 'unity_dep'],
)

bytebuf_test = executable(
  'bytebuf-test',
  ['test/bytebuf.c'],
  dependencies: [libsaru_buf_dep, unity_dep],
)
test('unittest, saru-bytebuf', bytebuf_test)

buf_test = executable(
  'buf-test',
  ['test/buf.c'],
  dependencies: [libsaru_buf_dep, unity_dep],
)
test('unittest, saru-buf', buf_test)

# For each public header in "inc/":
install_headers('inc/saru-buf.h', subdir : 'saru-buf')
install_headers('inc/saru-bytebuf.h', subdir : 'saru-buf')
