#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <stdexcept>
#include <cmath>
#include <memory>

using namespace std;

template<typename Object>
class denseMatrix
{
public:

	denseMatrix(int rows, int cols);
	denseMatrix(const vector<vector<Object>> & v);

	denseMatrix();
	denseMatrix(int rows, int cols, const Object&);
	denseMatrix(const vector<vector<Object>> &, const Object&);
	denseMatrix(const vector<Object> &, const Object&);
	denseMatrix(const denseMatrix<Object>&);
	~denseMatrix()
	{
		array.clear();
	}

	bool operator==(const denseMatrix<Object>&) const;
	bool operator!=(const denseMatrix<Object>&) const;

	denseMatrix<Object>& operator=(const denseMatrix<Object>&);

	void eye();
	void eye(int, int);
	denseMatrix<Object>& augment(const denseMatrix<Object>&);
	denseMatrix<Object>& swapRows(int, int);
	denseMatrix<Object>& swapRows(std::vector<Object>&, int);
	denseMatrix<Object>& multiplyRow(int, double);
	denseMatrix<Object>& addRows(int, int, int);
	denseMatrix<Object>& addRows(vector<Object>&, int, int);

	typedef typename std::vector<std::vector<Object>>::iterator arrayIterator;
	typedef typename std::vector<std::vector<Object>>::const_iterator const_arrayIterator;

	const vector<Object> & operator[](int row) const
	{
		return array.at(row);
	}
	vector<Object> & operator[](int row)
	{
		return array.at(row);
	}

	int numrows() const
	{
		// std::cerr << array.size() << endl;
		return array.size();
	}

	int numcols() const
	{
		int nCols = 0;
		// std::cerr << (numrows() ? array.at(0).size() : 0) << endl;
		// return (numrows() ? array.at(0).size() : 0);
		if (numrows() == 0)
		{
			nCols = 0;
		}
		else
		{
			const_arrayIterator row = array.begin();
			nCols = row->size();
		}
		return nCols;
	}

private:
	vector<vector<Object>> array;
};

struct MatrixSizeException: public exception
{
	const char * what() const throw ()
	{
		return "Matrix size mismatch";
	}
};

template<typename Object>
denseMatrix<Object>::denseMatrix()
{
}

template<typename Object>
denseMatrix<Object>::denseMatrix(int rows, int cols) :
		array(rows)
{
//	for (auto & thisRow : array)
//		thisRow.resize(cols);

//	typedef denseMatrix<Object>::iterator arrayIterator;

	for (arrayIterator row = array.begin(); row != array.end(); ++row)
	{
		row->resize(cols);
	}
}

template<typename Object>
denseMatrix<Object>::denseMatrix(int rows, int cols, const Object& defaultValue) :
		array(rows)
{
//	typedef denseMatrix<Object>::iterator arrayIterator;

	for (arrayIterator row = array.begin(); row != array.end(); ++row)
	{
		//*row = vector<Object>(cols, defaultValue);
		row->assign(cols, defaultValue);
	}
	//for (auto & thisRow : array)
	//	thisRow.assign(cols, defaultValue);
}

template<typename Object>
denseMatrix<Object>::denseMatrix(const vector<vector<Object>> & v) :
		array
		{ v }
{
}

template<typename Object>
denseMatrix<Object>::denseMatrix(const vector<vector<Object>> & v,
		const Object& defaultValue) :
		array
		{ v }
{
}

template<typename Object>
denseMatrix<Object>::denseMatrix(const vector<Object> & v,
		const Object& defaultValue)
{
	if (array.size() != 0)
	{
		array.clear();
	}
	array.push_back(v);
}

template<typename Object>
denseMatrix<Object>::denseMatrix(const denseMatrix<Object>& m) :
		array
		{ m.array }
{

}

