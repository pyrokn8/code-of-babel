char* randomsearch(mpz_t *seed) {
    unsigned long long i = randull();
    return searchwithkey(i, seed);
}