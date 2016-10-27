/* 
   ===============  The GNU Lesser General Public License  =====================
   
     This file is part of Coroutine. 
   Coroutine is free software: you can redistribute it 
   and/or modifyit under the terms of the GNU Lesser Public License as published
   bythe Free Software Foundation, either version 3 of the License, 
   or(at your option) any later version. 
     Coroutine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See theGNU Lesser  Public  License  for 
   more details. 
     You should have received a copy of the GNU Lesser Public Licensealong with
   SMLibrary.If not, see <http://www.gnu.org/licenses/>. 
   
   ============================================================================
*/

/**
 * Coroutine Header 
 * author:    Sunneo.IceCold
 * email:     sunneo529@hotmail.com
 * homepage:  http://sunneo.myweb.hinet.net
 */



#ifndef COROUTINE_H_
#   define COROUTINE_H_
#   include <setjmp.h>

#   if defined( BUILDING_DLL ) & defined( DLLLIB )
#      define EXPORT  __declspec(dllexport)
#   elif defined( DLLLIB )
#      define EXPORT  __declspec(dllimport)
#   else
#      define EXPORT
#   endif 

#   ifdef __cplusplus
#      define EXTERN extern "C" 
#   else
#      define EXTERN extern
#   endif


#   ifndef CALLBACK
#      define CALLBACK 
#   endif

#include <stdio.h>

typedef struct EXPORT RuntimeStack{
   unsigned char* bp,*sp,*buf;
   unsigned int size;
}RuntimeStack;

typedef void (CALLBACK* CallBackRoutine) (void*);
typedef struct EXPORT Coroutine{
   jmp_buf ctx;
   int status;
   CallBackRoutine fn;
   void* param;
   struct Coroutine* caller;
   RuntimeStack stack;
}Coroutine;

EXTERN EXPORT Coroutine* co_create( CallBackRoutine fn ,void* param);
EXTERN EXPORT void co_start( Coroutine* co );
EXTERN EXPORT void co_pause();
EXTERN EXPORT void co_resume( Coroutine* co );
EXTERN EXPORT void co_terminate2( Coroutine* co );
EXTERN EXPORT void co_terminate();
EXTERN EXPORT int co_terminated( Coroutine* co );
EXTERN EXPORT void co_delete( Coroutine* co );
EXTERN EXPORT Coroutine* co_current();

#endif
