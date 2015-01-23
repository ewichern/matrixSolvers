#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>
using namespace std;

template <typename Object>
class matrix
{
public:
	matrix( int rows, int cols ) : array( rows )
{
		for( auto & thisRow : array )
			thisRow.resize( cols );
}

	/*  Not yet supported
    matrix( initializer_list<vector<Object>> lst ) : array( lst.size( ) )
    {
        int i = 0;
        for( auto & v : lst )
            array[ i++ ] = std::move( v );
    }
	 */

	matrix( const vector<vector<Object>> & v ) : array{ v }
	{ }

	/*  Not yet supported
	matrix( vector<vector<Object>> && v ) : array{ std::move( v ) }
	{ }
	 */

	const vector<Object> & operator[]( int row ) const
	{ return array[ row ]; }
	vector<Object> & operator[]( int row )
	{ return array[ row ]; }

	int numrows( ) const
	{ return array.size( ); }
	int numcols( ) const
	{ return numrows( ) ? array[ 0 ].size( ) : 0; }


	bool operator== (const matrix<Object>& m) const
	{
		if (numcols() != m.numcols() || numrows() != m.numrows())
			return false;

		const matrix<Object>& self = *this;

		for (int j = 0; j < m.numrows(); ++j)
			for (int i = 0; i < m.numcols(); ++i)
			{
				if (self[j][i] != m[j][i])
					return false;
			}
		return true;
	}

private:
vector<vector<Object>> array;
};



template <typename Object>
std::ostream& operator<< (std::ostream& out, const matrix<Object>& m)
{
	for (int j = 0; j < m.numrows(); ++j)
	{
		for (int i = 0; i < m.numcols(); ++i)
		{
			if (i > 0)
				out << ' ';
			out << m[j][i];
		}
		out << "\n";
	}
	return out;
}


#endif


