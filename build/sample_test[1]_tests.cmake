add_test([=[AdditionTest.HandlesPositiveInput]=]  /home/soumya/googletest-env/myproject/build/sample_test [==[--gtest_filter=AdditionTest.HandlesPositiveInput]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AdditionTest.HandlesPositiveInput]=]  PROPERTIES WORKING_DIRECTORY /home/soumya/googletest-env/myproject/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  sample_test_TESTS AdditionTest.HandlesPositiveInput)
