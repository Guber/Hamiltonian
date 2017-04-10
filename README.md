# Hamiltonian

Search for a hamiltonian cycle, than if there is no hamiltonian cycle, we can search for an almost hamiltonian path using dynamic programming and tabulation tehniques.
This has been don for a colleuge class in graph theory. And together with my code I supply a few of test cases which we were given in the class.

To run it you need to pass to it as an argumant the name of a file wich contains an adjacency matrix.
So if we have a file test1.txt we call the compiled program  with a command to the cmd "testhamiltonian.exe test1.txt".

File should in a first line state the number of vetices in the graph, followed by the adjacency matrix in the next lines.

For instance test1.txt could be:
4

0111

1011

1101

1101
