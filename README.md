- ## High-level aSseMbly Language

> programming language i made for fun.

### Simple Swap Program
```
lab .swap
    adr temp &0
    adr a &1
    adr b &2
    
    pop b
    pop a
    
    set temp *a
    set a *b
    set b *temp
    
    psh *a
    psh *b
    
    ret

lab .catch
    prl "Runtime Error !"

lab .main
    adr a &0
    adr b &1
    
    prl "Input Number 1: "
    
    inp a
    try 1 catch
    int a *a
    
    prl "Input Number 2 : "
    
    inp b
    try 1 catch
    int b *b
    
    prt *a
    prt "    "
    prt *b
    prt "\n"
    
    psh *b
    psh *a
    cal swap
    pop a
    pop b
    
    prt *a
    prt "    "
    prt *b
    prt "\n"
    
    ret
    
```

### Labels
- define label with "lab" keyword.
- the content must be indented 4 spaces after the label keyword.
```
lab .[labelName]
  [command1]
  [command2]
  [command3]
  [...]
```

### Comments
- write comments with // and /* */.

### Commands
- `adr [addressName] &[address]` -> define address name
- `pop [address]` -> pop value from global stack and copy it to given address
- `psh [value]` -> push value to global stack
- `set [address] [value]` -> set address with given value
- `inc [address] [value]` -> increase value of given address
- `dec [address] [value]` -> decrease value of given address
- `jmp [index]` -> jump to (currentIndex + givenIndex)
- `ret` -> end label and return to last call index
- `prt [value]` -> print given value
- `prl [value]` -> println given value
- `try [index] [labelName]` -> (use it with "int", "flt", "str") try to execute (currentIndex + givenIndex) and if it returns error, then jump to given label
- `int [address] [value]` -> int(value) and copy it to given address
- `str [address] [value]` -> str(value) and copy it to given address
- `flt [address] [value]` -> float(value) and copy it to given address
- `inp [address]` -> get string input from user
- `cal [labelName]` -> call given label
- `ext [code]` -> exit program with given code.
- `add [address] [left] [right]` -> add left and right and copy it to given address
- `sub [address] [left] [right]` -> subtract left and right and copy it to given address
- `mul [address] [left] [right]` -> multiply left and right and copy it to given address
- `div [address] [left] [right]` -> divide left to right and copy it to given address
- `mod [address] [left] [right]` -> modulo left to right and copy it to given address
- `pow [address] [left] [right]` -> power left and right and copy it to given address
- `grt [leftAddress] [rightAddress] [index]` -> jump to given index if left > right
- `goe [leftAddress] [rightAddress] [index]` -> jump to given index if left >= right
- `les [leftAddress] [rightAddress] [index]` -> jump to given index if left < right
- `loe [leftAddress] [rightAddress] [index]` -> jump to given index if left <= right
- `eql [leftAddress] [rightAddress] [index]` -> jump to given index if left == right
- `neq [leftAddress] [rightAddress] [index]` -> jump to given index if left != right
- `lad [leftAddress] [rightAddress] [index]` -> jump to given index if left && right
- `lor [leftAddress] [rightAddress] [index]` -> jump to given index if left || right

  
