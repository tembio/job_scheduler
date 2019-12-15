JOB SCHEDULER

-- Generation --

1. In the root directory create a folder "build"
2. cd into the build directory
3. Run:
         cmake ..

-- Compilation --

Once the project has been generated, run:

        cmake --build .

And the executable "job_scheduler" will be generated.

TESTS

By default tests are not generated. 
To enable test generation run:

        cmake .. -DGENERATE_TESTS=TRUE

An internet connection is needed to generate the project with tests.
During the generation process test dependencies (GTests and GMocks) will be downloaded.

To run the tests:

        ctest
        