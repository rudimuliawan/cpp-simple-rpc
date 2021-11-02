//
// Created by rudi on 02/11/21.
//

#ifndef SIMPLE_BUFFER_HPP
#define SIMPLE_BUFFER_HPP

#include <cstdlib>

#define SENTINEL_VALUE 0xFFFFFFFF

namespace SimpleRPC {
class SimpleBuffer {
public:
    /*	\brief Construct a Simple Buffer Client.
     */
    SimpleBuffer();

    /*	\brief Destructor
     */
    ~SimpleBuffer();

    void Serialize(char *data, size_t nbytes);
    void Deserialize(char *dest, size_t size);
    void Skip(size_t skipSize);
    void SeekToZero();
    void Clear();

private:
    char *start_;
    std::size_t size_;
    std::size_t next_;

    static constexpr size_t SIMPLE_BUFFER_DEFAULT_SIZE = 100;
};
}

#endif // SIMPLE_BUFFER_HPP
