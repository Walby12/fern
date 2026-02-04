{
    depfiles = "parser.o: src\\parser.c src\\parser.h src\\comp.h src\\lexer.h src\\vm.h\
",
    depfiles_format = "gcc",
    values = {
        [[C:\msys64\ucrt64\bin\gcc.exe]],
        {
            "-m64",
            "-Wall",
            "-Wextra",
            "-O2"
        }
    },
    files = {
        [[src\parser.c]]
    }
}