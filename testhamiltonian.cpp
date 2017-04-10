e#include <stdio.h>
#include <stdlib.h>

/**
Search for a hamiltonian cycle, than if there is no hamiltonian cycle, we can search for an almost hamiltonian path using dynamic programming and tabulation tehniques.
This has been don for a college class in graph theory. And together with my code I supply a few of test cases which we were given in the class.

To run it you need to pass to it as an argumant the name of a file wich contains an adjacency matrix.
So if we have a file test1.txt we call the compiled program  with a command to the cmd "testhamiltonian.exe test1.txt".

File should in a first line state the number of vertices in the graph, followed by the adjacency matrix in the next lines.

For instance test1.txt could be:
4
0111
1011
1101
1101
*/
void findHamiltonian(int *neighborhood, int *passedV, int *pathV,int currentV, int N);
void findAlmostHamiltonian(int *neighborhood, int *passedV, int *pathV,int currentV, int N);
int allPassed(int *passedV, int *pathV, int *neighborhood, int N);
void addToPath(int *pathV, int vertex, int N);
void removeFromPath(int *pathV, int vertex, int N);
void printPath(int *pathV, int N);
int isHamiltonianCycle(int *pathV, int *neighborhood, int N);

int main(int argc, char **argv) {
	
	if (argc != 2) {
        fprintf(stderr, "File need'n sir.\n");
        exit(1);
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "File cannout be openned sir!.\n");
        exit(1);    
    }

    int N;
    fscanf(input, "%d", &N);
    int neighborhood[N][N];
    int passedV[N];
    int pathV[N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(input, "%d", &neighborhood[i][j]);
        }
    }
    int flag = 0;
    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < N; j++) {
       		passedV[j] = 0;
       		pathV[j] = -1;
    	}
        
    	findHamiltonian(&neighborhood[0][0], &passedV[0], &pathV[0], i, N);
    	
    	if (allPassed(&passedV[0], &pathV[0], &neighborhood[0][0], N)) {
    		printf("The graph is hamiltonian with  a cycle:\n");
    		printPath(&pathV[0], N);
    	    printf(" -> %d\r\n", pathV[0] + 1);
    		break;
    	}
    	
    	if (i == N-1) {
    		flag = 1;
    	}
    }
    
    if (flag) {
    	for (int i = 0; i < N; i++) {
	    	for (int j = 0; j < N; j++) {
       		passedV[j] = 0;
       		pathV[j] = -1;
    	}
	        
	    	findAlmostHamiltonian(&neighborhood[0][0], &passedV[0], &pathV[0], i, N);
	    	if (allPassed(&passedV[0], &pathV[0], &neighborhood[0][0], N) && !isHamiltonianCycle(&pathV[0], &neighborhood[0][0], N) ) {
	    		printf("The graph is almost hamiltonian with a path:\n");
	    		printPath(&pathV[0], N);
	    		printf("\r\n");
	    		break;
	    	}
	    
	    	if (i == N-1) {
	    		printf("The graph has no path that traverses all vertices.\n");
	    	}
	    }	
    }
   
    return 0;
}

//find  the hamiltonian cycle
void findHamiltonian(int *neighborhood, int *passedV, int *pathV, int currentV,int N){
	passedV[currentV] = 1;
	
	int flag = 0;

	for (int i = 0; i < N; i++) {
		if ((neighborhood[currentV*N + i] == 1) && (!passedV[i])) {
			flag = 1;
			findHamiltonian(&neighborhood[0], &passedV[0], &pathV[0], i, N);
		}
	}
	
	addToPath(&pathV[0], currentV, N);
	
	if (!allPassed(&passedV[0], &pathV[0], &neighborhood[0], N) || !neighborhood[pathV[N-1]*N + pathV[0]]) {
			passedV[currentV] = 0;
			removeFromPath(&pathV[0], currentV, N);
	} 
}

//find an almost hamiltonian path
void findAlmostHamiltonian(int *neighborhood, int *passedV, int *pathV, int currentV,int N){
	passedV[currentV] = 1;
	int flag = 0;
	for (int i = 0; i < N; i++) {
		if ((neighborhood[currentV*N + i] == 1) && (!passedV[i])) {
			flag = 1;
			findAlmostHamiltonian(&neighborhood[0], &passedV[0], &pathV[0], i, N);
		}
	}
	
	if (!allPassed(&passedV[0], &pathV[0], &neighborhood[0], N) ) {
			passedV[currentV] = 0;
	} else {
		addToPath(&pathV[0], currentV, N);
	}
	
}

//check if all vertices are in the path
int allPassed(int *passedV, int *pathV, int *neighborhood, int N) {
	for (int i = 0; i < N; i++) {
		if (passedV[i] == 0) {
			return 0;
		}
	}
	
	return 1;
}

//a a vertex to the path
void addToPath(int *pathV, int vertex, int N){
	for (int i = N-1; i >= 0; i--) {
		if (pathV[i] == -1) {
			pathV[i] = vertex;
			break;
		} 
	}
}

//remove a vertex from the path
void removeFromPath(int *pathV, int vertex, int N){
	for (int i = N-1; i >= 0; i--) {
		if (pathV[i] == vertex) {
			pathV[i] = -1;
			break;
		} 
	}
}

//print the path to the stdio
void printPath(int *pathV, int N) {
	for (int i = 0; i < N; i++) {
		printf("%d", pathV[i] + 1);
		if (i != N - 1) {
			printf(" -> ");
		}
	}
}

//check if path is a hamiltonian cycle
int isHamiltonianCycle(int *pathV, int *neighborhood, int N) {
if (pathV[N-1] == -1 || pathV[0] == -1) {
	return 0;
} else if (neighborhood[pathV[N-1]*N + pathV[0]] == 1) {
	return 1;
}

return 0;
}
