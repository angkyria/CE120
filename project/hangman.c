//ilias konstaninou 1677 iliaskonst@uth.gr
//angelos kyriacou 1563 angkyria@inf.uth.gr

//programma leksiko to opio klevi ton xristi stin arxi tou programmatos dinoume tria orismata apo tin grami entolon likos leksi girous kai leksiko to programma dimioyrga mia lista me tis leksi me to epithimito plithos afou exi kani elexon ton orismaton pou exoun dothi oti einai sosta meta dimiourga tin proti katigoria i opia periexi oles tis leksi me to epithimito mikos kai meta ksekina i kiria litourgia tou pexnidiou sti opia ksekina o xristi kai dini gramata to programma kani anazitisi sto dinamika desmeumeno pinaka tis lista me tis katigories gia na dimiourgisi tis nees katigories me to grama pou exei dosi o xristi kai meta epilegi tin katigoria me tis poliplithesteres leksis

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define WORDLEN 30

struct dict {
    
    char word[WORDLEN];//leksi leksikou
    struct dict *next_dict;//komvos empomenis leksis
    
};

struct class_equivalence {
    
    int word_plithos;//plithos lekseon kathe katigorias
    char *agent_cat;//antiprosopos katigorias
    char **words;//pinakas lekseo
    struct class_equivalence *next_class_equivalence;//epomenos kovos katigorias
};

int elexos(char *argv1, char *argv2, int argc){//sinartisi stin opia elexoume kata poson exoun dothi orismata
    
    if ( argc == 4) {//elexos an exei dothi o sostos arithmos orismaton
        
        while ( (atoi(argv1)<1) || (atoi(argv1)==26) || (atoi(argv1)==27)|| (atoi(argv1)>29) ) {//elexos an exi dothi sosto to orisma gia to plithos to gramaton
            printf("There are no words of length %d in the dictionary\nSpecify a different length: ", atoi(argv1));
            scanf(" %s", argv1);
        }
        
        while (atoi(argv2)<1) {//elexos an exei dothi sostos arithmos giron
            printf("You may not have fewer than one turns.\nSpecify a different number of turns: ");
            scanf(" %s", argv2);
        }
        return 1;
    }else{
        if (argc<=3) {//elexos an exoun dothi ligotera orismata
            printf("Insufficient arguments.\n");
        }else{//elexos an exoun dothi perisotera orismata
            printf("Too many arguments.\n");
        }
        printf("./hangman LENGTH TURNS DICTIONARY\n\tLENGTH: requested length of mystery word. Must be >1, <30, !=26, !=27\n\tTURNS: requested number of turns. Must be >0\n\tDICTIONARY: name of dictionary file\n");//minima lathos oriamsaton
        return 0;
    }
    
};

char *getWord(char *filename)  {//sinartisi gia na perni tis leksis apo to arxio
	char formatstr[15], *word;
	static FILE *input;
	static int firstTime = 1;
	if (firstTime) {
		input = fopen(filename, "r");
		if (input == NULL) {
			printf("ERROR: Could not open file \"%s\"\n", filename);
			exit(1);
		}
		firstTime = 0;
	}
	word = (char*)malloc(sizeof(char)*WORDLEN);
	if (word == NULL) {
		printf("ERROR: Memory allocation error in getWord\n");
		exit(1);
	}
	sprintf(formatstr, "%%%ds", WORDLEN-1);
	fscanf(input, formatstr, word);
	if (feof(input)) {
		fclose(input);
		return NULL;
	}
	return word;
}

struct dict *word_len(char *argv1, char *argv3){//sinartisi stin opia dimiourgoume tin lista me tis epithimites leksis i opies periexoun to plithos to grammaton pou xriazomaste
    
    char *word;
    
    struct dict *curr, *new;
    curr = NULL;
    
