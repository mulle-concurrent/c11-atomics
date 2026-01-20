# C11 Atomics Detection Test

This repository tests whether various CI runners properly support and advertise C11 atomic operations (`<stdatomic.h>`).

## Purpose

Discovere github runners that fail to build code that uses mintomic as a fallback for platforms without C11 atomics. 
The issue is that mintomic doesn't support ARM64, but it should never be used on modern OS since C11 atomics are available.

This test verifies that:
1. The compiler properly advertises C11 atomic support via `__has_include(<stdatomic.h>)`
2. The `<stdatomic.h>` header is actually present and usable
3. Basic atomic operations compile and work correctly

## Test Matrix

Tests the same compiler/OS combinations as our main cmake-errors workflow:
- Ubuntu: GCC, Clang
- Windows: MSVC (Win32/Win64), GCC
- macOS: Clang, GCC

## Expected Results

All modern platforms should support C11 atomics. If any fail, it indicates:
- Missing or broken `<stdatomic.h>` header
- Compiler not properly advertising support
- Platform-specific issues that need workarounds

## Usage

The workflow runs automatically on push. Check the Actions tab to see results for each platform.

![vibecoded](https://www.mulle-kybernetik.com/pix/heartlessly-vibecoded.png)
