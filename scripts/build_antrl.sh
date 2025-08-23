#!/bin/bash
java -jar external/antlr-4.13.1-complete.jar src/antlr/Stc.g4 -visitor -Dlanguage=Cpp
