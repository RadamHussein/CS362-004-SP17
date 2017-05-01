Random Testing Quiz 2
Adam Smith
CS 362 - Spring 2017

Development: 

I first started off by probably overcomplicating things. I wanted to know if there
were any limits on how the randomization should work for both inputChar() and inputString().

inputChar() was the easiest to settle on as far as the implementation goes. It simply
generates a random number which corresponds to an index in an array of characters. I 
chose to fill that array with the lowercase alphabet and all the special characters which 
would also be needed to eventually make the error message appear. I then tested the program 
with inputString() returning the string literal 'reset\0'. This caused the error to occur at around 
200 iterations. 

inputString() took some more thought as to what would be appropriate for the randomization. My
first thought was to simply use the random characters returned from inputChar() to build
a random string in inputString(). I attempted this first and have actually left that code 
in inputString() with comments. It is a very good example of how random testing is not ideal
for uncovering edge cases. I let the program run through 200 million iterations and finally shut
it down. In this case, had I not had the source code for the testme() function, I would have 
likely settled on this implementation and passed the test without ever finding the error and without
letting it run through nearly that many iterations. However, this may also have been fine in a 
real world application depending on how it is being used. If this were something like a simple program
to generate randomized passwords, and such a program could be run at least 200 million times without 
an error, this could be completely acceptable. 

Next, in an attempt to actually reach the error message with a random string, I made 2 other 
alterations to inputString(). First, I tried constructing a random string using only the lowercase alphabet. In this situation also I ran the program until I reached 200 million iterations, then stopped. I still was not able to reach the error message. So I made a final alteration which you 
will see is what is currently imlemented. I assigned a char array with only the characters that make up
the 'reset\0' string and still use rand() to get randomly get indices from the char array to build the
string. Finally I was able to reach the error with this pseudorandom string at around 2000 iterations.