    do {
        
        word = getWord(argv3);//evrezi leksis
        if (word==NULL) {//elexos an exoume diavasi oles tis leksis
            break;
        }
        
        if (strlen(word)==atoi(argv1)) {//elexos tis leksi an exei to epithimito plithos gramatos gia prosthiki sti lista
            
            new = curr;
            if (new == NULL) {
              
                if (!(new = (struct dict*)malloc(sizeof(struct dict)))) {
                    printf("Memory overflow in insert\n");
                    exit(1);
                }
                
                strcpy(new->word,word);
                
                if (curr == NULL) {
                    
                    curr = new;
                    curr->next_dict = NULL;
                
                }else{
                    
                    new->next_dict = curr;
                    curr = new;
                    
                }

                
            }else{
                
                
                while (new!=NULL) {
                    new = new->next_dict;
                }
                if (!(new = (struct dict*)malloc(sizeof(struct dict)))) {
                    printf("Memory overflow in insert\n");
                    exit(1);
                }
                strcpy(new->word,word);
                
                if (curr == NULL) {
                    
                    curr = new;
                    curr->next_dict = NULL;
                    
                }else{
                    
                    new->next_dict = curr;
                    curr = new;
                    
                }
            }
            
        }

    } while (1);
    
    
    
    return curr;//epistrofi tis listas
};

struct class_equivalence *class_initialization(struct dict *curr_dict, struct class_equivalence *class_curr, char *argv1){//dimiourgia protou komvou o opios periexi mono tis '_' me to epithimito plithos gramaton
    
    int i;
    
    struct class_equivalence *new_class, *head_class;
    struct dict *new_dict;
    
    new_class = NULL;
    new_dict = NULL;
    head_class = NULL;
    
    
    if (class_curr == NULL) {
        
        if (!(new_class = (struct class_equivalence*)malloc(sizeof(struct class_equivalence)))) {
            printf("Memory overflow in insert");
            exit(1);
        }
        
        new_class->agent_cat = (char *)malloc(sizeof(char)*atoi(argv1));
        
        for (i=0; i<atoi(argv1); i++) {//pavloues
            new_class->agent_cat[i]='_';
        }
        
        i=0;
        new_dict=curr_dict;
        
        while (new_dict!=NULL) {//metritis lekseon
            i++;
            new_dict = new_dict->next_dict;
        }
        
        new_class->word_plithos = i;
        
        new_class->words = (char **)malloc(sizeof(char *)*i);//desmefsi mnimis gia pose leksi tha iparxoun(lines)
        
        for (i=0, new_dict = curr_dict; i < new_class->word_plithos; i++, new_dict = new_dict->next_dict) {
            new_class->words[i] = (char *) malloc(sizeof(char)*strlen(new_dict->word));//desmefsi mnimis gia to kathe gramma (columns)
            strcpy(new_class->words[i], new_dict->word);
        }
        new_class->next_class_equivalence = NULL;
        class_curr = new_class;
        
    }else{
        
        
        
    }
    
    return class_curr;
};

struct class_equivalence *class_creation (struct class_equivalence *home_class, char letter){//sinartisi stin opia dimiourgoume tis katigories kai epilegoume auti me tis poliplithesteres leksis
    
    struct class_equivalence *max_class, *curr_class, *head_class, *class, *start_class;
    int i, j, k, anagnoristiko;
    char *curr_word_agent;
    
    head_class = NULL;
    anagnoristiko = 0;
    start_class = home_class;
    
