//
// Created by Punit Soni on 6/25/16.
//

#include "Tester.h"

#include <iostream>

#include "android/log.h"

void hello() {
    std::cout << "Hello World\n";
    __android_log_print(ANDROID_LOG_INFO, "HELLO", "Hello World");
}