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

#ifndef _KDATA_H
#define _KDATA_H

#include "KDB.h"
#include "KPrecursor.h"
#include "KSpectrum.h"
#include "MSReader.h"
#include <iostream>

class KData {
public:

  KData();
  KData(kParams* p);
  ~KData();

  KSpectrum& operator[ ](const int& i);
  KSpectrum& at(const int& i);
  KSpectrum* getSpectrum(const int& i);

  bool      getBoundaries     (double mass1, double mass2, vector<int>& index);
  bool      getBoundaries2    (double mass, double prec, vector<int>& index);
  kLinker&  getLink           (int i);
  double    getMaxMass        ();
  double    getMinMass        ();
  bool      mapPrecursors     ();
  bool      outputPercolator  (FILE* f, KDatabase& db, kResults& r, int count);
  bool      outputResults     (KDatabase& db);
  bool      outputResults2    (KDatabase& db);
  void      readLinkers       (char* fn);
  bool      readSpectra       ();
  void      setLinker         (kLinker x);
  void      setVersion        (char* v);
  int       size              ();
  int       sizeLink          ();
  void      xCorr             (bool b);

private:

  //Data Members
  char               version[32];
  vector<KSpectrum>  spec;
  vector<kLinker>    link;
  vector<kMass>      massList;
  kParams*           params;

  //Utilities
  void        centroid          (Spectrum& s, Spectrum& out, double resolution, int instrument=0);
  void        collapseSpectrum  (Spectrum& s);
  static int  compareInt        (const void *p1, const void *p2);
  static int  compareMassList   (const void *p1, const void *p2);
  int         getCharge         (Spectrum& s, int index, int next);
  double      polynomialBestFit (vector<double>& x, vector<double>& y, vector<double>& coeff, int degree=2);

};


#endif
