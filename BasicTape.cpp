#pragma once
#include <fstream>
#include <vector>

#include "AbstractTape.cpp"

struct TimingsConfig
{
    int read_latency = 0;
    int record_latency = 0;
    int move_one_latency = 0;
    int rewind_latency = 0;
    bool is_rewind_latency_multiplier = false;
};

struct Timings
{
    int read = 0;
    int record = 0;
    int move_one = 0;
    int rewind = 0;

    int Total()
    {
        return read + record + move_one + rewind;
    }
};

class BasicTape : AbstractTape
{
private:
    std::vector<int> tape_data;
    size_t current_position;
    size_t tape_size;
    TimingsConfig timings_config;

public:
    Timings timings;

    BasicTape(size_t size, TimingsConfig timings_config = TimingsConfig()) : tape_data(size),
                                                                             current_position(0),
                                                                             tape_size(size),
                                                                             timings_config(timings_config){};
    BasicTape(TimingsConfig timings_config = TimingsConfig()) : BasicTape(0, timings_config){};

    size_t GetTapeSize()
    {
        return this->tape_size;
    };

    size_t GetCurrentPosition()
    {
        return this->current_position;
    }

    void ReadFromFile(std::string path)
    {
        std::ifstream infile(path);
        int number;

        while (infile >> number)
        {
            this->tape_data.push_back(number);
        }

        this->tape_size = tape_data.size();
    };

    void WriteToFile(std::string path)
    {
        std::ofstream outfile(path);

        for (auto number : tape_data)
        {
            outfile << number;
            outfile << " ";
        }
    }

    void Record(int number)
    {
        tape_data[current_position] = number;
        timings.record += timings_config.record_latency;
    };

    int GetData()
    {
        timings.read += timings_config.read_latency;
        return tape_data[current_position];
    };

    void Rewind(int steps)
    {

        if (timings_config.is_rewind_latency_multiplier)
        {
            timings.rewind += timings_config.rewind_latency * steps;
        }
        else
        {
            timings.rewind += timings_config.rewind_latency;
        }

        if (this->tape_size > current_position + steps)
        {
            this->current_position += steps;
        }
        else
        {
            std::cerr << "ERROR! Tape size is too small";
            current_position = std::max(std::min(current_position + steps, tape_size), (const size_t)0);
        }
    };

    void Forward()
    {
        timings.move_one += timings_config.move_one_latency;
        if (current_position != tape_size - 1)
        {
            current_position++;
        }
    };
    void Backward()
    {
        timings.move_one += timings_config.move_one_latency;
        if (current_position != 0)
        {
            current_position--;
        }
    };
};