/*  Not yet supported
 denseMatrix( initializer_list<vector<Object>> lst ) : array( lst.size( ) )
 {
 int i = 0;
 for( auto & v : lst )
 array[ i++ ] = std::move( v );
 }
 */

/*  Not yet supported
 denseMatrix( vector<vector<Object>> && v ) : array{ std::move( v ) }
 { }
 */

//Overloaded operators
//Comparison operators
template<typename Object>
bool denseMatrix<Object>::operator==(const denseMatrix<Object>& m) const
{
	if (numcols() != m.numcols() || numrows() != m.numrows())
		return false;

	const denseMatrix<Object>& self = *this;

	for (int j = 0; j < m.numrows(); ++j)
		for (int i = 0; i < m.numcols(); ++i)
		{
			if (self[j][i] != m[j][i])
				return false;
		}
	return true;
}

template<typename Object>
bool denseMatrix<Object>::operator!=(const denseMatrix<Object>& m) const
{
	return (!(*this == m));
}

template<typename Object>
denseMatrix<Object>& denseMatrix<Object>::operator=(
		const denseMatrix<Object>& right)
{
	if (!(*this == right))
	{
		array.clear();
		array = right.array;
	}
	return *this;
}

template<typename Object>
void denseMatrix<Object>::eye()
{

	denseMatrix<Object>& self = *this;
	if (array.size() != array.at(0).size())
	{
		throw std::logic_error("Matrix size mismatch");
	}
	else
	{
		array.clear();
		for (int i = 0; i < array.size(); ++i)
		{
			self[i][i] = 1.0;
		}
	}
}

template<typename Object>
void denseMatrix<Object>::eye(int rows, int cols)
{

	denseMatrix<Object>& self = *this;
	array.clear();
	array.resize(rows);

	for (int i = 0; i < array.size(); ++i)
	{
		array.at(i).assign(cols, 0.0);
		self[i][i] = 1.0;
	}
}

/*
 * Creates an augmented matrix with matrix parameter as input. numRows must
 * be equal in both matrices and right.numcols() must == 1.
 */
template<typename Object>
denseMatrix<Object>& denseMatrix<Object>::augment(const denseMatrix<Object>& right)
{
	if (!(array.size() == right.numrows()) || !(right.numcols() == 1))
	{
		throw std::logic_error("Matrix size mismatch");
	}

	for (int i = 0; i < array.size(); ++i)
	{
		array.at(i).push_back(right[i][0]);
	}

	return *this;

}

template<typename Object>
denseMatrix<Object>& denseMatrix<Object>::swapRows(int rowOne, int rowTwo)
{
	if ((rowOne < 0) || (rowOne > array.size()) ||
	(rowTwo < 0) || (rowTwo > array.size()))
	{
		throw std::out_of_range("parameters given are outside of matrix boundaries");
	}

	array.at(rowOne).swap(array.at(rowTwo));
	return *this;
}

template<typename Object>
denseMatrix<Object>& denseMatrix<Object>::swapRows(std::vector<Object>& swapRow, int rowOne)
{
	if ((rowOne < 0) || (rowOne > array.size()))
	{
		throw std::out_of_range("parameters given are outside of matrix boundaries");
	}

	std::vector<Object>& row1 = array.at(rowOne);

	row1.swap(swapRow);
	return *this;
}

template<typename Object>
denseMatrix<Object>& denseMatrix<Object>::multiplyRow(int rowNum, double scaler)
{
	if ((rowNum < 0) || (rowNum > array.size()))
	{
		throw std::out_of_range("parameters given are outside of matrix boundaries");
	}

	vector <Object>& row = array.at(rowNum);
	for (int i = 0; i < row.size(); ++i)
	{
		row[i] = scaler * row[i];
	}
	return *this;
}

