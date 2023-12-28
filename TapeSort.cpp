#pragma once
#include <iostream>

#include "BasicTape.cpp"
#include "AbstractTape.cpp"
#include "TapeSortHelper.cpp"
#include <cassert>

class TapeSort
{
private:
    BasicTape left_tape;
    BasicTape right_tape;

    void split(AbstractTape &_tape, int count)
    {
        int l_count;
        int r_count;

        if (count > 1)
        {
            l_count = count / 2;
            r_count = count - l_count;
            split(_tape, l_count);

            _tape.Rewind(l_count);
            split(_tape, r_count);

            _tape.Rewind(-l_count);
            merge(_tape, l_count, r_count);
        }

        return;
    };

    void merge(AbstractTape &output_tape, int l_count, int r_count)
    {

        Rewinder out_r(output_tape, l_count + r_count), left_r((AbstractTape &)left_tape, l_count), right_r((AbstractTape &)right_tape, r_count);
        if (left_tape.GetCurrentPosition() != 0)
        {
            left_tape.Rewind(-left_tape.GetCurrentPosition() + 1);
        }
        while (!left_r.OnTheEdge())
        {
            left_r.RecordAndForward(out_r.GetDataAndForward());
        }
        if (right_tape.GetCurrentPosition() != 0)
        {
            right_tape.Rewind(-right_tape.GetCurrentPosition() + 1);
        }
        while (!right_r.OnTheEdge())
        {
            right_r.RecordAndForward(out_r.GetDataAndForward());
        }
        if (!out_r.OnTheEdge())
        {
            std::cerr << "_out was not fully read";
        }

        out_r.Reset();
        left_r.Reset();
        right_r.Reset();

        while (!left_r.OnTheEdge() && !right_r.OnTheEdge())
        {
            if (left_tape.GetData() < right_tape.GetData())
            {
                out_r.RecordAndForward(left_r.GetDataAndForward());
            }
            else
            {
                out_r.RecordAndForward(right_r.GetDataAndForward());
            }
        }
        while (!left_r.OnTheEdge())
        {
            out_r.RecordAndForward(left_r.GetDataAndForward());
        }
        while (!right_r.OnTheEdge())
        {
            out_r.RecordAndForward(right_r.GetDataAndForward());
        }

        out_r.Reset();
        left_r.Reset();
        right_r.Reset();
    }

    ;

    void SortTape(AbstractTape &input_tape, AbstractTape &output_tape)
    {
        Rewinder inp_r(input_tape), out_r(output_tape, input_tape.GetTapeSize());
        while (!inp_r.OnTheEdge())
        {
            out_r.RecordAndForward(inp_r.GetDataAndForward());
        }

        inp_r.Reset();
        out_r.Reset();

        split(output_tape, output_tape.GetTapeSize());
    };

public:
    TapeSort(AbstractTape &input_tape,
             AbstractTape &output_tape)
    {
        if (output_tape.GetTapeSize() >= input_tape.GetTapeSize())
        {
            size_t l_half = output_tape.GetTapeSize() / 2;
            size_t r_half = output_tape.GetTapeSize() - l_half;

            left_tape = BasicTape(l_half);
            right_tape = BasicTape(r_half);

            SortTape(input_tape, output_tape);
        }
        else
        {
            std::cerr << "ERROR! tapes sizes are different";
        }
    }
};