Example .txt blocks can be changed and transformed to .bin blocks with simple command:
xxd -r -p input.txt output.bin

There are 4 .txt files containing blocks 5017, 5018, 5019 and 5020 and also their .bin representation.
File 5017_to_5020.txt and corresponding .bin file contain all four blocks together.
File 5017_to_5020_corrupted.txt is corrupted in block 5019 in hash of previous block so this blockchain should not be valid.

