# StackCode

A simple stack-oriented programming language.
## Data Types
- `Number` - 8 bytes integer
- `Bool` - `true` or `false` value
- `String` - text sequence
- `Array` - TO-DO
- `Type` - TO-DO

## Stack manipulation operations
| Stack | Operation| Stack    |
| :---:   | :---: | :---: |
|  a  | pop   |      |
|  a  | dup   |  a a    |
|  a b  | swap   |  b a    |
|  a b c | over   |  c b a  |

## Operations

### add (+)
```
a b +
```
Basic type addition rules:
- A Type + A Type = A Type
- A Type + B Type == B Type + A Type
- Bool + Number = Number
- Number + String = String 
- String + Bool = String 

Examples:

```
10 10 + put
```
result: 20
```
10 "abc" + put
```
result: 10abc
```
10 true + put
```
result: 11
```
"abc" false + put
```
result: abcfalse

### sub (-)
```
a b -
```
Basic type substract rules:
- A Type - A Type = A Type
- A Type - B Type == B Type - A Type

Examples:

```
10 4 - put
```
result: 6
```
10 false - put
```
result: 10

### mul (*)
```
a b *
```
Basic type multiplication rules:
- A Type * A Type = A Type
- A Type * B Type == B Type * A Type

Examples:

```
4 3 * put
```
result: 12
```
8 true * put
```
result: 8
```
"abc" 2 * put
```
result: abcabc

## Code structures

### if structure
```
[condition] if [code] end
```
### while structure
```
begin [condition] while [code] end
```
### iter structure
```
[begin: Number] [end: Number]  [step: Number] iter [code] end
```
do `[code]` and push counter to the stack `(end - begin)/step` times