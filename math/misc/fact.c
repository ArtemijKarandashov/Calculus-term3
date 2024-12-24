#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 100

typedef struct {
    int key;
    long long value;
} CacheUnit;

CacheUnit fact_cache[CACHE_SIZE];
int cache_size = 0;

long long 
cache_get(int key){
    for(int i = 0; i < cache_size; i++) {
        if (fact_cache[i].key == key) {
            return fact_cache[i].value;
        }
    }
    return -1;
}

void cache_add(int key, long long value){
    if (cache_size < CACHE_SIZE){
        fact_cache[cache_size].key = key;
        fact_cache[cache_size].value = value;
        cache_size++;
    }
}

long long
factorial (int n){
    if (n<0) return -1;
    if (n==0 || n == 1) return 1;

    long long cached_value = cache_get(n);
    if (cached_value != -1){
        return cached_value;
    }

    long long result = n * factorial(n-1);

    cache_add(n,result);
    return result;
}

