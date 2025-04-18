# Brain-ck-Interpreter
Based on the interpreter described in the [Wikipedia article](https://en.wikipedia.org/wiki/Brainfuck).

## Building
Build the interpreter by running the `build.sh` shell script (Linux):

```bash
./build.sh
```

## Running

Running the interpreter can be done in either an interactive mode, or in a mode that
reads BF source code directly from a file.

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
