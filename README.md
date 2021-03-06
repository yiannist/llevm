LLEVM
====================
llevm is an erlang wrapper to the C API functions of llvm. 
The documentation of the functions can be found at the official 
[llvm website]( http://llvm.org/doxygen/dir_ba5bdc16f452288d1429bb9e178a5965.html ). 
Unfortunately the documentation of the C functions seem to be very 
sparse, so when looking for what functions do one should try to find 
the corresponding C++ class function and read the documentation for it
instead. 

For examples on how to use llevm see the testcases, especially 
`tests/kaleidoscope_SUITE.erl` and `tests/kaleidoscope_SUITE_data/kal_gen.erl`
contain lots of basics in how to generate llvm code and use the JIT 
execution engine from Erlang. 

Most functions are converted to erlang and hopefully work as well :)
There is a list of which functions are not as yet converted in 
`api_gen/llvm_api.hrl`. The functions are listed in the LIMIT macro.

Compiling
--------------------
You should only have to run

    ./configure && make

to compile llevm. Make sure that the correct llvm version is in the
path. 

Some possible issues when compiling are:

 * The erlang vm and llvm has to have the same arch (i.e. 64 vs 32 bit)
 * You have to have the correct version of llvm. 
   As of this writing that is 2.9. If you need another version you have 
   to regenerate all the erlang and nif files. 

Generating a new llevm
--------------------
If you are not happy with the generated API you can regenerate it
to suite your needs. To do this you have to have doxygen in your path then run:

    ./configure && (cd api_gen && make)

then new `src/llevm.erl`, `csrc/llevm.c` and `include/llevm.hrl` should be 
regerated. The code which generated the llevm interface is in the api_gen 
folder and divided into the different files that they generate. 


Runnig test
---------------------
llevm comes with a set of test which tests that everything works as it should.
To run the tests type:

    make test

The tests are very basic and are more there to provide examples than to test
the actual interface. So just because they pass don't trust that llevm does
what it should :)

Debugging
---------------------
It is possible to enable lots of debug printouts in `api_gen/llvm_api_nif.erl`.
Just search for printf and uncomment those lines and then regenerate llevm. 
It is also helpful to use gdb to step through execution, there are some 
example commands in `os_lathund` to show how I do it on my mac. 