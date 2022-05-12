# A simple scripting language

# Motivation
I worked on an interpreter for arithmetic expressions a long while back.
This helped me on a project two friends and I created for the deerhacks 2022. We worked on
a language called pa!n which is deliberately hard to use for several reasons. The
original interpreter was written in Python.

This project is dedicated to continue developing the interpreter in C++ and removing the
elements that made it pretty much unusable. Taking away the pain lead to the name
no-pain.


# Overview
The interpreter is written in C++, built with Bazel and tested using the Googletest testing framework.
I have not set the syntax in stone yet, but there examples can be found in test-scripts.
