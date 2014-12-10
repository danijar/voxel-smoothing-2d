SFML Application Frame
======================

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
