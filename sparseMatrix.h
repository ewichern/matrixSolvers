#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <exception>
#include <cmath>

using namespace std;

template<typename Object>
class sparseMatrix
{

	struct Tuple
	{
		int i;
		int j;

		Tuple(int ii, int jj) :
				i(ii), j(jj)
		{
		}

		bool operator==(const Tuple& right) const
		{
			return i == right.i && j == right.j;
		}

		void put(std::ostream& out) const
		{
			out << "(" << i << "," << j << ")";
		}

	};

	class TupleHash
	{
		// Going to assign each member of the tuple a different
		// prime multiplier.
	public:
		std::size_t operator()(const Tuple& t) const
		{
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
	class Row
	{
		sparseMatrix<Object>* m;
		int rowNum;
	public:
		Row(sparseMatrix<Object>* matrix, int row) :
				m(matrix), rowNum(row)
		{
		}

		Object& operator[](int col)
		{
			/**locate the [rowNum][col] element of the matrix.*/

			HashTable &mapRef = m->data;
			Tuple keyAt(rowNum, col);

			hashIt loc = mapRef.find(keyAt);

			if (loc == mapRef.end())
			{
				//std::cerr << "Did not find a value for coords ";
				//keyAt.put(std::cerr);
				//std::cerr << ". Default value is " << m->defaultValue << endl;

				valueType newVal(keyAt, m->defaultValue);
				loc = mapRef.insert(newVal).first;

			}

			return loc->second;
		}

	};

	class ConstRow
	{
		const sparseMatrix<Object>* m;
		int rowNum;
	public:
		ConstRow(const sparseMatrix<Object>* matrix, int row) :
				m(matrix), rowNum(row)
		{
		}

		Object operator[](int col) const
		{
			/** locate the [rowNum][col] element of the matrix (or return the default
			 value if that element does not exist.
			 */

			const HashTable & mapRef = m->data;
			Tuple keyAt(rowNum, col);

			hashConstIt loc = mapRef.find(keyAt);

			if (loc == mapRef.cend())
			{
				return m->defaultValue;
			}

			return loc->second;
		}
	};

	sparseMatrix();
	sparseMatrix(int, int, const Object&);
	sparseMatrix(const vector<vector<Object>> &, const Object&);
	sparseMatrix(const vector<Object> &, const Object&);
	sparseMatrix(const sparseMatrix<Object>&);
	~sparseMatrix()
	{
		data.clear();
	}

	bool operator==(const sparseMatrix<Object>&) const;
	bool operator!=(const sparseMatrix<Object>&) const;

	sparseMatrix<Object>& operator=(const sparseMatrix<Object>&);

	void eye();
	void eye(int, int);

	const ConstRow operator[](int row) const
	{
		return ConstRow(this, row);
	}
	Row operator[](int row)
	{
		return Row(this, row);
	}

	int numrows() const
	{
		return nRows;
	}
	int numcols() const
	{
		return nCols;
	}

	Object getDefault() const
	{
		return defaultValue;
	}

private:

	int nRows;
	int nCols;
	Object defaultValue;
	std::unordered_map<Tuple, Object, TupleHash> data;
};

struct MatrixSizeException: public exception
{
	const char * what() const throw ()
	{
		return "Matrix size mismatch";
	}
};

template<typename Object>
sparseMatrix<Object>::sparseMatrix() :
		nRows(0), nCols(0), defaultValue(Object())
{
}

// Constructor for matrix of size rows*cols, filled with defaultValue
template<typename Object>
sparseMatrix<Object>::sparseMatrix(int rows, int cols, const Object& defaultv =
		Object()) :
		nRows(rows), nCols(cols), defaultValue(defaultv)
{
}

// Constructor from an existing STL vector<vector>
template<typename Object>
sparseMatrix<Object>::sparseMatrix(const vector<vector<Object>> & v,
		const Object& defaultv = Object()) :
		nRows(v.size()), nCols(v[0].size()), defaultValue(defaultv)
{

	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nCols; ++j)
		{
			Tuple t(i, j);
			data[t] = v[j][i];
		}
}

// Constructor from an existing STL vector<vector>
template<typename Object>
sparseMatrix<Object>::sparseMatrix(const vector<Object> & v,
		const Object& defaultv = Object()) :
		nRows(v.size()), nCols(1), defaultValue(defaultv)
{

	for (int i = 0; i < nRows; ++i)
	{
		Tuple t(i, 0);
		data[t] = v[i];
	}
}

// Copy constructor
template<typename Object>
sparseMatrix<Object>::sparseMatrix(const sparseMatrix<Object>& right)
{

	nRows = right.nRows;
	nCols = right.nCols;
	defaultValue = right.defaultValue;
	data = right.data;

}

// Overloaded operators
template<typename Object>
bool sparseMatrix<Object>::operator==(const sparseMatrix<Object>& m) const
{
	if (numcols() != m.numcols() || numrows() != m.numrows())
		return false;

	const sparseMatrix<Object>& self = *this;

	for (int j = 0; j < m.numrows(); ++j)
		for (int i = 0; i < m.numcols(); ++i)
		{
			if (self[j][i] != m[j][i])
				return false;
		}
	return true;
}

template<typename Object>
bool sparseMatrix<Object>::operator!=(const sparseMatrix<Object>& m) const
{
	return (!(*this == m));
}

template<typename Object>
void sparseMatrix<Object>::eye()
{

	sparseMatrix<Object>& self = *this;
	if (nRows != nCols)
	{
		throw std::logic_error("Matrix size mismatch");
	}
	else
	{
		data.clear();
		for (int i = 0; i < nRows; ++i)
		{
			self[i][i] = 1.0;
		}
	}
}

template<typename Object>
void sparseMatrix<Object>::eye(int rows, int cols)
{

	sparseMatrix<Object>& self = *this;
	data.clear();
	nRows = rows;
	nCols = cols;
	for (int i = 0; i < nRows; ++i)
	{
		self[i][i] = 1.0;
	}
}

/**
 class eye {
 public:
 template<typename Object>
 sparseMatrix<Object> eye(int rows, int cols) {
 sparseMatrix<Object> m(rows, cols, 0);
 for (int i = 0; i < m.numrows(); ++i) {
 m[i][i] = 1.0;
 }
 return *m;
 }
 };
 */

template<typename Object>
sparseMatrix<Object>& sparseMatrix<Object>::operator=(
		const sparseMatrix<Object>& right)
{
	if (!(*this == right))
	{
		data.clear();
		data = right.data;
		nRows = right.nRows;
		nCols = right.nCols;
		defaultValue = right.defaultValue;
	}
	return *this;
}

template<typename Object>
sparseMatrix<Object> operator*(const sparseMatrix<Object>& left,
		const sparseMatrix<Object>& right)
{

	if (left.numcols() != right.numrows())
	{
		throw std::logic_error("Matrix size mismatch");
	}
	else
	{
		sparseMatrix<Object>* solution = new sparseMatrix<Object>(
				left.numrows(), right.numcols());

		for (int i = 0; i < solution->numrows(); ++i)
		{
			for (int j = 0; j < solution->numcols(); ++j)
			{

				Object tempValue;
				for (int k = 0; k < left.numrows(); ++k)
				{
					if (k == 0)
					{
						tempValue = (left[i][k]) * (right[k][j]);
					}
					else
						tempValue += (left[i][k]) * (right[k][j]);
				}
				(solution->operator[](i)[j]) = tempValue;
			}
		}
		return *solution;
	}
}

template<typename Object>
sparseMatrix<Object> operator*(double scaler, const sparseMatrix<Object>& m)
{

	sparseMatrix<Object>* solution = new sparseMatrix<Object>(m.numrows(),
			m.numcols());
	for (int i = 0; i < solution->numrows(); ++i)
	{
		for (int j = 0; j < solution->numcols(); ++j)
		{

			(solution->operator[](i)[j]) = scaler * m[i][j];
		}
	}
	return *solution;
}

template<typename Object>
sparseMatrix<Object> operator*(const sparseMatrix<Object>& m, double scaler)
{

	sparseMatrix<Object>* solution = new sparseMatrix<Object>(m.numrows(),
			m.numcols());
	for (int i = 0; i < solution->numrows(); ++i)
	{
		for (int j = 0; j < solution->numcols(); ++j)
		{

			(solution->operator[](i)[j]) = scaler * m[i][j];
		}
	}
	return *solution;
}

template<typename Object>
sparseMatrix<Object> operator+(const sparseMatrix<Object>& left,
		const sparseMatrix<Object>& right)
{

	if (!(left.numrows() == right.numrows())
			|| !(left.numcols() == right.numcols()))
	{
		throw std::logic_error("Matrix size mismatch");
	}
	else
	{

		sparseMatrix<Object>* solution = new sparseMatrix<Object>(
				left.numrows(), right.numcols(), Object());

		for (int i = 0; i < solution->numrows(); ++i)
		{
			for (int j = 0; j < solution->numcols(); ++j)
			{

				solution->operator [](i)[j] = left[i][j] + right[i][j];

			}
		}
		return *solution;
	}
}

template<typename Object>
sparseMatrix<Object> operator-(const sparseMatrix<Object>& left,
		const sparseMatrix<Object>& right)
{

	if (!(left.numrows() == right.numrows())
			|| !(left.numcols() == right.numcols()))
	{
		throw std::logic_error("Matrix size mismatch");
	}
	else
	{

		sparseMatrix<Object>* solution = new sparseMatrix<Object>(
				left.numrows(), right.numcols(), Object());

		for (int i = 0; i < solution->numrows(); ++i)
		{
			for (int j = 0; j < solution->numcols(); ++j)
			{

				solution->operator [](i)[j] = left[i][j] - right[i][j];

			}
		}
		return *solution;
	}
}

template<typename Object>
std::ostream& operator<<(std::ostream& out, const sparseMatrix<Object>& m)
{
	for (int j = 0; j < m.numrows(); ++j)
	{
		for (int i = 0; i < m.numcols(); ++i)
		{
			// if (i > 0) out << ' ';
			out << setprecision(17) << setw(20);
			out << m[j][i];
		}
		out << "\n";
	}
	return out;
}

template <typename Object>
double relError (const sparseMatrix<Object>& left, const sparseMatrix<Object>& right)
{
	typedef sparseMatrix<Object> matrix;

	if (!(left.numrows() == right.numrows())
			|| !(left.numcols() == right.numcols()))
	{
		throw std::logic_error("Matrix size mismatch");
	}

	matrix diff = left - right;
	double diffSumOfSquares = 0.0;

	for (int i = 0; i < diff.numrows(); ++i)
	{
		for (int j = 0; j < diff.numcols(); ++j)
		{
			double diffSquared = pow((diff[i][j]), 2.0);
			diffSumOfSquares += diffSquared;

			/*
			std::cerr << "diff[" << i << "][" << j << "]:" << std::endl;
			std::cerr << diff[i][j] << std::endl;
			std::cerr << "diffSquared: " << diffSquared << std::endl;
			std::cerr << "diffSumOfSquares: " << diffSumOfSquares << std::endl;
			*/
		}
	}

	double err = sqrt(diffSumOfSquares);
	//std::cerr << "relError: " << err << endl;
	return err;

}

#endif

