// https://zhaowuluo.wordpress.com/2011/01/02/cplusplus_threading_matrix_multiplication/
#pragma once
#include <boost\thread\thread.hpp>
#include <boost\bind.hpp>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

#define SIZE 10
// Multiply matrix of SIZE by SIZE of type T
class Matrix
{
// Function
public:
	Matrix(int num)
	{
		init(A);
		init(B);
		num_thread = num;
	}

	void multiply(const int& slice)
	{
		/*
		Each thread works on its own separate slice only
		Ther is no need for synchronization among threads
		*/
		const int from = (slice * SIZE) / num_thread;
		const int to = ((slice + 1)*SIZE) / num_thread;
		io_mutex.lock();
		cout << "Thread Id = " << boost::this_thread::get_id() << " is computing slice" << " from row " << from << " to column" << to - 1 << "." << endl;
		io_mutex.unlock();
		for (int i = from; i < to; i++)
		{
			for (size_t j = 0; j < SIZE; j++)
			{
				// Initialize matrix C
				C[i][j] = 0;
				for (size_t k = 0; k < SIZE; k++)
				{
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		io_mutex.lock();
		cout << "Finished slice: " << slice << endl;
		io_mutex.unlock();
	}

	void output()
	{
		print_matrix(A);
		cout << endl << " * " << endl;
		print_matrix(B);
		cout << endl << " = " << endl;
		print_matrix(C);
	}

	void print_matrix(double M[SIZE][SIZE])
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			cout << endl << "     ";
			for (size_t j = 0; j < SIZE; j++)
			{
				cout << M[i][j] << " ";
			}
			cout << endl << "      ";
		}
	}


public:
	int num_thread;
	double A[SIZE][SIZE];
	double B[SIZE][SIZE];
	double C[SIZE][SIZE];
	boost::mutex io_mutex;

private:
	void init(double M[SIZE][SIZE])
	{
		int value = 0;
		for (size_t i = 0; i < SIZE; i++)
		{
			for (size_t j = 0; j < SIZE; j++)
			{
				M[i][j] = value++;
			}
		}
	}
};

int main()
{
	cout << "In this machine, we have " << boost::thread::hardware_concurrency() << " processors" << endl;
	cout << "We will use all" << endl;
	int m_num_thread = boost::thread::hardware_concurrency();
	cout << "Main thread Id: " << boost::this_thread::get_id() << endl;

	cout << "Start to process with matrix type double with size = 10*10" << endl;
	Matrix m_matrix(m_num_thread);
	boost::thread_group m_thread_groups;

	for (size_t i = 0; i < m_num_thread; i++)
	{
		m_thread_groups.create_thread(
			boost::bind(&Matrix::multiply, 
						boost::ref(m_matrix), 
						i));
	}


	m_thread_groups.join_all();
	m_matrix.output();
	return 0;
}


