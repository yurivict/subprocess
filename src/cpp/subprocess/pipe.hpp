#pragma once

#include "basic_types.hpp"

namespace subprocess {
    /*  You might be wondering why the C-like API. I played around with a more
        C++ like API but it gets hairy quite fast trying to support all the
        possible use-cases. My opinion is to simply roll a RAII class for
        when you need it that is specific to your needs. 1, or a set of RAII
        classes is too complex.
    */
    struct PipePair {
        PipeHandle input    = kBadPipeValue;
        PipeHandle output   = kBadPipeValue;

        explicit operator bool() const noexcept {
            return input != output;
        }
    };

    /** Closes a pipe handle.
        @param handle   The handle to close.
        @returns true on success
    */
    bool pipe_close(PipeHandle handle);
    PipePair pipe_create(bool inheritable = true);
    bool pipe_set_no_inherit(PipeHandle handle);

    /**
        @returns    -1 on error. if 0 it could be the end, or perhaps wait for
                    more data.
    */
    ssize_t pipe_read(PipeHandle, void* buffer, size_t size);
    /**
        @returns    -1 on error. if 0 it could be full, or perhaps wait for
                    more data.
    */
    ssize_t pipe_write(PipeHandle, const void* buffer, size_t size);

    /** Read contents of handle until no more data is available.

        If the pipe is non-blocking this will end prematurely.

        @return all data read from pipe as a string object. This works fine
                with binary data.
    */
    std::string pipe_read_all(PipeHandle handle);
}