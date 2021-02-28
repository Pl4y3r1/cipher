#include "cyphers.h"

int main(int argc, char* argv[]){
	FILE* scram;
	int opt;
	int fcheck = 0;
	int nflag = 0;
	int btype = 0;
	int bitflip = 0;
	char** line = malloc(sizeof(char *) * 16);
	int i = 0;
	int j = 0;
	int k = 0;
	size_t len = 0;
	int ntot = 0;
	char* buffer;
	char* bitstring;
	char* temp;
	int runBacon = 0;
	int runHex = 0;
	int xorit = 0;
	int runDNA = 0;
	int runRNA = 0;
	int verbose = 0;

	while((opt = getopt(argc, argv, "hvf:a:n:i:x:HBDR")) != -1){
		switch(opt){
			case 'h':
				printf("\nUSAGE: ./decode -f path_to_input_file type_of_decode options\n");
				printf("OPTIONS: -f [FILENAME] to specify input file\n");
				printf("OPTIONS: -v for verbose mode\n");
				printf("OPTIONS: -a [a or b] to specify which type of bacon alphebet (Bacon Cypher Only)\n");
				printf("OPTIONS: -n [0 or 1 or 2 or 3] to specify how the bitstring should be read\n");
				printf("OPTIONS: -i [t or f] to specify how 0's and 1's are read from the bitstring\n");
				printf("OPTIONS: -x [bitstring] to xor bits with given bitstring\n");
				printf("OPTIONS: -B for Bacon Cypher\n");
				printf("OPTIONS: -H for HEX conversion\n");
				printf("OPTIONS: -D for DNA RNA Stop Codon Cypher Version 1 (Provide Bases or Flame Colors)\n");
				printf("OPTIONS: -R for DNA RNA Stop Codon Cypher Version 2 (Flame Pairs Only)\n");
				printf("OPTIONS: -h displays this menu\n");
				printf("\nEXAMPLE: ./decode -f file -B -a b -n 2 -i f -v\n");
				exit(EXIT_SUCCESS);
			case 'f':
				scram = fopen(optarg, "r");
				fcheck = 1;
				break;
			case 'v':
				printf("\nTurning on Verbose Mode...\n");
				verbose = 1;
				break;
			case 'a':
				if(optarg[0] == 'a' || optarg[0] == 'A'){
					btype = 0;
				} else if(optarg[0] == 'b' || optarg[0] == 'B'){
					btype = 1;
				} else{
					printf("\nERROR: Invalid argument for for -a option, must be a or b\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'n':
				if(atoi(optarg) < 4){
					nflag = atoi(optarg);
				} else{
					printf("\nERROR: Invalid argument for -n option, must be 0, 1, 2, or 3\n");
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
					printf("\nERROR: Cannot run Bacon Cypher and Hex conversion together\n");
					exit(EXIT_FAILURE);
				} else if(runDNA == 1 || runRNA == 1){
					printf("\nERROR: Cannot run Bacon Cypher and DNA RNA conversion together\n");
					exit(EXIT_FAILURE);
				} else{
					runBacon = 1;
				}
				break;
			case 'H':
				if(runBacon == 1){
					printf("\nERROR: Cannot run Bacon Cypher and Hex conversion together\n");
					exit(EXIT_FAILURE);
				} else if(runDNA== 1 || runRNA == 1){
					printf("\nERROR: Cannot run DNA RNA Cypher and Hex conversion together\n");
					exit(EXIT_FAILURE);
				} else{
					runHex = 1;
				}
				break;
			case 'D':
				if(runHex == 1){
					printf("\nERROR: Cannot run Hex conversion and DNA RNA Cypher together\n");
					exit(EXIT_FAILURE);
				} else if(runBacon == 1){
					printf("\nERROR: Cannot run Bacon Cypher and DNA RNA Cypher together\n");
					exit(EXIT_FAILURE);
				} else if(runRNA == 1){
					printf("\nERROR: Cannot run both versions of DNA RNA Cypher together\n");
					exit(EXIT_FAILURE);
				} else{
					runDNA = 1;
				}
				break;
			case 'R':
				if(runHex == 1){
					printf("\nERROR: Cannot run Hex conversion and DNA RNA Cypher together\n");
					exit(EXIT_FAILURE);
				} else if(runBacon == 1){
					printf("\nERROR: Cannot run Bacon Cypher and DNA RNA Cypher together\n");
					exit(EXIT_FAILURE);
				} else if(runDNA == 1){
					printf("\nERROR: Cannot run both versions of DNA RNA Cypher together\n");
					exit(EXIT_FAILURE);
				} else{
					runRNA = 1;
				}
				break;
			default:
				printf("ERROR: Unrecognized option, try -h\n");
				exit(EXIT_FAILURE);
		}
	}

	if(fcheck == 0){
		printf("ERROR: Must specify input file, try -h\n");
		exit(EXIT_FAILURE);
	} else if(argc <= 3){
		printf("ERROR: Must specify -H, -B, -D or -R.., try -h for help\n");
	}

	i = getlines(scram, &line, &ntot, len);

	if(verbose == 1){
		for(j = 0; j < i; j++){
			printf("line %i is: %s\n", j, line[j]);
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
				printf("\nDNA RNA Cypher Decode\n");
			}
			deRNA(buffer);
			shift(buffer, verbose);
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

	for(j = 0; j < i; j++){
        	if(verbose == 1){
                	printf("Normalizeing line %i\n", j);
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
	fclose(scram);
	free(buffer);
	free(temp);
	return 0;
}
