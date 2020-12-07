#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(void) {
	int val;
	int val2;
	// expect in_illuminance_input is fixed point number: e.g. 8.400000
	char *input = "/sys/bus/iio/devices/iio:device0/in_illuminance_input";
	char *output = "/sys/class/backlight/backlight/brightness";
	FILE *in;
	FILE *out;

	while(1) {

		in = fopen(input, "r");
		if(in == NULL){
			perror("Error open input file");
			exit(EXIT_FAILURE);
		}
		
		int count = fscanf(in, "%d.%d", &val, &val2);
		if (count == 1){
			val2 = 0;
		}
		fclose(in);

		out = fopen(output, "w");
		if(out == NULL){
			perror("Error open output file");
			exit(EXIT_FAILURE);
		}

		if(val == 0 && val2 == 0){
			fprintf(out, "%d", 500);
		}
		else if(val < 500){
			fprintf(out, "%d", 2000);
		}
		else if(val < 1000 || (val == 1000 && val2 == 0)){
			fprintf(out, "%d", 3999);
		}

		fclose(out);
		sleep(1);		
		
	}
	return EXIT_SUCCESS;
}
