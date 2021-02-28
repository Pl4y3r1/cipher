#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void flip(char *string){
        char *i;
        for(i=string; *i; i++){
                if(*i == '1'){
                        *i = '0';
                } else if(*i == '0'){
                        *i = '1';
                }
        }
}

void deHex(char *string){
        char buffer[5];
        int i = 0;

        while(string[i] != '\0'){
                buffer[0] = string[i];
                i++;
                buffer[1] = string[i];
                i++;
                buffer[2] = string[i];
                i++;
                buffer[3] = string[i];
                buffer[4] = '\0';
                i+=2;

                if(strcmp(buffer, "0000") == 0){
                        printf("0");
                } else if(strcmp(buffer, "0001") == 0){
                        printf("1");
                } else if(strcmp(buffer, "0010") == 0){
                        printf("2");
                } else if(strcmp(buffer, "0011") == 0){
                        printf("3");
                } else if(strcmp(buffer, "0100") == 0){
                        printf("4");
                } else if(strcmp(buffer, "0101") == 0){
                        printf("5");
                } else if(strcmp(buffer, "0110") == 0){
                        printf("6");
                } else if(strcmp(buffer, "0111") == 0){
                        printf("7");
                } else if(strcmp(buffer, "1000") == 0){
                        printf("8");
                } else if(strcmp(buffer, "1001") == 0){
                        printf("9");
                } else if(strcmp(buffer, "1010") == 0){
                        printf("A");
                } else if(strcmp(buffer, "1011") == 0){
                        printf("B");
                } else if(strcmp(buffer, "1100") == 0){
                        printf("C");
                } else if(strcmp(buffer, "1101") == 0){
                        ;printf("D");
                } else if(strcmp(buffer, "1110") == 0){
                        printf("E");
                } else if(strcmp(buffer, "1111") == 0){
                        printf("F");
                } else{
                        printf(" ");
                }
        }
        printf("\n");
}

void divideString(char *string, int n){
        int size = strlen(string);
        int i = 1;
        int j = 1;
        char* buffer = malloc(sizeof(char* ) * strlen(string) * 2);

        strcpy(buffer,string);
        string[0] = buffer[0];

        for(i = 1; j < size; i++){
                if(j%n == 0){
                        string[i] = ' ';
                        i++;
                }
                        string[i] = buffer[j];
                        j++;
        }
        string[i] = '\0';
        free(buffer);
}

int getlines(FILE* stream, char*** line, int* ntot, size_t len){
        int i = 0;
	int max = 16;
	ssize_t nread;

	while((nread = getline(&(*line)[i], &len, stream)) != -1){
		if(i == (max-1)){
			max = max*2;
			*line = realloc(*line, sizeof(char*) * max);
			if(*line == NULL){
				printf("ERROR: Memmory Allocation Failed\n");
				exit(EXIT_FAILURE);
			}
		}
		*ntot += (nread - 1);
		i++;
	}
 
        return i;
}

char** atbash(FILE* stream1){
	int i = 0;
	int j = 0;
	int max = 16;
	char** abc = malloc(sizeof(char*) * max);
	char* line;
	size_t len = 0;
	ssize_t nread;

	while((nread = getline(&line, &len, stream1)) != -1){
		printf("line# %i = %s", i, line);
		abc[i] = malloc(sizeof(char*) * strlen(line) * max);
		strncpy(abc[i], line, (len * 2));
		i++;
	}
	i--;
	
	printf("I = %i\n", i);
	for(j = 0; j < i; j++){
		printf("%s", abc[j]);
	}
	//free(line);
	fclose(stream1);
	return abc;
}

void shift(char* string, int verbose){
        char *nospace = string;
        char *temp = string;
	char* buffer = malloc(sizeof(char* ) * strlen(string) * 2);

        char t;
        int i = 0;
        int size;

        if(verbose == 1){
                printf("\nRemoving Spaces\n");
        }
        while(*temp != 0){
                *nospace = *temp++;
                if(*nospace != ' '){
                        nospace++;
                }
        }
        *nospace = 0;
        if(verbose == 1){
                printf("\n%s\n", string);
                printf("\nShifting String\n");
        }
        strcpy(buffer, string);
        if(verbose == 1){
                printf("Buffer: \n%s\n\n", buffer);
        }
        t = string[0];
        size = strlen(string);
        for(i = 0; i < (size-1); i++){
                string[i] = buffer[i+1];
        }
        string[i] = t;
        string[i+1] = '\0';
        if(verbose == 1){
                printf("%s\n", string);
        }
	free(buffer);
}

void clean(char* string, int verbose){
        char *nospace = string;
        char *temp = string;

        if(verbose == 1){
                printf("\nRemoving Spaces\n");
        }
        while(*temp != 0){
                *nospace = *temp++;
                if(*nospace != ' '){
                        nospace++;
                }
        }
        *nospace = 0;
}

