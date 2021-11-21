#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showBanner(const char* fileName)
{
    FILE *fin;
    fin = fopen(fileName, "rb");

    char banner[128];
    fread(banner, 1, sizeof(banner), fin);
    printf("\nFILE %s BANNER: %s\n", fileName, banner);
    fclose(fin);
}


void encrypt(const char* fileName, const char* newFileName, const char* KWORD, int K)
{
    FILE *fin, *fout;
    fin = fopen(fileName, "rb");
    fout = fopen(newFileName, "wb+");

    if(!fin)
    {
        printf("\n[ERROR] - Could not open the file %s\n", fileName);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\n[Info] - File %s has been opened successfully\n", fileName);
        
        char block[512];
        
        size_t keylen = strlen(KWORD),
        byteCount = 0, allBytes = 0;

        while((byteCount = fread(block, 1, sizeof(block), fin)) > 0)
        {
            allBytes += byteCount;
            printf("\r[Info] - Byte has been read: %zu\r", byteCount);
            
            for (size_t i = 0; i < byteCount; i++)
            {
                K = K % keylen; // silly, ikr
                char kwordPos = KWORD[K];
                block[i] ^= (int)kwordPos;
                K++;
            }
            fwrite(block, 1, byteCount, fout);
        }
        printf("\n[Info] - All bytes read:%zu\n", allBytes);

    }
    fclose(fin);fclose(fout);
    showBanner(fileName);showBanner(newFileName);
}

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        fprintf(stderr, 
            "####################################################################\
                Usage: encrypter INPUT_FILE OUTPUT_FILE KEYWORD(string) KEY(integer)\
            ###############################108806################################\
                SIMPLE C encrypter. Encrypt again to decrypt the file\
            #####################################################################\
            \n");
    }
    encrypt(argv[1], argv[2], argv[3],atoi(argv[4]));
    return EXIT_SUCCESS;
}
