#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
#include "cyphers.h"

int main(int argc, char** argv){
	int c;
	int fcheck = 0;
	int abcCheck = 0;
	int abflag = 0;
	int nflag = 0;
	int btype = 0;
	int bitflip = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int ntot = 0;
	int runBacon = 0;
	int runHex = 0;
	int xorit = 0;
	int runDNA = 0;
	int runRNA = 0;
	int verbose = 0;
	char* buffer;
	char* bitstring;
	char* temp;
	char** alphabet;
	char** line = malloc(sizeof(char *) * 16);
	size_t len = 0;
	FILE* scram;
 
	if(argc >= 2){
		while((c = getopt(argc, argv, "hd:vf:F:a:n:i:x:HBDRA")) != -1){
			switch(c){
				case 'h':
					printf("Usage: ./decrypt -f path_to_input_file type_of_decode options\n\n\n");
					printf("OPTIONS: -f [FILENAME]      - Input File\n");
					printf("OPTIONS: -h                 - Help\n");
					printf("OPTIONS: -d                 - Decrypt Using All Methods (Brute Force)\n");
					printf("OPTIONS: -A                 - Decrypt Using AtBash\n");
					printf("OPTIONS: -v                 - Verbose Mode\n");
					printf("OPTIONS: -a [a or b]        - Select Bacon Alphabet\n");
					printf("OPTIONS: -n [0, 1, 2, or 3] - Bitstring read mode\n");
					printf("OPTIONS: -i [t or f]        - 0/1 read mode\n");
					printf("OPTIONS: -x [bitstring]     - xor with Bitstring\n");
					printf("OPTIONS: -B                 - Decrypt Bacon Cipher\n");
					printf("OPTIONS: -H                 - Hex Conversion\n");
					printf("OPTIONS: -D                 - DNA RNA STOP Codon Cipher V1\n");
					printf("OPTIONS: -R                 - DNA RNA STOP Codon Cipher V2\n\n\n");
					printf("EXAMPLE: ./decrypt -f [FILENAME] -B -a b -n 2 -i f -v\n");
					exit(EXIT_SUCCESS);
					break;
				case 'd':
					break;
				case 'A':
					if(fcheck == 0 || abcCheck == 0){
						printf("ERROR, Need encrypted text as well as alphabet to run AtBash cipher\n");
						exit(EXIT_FAILURE);
					} else{
						abflag = 1;
					}
					break;
				case 'f':
					scram = fopen(optarg, "r");
					fcheck = 1;
					break;
				case'F':
					alphabet = atbash(fopen(optarg, "r"));
					abcCheck = 1;
					break;
				case 'v':
					printf("\nTurning on Verbose Mode ... \n");
					verbose = 1;
					break;
				case 'a':
					if(optarg[0] == 'a' || optarg[0] == 'A'){
						btype = 0;
					} else if (optarg[0] == 'b' || optarg[0] == 'B'){
						btype = 1;
					} else{
						printf("\nERROR: Invalid argument for -a option, must be a or b\n");
						exit(EXIT_FAILURE);
					}
					break;
				case 'n':
					if(atoi(optarg) < 4){
						nflag = atoi(optarg);
					} else{
						printf("\nERROR: Invalid argument for -n option, must be 0, 1, 2, or 3\n");
						exit(EXIT_FAILURE);
					}
					break;
				case 'i':
					if(optarg[0] == 't' || optarg[0] == 'T'){
						bitflip = 1;
					}
					break;
				case 'x':
					xorit = 1;
					bitstring = malloc(sizeof(char*) * strlen(optarg));
					strcpy(bitstring, optarg);
					break;
				case 'B':
					if(runHex == 1){
						printf("\nERROR: Cannot run Bacon Cipher and Hex conversion together\n");
						exit(EXIT_FAILURE);
					} else if(runDNA == 1 || runRNA == 1){
						printf("\nERROR: Cannot run Bacon Cipher and DNA/RNA conversion together\n");
						exit(EXIT_FAILURE);
					} else{
						runBacon = 1;
					}
					break;
				case 'H':
					if(runBacon == 1){
						printf("\nERROR: Cannot run Bacon Cipher and Hex conversion together\n");
						exit(EXIT_FAILURE);
					} else if(runDNA == 1 || runRNA == 1){
						printf("\nERROR: Cannot run DNA/RNA Cipher and Hex conversion together\n");
						exit(EXIT_FAILURE);
					} else{
						runHex = 1;
					}
					break;
				case 'D':
					if(runHex == 1){
						printf("\nERROR: Cannot run Hex conversion and DNA/RNA Cipher together\n");
						exit(EXIT_FAILURE);
					} else if(runBacon == 1){
						printf("\nERROR: Cannot run Bacon Cipher and DNA/RNA Cipher together\n");
						exit(EXIT_FAILURE);
					} else if(runRNA == 1){
						printf("\nERROR: Cannot run both versions of DNA/RNA Cipher together\n");
						exit(EXIT_FAILURE);
					} else{
						runDNA = 1;
					}
					break;
				case 'R':
					if(runHex == 1){
						printf("\nERROR: Cannot run Hex conversion and DNA/RNA Cipher together\n");
						exit(EXIT_FAILURE);
					} else if(runBacon == 1){
						printf("\nERROR: Cannot run Bacon Cipher and DNA/RNA Cipher together\n");
						exit(EXIT_FAILURE);
					} else if(runDNA == 1){
						printf("\nERROR: Cannot run both versions of DNA/RNA Cipher together\n");
						exit(EXIT_FAILURE);
					} else{
						runRNA = 1;
					}
					break;
				case '?':
//					if(optopt == 'c'){
//						fprintf(stderr, "Option -%c requires an argument.\n", optopt);
//					} else 
					if(isprint (optopt)){
						fprintf(stderr, "Unknown option '-%c'.\n", optopt);
					} else{
						fprintf(stderr, "Unknown option character\n");
						exit(1);
					}
				default:
					exit(1);
			}
		}
	} else{
		printf("No Inputs Detected, Exiting...\n");
		exit(1);
	}
	if(fcheck == 0){
		printf("ERROR: Must specify input file, try -h\n");
		exit(EXIT_FAILURE);
	} else if(argc <= 3){
		printf("ERROR: Must specify -H, -B, -D, or -R.., try -h for help\n");
	}

	i = getlines(scram, &line, &ntot, len);

	if(verbose == 1){
		for(j = 0; j < i; j++){
			printf("line %i is: %s\n", j, line[i]);
		}
		printf("Total Characters Read: %i\n\n", ntot);
		j = 0;
	}

	buffer = malloc(sizeof(char) * ntot * 5);
	temp = malloc(sizeof(char) * ntot * 5);

	if(runDNA == 1){
		for(j = 0; j < i; j++){
			line[j] = normalize(line[j], 8);
		}
		j = 1;
		strcpy(buffer, line[0]);
		for(j = 1; j < i; j++){
			strcat(buffer, line[j]);
		}

		if(verbose == 1){
			printf("\nCombined String: %s\n", buffer);
		}

		for(k = 0; k <= strlen(buffer); k++){
			divideString(buffer, 3);
			if(verbose == 1){
				printf("\nString split into 3's for decoding:\n");
				printf("%s\n", buffer);
				printf("\nDNA RNA Cipher Decode\n");
			}
			deRNA(buffer);
			shift(buffer, verbose);
		}
		for(j = 0; j <=i; j++){
			free(line[i]);
		}
		free(line);
		free(buffer);
		free(temp);
		if(xorit == 1){
			free(bitstring);
		}
		fclose(scram);
		return 0;
	} else if(runRNA == 1){
		for(j = 0; j < i; j++){
			line[j] = normalize(line[j], 8);
		}
		j = 1;
		strcpy(buffer, line[0]);
		for(j = 1; j < i; j++){
			strcat(buffer, line[j]);
		}
		for(j = 0; j <= i; j++){
			free(line[j]);
		}
		free(line);
		free(buffer);
		free(temp);
		if(xorit == 1){
			free(bitstring);
		}
		fclose(scram);
		return 0;
	}

	for(j = 0; j< i; j++){
		if(verbose == 1){
			printf("Normalizing line %i\n", j);
		}
		if(bitflip == 1){
			flip(line[j]);
		}
		line[j] = normalize(line[j], nflag);
		if(verbose == 1){
			printf("Line %i is now: %s\n", j, line[j]);
		}
	}

	j = 1;
	strcpy(buffer, line[0]);
	for(j = 1; j < i; j++){
		strcat(buffer, line[j]);
	}

	if(verbose == 1){
		printf("\nCombined String: %s\n", buffer);
	}

	if(xorit == 1){
		if(verbose == 1){
			printf("XORING with %s\n", bitstring);
		}
		xors(buffer, bitstring);
		if(verbose == 1){
			printf("Resulting string %s\n", buffer);
		}
	}

	if(runBacon == 1){
		for(k = 0; k <= strlen(buffer); k++){
			divideString(buffer, 5);
			if(verbose == 1){
				printf("\nString split into 5's for decoding:\n");
				printf("%s\n", buffer);
				printf("\nDebaconing:\n");
			}
			debacon(buffer, btype);
			shift(buffer, verbose);
		}
	}

	if(runHex == 1){
		for(k = 0; k <= strlen(buffer); k++){
			if(strlen(buffer)%4 != 0){
				switch(strlen(buffer)%4){
					case 1:
						temp[0] = '0';
						temp[1] = '0';
						temp[2] = '0';
						temp[3] = '\0';
						strcat(temp, buffer);
						break;
					case 2:
						temp[0] = '0';
						temp[1] = '0';
						temp[2] = '\0';
						strcat(temp, buffer);
						break;
					case 3:
						temp[0] = '0';
						temp[1] = '\0';
						strcat(temp, buffer);
						break;
					default:
						printf("Something bad happened...\n");
						break;
				}
			} else{
				strcpy(temp, buffer);
			}
			divideString(temp, 4);
			if(verbose == 1){
				printf("\nString split into 4's\n");
				printf("%s\n", temp);
				printf("\nConverting to Hex:\n");
			}
			deHex(temp);
			clean(temp, verbose);
			shift(buffer, verbose);
		}
	}
	j = 0;
	for(j = 0; j <= i; j++){
		free(line[j]);
	}
	free(line);
	if(xorit == 1){
		free(bitstring);
	}
	if(abflag == 1){
		free(alphabet);
	}
	fclose(scram);
	free(buffer);
	free(temp);
	return 0;
}
