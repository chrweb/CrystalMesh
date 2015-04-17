/* 
 * File:   main.cpp
 * Author: christoph
 *
 * Created on 17. April 2015, 22:35
 */

#include <cstdlib>
#include "test.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    CubeViewUI * view = new CubeViewUI();
    view->show(0, nullptr);
    
    return Fl::run();
}

