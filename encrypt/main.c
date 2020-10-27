#include <stdio.h>
#include <string.h>

void make_new_name(char *new_name, char *original_name);
int length_of_password(char *password);
int is_alpha(char c);
int is_digit(char c);
int is_valid_password(char *password);
void perform_XOR(char *input_filename, char *output_filename, char *password);
void print_first_five(char *filename);

int main(int argc, char *argv[]) {
    char original_name[100];
    char password[100];
    char new_name[100];
    scanf("%s%s",original_name,password);
    make_new_name(&new_name,&original_name);
    printf("New filename = %s\n",new_name);
    //printf("%s%s",filename,password);
    int password_validation = is_valid_password(&password);

    if(password_validation==1){
        perform_XOR(&original_name,&new_name,&password);
        print_first_five(&new_name);
    }
    return 0;
}

void print_first_five(char *filename){
    /*
    FILE *filePointer;
    char ch;
    int count=0;
    //2
    filePointer = fopen(filename, "rb");

    if (filePointer == NULL)
    {
        printf("File is not available \n");
    }
    else
    {
        while ((ch = fgetc(filePointer)) != EOF)
        {
            printf("%x\n",(ch));
            count++;
            if(count>5){break;}
        }
    }
    fclose(filePointer);
    */
    FILE *fileptr;
    char *buffer;
    long filelen;

    fileptr = fopen(filename, "rb");  // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    fread(buffer, 1, filelen+1, fileptr); // Read in the entire file
    fclose(fileptr); // Close the file
    int i=0;
    for(i=0;i<5;i++){
        printf("%x\n",buffer[i]);
    }
}
void make_new_name(char *new_name, char *original_name){
    strcpy(new_name,"new-");
    strcat(new_name,original_name);
}

int length_of_password(char *password){
    //print the password to confirm that the password is passed
    //printf("%s\n",password);
    return strlen(password);
}

int is_alpha(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        return 1;
    }
    return 0;
}

int is_digit(char c){
    if(c >= '0' && c <= '9'){
        return 1;
    }
    return 0;
}

void perform_XOR(char *input_filename, char *output_filename, char *password){
    int blockSize =  length_of_password(password);
    FILE *file, *newFile;
    char block[blockSize];
    int i, numBytes;
    file = fopen(input_filename, "rb");
    newFile = fopen(output_filename, "wb");
    do {
        numBytes = fread(block, 1, blockSize, file);
        for (i=0; i<numBytes; i++){
            block[i] = block[i]^password[i];
        }
        // write the result of XOR to the output file
        fwrite(block, 1, numBytes, newFile);
      } while (numBytes == blockSize);


      fclose(newFile);
      fclose(file);


    return 0;
}


int is_valid_password(char *password){
    //print the password to confirm that the password is passed
    //printf("%s\n",password);

    int password_length = length_of_password(password);
    printf("Password length = %d\n",password_length);

    //print the password length to confirm that the password length is correct
    //printf("%d\n",password_length);

    int alphabet_count = 0;
    int digit_count = 0;
    int validity = 0;
    int check_validity = 1;

    if(password_length<8){
      printf("The password need to have at least 8 characters.\n");
      check_validity=0;
    }

    int i=0;
    for(i=0;i<password_length;i++){
        validity = is_alpha(password[i]);
        if(validity==1){
            alphabet_count+=1;
        }
    }
    i =0;
    for(i=0;i<password_length;i++){
        validity = is_digit(password[i]);
        if(validity==1){
            digit_count+=1;
        }
    }
    //check the number of digits, letters and special character count =>special_character_count = password_length-(alphabet_count+digit_count)
    //printf("%d %d %d\n",password_length,alphabet_count,digit_count);

    if(alphabet_count==0){
        printf("The password needs to contain at least one alphabetical character.\n");
        check_validity=0;
    }
    if(digit_count==0){
        printf("The password needs to contain at least one digit.\n");
        check_validity=0;
    }

    int special_character_count = password_length-(alphabet_count+digit_count);
    if(special_character_count>0){
        printf("The password should not contain any special characters.\n");
        check_validity=0;
    }

    if (check_validity==1){
        return 1;
    }
    return 0;
}

