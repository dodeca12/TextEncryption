# TextEncryption

A C program that implements a simpler version of the Counter (CTR) mode of the Advanced Encryption Standard (AES) 
symmetric encryption algorithm. 


## Compilation Instructions

Compilation can by done by use of the provided makefile - simple type ```make``` into the terminal to compile.

## Running

To run the program, type ```./encryption``` into the terminal

## Usage

Running the created binary gives you two options:
	- To encrypt a message
	- To decrypt a message

Choose your preferred command. Copy and paste the output in the opposite command to get the encrypted/decrypted message.

## Example

Shown below is an example of the program. I will encrypt the message "Please hire me!"

```bash
You may:
  (1) Encrypt a message
  (2) Decrypt a message

  what is your selection: 1

Please enter your plain-text message: 
Please hire me!

80 108 100 96 115 100 33 104 105 114 101 32 109 101 33 -1
```

Now we have the encrypted message "Please hire me!" using the simple CTR mode AES symmetric encryption. To decrypt, run the program again and select option 2, the copy paste the encrypted message to decrypt.

```bash
You may:
  (1) Encrypt a message
  (2) Decrypt a message

  what is your selection: 2

Please enter your encrypted message to be de-crypted:
80 108 100 96 115 100 33 104 105 114 101 32 109 101 33 -1
Please hire me!
```



