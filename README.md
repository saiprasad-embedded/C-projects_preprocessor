**** C Preprocessor Implementation****

A custom C preprocessor built in C that replicates core preprocessing stages before compilation.

 **Features**
Comment Removal (`comment_removal.c`): Strips single-line (`//`) and multi-line (`/* ... */`) comments from source code.
File Inclusion (`file_inclusion.c`):Handles `#include` directives by inserting header file contents (`myheader.h`).
Macro substitution (`macro_handler.c`): Parses and expands `#define` macro definitions across the source file.

&& **Project Structure**
* main.c – Entry point that coordinates the preprocessing pipeline.
* preprocessor.h – Function declarations and shared definitions.
* comment_removal.c – Logic for removing C comments.
* file_inclusion.c – Logic for resolving `#include` directives.
* macro_handler.c – Logic for handling `#define` macros.
* Inputfile.c & myheader.h – Sample C input and header files for testing.
* Makefile – Build configuration for compiling the project.

## How to Build and Run

1. **Compile the project using `make`:
   make
  

2. **Run the preprocessor on the sample input file:**
   ```bash
   ./a.out Inputfile.c
   ```
   *(Note: Replace `./a.out` with your executable name if defined differently in your `Makefile`.)*
