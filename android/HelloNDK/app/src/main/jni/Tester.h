//
// Created by Punit Soni on 6/25/16.
//

#ifndef HELLO_NDK_TESTER_H
#define HELLO_NDK_TESTER_H

#if 0
class Tester {

public:
    static void hello()
    {
        std::cout << "Hello World.\n";
    }

};
#endif

#ifdef __cplusplus
extern "C" {
#endif

void hello();

#ifdef __cplusplus
}
#endif


#endif //HELLO_NDK_TESTER_H
