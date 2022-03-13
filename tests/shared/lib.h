#pragma once

#if defined(_MSC_VER)
#  if defined(TEST_LIB_DECLARE_EXPORT)
#    define TEST_LIB_EXPORT __declspec(dllexport)
#  elif defined(TEST_LIB_DECLARE_IMPORT)
#    define TEST_LIB_EXPORT __declspec(dllimport)
#  else 
#    define TEST_LIB_EXPORT
#  endif
#else
#  define TEST_LIB_EXPORT
#endif

TEST_LIB_EXPORT void test_lib_function(class LogObject* log_object);
void log_smth();
