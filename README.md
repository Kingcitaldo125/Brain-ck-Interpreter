# Brain-ck-Interpreter
A compiler and interpreter for the Brainf*ck esoteric programming language.
This is based on the language design section described in the [Wikipedia article](https://en.wikipedia.org/wiki/Brainfuck).

![](https://raw.githubusercontent.com/Kingcitaldo125/Brain-ck-Interpreter/refs/heads/main/images/mandelbrot_out.PNG "Mandelbrot set output")

## Building
Build the programs by running the `build.sh` shell script (Linux):

```bash
./build.sh
```

This will take care of building the compiler, interpreter, and all of the necessary link libraries
needed by the compiler and interpreter.

One may also build the tests and/or build in debug mode by adding `"debug"` or `"test"` to the `./build.sh`
invocation as an optional argument.

### Dependencies
To compile the base programs, you will need a C++17 compatible compiler and [CMake](https://cmake.org/).

To use the BF compiler, you will need to have `gcc` (GNU C Compiler) installed.
Each of these dependencies can be installed in **Debian/Ubuntu** linux by way of the `apt` package manager:
```bash
sudo apt -y update && sudo apt -y install build-essential cmake
```

### Tests
Normally, the Brainfck test scripts may be ran using the `test.sh` shell script.
This will just interpret the brainfck source present in the repository, exercising the interpreter.

If you wish to build and run the tests as well, [Vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-bash)
will be needed to retrieve the Catch2 unit test suite, which is in turn needed to run the unit tests.

Running the unit tests, in conjunction with the test scripts, requires the project to be built by passing
`"test"` to the `build.sh` shell script _prior_ to the `test.sh` invocation.
This is due to the fact that unit tests were not set up to be ran automatically, in favor of simply running
the Brainf*ck test scripts.
Unit tests are ran automatically on commits to `main`, thanks to the project's GH actions.

## Running
One may run either the compiler or the interpreter via two shell scripts at the root of the source code:

- compile.sh
- run.sh

`compile.sh` will invoke the compiler and `run.sh` will run the interpreter.

More information on these two options are described in the sections below.

Please note that running large Brainf*ck programs with the interpreter may be much slower
than compiling and running the same programs.

### Compiler
Brainf*ck code may be compiled down to assembly and/or an executable using the `gcc` C compiler.
Usage of the compiler assumes that the `gcc` command is already available on the system path.

To compile a program, run:

```bash
./compile -f ./myfile.bf
```

If the program can be compiled, resulting `out.c` and `out` files will be written to the directory of the invocation.
These two files are the C source code, and the binary executable resulting from the compiler invocation, respectively.

Optionally, one may also specify assembly output to the compile command:

```bash
./compile.sh -a -f ./myfile.bf
```

Selecting the option to generate the resulting assembly output will also trigger a full rebuild of the source code.

### Interactive interpreter
Run the interactive interpreter by running the `run.sh` shell script (Linux):

```bash
./run.sh
```

This will compile (if not already) the code in the project and start up an interactive Brainf*ck interpreter.

Once the interactive interpreter is running, you should see `BF(X)` in the terminal window.
The `X` is a numeric value indicating which data/cell the data pointer is currently pointing to.

Type "CTRL+C" or "CTRL+D" to exit the interactive interpreter at any time.

### Non-Interactive interpreter
You can also interpret files directly with:

```bash
./run.sh -f ./myfile.bf
```

One may also leverage the interpreter directly from the command line:

```bash
./run.sh -i "++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>>++.>+.+++++++..+++.<<+++."
```

This will output `Hello!` in the terminal that the `run.sh` was invoked from.

## License
See the [LICENSE](https://github.com/Kingcitaldo125/Brain-ck-Interpreter/blob/main/LICENSE) file for details.
