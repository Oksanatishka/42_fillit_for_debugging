# fillit

Description
This program will take a file as parameter, which contains a list of Tetriminos, and arrange them in order to create the smallest square possible.

The program
The executable “fillit” takes only one parameter, a file which contains a list of Tetriminos to assemble.

Input Sample:
Each tetraminos is represented with 4 lines of 4 characters, each followed by a new line. A Tetrimino is a classic piece of Tetris composed of 4 blocks. Each character must be either a block character(’#’) or an empty character (’.’). Each block of a Tetrimino must touch at least one other block on any of his 4 sides (up, down, left and right).

Solution
The program is divided in two parts:
A part that reads, validate, organize the input 
B part solves the problem using backtracking. 

Here is how the program works:


Reading the input and preparing the data
The program take the path of the input file as argument, returns usage instruction if argument is blank, error if there are more than 1 arguments.
The function main() calls setup(), here the buffer of the file reads 21 bytes while it counts and validate formally the block.
Kowning how many blocks are in the input file gen_matrices() allocates a list of size matrices (4×4) and then fill_matrices() fills it with the letters representing the different blocks.
The empty rows and column of the matries representig each block are removed by the functions clean_row_matrices() and clean_column_matrices(), (this is probably not the best way to do this).

Solving the problem
Takes the list of tetraminos and evaluates how big should be the minimum square that can hold all those pieces.
Generates a matrix of size min_size with the fucntion gen_row().
Calls the function bfs_big_fucking_solver() wich taking in the emty solution grid and the list of tetraminos solves the problem wihtout allocating any more memory trough backtracking, insertions and restorations.
The solution is printed by print_row(row)
