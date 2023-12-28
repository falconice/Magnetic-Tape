#pragma once

class AbstractTape
{

public:
    virtual size_t GetTapeSize() = 0;

    virtual size_t GetCurrentPosition() = 0;

    virtual void Record(int number) = 0;

    virtual int GetData() = 0;

    virtual void Rewind(int steps) = 0;

    virtual void Forward() = 0;

    virtual void Backward() = 0;

    virtual ~AbstractTape(){};
};