char* normalize(char* string, int nflag){
        char *i;
        switch(nflag){
                case 0:
                        for(i=string; *i; i++){  
                                if(*i == 'y' || *i == 'Y'){
                                        *i = '1';
                                } else if(*i == 'o' || *i == 'O'){
                                        *i = '0';
                                } else if(*i == 'g' || *i == 'G'){
                                        *i = '1';
                                } else if(*i == 'p' || *i == 'P' || *i == 'b' || *i == 'B'){
                                        *i = '0';
                                } else if(*i == '\n'){
                                        *i = '\0';
                                }
                        } 
                        return string;
                case 1:
                        for(i=string; *i; i++){  
                                if(*i == 'y' || *i == 'Y'){
                                        *i = '0';
                                } else if(*i == 'o' || *i == 'O'){
                                        *i = '1';
                                } else if(*i == 'g' || *i == 'G'){
                                        *i = '1';
                                } else if(*i == 'p' || *i == 'P' || *i == 'b' || *i == 'B'){
                                        *i = '0';
                                } else if(*i == '\n'){
                                        *i = '\0';
                                }
                        }
                        return string;
                case 2:
                        for(i=string; *i; i++){   
                                if(*i == 'y' || *i == 'Y'){
                                        *i = '1';
                                } else if(*i == 'o' || *i == 'O'){
                                        *i = '0';
                                } else if(*i == 'g' || *i == 'G'){
                                        *i = '0';
                                } else if(*i == 'p' || *i == 'P' || *i == 'b' || *i == 'B'){
                                        *i = '1';
                                } else if(*i == '\n'){
                                        *i = '\0';
                                }
                        }
                        return string;
                case 3:  
                        for(i=string; *i; i++){
                                if(*i == 'y' || *i == 'Y'){
                                        *i = '0';
                                } else if(*i == 'o' || *i == 'O'){
                                        *i = '1';
                                } else if(*i == 'g' || *i == 'G'){
                                        *i = '0';
                                } else if(*i == 'p' || *i == 'P' || *i == 'b' || *i == 'B'){
                                        *i = '1';
                                } else if(*i == '\n'){
                                        *i = '\0';
                                } 
                        }
                        return string;
                case 8:  
                        for(i=string; *i; i++){
                                if(*i == '\n'){
                                        *i = '\0';
                                }
                        }
                        return string;
                default:
                        printf("\nERROR: Could not normalize stirng\n");
                        return string;
        }
}

