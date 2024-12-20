
/*IMPORTANT*/
/*to compile: gcc mcarlo.c -o mcarlo -lpthread -lm */

#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int total_hit_count = 0;
double x, y;

double random_double();
void *hit_first_half(void *arg);
void *hit_second_half(void *arg);

int main(int argc, char*argv[]){

	int num_args;
	int result;
        double pi_estimate;

	/*make sure the number of arguments entered is correct*/
	if (argc != 2) {
        	printf("Invalid number of arguments\n");
        	return -1;
    	}

	if (atoi(argv[1]) < 0) {
        	printf("Error: The number of points must be a valid positive integer.\n");
        	return -1;
    	}

	/*if the input is an odd number, I add one to it so the threads have an even number of points to generate, more is better because it's more precise */
	if(atoi(argv[1]) % 2 == 0){
		num_args = atoi(argv[1])/2;
	} else {
		num_args = (atoi(argv[1]) + 1)/2 ;
	}

	pthread_t hit1_tid, hit2_tid;

	result = pthread_create(&hit1_tid, NULL, hit_first_half, &num_args);
	if (result != 0){
		printf("error creating calc_avg thread \n");
		return -1;
	}

	result = pthread_create(&hit2_tid, NULL, hit_second_half, &num_args);
        if (result != 0){
                printf("error creating calc_avg thread \n");
                return -1;
        }

	pthread_join(hit1_tid, NULL);
	pthread_join(hit2_tid, NULL);

	pi_estimate = 4.0 * total_hit_count / atoi(argv[1]);
	printf("the estimation of pi is: %f\n", pi_estimate);

	return 0;
}

void *hit_first_half(void *arg){
	int hit_count = 0;
	int npoints = *(int *)arg;
	/* Check for points inside circle*/
	for (int i = 0; i < npoints; i++) {
	/* generate random numbers between -1.0 and +1.0 (exclusive) */
		x = random_double() * 2.0 - 1.0;
		y = random_double() * 2.0 - 1.0;
		if (sqrt(x*x + y*y) < 1.0 )
		++hit_count;
	}

	total_hit_count += hit_count;

	pthread_exit(0);


}

void *hit_second_half(void *arg){
	int hit_count = 0;
        int npoints = *(int *)arg;
        /* Check for points inside circle*/
        for (int i = 0; i < npoints; i++) {
        /* generate random numbers between -1.0 and +1.0 (exclusive) */
                x = random_double() * 2.0 - 1.0;
                y = random_double() * 2.0 - 1.0;
                if (sqrt(x*x + y*y) < 1.0 )
                ++hit_count;
        }

	total_hit_count += hit_count;
        pthread_exit(0);


}

/* Generates a double precision random number */
double random_double(){

	return random() / ((double)RAND_MAX + 1);
}
