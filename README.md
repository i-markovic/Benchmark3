# Benchmark3

## Test "map" concept, find/access wstring element with index ID

Different ways to store <size_t,wstring> key/value and find specific element. Type wstring is choosen because it is common use case and wstring container can influence performace in a measureable way.

Configuration used:
- MSVC 2019, i7 8 Core CPU

Set:
- Configuration Properties->General->C++ Language Standard:
  Preview - Features from the Latest C++ Working Draft (/std:c++latest)

- Measure using the Release configuration, for optimized algorithms

Conclusion:
Fastest way by far is to have single dimension vector<wstring>, resize size, and store values at key (size_t i.e. vector[index]) positions. 
From the standard ways of using containers/agorithms:
```
Test setup:
Containers size 1000000
Number of random element access 100000

test 1a :  14676 msec >> auto it = std::find(V1.begin(), V1.end(), i);
test 1b :  52730 msec >> auto it = ranges::find(V1.begin(), V1.end(), i);
test 1c :  16758 msec >> auto it = std::find(std::execution::par, V1.begin(), V1.end(), i);
test 1d :  52685 msec >> auto it = std::ranges::find(V1, i);
test 2a : 176648 msec >> auto it = find_if(VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });
test 2b : 173839 msec >> auto it = ranges::find_if(VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });
test 2c :  44267 msec >> auto it = std::find_if(std::execution::par,VP1.begin(), VP1.end(), [&](const auto& val) { return val.first == i; });
test 3 :     169 msec >> w = map[i];
test 4 :      10 msec >> w = vector[i];
```

