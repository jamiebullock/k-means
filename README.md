# k-means

k-means is a simple C library for k-means clustering

## Limitations

This code currently assumes a 2-dimensional dataset scaled to the range -6..6. This will be revised in a future version.

## Portability 

The code in this directory has been written to conform to the ANSI C99 standard.

It compiles and has been tested on Mac OS X 10.10 and GNU/Linux Raspbian (Wheezy).

It should also compile on Windows using Visual Studio 2013 or later, or using an environment that includes a compliant compiler such as CYGWIN or MINGW. This has not been tested, however.

## Compiling

To compile the code in a Unix environment, type `make` from a command-line prompt.

This will generate an executable named `km_test`.

To delete built files, type `make clean`.

## Running

To run the test program type `./km_test <infile.csv> <outfile.csv>` from a command-line prompt, where `<infile.csv>` is the path to a CSV file containing N rows of equal length containing only floating point values and `<outfile.csv>` is the path where an output file will be written. The output file will contain N rows, each of which contains an integer representing the cluster id of the corresponding row in the input file.

## Optimisation

The k-means algorithm has been implemented using [Lloyd's algorithm](http://en.wikipedia.org/wiki/Lloyd's_algorithm) with the SQRT step omitted from the distance computation for efficiency. 

If further optimisation is required, a more efficient implementation such that proposed by Kanugo et al could be considered: http://www.cs.umd.edu/~mount/Projects/KMeans


