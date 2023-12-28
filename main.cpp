#include <iostream>
#include <fstream>
#include <filesystem>
#include <list>

#include "BasicTape.cpp"
#include "TapeSort.cpp"
int main()
{
   
    std::filesystem::create_directory("tmp");
    std::ifstream timings_config_data("timings_config.txt");
    TimingsConfig timings_config;

    std::string _s;
    std::getline(timings_config_data, _s);
    if (!_s.starts_with("#"))
    {
        std::cout << "config in 'timings_config.txt' have wrong format, skipping";
    }
    else
    {
        timings_config_data >>
            timings_config.read_latency >>
            timings_config.record_latency >>
            timings_config.move_one_latency >>
            timings_config.rewind_latency >>
            timings_config.is_rewind_latency_multiplier;
    }

    

    BasicTape tape_in(timings_config);
  
    std::string filename_in, filename_out;

    std::cin >> filename_in;  //  = "input.txt";
    std::cin >> filename_out; // = "output.txt";

    tape_in.ReadFromFile(filename_in);
    BasicTape tape_out(tape_in.GetTapeSize(), timings_config);
    
    
    TapeSort sort_tape((AbstractTape &)tape_in, (AbstractTape &)tape_out);

    tape_out.WriteToFile(filename_out);
    std::cout << "Timings:\n\tRead: " << tape_out.timings.read << "\n\tRecord: " << tape_out.timings.record;
    std::cout << "\n\tMove one: " << tape_out.timings.move_one << "\n\tRewind: " << tape_out.timings.rewind << "\n";
    return 0;
}