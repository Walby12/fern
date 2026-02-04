{
    depfiles_format = "gcc",
    depfiles = "argparse.o: src\\argparse.c src\\argparse.h\
",
    files = {
        [[src\argparse.c]]
    },
    values = {
        [[C:\msys64\ucrt64\bin\gcc.exe]],
        {
            "-m64",
            "-Wall",
            "-Wextra",
            "-O2"
        }
    }
}