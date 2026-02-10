# fern

A lightweight, high-performance interpreted programming language built from scratch in C.

> [!WARNING]  
> **Early Development:** fern is an experimental project under active development. Expect breaking changes and incomplete features.

## Features

-  **Simple syntax** - Easy to learn and read
-  **Fast compilation** - Compiles to intermediate representation (IR)


## Getting Started

### Prerequisites

- **C Compiler:** GCC or Clang
- **Build System:** [Xmake](https://xmake.io/)


### Build Modes
```bash
# Debug build 
xmake debug

# Release build 
xmake release
```

## Architecture

fern uses a two-stage compilation process:

1. **Compiler** (`src/parser.c`, `src/lexer.c`) - Parses source code and generates IR
2. **VM** (`src/vm.c`) - Interprets the IR and executes the program

## Contributing

Contributions are welcome! This is a learning project, so feel free to experiment and suggest improvements.

## License

[MIT]
