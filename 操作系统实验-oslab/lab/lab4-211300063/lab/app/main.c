#include "lib.h"
#include "types.h"

// 一些用于控制测试的宏 main.c
// #define TEST_SCANF  // 测试scanf
// #define TEST_SEM	// 测试信号量
// #define TEST_PHI_EATING  // 测试哲学家进餐问题
// #define TEST_PC_PROBLEM  // 测试生产者-消费者问题
#define TEST_WR_PROBLEM  // 测试读者-写着问题


/********************哲学家进餐*********************/

#ifdef TEST_PHI_EATING
#define N 5
sem_t forks[N];

void philosopher();
void test_philosopher();

void philosopher() { 
	int i = get_pid() - 1;
	while (1) {
		if (i % 2 == 0) {
			sem_wait(&forks[i]);
			sleep(128);
			sem_wait(&forks[(i + 1) % N]);
		}
		else {
			sem_wait(&forks[(i + 1) % N]);
			sleep(128);
			sem_wait(&forks[i]);
		}
		printf("Philosopher %d: eat\n", i);
		sleep(128); // eat
		printf("Philosopher %d: think\n", i);
		sem_post(&forks[i]);
		sleep(128);
		sem_post(&forks[(i + 1) % N]);
		sleep(128); // think
	}
}

void test_philosopher() {
	for (int i = 0; i < N; ++i)
		sem_init(&forks[i], 1);
	for (int i = 0; i < N - 1; ++i) {	
		int ret = fork();
		if (ret == -1) {
			printf("create %d philosopher error!\n", i);
			exit();
		}
		if (ret == 0) { // child process 
			philosopher();
			exit();
		} 
	}
	philosopher();
	for (int i = 0; i < N; ++i)
		sem_destroy(&forks[i]);
}
#endif

/********************************************************/



/********************生产者-消费者问题*********************/

#ifdef TEST_PC_PROBLEM
#define NR_P 4
sem_t mutex;
sem_t full;
sem_t empty;

void producer(sem_t *mutex, sem_t *empty, sem_t *full);
void consumer(sem_t *mutex, sem_t *empty, sem_t *full);
void producer_comsumer();

void producer(sem_t *mutex, sem_t *empty, sem_t *full) {
	int id = get_pid() - 1;
	while (1) {
		sem_wait(empty);
		sleep(128);
		sem_wait(mutex);
		sleep(128);
		printf("Producer %d: produce\n", id);
		sleep(128);
		sem_post(mutex);
		sleep(128);
		sem_post(full);
		sleep(128);
	}
}

void consumer(sem_t *mutex, sem_t *empty, sem_t *full) {
	while (1) {
		sem_wait(full);
		sleep(128);
		sem_wait(mutex);
		sleep(128);
		printf("Consumer: consume\n");
		sleep(128);
		sem_post(mutex);
		sleep(128);
		sem_post(empty);
		sleep(128);
	}
}

void producer_comsumer() {
	sem_init(&mutex, 1);
	sem_init(&full, 0);
	sem_init(&empty, 3);

	for (int i = 0; i < NR_P; i ++) {
		int ret = fork();
		if (ret == -1) {
			printf("create %d producer error!\n", i);
			exit();
		} 
		if (ret == 0) {	
			producer(&mutex, &empty, &full);
			// exit();
		} else {
			printf("create producer process: %d\n", ret - 1);
		}
	}
	consumer(&mutex, &empty, &full);

}
#endif

/********************************************************/



/********************读者-写者问题*********************/

#ifdef TEST_WR_PROBLEM
#define N 3
sem_t writemutex, countmutex, rcount;

void writer(sem_t *writeMutex);
void reader(sem_t *rcount, sem_t *writemutex, sem_t *countmutex);
void reader_writer();

void writer(sem_t *writeMutex) {
	int pid = get_pid();
	while(1) {
		sem_wait(writeMutex);
		// sleep(128);
		printf("Writer pid=%d: write\n", pid);
		sleep(128);
		sem_post(writeMutex);
		sleep(128);
	}
}



void reader(sem_t *rcount, sem_t *writemutex, sem_t *countmutex) {
	int id = get_pid();
	int count;
	while (1) {
		sem_wait(countmutex);
		count = sem_read(rcount);
		if (count == 0) {
			sem_wait(writemutex);
		}
		sem_inc(rcount);
		sem_post(countmutex);
		printf("Reader pid=%d: read\n", id);
		sleep(128);
		count = sem_read(rcount);
		printf("Reader pid=%d: stop read, there are %d reader\n", id, count - 1);
		sem_wait(countmutex);
		sem_dec(rcount);
		count = sem_read(rcount);
		if (count == 0) {
			printf("There is no reader!\n");
			sem_post(writemutex);
		}
		sem_post(countmutex);
		sleep(128);
	}
}


void reader_writer() {
	sem_init(&writemutex, 1);
	sem_init(&countmutex, 1);
	sem_init(&rcount, 0);
	
	int ret;
	for (int i = 0; i < N; i++) {
		ret = fork();
		if (ret == -1) {
			printf("create writer %d error!\n", i);
			exit();
		}
		if (ret == 0) {
			writer(&writemutex);
			exit();
		} else {
			printf("create writer, pid = %d\n", ret);
		}
	}
	for (int i = 0; i < N - 1; i++) {
		ret = fork();
		if (ret == -1) {
			printf("create reader %d error!\n", i);
			exit();
		}
		if (ret == 0) {
			reader(&rcount, &writemutex, &countmutex);
			exit();
		} else {
			printf("create reader, pid = %d\n", ret);
		}
	}
	reader(&rcount, &writemutex, &countmutex);
}
#endif

int uEntry(void) {
	// For lab4.1
	// Test 'scanf' 
#ifdef TEST_SCANF
	int ret = 0;
	int dec = 0;
	int hex = 0;
	char str[6];
	char cha = 0;
	while(1){
		printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
		ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
		printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
		if (ret == 4)
			break;
	}
#endif

	// For lab4.2
	// Test 'Semaphore'
#ifdef TEST_SEM
	int i = 4;

	sem_t sem;
	printf("Father Process: Semaphore Initializing.\n");
	int ret = sem_init(&sem, 2);
	if (ret == -1) {
		printf("Father Process: Semaphore Initializing Failed.\n");
		exit();
	}

	ret = fork();
	if (ret == 0) { // 子进程
		while( i != 0) {
			i --;
			printf("Child Process: Semaphore Waiting.\n");
			sem_wait(&sem);
			printf("Child Process: In Critical Area.\n");
		}
		printf("Child Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
	else if (ret != -1) {  // 父进程
		while( i != 0) {
			i --;
			printf("Father Process: Sleeping.\n");
			sleep(128);
			printf("Father Process: Semaphore Posting.\n");
			sem_post(&sem);
		}
		printf("Father Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
#endif
	// For lab4.3
	// TODO: You need to design and test the philosopher problem.
	// Producer-Consumer problem and Reader& Writer Problem are optional.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.

#ifdef TEST_PHI_EATING
	test_philosopher();
#endif
	// test_producer_consumer();

#ifdef TEST_PC_PROBLEM
	producer_comsumer();
#endif

#ifdef TEST_WR_PROBLEM
	reader_writer();
#endif
	return 0;
}
