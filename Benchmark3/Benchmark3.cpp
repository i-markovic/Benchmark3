#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <random>
#include <ranges>
#include <execution>
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;

using namespace std;
using ID = size_t;

int main()
{
	// containers sizes to test "map" concept "find wstring element with index ID"
	const size_t sz = 1000000;

	// vector index is ID
	vector<wstring> V0(sz);

	// V1 for IDs, V2 for wstrings
	vector<ID> V1(sz);
	vector<wstring> V2(sz);

	// vector with pairs <ID,wstring>
	vector < pair<ID, wstring>> VP1(sz);

	// map with pairs <ID,wstring>
	map < ID, wstring> MP;

	// Create and fill conatiners, wstring is name of ID
	for (auto i = 0; i < sz; ++i)
	{
		wstring w = to_wstring(i);
		V0[i] = w;
		V1[i] = i; V2[i] = w;
		VP1[i] = pair(i, w);
		MP[i] = w;
	}

	// Random IDs for test
	const size_t szI = 100000;//number of test accesses

	vector<ID> vIDs(szI);
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, sz - 1); // distribution range
	for (auto i = 0; i < szI; ++i)
	{
		vIDs[i] = dist6(rng);
	}

	// Tests
	cout << "Test setup:" << endl <<
		"Containers size " << sz << endl <<
		"Number of random element access " << szI << endl << endl;

	{
		wstring w;
		auto startTime = high_resolution_clock::now();
		for (auto i : vIDs)
		{
			auto it = std::find(V1.begin(), V1.end(), i);
			w = V2.at(it - V1.begin());
		}
		auto endTime = high_resolution_clock::now();
		auto ft = duration_cast<duration<double, milli>>(endTime - startTime).count();
		cout << "test 1a : " << ft << " msec >> auto it = std::find(V1.begin(), V1.end(), i);" << endl;
	}

	{
		wstring w;
		auto startTime = high_resolution_clock::now();
		for (auto i : vIDs)
		{
			auto it = ranges::find(V1.begin(), V1.end(), i);
			w = V2.at(it - V1.begin());
		}
		auto endTime = high_resolution_clock::now();
		auto ft = duration_cast<duration<double, milli>>(endTime - startTime).count();
		cout << "test 1b : " << ft << " msec >> auto it = ranges::find(V1.begin(), V1.end(), i);" << endl;
	}

	{
		wstring w;
		auto startTime = high_resolution_clock::now();
		for (auto i : vIDs)
		{
			auto it = std::find(std::execution::par, V1.begin(), V1.end(), i);
			w = V2.at(it - V1.begin());
		}
		auto endTime = high_resolution_clock::now();
		auto ft = duration_cast<duration<double, milli>>(endTime - startTime).count();
		cout << "test 1c : " << ft << " msec >> auto it = std::find(std::execution::par, V1.begin(), V1.end(), i);" << endl;
	}

	{
		wstring w;
		auto startTime = high_resolution_clock::now();
		for (auto i : vIDs)
		{
			auto it = std::ranges::find(V1, i);
			w = V2.at(it - V1.begin());
		}
		auto endTime = high_resolution_clock::now();
		auto ft = duration_cast<duration<double, milli>>(endTime - startTime).count();
		cout << "test 1d : " << ft << " msec >> auto it = std::ranges::find(V1, i);" << endl;
	}

	{
		wstring w;
		auto startTime = high_resolution_clock::now();
		for (auto i : vIDs)
		{
			auto it = std::find_if(VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });
			w = it->second;
		}
		auto endTime = high_resolution_clock::now();
		auto ft = duration_cast<duration<double, milli>>(endTime - startTime).count();
		cout << "test 2a : " << ft << " msec >> auto it = find_if(VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });" << endl;
	}

	{
		wstring w;
		auto startTime = high_resolution_clock::now();
		for (auto i : vIDs)
		{
			auto it = ranges::find_if(VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });
			w = it->second;
		}
		auto endTime = high_resolution_clock::now();
		auto ft = duration_cast<duration<double, milli>>(endTime - startTime).count();
		cout << "test 2b : " << ft << " msec >> auto it = ranges::find_if(VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });" << endl;
	}



	{
		wstring w;
		auto startTime = high_resolution_clock::now();
		for (auto i : vIDs)
		{
			auto it = std::find_if(std::execution::par, VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });
			w = it->second;
		}
		auto endTime = high_resolution_clock::now();
		auto ft = duration_cast<duration<double, milli>>(endTime - startTime).count();
		cout << "test 2c : " << ft << " msec >> auto it = std::find_if(std::execution::par,VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });" << endl;
	}

	{
		wstring w;
		auto startTime = high_resolution_clock::now();
		for (auto i : vIDs)
		{
			w = MP[i];
		}
		auto endTime = high_resolution_clock::now();
		auto ft = duration_cast<duration<double, milli>>(endTime - startTime).count();
		cout << "test 3 : " << ft << " msec >>   w = map[i];" << endl;
	}

	{
		wstring w;
		auto startTime = high_resolution_clock::now();
		for (auto i : vIDs)
		{
			w = V0[i];
		}
		auto endTime = high_resolution_clock::now();
		auto ft = duration_cast<duration<double, milli>>(endTime - startTime).count();
		cout << "test 4 : " << ft << " msec >>   w = vector[i];" << endl;
	}


	std::cout << "End";
}

// Test setup :
// Containers size 1000000
// Number of random element access 100000
// 
// test 1a :  11982 msec >> auto it = std::find(V1.begin(), V1.end(), i);
// test 1b :  11938 msec >> auto it = ranges::find(V1.begin(), V1.end(), i);
// test 1c :   5459 msec >> auto it = std::find(std::execution::par, V1.begin(), V1.end(), i);
// test 1d :  11753 msec >> auto it = std::ranges::find(V1, i);
// test 2a :  97127 msec >> auto it = find_if(VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });
// test 2b : 101575 msec >> auto it = ranges::find_if(VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });
// test 2c :  50948 msec >> auto it = std::find_if(std::execution::par, VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });
// test 3 :     180 msec >> w = map[i];
// test 4 :      10 msec >> w = vector[i];
// End