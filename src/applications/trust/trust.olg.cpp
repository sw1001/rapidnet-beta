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
materialize(trust, infinity, infinity, keys(1, 2:int32, 3:int32)).
materialize(trustPath, infinity, infinity, keys(1, 2:int32, 3:int32)).
materialize(trustEvent, infinity, infinity, keys(1, 2:int32, 3:int32)).
materialize(mutualTrustPath, infinity, infinity, keys(1, 2:int32, 3:int32)).
// materialize(shaResult, infinity, infinity, keys(1, 2:cid, 3:str)).
ra 1.0 trustEvent(@Local, P1, P2) :- trustPath(@Local, P1, P2).
r1 1.0 trustPath(@Local, P1, P2) :- trust(@Local, P1, P2).
r2 1.0 trustPath(@Local, P1, P3) :- trust(@Local, P1, P2), trustPath(@Local, P2, P3), P1!=P3.
r3 0.8 mutualTrustPath(@Local, P1, P2) :- trustEvent(@Local, P1, P2), trustPath(@Local, P2, P1).
/*
r4 shaResult(@Local, VID, Content) :- trust(@Local, P1, P2), VID:=f_sha1("trust"+Local+","+P1+","+P2), Name:="trust", Content:=Name+P1+"-"+P2.
r5 shaResult(@Local, VID, Content) :- trustPath(@Local, P1, P2), VID:=f_sha1("trustPath"+Local+","+P1+","+P2), Name:="trustPath", Content:=Name+P1+"-"+P2.
r6 shaResult(@Local, VID, Content) :- trustEvent(@Local, P1, P2), VID:=f_sha1("trustEvent"+Local+","+P1+","+P2), Name:="trustEvent", Content:=Name+P1+"-"+P2.
r7 shaResult(@Local, VID, Content) :- mutualTrustPath(@Local, P1, P2), VID:=f_sha1("mutualTrustPath"+Local+","+P1+","+P2), Name:="mutualTrustPath", Content:=Name+P1+"-"+P2.
*/