void deRNA(char *string){
	char buffer[4];
	int i = 0;

	while(string[i] != '\0'){
		buffer[0] = string[i];
		i++;
		buffer[1] = string[i];
		i++;
		buffer[2] = string[i];
		buffer[3] = '\0';
		i+=2;

		if(strcmp(buffer, "yyy") == 0 || strcmp(buffer, "YYY") == 0 || strcmp(buffer, "ttt") == 0 || strcmp(buffer, "TTT") == 0 || strcmp(buffer, "uuu") == 0 || strcmp(buffer, "UUU") == 0){
			printf("F");
		} if(strcmp(buffer, "yyp") == 0 || strcmp(buffer, "YYP") == 0 || strcmp(buffer, "yyb") == 0 || strcmp(buffer, "YYB") == 0 || strcmp(buffer, "ttc") == 0 || strcmp(buffer, "TTC") == 0 || strcmp(buffer, "uuc") == 0 || strcmp(buffer, "UUC") == 0){
			printf("F");
		} if(strcmp(buffer, "yyo") == 0 || strcmp(buffer, "YYO") == 0 || strcmp(buffer, "yyr") == 0 || strcmp(buffer, "YYR") == 0 || strcmp(buffer, "tta") == 0 || strcmp(buffer, "TTA") == 0 || strcmp(buffer, "uua") == 0 || strcmp(buffer, "UUA") == 0){
			printf("L");
		} if(strcmp(buffer, "yyg") == 0 || strcmp(buffer, "YYG") == 0 || strcmp(buffer, "ttg") == 0 || strcmp(buffer, "TTG") == 0 || strcmp(buffer, "uug") == 0 || strcmp(buffer, "UUG") == 0){
			printf("L");
		} if(strcmp(buffer, "pyy") == 0 || strcmp(buffer, "PYY") == 0 || strcmp(buffer, "byy") == 0 || strcmp(buffer, "BYY") == 0 || strcmp(buffer, "ctt") == 0 || strcmp(buffer, "CTT") == 0 || strcmp(buffer, "cuu") == 0 || strcmp(buffer, "CUU") == 0){
			printf("L");
		} if(strcmp(buffer, "pyp") == 0 || strcmp(buffer, "PYP") == 0 || strcmp(buffer, "byb") == 0 || strcmp(buffer, "BYB") == 0 || strcmp(buffer, "ctc") == 0 || strcmp(buffer, "CTC") == 0 || strcmp(buffer, "cuc") == 0 || strcmp(buffer, "CUC") == 0){
			printf("L");
		} if(strcmp(buffer, "pyo") == 0 || strcmp(buffer, "PYO") == 0 || strcmp(buffer, "byo") == 0 || strcmp(buffer, "BYO") == 0 || strcmp(buffer, "pyr") == 0 || strcmp(buffer, "PYR") == 0 || strcmp(buffer, "byr") == 0 || strcmp(buffer, "BYR") == 0 || strcmp(buffer, "cta") == 0 || strcmp(buffer, "CTA") == 0 || strcmp(buffer, "cua") == 0 || strcmp(buffer, "CUA") == 0){
			printf("L");
		} if(strcmp(buffer, "pyg") == 0 || strcmp(buffer, "PYG") == 0 || strcmp(buffer, "byg") == 0 || strcmp(buffer, "bYG") == 0 || strcmp(buffer, "cug") == 0 || strcmp(buffer, "CUG") == 0 || strcmp(buffer, "ctg") == 0 || strcmp(buffer, "CTG") == 0){
			printf("L");
		} if(strcmp(buffer, "oyy") == 0 || strcmp(buffer, "OYY") == 0 || strcmp(buffer, "ryy") == 0 || strcmp(buffer, "RYY") == 0 || strcmp(buffer, "auu") == 0 || strcmp(buffer, "AUU") == 0 || strcmp(buffer, "att") == 0 || strcmp(buffer, "ATT") == 0){
			printf("I");
		} if(strcmp(buffer, "oyp") == 0 || strcmp(buffer, "OYP") == 0 || strcmp(buffer, "oyb") == 0 || strcmp(buffer, "OYB") == 0 || strcmp(buffer, "ryp") == 0 || strcmp(buffer, "RYP") == 0 || strcmp(buffer, "ryb") == 0 || strcmp(buffer, "RYB") == 0 || strcmp(buffer, "atc") == 0 || strcmp(buffer, "ATC") == 0 || strcmp(buffer, "auc") == 0 || strcmp(buffer, "AUC") == 0){
			printf("I");
		} if(strcmp(buffer, "oyo") == 0 || strcmp(buffer, "OYO") == 0 || strcmp(buffer, "ryr") == 0 || strcmp(buffer, "RYR") == 0 || strcmp(buffer, "aua") == 0 || strcmp(buffer, "AUA") == 0 || strcmp(buffer, "ata") == 0 || strcmp(buffer, "ATA") == 0){
			printf("I");
		} if(strcmp(buffer, "oyg") == 0 || strcmp(buffer, "OYG") == 0 || strcmp(buffer, "ryg") == 0 || strcmp(buffer, "RYG") == 0 || strcmp(buffer, "aug") == 0 || strcmp(buffer, "AUG") == 0 || strcmp(buffer, "atg") == 0 || strcmp(buffer, "ATG") == 0){
			printf(" - M - ");
		} if(strcmp(buffer, "gyy") == 0 || strcmp(buffer, "GYY") == 0 || strcmp(buffer, "guu") == 0 || strcmp(buffer, "GUU") == 0 || strcmp(buffer, "gtt") == 0 || strcmp(buffer, "GTT") == 0){
			printf("V");
		} if(strcmp(buffer, "gyp") == 0 || strcmp(buffer, "GYP") == 0 || strcmp(buffer, "gyb") == 0 || strcmp(buffer, "GYB") == 0 || strcmp(buffer, "guc") == 0 || strcmp(buffer, "GUC") == 0 || strcmp(buffer, "gtc") == 0 || strcmp(buffer, "GTC") == 0){
			printf("V");
		} if(strcmp(buffer, "gyo") == 0 || strcmp(buffer, "GYO") == 0 || strcmp(buffer, "gyr") == 0 || strcmp(buffer, "GYR") == 0 || strcmp(buffer, "gua") == 0 || strcmp(buffer, "GUA") == 0 || strcmp(buffer, "gta") == 0 || strcmp(buffer, "GTA") == 0){
			printf("V");
		} if(strcmp(buffer, "gyg") == 0 || strcmp(buffer, "GYG") == 0 || strcmp(buffer, "gug") == 0 || strcmp(buffer, "GUG") == 0 || strcmp(buffer, "gtg") == 0 || strcmp(buffer, "GTG") == 0){
			printf("V");
		} if(strcmp(buffer, "ypy") == 0 || strcmp(buffer, "YPY") == 0 || strcmp(buffer, "yby") == 0 || strcmp(buffer, "YBY") == 0 || strcmp(buffer, "ucu") == 0 || strcmp(buffer, "UCU") == 0 || strcmp(buffer, "tct") == 0 || strcmp(buffer, "TCT") == 0){
			printf("S");
		} if(strcmp(buffer, "ypp") == 0 || strcmp(buffer, "YPP") == 0 || strcmp(buffer, "ybb") == 0 || strcmp(buffer, "YBB") == 0 || strcmp(buffer, "ucc") == 0 || strcmp(buffer, "UCC") == 0 || strcmp(buffer, "tcc") == 0 || strcmp(buffer, "TCC") == 0){
			printf("S");
		} if(strcmp(buffer, "ypo") == 0 || strcmp(buffer, "YPO") == 0 || strcmp(buffer, "ybo") == 0 || strcmp(buffer, "YBO") == 0 || strcmp(buffer, "ypr") == 0 || strcmp(buffer, "YPR") == 0 || strcmp(buffer, "ybr") == 0 || strcmp(buffer, "YBR") == 0 || strcmp(buffer, "uca") == 0 || strcmp(buffer, "UCA") == 0 || strcmp(buffer, "tca") == 0 || strcmp(buffer, "TCA") == 0){
			printf("S");
		} if(strcmp(buffer, "ypg") == 0 || strcmp(buffer, "YPG") == 0 || strcmp(buffer, "ybg") == 0 || strcmp(buffer, "YBG") == 0 || strcmp(buffer, "ucg") == 0 || strcmp(buffer, "UCG") == 0 || strcmp(buffer, "tcg") == 0 || strcmp(buffer, "TCG") == 0){
			printf("S");
		} if(strcmp(buffer, "ppy") == 0 || strcmp(buffer, "PPY") == 0 || strcmp(buffer, "bby") == 0 || strcmp(buffer, "BBY") == 0 || strcmp(buffer, "ccu") == 0 || strcmp(buffer, "CCU") == 0 || strcmp(buffer, "cct") == 0 || strcmp(buffer, "CCT") == 0){
			printf("P");
		} if(strcmp(buffer, "ppp") == 0 || strcmp(buffer, "PPP") == 0 || strcmp(buffer, "bbb") == 0 || strcmp(buffer, "BBB") == 0 || strcmp(buffer, "ccc") == 0 || strcmp(buffer, "CCC") == 0){
			printf("P");
		} if(strcmp(buffer, "ppo") == 0 || strcmp(buffer, "PPO") == 0 || strcmp(buffer, "bbo") == 0 || strcmp(buffer, "BBO") == 0 || strcmp(buffer, "ppr") == 0 || strcmp(buffer, "PPR") == 0 || strcmp(buffer, "bbr") == 0 || strcmp(buffer, "BBR") == 0 || strcmp(buffer, "cca") == 0 || strcmp(buffer, "CCA") == 0){
			printf("P");
		} if(strcmp(buffer, "ppg") == 0 || strcmp(buffer, "PPG") == 0 || strcmp(buffer, "bbg") == 0 || strcmp(buffer, "BBG") == 0 || strcmp(buffer, "ccg") == 0 || strcmp(buffer, "CCG") == 0){
			printf("P");
		} if(strcmp(buffer, "opy") == 0 || strcmp(buffer, "OPY") == 0 || strcmp(buffer, "oby") == 0 || strcmp(buffer, "OBY") == 0 || strcmp(buffer, "rpy") == 0 || strcmp(buffer, "RPY") == 0 || strcmp(buffer, "rby") == 0 || strcmp(buffer, "RBY") == 0 || strcmp(buffer, "acu") == 0 || strcmp(buffer, "ACU") == 0 || strcmp(buffer, "act") == 0 || strcmp(buffer, "ACT") == 0){
			printf("T");
		} if(strcmp(buffer, "opp") == 0 || strcmp(buffer, "OPP") == 0 || strcmp(buffer, "obb") == 0 || strcmp(buffer, "OBB") == 0 || strcmp(buffer, "rpp") == 0 || strcmp(buffer, "RPP") == 0 || strcmp(buffer, "rbb") == 0 || strcmp(buffer, "RBB") == 0 || strcmp(buffer, "acc") == 0 || strcmp(buffer, "ACC") == 0){
			printf("T");
		} if(strcmp(buffer, "opo") == 0 || strcmp(buffer, "OPO") == 0 || strcmp(buffer, "obo") == 0 || strcmp(buffer, "OBO") == 0 || strcmp(buffer, "rpr") == 0 || strcmp(buffer, "RPR") == 0 || strcmp(buffer, "rbr") == 0 || strcmp(buffer, "RBR") == 0 || strcmp(buffer, "aca") == 0 || strcmp(buffer, "ACA") == 0){
			printf("T");
		} if(strcmp(buffer, "opg") == 0 || strcmp(buffer, "OPG") == 0 || strcmp(buffer, "obg") == 0 || strcmp(buffer, "OBG") == 0 || strcmp(buffer, "rpg") == 0 || strcmp(buffer, "RPG") == 0 || strcmp(buffer, "rbg") == 0 || strcmp(buffer, "RBG") == 0 || strcmp(buffer, "acg") == 0 || strcmp(buffer, "ACG") == 0){
			printf("T");
		} if(strcmp(buffer, "gpy") == 0 || strcmp(buffer, "GPY") == 0 || strcmp(buffer, "gby") == 0 || strcmp(buffer, "GBY") == 0 || strcmp(buffer, "gcu") == 0 || strcmp(buffer, "GCU") == 0 || strcmp(buffer, "gct") == 0 || strcmp(buffer, "GCT") == 0){
			printf("A");
		} if(strcmp(buffer, "gpp") == 0 || strcmp(buffer, "GPP") == 0 || strcmp(buffer, "gbb") == 0 || strcmp(buffer, "GBB") == 0 || strcmp(buffer, "gcc") == 0 || strcmp(buffer, "GCC") == 0){
			printf("A");
		} if(strcmp(buffer, "gpo") == 0 || strcmp(buffer, "GPO") == 0 || strcmp(buffer, "gbo") == 0 || strcmp(buffer, "GBO") == 0 || strcmp(buffer, "gpr") == 0 || strcmp(buffer, "GPR") == 0 || strcmp(buffer, "gbr") == 0 || strcmp(buffer, "GBR") == 0 || strcmp(buffer, "gca") == 0 || strcmp(buffer, "GCA") == 0){
			printf("A");
		} if(strcmp(buffer, "gpg") == 0 || strcmp(buffer, "GPG") == 0 || strcmp(buffer, "gbg") == 0 || strcmp(buffer, "GBG") == 0 || strcmp(buffer, "gcg") == 0 || strcmp(buffer, "GCG") == 0){
			printf("A");
		} if(strcmp(buffer, "yoy") == 0 || strcmp(buffer, "YOY") == 0 || strcmp(buffer, "yry") == 0 || strcmp(buffer, "YRY") == 0 || strcmp(buffer, "uau") == 0 || strcmp(buffer, "UAU") == 0 || strcmp(buffer, "tat") == 0 || strcmp(buffer, "TAT") == 0){
			printf("Y");
		} if(strcmp(buffer, "yop") == 0 || strcmp(buffer, "YOP") == 0 || strcmp(buffer, "yob") == 0 || strcmp(buffer, "YOB") == 0 || strcmp(buffer, "yrp") == 0 || strcmp(buffer, "YRP") == 0 || strcmp(buffer, "yrb") == 0 || strcmp(buffer, "YRB") == 0 || strcmp(buffer, "uac") == 0 || strcmp(buffer, "UAC") == 0 || strcmp(buffer, "tac") == 0 || strcmp(buffer, "TAC") == 0){
			printf("Y");
		} if(strcmp(buffer, "yoo") == 0 || strcmp(buffer, "YOO") == 0 || strcmp(buffer, "yrr") == 0 || strcmp(buffer, "YRR") == 0 || strcmp(buffer, "uaa") == 0 || strcmp(buffer, "UAA") == 0 || strcmp(buffer, "taa") == 0 || strcmp(buffer, "TAA") == 0){
			printf(" STOP ");
		} if(strcmp(buffer, "yog") == 0 || strcmp(buffer, "YOG") == 0 || strcmp(buffer, "yrg") == 0 || strcmp(buffer, "YRG") == 0 || strcmp(buffer, "uag") == 0 || strcmp(buffer, "UAG") == 0 || strcmp(buffer, "tag") == 0 || strcmp(buffer, "TAG") == 0){
			printf(" STOP ");
		} if(strcmp(buffer, "poy") == 0 || strcmp(buffer, "POY") == 0 || strcmp(buffer, "boy") == 0 || strcmp(buffer, "BOY") == 0 || strcmp(buffer, "pry") == 0 || strcmp(buffer, "PRY") == 0 || strcmp(buffer, "bry") == 0 || strcmp(buffer, "BRY") == 0 || strcmp(buffer, "cau") == 0 || strcmp(buffer, "CAU") == 0 || strcmp(buffer, "cat") == 0 || strcmp(buffer, "CAT") == 0){
			printf("H");
		} if(strcmp(buffer, "pop") == 0 || strcmp(buffer, "POP") == 0 || strcmp(buffer, "bob") == 0 || strcmp(buffer, "BOB") == 0 || strcmp(buffer, "prp") == 0 || strcmp(buffer, "PRP") == 0 || strcmp(buffer, "brb") == 0 || strcmp(buffer, "BRB") == 0 || strcmp(buffer, "cac") == 0 || strcmp(buffer, "CAC") == 0){
			printf("H");
		} if(strcmp(buffer, "poo") == 0 || strcmp(buffer, "POO") == 0 || strcmp(buffer, "boo") == 0 || strcmp(buffer, "BOO") == 0 || strcmp(buffer, "prr") == 0 || strcmp(buffer, "PRR") == 0 || strcmp(buffer, "brr") == 0 || strcmp(buffer, "BRR") == 0 || strcmp(buffer, "caa") == 0 || strcmp(buffer, "CAA") == 0){
			printf("Q");
		} if(strcmp(buffer, "pog") == 0 || strcmp(buffer, "POG") == 0 || strcmp(buffer, "bog") == 0 || strcmp(buffer, "BOG") == 0 || strcmp(buffer, "prg") == 0 || strcmp(buffer, "PRG") == 0 || strcmp(buffer, "brg") == 0 || strcmp(buffer, "BRG") == 0 || strcmp(buffer, "cag") == 0 || strcmp(buffer, "CAG") == 0){
			printf("Q");
		} if(strcmp(buffer, "ooy") == 0 || strcmp(buffer, "OOY") == 0 || strcmp(buffer, "rry") == 0 || strcmp(buffer, "RRY") == 0 || strcmp(buffer, "aau") == 0 || strcmp(buffer, "AAU") == 0 || strcmp(buffer, "aat") == 0 || strcmp(buffer, "AAT") == 0){
			printf("N");
		} if(strcmp(buffer, "oop") == 0 || strcmp(buffer, "OOP") == 0 || strcmp(buffer, "oob") == 0 || strcmp(buffer, "OOB") == 0 || strcmp(buffer, "rrp") == 0 || strcmp(buffer, "RRP") == 0 || strcmp(buffer, "rrb") == 0 || strcmp(buffer, "RRB") == 0 || strcmp(buffer, "aac") == 0 || strcmp(buffer, "AAC") == 0){
			printf("N");
		} if(strcmp(buffer, "ooo") == 0 || strcmp(buffer, "OOO") == 0 || strcmp(buffer, "rrr") == 0 || strcmp(buffer, "RRR") == 0 || strcmp(buffer, "aaa") == 0 || strcmp(buffer, "AAA") == 0){
			printf("K");
		} if(strcmp(buffer, "oog") == 0 || strcmp(buffer, "OOG") == 0 || strcmp(buffer, "rrg") == 0 || strcmp(buffer, "RRG") == 0 || strcmp(buffer, "aag") == 0 || strcmp(buffer, "AAG") == 0){
			printf("K");
		} if(strcmp(buffer, "goy") == 0 || strcmp(buffer, "GOY") == 0 || strcmp(buffer, "gry") == 0 || strcmp(buffer, "GRY") == 0 || strcmp(buffer, "gau") == 0 || strcmp(buffer, "GAU") == 0 || strcmp(buffer, "gat") == 0 || strcmp(buffer, "GAT") == 0){
			printf("D");
		} if(strcmp(buffer, "gop") == 0 || strcmp(buffer, "GOP") == 0 || strcmp(buffer, "gob") == 0 || strcmp(buffer, "GOB") == 0 || strcmp(buffer, "grp") == 0 || strcmp(buffer, "GRP") == 0 || strcmp(buffer, "grb") == 0 || strcmp(buffer, "GRB") == 0 || strcmp(buffer, "gac") == 0 || strcmp(buffer, "GAC") == 0){
			printf("D");
		} if(strcmp(buffer, "goo") == 0 || strcmp(buffer, "GOO") == 0 || strcmp(buffer, "grr") == 0 || strcmp(buffer, "GRR") == 0 || strcmp(buffer, "gaa") == 0 || strcmp(buffer, "GAA") == 0){
			printf("E");
		} if(strcmp(buffer, "gog") == 0 || strcmp(buffer, "GOG") == 0 || strcmp(buffer, "grg") == 0 || strcmp(buffer, "GRG") == 0 || strcmp(buffer, "gag") == 0 || strcmp(buffer, "GAG") == 0){
			printf("E");
		} if(strcmp(buffer, "ygy") == 0 || strcmp(buffer, "YGY") == 0 || strcmp(buffer, "ugu") == 0 || strcmp(buffer, "UGU") == 0 || strcmp(buffer, "tgt") == 0 || strcmp(buffer, "TGT") == 0){
			printf("C");
		} if(strcmp(buffer, "ygp") == 0 || strcmp(buffer, "YGP") == 0 || strcmp(buffer, "ygb") == 0 || strcmp(buffer, "YGB") == 0 || strcmp(buffer, "ugc") == 0 || strcmp(buffer, "UGC") == 0 || strcmp(buffer, "tgc") == 0 || strcmp(buffer, "TGC") == 0){
			printf("C");
		} if(strcmp(buffer, "ygo") == 0 || strcmp(buffer, "YGO") == 0 || strcmp(buffer, "ygr") == 0 || strcmp(buffer, "YGR") == 0 || strcmp(buffer, "uga") == 0 || strcmp(buffer, "UGA") == 0 || strcmp(buffer, "tga") == 0 || strcmp(buffer, "TGA") == 0){
			printf(" STOP ");
		} if(strcmp(buffer, "ygg") == 0 || strcmp(buffer, "YGG") == 0 || strcmp(buffer, "ugg") == 0 || strcmp(buffer, "UGG") == 0 || strcmp(buffer, "tgg") == 0 || strcmp(buffer, "TGG") == 0){
			printf("W");
		} if(strcmp(buffer, "pgy") == 0 || strcmp(buffer, "PGY") == 0 || strcmp(buffer, "bgy") == 0 || strcmp(buffer, "BGY") == 0 || strcmp(buffer, "cgu") == 0 || strcmp(buffer, "CGU") == 0 || strcmp(buffer, "cgt") == 0 || strcmp(buffer, "CGT") == 0){
			printf("R");
		} if(strcmp(buffer, "pgp") == 0 || strcmp(buffer, "PGP") == 0 || strcmp(buffer, "bgb") == 0 || strcmp(buffer, "BGB") == 0 || strcmp(buffer, "cgc") == 0 || strcmp(buffer, "CGC") == 0){
			printf("R");
		} if(strcmp(buffer, "pgo") == 0 || strcmp(buffer, "PGO") == 0 || strcmp(buffer, "bgo") == 0 || strcmp(buffer, "BGO") == 0 || strcmp(buffer, "pgr") == 0 || strcmp(buffer, "PGR") == 0 || strcmp(buffer, "bgr") == 0 || strcmp(buffer, "BGR") == 0 || strcmp(buffer, "cga") == 0 || strcmp(buffer, "CGA") == 0){
			printf("R");
		} if(strcmp(buffer, "pgg") == 0 || strcmp(buffer, "PGG") == 0 || strcmp(buffer, "bgg") == 0 || strcmp(buffer, "BGG") == 0 || strcmp(buffer, "cgg") == 0 || strcmp(buffer, "CGG") == 0){
			printf("R");
		} if(strcmp(buffer, "ogy") == 0 || strcmp(buffer, "OGY") == 0 || strcmp(buffer, "rgy") == 0 || strcmp(buffer, "RGY") == 0 || strcmp(buffer, "agu") == 0 || strcmp(buffer, "AGU") == 0 || strcmp(buffer, "agt") == 0 || strcmp(buffer, "AGT") == 0){
			printf("S");
		} if(strcmp(buffer, "ogp") == 0 || strcmp(buffer, "OGP") == 0 || strcmp(buffer, "ogb") == 0 || strcmp(buffer, "OGB") == 0 || strcmp(buffer, "rgp") == 0 || strcmp(buffer, "RGP") == 0 || strcmp(buffer, "rgb") == 0 || strcmp(buffer, "RGB") == 0 || strcmp(buffer, "agc") == 0 || strcmp(buffer, "AGC") == 0){
			printf("S");
		} if(strcmp(buffer, "ogo") == 0 || strcmp(buffer, "OGO") == 0 || strcmp(buffer, "rgr") == 0 || strcmp(buffer, "RGR") == 0 || strcmp(buffer, "aga") == 0 || strcmp(buffer, "AGA") == 0){
			printf("R");
		} if(strcmp(buffer, "ogg") == 0 || strcmp(buffer, "OGG") == 0 || strcmp(buffer, "rgg") == 0 || strcmp(buffer, "RGG") == 0 || strcmp(buffer, "agg") == 0 || strcmp(buffer, "AGG") == 0){
			printf("R");
		} if(strcmp(buffer, "ggy") == 0 || strcmp(buffer, "GGY") == 0 || strcmp(buffer, "ggu") == 0 || strcmp(buffer, "GGU") == 0 || strcmp(buffer, "ggt") == 0 || strcmp(buffer, "GGT") == 0){
			printf("G");
		} if(strcmp(buffer, "ggp") == 0 || strcmp(buffer, "GGP") == 0 || strcmp(buffer, "ggb") == 0 || strcmp(buffer, "GGB") == 0 || strcmp(buffer, "ggc") == 0 || strcmp(buffer, "GGC") == 0){
			printf("G");
		} if(strcmp(buffer, "ggo") == 0 || strcmp(buffer, "GGO") == 0 || strcmp(buffer, "ggr") == 0 || strcmp(buffer, "GGR") == 0 || strcmp(buffer, "gga") == 0 || strcmp(buffer, "GGA") == 0){
			printf("G");
		} if(strcmp(buffer, "ggg") == 0 || strcmp(buffer, "GGG") == 0){
			printf("G");
		} else{
			printf(" ");
		}
	}
	printf("\n");
}


