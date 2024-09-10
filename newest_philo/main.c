#include "philo.h"

#define NUM_PHILOSOPHERS 200
#define NUM_MEALS 4

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t print_mutex;

void* philosopher_routine(void* arg) {
    int id = *(int*)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    int meals_eaten = 0;

    while (meals_eaten < NUM_MEALS) {
        // Thinking
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is thinking\n", id);
        pthread_mutex_unlock(&print_mutex);
        usleep(10000);

        // Pick up forks
        if (left_fork < right_fork) {
            pthread_mutex_lock(&forks[left_fork]);
            pthread_mutex_lock(&forks[right_fork]);
        } else {
            pthread_mutex_lock(&forks[right_fork]);
            pthread_mutex_lock(&forks[left_fork]);
        }

        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is eating\n", id);
        pthread_mutex_unlock(&print_mutex);
        usleep(10000);
        meals_eaten++;

        // Put down forks
        if (left_fork < right_fork) {
            pthread_mutex_unlock(&forks[right_fork]);
            pthread_mutex_unlock(&forks[left_fork]);
        } else {
            pthread_mutex_unlock(&forks[left_fork]);
            pthread_mutex_unlock(&forks[right_fork]);
        }

        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is putting down forks\n", id);
        pthread_mutex_unlock(&print_mutex);
    }

    pthread_mutex_lock(&print_mutex);
    printf("Philosopher %d has finished eating\n", id);
    pthread_mutex_unlock(&print_mutex);
    return NULL;
}

int main(void) {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    pthread_mutex_init(&print_mutex, NULL);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher_routine, &ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&print_mutex);

    return 0;
}
