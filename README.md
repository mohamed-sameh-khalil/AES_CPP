# AES_CPP
Implementation of AES using C++
To use call the function ```AES(pMSB, pLSB, kMSB, kLSB, choice)``` where:
-```pMSB``` is the most significant 64 bits of plain text
-```pLSB``` is the least significant 64 bits of plain text
-```kMSB``` is the most significant 64 bits of key
-```kLSB``` is the least significant 64 bits of key
-```choice``` is 1 for encryption and 0 for decryption

for testing one can use the console interface provided by the ```main()``` function
to use as part of another program add all the .cpp and .h files to your project and delete the ```main()``` function in AES.cpp
