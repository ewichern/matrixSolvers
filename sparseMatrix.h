#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

template<typename Object>
class sparseMatrix {

	struct Tuple {
		int i;
		int j;

		Tuple(int ii, int jj) :
				i(ii), j(jj) {
		}

		bool operator==(const Tuple& right) const {
			return i == right.i && j == right.j;
		}

		void put(std::ostream& out) const {
			out << "(" << i << "," << j << ")";
		}

	};

	class TupleHash {
		/** add your code here */
		// Going to assign each member of the tuple a different
		// prime multiplier.
	public:
		std::size_t operator()(const Tuple& t) const {
			unsigned temp = 313 * t.i + 317 * t.j;
			return (std::size_t) temp;
		}
	};

	/** add your code here to use unordered_map to create
	 a hash table mapping Tuples onto Objects */
	typedef std::unordered_map<Tuple, Object, TupleHash> HashTable;

	typedef typename HashTable::value_type valueType;
	typedef typename HashTable::iterator hashIt;
	typedef typename HashTable::const_iterator hashConstIt;

public:
	class Row {
		sparseMatrix<Object>* m;
		int rowNum;
	public:
		Row(sparseMatrix<Object>* matrix, int row) :
				m(matrix), rowNum(row) {
		}

		Object& operator[](int col) const {
			/**
			 Add your code here to locate the [rowNum][col]
			 element of the matrix.
			 */

			HashTable &mapRef = m->data;
			Tuple keyAt(rowNum, col);

			hashIt loc = mapRef.find(keyAt);

			if (loc == mapRef.end()) {
				//std::cerr << "Did not find a value for coords ";
				//keyAt.put(std::cerr);
				//std::cerr << ". Default value is " << m->defaultValue << endl;

				valueType newVal(keyAt, m->defaultValue);
				loc = mapRef.insert(newVal).first;

			}
			/*
			 else {
			 //std::cerr << "Found " << loc->second << " at ";
			 //keyAt.put(std::cerr);
			 //std::cerr << "." << endl;
			 //return newLoc.first->second;
			 }
			 */
			return loc->second;
			/*
			 if (loc != mapRef.end()) {
			 //std::cerr << "Found " << loc->second << " at ";
			 //keyAt.put(std::cerr);
			 //std::cerr << "." << endl;
			 return loc->second;
			 } else {
			 //std::cerr << "Did not find a value for coords ";
			 //keyAt.put(std::cerr);
			 //std::cerr << ". Default value is " << m->defaultValue << endl;
			 valueType newVal(keyAt, m->defaultValue);
			 auto newLoc = mapRef.insert(newVal);
			 return newLoc.first->second;
			 }
			 */
		}

	};

	class ConstRow {
		const sparseMatrix<Object>* m;
		int rowNum;
	public:
		ConstRow(const sparseMatrix<Object>* matrix, int row) :
				m(matrix), rowNum(row) {
		}

		Object operator[](int col) const {
			/**
			 Add your code here to locate the [rowNum][col]
			 element of the matrix (or return the default
			 value if that element does not exist.
			 */

			// const Object& defaultValue = m->defaultValue;

			const HashTable & mapRef = m->data;
			Tuple keyAt(rowNum, col);

			hashConstIt loc = mapRef.find(keyAt);

			if (loc != mapRef.cend()) {
				//std::cerr << "Found " << loc->second << " at ";
				//keyAt.put(std::cerr);
				//std::cerr << "." << endl;
				return loc->second;
			} else {
				//std::cerr << "Did not find a value for coords ";
				//keyAt.put(cerr);
				//std::cerr << ". Default value is " << m->defaultValue << endl;
				return m->defaultValue;
			}
		}
	};

	sparseMatrix(int rows, int cols, const Object& defaultv = Object()) :
			nRows(rows), nCols(cols), defaultValue(defaultv) {
	}

	/* not yet supported
	 sparseMatrix( initializer_list<vector<Object>> lst ) : array( lst.size( ) )
	 {
	 int i = 0;
	 for( auto & v : lst )
	 array[ i++ ] = std::move( v );
	 }
	 */

	sparseMatrix(const vector<vector<Object>> & v, const Object& defaultv =
			Object()) :
			nRows(v.size()), nCols(v[0].size()), defaultValue(defaultv) {
		for (int i = 0; i < nRows; ++i)
			for (int j = 0; j < nCols; ++j) {
				Tuple t(i, j);
				data[t] = v[j][i];
			}
	}
	/* not yet supported
	 sparseMatrix( vector<vector<Object>> && v ) : array{ std::move( v ) }
	 { }
	 */

	const ConstRow operator[](int row) const {
		return ConstRow(this, row);
	}

	Row operator[](int row) {
		return Row(this, row);
	}

	int numrows() const {
		return nRows;
	}
	int numcols() const {
		return nCols;
	}

	bool operator==(const sparseMatrix<Object>& m) const {
		if (numcols() != m.numcols() || numrows() != m.numrows())
			return false;

		const sparseMatrix<Object>& self = *this;

		for (int j = 0; j < m.numrows(); ++j)
			for (int i = 0; i < m.numcols(); ++i) {
				if (self[j][i] != m[j][i])
					return false;
			}
		return true;
	}
private:

	int nRows;
	int nCols;
	Object defaultValue;
	std::unordered_map<Tuple, Object, TupleHash> data;
};

template<typename Object>
std::ostream& operator<<(std::ostream& out, const sparseMatrix<Object>& m) {
	for (int j = 0; j < m.numrows(); ++j) {
		for (int i = 0; i < m.numcols(); ++i) {
			if (i > 0)
				out << ' ';
			out << m[j][i];
		}
		out << "\n";
	}
	return out;
}

#endif

