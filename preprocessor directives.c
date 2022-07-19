#define E 1111

#undef E
//E is not defined for any value after using #undef, so it holds no value in the above example.
  
  #ifdef M
//execute code if true i.e., the macro is defined
  
  #ifndef:
//It works exactly the opposite of ifdef. Meaning that it executes the code if the macro is undefined.

#if condition 
// execute code if true i.e. condition satisfied

#if condition 
// execute code if true else pass it to #else

#else 
// execute code if “if condition” is false

#if condition 
// execute code if true else pass it to #elif

#elif expression 
// execute code if true else pass it to #else

#else 
//else code

#pragma
//Pragma is used to issue some special commands to compiler.

