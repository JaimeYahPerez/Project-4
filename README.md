# project 4
## Student Information
Name: Jaime Yah-Perez Student ID: 008856387 git: https://github.com/JaimeYahPerez/Project-4
## Collaboration and Resources
For this project, references to project 3 were utilized heavily and certain files and implementations were reused. And debugging was again,
done with the aid of chatgpt.
<br><br>
Lecture and main project page provided helpful details and implementation steps for the program, and the structure of project 3 aided with development
<br><br>
The construction of main() was done by working off of what I had in project 3, simply making sure to adjust for the needed inputs in this scenario.
As a result, the structure is very similar to what was present in project 3. Although the addition of the helper function was done so as a suggestion from chatgpt due to unxureness of where or how to handle 
construction of a vector of pairs from header
<br><br>
TreeNode and utils were ported over directly from project 3 due to the expectation that it would be needed.
<br><br>
huffmanDecoder was made to be structured similarly to what was present in project 3. Just in this case it was made to work as stated in the project page.
The two needed functions were made and structured as needed, and were implemented in a straightforward manner using what was known.
<br><br>
## Implementation Details
### Huffman Decoder
The structure of the class was kept minimal, as we already have the structure of a huffman tree given from the inputs, we simply need to assemble it in the class using
TreeNode. <br>
readHeaderFile takes a vector string pair called header as its' input, and first destroys the current huffman tree as a safety measure. After resetting root_, a new treeNode with freq 0 is assigned to root_ with key "".
Then, a range for loop is entered which spans the given header pair, and creates the word, code string variables taking in values from header. A temporary TreeNode called curr is made, then a second ranged for loop is made 
to span each bit in the current code. if 0, then we traverse the left subtree, if it is null, then a new node is created and then traversal occurs. If the bit is 1 then a similar operation is done, but for the right subtree.
if the bit is neither value, then an invalid bit is present, and an error is returned. Once the end of the code is reached, it is assumed that the current node must be a leaf, and the word is assigned.
<br>
The decode function takes in the filepath of the code file and the output file as inputs, codeStream and outStream respectively. First, root_ is checked if it is null, if yes the function short circuits with no error.
If the codeStream or outStream are not good, then an error is returned. After the checks are passed, a temporary node called curr is made pointing to root_, alongside a char variable ch.
A while loop is then entered for as long as characters can be pulled from codeStream. If a new line is detected, it is skipped, if a character that isnt 0 or 1, an error is returned. if 0 we enter the left subtree, 
if not then we enter the right subtree. If we enter a nullptr, then an error is returned. A check for a leaf is done by seeing if both subtrees are null, if yes, then the current nodes' key() is written into the output file.
With an extra check being done to make sure writing to the outStream is successful. After writing, the node is reset to the root node. After the while loop, if curr is not set back to the root node, then an error in writing has 
occurred and an error is returned.
<br>
### main
main() works very similarly to what was done in project3, simply adjusting for two file inputs. Two file paths are created for the header and code paths respectively, and are normalized to ensure that the 
input_output directory is found. Then the output path is created. Checks are done for these paths to make sure they are existent and usable, in a manner done similarly in project 3. A helper function is then called 
to read from the header file, and build a vector of string pairs.
<br>
readHeaderFile() is the helper function in question, and it takes inthe header file path and the header vector as inputs. The vector is cleared as a safety check, and the input file path is taken
into ifstream. If the input file stream is not open, then an error is returned. Two string variables are created for word and code resptectively. For every available word, code input in the file stream, a check is done to make sure
the inputs are valid, otherwise an error is returned. If successfully passed, the pair are emplaced back into the vector. After all inputs are checked, then no error is returned.
<br>
Continuing in main(), once the vector is formed, a new huffmanTree is declared from huffmanDecoder called decoder. The vector is passed into this decoder using buildFromHeader(), and is checked for any error.
After successful building, the code file path is opened and checked for usability, along with the output file path. The two are then passed into decoder using decode(), and the result
is handled by this last call.
## Testing and Status
Testing has proved successful and has shown 11 matches after succesful debugging.
