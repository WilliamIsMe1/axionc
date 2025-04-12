# axionc
---
Axion is a bytecode compiled language run on a VM for portability, made to merge the FP and the OOP paradigms in a new way that allows things like native partial function application, closures, first-class functions, special constructors, plenty of sugared types that can be extended, and a list of primitive types such as:
- int
- float
- long
- double
- short
- hfloat
- char
- byte
- fraction
- array (the only primitive generic type)
- string (an array of characters with special sugaring)

# Format
Fields, Methods, and Classes will all be named in PascalCase

Local variables will be in camelCase

Constants will be in SCREAMING_SNAKE_CASE

# Syntax features
This will be a C-like with Swift features, Python ecosystems, and Java's type safety and portability, along with reified generics

As for syntax, you have a number of operators at your disposal. For arithmetic, you have `+`, `-`, `*`, `**`, `/`, `++`. `--`. and :. You will recognize most of them except for the `:` and the `**` operators. `:` is the ratio operator, and it is not very binding, as it is meant to create fractions, which are a primitive type that uses integers as it's numerator and denominator. `**` is from python, and it is just an exponentiation operator.

Some example code will be listed below. Most of the code is not final, and will be used to show off syntax.
```
import axion.util
import axion.io

/** This is a simple filter stream that only allows
 * lowercase letters to pass through.
 * @author William
 */
class LowercaseFilterStream extends FilterStream {
    @Override
    public byte Read() {
        while true {
            char c = (char) super.Read()
            if IsUpper(c) {
                continue
            } else {
                return (byte) c
            }
        }
    }
}

string SomeRandomReverseFunction(string input) {
    return String.valueOf(input)
        .ToStream()
        .Reverse()
        .ToString()
}

lambda<int>(int, int) Add = (a, b) => {
    return a + b
}

lambda<int>(int) Add5 = bind (?, 5) to Add

class GenericThing<T extends number> {
    T value

    public GenericThing(T in) {
        value = in
    }

    public AddToSelf(T in) {
        value += in
    }
}

void Main() {
    SystemOut.PrintLn("Hello, Axion World!")
    SystemOut.Print("That reversed being: ")
    SystemOut.PrintLn(SomeRandomReverseFunction("Hello, Axion World!"))
    SystemOut.PrintLn("There is nothing more for now, so bye!")
}

```