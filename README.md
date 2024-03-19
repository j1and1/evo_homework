
## To build the code you should do the following:

1. Create a build directory `mkdir build && cd build`
2. Run cmake command to generate project files `cmake ..`
3. Run cmake build to compile the project files `cmake --build . --config Release`
4. And if all went well, then you can run the executable by calling `./evo_homework`

## How to modify ranges for random number generator

In generator.cpp file edit the following lines to affect the time spent on generating data, sleeping, and the size of the vector.
```
std::uniform_int_distribution<int> time_distr(1, 10000); // Runtime distr between 1 and 10s
std::uniform_int_distribution<int> sleep_distr(1000, 2.5e7); // sleep distr between 0.001ms and 2.5ms
std::uniform_int_distribution<int> vector_distr(2, 20); // element values and size
```

since prints sometimes affect the performance of the code then sleep can be commented out in generator.cpp file


## Excuses :D

Since the task didn't specify if the data should be processed or not when generator stops (after the time limit) the app just consumes all the generated data and calculates result and then exits the program.