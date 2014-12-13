Voxel Smoothing 2D
==================

This is the implementation of an algorithm for smoothing voxel structures, I
designed. Even though this is a 3D problem, solving it in 2D is a first step.
This application displays a grid where you can add or remove blocks with the
mouse. The smoothed shape outline is rendered ontop.

![Screenshot](screenshot/2014-12-12.png?raw=true)

Instructions
------------

To generate build files, run `cmake` with these command line options. Only the
first option is required if you stick with the default configuration and have
Git globally available.

Option                                     | Usage
------------------------------------------ | -----------------------------------------------
`-G"<generator>"`                          | E.g. `Visual Studio 12` or `Unix Makefiles`.
`-DGIT_EXECUTABLE:FILEPATH=<git>`          | Path to `git.exe` if not globally available.
`-DCMAKE_BUILD_TYPE:STRING="<variant>"`    | `Debug` or `Release`, defaults to release.
`-DBUILD_SHARED_LIBS:BOOL=<linkage>`       | What type to build, `TRUE` or `FALSE`.
`-DUSE_STATIC_STD_LIBS:BOOL=<std-linkage>` | Advanced option, defaults to opposite of above.

To build the project, it's recommended that you use your selected toolchain.
It's also possible to use `cmake --build . --config <variant>`.

When using Visual Studio, you have to manually set the startup project to your
own one, since it's `ALL_BUILD` by default. Moreover, make sure to select the
build type you chose above when running the application.

In case you want to clean up build files later on, run `git clean -xffd` from
the repository root.
