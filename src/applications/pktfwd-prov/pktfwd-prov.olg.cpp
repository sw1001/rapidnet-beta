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
materialize(link,infinity,infinity,keys(1,2)).
materialize(path,infinity,infinity,keys(4:list)).
materialize(bestPath,infinity,infinity,keys(1,2)).
materialize(status,infinity,infinity,keys(1)).
materialize(table,infinity,infinity,keys(1,2:int32)).
/* Base Rules */
p1 path(@X,Y,C,P,N) :- link(@X,Y,C),
         P1:=f_append(X),
      P2:=f_append(Y),
      P:=f_concat(P1,P2),
      N:=Y.
p2 path(@Z,Y,C,P,N) :- link(@X,Z,C1),
     bestPath(@X,Y,C2,P2,N1),
    C:=C1+C2,
    f_member(P2,Z)==0,
    P1:=f_append(Z), P:=f_concat(P1,P2),
    N:=X.
p3 bestPath(@X,Y,a_MIN<C>,P,N) :- path(@X,Y,C,P,N).
i0 init(@X,Ind) :- periodic(@X,E,0.01,9000), status(@X), Ind:=f_rand().
i1 eSend(@X,D) :- init(@X,Ind), table(@X,Ind,D).
r0 packet(@X,D,PID,Data) :- eSend(@X,D), Time:=f_now(), PID:=f_sha1(""+Time),
     Data:="0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef".
r1 packet(@N,D,PID,Data) :- packet(@X,D,PID,Data), bestPath(@X,D,C,P,N), X!=D.
