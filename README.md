## Abstract-VM
This project introduce to c++ in school 42 franchise Unit Factory.
AbstractVM is a project of creation virtual machine with a few type and some commands.
You can execute program without arguments, so programm gets input from console.
Or give filename or '-'(Console input) as arguments.
See more details in pdf.

### Commands:
* *push* *type* (see below)  -> Push type to stack
* *pop* -> Pop top value from stack
* *assert* *type* -> Assert that top value of stack is equal to the argument
* *print* -> Assert that top value is Int8 and print them as ascii char
* *dump* -> Dump stack
* *add* -> Add two top of the stack, delete them, and push new value
* *sub* -> Subtract two top of the stack, delete them, and push new value
* *mul* -> Multiply two top of the stack, delete them, and push new value
* *div* -> Divise two top of the stack, delete them, and push new value
* *mod* -> Modulo two top of the stack, delete them, and push new value
* *exit* -> Stop execution. Must have instruction

And from me:
* *or* use Binary Or, as add
* *xor* use Binary Xor, as add
* *and* use Binary And, as add

### Types:
* int8($)
* int16($)
* int32($)
* float($)
* double($)

*$*-> string value that represent type

### Example input:
```
./AbstractVM
push int8(16)
          push                int32(16)
    ; Thats a comment      
dump
add
assert int32(32) ; And this too
push float(5.5)
push float(2.1e10)
dump
add
dump
exit
;;
```
Output:
```
Start Stack Dump
Int32   16
Int8    16
End Stack Dump
Start Stack Dump
Float   2.1e10
Float   5.5
Int32   32
End Stack Dump
Start Stack Dump
Float   20999999488.000000
Int32   32
End Stack Dump
```

