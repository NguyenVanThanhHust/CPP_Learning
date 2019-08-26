#include <iostream>
#include <thread>
#include <memory>
#include <mutex>
#include <functional>
#include <chrono>
#include <vector>

using namespace std;

#define SIZE 10

template<typename T>
class Matrix
{
public:
	Matrix(int num)
	{
		init(A);
		init(B);
		num_thread = num;
	}

	void multiply(const int& slice)
	{
		const int from = (slice * SIZE) / num_thread;
		const int to = ((slice + 1)*SIZE) / num_thread;
		m_mutex.lock();
		cout << "Thread Id = " << std::this_thread::get_id << " is computing slice from " << from << " to " << to << endl;
		m_mutex.unlock();
		for (size_t i = from; i < to; i++)
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
		m_mutex.lock();
		cout << "Finished slice: " << slice << endl;
		m_mutex.unlock();
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
private:
	void init(T M[SIZE][SIZE])
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (size_t j = 0; j < SIZE; j++)
			{
				M[i][j] = 0;
			}
		}
	}
private:
	int num_thread;
	T A[SIZE][SIZE];
	T B[SIZE][SIZE];
	T C[SIZE][SIZE];
	std::mutex m_mutex;

};

int main()
{
	cout << "In this machine, we have " << std::thread::hardware_concurrency() << " processors" << endl;
	cout << "We will use all" << endl;
	int m_num_thread = std::thread::hardware_concurrency();
	cout << "Main thread Id: " << std::this_thread::get_id() << endl;
	cout << "Start to process with matrix type double with size = 10*10" << endl;
	Matrix<double> m_matrix(m_num_thread);
	std::vector<std::thread> vector_thread;
	for (size_t i = 0; i < m_num_thread; i++)
	{
		vector_thread.emplace_back(std::bind(&Matrix<double>::multiply,i));
	}

	for (auto& thread:vector_thread)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
    return 0;
}
