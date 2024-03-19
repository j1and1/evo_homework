#include "ts_queue.hpp"

#include "generator.hpp"
#include "processor.hpp"
#include "agregator.hpp"

#include <vector>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    TSQueue<std::vector<int>> data_list;
    TSQueue<float> calculation_results;

    Generator data_generator(data_list);
    Processor data_processor(data_list, calculation_results);
    Agregator data_aggregator(calculation_results);

    // wait until the generator is finished
    data_generator.wait_until_finished();
    data_processor.wait_until_finished();
    data_aggregator.wait_until_finished();

    return 0;
}