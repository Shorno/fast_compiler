# Building the Compiler on Windows (without CLion)

## Required Tools

1. **MinGW-w64 or MSYS2** (for gcc and make)
2. **WinFlexBison** (for flex/bison tools)

## Installation Steps

### Option 1: MSYS2 (Recommended)
1. Download and install MSYS2 from: https://www.msys2.org/
2. Open MSYS2 terminal and run:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-make
   pacman -S mingw-w64-x86_64-flex
   pacman -S mingw-w64-x86_64-bison
   ```
3. Add `C:\msys64\mingw64\bin` to your Windows PATH

### Option 2: Standalone Tools
1. **MinGW-w64**: Download from https://www.mingw-w64.org/
2. **WinFlexBison**: Download from https://github.com/lexxmark/winflexbison/releases
   - Extract to `C:\tools\winflexbison\`
   - Add to PATH or update Makefile paths

## Building the Project

1. Open Command Prompt or PowerShell
2. Navigate to the project directory:
   ```cmd
   cd C:\path\to\fast_compiler
   ```
3. Build the project:
   ```cmd
   make
   ```
4. Test the compiler:
   ```cmd
   make test
   ```
5. Clean build files:
   ```cmd
   make clean
   ```

## Manual Testing

After building, you can test manually:
```cmd
echo "4 + 2" | compiler.exe
echo "x = 10" | compiler.exe
echo "(2 + 3) * 4" | compiler.exe
```

## Troubleshooting

- If `win_flex` or `win_bison` not found, update the FLEX and BISON variables in Makefile
- If `gcc` not found, ensure MinGW is properly installed and in PATH
- If `make` not found, use `mingw32-make` instead
