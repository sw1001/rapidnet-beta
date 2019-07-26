/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
materialize(emission,infinity,infinity,keys(1,2:str,3:str,4:real)).
materialize(transition,infinity,infinity,keys(1,2:str,3:str,4:real)).
materialize(observation,infinity,infinity,keys(1,2:str,3:int32)).
materialize(matrixTemp,infinity,infinity,keys(1,2:str,3:str,4:int32,5:real)).
materialize(maxProb,infinity,infinity,keys(1,2:str,3:str,4:int32,5:real)).
materialize(shaResult,infinity,infinity,keys(1,2:cid,3:str)).
r1 matrixTemp(@X,ST,OB,N,PM) :- transition(@X,ST,ST0,PT), emission(@X,OB,ST,PE), observation(@X,OB,N), ST0=="START", N==1, PM:=PT*PE.
r2 matrixTemp(@X,ST1,OB1,N1,PM1) :- matrixTemp(@X,ST0,OB0,N,PM), transition(@X,ST1,ST0,PT), emission(@X,OB1,ST1,PE), observation(@X,OB1,N1), ST0!="START", ST1!="END", N1==N+1, PM1:=PM*PT*PE.
r3 matrixTemp(@X,ST1,OB1,N1,PM1) :- matrixTemp(@X,ST0,OB0,N,PM), transition(@X,ST1,ST0,PT), observation(@X,OB1,N1), ST1=="END", OB1=="END", N1==N+1, PM1:=PM*PT.
r4 maxProb(@X,ST,OB,N,PM) :- matrixTemp(@X,ST,OB,N,PM), ST=="END", OB=="END".
sr1 shaResult(@X,VID,Content) :- emission(@X,OB,ST,PE), VID:=f_sha1("emission"+X+","+OB+","+ST+","+PE), Name:="emission", Content:=Name+"("+OB+","+ST+","+PE+")".
sr2 shaResult(@X,VID,Content) :- transition(@X,ST,ST0,PT), VID:=f_sha1("transition"+X+","+ST+","+ST0+","+PT), Name:="transition", Content:=Name+"("+ST+","+ST0+","+PT+")".
sr3 shaResult(@X,VID,Content) :- observation(@X,OB,N), VID:=f_sha1("observation"+X+","+OB+","+N), Name:="observation", Content:=Name+"("+OB+","+N+")".
sr4 shaResult(@X,VID,Content) :- matrixTemp(@X,ST,OB,N,PM), VID:=f_sha1("matrixTemp"+X+","+ST+","+OB+","+N+","+PM), Name:="matrixTemp", Content:=Name+"("+ST+","+OB+","+N+","+PM+")".
sr5 shaResult(@X,VID,Content) :- maxProb(@X,ST,OB,N,PM), VID:=f_sha1("maxProb"+X+","+ST+","+OB+","+N+","+PM), Name:="maxProb", Content:=Name+"("+ST+","+OB+","+N+","+PM+")".