template<typename Object>
denseMatrix<Object>& denseMatrix<Object>::addRows(int rowOne, int rowTwo, int destinationRow)
{
	if ((rowOne < 0) || (rowOne > array.size()) ||
	(rowTwo < 0) || (rowTwo > array.size()) ||
	(destinationRow < 0) || (destinationRow > array.size()))
	{
		throw std::out_of_range("parameters given are outside of matrix boundaries");
	}

	vector <Object>& row1 = array.at(rowOne);
	vector <Object>& row2 = array.at(rowTwo);
	vector <Object>& writeRow = array.at(destinationRow);

	for (int i = 0; i < row1.size(); ++i)
	{
		Object temp = row1[i] + row2[i];
		writeRow[i] = temp;
	}
	return *this;
}

template<typename Object>
denseMatrix<Object>& denseMatrix<Object>::addRows(vector<Object>& rowOne, int rowTwo, int destinationRow)
{
	if ((rowTwo < 0) || (rowTwo > array.size()) ||
	(destinationRow < 0) || (destinationRow > array.size()))
	{
		throw std::out_of_range("parameters given are outside of matrix boundaries");
	}

	vector <Object>& row2 = array.at(rowTwo);
	vector <Object>& writeRow = array.at(destinationRow);

	for (int i = 0; i < row2.size(); ++i)
	{
		Object temp = rowOne[i] + row2[i];
		writeRow[i] = temp;
	}
	return *this;
}

template<typename Object>
denseMatrix<Object> operator*(const denseMatrix<Object>& left,
		const denseMatrix<Object>& right)
{

	if (left.numcols() != right.numrows())
	{
		throw std::logic_error("Matrix size mismatch");
	}
	else
	{
		std::unique_ptr<denseMatrix<Object> > solution(
				new denseMatrix<Object>(left.numcols(), right.numcols()));

		for (int i = 0; i < left.numrows(); ++i)
		{
			for (int j = 0; j < right.numcols(); ++j)
			{

				Object tempValue;
				for (int k = 0; k < right.numrows(); ++k)
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
denseMatrix<Object> operator*(double scaler, const denseMatrix<Object>& m)
{

	std::unique_ptr<denseMatrix<Object> > solution(
			new denseMatrix<Object>(m.numcols(), m.numcols()));
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
denseMatrix<Object> operator*(const denseMatrix<Object>& m, double scaler)
{

	std::unique_ptr<denseMatrix<Object> > solution(
			new denseMatrix<Object>(m.numcols(), m.numcols()));
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
denseMatrix<Object> operator+(const denseMatrix<Object>& left,
		const denseMatrix<Object>& right)
{

	if (!(left.numrows() == right.numrows())
			|| !(left.numcols() == right.numcols()))
	{
		throw std::logic_error("Matrix size mismatch");
	}
	else
	{

		std::unique_ptr<denseMatrix<Object> > solution(
				new denseMatrix<Object>(left.numcols(), right.numcols()));

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
denseMatrix<Object> operator-(const denseMatrix<Object>& left,
		const denseMatrix<Object>& right)
{

	if (!(left.numrows() == right.numrows())
			|| !(left.numcols() == right.numcols()))
	{
		throw std::logic_error("Matrix size mismatch");
	}
	else
	{

		std::unique_ptr<denseMatrix<Object> > solution(
				new denseMatrix<Object>(left.numcols(), right.numcols()));

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
std::ostream& operator<<(std::ostream& out, const denseMatrix<Object>& m)
{
	for (int j = 0; j < m.numrows(); ++j)
	{
		for (int i = 0; i < m.numcols(); ++i)
		{
			if (i > 0)
				out << ' ';
			out << setprecision(17) << setw(20);
			out << m[j][i];
		}
		out << "\n";
	}
	return out;
}

template<typename Object>
double relError(const denseMatrix<Object>& left,
		const denseMatrix<Object>& right)
{

	if (!(left.numrows() == right.numrows())
			|| !(left.numcols() == right.numcols()))
	{
		throw std::logic_error("Matrix size mismatch");
	}

	denseMatrix<Object> diff = left - right;
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

