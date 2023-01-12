# CppEmbedGenerator:

An application to convert a given file into a header file with a byte array that can be embedded into your application at compile time.

# Compile:

```
g++ -std=c++17 cpp-embed-gen.cpp -o cpp-embed-gen
```

# Use:

```
cpp-embed-gen [file_to_embed] [output_file_name]
```

You can optionally change the namespace by adding the desired name onto the end of the command like so:

```
cpp-embed-gen [file_to_embed] [output_file_name] [namespace]
```