    for (i=0; i<start_class->word_plithos; i++) {//loop pou pernoume tin kathe leksi gia na elksoume an mas kani gia dimiourgia katigorias
        
        if (start_class->words[i]!=NULL) {//elexos an i leksi einai null
            
            curr_class = NULL;
            curr_class = (struct class_equivalence*) malloc(sizeof( struct class_equivalence));
            curr_class->word_plithos = 0;
            curr_class->agent_cat = (char *) malloc(sizeof(char)*strlen(start_class->agent_cat));
            strcpy(curr_class->agent_cat, start_class->agent_cat);
            
            for (j=0; j<strlen(start_class->words[i]); j++) {//dimiourgia katigorias
                
                if (start_class->words[i][j] == letter) {
                    
                    curr_class->agent_cat[j] = letter;
                    anagnoristiko = 1;
                    
                }
                
            }
            
            if (anagnoristiko == 1) {//an to anagnoristiko einai ena simeni oti i leksi periexi toulaxisto to ena gramma pou mas exei dosi o xristis
                
                curr_class->words = (char **)malloc(sizeof(char *));
                curr_class->words[curr_class->word_plithos] = (char *)malloc(sizeof(char)*strlen(start_class->words[i]));
                strcpy(curr_class->words[curr_class->word_plithos], start_class->words[i]);
                curr_class->word_plithos++;
                
                if (head_class == NULL) {//elexos an iparxi alli katigoria an den iparxi dimiourga ti nea katigoria
                    
                    head_class = (struct class_equivalence*)malloc(sizeof(struct class_equivalence));
                    
                    for (j=i+1; j<start_class->word_plithos; j++) {//loop sto opio kanoume tis katigories
                        
                        curr_word_agent = NULL;
                        curr_word_agent = (char *)malloc(sizeof(char)*strlen(start_class->agent_cat));
                        strcpy(curr_word_agent, start_class->agent_cat);
                        
                        for (k=0; k<strlen(curr_class->agent_cat); k++) {//loop sto opio dimiourgoume tin katigoria
                            
                            if (start_class->words[j]==NULL) {
                                break;
                            }
                            
                            if (start_class->words[j][k] == letter) {
                                
                                curr_word_agent[k] = letter;
                                
                            }
                            
                        }
                        
                        if (strcmp(curr_class->agent_cat, curr_word_agent) == 0) {//elexos an einai i idia katigoria an iparxi kanoume realloc ti leksi kai tin prosthetoume
                            
                            
                            curr_class->words = (char **) realloc (curr_class->words, (curr_class->word_plithos + 1)* (sizeof(char *))) ;
                            curr_class->words[curr_class->word_plithos] = (char *)malloc(sizeof(strlen(start_class->words[i])));
                            strcpy(curr_class->words[curr_class->word_plithos], start_class->words[j]);
                            curr_class->word_plithos++;
                            start_class->words[j] = NULL;//diagrafi tis tis leksi apo tin lista
                            
                        }
                        
                    }
                    
                    head_class->word_plithos = curr_class->word_plithos;
                    head_class->agent_cat = (char *) malloc(sizeof(char)*strlen(curr_class->agent_cat));
                    strcpy(head_class->agent_cat, curr_class->agent_cat);
                    head_class->words = (char **) malloc ( curr_class->word_plithos * sizeof(char *));
                    for (j = 0;j<head_class->word_plithos;j++) {
                        
                        head_class->words[j] = (char *)malloc(sizeof(strlen(curr_class->words[j])));
                        strcpy(head_class->words[j], curr_class->words[j]);
                        
                    }
                    head_class->next_class_equivalence=NULL;
                    
                    
                }else{
                    
                    class = head_class;//antigrafi tis arxikis listas me tis katigories
                    
                    while (class != NULL) {//loop sto opio ftanoume sto telos tis katigorias
                        
                        class = class->next_class_equivalence;
                        
                    }
                    
                    class = (struct class_equivalence*)malloc(sizeof(struct class_equivalence));
                    
                    for (j=i+1; j<start_class->word_plithos; j++) {//loop sto opio pernoume tin kathe leksi
                        
                        curr_word_agent = NULL;
                        curr_word_agent = (char *)malloc(sizeof(char)*strlen(start_class->agent_cat));
                        strcpy(curr_word_agent, start_class->agent_cat);
                        
                        for (k=0; k<strlen(start_class->agent_cat); k++) {//dimiourgia tou antiproso pou katigorias
                            
                            if (start_class->words[j]==NULL) {//elexos an iparxi leksi se auti ti thesi
                                break;
                            }
                            
                            if (start_class->words[j][k] == letter) {
                                
                                curr_word_agent[k] = letter;
                                
                            }
                            
                        }
                        
                        if (strcmp(curr_class->agent_cat, curr_word_agent) == 0) {//elexos an einai i idia katigoria an iparxi kanoume realloc ti leksi kai tin prosthetoume
                            
                            
                            curr_class->words = (char **) realloc (curr_class->words, (curr_class->word_plithos + 1)* (sizeof(char *))) ;
                            curr_class->words[curr_class->word_plithos] = (char *)malloc(sizeof(strlen(start_class->words[i])));
                            strcpy(curr_class->words[curr_class->word_plithos], start_class->words[j]);
                            curr_class->word_plithos++;
                            start_class->words[j] = NULL;//diagrafi tis leksi apo tin lista
                            
                            
                        }
                        
                    }
                    
                    
                    class->word_plithos = curr_class->word_plithos;
                    class->agent_cat = (char *) malloc(sizeof(char)*strlen(curr_class->agent_cat));
                    strcpy(class->agent_cat, curr_class->agent_cat);
                    class->words = (char **) malloc ( curr_class->word_plithos * sizeof(char *));
                    for (j = 0;j<class->word_plithos;j++) {
                        
                        class->words[j] = (char *)malloc(sizeof(strlen(curr_class->words[j])));
                        strcpy(class->words[j], curr_class->words[j]);
                        
                    }

                    class->next_class_equivalence = head_class;
                    head_class = class;
                    
                    
                }
                
                
                anagnoristiko = 0;
                
            }
            
        }

    
    }
    
