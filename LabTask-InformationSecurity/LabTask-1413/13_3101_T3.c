//Vignere Cipher

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    char msg[200];
    char key[200];
    printf("Enter the Message:");
    scanf("%s",msg);
        printf("Enter the Key:");
    scanf("%s",key);
   int ml=strlen(msg),kl=strlen(key),i,j;
    char newKey[ml], encryptedMsg[ml], decryptedMsg[ml];
   for(i=0,j=0;i<ml;i++,j++){
        if(j == kl)
            j = 0;

        newKey[i] = key[j];
   }
       newKey[i] = '\0';

        for(i = 0; i<ml; ++i)
        encryptedMsg[i] = ((msg[i] + newKey[i]) % 26) + 'A';

    encryptedMsg[i] = '\0';
        for(i = 0; i <ml; ++i)
        decryptedMsg[i] = (((encryptedMsg[i] - newKey[i]) + 26) % 26) + 'A';

    decryptedMsg[i] = '\0';

    printf("Original Message: %s", msg);
    printf("\nKey: %s", key);
    printf("\nNew Generated Key: %s", newKey);
    printf("\nEncrypted Message: %s", encryptedMsg);
    printf("\nDecrypted Message: %s", decryptedMsg);

    return 0;
}
/*
Enter the Message:INFORMATIONSECURITY
Enter the Key:CAPTCHA
Original Message: INFORMATIONSECURITY
Key: CAPTCHA
New Generated Key: CAPTCHACAPTCHACAPTC
Encrypted Message: KNUHTTAVIDGULCWRXMA
Decrypted Message: INFORMATIONSECURITY */


