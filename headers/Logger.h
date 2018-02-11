/*
 * The MIT License
 *
 * Copyright 2017 yacinehaoues.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   Logger.h
 * Author: yacinehaoues
 *
 * Created on November 11, 2017, 1:48 PM
 */

#ifndef LOGGER_H
#define LOGGER_H


/* #include<boost/log/trivial.hpp>*/
#include <Types.h>
#include <iostream>

namespace API {
enum CLogLevel {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERR = 4,
    FATAL = 5
};

class Logger {

public :
   

    Logger(CLogLevel l) :close(false), lvl(l) {
        operator << ("[" + getHeader(l) + "] ");
    };

    virtual ~Logger() {
        if (close) {
            std::cout << std::endl;
        }
        close = false;
    };
    template<class T> inline Logger &operator<<(const T &msg) {
         std::cout << msg;
         close = true;
         return *this;
    }

private:
   

    inline String getHeader(CLogLevel l) {
        String label;
        switch (l) {
            case TRACE: label = "TRACE"; break;
            case DEBUG: label = "DEBUG"; break;
            case INFO:  label = "INFO "; break;
            case WARN:  label = "WARN "; break;
            case ERR: label = "ERROR"; break;
            case FATAL: label = "FATAL"; break;
        }
        return label;
    }
    bool close;
    CLogLevel lvl;
};

#define Trace   API::Logger(API::TRACE)
#define Debug   API::Logger(API::DEBUG)
#define Info    API::Logger(API::INFO)
#define Warn    API::Logger(API::WARN)
#define Error   API::Logger(API::ERR)
#define Fatal   API::Logger(API::FATAL)

}
#endif /* LOGGER_H */

