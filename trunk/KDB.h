/*
Copyright 2014, Michael R. Hoopmann, Institute for Systems Biology

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef _KDB_H
#define _KDB_H

#include <iostream>
#include <string>
#include <vector>

#include "KStructs.h"

using namespace std;


class KDatabase{
public:

  //Constructors & Destructors
  KDatabase();

  //Operators
  kDB& operator[ ](const int& i);

  //User Functions
  bool  buildDB       (char* fname);                     //Reads FASTA file and populates vDB
  bool  buildPeptides (double min, double max, int mis); //Make peptide list within mass boundaries and miscleavages.
  void  combo         ();

  //Accessors & Modifiers
  void                addFixedMod         (char mod, double mass);
  kDB&                at                  (const int& i);
  kPeptide&           getPeptide          (int index, bool linkable);
  vector<kPeptide>*   getPeptideList      (bool linkable);
  int                 getPeptideListSize  (bool linkable);
  bool                getPeptideSeq       (int index, int start, int stop, char* str);
  bool                getPeptideSeq       (int index, int start, int stop, string& str);
  bool                getPeptideSeq       (kPeptide& p, string& str);
  kDB&                getProtein          (int index);
  int                 getProteinDBSize    ();
  bool                setEnzyme           (char* str);
  bool                setXLType           (int a=0, int b=0);

private:
  
  //Data Members
  double        AA[128];   //Amino acid masses
  kEnzymeRules  enzyme;    //Where to cut to generate peptides
  int           setA;
  int           setB;

  vector<kDB>      vDB;    //Entire FASTA database stored in memory
  vector<kPeptide> vPep;   //List of all peptides not linkable
  vector<kPeptide> vPepK;  //List of all peptides with a linkable K

  void checkAA(kPeptide& p, int type, int set, int i, int start, int n, int seqSize);

  //Utility functions (for sorting)
  static int compareMass      (const void *p1, const void *p2);
  static int compareSequence  (const void *p1, const void *p2);

};

#endif
