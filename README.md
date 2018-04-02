# proi-2
Calculator made for university project.

It allows basic operations (+, -, *, /, ^, !) on floating point numbers and some functions (ln, log, exp).

It allows creating variables that can also refer to each other:
```
a=6
> a = 6
b=a^2
> b = 36
a=4
> a = 4
b
> ans = 16
```

You can exit program with `Ctrl + D` or by writing `exit`.

## Building
You can build project with `make all`. You can run it with `make run` or `./calc` after building.

## Tests
You can run tests with `make test`.

## Documentation
You can generate documentation using Doxygen with `doxygen Doxyfile`.

##Cleaning
You can remove files generated by building with `make clean`.
