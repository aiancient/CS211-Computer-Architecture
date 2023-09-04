#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

unsigned int cost (
    unsigned int matrixCount,
    unsigned int* rowSizes,
    unsigned int* colSizes
) {
    if ( matrixCount==1 ) { // Base case.
        return 0; // No multplication to be done.
    } else {

        unsigned int numPossibleSplits = matrixCount-1; // Think: if there are two matrices to multiply, there is one way to split.
        // AB: (A)(B)
        // ABC: (A)(BC) and (AB)(C)

        unsigned int costs[numPossibleSplits];
        for ( unsigned int split=0; split<numPossibleSplits; split++ ) {

            unsigned int l = rowSizes[0];
            assert ( colSizes[split] == rowSizes[split+1] );
            unsigned int m = colSizes[split];
            unsigned int n = colSizes[matrixCount-1];

            costs[split] =
                cost( split+1, rowSizes, colSizes ) + // cost of left subchain
                l * m * n + // cost of multiplying the two chains
                cost( matrixCount-split-1, rowSizes+split+1, colSizes+split+1 ); // cost of right subchain
        }

        unsigned int minCost = costs[0];
        for ( unsigned int split=1; split<numPossibleSplits; split++ ) {
            if ( costs[split]<minCost ) {
                minCost = costs[split];
            }
        }

        return minCost;
    }
}

void matMul (
    unsigned int l,
    unsigned int m,
    unsigned int n,
    int** matrix_a,
    int** matrix_b,
    int** matMulProduct
) {

     //printf("l=%d\n", l);
     //printf("m=%d\n", m);
     //printf("n=%d\n", n);

    for ( unsigned int i=0; i<l; i++ ) {
        // printf("i=%d\n", i);
        for ( unsigned int k=0; k<n; k++ ) {
            // printf("k=%d\n", k);
            matMulProduct[i][k] = 0;
            for ( unsigned int j=0; j<m; j++ ) {
                matMulProduct[i][k] += matrix_a[i][j] * matrix_b[j][k];
            }
        }
    }

}

int main(int argc, char* argv[]) {

    unsigned int matrixCount;
    unsigned int* rowSizes;
    unsigned int* colSizes;

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    if (!fscanf(fp, "%d\n", &matrixCount)) {
        perror("reading the number of matrices failed");
        exit(EXIT_FAILURE);
    }

    rowSizes = calloc( matrixCount, sizeof(int) );
    colSizes = calloc( matrixCount, sizeof(int) );

    int count = 0; 
    unsigned int length_l, length_m;
    unsigned int temp, length_n;
    int** matrix_a;
    int** matrix_b;

    for (unsigned int matIndex=0; matIndex<matrixCount; matIndex++) {

        unsigned int rows, cols;
        if (!fscanf(fp, "%d %d\n", &rows, &cols)) {
            perror("reading the dimensions of matrix failed");
            exit(EXIT_FAILURE);
        }
        rowSizes[matIndex] = rows;
        colSizes[matIndex] = cols;

        if(count==0)
        {
            length_l = rows; 
            length_m = cols;  
            matrix_a = calloc( length_l, sizeof(int*) );
            for ( unsigned int i=0; i<length_l; i++ ) {
                matrix_a[i] = calloc( length_m, sizeof(int) );
                for ( unsigned int j=0; j<length_m; j++ ) {
                    int element;
                    if (!fscanf(fp, "%d", &element)) {
                        perror("reading the elements of matrix A failed");
                        exit(EXIT_FAILURE);
                    }
                    matrix_a[i][j] = element;
                }
            }
            count++; 
        }

        else
        {
            temp = rows; 
            length_n = cols; 
            assert ( temp == length_m ); 
            matrix_b = calloc( length_m, sizeof(int*) );
            for ( unsigned int j=0; j<length_m; j++ ) {
                matrix_b[j] = calloc( length_n, sizeof(int) );
                for ( unsigned int k=0; k<length_n; k++ ) {
                    int element;
                    if (!fscanf(fp, "%d", &element)) {
                        perror("reading the elements of matrix B failed");
                        exit(EXIT_FAILURE);
                    }
                matrix_b[j][k] = element;
                }
            }

            // Malloc the memory space for the matMulProduct
            int** matMulProduct = calloc( length_l, sizeof(int*) );
            for ( unsigned int i=0; i<length_l; i++ ) {
                matMulProduct[i] = calloc( length_n, sizeof(int) );
            }

            matMul ( length_l, length_m, length_n, matrix_a, matrix_b, matMulProduct );
            
            if(matIndex+1 == matrixCount)
            {
                printf("%d\n", cost(matrixCount, rowSizes, colSizes) );
                for ( unsigned int i=0; i<length_l; i++ ) {
                    for ( unsigned int k=0; k<length_n; k++ ) {
                        printf ("%d ", matMulProduct[i][k]);
                    }
                    printf ("\n");
                }
            }

            for ( unsigned int i=0; i<length_l; i++ ) {
                free( matrix_a[i] );
            }

            free( matrix_a );
            matrix_a = matMulProduct;

            for ( unsigned int j=0; j<length_m; j++ ) {
                free( matrix_b[j] );
            }
            free( matrix_b );

            length_m = cols; 
            count++; 
        }

    }

    //printf("%d\n", cost(matrixCount, rowSizes, colSizes) );

    free(colSizes);
    free(rowSizes);
    
    fclose(fp);

    exit(EXIT_SUCCESS);

}
        
    