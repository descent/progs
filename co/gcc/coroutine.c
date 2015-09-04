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
 * Coroutine Source Code 
 * author:    Sunneo.IceCold
 * email:     sunneo529@hotmail.com
 * homepage:  http://sunneo.myweb.hinet.net
 */
#include "coroutine.h"
#include <setjmp.h>
#include <stdlib.h>


#define PRIVATE static 
PRIVATE Coroutine* co_cur = 0;
PRIVATE const unsigned int cosize = sizeof(Coroutine);
PRIVATE const unsigned int longsize = sizeof(long);

PRIVATE 
void CALLBACK def_routine(void* param){
    
}

PRIVATE
void copy_memory(unsigned char* dest,const unsigned char* src,unsigned int size){
   while(size>=4) {
      *(unsigned long*)dest = *(unsigned long*)src;
      dest +=  longsize;
      src += longsize;
      size -= 4;
   }
   while(size--) {
      *(unsigned char*)dest++ = *(unsigned char*)src++;
   }
}

#define STATUS_NEW 0
#define STATUS_READY 1
#define STATUS_TERMINATED 2

EXPORT 
Coroutine* co_current(){
   return co_cur;
}

EXPORT 
Coroutine* co_create( CallBackRoutine fn ,void* param){
   Coroutine* co = (Coroutine*)malloc(cosize);
   co->stack.buf = 0;
   co->stack.size = 0;
   co->status = 0;
   co->fn = fn;
   co->param = param;
   return co;
}

EXPORT 
void co_start( Coroutine* co ){
   unsigned char* p;
   co->stack.bp = (unsigned char*)&p;
   co->status = STATUS_READY;
   co->caller = co_cur ? co_cur : co_create(def_routine,0);
   if(!setjmp(co->caller->ctx) ){
      co_cur = co;
      co->fn(co->param);
      co_terminate() ;
   }
}

EXPORT 
void co_pause(){
   unsigned char* p = ((unsigned char*)&p) - 4;
   unsigned int stksize = (unsigned int)(co_cur->stack.bp - p);
   co_cur->stack.sp = p;
   switch( (unsigned long)co_cur->stack.buf ){
      default:
        if(co_cur->stack.size >= stksize ) break;
        free(co_cur->stack.buf);
      case 0:
        co_cur->stack.size = stksize;
        co_cur->stack.buf = (unsigned char*)malloc(stksize);
        break;
   }
   if(!setjmp(co_cur->ctx) ) {
      copy_memory(co_cur->stack.buf,p,stksize);
      co_cur = co_cur->caller;
      longjmp(co_cur->ctx,1);
   }
   copy_memory(co_cur->stack.sp,co_cur->stack.buf,co_cur->stack.size);
}

EXPORT 
void co_resume( Coroutine* co ){
   switch(co->status){
      case STATUS_NEW:
         co_start(co);
      case STATUS_TERMINATED:
         return;
      default:
         if( !setjmp(co_cur->ctx) ){
            co_cur = co;
            longjmp(co_cur->ctx,1);
         }
   }
}

EXPORT 
void co_terminate2( Coroutine* co ){
   co->status = STATUS_TERMINATED;
   free(co->stack.buf);
   co->stack.size = 0;
   co_cur = co->caller;
   longjmp(co_cur->ctx,1);
}

EXPORT 
void co_terminate(){
   co_cur->status = STATUS_TERMINATED;
   free(co_cur->stack.buf);
   co_cur->stack.size = 0;
   co_cur = co_cur->caller;
   longjmp(co_cur->ctx,1);
}

EXPORT 
int co_terminated( Coroutine* co ){
   return co->status == STATUS_TERMINATED;
}

EXPORT 
void co_delete( Coroutine* co ){
   if( co->stack.buf ) free( co->stack.buf );
   free(co);
}
