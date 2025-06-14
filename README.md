# Apple cctools port (ld64) for Linux, *BSD and Windows #

Current Version: 877.8 + ld64-253.9.  
Originally ported by [cjacker](http://ios-toolchain-based-on-clang-for-linux.googlecode.com).

## SUPPORTED HOSTS ##

**SUPPORTED OPERATING SYSTEMS:**

Currently Tested: Linux, Windows

Untested: FreeBSD, NetBSD, OpenBSD, DragonFlyBSD, Mac OS X and iOS

**SUPPORTED HOST ARCHITECTURES:**

Tested: x86_64

Untested: x86, arm, aarch64, ppc, ppc64

## SUPPORTED TARGET ARCHITECTURES ##

armv4t, armv5, armv6, armv7, armv7f, armv7k, armv7s, armv6m  
armv7m, armv7em, armv8, arm64, arm64v8, i386, x86_64 and x86_64h.

## SUPPORTED TARGET OPERATING SYSTEMS ##

Mac OS X, iOS, watchOS (untested) and tvOS (untested)

## DEPENDENCIES ##

`Clang` and `cmake 3.20+`.

Optional, but recommended:

`llvm-devel`               (For Link Time Optimization Support)  
`uuid-devel`               (For ld64 `-random_uuid` Support)  
`llvm-devel` + `xar-devel` (For ld64 `-bitcode_bundle` Support)

You can find xar [here](https://github.com/mackyle/xar).  
Do not install libxar-dev on Ubuntu, it's a different package.

## Building ##

* `cmake -S . -B build`
* `cmake --build build`