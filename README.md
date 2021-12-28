# cnit
## Minimal Header-only Unit Testing for C
Extremely minimal unit testing in two headers, written in ANSI C.

## Example Project
An example CMake project that uses this library can be seen
[here](https://github.com/ldm2468/cnit_example).

## Usage
Include `cnit.h` in all test source files.

Include `cnit_main.h` in **one** source file per test executable
(the one with the `main()` function).

Declare test cases as a regular C function that takes no arguments
and returns a single integer. It must return `0` at the end.
```C
int example_test_case() {
    CNIT_ASSERT(2 + 2 == 4);
    return 0;
}
int another_example_test_case() {
    CNIT_ASSERT(2 + 2 == 5);
    return 0;
}
```
Note that only a single assert macro is provided: `CNIT_ASSERT()`.

In the `main()` function, register each test case with the
`cnit_add_test()` function and run them with `cnit_run_tests()`.
```C
int main() {
    cnit_add_test(example_test_case, "Example test case");
    cnit_add_test(another_example_test_case, "Another example test case");
    return cnit_run_tests();
}
```
Returning the value of `cnit_run_tests()` is useful for integration with
CMake tests, etc.

When run, the output should look like the following:
```
Running tests...
  1 /   2 | O | Example test case
  2 /   2 | X | Another example test case | line 9
1/2 tests passed. (50%)
```
If a test case fails, the line number of the first failed assertion is printed.

If the output looks strange, it might be because the environment does not
support ANSI colors. If so, disable color output by adding the macro definition
`DISABLE_COLORS` when compiling. CMake example:
```CMake
target_compile_definitions(my_target PRIVATE DISABLE_COLORS)
```