    if (head_class == NULL) {//an to head einai null simeni den iparxi tetio gramma
        return home_class;
    }
    //arxikopisi tou megistou me to proto stixio stilista
    max_class=NULL;
    max_class = (struct class_equivalence *)malloc(sizeof(struct class_equivalence));
    max_class->word_plithos = head_class->word_plithos;
    max_class->agent_cat = (char *) malloc(sizeof(char)*strlen(start_class->agent_cat));
    strcpy(max_class->agent_cat, head_class->agent_cat);
    max_class->words = (char **) malloc ( max_class->word_plithos * sizeof(char *));
    
    for (i = 0;i<max_class->word_plithos;i++) {
    
        max_class->words[i] = (char *)malloc(sizeof(strlen(head_class->words[i])));
        strcpy(max_class->words[i], head_class->words[i]);
    
    }
    
    max_class->next_class_equivalence = NULL;
    
    head_class =   head_class->next_class_equivalence;
    
    
    
    while (head_class!=NULL) {//diatreksi tis lista an iparxoun gia na vrethi to megisto
        
        if (max_class->word_plithos<head_class->word_plithos) {//elexos katigorias oti einai i megisti
            
            max_class =NULL;
            max_class = (struct class_equivalence *)malloc(sizeof(struct class_equivalence));
            max_class->word_plithos = head_class->word_plithos;
            max_class->agent_cat = (char *) malloc(sizeof(char)*strlen(head_class->agent_cat));
            strcpy(max_class->agent_cat, head_class->agent_cat);
            max_class->words = (char **) malloc ( head_class->word_plithos * sizeof(char *));
            for (i = 0;i<max_class->word_plithos; i++) {
                max_class->words[i] = (char *)malloc(sizeof(strlen(head_class->words[i])));
                strcpy(max_class->words[i], head_class->words[i]);
            }
            //max_class->words = head_class->words;
            max_class->next_class_equivalence = NULL;
            
        }
        
        head_class = head_class->next_class_equivalence;
        
    }
    
    //apodesmeusi mnimis
    while (head_class!=NULL) {
        
        curr_class = head_class;
        head_class=head_class->next_class_equivalence;
        free(curr_class->words);
        free(curr_class->agent_cat);
        free(curr_class);
    }
    
    free(curr_word_agent);
    
    return max_class;
};

