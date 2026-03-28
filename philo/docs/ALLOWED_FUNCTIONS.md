# ⚡ İzin Verilen Fonksiyonlar — Hızlı Referans

> Bu belge yalnızca kullanılabilecek fonksiyonları içerir. Burada **OLMAYAN** hiçbir fonksiyon kullanılamaz.

---

## Mandatory Part (`philo/`)

### 🧱 Bellek ve I/O

```c
#include <string.h>
void    *memset(void *s, int c, size_t n);

#include <stdlib.h>
void    *malloc(size_t size);
void     free(void *ptr);

#include <stdio.h>
int      printf(const char *format, ...);

#include <unistd.h>
ssize_t  write(int fd, const void *buf, size_t count);
```

### ⏱ Zaman

```c
#include <unistd.h>
int      usleep(useconds_t usec);

#include <sys/time.h>
int      gettimeofday(struct timeval *tv, struct timezone *tz);
```

### 🧵 Thread

```c
#include <pthread.h>
int      pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                        void *(*start_routine)(void *), void *arg);
int      pthread_detach(pthread_t thread);
int      pthread_join(pthread_t thread, void **retval);
```

### 🔒 Mutex

```c
#include <pthread.h>
int      pthread_mutex_init(pthread_mutex_t *mutex,
                            const pthread_mutexattr_t *attr);
int      pthread_mutex_destroy(pthread_mutex_t *mutex);
int      pthread_mutex_lock(pthread_mutex_t *mutex);
int      pthread_mutex_unlock(pthread_mutex_t *mutex);
```

---

## Bonus Part (`philo_bonus/`)

> Mandatory'deki fonksiyonlara **ek olarak** aşağıdakiler kullanılabilir:

### 🔀 Process

```c
#include <unistd.h>
pid_t    fork(void);

#include <signal.h>
int      kill(pid_t pid, int sig);

#include <stdlib.h>
void     exit(int status);

#include <sys/wait.h>
pid_t    waitpid(pid_t pid, int *status, int options);
```

### 🚦 Semaphore

```c
#include <semaphore.h>
sem_t   *sem_open(const char *name, int oflag, ...);
int      sem_close(sem_t *sem);
int      sem_post(sem_t *sem);
int      sem_wait(sem_t *sem);
int      sem_unlink(const char *name);
```

---

## ❌ YASAKLAR

```
❌ Global değişkenler
❌ Yukarıda listelenmeyen fonksiyonlar
❌ libft
❌ Data race
❌ Memory leak
❌ for döngüsü (Norm kuralı)
❌ Fonksiyon içi yorum satırı (Norm kuralı)
```
