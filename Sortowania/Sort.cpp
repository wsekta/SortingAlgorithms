#include "Sort.h"
#include <stdlib.h>
#include <algorithm> 
#include <memory.h>

void updateHeap( int* tab, int l, int p );
void merge( int* tab, int* tmp, int size, int l, int m, int p );





//====================================
void insertSort( int *tab, int size )
{
	for ( int i = 1; i < size; i++ )
	{
		int x = tab[ i ];
		int j = i - 1;
		while ( ( j >= 0 ) && ( tab[ j ] > x ) )
			tab[ j + 1 ] = tab[ j-- ];
		tab[ j + 1 ] = x;
	}
}





//====================================
void halfSort( int *tab, int size )
{
	for ( int i = 1; i < size; i++ ) {

		int x = tab[ i ];
		int l = 0;
		int p = i - 1;
		int sr;

		while ( l <= p )
		{
			sr = ( l + p ) / 2;
			if ( x < tab[ sr ] )
				p = sr - 1;
			else
				l = sr + 1;
		}
		if ( l < i )
		{
			memcpy( tab + l + 1, tab + l, ( i - l ) * sizeof( int ) ); // MEGAFAST!
			//for ( int j = i - 1; j >= sr; j-- )
				//tab[ j + 1 ] = tab[ j ];
			tab[ l ] = x;
		}
	}
}





//====================================
void bubbleSort( int *tab, int size )
{
	//od du¿ych do ma³ych
	for ( int j = 0; j < size - 1; j++ )
	{
		for ( int i = size - 1; i > j; i-- )
		{
			if ( tab[ i ] < tab[ i - 1 ] )
			{
				int temp = tab[ i ];
				tab[ i ] = tab[ i - 1 ];
				tab[ i - 1 ] = temp;
			}
		}
	}
}





//====================================
void selectSort( int *tab, int size )
{
	for ( int i = 0; i < size - 1; i++ )
	{
		int min = tab[ i ];
		int pozMin = i;

		for ( int j = i + 1; j < size; j++ )
			if ( tab[ j ] < min )
			{
				min = tab[ j ];
				pozMin = j;
			}

		tab[ pozMin ] = tab[ i ];
		tab[ i ] = min;
	}
}





//====================================
void mixedSort( int *tab, int size )
{
	//od du¿ych do ma³ych
	//do ostatniej zamiany
	int l = 1;
	int r = size - 1;
	int k = size - 1;

	while ( r > l ) {
		for ( int j = r; j >= l; j-- )
		{

			if ( tab[ j - 1 ] > tab[ j ] )
			{
				int x = tab[ j - 1 ];
				tab[ j - 1 ] = tab[ j ];
				tab[ j ] = x;
				k = j;
			}
		}
		l = k + 1;

		for ( int j = l; j <= r; j++ )
		{
			if ( tab[ j - 1 ] > tab[ j ] )
			{
				int x = tab[ j - 1 ];
				tab[ j - 1 ] = tab[ j ];
				tab[ j ] = x;
				k = j;
			}
		}
		r = k - 1;
	}
}





//====================================
void heapSort( int *tab, int size )
{
	//stogowe/kopcowe
	//kopiec: h[i] >= h[2i] oraz h[i] >= h[2i+1]
	//
	//
	for ( int j = size / 2 + 1; j > 0; )
		updateHeap( tab, --j, size - 1 );

	for ( int j = size - 1; j; )
	{
		int x = tab[ j ];
		tab[ j ] = tab[ 0 ];
		tab[ 0 ] = x;
		updateHeap( tab, 0, --j );
	}
}





//====================================
void updateHeap( int* tab, int l, int p )
{
	int i = l;
	int j = 2 * i;
	int x = tab[ i ];

	while ( j <= p )
	{
		if ( j < p )
			if ( tab[ j ] < tab[ j + 1 ] )
				j++;

		if ( tab[ j ] <= x ) break;

		tab[ i ] = tab[ j ];
		i = j;
		j = 2 * i;
	}
	tab[ i ] = x;
}





