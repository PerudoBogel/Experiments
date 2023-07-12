#pragma once
#include <iostream>

using namespace std;

#define DEBUG_DUMP_VAR(var) (cout<<__FILE__<<":"<<__LINE__<<": "<<#var<<": "<<(var)<<endl)
#define DEBUG_DUMP_VAR_COMMENT(var, comment) (cout<<__FILE__<<":"<<__LINE__<<": "<<#var<<": "<<(var)<<". Comment: "<<(comment)<<endl)

#define DEBUG_DUMP_CALL() (cout<<__FILE__<<":"<<__LINE__<<": "<<__PRETTY_FUNCTION__<<" was called"<<endl)
#define DEBUG_DUMP_CALL_COMMENT(comment) (cout<<__FILE__<<":"<<__LINE__<<": "<<__PRETTY_FUNCTION__<<" was called"<<". Comment: "<<(comment)<<endl)