void game_function(struct class_equivalence *curr_class, struct dict *curr_dict, char *argv1, char *argv2){//sinartisi gia ekinisi pexnidiou
    
    int turns, i, j, k, anagnoristiko_grammatos;
    
    turns = atoi(argv2);
    
    char letters[atoi(argv2)], letter, temp_letter;
    
    for (i=0; i<turns; i++) {
        letters[i]='~';
    }
    
    
    
    for (i=0; i<turns; i++) {//elexos gia ton arithmo ton giro
        
        
        printf("Remaining guesses: %d\n", turns-i);//eptiposi enapominoton giron
        
        for (j=0; j<turns; j++) {//taksinomisi grammaton
            
            for (k=0; k<turns; k++) {
                if (letters[k-1]<letters[k]) {
                    
                    temp_letter = letters[j];
                    letters[j] = letters[j-1];
                    letters[j-1] = temp_letter;
                    
                }
            }
            
        }

        printf("Used Letters: ");
        
        for (j=0; j<turns; j++) {//ektiposi xrisimopimeno gramaton
            
            if (letters[j]!='~') {
                printf("%c ", letters[j]);
            }
            
        }
        
        printf("\nUnused letters: ");
        
        for (letter='a', j=0; j<26; j++, letter++) {//eptiposi gramaton pou den xrisimopithikan
            
            for (k=0, anagnoristiko_grammatos = 0; k<turns; k++) {
                
                if (letters[k] == letter) {
                    anagnoristiko_grammatos = 1;
                }
                
            }
            
            if (anagnoristiko_grammatos == 0) {
                printf("%c ", letter);
            }
            
        }
        
        printf("\nWord: %s", curr_class->agent_cat);//ektiposi leksi pou exi kataskevasi mexri stigmis
        
        printf("\nCategory size : %d\n", curr_class->word_plithos);

        
        do {//loop sto opoio pentoume to gramma kai elexoume an to exoume xrisimopioisi i oxi
            
            printf("\nGuess a letter: ");
            
            scanf(" %c", &letter);
            
            for (j=0, anagnoristiko_grammatos=0; j<i; j++) {
                
                if (letters[j]==letter) {
                    anagnoristiko_grammatos=1;
                }
                
                if (anagnoristiko_grammatos==1) {
                    printf("You have already guessed this letter");
                    break;
                }
                
            }
            
        } while ( (letter<'a'&&letter>'z') || (letter<'A'&&letter>'Z')||(anagnoristiko_grammatos==1));
        
        if (isupper(atoi(&letter)!=0)) {//an to gramma einai kefaleo to metatrepoume se mikro
            letter = letter + 32;
        }
        
        
        
        letters[i]=letter;//metavliti stin opia apothikevounte ta xrisimopimena grammata
        
        
        
        curr_class = class_creation(curr_class, letter);
        
        
        
    }
        
        for (i=0; i<atoi(argv1); i++) {
            
            if (curr_class->agent_cat[i]=='_') {
                printf("YOU LOST! The word is %s", curr_class->words[i]);
                return ;
            }
            
        }
        printf("YOU WON! The word is %s", curr_class->agent_cat);
    
    
    return;
}

int main (int argc, char *argv[]){
    
    int start;
    char play_again;
    
    struct dict *dict_head, *curr;
    struct class_equivalence *class_equivalence_head, *curr_class;
    
    dict_head = NULL;
    class_equivalence_head = NULL;
    
    start = elexos(argv[1], argv[2], argc);//kalesma sinartisi gia elexo ton orismaton
    
    dict_head = word_len(argv[1], argv[3]);//dimiourigia lista me tis epithimites leksis pou xriazonte
    
    class_equivalence_head = class_initialization(dict_head, class_equivalence_head, argv[1]);//dimiourgia protis katigorias i opia periexi mono '_'
    
    game_function(class_equivalence_head, dict_head, argv[1], argv[2]);//kalesma sinartisi gia ksekinima tou pexnidiou
    
    free(class_equivalence_head);
    class_equivalence_head = NULL;
    printf("\nPlay again? (y/n)\n");
    scanf(" %c", &play_again);
    while (play_again=='y'||play_again=='Y') {
       
        class_equivalence_head = class_initialization(dict_head, class_equivalence_head, argv[1]);
        
        game_function(class_equivalence_head, dict_head, argv[1], argv[2]);
        
        free(class_equivalence_head);
        class_equivalence_head = NULL;
        printf("\nPlay again? (y/n)\n");
        scanf(" %c", &play_again);
    }
    //apodesmefsi mnimis
    
    while (dict_head!=NULL) {
        curr=dict_head;
        dict_head=dict_head->next_dict;
        free(curr);
    }
    
    while (class_equivalence_head!=NULL) {
        
        curr_class=class_equivalence_head;
        class_equivalence_head=class_equivalence_head->next_class_equivalence;
        free(class_equivalence_head->words);
        free(class_equivalence_head->agent_cat);
        free(curr_class);
    }
    
    
    
    
    
    
    return 0;
}