//====================================
void quickSort( int *tab, int l, int p )
{
	int i = l;
	int j = p;
	int x = tab[ ( i + j ) / 2 ];

	while ( i < j )
	{
		while ( tab[ i ] < x ) i++;
		while ( tab[ j ] > x ) j--;

		if ( i <= j )
		{
			int pom = tab[ i ];
			tab[ i ] = tab[ j ];
			tab[ j ] = pom;
			i++;
			j--;
		}
	}
	if ( l < j )
		quickSort( tab, l, j );
	if ( i < p )
		quickSort( tab, i, p );
}





//====================================
void mergeSort( int* tab, int* tmp, int size, int l, int p )
{
	if ( l <p )
	{
		int m = ( l + p ) / 2;
		mergeSort( tab, tmp, size, l, m );
		mergeSort( tab, tmp, size, m + 1, p );
		merge( tab, tmp, size, l, m, p );
	}
}





//====================================
void merge( int* tab, int* tmp, int size, int l, int m, int p )
{
	memcpy( tmp, tab, size * sizeof( *tab ) );

	int i = l;
	int j = m + 1;
	int k = l;

	while ( i <= m && j <= p )
	{
		if ( tmp[ i ] < tmp[ j ] )
			tab[ k++ ] = tmp[ i++ ];
		else
			tab[ k++ ] = tmp[ j++ ];
	}
	while ( i <= m )
		tab[ k++ ] = tmp[ i++ ];
}





//====================================
int copy( int* tab, int* temp, int nSize, int* i, int* ix )
{
	tab[ ( *i )++ ] = temp[ ( *ix )++ ];
	if ( *ix == nSize )
		return 1;

	return ( temp[ *ix - 1 ] > temp[ *ix ] );
}





//====================================
void CopySerie( int* tab, int* temp, int nSize, int* i, int* ix )
{
	while ( !copy( tab, temp, nSize, i, ix ) );
}





//====================================
void mergeSortSeq( int* tab, int nSize )
{
	int* tmp1 = ( int* )calloc( nSize, sizeof( int ) );
	int* tmp2 = ( int* )calloc( nSize, sizeof( int ) );
	if ( !tmp1 || !tmp2 )
	{
		perror( "MEMORY ERROR!" );
		return;
	}

	int nSerie;
	do
	{
		int i = 0;
		int j = 0;
		int k = 0;
		while ( i < nSize )
		{
			while ( ( i < nSize - 1 ) && ( tab[ i ] <= tab[ i + 1 ] ) )
				tmp1[ j++ ] = tab[ i++ ];
			if ( i < nSize )
				tmp1[ j++ ] = tab[ i++ ];
			while ( ( i < nSize - 1 ) && ( tab[ i ] < tab[ i + 1 ] ) )
				tmp2[ k++ ] = tab[ i++ ];
			if ( i < nSize )
				tmp2[ k++ ] = tab[ i++ ];
		}

		int nLast1 = j;
		int nLast2 = k;
		nSerie = 0;
		i = j = k = 0;

		while ( ( j < nLast1 ) && ( k < nLast2 ) )
		{
			int end = 0;
			while ( !end )
			{
				if ( tmp1[ j ] <= tmp2[ k ] )
				{
					end = copy( tab, tmp1, nLast1, &i, &j );
					if ( end )
						CopySerie( tab, tmp2, nLast2, &i, &k );
				}
				else
				{
					end = copy( tab, tmp2, nLast2, &i, &k );
					if ( end )
						CopySerie( tab, tmp1, nLast1, &i, &j );
				}
			}
			nSerie++;
		}

		while ( j < nLast1 )
		{
			CopySerie( tab, tmp1, nLast1, &i, &j );
			nSerie++;
		}

	} while ( nSerie > 1 );

	free( tmp1 );
	free( tmp2 );
}