void debacon(char *string, int btype){
	char buffer[6];
	int i = 0;

	while(string[i] != '\0'){

		buffer[0] = string[i];
		i++;
		buffer[1] = string[i];
		i++;
		buffer[2] = string[i];
		i++;
		buffer[3] = string[i];
		i++;
		buffer[4] = string[i];
		buffer[5] = '\0';
		i+=2;

		if(btype == 0){
			if(strcmp(buffer, "00000") == 0){
				printf("A");
			} else if(strcmp(buffer, "00001") == 0){
				printf("B");
			} else if(strcmp(buffer, "00010") == 0){
				printf("C");
			} else if(strcmp(buffer, "00011") == 0){
				printf("D");
			} else if(strcmp(buffer, "00100") == 0){
				printf("E");
			} else if(strcmp(buffer, "00101") == 0){
				printf("F");
			} else if(strcmp(buffer, "00110") == 0){
				printf("G");
			} else if(strcmp(buffer, "00111") == 0){
				printf("H");
			} else if(strcmp(buffer, "01000") == 0){
				printf("J");
			} else if(strcmp(buffer, "01001") == 0){
				printf("K");
			} else if(strcmp(buffer, "01010") == 0){
				printf("L");
			} else if(strcmp(buffer, "01011") == 0){
				printf("M");
			} else if(strcmp(buffer, "01100") == 0){
				printf("N");
			} else if(strcmp(buffer, "01101") == 0){
				printf("O");
			} else if(strcmp(buffer, "01110") == 0){
				printf("P");
			} else if(strcmp(buffer, "01111") == 0){
				printf("Q");
			} else if(strcmp(buffer, "10000") == 0){
				printf("R");
			} else if(strcmp(buffer, "10001") == 0){
				printf("S");
			} else if(strcmp(buffer, "10010") == 0){
				printf("T");
			} else if(strcmp(buffer, "10011") == 0){
				printf("V");
			} else if(strcmp(buffer, "10100") == 0){
				printf("W");
			} else if(strcmp(buffer, "10101") == 0){
				printf("X");
			} else if(strcmp(buffer, "10110") == 0){
				printf("Y");
			} else if(strcmp(buffer, "10111") == 0){
				printf("Z");
			} else{
				printf(" ");
			}
		}
		if(btype == 1){
			if(strcmp(buffer, "00000") == 0){
				printf("A");
			} else if(strcmp(buffer, "00001") == 0){
				printf("B");
			} else if(strcmp(buffer, "00010") == 0){
				printf("C");
			} else if(strcmp(buffer, "00011") == 0){
				printf("D");
			} else if(strcmp(buffer, "00100") == 0){
				printf("E");
			} else if(strcmp(buffer, "00101") == 0){
				printf("F");
			} else if(strcmp(buffer, "00110") == 0){
				printf("G");
			} else if(strcmp(buffer, "00111") == 0){
				printf("H");
			} else if(strcmp(buffer, "01000") == 0){
				printf("I");
			} else if(strcmp(buffer, "01001") == 0){
				printf("J");
			} else if(strcmp(buffer, "01010") == 0){
				printf("K");
			} else if(strcmp(buffer, "01011") == 0){
				printf("L");
			} else if(strcmp(buffer, "01100") == 0){
				printf("M");
			} else if(strcmp(buffer, "01101") == 0){
				printf("N");
			} else if(strcmp(buffer, "01110") == 0){
				printf("O");
			} else if(strcmp(buffer, "01111") == 0){
				printf("P");
			} else if(strcmp(buffer, "10000") == 0){
				printf("Q");
			} else if(strcmp(buffer, "10001") == 0){
				printf("R");
			} else if(strcmp(buffer, "10010") == 0){
				printf("S");
			} else if(strcmp(buffer, "10011") == 0){
				printf("T");
			} else if(strcmp(buffer, "10100") == 0){
				printf("U");
			} else if(strcmp(buffer, "10101") == 0){
				printf("V");
			} else if(strcmp(buffer, "10110") == 0){
				printf("W");
			} else if(strcmp(buffer, "10111") == 0){
				printf("X");
			} else if(strcmp(buffer, "11000") == 0){
				printf("Y");
			} else if(strcmp(buffer, "11001") == 0){
				printf("Z");
			} else{
				printf(" ");
			}
		}
	}
	printf("\n");
}

void xors(char* string1, char* string2){
	int j = strlen(string2);
	int k = 0;
	char* i;

	for(i=string1; *i; i++){
		if(k >= j){
			k = 0;
		}
	        if(*i == '0' && string2[k] == '0'){
        	        *i = '0';
                } else if(*i == '0' && string2[k] == '1'){
                        *i = '1';
                } else if(*i == '1' && string2[k] == '0'){
                        *i = '1';
                } else if(*i == '1' && string2[k] == '1'){
                        *i = '0';
                }
		k++;
	}
}
