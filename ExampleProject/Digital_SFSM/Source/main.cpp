#include <iostream>

#include <ExampleObject.h>

#include <string>

int main(int /*argc*/, char* /*argv*/[]) {

    // Create Example Object
    ExampleObject obj;
    obj.Oncreate();

    //while (obj.enabled_) {
    //    std::cout << "------------------" << std::endl;
    //    obj.Update();
    //    std::cout << "------------------" << std::endl;
    //}

    int max_count = 6;
    for (int count = 0; count < max_count; ++count) {
        std::cout << "------------------" << std::endl;
        std::cout << "Count: "<< std::to_string(count) << std::endl;
        obj.Update();
    }

    system("PAUSE");

    return 0;
}