#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include <iomanip>

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
		// Going to assign each member of the tuple a different
		// prime multiplier.
	public:
		std::size_t operator()(const Tuple& t) const {
			unsigned temp = 313 * t.i + 317 * t.j;
			return (std::size_t) temp;
		}
	};

	/** use unordered_map to create a hash table mapping Tuples onto Objects */
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
			/**locate the [rowNum][col] element of the matrix.*/

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

			return loc->second;
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
			/** locate the [rowNum][col] element of the matrix (or return the default
			 value if that element does not exist.
			 */

			const HashTable & mapRef = m->data;
			Tuple keyAt(rowNum, col);

			hashConstIt loc = mapRef.find(keyAt);

			if (loc == mapRef.cend()) {
				return m->defaultValue;
			}

			return loc->second;
		}
	};

	sparseMatrix();
	sparseMatrix(int, int, const Object&);
	sparseMatrix(const vector<vector<Object>> &,
				const Object&);
	sparseMatrix(const sparseMatrix<Object>&);
	~sparseMatrix() { data.clear(); }

	bool operator==(const sparseMatrix<Object>&) const;
	const sparseMatrix<Object>& operator=(const sparseMatrix<Object>&);
	const sparseMatrix<Object>& operator*(const sparseMatrix<Object>&);

	const ConstRow operator[](int row) const {return ConstRow(this, row);}
	Row operator[](int row) {return Row(this, row);}

	int numrows() const {return nRows;}
	int numcols() const {return nCols;}

private:

	int nRows;
	int nCols;
	Object defaultValue;
	std::unordered_map<Tuple, Object, TupleHash> data;
};


template<typename Object>
sparseMatrix<Object>::sparseMatrix() :
			nRows(0), nCols(0), defaultValue(Object()) {
	}

// Constructor for matrix of size rows*cols, filled with defaultValue
template<typename Object>
sparseMatrix<Object>::sparseMatrix(int rows, int cols, const Object& defaultv = Object()) :
			nRows(rows), nCols(cols), defaultValue(defaultv) {
	}

// Constructor from an existing STL vector<vector>
template<typename Object>
sparseMatrix<Object>::sparseMatrix(const vector<vector<Object>> & v,
		const Object& defaultv = Object()) :
		nRows(v.size()), nCols(v[0].size()), defaultValue(defaultv) {

	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nCols; ++j) {
			Tuple t(i, j);
			data[t] = v[j][i];
		}
}

// Copy constructor
template<typename Object>
sparseMatrix<Object>::sparseMatrix(const sparseMatrix<Object>& right) {

	nRows = right.nRows;
	nCols = right.nCols;
	defaultValue = right.defaultValue;
	data = right.data;

}

// Overloaded operators
template<typename Object>
bool sparseMatrix<Object>::operator==(const sparseMatrix<Object>& m) const {
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

template<typename Object>
const sparseMatrix<Object>& sparseMatrix<Object>::operator=(
		const sparseMatrix<Object>& right) {
	if (this != right) {
		data.clear();
		data = right.data;
		nRows = right.nRows;
		nCols = right.nCols;
		defaultValue = right.defaultValue;
	}
	return *this;
}

template<typename Object>
const sparseMatrix<Object>& sparseMatrix<Object>::operator*(
		const sparseMatrix<Object>& right) {
	if (nCols == right.nRows) {
		sparseMatrix<Object> solution(nRows, right.nCols, Object());
		for (int i = 0; i < solution.numrows(); ++i){
			sparseMatrix<Object> Ai(this, i);

			for (int j = 0; j < solution.numcols(); ++j){
				Object tempValue;
				for (int k = 0; k < nRows; ++k){
					if (k == 0) {
						tempValue = (Ai[k]) * (right[k][j]);
					}
					else
						tempValue += (Ai[k]) * (right[k][j]);
				}
				solution[i][j] = tempValue;
			}
		}
		return solution;
	}
	else {
		sparseMatrix<double> failMatrix(1, 1, -999.0);
		return failMatrix;
	}
}

template<typename Object>
std::ostream& operator<<(std::ostream& out, const sparseMatrix<Object>& m) {
	for (int j = 0; j < m.numrows(); ++j) {
		for (int i = 0; i < m.numcols(); ++i) {
			// if (i > 0) out << ' ';
			out << setprecision(5) << setw(8);
			out << m[j][i];
		}
		out << "\n";
	}
	return out;
}

#endif

