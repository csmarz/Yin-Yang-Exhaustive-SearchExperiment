# Yin-Yang-Exhaustive-Search

These are some programs for Exhaustive Search Yin-Yang solver, Prune-and-Search Yin-Yang solver, and Yin-Yang verifier.

### How to run

Open cmd in the designated folder and run the exe file.

### Input/Output Format

The input for programs without "Input" in its name consists of two integers, representing the value of m and n, separated with a space.
The input format is as follows:

    2 3

The program fills a 2×3 Array with empty cells. The illustration is as follows:

    * * *
    * * *

The input for programs with "Input" in its name consists of two integers, along with the value of each cell. Black cirlce is 0, White circle is 1, and Empty cell is *.
The input format is as follows:

    3 3
    1 * 0
    0 * 0
    * * *

The output consists of the number of solutions based on input, along with the duration of the algorithm. The program runs the algorithm three times to receive three different durations in a single run.

Output example for the first input:

	18
    Duration : 0.000639 seconds
    18
    Duration : 0.000726 seconds
    18
    Duration : 0.000654 seconds

Output example for the second input:

    1
    Duration : 0.000378 seconds
    1
    Duration : 0.000311 seconds
    1
    Duration : 0.000378 seconds

For the Verifier, the input format is the same as "Input" programs, except that the accepted cell values are 0 and 1. 
The format is as follows:

    3 3
    1 1 1
    0 0 1
    1 1 1

The output consist of if the configuration is a solution or not, and the duration of the program.
Example:

    Configuration is a solution
    Duration : 0.000385 seconds
    Configuration is a solution
    Duration : 0.00039 seconds
    Configuration is a solution
    Duration : 0.00042 seconds

### Expeted Running Time

The asymptotic time complexity for the solver programs is O(max(mn,2^(e))) where 'e' is the number of empty cells. The more empty cells in a Yin-Yang instance, the longer the program runs.

For more information about Yin-Yang puzzle see https://erikdemaine.org/fonts/yinyang/ .
