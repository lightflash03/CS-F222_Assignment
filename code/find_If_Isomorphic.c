#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}  

void permute(int *bijection, int l, int r, int adjacenyMatrix1[][r+1], int adjacenyMatrix2[][r+1])
{ 
   if (l == r) {
        for (int i = 0; i < r+1; i++) {
            for (int j = 0; j < r+1; j++) {
                if (adjacenyMatrix1[bijection[i]][bijection[j]] != adjacenyMatrix2[i][j]) {
                    return;
                }
            }
        }

        printf("Isomorphic.\n");
        for (int i = 0; i < (r+1); i++) {
            int j = 0;
            for (j = 0; j < r+1; j++) {
                if(bijection[j] == i) {
                    printf ("%d %d\n", bijection[j] + 1, j + 1);
                }
            }
        }
        exit(0);
   }

   else
   {
        int i;
       for (i = l; i <= r; i++)
       {
          swap((bijection+l), (bijection+i));
          permute(bijection, l+1, r, adjacenyMatrix1, adjacenyMatrix2);
          swap((bijection+l), (bijection+i));
       }
   }
}

int main(int argc, char **argv) {
    int numOfNodes1, numOfEdges1;
    FILE *inputFile1  = fopen(argv[1], "r");
    if (inputFile1 == NULL) {   
        printf("Error! Such a file does not exist\n"); 
        exit(-1);
    } 

    fscanf(inputFile1, "%d", &numOfNodes1);  
    fscanf(inputFile1, "%d", &numOfEdges1);

    int adjacenyMatrix1[numOfNodes1][numOfNodes1];

    for (int i = 0; i < numOfNodes1; i++) {
        for (int j = 0; j < numOfNodes1; j++) {
            adjacenyMatrix1[i][j] = 0;
        }
    }

    for (int i = 0; i < numOfEdges1; i++) {
        int endPoint1, endPoint2;
        fscanf(inputFile1, "%d", &endPoint1);
        fscanf(inputFile1, "%d", &endPoint2);
        adjacenyMatrix1[endPoint1-1][endPoint2-1]++;
        adjacenyMatrix1[endPoint2-1][endPoint1-1]++;
    }

    int degreeSequence1[numOfNodes1];
    for (int i = 0; i < numOfNodes1; i++) {
        int sum = 0;
        for (int j = 0; j < numOfNodes1; j++) {
            sum += adjacenyMatrix1[i][j];
        }
        degreeSequence1[i] = sum;
    }

    for (int i = 0; i < numOfNodes1; i++) {
        for (int j = i + 1; j < numOfNodes1; j++) {
            if (degreeSequence1[i] < degreeSequence1[j]) {
                int temp = degreeSequence1[i];
                degreeSequence1[i] = degreeSequence1[j];
                degreeSequence1[j] = temp;
            }
        }
    }

    // ------------------------------------------------------------------- //

    int numOfNodes2, numOfEdges2;
    FILE *inputFile2  = fopen(argv[2], "r");
    if (inputFile2 == NULL) {   
        printf("Error! Such a file does not exist\n"); 
        exit(-1);
    } 

    fscanf(inputFile2, "%d", &numOfNodes2);  
    fscanf(inputFile2, "%d", &numOfEdges2);

    if ((numOfEdges1 != numOfEdges2) || (numOfNodes1 != numOfNodes2)) {
        printf ("Not Isomorphic\n");
        return 0;
    }

    int adjacenyMatrix2[numOfNodes2][numOfNodes2];

    for (int i = 0; i < numOfNodes2; i++) {
        for (int j = 0; j < numOfNodes2; j++) {
            adjacenyMatrix2[i][j] = 0;
        }
    }

    for (int i = 0; i < numOfEdges2; i++) {
        int endPoint1, endPoint2;
        fscanf(inputFile2, "%d", &endPoint1);
        fscanf(inputFile2, "%d", &endPoint2);
        adjacenyMatrix2[endPoint1-1][endPoint2-1]++;
        adjacenyMatrix2[endPoint2-1][endPoint1-1]++;
    }

    int degreeSequence2[numOfNodes2];
    for (int i = 0; i < numOfNodes2; i++) {
        int sum = 0;
        for (int j = 0; j < numOfNodes2; j++) {
            sum += adjacenyMatrix2[i][j];
        }
        degreeSequence2[i] = sum;
    }
    
    for (int i = 0; i < numOfNodes2; i++) {
        for (int j = i + 1; j < numOfNodes2; j++) {
            if (degreeSequence2[i] < degreeSequence2[j]) {
                int temp = degreeSequence2[i];
                degreeSequence2[i] = degreeSequence2[j];
                degreeSequence2[j] = temp;
            }
        }
    }

    // -------------------------------------------------------------- //

    for (int i = 0; i < numOfNodes1; i++) {
        if (degreeSequence1[i] != degreeSequence2[i]) {
            printf ("Not Isomorphic\n");
            return 0;
        }
    }

    int bijection[numOfNodes1];

    for (int i = 0; i < numOfNodes1; i++) {
        bijection[i] = i;
    }

    permute (bijection, 0, numOfNodes1-1, adjacenyMatrix1, adjacenyMatrix2);

    printf ("Not Isomorphic, no bijection found.\n");

    return 0;
}
