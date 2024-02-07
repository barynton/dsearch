#!/bin/bash
lcov -c -d build_Debug -o build_Debug/coverage.info --include \*/core/\*
genhtml build_Debug/coverage.info -o build_Debug/coverage_report