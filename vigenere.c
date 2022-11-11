/* vigenere.c
   CSC 111 - Fall 2021 - Assignment 6


   B. Bird - 10/23/2021
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* index_to_character(index)
   Given an index, which MUST be in the range 0 through 25 (inclusive), return
   the corresponding lowercase character of the English alphabet, where
   the index 0 refers to 'a' and the index 25 refers to 'z'.

   If the index is not in the range 0 through 25, the behavior of this function
   is undefined.

   Parameters: index (integer)
   Return value (char): The character of the English alphabet with the
                        provided index.
*/
char index_to_character(int index){
    return 'a' + index;
}


/* character_to_index(ch)
   Given a lowercase English letter, return the index of that character in the
   English alphabet, where 'a' has the index 0 and 'z' has the index 25.

   If the character is not a lowercase letter, the behavior of this function
   is undefined.

   Parameters: ch (character)
   Return value (int): The index of the provided character in the English
                       alphabet.
*/
int character_to_index(char ch){
    return ch - 'a';
}


int main(){

    char key[100];
    char message[100];
    char encrypted[100];
    char decrypted[100];
    
    FILE* input_file = fopen("input.txt", "r");

    fgets(key, 100, input_file);
    fgets(message, 100, input_file);
    
    //deletes the \n in the string key and message
    for(int i = 0; i < strlen(key); i++){
        if(key[i] == '\n'){
            key[i] = '\0';
        }
    }
    
    for(int i = 0; i < strlen(message); i++){
        if(message[i] == '\n'){
            message[i] = '\0';
        }
    }
    
    //errors
    //Unable to open file
    if(input_file == NULL){
        printf("Error: Unable to open input file.\n");
        fclose(input_file);
        return 1;
    }
    
    //Invalid key
    for(int i = 0; i < strlen(key); i++){
        if(islower(key[i]) == 0){
            printf("Error: Invalid key.\n");
            fclose(input_file);
            return 1;
        }
    }
    
    if(strlen(key) == 0){
        printf("Error: Invalid key.\n");
        fclose(input_file);
        return 1;
    }
    
    //Invalid Message
    for(int i = 0; i < strlen(message); i++){
        if(islower(message[i]) == 0){
            printf("Error: Invalid message.\n");
            fclose(input_file);
            return 1;
        }
    }
    
    if(strlen(message) == 0){
        printf("Error: Invalid message.\n");
        fclose(input_file);
        return 1;
    }
    
    
    //Start of encrption
    //Adds character indices from the message and the key
    int i = 0;
    int j = 0;
    while(isalpha(message[i])){
        encrypted[i] = character_to_index(message[i]) + character_to_index(key[j]);
        i++;
        j++;
        //when the key gets to the end go back to the start
        if(isalpha(key[j]) == 0){
            j = 0;
        }
    }
    encrypted[i] = '\0';
    
    //wraps indices and converts indices to letters
    for(int l = 0; l < i; l++){
        if(encrypted[l] >= 26){
            encrypted[l] = encrypted[l] - 26; 
        }
        encrypted[l] = index_to_character(encrypted[l]);
    }
    //end of Encryption
    
    //start of decryption
    //subtracting the indices
    int m = 0;
    int k = 0;
    while(m < strlen(message)){
        decrypted[m] = character_to_index(message[m]) - character_to_index(key[k]);
        m++;
        k++;
        //when the key ends go to the start
        if(k == strlen(key)){
            k = 0;
        }
    }
    decrypted[m] = '\0';
   
    //wraps indices and converts indices to letters
    for(int i = 0; i < m; i++){
        if(decrypted[i] < 0){
            decrypted[i] = decrypted[i] + 26; 
        }
        decrypted[i] = index_to_character(decrypted[i]);
    }
    
    /* Example of the expected output format (using fake output strings) */


    //You can reuse this print statements in your solution (assuming you store each string
    //in the same variables).
    printf("Message: [%s]\n",message);
    printf("Key: [%s]\n",key);
    printf("Encrypted: [%s]\n",encrypted);
    printf("Decrypted: [%s]\n",decrypted);
    
    fclose(input_file);
    return 0;
}