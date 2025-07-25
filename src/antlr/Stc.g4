
grammar Stc;

prog          : (functionDef | struct)+ EOF;

functionDef   : 'fun' ID arguments? block; 


type           : (SIMPLE_TYPE) | ID | SIMPLE_TYPE '<'(type | ID) '>';


statement       : newStructAssign
                | newOperator
                | varReference
                | varAssign
                | arrayIndex
                | arrayNew
                | array
                | operation
                | stackOperation
                | push
                | identifier
                | functionDef
                | ifBlock
                | repeatBlock

                ;

block         : '{' (statement)+'}';

newStructAssign   : NEW ':' ID ID ASSIGN_OPERATOR;

newOperator   : NEW ':' ID;

struct        : STRUCT_DEFINITION ID structBody;

structElement : ID varType;
structBody    : '{' structElement+ '}';





ifBlock       : 'if' block (elseBlock)?;
elseBlock     : 'else' block;
repeatBlock   : 'repeat' arguments? block;


arguments : '(' argument+ ')' ;

operation     : STACK_PREVENTION? operaor;
operaor       : LOGIC_OPERATOR 
              | ARITHMETIC_OPERATOR 
              | BUILD_IN_OPERATOR
              | ASSIGN_OPERATOR
              ;
stackOperation: 'dup' 
              | 'rot' 
              | 'swap' 
              | 'pop'
              | 'over'
              ;
push          : SIGNED_NUMBER
              | NUMBER
              | SIGNED_FLOAT 
              | FLOAT 
              | SIGNED_FLOAT_E 
              | FLOAT_E 
              | BIN_NUMBER 
              | HEX_NUMBER 
              | CHAR 
              | STRING 
              | BOOL 
              | SIMPLE_TYPE
              ;
arrayElement  : SIGNED_NUMBER 
              | NUMBER
              | SIGNED_FLOAT 
              | FLOAT 
              | SIGNED_FLOAT_E 
              | FLOAT_E 
              | BIN_NUMBER 
              | HEX_NUMBER 
              | CHAR 
              | STRING 
              | BOOL 
              | SIMPLE_TYPE
              | arrayIndex
              | varIdentifier
              | array
              ;

arrayBase : varIdentifier;
arrayIndexShift: (NUMBER|varIdentifier );
arrayIndex:  arrayBase '@' arrayIndexShift;


capacity: 'c:' NUMBER;
array: ARRAY_OPEN (arrayElement)+ ARRAY_CLOSE capacity?;
arrayDescriber: ARRAY_OPEN NUMBER ARRAY_CLOSE;
arrayNew: ARRAY_OPERATOR arrayDescriber arrayDescriber?;


argument    : ID varType?;
varAssign   : (varAssignIdentifier|arrayIndex|identifier) ASSIGN_OPERATOR;
varAssignIdentifier : varIdentifier  varType;
varType: '<'type'>';
varReference: REFERENCE_OPERATOR varIdentifier;
varIdentifier: ID ((':' ID)+)?;
identifier: (STACK_PREVENTION)? ID ((':' ID)+)?;


NEW: 'new';
STRUCT_DEFINITION: 'struct';
STACK_PREVENTION: '!';

NUMBER: DIGIT+; // Unsigned number
SIGNED_NUMBER: [+-] DIGIT+; // Signed number
FLOAT: DIGIT+ '.' DIGIT+; // Unsigned float
SIGNED_FLOAT: [+-] DIGIT+ '.' DIGIT+; // Signed float
FLOAT_E: DIGIT+ ('.' DIGIT+)? [eE] [+-]? DIGIT+; // Scientific notation
SIGNED_FLOAT_E: [+-] DIGIT+ ('.' DIGIT+)? [eE] [+-]? DIGIT+; // Signed scientific notation

fragment DIGIT: [0-9];

BIN_NUMBER: '0' [bB] [01]+;
HEX_NUMBER:  '0' [xX] [0-9a-fA-F]+;
STRING: '"' (ESC | ~["\\])* '"';     
CHAR: '\'' (ESC | ~['\\]) '\'';
BOOL: 'true' | 'false';
fragment ESC: '\\' [btnfr"'\\];
SIMPLE_TYPE        : 'I64'
                   | 'I8' 
                   | 'Str' 
                   | 'F64' 
                   | 'Arr'
                   | 'Bool'
                   | 'Struct'
                   ;
LOGIC_OPERATOR     : '<='
                   | '<'
                   | '>'
                   | '>='
                   | '!='
                   | '=='
                   | 'and' 
                   | 'or' 
                   | 'not'
                   ;
ARITHMETIC_OPERATOR: '+' 
                   | '-'
                   | '*' 
                   | '/' 
                   | '%' 
                   ;  
ASSIGN_OPERATOR    : ':=';
REFERENCE_OPERATOR : '&';
BUILD_IN_OPERATOR  : 'typeof'
                   | 'len'
                   | 'call'
                   | 'copy'
                   ;


ARRAY_OPEN: '[';
ARRAY_CLOSE: ']';
ARRAY_OPERATOR: 'arr';

AT: '@';

ID: [a-zA-Z_][a-zA-Z_0-9]*;  





WS: [ \t\r\n]+ -> skip;  // Ignore whitespace