#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "Sort.h"

#define PRT_TAB

void printTab( int *tab, int size );
int createTab( int **tab, int size );
void generateTab( int *tab, int size );
void copyTab( int *tab, int **res, int size );
void startQuickSort( int *tab, int size );
void startMergeSort( int *tab, int size );

int main()
{
	typedef void( *SortFoo )( int *, int );
	clock_t start = 0;
	clock_t end = 0;
	srand( 0 );
	int tabSize;
	scanf( "%d", &tabSize );

	int *tab = NULL;
	if ( !createTab( &tab, tabSize ) )
	{
		perror( "main: alocation memory error" );
		return 1;
	}

	int *tab2 = NULL;
	if ( !createTab( &tab2, tabSize ) )
	{
		perror( "main: alocation memory error" );
		return 1;
	}

	generateTab( tab, tabSize );

	SortFoo sortTab[] = { startQuickSort, heapSort, startMergeSort, mergeSortSeq ,  halfSort  , insertSort, selectSort, mixedSort, bubbleSort};
	const char* sortNames[] = { "Quick Sort", "Heap Sort", "Merge Sort", "Merge Sort Sequence " , "Half Sort"  , "Insert Sort", "Select Sort", "Mixed Sort", "Bubble Sort"};
	int no = sizeof( sortTab ) / sizeof( SortFoo );
	for ( int i = 0; i < no; i++ )
	{
		copyTab( tab, &tab2, tabSize );
		start = clock();
		sortTab[ i ]( tab2, tabSize );
		end = clock();
		printf( "%s get time %4.4lfsec\n", sortNames[ i ], ( ( double )( end - start ) ) / CLOCKS_PER_SEC );
#ifdef PRT_TAB
		printTab( tab2, tabSize );
#endif PRT_TAB
	}

	free( tab );
	free( tab2 );
}





//====================================
#ifdef PRT_TAB
void printTab( int *tab, int size )
{
	if ( size > 100 )
		size = 100;
	int *iter = tab;
	for ( int i = 0; i < size; i++ )
		printf( "%d\t", *( iter++ ) );
	printf( "\n" );
}
#endif





//====================================
int createTab( int **tab, int size )
{
	*tab = ( int* )malloc( size * sizeof( int ) );
	if ( !*tab )
		return 0;
	memset( &tab, 0, size * sizeof( int ) );
	return 1;
}





//====================================
void generateTab( int *tab, int size )
{
	for ( int i = 0; i < size; i++ )
		*( tab++ ) = rand() % size;
}





//====================================
void copyTab( int *tab, int **res, int size )
{
	memcpy( *res, tab, size * sizeof( int ) );
}





//====================================
void startQuickSort( int *tab, int size )
{
	quickSort( tab, 0, size - 1 );
}





//====================================
void startMergeSort( int *tab, int size )
{
	int *tmp = NULL;
	if ( !createTab( &tmp, size ) )
	{
		perror( "main: alocation memory error" );
		return;
	}
	mergeSort( tab, tmp, size, 0, size - 1 );
}