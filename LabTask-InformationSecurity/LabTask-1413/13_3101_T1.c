//Casear Cipher
#include<stdio.h>
#include<stdlib.h>
void encrypt(char text[],int shift){
    for(int i=0;text[i]!=0;i++){
    if(text[i]>='A' && text[i]<='Z'){
    text[i]=(text[i]+shift-'A')%26 + 'A';

    }
        else if(text[i]>='a' && text[i]<='z'){
    text[i]=(text[i]+shift-'a')%26 + 'a';

    }
}

}
    void decrypt(char text[],int shift){
    encrypt(text,-shift);
}
int main(){
int shift;
char text[100];
printf("Enter text to Encrypt:");
fgets(text,sizeof(text),stdin);
printf("Enter Shift Value:");
scanf("%d",&shift);
encrypt(text,shift);
printf("Encrypted text:%s\n",text);

decrypt(text,shift);
printf("Decrypted text:%s\n",text);
return 0;
}
        /* Enter text to Encrypt:JIHAD
        Enter Shift Value:3
        Encrypted text:MLKDG
        Decrypted text:JIHAD
    */
    
    
    
   /*  Enter text to Encrypt:JIHAD
Enter Shift Value:3
Encrypted text:MLKDG

Decrypted text:JIHAD
*/

