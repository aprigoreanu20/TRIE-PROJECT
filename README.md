# TRIE PROJECT
**OVERVIEW**\
The purpose of this project is to efficiently store and search strings, using a specialized data stucture, trie. Written in the C language, the implementation uses a tree data structure for storing words read from an input file. The project provides additional functionalities, such as computing statistics based on the tree, searching suffixes in the tree and turning the tree into a compact one.

**IMPLEMENTATION DETAILS**\
The tree is built based on words read from an input file. Each node of the trie represents a character, and suffixes are stored as paths from the root to leaf nodes.
A suffix is a substring that starts at any position in a word and continues up to its end. To simplify the implementation, the node also holds additional information, such as the string formed by covering the path from the root to the current path, the number of direct descendants and the level of the node. Each node has up to 27 children representing English alphabet characters, and edges denoting the characters. By convention, the '$' character is used to terminate a suffix.

**COMPILATION**\
The project includes a Makefile. To compile the project, type *make* in the terminal. This command will generate an executable named *out*. Each feature is executed with a separate command in the command line (see below). To remove the executable and other compiled files, type *make clean* in the terminal.

**FEATURES**\
For each feature, the project is run using a different command in the command line
1. *CREATE TRIE*\
The trie is created by adding words read from an input file. The tree is then displayed level order in the output file.\
To run the project for this feature, type the following command:\
./out -1 [input_file] [output_file]
3. *CALCULATE STATISTICS*\
Once the tree is built from the words in the input file, it is processed to compute various statistics, including the number of terminal leaves, the maximum number of descendants, and the number of suffixes of length k, where k is specified via the command line.\
To run the project for this feature, type the following command:\
./out -2 [k] [input_file] [output_file]
5. *SEARCH SUFFIXES*\
The trie is created based on the words read. The input file also contains the suffixes, which will be searched in the tree. The results of the search are displayed in the output file.\
To run the project for this feature, type the following command:\
./out -3 [input_file] [output_file]
7. *BUILD COMPACT TREE*\
The words read from an input file are added to a tree, which is then turned into a compact trie by eliminating redundant links from the tree. The compact trie is displayed level order in the output file.\
To run the project for this feature, type the following command:\
./out -4 [input_file] [output_file]
