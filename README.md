# Simple stack-oriented VM

## Operations

| operation  | op_code  | description
|---|---|---|
| push a |BIN_PUSH   |  [] -> [`a`] |
| pop |BIN_POP   |  [`a`] -> [] |
| dup |BIN_DUP   | [`a`] -> [`a` `a`] |
| swap |BIN_SWAP   |  [`a` `b`] -> [`b` `a`] |
| add |BIN_ADD   |  [`a` `b`] -> [`(a+b)`] |
| sub |BIN_SUB   |  [`a b`] -> [`(a-b)`] |
| div |BIN_DIV   |  [`a b`] -> [`(a/b)`] |
| mul |BIN_MUL   |  [`a b`] -> [`(a*b)`] |
| eq |BIN_EQUAL   |  [`a b`] -> [`(a==b)`] |
| neq |BIN_NOT_EQUAL   |  [`a b`] -> [`(a!=b)`] |
| gr |BIN_GREATER   |  [`a b`] -> [`(a>b)`] |
| ge |BIN_GREATER_OR_EQUAL   |  [`a b`] -> [`(a<=b)`] |
| lt |BIN_LOWER   |  [`a b`] -> [`(a<b)`] |
| le |BIN_LOWER_OR_EQUAL   |  [`a b`] -> [`(a>=b)`] |
| not |BIN_NOT   |  [`a`] -> [`(!a)`] |
| and |BIN_AND  |  [`a b`] -> [`(a&&b)`] |
| or |BIN_OR  |  [`a b`] -> [`(a\|\|b)`] |
| lb a |BIN_LABEL  |  set label `a`  |
| jmp a |BIN_JMP  |  jump to label `a`  |
| jme a |BIN_JMP_IF  |  jump to label `a` if [`b`] equals `true` |
| jmn a |BIN_JMP_IF_NOT  |  jump to label `a` if [`b`] equals `false` |
| bor |BIN_BITWISE_OR   |  [`a b`] -> [`(a\|b)`] |
| band |BIN_BITWISE_AND   |  [`a b`] -> [`(a&b)`] |
| xor |BIN_BITWISE_XOR   |  [`a b`] -> [`(a xor b)`] |
| bnot |BIN_BITWISE_NOT   |  [`a`] -> [`(!a)`] |
| shl |BIN_LEFT_SHIFT  |  [`a b`] -> [`(a<<b)`] |
| shr |BIN_RIGHT_SHIFT  |  [`a b`] -> [`(a>>b)`] |
| typeof |BIN_TYPEOF |  [`a`] -> [`a type`] |
| sizeof |BIN_SIZEOF  |  [`a`] -> [`a size`] |
| vld |BIN_VLOAD  |  [] -> [`var pool element from given index`] |
| vst |BIN_VSTORE  |  [`a`] -> [] var pool at given index `a`|
| dump |BIN_DUMP  |  [`a`] -> [] print to std out `a`|
| in |BIN_VSTORE  |  [`a(Type)`] -> [`b`] read std in and push on stack result with given type|
| call a| BIN_CALL  |  invoke function with index `a` |
| @arr [length capacity default]| BIN_ARR_NEW  |  allocate new array with `length` and `capacity` with default `value`  |
| s@arr | BIN_ARR_NEW_STACK  |  allocate new array with `length` and `capacity` with default `value` (values from stack in given order) |
| @app | BIN_ARR_APPEND  |  append new element to array to index [`length+1`] if length + 1 <= capacity |
| @st | BIN_ARR_SET | set `array` element with given `index` [`index value array`] -> []|
| @ld | BIN_ARR_GET | get element `a` from `array` with given `index` [`index array`] -> [`a`]|
| eop |BIN_EOP | end of program |

## Byte code assembler

* The file is divided into sections
* Each section has a new line at the end
* File has a new line at the end
* The lines that belong to the section start with a tab
* To get element of a const pool use prefix `$` and element id  (e.g. `$1`)
* To get element of a const var use prefix `*` and element id  (e.g. `*1`)

| section  | description
|---|---|
| ::DATA | contains vm metadata |
| ::CONST_POOL |  definitions of constant elements in program (each element in new line)  |
| ::FUNCTION `name` | operations   |

## ::DATA properties

| name | description
|---|---|
| .stack_size| size of function stack|
| .labels| available number of labels in program|
| .functions| amount of functions in program|
| .const_pool_size| size of constance pool|
| .var_pool_size| size of variable pool|
