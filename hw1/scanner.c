//
//  scanner.c
//  askisi2
//
//  Created by Angelos Kyriacou on 11/3/12.
//
//
/*programa to opio dinoume ena kimeno kai mas tiponi tis leksis pou iparxoun se auto*/
#include <stdio.h>
#define SIZE 1024
#define SIZE_COL 28
#define SIZE_ROW 512

int main(int argc, char*argv[]){
    
    int plithos_char, i, j, k;
    char charaktiras[SIZE], array_words[SIZE_ROW][SIZE_COL];
    
    for (i=0; i<SIZE_ROW; i++) {/*arxikopioisi pinaka*/
        
        for (j=0; j<SIZE_COL; j++) {
            
            array_words[i][j] = '\0';
        }
        
        
    }
    
    i = 0;
    
    do{
    
        charaktiras[i] = getchar();
        i++;
    
    }while ((i < SIZE) && (charaktiras[i-1] != EOF));/*elexos mexri na ftasi sto megisto plithos charaktiro i mexri to EOF*/
    
    plithos_char = i - 1;
    
    j = 0;
    k =0 ;
    for (i=0; i<plithos_char; i++) {
        
        if ((charaktiras[i] >= 'a' && charaktiras[i] <= 'z') || (charaktiras[i] >= 'A' && charaktiras[i] <= 'Z')) {/*sinthiki gia na eleksi an o xaraktiras einai entos ton orion*/
            
            array_words[j][k] = charaktiras[i];
            k++;
            
        }
        
        else{
            
            array_words[j][k] = '\0';
            j++;
            k = 0;
            
        }
        
    }
    
    for (i=0; i<SIZE_ROW; i++) {/*ektiposi lekseon*/
        
        for (j=0; j<SIZE_COL; j++) {
            
            printf("%c",array_words[i][j]);
        }
        
        if(array_words[i][j] !='\0'){
            printf("\n");
        }
        
        
    }
    
    return(0);
    
}