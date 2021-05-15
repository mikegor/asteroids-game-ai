#include "Matrix.h"

Matrix::Matrix(std::vector<float> vec)
{
	rows = vec.size();
	cols = 1;
	for (int i = 0; i < rows; i++) {
		matrix.push_back(std::vector<float>());
		for (int j = 0; j < cols; j++) {
			matrix[i].push_back(vec[i]);
		}
	}
}

Matrix::Matrix(int r, int c)
{
	rows = r;
	cols = c;
	for (int i = 0; i < rows; i++) {
		matrix.push_back(std::vector<float>());
		for (int j = 0; j < cols; j++) {
			matrix[i].push_back(StaticRandom::getRangeRandomFloat(-1, 1));
		}
	}
}

std::shared_ptr<Matrix> Matrix::get1ColumnMatrix(std::vector<float> vec)
{
	auto n = std::make_shared<Matrix>(Matrix(vec));
	return n;
}

std::shared_ptr<Matrix> Matrix::addBias()
{
	auto n = std::make_shared<Matrix>(rows + 1, 1);
	for (int i = 0; i < rows; i++) {
		n->matrix[i][0] = matrix[i][0];
	}
	n->matrix[rows][0] = 1;
	return n;
}

std::shared_ptr<Matrix> Matrix::activate(){
	auto n = std::make_shared<Matrix>(rows, cols);
	for (int i = 0; i < rows;i++) {
		for (int j = 0; j < cols; j++) {
			n->matrix[i][j] = StaticRandom::getSigmoid(matrix[i][j]);
		}
	}
	return n;
}

std::shared_ptr<Matrix> Matrix::multiplyMatrices(std::shared_ptr<Matrix> n)
{
	auto result = std::make_shared<Matrix>(rows, n->cols);

	if (cols == n->rows) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < n->cols; j++) {
				float sum = 0;
				for (int k = 0; k < cols;k++) {
					sum += matrix[i][k] * n->matrix[k][j];
				}
				result->matrix[i][j] = sum;
			}
		}
	}
	return result;
}

std::vector<float> Matrix::toVec()
{
	std::vector<float> vec(rows * cols);
	for (int i = 0; i < rows;i++) {
		for (int j = 0; j < cols; j++) {
			vec[i * cols + j] = matrix[i][j];
		}
	}
	return vec;
}

std::shared_ptr<Matrix> Matrix::clone()
{
	auto c = std::make_shared<Matrix>(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c->matrix[i][j] = matrix[i][j];
		}
	}
	return c;
}

void Matrix::mutate(float mutationRate)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			float r = StaticRandom::getRangeRandomFloat(0, 1);
			if (r < mutationRate) {
				matrix[i][j] = StaticRandom::getRandomFloatNormalDist(0, 0.5, -1, 1);
			}
		}
	}
}

std::shared_ptr<Matrix> Matrix::crossover(std::shared_ptr<Matrix> pair)
{
	auto child = std::make_shared<Matrix>(Matrix(rows, cols));
	int randRow = StaticRandom::getRangeRandomInt(0, rows - 1);
	int randCol = StaticRandom::getRangeRandomInt(0, cols - 1);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if ((i < randRow) || (i == randRow && j <= randCol))
				child->matrix[i][j] = matrix[i][j];
			else
				child->matrix[i][j] = pair->matrix[i][j];
		}
	}
	return child;
}
