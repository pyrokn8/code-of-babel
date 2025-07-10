char* randomsearch(mpz_t *seed, bool decompile, bool store) {
    unsigned long long i = randull();
    return searchwithkey(i, seed, decompile, store);
}