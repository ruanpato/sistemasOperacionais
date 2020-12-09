#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define MAX_NAME_LENGTH 30
#define AMOUNT_OF_PHILOSOPHERS_NAMES 101

typedef struct philosopher {
    int id;
    char name[MAX_NAME_LENGTH];
    pthread_t thread;
} tp_philosopher;

tp_philosopher philosophers[AMOUNT_OF_PHILOSOPHERS_NAMES];
sem_t desk; // Semaphore 
sem_t forks[AMOUNT_OF_PHILOSOPHERS_NAMES]; // Forks semaphore (used instead mutexes)
int amount_of_philosophers=0, philosophers_eating=0, 
philosopher_already_eat=0, flag_read=0, phil_max=0;
char philosophers_names[AMOUNT_OF_PHILOSOPHERS_NAMES][MAX_NAME_LENGTH] = {
    "A. J. Ayer",
    "Adolf Grünbaum",
    "Alasdair MacIntyre",
    "Alice Crary",
    "Alvin Plantinga",
    "Antony Flew",
    "Aristotle",
    "Barry Stroud",
    "Bas van Fraassen",
    "Bernard Williams",
    "Bertrand Russell",
    "Carl Gustav Hempel",
    "Charles Taylor",
    "Charlie Broad",
    "Christine Korsgaard",
    "Confucius",
    "Cora Diamond",
    "Daniel Dennett",
    "David Chalmers",
    "David Hume",
    "David Lewis",
    "Derek Parfit",
    "Donald Davidson",
    "Ernest Nagel",
    "Ernest Sosa",
    "Frank P. Ramsey",
    "Friedrich Nietzsche",
    "G. E. M. Anscombe",
    "G. E. Moore",
    "Georg Wilhelm Friedrich Hegel",
    "Gilbert Ryle",
    "Gottlob Frege",
    "Graham Priest",
    "Hans Reichenbach",
    "Hilary Putnam",
    "Ian Hacking",
    "Immanuel Kant",
    "J. J. C. Smart",
    "J. L. Austin",
    "J. L. Mackie",
    "Jaegwon Kim",
    "James F. Conant",
    "Jean-Jacques Rousseau",
    "Jean-Paul Sartre",
    "Jerry Fodor",
    "John Locke",
    "John McDowell",
    "John Rawls",
    "John Searle",
    "John Stuart Mill",
    "Karl Marx",
    "Karl Popper",
    "Keith Donnellan",
    "Kurt Gödel",
    "Lao-Tzu",
    "Ludwig Wittgenstein",
    "Ludwig Wittgenstein",
    "Martin Heidegger",
    "Max Stirner",
    "Michael Dummett",
    "Michael Walzer",
    "Michel Foucault",
    "Mikhail Bakunin",
    "Moritz Schlick",
    "Nelson Goodman",
    "Niccolo Machiavelli",
    "Nicholas Rescher",
    "Noam Chomsky",
    "Norman Malcolm",
    "Otto Neurath",
    "P. F. Strawson",
    "Patricia Churchland",
    "Paul Churchland",
    "Paul Feyerabend",
    "Paul Grice",
    "Peter Geach",
    "Peter Singer",
    "Peter van Inwagen",
    "Philippa Foot",
    "Plato",
    "R. M. Hare",
    "Ralph Waldo Emerson",
    "René Descartes",
    "Richard Rorty",
    "Richard Swinburne",
    "Robert Audi",
    "Robert Brandom",
    "Robert Nozick",
    "Roderick Chisholm",
    "Rudolf Carnap",
    "Ruth Millikan",
    "Saul Kripke",
    "Socrates",
    "Søren Kierkegaard",
    "Theodor W. Adorno",
    "Thomas Aquinas",
    "Thomas Kuhn",
    "Thomas Nagel",
    "Timothy Williamson",
    "W. V. O. Quine",
    "Wilfrid Sellars"
};

void clean_screen();
void * philosopher(void *);
void randomize ();
void swap(int i, int j);

