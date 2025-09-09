# Language Fundamentals

> **Tip:**  
> This guide explains the stack-based behavior and type system of the language, with visual examples to help you understand how operations affect the stack.

## Stack Operations

The stack is the main data structure for all computations. Each stack item is 64 bits wide and carries type information. Operations follow a LIFO (Last In, First Out) order: the last value pushed is the first to be popped.

> **Notation:**  
> `[before] -> [after]` shows the stack contents before and after an operation.  
> For example:  
> ```
> Before: []
> After:  [a]
> ```
> This means the stack was empty, and after the operation, it contains the value `a`.

---

## Stack Operations and Visual Examples

> **Info:**  
> The following diagrams and explanations show how each stack operation works and how the stack changes.

### Push Operation
- **Description:** Adds a value `a` to the top of the stack.
- **Example:**  
  ```
  10
  ```
  Stack after: `[10]`
- **Picture:**  
  ![push](img/push.svg)

### Duplication (`dup`)
- **Description:** Duplicates the top value of the stack.
- **Example:**  
  Before: `[10]`  
  After: `[10, 10]`
- **Picture:**  
  ![dup](img/dup.svg)

### Pop Operation (`pop`)
- **Description:** Removes the top element from the stack.
- **Example:**  
  Before: `[10, 20]`  
  After: `[20]`
- **Picture:**  
  ![pop](img/pop.svg)

### Swap Operation (`swap`)
- **Description:** Swaps the top two elements of the stack.
- **Example:**  
  Before: `[10, 20]`  
  After: `[20, 10]`
- **Picture:**  
  ![swap](img/swap.svg)

### Rotate Operation (`rot`)
- **Description:** Rotates the top three elements, moving the top element to the bottom.
- **Example:**  
  Before: `[10, 20, 30]`  
  After: `[30, 20, 10]`
- **Picture:**  
  ![rot](img/rot.svg)

### Over Operation (`over`)
- **Description:** Duplicates the second top element, placing it on top.
- **Example:**  
  Before: `[10, 20]`  
  After: `[10, 20, 20]`
- **Picture:**  
  ![over](img/over.svg)
---

## Type System

> **Info:**  
> The language supports several types, each mapped to a C type.

| **Type**    | **Equivalent C Type** | **Description**                       |
|-------------|:---------------------:|---------------------------------------|
| `I64`       | `long`                | 64-bit integer                        |
| `F64`       | `double`              | 64-bit floating-point number          |
| `I8`        | `char`                | 8-bit character                       |
| `Type`      | `long`                | Type tag or size                      |
| `Ref`       | `void*`               | Reference to variable                 |
| `Str`       | `String`              | Sequence of characters                |

---

## Number Types

### Integer Types

> **Note:**  
> There are two integer types: `I8` (character) and `I64` (64-bit integer).

#### `I8`
- Format: `'x'` (single ASCII character)
- Size: 8 bits
- Usage: Characters or byte-sized numbers

#### `I64`
- Format: Decimal (`123`), Hex (`0x1A`), Octal (`0o17`), Binary (`0b1010`)
- Size: 64 bits
- Usage: General-purpose integer

| **Format**      | **Example** | **Description**                    |
|-----------------|------------|------------------------------------|
| Decimal         | `123`      | Base-10 integer                    |
| Hexadecimal     | `0x1A`     | Base-16, prefixed with `0x`        |
| Octal           | `0o17`     | Base-8, prefixed with `0o`         |
| Binary          | `0b1010`   | Base-2, prefixed with `0b`         |

#### Floating-Point Types

- Format: Includes decimal point or exponent (`1.23`, `4.56e-2`)
- Type: `F64` (like C `double`)

---

## Stack Persistence Modifier

> **Tip:**  
> Use the `!` suffix to keep values on the stack after an operation.

**Example:**
```stc
5 4 !+
```
Before `!+`:
```
[5 4]
```
After `!+`:
```
[5 4 9]
```

![add](img/add.svg)

---

## Variables

> **Info:**  
> Variables are dynamically typed and mutable. Use `:=` to assign.

### Assign By Expression

Assign a value from the stack:
```stack
10 a :=
```
This pops `10` from the stack and assigns it to `a`.

### Assign By Reference

Assign by referencing a variable:
```stack
0 a :=

5 &a :=
```
Here, `5` is pushed, then assigned to the reference `a`.

> **Note:**  
> The variable must be defined before using reference assignment.

---

## Array And String Operators

> **Tip:**  
> Arrays can store elements of any type. Use `[]` to create arrays.

### Visualizing Array Creation

```
Code: [1 2 3]
Stack after:
+-----------+
| [1 2 3]   |
+-----------+
```

### Visualizing Array Set

```
Code: [10 20 30] arr :=

Stack before: 99 arr 0 set
+----+-----------+----+
| 99 | [10 20 30]| 0  |
+----+-----------+----+

After set:
+--------------+
| [99 20 30]   |
+--------------+
```

### Visualizing String Indexing

```
Code: "foo" 1 at

Stack before:
+-----+---+
|foo  | 1 |
+-----+---+

After at:
+---+
| o |
+---+
```

---

### Creating an Array

To define an array:
```stack
[1 2 3]
```
Pushes `[1, 2, 3]` onto the stack.

To set array capacity:
```stack
[0 0 0]c5
```
Creates `[0, 0, 0]` with capacity 5.

> **Warning:**  
> Arrays use reference copying. Copying an array creates a reference, not a deep copy. This may change in future versions.

---

### Setting Array Values

The `set` operator updates an array at a specific index.

- Stack order: value, array, index (top)
- Updates array in place

**Example:**
```stack
[10 20 30] arr :=

99 arr 0 set
```
Before: `[99, [10, 20, 30], 0]`  
After: `[[99, 20, 30]]`

---

### `len` Operator

> **Info:**  
> `len` returns the length of a string or array (not capacity).

**Example:**
```stack
"foo" len print
```
Output: `3`

---

### `at` Operator

> **Info:**  
> `at` retrieves the value at a given index from a string or array.

**Example:**
```stack
"foo" 1 at print
```
Output: `o`

---

> **Summary:**  
> The language uses a stack-based model. Operations manipulate the stack, and types are flexible. Arrays and strings are first-class, and visual diagrams above show how values move and change.
