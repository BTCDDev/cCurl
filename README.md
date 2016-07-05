# cCurl:

A ternary hash function for IOTA, the cryptocurrency for the Internet of Things economy @ iotatoken.com


2016 BTCDDev

Original Code by Come-from-Beyond


### To Use:

Create a `struct Curl` variable and pass it by reference to `setup_Curl()`

Create a variable input int array of balanced ternary

`absorb()` the array into the Curl struct with size, optional offset and length

`squeeze()` the hash into an output int array with optional offset, output length is 3<sup>5</sup>



### To Test:

Uncomment the end of the file, right before the `run_tests()` declaration.

Compile with `clang cCurl.c -Wall -O3`


Make sure you compile CurlReference.java with
`javac CurlReference.java`


For the speed test, compile with `clang cCurl.c speedtest.c -Wall -Ofast`. Run with `./a.out <num hashes>`

### note:

You are responsible for all bounds checks, cCurl currently doesn't do much

### Version:
0.0.1


Errors or comments, please email at:

bitcoindarkdev@gmail.com
