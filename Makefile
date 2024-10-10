

run_tests:
	cmake -B build_tests -DTESTING=ON
	cmake --build build_tests
	ctest --test-dir build_tests --output-on-failure
	gcovr -e tests
	gcovr -e tests --branch
