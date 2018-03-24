//g++ -std=c++11 main.cpp -lpthread -Wall
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

using namespace std;

void populate_nums(vector<long long> &vec, size_t N)
{
    for(size_t i = 0; i < N; ++i) {
	vec.push_back(i + 1);
    }
}

void sum_thread(const vector<long long> &data, size_t a, size_t b, long long *ans)
{
    long long tmp = 0;
    for (size_t i = a; i < b; ++i) {
	tmp += data[i];
    }
    cout <<"a="<<a<<" b="<<b<<" ans="<<tmp<<endl;
    *ans = tmp;
}

int main()
{
    size_t N, M;
    cout << "Enter the size of the array:";
    cin >> N;
    cout << "Enter the number of threads:";
    cin >> M;
    size_t partition_sz = N / M;
    if (0 == partition_sz) {
	cout << "M cannot be smaller than N!" <<endl;
	exit(0);
    }

    vector<long long> data;
    data.reserve(N);
    populate_nums(data, N);

    vector<long long> partial_result(M, 0);
    vector<thread> thread_vec;
    for (size_t i = 0; i < partial_result.size(); ++i) {
	size_t begin = i * partition_sz;
	size_t end = i == partial_result.size()-1 ?  data.size() : begin + partition_sz;
	thread_vec.push_back(thread(sum_thread, data, begin, end, &partial_result[i]));
    }

    for (size_t i = 0; i < thread_vec.size(); ++i) {
	thread_vec[i].join();
    }

    long long ans;
    sum_thread(partial_result, 0, partial_result.size(), &ans);

    cout << "Sum = " << ans << endl;

}
