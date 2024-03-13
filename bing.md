To read bits from a file in **C**, you'll need to work with bytes as the smallest granularity. Here are some approaches you can take:

1. **Reading One Byte at a Time and Extracting Bits**:

   - Use `fread` to read one byte at a time from the file.
   - Then, use bitwise operators (`>>` and `&`) to extract individual bits from the byte.
   - For example, to read 12 bits, you can read one byte and then extract the relevant bits using shifts and masks.
   - Here's a basic example:

     ```c
     #include <stdio.h>

     int main() {
         FILE *file = fopen("your_file.bin", "rb");
         if (!file) {
             perror("Error opening file");
             return 1;
         }

         unsigned char byte;
         while (fread(&byte, 1, 1, file) == 1) {
             // Extract bits from 'byte' here
             // Example: Read the first 12 bits
             unsigned int bits = (byte >> 4) & 0xFFF;
             printf("Read bits: %u\n", bits);
         }

         fclose(file);
         return 0;
     }
     ```

   - Adjust the bit extraction logic according to your specific requirements.

2. **Custom Bit-Level I/O**:

   - If you need more fine-grained control, consider implementing custom bit-level I/O functions.
   - Create a structure to keep track of the current bit position within a byte.
   - Read bytes from the file and manipulate the bit cursor accordingly.
   - Here's a high-level idea (you'll need to implement the details):

     ```c
     struct BitCursor {
         FILE *file;
         unsigned char buffer;
         int bitPos;
     };

     // Initialize the bit cursor
     struct BitCursor cursor = {file, 0, 0};

     // Read 12 bits
     unsigned int ReadBits(struct BitCursor *cursor, int numBits) {
         unsigned int result = 0;
         for (int i = 0; i < numBits; ++i) {
             if (cursor->bitPos == 0) {
                 if (fread(&cursor->buffer, 1, 1, cursor->file) != 1) {
                     // Handle end of file
                     break;
                 }
                 cursor->bitPos = 8;
             }
             result <<= 1;
             result |= (cursor->buffer >> (--cursor->bitPos)) & 1;
         }
         return result;
     }

     // Usage:
     unsigned int bits = ReadBits(&cursor, 12);
     printf("Read bits: %u\n", bits);
     ```

   - Adapt this concept to your specific needs.

Remember that reading individual bits directly into an array isn't straightforward due to the lack of a bit data type. You'll need to work with bytes and extract the relevant bits as needed. Good luck with your bit-level file reading! 📄🔍

Origem: conversa com o Bing, 11/03/2024
(1) c - Reading a binary file bit by bit - Stack Overflow. https://stackoverflow.com/questions/11680248/reading-a-binary-file-bit-by-bit.
(2) Read a File in C - geekbits.io. https://www.geekbits.io/read-a-file-in-c/.
(3) ifstream - Read file by bits c++ - Stack Overflow. https://stackoverflow.com/questions/22390641/read-file-by-bits-c.
(4) How to read/write arbitrary bits in C/C++ - Stack Overflow. https://stackoverflow.com/questions/11815894/how-to-read-write-arbitrary-bits-in-c-c.
(5) Reading/writing single bits from/to FILE - Code Review Stack Exchange. https://codereview.stackexchange.com/questions/185608/reading-writing-single-bits-from-to-file.
(6) undefined. http://www.cprogramming.com/tutorial/bitwise_operators.html.
