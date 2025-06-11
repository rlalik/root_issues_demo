# CERN ROOT demo for a couple of issues with modules and c++23

## Installation
1. Clone the repository and enter the rpository directory.
2. Install it:
```bash
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/tmp/root_demo
make install -j$(nproc)
```
3. Load profile to setup `LD_LIBRARY_PATH`
```bash
. /tmp/root_demo/bin/profile.sh
```

## Usage

### With `runtime_cxxmodules` enabled
```bash
ROOTENV_NO_HOME=1 root ../macro.C
```
yields:
```
root [0]
Processing ../macro.C...
In file included from input_line_11:1:
/home/rafal/projects/cern/demos/cpp_23/macro.C:1:10: remark: could not acquire lock file for module 'root_demo': failed to create unique file /usr/lib64/root/root_demo.pcm.lock-489b66fb: Permission denied [-Rmodule-build]
#include <header.hpp>
         ^
/home/rafal/projects/cern/demos/cpp_23/macro.C:1:10: remark: building module 'root_demo' as '/usr/lib64/root/root_demo.pcm' [-Rmodule-build]
error: unable to open output file '/usr/lib64/root/root_demo.pcm': 'Permission denied'
/home/rafal/projects/cern/demos/cpp_23/macro.C:1:10: remark: finished building module 'root_demo' [-Rmodule-build]
/home/rafal/projects/cern/demos/cpp_23/macro.C:1:10: fatal error: could not build module 'root_demo'
#include <header.hpp>
 ~~~~~~~~^
```

```bash
ROOTENV_NO_HOME=1 root ../macro.C+
```
yields:
```
root [0]
Processing ../macro.C+...
Info in <TUnixSystem::ACLiC>: creating shared library /home/rafal/projects/cern/demos/cpp_23/build_modules_on/./../macro_C.so
Building in /home/rafal/projects/cern/demos/cpp_23
Building in /home/rafal/projects/cern/demos/cpp_23
In file included from macro_C_ACLiC_dict dictionary payload:8:
././../macro.C:1:10: remark: could not acquire lock file for module 'root_demo': failed to create unique file /usr/lib64/root/root_demo.pcm.lock-a20ebec9: Permission denied [-Rmodule-build]
#include <header.hpp>
         ^
././../macro.C:1:10: remark: building module 'root_demo' as '/usr/lib64/root/root_demo.pcm' [-Rmodule-build]
error: unable to open output file '/usr/lib64/root/root_demo.pcm': 'Permission denied'
././../macro.C:1:10: remark: finished building module 'root_demo' [-Rmodule-build]
././../macro.C:1:10: fatal error: could not build module 'root_demo'
#include <header.hpp>
 ~~~~~~~~^
Warning in <TInterpreter::TCling::RegisterModule>: Problems declaring payload for module macro_C_ACLiC_dict.
input_line_14:2:3: error: use of undeclared identifier 'macro'
 (macro())
  ^
Error in <HandleInterpreterException>: Error evaluating expression (macro())
Execution of your code was aborted.
```

### With `runtime_cxxmodules` disabled
```bash
ROOTENV_NO_HOME=1 root ../macro.C
```
yields:
```
root [0]
Processing ../macro.C...
In file included from input_line_11:1:
In file included from /home/rafal/projects/cern/demos/cpp_23/macro.C:1:
/home/rafal/projects/cern/demos/cpp_23/include/header.hpp:3:8: error: redefinition of 'struct_foo'
struct struct_foo {};
       ^
input_line_12:1:10: note: '/home/rafal/projects/cern/demos/cpp_23/include/header.hpp' included multiple times, additional include site here
#include "/home/rafal/projects/cern/demos/cpp_23/include/header.hpp"
         ^
/home/rafal/projects/cern/demos/cpp_23/macro.C:1:10: note: '/home/rafal/projects/cern/demos/cpp_23/include/header.hpp' included multiple times, additional include site here
#include <header.hpp>
         ^
In file included from input_line_11:1:
In file included from /home/rafal/projects/cern/demos/cpp_23/macro.C:1:
/home/rafal/projects/cern/demos/cpp_23/include/header.hpp:5:13: error: redefinition of 'foo'
inline void foo() {}
            ^
/home/rafal/projects/cern/demos/cpp_23/include/header.hpp:5:13: note: previous definition is here
inline void foo() {}
```

```bash
ROOTENV_NO_HOME=1 root ../macro.C+
```
yields:
```
root [0]
Processing ../macro.C+...
Info in <TUnixSystem::ACLiC>: creating shared library /home/rafal/projects/cern/demos/cpp_23/build_modules_off/./../macro_C.so
Building in /home/rafal/projects/cern/demos/cpp_23
Building in /home/rafal/projects/cern/demos/cpp_23
```
This is expected output and gives proper compiled macro.