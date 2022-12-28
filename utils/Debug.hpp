#pragma once
#include <iostream>

using namespace std;

#define DEBUG_DUMP_VAR(var) (cout<<#var<<": "<<(var)<<endl)
#define DEBUG_DUMP_CALL() (cout<<__PRETTY_FUNCTION__<<" was called"<<endl)