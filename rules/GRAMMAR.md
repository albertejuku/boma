### FORMAL GRAMMAR

- variables
- expressions
- control flow  

variableDeclaration ::= const var <identifier> : <type> = <value> ; | var <identifier> : <type> = <value>; | var <identifier> : <type>;  
identifier ::= [a-zA-Z_0-9]
type ::= int | char | boolean | byte | string | float | array | list | set | map | json | object
value ::= intLiteral | floatLiteral | stringLiteral | byteLiteral | boolLiteral | object
intLiteral ::= [0-9] 
floatLiteral ::= [0.0...]
stringLiteral ::= ["abc..."]
characters ::= character | { character }
character ::= letter | digit | specialCharacter
letter ::= "a" | "b" | "c" | ... | "z" | "A" | "B" | "C" | ... | "Z"
digit ::= "0" | "1" | "2" | ... | "9"
specialCharacter ::= any special character allowed in a string literal
