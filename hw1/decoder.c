
//  decoder.c
//  askisi1
//
//  Created by Angelos Kyriacou on 11/1/12.
//
//

/* programa to opio apokriptografi xaraktires*/

#include <stdio.h>
#define SIZE 1024

int main (int argc, char *argv[]){
    
    int i, thesi, plithos_char[94], max_plithos_char, key;
    char charaktiras[SIZE], ekti_char;
   
    
    for (i=0; i<94; i++) {/* arxikopisi metriti gia to plithos tou kathe charaktira*/
        plithos_char[i] = 0;
    }
   
    for (i=0; i<SIZE; i++) {/*arxikopisi pinaka xaraktiron*/
        charaktiras[i] = '\0';
    }
    
    i = 0;
    
    do {
        
        
        charaktiras[i] = getchar();
        thesi = charaktiras[i] - 32;
        plithos_char[thesi]++;
        i++;
        
    } while ((i<SIZE) && (charaktiras[i-1] != EOF));/*elexos  gia mexrin na pari to megisto plithos xaraktiron i mexri na ftasi sto EOF*/
    
    max_plithos_char = plithos_char[0];
    
    key = 0;
    
    for (i = 1; i<94; i++) {/*euresi xaraktira me to megalitero plithos kai klidiou*/
        if (max_plithos_char < plithos_char[i]) {
            max_plithos_char = plithos_char[i];
            key = i ;
        }
    }
    
    
    
    printf("Key: %d\n\n", key);
   
    printf("Text :\n");
    
    for (i = 0; i<SIZE; i = i + 1) {/*ektiposi kodikopiimenou xaraktira*/
        
        if ((charaktiras[i] >= ' ') && (charaktiras[i] <= '~')) {
            
        
            if(charaktiras[i] - key < ' '){
        
                ekti_char = ('~' - key + 1)  + (charaktiras[i] - ' ');
        
            }
    
            else{
            
                ekti_char = ((charaktiras[i] - ' ') %  ('~'- ' ')) - key + ' ' ;
            
            }
        }
        else{
            
            ekti_char = charaktiras[i];
            
        }
    
        printf("%c", ekti_char);
    }
    printf("\n");
    
    return(0);
}