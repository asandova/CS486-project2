//
//  sequence.cpp
//  k-assembler
//
//  Created by Joe Song on 12/14/15.
//  Copyright © 2015 Joe Song. All rights reserved.
//
//  Updated 3/19/2018

#include "k-assembler.hpp"

#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

string random_DNA_sequence(size_t min_length=10, size_t max_length=10000)
// generate a DNA sequence of length in the given range
{
    string DNA;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned int> length_dis(min_length, max_length);
    
    // random generate a length
    DNA.resize(length_dis(gen));
    
    // random generate the DNA sequence using alphabet atgc
    uniform_int_distribution<unsigned int> nucleotide_dis(0, 3);
    
    string atgc = "atgc";
    
    for (int n = 0; n < DNA.size(); ++n) {
        DNA[n] = atgc[nucleotide_dis(gen)];
    }
    
    return DNA;
}

vector<string> get_kmers(string seq, size_t k, bool randomized=true)
// obtain all k-mers of a given sequence. The order of the k-mers
//   is randomized by default.
{
    vector<string> kmers(seq.length() - k + 1);
    
    for (size_t i=0; i<kmers.size(); ++i) {
        kmers[i] = seq.substr(i, k);
    }
    
    if (randomized) {
        vector<string> randomized_kmers(kmers.size());
        
        random_device rd;
        mt19937 gen(rd());
        
        size_t nkmers = kmers.size();
        
        for (size_t i=0; i<nkmers-1; ++i) {
            uniform_int_distribution<unsigned int> dis(i, kmers.size()-1);
            size_t j = dis(gen);
            string kmer = kmers[j];
            kmers[j] = kmers[i];
            kmers[i] = kmer;
        }
    }
    
    return kmers;
}

bool compare_spectrum(const string & s1, const string & s2, size_t k)
// compare the canonical spectrum of two sequences. Canonical
//   spectrum is all k-mers arranged in dictionary order.
{
    bool same_spectrum = true;
    
    if (s1.length() != s2.length()) {
        same_spectrum = false;
    } else if(s1 == s2) {
        same_spectrum = true;
    } else {
        auto spectrum1 = get_kmers(s1, k);
        sort(spectrum1.begin(), spectrum1.end());
        auto spectrum2 = get_kmers(s2, k);
        sort(spectrum2.begin(), spectrum2.end());
        same_spectrum = spectrum1 == spectrum2;
    }
    return same_spectrum;
}