int main() {

    do {
        clean_screen();
        if (flag_read == 1)
            printf("Type a valid value: [2, %d].\n", AMOUNT_OF_PHILOSOPHERS_NAMES);
        printf("Please type the amount of philosophers:\n-> ");
        flag_read=1;
        scanf("%d", &amount_of_philosophers);
    } while(amount_of_philosophers < 2 || amount_of_philosophers > AMOUNT_OF_PHILOSOPHERS_NAMES);

    randomize();

	// Initialize Desk capacity
	sem_init(&desk, 0, (amount_of_philosophers-1));
	
    // Set fork states
	for(int i=0; i < amount_of_philosophers; i++) sem_init(&forks[i],0,1); 
	
    // Create Philosophers threads
	for(int i=0; i < amount_of_philosophers; i++) {
        philosophers[i].id = i;
        strcpy(philosophers[i].name, philosophers_names[i]);
		pthread_create(&philosophers[i].thread,NULL,philosopher,(void *)&philosophers[i]);
	}

    // Wait for threads terminates
	for(int i = 0; i < amount_of_philosophers; i++)
        pthread_join(philosophers[i].thread, NULL);

    printf("\n[INFO]     ! PHILOSOPHERS ALREADY EAT: %d\n", philosopher_already_eat);
    printf("[INFO]     ! PHILOSOPHERS EATING AT SAME TIME: %d\n", phil_max);
}

void clean_screen() {
	#ifdef WIN32
		system("cls");
	#endif
		system("clear");
}

void eat(tp_philosopher actual_philosopher) {
    // Eating
    printf("[INFO]     ! PHILOSOPHERS EATING: %d\n", ++philosophers_eating);
    phil_max = phil_max > philosophers_eating ? phil_max : philosophers_eating;
	printf("[EATING]   @ {%d} %s IS EATING\n", actual_philosopher.id, actual_philosopher.name);

	sleep(2); // Sleep to "fill" the thread
	printf("[FINISHED] # {%d} %s HAS FINISHED EATING\n", actual_philosopher.id, actual_philosopher.name);
    --philosophers_eating;
    ++philosopher_already_eat;
}

void take_forks(tp_philosopher actual_philosopher) {
	sem_wait(&forks[actual_philosopher.id]); // Get the left fork 
	sem_wait(&forks[(actual_philosopher.id+1)%amount_of_philosophers]); // Get the right fork
}

void think(tp_philosopher actual_philosopher) {
	sem_wait(&desk); // Change desk semaphore ('ll "get forks")
	printf("[THINKING] - {%d} %s IS THINKING\n", actual_philosopher.id, actual_philosopher.name);
}

void put_forks(tp_philosopher actual_philosopher) {
	sem_post(&desk); // Change desk semaphore ('ll "give back forks")
	sem_post(&forks[(actual_philosopher.id+1)%amount_of_philosophers]); // Put on desk the right fork
	sem_post(&forks[actual_philosopher.id]); // Put on desk the left fork
}

void * philosopher(void * philosopher) {
	tp_philosopher actual_philosopher=*(tp_philosopher *)philosopher;

    think(actual_philosopher);

    take_forks(actual_philosopher);

    eat(actual_philosopher);

    put_forks(actual_philosopher);
}

// Code bellow this line was extracted from:
// https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
void randomize () {
    int i, j;
    // Use a different seed value so that  
    // we don't get same result each time 
    // we run this program 
    srand (time(NULL));  
  
    // Start from the last element and swap  
    // one by one. We don't need to run for  
    // the first element that's why i > 0  
    for (i = (AMOUNT_OF_PHILOSOPHERS_NAMES - 1); i > 0; i--) {
        // Pick a random index from 0 to i
        j = (rand() % (i + 1))%AMOUNT_OF_PHILOSOPHERS_NAMES;
        // Swap arr[i] with the element
        // at random index
        swap(i, j);
    }  
}

void swap(int i, int j) { 
    char temp[MAX_NAME_LENGTH];
    strcpy(temp, philosophers_names[i]);
    strcpy(philosophers_names[i], philosophers_names[j]);
    strcpy(philosophers_names[j], temp);
}
