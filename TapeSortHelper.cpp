#pragma once
#include <iostream>

#include "AbstractTape.cpp"

class Rewinder
{
    AbstractTape &tape;
    int total_move;
    int real_size;
    bool on_the_edge;

public:
    Rewinder(AbstractTape &tape, int real_size) : tape(tape), total_move(0), on_the_edge(false)
    {
        this->real_size = real_size;
    }
    Rewinder(AbstractTape &tape) : Rewinder(tape, tape.GetTapeSize()) {}

    void RecordAndForward(int value)
    {
        tape.Record(value);
        if (total_move == real_size - 1)
        {
            if (!on_the_edge)
            {
                on_the_edge = true;
            }
            else
            {
                std::cerr << "RECORD: Second attempt to move beyond the edge\n";
            }
        }
        else
        {
            total_move++;
            tape.Forward();
        }
    }

    int GetDataAndForward()
    {
        int data = tape.GetData();
        if (total_move == real_size - 1)
        {
            if (!on_the_edge)
            {
                on_the_edge = true;
            }
            else
            {
                std::cerr << "GET DATA: Second attempt to move beyond the edge";
            }
        }
        else
        {
            total_move++;
            tape.Forward();
        }
        return data;
    }

    bool OnTheEdge()
    {
        return on_the_edge;
    }

    void Reset()
    {
        tape.Rewind(-total_move);
        on_the_edge = false;
        total_move = 0;
    }
};