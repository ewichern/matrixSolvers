#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <unordered_map>

using namespace std;

template<typename Object>
class denseMatrix {

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
	public:
		std::size_t operator()(const Tuple& t) const {
			return (std::size_t) (3507 * t.i + 3049 * t.j);
		}
	};

	typedef std::unordered_map<Tuple, Object, TupleHash> HashTable;
	typedef typename HashTable::value_type valueType;

public:
	class Row {
		denseMatrix<Object>* m;
		int rowNum;
	public:
		Row(denseMatrix<Object>* matrix, int row) :
				m(matrix), rowNum(row) {
		}

		Object& operator[](int col) const {
			Tuple t(rowNum, col);
			auto pos = m->data.find(t);
			if (pos == m->data.end()) {
				valueType keyValue(t, m->defaultValue);
				pos = m->data.insert(keyValue).first;
			}
			return pos->second;
		}

	};

	class ConstRow {
		const denseMatrix<Object>* m;
		int rowNum;
	public:
		ConstRow(const denseMatrix<Object>* matrix, int row) :
				m(matrix), rowNum(row) {
		}

		Object operator[](int col) const {
			Tuple t(rowNum, col);
			auto pos = m->data.find(t);
			if (pos != m->data.end())
				return pos->second;
			else
				return m->defaultValue;
		}

	};

	denseMatrix(int rows, int cols, const Object& defaultv = Object()) :
			nRows(rows), nCols(cols), defaultValue(defaultv) {
	}

	/* not yet supported
	 denseMatrix( initializer_list<vector<Object>> lst ) : array( lst.size( ) )
	 {
	 int i = 0;
	 for( auto & v : lst )
	 array[ i++ ] = std::move( v );
	 }
	 */

	denseMatrix(const vector<vector<Object>> & v, const Object& defaultv =
			Object()) :
			nRows(v.size()), nCols(v[0].size()), defaultValue(defaultv) {
		for (int i = 0; i < nRows; ++i)
			for (int j = 0; j < nCols; ++j) {
				Tuple t(i, j);
				data[t] = v[j][i];
			}
	}
	/* not yet supported
	 denseMatrix( vector<vector<Object>> && v ) : array{ std::move( v ) }
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

	bool operator==(const denseMatrix<Object>& m) const {
		if (numcols() != m.numcols() || numrows() != m.numrows())
			return false;

		const denseMatrix<Object>& self = *this;

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
std::ostream& operator<<(std::ostream& out, const denseMatrix<Object>& m) {
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

