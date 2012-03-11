#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llvm-c/Core.h"
#include "llvm-c/ExecutionEngine.h"
#include "llvm-c/Transforms/Scalar.h"
#include "llvm-c/Transforms/IPO.h"
#include "llvm-c/Target.h"
#include "llvm-c/Initialization.h"
#include "llvm-c/lto.h"
#include "llvm-c/LinkTimeOptimizer.h"
#include "llvm-c/BitWriter.h"
#include "llvm-c/BitReader.h"
#include "llvm-c/EnhancedDisassembly.h"
#include "llvm-c/Analysis.h"
#include "llvm-c/Transforms/PassManagerBuilder.h"
#include "llvm-c/Object.h"
#include "llvm-c/Disassembler.h"

#include "erl_nif.h"

typedef enum {
//  @@TYPES@@
// -- Start generating from Disassembler_8h.xml on {{2012,2,25},{14,37,58}}--

RTLLVMDisasmContextRef,
RTLLVMOpInfoCallback,
RTLLVMSymbolLookupCallback,
// --- Stop generating from Disassembler_8h.xml

// -- Start generating from Core_8h.xml on {{2012,2,25},{14,37,57}}--

RTLLVMAttribute,
RTLLVMOpcode,
RTLLVMTypeKind,
RTLLVMLinkage,
RTLLVMVisibility,
RTLLVMCallConv,
RTLLVMIntPredicate,
RTLLVMRealPredicate,
RTLLVMLandingPadClauseTy,
RTLLVMBool,
RTLLVMContextRef,
RTLLVMModuleRef,
RTLLVMTypeRef,
RTLLVMValueRef,
RTLLVMBasicBlockRef,
RTLLVMBuilderRef,
RTLLVMModuleProviderRef,
RTLLVMMemoryBufferRef,
RTLLVMPassManagerRef,
RTLLVMPassRegistryRef,
RTLLVMUseRef,
// --- Stop generating from Core_8h.xml

// -- Start generating from BitWriter_8h.xml on {{2012,2,25},{14,37,57}}--

// --- Stop generating from BitWriter_8h.xml

// -- Start generating from BitReader_8h.xml on {{2012,2,25},{14,37,57}}--

// --- Stop generating from BitReader_8h.xml

// -- Start generating from Analysis_8h.xml on {{2012,2,25},{14,37,57}}--

RTLLVMVerifierFailureAction,
// --- Stop generating from Analysis_8h.xml

RTVoidPtr
} llvm_type_t;

typedef struct llvm_ptr {
  llvm_type_t type;
  void *value;
} llvm_ptr_t;

// @@RESOURCE_TYPES@@
// -- Start generating from Disassembler_8h.xml on {{2012,2,25},{14,37,58}}--

// --- Stop generating from Disassembler_8h.xml

// -- Start generating from Core_8h.xml on {{2012,2,25},{14,37,58}}--

// --- Stop generating from Core_8h.xml

// -- Start generating from BitWriter_8h.xml on {{2012,2,25},{14,37,57}}--

// --- Stop generating from BitWriter_8h.xml

// -- Start generating from BitReader_8h.xml on {{2012,2,25},{14,37,57}}--

// --- Stop generating from BitReader_8h.xml

// -- Start generating from Analysis_8h.xml on {{2012,2,25},{14,37,57}}--

// --- Stop generating from Analysis_8h.xml

static ErlNifResourceType* module;

static int load_nif(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info) {
  module = enif_open_resource_type(env, "llvm_nif", "module", NULL,
				   ERL_NIF_RT_CREATE, NULL);
  return 0;
}

static int llvm_ptr_deref(ErlNifEnv* env, ERL_NIF_TERM term, void** objp) {
  llvm_ptr_t *ptr;
  enif_get_resource(env, term, module, (void **) &ptr);
  //  printf("fetching %ld\n",(long)ptr->value);
  *objp = ptr->value;
  return 0;
}

static ERL_NIF_TERM llvm_ptr_create(ErlNifEnv* env, llvm_type_t type,
				    void *data) {
  ERL_NIF_TERM term;
  llvm_ptr_t *ptr = (llvm_ptr_t*) enif_alloc_resource(module,
						      sizeof(llvm_ptr_t));

  //  printf("storing %ld\n",(long)data);
  /* initialize struct ... */
  ptr->type = type;
  ptr->value = data;

  term = enif_make_resource(env, ptr);

//  enif_release_resource(ptr);
enif_keep_resource(ptr);
  return term;
}


// @@FUNCTIONS@@
// -- Start generating from Disassembler_8h.xml on {{2012,2,25},{14,37,59}}--

// --- Stop generating from Disassembler_8h.xml

// -- Start generating from Core_8h.xml on {{2012,2,25},{14,37,58}}--

static ERL_NIF_TERM LLVMDisposeMessage_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  char *Message = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[0], (char*)Message, 255, ERL_NIF_LATIN1);

LLVMDisposeMessage((char *)Message);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMContextCreate_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef retVal = LLVMContextCreate();

  return   llvm_ptr_create(env, RTLLVMContextRef, retVal);
}

static ERL_NIF_TERM LLVMGetGlobalContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef retVal = LLVMGetGlobalContext();

  return   llvm_ptr_create(env, RTLLVMContextRef, retVal);
}

static ERL_NIF_TERM LLVMContextDispose_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

LLVMContextDispose((LLVMContextRef)C);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetMDKindIDInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

  unsigned SLen;
  enif_get_uint(env, argv[2], (unsigned*)&SLen);

  unsigned retVal = LLVMGetMDKindIDInContext((LLVMContextRef)C,(const char *)Name,(unsigned)SLen);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetMDKindID_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[0], (char*)Name, 255, ERL_NIF_LATIN1);

  unsigned SLen;
  enif_get_uint(env, argv[1], (unsigned*)&SLen);

  unsigned retVal = LLVMGetMDKindID((const char *)Name,(unsigned)SLen);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMModuleCreateWithName_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  char *ModuleID = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[0], (char*)ModuleID, 255, ERL_NIF_LATIN1);

  LLVMModuleRef retVal = LLVMModuleCreateWithName((const char *)ModuleID);

  return   llvm_ptr_create(env, RTLLVMModuleRef, retVal);
}

static ERL_NIF_TERM LLVMModuleCreateWithNameInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  char *ModuleID = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[0], (char*)ModuleID, 255, ERL_NIF_LATIN1);

  LLVMContextRef C;
  llvm_ptr_deref(env, argv[1], (void **) &C);

  LLVMModuleRef retVal = LLVMModuleCreateWithNameInContext((const char *)ModuleID,(LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMModuleRef, retVal);
}

static ERL_NIF_TERM LLVMDisposeModule_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

LLVMDisposeModule((LLVMModuleRef)M);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetDataLayout_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  const char * retVal = LLVMGetDataLayout((LLVMModuleRef)M);

  return   enif_make_string(env,retVal,ERL_NIF_LATIN1);
}

static ERL_NIF_TERM LLVMSetDataLayout_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *Triple = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Triple, 255, ERL_NIF_LATIN1);

LLVMSetDataLayout((LLVMModuleRef)M,(const char *)Triple);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetTarget_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  const char * retVal = LLVMGetTarget((LLVMModuleRef)M);

  return   enif_make_string(env,retVal,ERL_NIF_LATIN1);
}

static ERL_NIF_TERM LLVMSetTarget_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *Triple = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Triple, 255, ERL_NIF_LATIN1);

LLVMSetTarget((LLVMModuleRef)M,(const char *)Triple);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMDumpModule_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

LLVMDumpModule((LLVMModuleRef)M);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMSetModuleInlineAsm_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *Asm = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Asm, 255, ERL_NIF_LATIN1);

LLVMSetModuleInlineAsm((LLVMModuleRef)M,(const char *)Asm);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetModuleContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMContextRef retVal = LLVMGetModuleContext((LLVMModuleRef)M);

  return   llvm_ptr_create(env, RTLLVMContextRef, retVal);
}

static ERL_NIF_TERM LLVMGetTypeKind_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMTypeKind retVal = LLVMGetTypeKind((LLVMTypeRef)Ty);

  return   enif_make_int(env, (int)retVal);
}

static ERL_NIF_TERM LLVMTypeIsSized_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMBool retVal = LLVMTypeIsSized((LLVMTypeRef)Ty);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMGetTypeContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMContextRef retVal = LLVMGetTypeContext((LLVMTypeRef)Ty);

  return   llvm_ptr_create(env, RTLLVMContextRef, retVal);
}

static ERL_NIF_TERM LLVMInt1TypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMInt1TypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMInt8TypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMInt8TypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMInt16TypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMInt16TypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMInt32TypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMInt32TypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMInt64TypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMInt64TypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMIntTypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  unsigned NumBits;
  enif_get_uint(env, argv[1], (unsigned*)&NumBits);

  LLVMTypeRef retVal = LLVMIntTypeInContext((LLVMContextRef)C,(unsigned)NumBits);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMInt1Type_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMInt1Type();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMInt8Type_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMInt8Type();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMInt16Type_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMInt16Type();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMInt32Type_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMInt32Type();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMInt64Type_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMInt64Type();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMIntType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  unsigned NumBits;
  enif_get_uint(env, argv[0], (unsigned*)&NumBits);

  LLVMTypeRef retVal = LLVMIntType((unsigned)NumBits);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMGetIntTypeWidth_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef IntegerTy;
  llvm_ptr_deref(env, argv[0], (void **) &IntegerTy);

  unsigned retVal = LLVMGetIntTypeWidth((LLVMTypeRef)IntegerTy);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMFloatTypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMFloatTypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMDoubleTypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMDoubleTypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMX86FP80TypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMX86FP80TypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMFP128TypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMFP128TypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMPPCFP128TypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMPPCFP128TypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMFloatType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMFloatType();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMDoubleType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMDoubleType();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMX86FP80Type_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMX86FP80Type();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMFP128Type_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMFP128Type();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMPPCFP128Type_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMPPCFP128Type();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMFunctionType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef ReturnType;
  llvm_ptr_deref(env, argv[0], (void **) &ReturnType);

  int ParamTypessize = 0;
  ERL_NIF_TERM *ParamTypesarray;
  enif_get_tuple(env, argv[1], &ParamTypessize, (const ERL_NIF_TERM **)&ParamTypesarray);
  LLVMTypeRef * ParamTypes;
  if (ParamTypessize == 0)
    ParamTypes = NULL;
  else {
    ParamTypes = (LLVMTypeRef *)malloc(sizeof(LLVMTypeRef *)*ParamTypessize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < ParamTypessize; i++) {
      enif_get_tuple(env,*(ParamTypesarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)ParamTypes+i);
    }
  }

  unsigned ParamCount;
  enif_get_uint(env, argv[2], (unsigned*)&ParamCount);

  char *IsVarArg_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[3], (char*)IsVarArg_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool IsVarArg = (strcmp(IsVarArg_tmp,"true") == 0);

  LLVMTypeRef retVal = LLVMFunctionType((LLVMTypeRef)ReturnType,(LLVMTypeRef *)ParamTypes,(unsigned)ParamCount,(LLVMBool)IsVarArg);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMIsFunctionVarArg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef FunctionTy;
  llvm_ptr_deref(env, argv[0], (void **) &FunctionTy);

  LLVMBool retVal = LLVMIsFunctionVarArg((LLVMTypeRef)FunctionTy);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMGetReturnType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef FunctionTy;
  llvm_ptr_deref(env, argv[0], (void **) &FunctionTy);

  LLVMTypeRef retVal = LLVMGetReturnType((LLVMTypeRef)FunctionTy);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMCountParamTypes_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef FunctionTy;
  llvm_ptr_deref(env, argv[0], (void **) &FunctionTy);

  unsigned retVal = LLVMCountParamTypes((LLVMTypeRef)FunctionTy);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetParamTypes_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef FunctionTy;
  llvm_ptr_deref(env, argv[0], (void **) &FunctionTy);

  LLVMTypeRef * Dest;
  llvm_ptr_deref(env, argv[1], (void **) &Dest);

LLVMGetParamTypes((LLVMTypeRef)FunctionTy,(LLVMTypeRef *)Dest);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMStructTypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  int ElementTypessize = 0;
  ERL_NIF_TERM *ElementTypesarray;
  enif_get_tuple(env, argv[1], &ElementTypessize, (const ERL_NIF_TERM **)&ElementTypesarray);
  LLVMTypeRef * ElementTypes;
  if (ElementTypessize == 0)
    ElementTypes = NULL;
  else {
    ElementTypes = (LLVMTypeRef *)malloc(sizeof(LLVMTypeRef *)*ElementTypessize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < ElementTypessize; i++) {
      enif_get_tuple(env,*(ElementTypesarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)ElementTypes+i);
    }
  }

  unsigned ElementCount;
  enif_get_uint(env, argv[2], (unsigned*)&ElementCount);

  char *Packed_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[3], (char*)Packed_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool Packed = (strcmp(Packed_tmp,"true") == 0);

  LLVMTypeRef retVal = LLVMStructTypeInContext((LLVMContextRef)C,(LLVMTypeRef *)ElementTypes,(unsigned)ElementCount,(LLVMBool)Packed);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMStructType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int ElementTypessize = 0;
  ERL_NIF_TERM *ElementTypesarray;
  enif_get_tuple(env, argv[0], &ElementTypessize, (const ERL_NIF_TERM **)&ElementTypesarray);
  LLVMTypeRef * ElementTypes;
  if (ElementTypessize == 0)
    ElementTypes = NULL;
  else {
    ElementTypes = (LLVMTypeRef *)malloc(sizeof(LLVMTypeRef *)*ElementTypessize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < ElementTypessize; i++) {
      enif_get_tuple(env,*(ElementTypesarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)ElementTypes+i);
    }
  }

  unsigned ElementCount;
  enif_get_uint(env, argv[1], (unsigned*)&ElementCount);

  char *Packed_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[2], (char*)Packed_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool Packed = (strcmp(Packed_tmp,"true") == 0);

  LLVMTypeRef retVal = LLVMStructType((LLVMTypeRef *)ElementTypes,(unsigned)ElementCount,(LLVMBool)Packed);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMStructCreateNamed_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMTypeRef retVal = LLVMStructCreateNamed((LLVMContextRef)C,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMGetStructName_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  const char * retVal = LLVMGetStructName((LLVMTypeRef)Ty);

  return   enif_make_string(env,retVal,ERL_NIF_LATIN1);
}

static ERL_NIF_TERM LLVMStructSetBody_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef StructTy;
  llvm_ptr_deref(env, argv[0], (void **) &StructTy);

  LLVMTypeRef * ElementTypes;
  llvm_ptr_deref(env, argv[1], (void **) &ElementTypes);

  unsigned ElementCount;
  enif_get_uint(env, argv[2], (unsigned*)&ElementCount);

  char *Packed_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[3], (char*)Packed_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool Packed = (strcmp(Packed_tmp,"true") == 0);

LLVMStructSetBody((LLVMTypeRef)StructTy,(LLVMTypeRef *)ElementTypes,(unsigned)ElementCount,(LLVMBool)Packed);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMCountStructElementTypes_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef StructTy;
  llvm_ptr_deref(env, argv[0], (void **) &StructTy);

  unsigned retVal = LLVMCountStructElementTypes((LLVMTypeRef)StructTy);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetStructElementTypes_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef StructTy;
  llvm_ptr_deref(env, argv[0], (void **) &StructTy);

  LLVMTypeRef * Dest;
  llvm_ptr_deref(env, argv[1], (void **) &Dest);

LLVMGetStructElementTypes((LLVMTypeRef)StructTy,(LLVMTypeRef *)Dest);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMIsPackedStruct_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef StructTy;
  llvm_ptr_deref(env, argv[0], (void **) &StructTy);

  LLVMBool retVal = LLVMIsPackedStruct((LLVMTypeRef)StructTy);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMIsOpaqueStruct_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef StructTy;
  llvm_ptr_deref(env, argv[0], (void **) &StructTy);

  LLVMBool retVal = LLVMIsOpaqueStruct((LLVMTypeRef)StructTy);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMGetTypeByName_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMTypeRef retVal = LLVMGetTypeByName((LLVMModuleRef)M,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMArrayType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef ElementType;
  llvm_ptr_deref(env, argv[0], (void **) &ElementType);

  unsigned ElementCount;
  enif_get_uint(env, argv[1], (unsigned*)&ElementCount);

  LLVMTypeRef retVal = LLVMArrayType((LLVMTypeRef)ElementType,(unsigned)ElementCount);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMPointerType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef ElementType;
  llvm_ptr_deref(env, argv[0], (void **) &ElementType);

  unsigned AddressSpace;
  enif_get_uint(env, argv[1], (unsigned*)&AddressSpace);

  LLVMTypeRef retVal = LLVMPointerType((LLVMTypeRef)ElementType,(unsigned)AddressSpace);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMVectorType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef ElementType;
  llvm_ptr_deref(env, argv[0], (void **) &ElementType);

  unsigned ElementCount;
  enif_get_uint(env, argv[1], (unsigned*)&ElementCount);

  LLVMTypeRef retVal = LLVMVectorType((LLVMTypeRef)ElementType,(unsigned)ElementCount);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMGetElementType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMTypeRef retVal = LLVMGetElementType((LLVMTypeRef)Ty);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMGetArrayLength_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef ArrayTy;
  llvm_ptr_deref(env, argv[0], (void **) &ArrayTy);

  unsigned retVal = LLVMGetArrayLength((LLVMTypeRef)ArrayTy);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetPointerAddressSpace_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef PointerTy;
  llvm_ptr_deref(env, argv[0], (void **) &PointerTy);

  unsigned retVal = LLVMGetPointerAddressSpace((LLVMTypeRef)PointerTy);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetVectorSize_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef VectorTy;
  llvm_ptr_deref(env, argv[0], (void **) &VectorTy);

  unsigned retVal = LLVMGetVectorSize((LLVMTypeRef)VectorTy);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMVoidTypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMVoidTypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMLabelTypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMLabelTypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMX86MMXTypeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMTypeRef retVal = LLVMX86MMXTypeInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMVoidType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMVoidType();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMLabelType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMLabelType();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMX86MMXType_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef retVal = LLVMX86MMXType();

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMTypeOf_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMTypeRef retVal = LLVMTypeOf((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMTypeRef, retVal);
}

static ERL_NIF_TERM LLVMGetValueName_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  const char * retVal = LLVMGetValueName((LLVMValueRef)Val);

  return   enif_make_string(env,retVal,ERL_NIF_LATIN1);
}

static ERL_NIF_TERM LLVMSetValueName_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

LLVMSetValueName((LLVMValueRef)Val,(const char *)Name);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMDumpValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

LLVMDumpValue((LLVMValueRef)Val);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMReplaceAllUsesWith_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef OldVal;
  llvm_ptr_deref(env, argv[0], (void **) &OldVal);

  LLVMValueRef NewVal;
  llvm_ptr_deref(env, argv[1], (void **) &NewVal);

LLVMReplaceAllUsesWith((LLVMValueRef)OldVal,(LLVMValueRef)NewVal);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMHasMetadata_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  int retVal = LLVMHasMetadata((LLVMValueRef)Val);

  return   enif_make_int(env, retVal);
}

static ERL_NIF_TERM LLVMGetMetadata_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  unsigned KindID;
  enif_get_uint(env, argv[1], (unsigned*)&KindID);

  LLVMValueRef retVal = LLVMGetMetadata((LLVMValueRef)Val,(unsigned)KindID);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMSetMetadata_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  unsigned KindID;
  enif_get_uint(env, argv[1], (unsigned*)&KindID);

  LLVMValueRef Node;
  llvm_ptr_deref(env, argv[2], (void **) &Node);

LLVMSetMetadata((LLVMValueRef)Val,(unsigned)KindID,(LLVMValueRef)Node);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMIsAArgument_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAArgument((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsABasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsABasicBlock((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAInlineAsm_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAInlineAsm((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAMDNode_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAMDNode((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAMDString_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAMDString((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAUser_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAUser((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAConstant_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAConstant((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsABlockAddress_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsABlockAddress((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAConstantAggregateZero_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAConstantAggregateZero((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAConstantArray_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAConstantArray((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAConstantExpr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAConstantExpr((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAConstantFP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAConstantFP((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAConstantInt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAConstantInt((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAConstantPointerNull_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAConstantPointerNull((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAConstantStruct_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAConstantStruct((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAConstantVector_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAConstantVector((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAGlobalValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAGlobalValue((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAFunction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAFunction((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAGlobalAlias_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAGlobalAlias((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAGlobalVariable_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAGlobalVariable((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAUndefValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAUndefValue((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAInstruction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAInstruction((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsABinaryOperator_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsABinaryOperator((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsACallInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsACallInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAIntrinsicInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAIntrinsicInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsADbgInfoIntrinsic_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsADbgInfoIntrinsic((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsADbgDeclareInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsADbgDeclareInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAEHExceptionInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAEHExceptionInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAEHSelectorInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAEHSelectorInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAMemIntrinsic_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAMemIntrinsic((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAMemCpyInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAMemCpyInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAMemMoveInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAMemMoveInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAMemSetInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAMemSetInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsACmpInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsACmpInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAFCmpInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAFCmpInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAICmpInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAICmpInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAExtractElementInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAExtractElementInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAGetElementPtrInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAGetElementPtrInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAInsertElementInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAInsertElementInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAInsertValueInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAInsertValueInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsALandingPadInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsALandingPadInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAPHINode_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAPHINode((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsASelectInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsASelectInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAShuffleVectorInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAShuffleVectorInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAStoreInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAStoreInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsATerminatorInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsATerminatorInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsABranchInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsABranchInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAIndirectBrInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAIndirectBrInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAInvokeInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAInvokeInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAReturnInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAReturnInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsASwitchInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsASwitchInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAUnreachableInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAUnreachableInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAResumeInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAResumeInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAUnaryInstruction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAUnaryInstruction((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAAllocaInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAAllocaInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsACastInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsACastInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsABitCastInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsABitCastInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAFPExtInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAFPExtInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAFPToSIInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAFPToSIInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAFPToUIInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAFPToUIInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAFPTruncInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAFPTruncInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAIntToPtrInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAIntToPtrInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAPtrToIntInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAPtrToIntInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsASExtInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsASExtInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsASIToFPInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsASIToFPInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsATruncInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsATruncInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAUIToFPInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAUIToFPInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAZExtInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAZExtInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAExtractValueInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAExtractValueInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsALoadInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsALoadInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsAVAArgInst_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMValueRef retVal = LLVMIsAVAArgInst((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetFirstUse_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMUseRef retVal = LLVMGetFirstUse((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMUseRef, retVal);
}

static ERL_NIF_TERM LLVMGetNextUse_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMUseRef U;
  llvm_ptr_deref(env, argv[0], (void **) &U);

  LLVMUseRef retVal = LLVMGetNextUse((LLVMUseRef)U);

  return   llvm_ptr_create(env, RTLLVMUseRef, retVal);
}

static ERL_NIF_TERM LLVMGetUser_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMUseRef U;
  llvm_ptr_deref(env, argv[0], (void **) &U);

  LLVMValueRef retVal = LLVMGetUser((LLVMUseRef)U);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetUsedValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMUseRef U;
  llvm_ptr_deref(env, argv[0], (void **) &U);

  LLVMValueRef retVal = LLVMGetUsedValue((LLVMUseRef)U);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetOperand_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  unsigned Index;
  enif_get_uint(env, argv[1], (unsigned*)&Index);

  LLVMValueRef retVal = LLVMGetOperand((LLVMValueRef)Val,(unsigned)Index);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMSetOperand_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef User;
  llvm_ptr_deref(env, argv[0], (void **) &User);

  unsigned Index;
  enif_get_uint(env, argv[1], (unsigned*)&Index);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[2], (void **) &Val);

LLVMSetOperand((LLVMValueRef)User,(unsigned)Index,(LLVMValueRef)Val);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetNumOperands_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  int retVal = LLVMGetNumOperands((LLVMValueRef)Val);

  return   enif_make_int(env, retVal);
}

static ERL_NIF_TERM LLVMConstNull_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMValueRef retVal = LLVMConstNull((LLVMTypeRef)Ty);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstAllOnes_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMValueRef retVal = LLVMConstAllOnes((LLVMTypeRef)Ty);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetUndef_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMValueRef retVal = LLVMGetUndef((LLVMTypeRef)Ty);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMIsConstant_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMBool retVal = LLVMIsConstant((LLVMValueRef)Val);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMIsNull_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMBool retVal = LLVMIsNull((LLVMValueRef)Val);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMIsUndef_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMBool retVal = LLVMIsUndef((LLVMValueRef)Val);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMConstPointerNull_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMValueRef retVal = LLVMConstPointerNull((LLVMTypeRef)Ty);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMMDStringInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  char *Str = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Str, 255, ERL_NIF_LATIN1);

  unsigned SLen;
  enif_get_uint(env, argv[2], (unsigned*)&SLen);

  LLVMValueRef retVal = LLVMMDStringInContext((LLVMContextRef)C,(const char *)Str,(unsigned)SLen);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMMDString_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  char *Str = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[0], (char*)Str, 255, ERL_NIF_LATIN1);

  unsigned SLen;
  enif_get_uint(env, argv[1], (unsigned*)&SLen);

  LLVMValueRef retVal = LLVMMDString((const char *)Str,(unsigned)SLen);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMMDNodeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMValueRef * Vals;
  llvm_ptr_deref(env, argv[1], (void **) &Vals);

  unsigned Count;
  enif_get_uint(env, argv[2], (unsigned*)&Count);

  LLVMValueRef retVal = LLVMMDNodeInContext((LLVMContextRef)C,(LLVMValueRef *)Vals,(unsigned)Count);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMMDNode_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int Valssize = 0;
  ERL_NIF_TERM *Valsarray;
  enif_get_tuple(env, argv[0], &Valssize, (const ERL_NIF_TERM **)&Valsarray);
  LLVMValueRef * Vals;
  if (Valssize == 0)
    Vals = NULL;
  else {
    Vals = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*Valssize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < Valssize; i++) {
      enif_get_tuple(env,*(Valsarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)Vals+i);
    }
  }

  unsigned Count;
  enif_get_uint(env, argv[1], (unsigned*)&Count);

  LLVMValueRef retVal = LLVMMDNode((LLVMValueRef *)Vals,(unsigned)Count);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetMDString_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef V;
  llvm_ptr_deref(env, argv[0], (void **) &V);

  unsigned * Len;
  llvm_ptr_deref(env, argv[1], (void **) &Len);

  const char * retVal = LLVMGetMDString((LLVMValueRef)V,(unsigned *)Len);

  return   enif_make_string(env,retVal,ERL_NIF_LATIN1);
}

static ERL_NIF_TERM LLVMGetNamedMetadataNumOperands_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)name, 255, ERL_NIF_LATIN1);

  unsigned retVal = LLVMGetNamedMetadataNumOperands((LLVMModuleRef)M,(const char *)name);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetNamedMetadataOperands_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)name, 255, ERL_NIF_LATIN1);

  LLVMValueRef * Dest;
  llvm_ptr_deref(env, argv[2], (void **) &Dest);

LLVMGetNamedMetadataOperands((LLVMModuleRef)M,(const char *)name,(LLVMValueRef *)Dest);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMConstInt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef IntTy;
  llvm_ptr_deref(env, argv[0], (void **) &IntTy);

  unsigned long long N;
  enif_get_uint64(env, argv[1], (ErlNifUInt64 *)&N);

  char *SignExtend_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[2], (char*)SignExtend_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool SignExtend = (strcmp(SignExtend_tmp,"true") == 0);

  LLVMValueRef retVal = LLVMConstInt((LLVMTypeRef)IntTy,(unsigned long long)N,(LLVMBool)SignExtend);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstIntOfString_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef IntTy;
  llvm_ptr_deref(env, argv[0], (void **) &IntTy);

  char *Text = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Text, 255, ERL_NIF_LATIN1);

  uint8_t Radix;
  llvm_ptr_deref(env, argv[2], (void **) &Radix);

  LLVMValueRef retVal = LLVMConstIntOfString((LLVMTypeRef)IntTy,(const char *)Text,(uint8_t)Radix);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstIntOfStringAndSize_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef IntTy;
  llvm_ptr_deref(env, argv[0], (void **) &IntTy);

  char *Text = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Text, 255, ERL_NIF_LATIN1);

  unsigned SLen;
  enif_get_uint(env, argv[2], (unsigned*)&SLen);

  uint8_t Radix;
  llvm_ptr_deref(env, argv[3], (void **) &Radix);

  LLVMValueRef retVal = LLVMConstIntOfStringAndSize((LLVMTypeRef)IntTy,(const char *)Text,(unsigned)SLen,(uint8_t)Radix);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstReal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef RealTy;
  llvm_ptr_deref(env, argv[0], (void **) &RealTy);

  double N;
  enif_get_double(env, argv[1], (double*)&N);

  LLVMValueRef retVal = LLVMConstReal((LLVMTypeRef)RealTy,(double)N);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstRealOfString_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef RealTy;
  llvm_ptr_deref(env, argv[0], (void **) &RealTy);

  char *Text = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Text, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMConstRealOfString((LLVMTypeRef)RealTy,(const char *)Text);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstRealOfStringAndSize_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef RealTy;
  llvm_ptr_deref(env, argv[0], (void **) &RealTy);

  char *Text = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Text, 255, ERL_NIF_LATIN1);

  unsigned SLen;
  enif_get_uint(env, argv[2], (unsigned*)&SLen);

  LLVMValueRef retVal = LLVMConstRealOfStringAndSize((LLVMTypeRef)RealTy,(const char *)Text,(unsigned)SLen);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstIntGetZExtValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  unsigned long long retVal = LLVMConstIntGetZExtValue((LLVMValueRef)ConstantVal);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMConstIntGetSExtValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  long long retVal = LLVMConstIntGetSExtValue((LLVMValueRef)ConstantVal);

  return   enif_make_int(env, retVal);
}

static ERL_NIF_TERM LLVMConstStringInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  char *Str = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Str, 255, ERL_NIF_LATIN1);

  unsigned Length;
  enif_get_uint(env, argv[2], (unsigned*)&Length);

  char *DontNullTerminate_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[3], (char*)DontNullTerminate_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool DontNullTerminate = (strcmp(DontNullTerminate_tmp,"true") == 0);

  LLVMValueRef retVal = LLVMConstStringInContext((LLVMContextRef)C,(const char *)Str,(unsigned)Length,(LLVMBool)DontNullTerminate);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstStructInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  int ConstantValssize = 0;
  ERL_NIF_TERM *ConstantValsarray;
  enif_get_tuple(env, argv[1], &ConstantValssize, (const ERL_NIF_TERM **)&ConstantValsarray);
  LLVMValueRef * ConstantVals;
  if (ConstantValssize == 0)
    ConstantVals = NULL;
  else {
    ConstantVals = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*ConstantValssize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < ConstantValssize; i++) {
      enif_get_tuple(env,*(ConstantValsarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)ConstantVals+i);
    }
  }

  unsigned Count;
  enif_get_uint(env, argv[2], (unsigned*)&Count);

  char *Packed_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[3], (char*)Packed_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool Packed = (strcmp(Packed_tmp,"true") == 0);

  LLVMValueRef retVal = LLVMConstStructInContext((LLVMContextRef)C,(LLVMValueRef *)ConstantVals,(unsigned)Count,(LLVMBool)Packed);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstString_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  char *Str = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[0], (char*)Str, 255, ERL_NIF_LATIN1);

  unsigned Length;
  enif_get_uint(env, argv[1], (unsigned*)&Length);

  char *DontNullTerminate_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[2], (char*)DontNullTerminate_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool DontNullTerminate = (strcmp(DontNullTerminate_tmp,"true") == 0);

  LLVMValueRef retVal = LLVMConstString((const char *)Str,(unsigned)Length,(LLVMBool)DontNullTerminate);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstArray_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef ElementTy;
  llvm_ptr_deref(env, argv[0], (void **) &ElementTy);

  int ConstantValssize = 0;
  ERL_NIF_TERM *ConstantValsarray;
  enif_get_tuple(env, argv[1], &ConstantValssize, (const ERL_NIF_TERM **)&ConstantValsarray);
  LLVMValueRef * ConstantVals;
  if (ConstantValssize == 0)
    ConstantVals = NULL;
  else {
    ConstantVals = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*ConstantValssize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < ConstantValssize; i++) {
      enif_get_tuple(env,*(ConstantValsarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)ConstantVals+i);
    }
  }

  unsigned Length;
  enif_get_uint(env, argv[2], (unsigned*)&Length);

  LLVMValueRef retVal = LLVMConstArray((LLVMTypeRef)ElementTy,(LLVMValueRef *)ConstantVals,(unsigned)Length);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstStruct_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int ConstantValssize = 0;
  ERL_NIF_TERM *ConstantValsarray;
  enif_get_tuple(env, argv[0], &ConstantValssize, (const ERL_NIF_TERM **)&ConstantValsarray);
  LLVMValueRef * ConstantVals;
  if (ConstantValssize == 0)
    ConstantVals = NULL;
  else {
    ConstantVals = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*ConstantValssize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < ConstantValssize; i++) {
      enif_get_tuple(env,*(ConstantValsarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)ConstantVals+i);
    }
  }

  unsigned Count;
  enif_get_uint(env, argv[1], (unsigned*)&Count);

  char *Packed_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[2], (char*)Packed_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool Packed = (strcmp(Packed_tmp,"true") == 0);

  LLVMValueRef retVal = LLVMConstStruct((LLVMValueRef *)ConstantVals,(unsigned)Count,(LLVMBool)Packed);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNamedStruct_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef StructTy;
  llvm_ptr_deref(env, argv[0], (void **) &StructTy);

  LLVMValueRef * ConstantVals;
  llvm_ptr_deref(env, argv[1], (void **) &ConstantVals);

  unsigned Count;
  enif_get_uint(env, argv[2], (unsigned*)&Count);

  LLVMValueRef retVal = LLVMConstNamedStruct((LLVMTypeRef)StructTy,(LLVMValueRef *)ConstantVals,(unsigned)Count);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstVector_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int ScalarConstantValssize = 0;
  ERL_NIF_TERM *ScalarConstantValsarray;
  enif_get_tuple(env, argv[0], &ScalarConstantValssize, (const ERL_NIF_TERM **)&ScalarConstantValsarray);
  LLVMValueRef * ScalarConstantVals;
  if (ScalarConstantValssize == 0)
    ScalarConstantVals = NULL;
  else {
    ScalarConstantVals = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*ScalarConstantValssize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < ScalarConstantValssize; i++) {
      enif_get_tuple(env,*(ScalarConstantValsarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)ScalarConstantVals+i);
    }
  }

  unsigned Size;
  enif_get_uint(env, argv[1], (unsigned*)&Size);

  LLVMValueRef retVal = LLVMConstVector((LLVMValueRef *)ScalarConstantVals,(unsigned)Size);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetConstOpcode_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMOpcode retVal = LLVMGetConstOpcode((LLVMValueRef)ConstantVal);

  return   enif_make_int(env, (int)retVal);
}

static ERL_NIF_TERM LLVMAlignOf_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMValueRef retVal = LLVMAlignOf((LLVMTypeRef)Ty);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMSizeOf_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  LLVMValueRef retVal = LLVMSizeOf((LLVMTypeRef)Ty);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNeg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMValueRef retVal = LLVMConstNeg((LLVMValueRef)ConstantVal);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNSWNeg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMValueRef retVal = LLVMConstNSWNeg((LLVMValueRef)ConstantVal);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNUWNeg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMValueRef retVal = LLVMConstNUWNeg((LLVMValueRef)ConstantVal);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFNeg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMValueRef retVal = LLVMConstFNeg((LLVMValueRef)ConstantVal);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNot_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMValueRef retVal = LLVMConstNot((LLVMValueRef)ConstantVal);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstAdd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstAdd((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNSWAdd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstNSWAdd((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNUWAdd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstNUWAdd((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFAdd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstFAdd((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstSub_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstSub((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNSWSub_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstNSWSub((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNUWSub_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstNUWSub((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFSub_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstFSub((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstMul_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstMul((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNSWMul_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstNSWMul((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstNUWMul_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstNUWMul((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFMul_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstFMul((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstUDiv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstUDiv((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstSDiv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstSDiv((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstExactSDiv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstExactSDiv((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFDiv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstFDiv((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstURem_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstURem((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstSRem_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstSRem((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFRem_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstFRem((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstAnd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstAnd((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstOr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstOr((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstXor_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstXor((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstICmp_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMIntPredicate Predicate;
  enif_get_uint(env, argv[0], (LLVMIntPredicate*)&Predicate);

  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[2], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstICmp((LLVMIntPredicate)Predicate,(LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFCmp_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMRealPredicate Predicate;
  enif_get_uint(env, argv[0], (LLVMRealPredicate*)&Predicate);

  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[2], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstFCmp((LLVMRealPredicate)Predicate,(LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstShl_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstShl((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstLShr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstLShr((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstAShr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LHSConstant;
  llvm_ptr_deref(env, argv[0], (void **) &LHSConstant);

  LLVMValueRef RHSConstant;
  llvm_ptr_deref(env, argv[1], (void **) &RHSConstant);

  LLVMValueRef retVal = LLVMConstAShr((LLVMValueRef)LHSConstant,(LLVMValueRef)RHSConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstGEP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  int ConstantIndicessize = 0;
  ERL_NIF_TERM *ConstantIndicesarray;
  enif_get_tuple(env, argv[1], &ConstantIndicessize, (const ERL_NIF_TERM **)&ConstantIndicesarray);
  LLVMValueRef * ConstantIndices;
  if (ConstantIndicessize == 0)
    ConstantIndices = NULL;
  else {
    ConstantIndices = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*ConstantIndicessize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < ConstantIndicessize; i++) {
      enif_get_tuple(env,*(ConstantIndicesarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)ConstantIndices+i);
    }
  }

  unsigned NumIndices;
  enif_get_uint(env, argv[2], (unsigned*)&NumIndices);

  LLVMValueRef retVal = LLVMConstGEP((LLVMValueRef)ConstantVal,(LLVMValueRef *)ConstantIndices,(unsigned)NumIndices);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstInBoundsGEP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  int ConstantIndicessize = 0;
  ERL_NIF_TERM *ConstantIndicesarray;
  enif_get_tuple(env, argv[1], &ConstantIndicessize, (const ERL_NIF_TERM **)&ConstantIndicesarray);
  LLVMValueRef * ConstantIndices;
  if (ConstantIndicessize == 0)
    ConstantIndices = NULL;
  else {
    ConstantIndices = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*ConstantIndicessize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < ConstantIndicessize; i++) {
      enif_get_tuple(env,*(ConstantIndicesarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)ConstantIndices+i);
    }
  }

  unsigned NumIndices;
  enif_get_uint(env, argv[2], (unsigned*)&NumIndices);

  LLVMValueRef retVal = LLVMConstInBoundsGEP((LLVMValueRef)ConstantVal,(LLVMValueRef *)ConstantIndices,(unsigned)NumIndices);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstTrunc_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstTrunc((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstSExt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstSExt((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstZExt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstZExt((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFPTrunc_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstFPTrunc((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFPExt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstFPExt((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstUIToFP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstUIToFP((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstSIToFP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstSIToFP((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFPToUI_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstFPToUI((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFPToSI_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstFPToSI((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstPtrToInt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstPtrToInt((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstIntToPtr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstIntToPtr((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstBitCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstBitCast((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstZExtOrBitCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstZExtOrBitCast((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstSExtOrBitCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstSExtOrBitCast((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstTruncOrBitCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstTruncOrBitCast((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstPointerCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstPointerCast((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstIntCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  char *isSigned_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[2], (char*)isSigned_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool isSigned = (strcmp(isSigned_tmp,"true") == 0);

  LLVMValueRef retVal = LLVMConstIntCast((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType,(LLVMBool)isSigned);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstFPCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantVal);

  LLVMTypeRef ToType;
  llvm_ptr_deref(env, argv[1], (void **) &ToType);

  LLVMValueRef retVal = LLVMConstFPCast((LLVMValueRef)ConstantVal,(LLVMTypeRef)ToType);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstSelect_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef ConstantCondition;
  llvm_ptr_deref(env, argv[0], (void **) &ConstantCondition);

  LLVMValueRef ConstantIfTrue;
  llvm_ptr_deref(env, argv[1], (void **) &ConstantIfTrue);

  LLVMValueRef ConstantIfFalse;
  llvm_ptr_deref(env, argv[2], (void **) &ConstantIfFalse);

  LLVMValueRef retVal = LLVMConstSelect((LLVMValueRef)ConstantCondition,(LLVMValueRef)ConstantIfTrue,(LLVMValueRef)ConstantIfFalse);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstExtractElement_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef VectorConstant;
  llvm_ptr_deref(env, argv[0], (void **) &VectorConstant);

  LLVMValueRef IndexConstant;
  llvm_ptr_deref(env, argv[1], (void **) &IndexConstant);

  LLVMValueRef retVal = LLVMConstExtractElement((LLVMValueRef)VectorConstant,(LLVMValueRef)IndexConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstInsertElement_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef VectorConstant;
  llvm_ptr_deref(env, argv[0], (void **) &VectorConstant);

  LLVMValueRef ElementValueConstant;
  llvm_ptr_deref(env, argv[1], (void **) &ElementValueConstant);

  LLVMValueRef IndexConstant;
  llvm_ptr_deref(env, argv[2], (void **) &IndexConstant);

  LLVMValueRef retVal = LLVMConstInsertElement((LLVMValueRef)VectorConstant,(LLVMValueRef)ElementValueConstant,(LLVMValueRef)IndexConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstShuffleVector_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef VectorAConstant;
  llvm_ptr_deref(env, argv[0], (void **) &VectorAConstant);

  LLVMValueRef VectorBConstant;
  llvm_ptr_deref(env, argv[1], (void **) &VectorBConstant);

  LLVMValueRef MaskConstant;
  llvm_ptr_deref(env, argv[2], (void **) &MaskConstant);

  LLVMValueRef retVal = LLVMConstShuffleVector((LLVMValueRef)VectorAConstant,(LLVMValueRef)VectorBConstant,(LLVMValueRef)MaskConstant);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstExtractValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef AggConstant;
  llvm_ptr_deref(env, argv[0], (void **) &AggConstant);

  unsigned * IdxList;
  llvm_ptr_deref(env, argv[1], (void **) &IdxList);

  unsigned NumIdx;
  enif_get_uint(env, argv[2], (unsigned*)&NumIdx);

  LLVMValueRef retVal = LLVMConstExtractValue((LLVMValueRef)AggConstant,(unsigned *)IdxList,(unsigned)NumIdx);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstInsertValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef AggConstant;
  llvm_ptr_deref(env, argv[0], (void **) &AggConstant);

  LLVMValueRef ElementValueConstant;
  llvm_ptr_deref(env, argv[1], (void **) &ElementValueConstant);

  unsigned * IdxList;
  llvm_ptr_deref(env, argv[2], (void **) &IdxList);

  unsigned NumIdx;
  enif_get_uint(env, argv[3], (unsigned*)&NumIdx);

  LLVMValueRef retVal = LLVMConstInsertValue((LLVMValueRef)AggConstant,(LLVMValueRef)ElementValueConstant,(unsigned *)IdxList,(unsigned)NumIdx);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMConstInlineAsm_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[0], (void **) &Ty);

  char *AsmString = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)AsmString, 255, ERL_NIF_LATIN1);

  char *Constraints = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Constraints, 255, ERL_NIF_LATIN1);

  char *HasSideEffects_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[3], (char*)HasSideEffects_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool HasSideEffects = (strcmp(HasSideEffects_tmp,"true") == 0);

  char *IsAlignStack_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[4], (char*)IsAlignStack_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool IsAlignStack = (strcmp(IsAlignStack_tmp,"true") == 0);

  LLVMValueRef retVal = LLVMConstInlineAsm((LLVMTypeRef)Ty,(const char *)AsmString,(const char *)Constraints,(LLVMBool)HasSideEffects,(LLVMBool)IsAlignStack);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBlockAddress_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef F;
  llvm_ptr_deref(env, argv[0], (void **) &F);

  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[1], (void **) &BB);

  LLVMValueRef retVal = LLVMBlockAddress((LLVMValueRef)F,(LLVMBasicBlockRef)BB);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetGlobalParent_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  LLVMModuleRef retVal = LLVMGetGlobalParent((LLVMValueRef)Global);

  return   llvm_ptr_create(env, RTLLVMModuleRef, retVal);
}

static ERL_NIF_TERM LLVMIsDeclaration_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  LLVMBool retVal = LLVMIsDeclaration((LLVMValueRef)Global);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMGetLinkage_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  LLVMLinkage retVal = LLVMGetLinkage((LLVMValueRef)Global);

  return   enif_make_int(env, (int)retVal);
}

static ERL_NIF_TERM LLVMSetLinkage_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  LLVMLinkage Linkage;
  enif_get_uint(env, argv[1], (LLVMLinkage*)&Linkage);

LLVMSetLinkage((LLVMValueRef)Global,(LLVMLinkage)Linkage);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetSection_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  const char * retVal = LLVMGetSection((LLVMValueRef)Global);

  return   enif_make_string(env,retVal,ERL_NIF_LATIN1);
}

static ERL_NIF_TERM LLVMSetSection_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  char *Section = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Section, 255, ERL_NIF_LATIN1);

LLVMSetSection((LLVMValueRef)Global,(const char *)Section);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetVisibility_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  LLVMVisibility retVal = LLVMGetVisibility((LLVMValueRef)Global);

  return   enif_make_int(env, (int)retVal);
}

static ERL_NIF_TERM LLVMSetVisibility_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  LLVMVisibility Viz;
  enif_get_uint(env, argv[1], (LLVMVisibility*)&Viz);

LLVMSetVisibility((LLVMValueRef)Global,(LLVMVisibility)Viz);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetAlignment_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  unsigned retVal = LLVMGetAlignment((LLVMValueRef)Global);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMSetAlignment_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Global;
  llvm_ptr_deref(env, argv[0], (void **) &Global);

  unsigned Bytes;
  enif_get_uint(env, argv[1], (unsigned*)&Bytes);

LLVMSetAlignment((LLVMValueRef)Global,(unsigned)Bytes);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMAddGlobal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[1], (void **) &Ty);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMAddGlobal((LLVMModuleRef)M,(LLVMTypeRef)Ty,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMAddGlobalInAddressSpace_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[1], (void **) &Ty);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  unsigned AddressSpace;
  enif_get_uint(env, argv[3], (unsigned*)&AddressSpace);

  LLVMValueRef retVal = LLVMAddGlobalInAddressSpace((LLVMModuleRef)M,(LLVMTypeRef)Ty,(const char *)Name,(unsigned)AddressSpace);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetNamedGlobal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMGetNamedGlobal((LLVMModuleRef)M,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetFirstGlobal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMValueRef retVal = LLVMGetFirstGlobal((LLVMModuleRef)M);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetLastGlobal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMValueRef retVal = LLVMGetLastGlobal((LLVMModuleRef)M);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetNextGlobal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef GlobalVar;
  llvm_ptr_deref(env, argv[0], (void **) &GlobalVar);

  LLVMValueRef retVal = LLVMGetNextGlobal((LLVMValueRef)GlobalVar);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetPreviousGlobal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef GlobalVar;
  llvm_ptr_deref(env, argv[0], (void **) &GlobalVar);

  LLVMValueRef retVal = LLVMGetPreviousGlobal((LLVMValueRef)GlobalVar);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMDeleteGlobal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef GlobalVar;
  llvm_ptr_deref(env, argv[0], (void **) &GlobalVar);

LLVMDeleteGlobal((LLVMValueRef)GlobalVar);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetInitializer_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef GlobalVar;
  llvm_ptr_deref(env, argv[0], (void **) &GlobalVar);

  LLVMValueRef retVal = LLVMGetInitializer((LLVMValueRef)GlobalVar);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMSetInitializer_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef GlobalVar;
  llvm_ptr_deref(env, argv[0], (void **) &GlobalVar);

  LLVMValueRef ConstantVal;
  llvm_ptr_deref(env, argv[1], (void **) &ConstantVal);

LLVMSetInitializer((LLVMValueRef)GlobalVar,(LLVMValueRef)ConstantVal);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMIsThreadLocal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef GlobalVar;
  llvm_ptr_deref(env, argv[0], (void **) &GlobalVar);

  LLVMBool retVal = LLVMIsThreadLocal((LLVMValueRef)GlobalVar);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMSetThreadLocal_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef GlobalVar;
  llvm_ptr_deref(env, argv[0], (void **) &GlobalVar);

  char *IsThreadLocal_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[1], (char*)IsThreadLocal_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool IsThreadLocal = (strcmp(IsThreadLocal_tmp,"true") == 0);

LLVMSetThreadLocal((LLVMValueRef)GlobalVar,(LLVMBool)IsThreadLocal);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMIsGlobalConstant_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef GlobalVar;
  llvm_ptr_deref(env, argv[0], (void **) &GlobalVar);

  LLVMBool retVal = LLVMIsGlobalConstant((LLVMValueRef)GlobalVar);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMSetGlobalConstant_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef GlobalVar;
  llvm_ptr_deref(env, argv[0], (void **) &GlobalVar);

  char *IsConstant_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[1], (char*)IsConstant_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool IsConstant = (strcmp(IsConstant_tmp,"true") == 0);

LLVMSetGlobalConstant((LLVMValueRef)GlobalVar,(LLVMBool)IsConstant);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMAddAlias_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[1], (void **) &Ty);

  LLVMValueRef Aliasee;
  llvm_ptr_deref(env, argv[2], (void **) &Aliasee);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMAddAlias((LLVMModuleRef)M,(LLVMTypeRef)Ty,(LLVMValueRef)Aliasee,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMAddFunction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMTypeRef FunctionTy;
  llvm_ptr_deref(env, argv[2], (void **) &FunctionTy);

  LLVMValueRef retVal = LLVMAddFunction((LLVMModuleRef)M,(const char *)Name,(LLVMTypeRef)FunctionTy);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetNamedFunction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMGetNamedFunction((LLVMModuleRef)M,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetFirstFunction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMValueRef retVal = LLVMGetFirstFunction((LLVMModuleRef)M);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetLastFunction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMValueRef retVal = LLVMGetLastFunction((LLVMModuleRef)M);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetNextFunction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMValueRef retVal = LLVMGetNextFunction((LLVMValueRef)Fn);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetPreviousFunction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMValueRef retVal = LLVMGetPreviousFunction((LLVMValueRef)Fn);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMDeleteFunction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

LLVMDeleteFunction((LLVMValueRef)Fn);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetIntrinsicID_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  unsigned retVal = LLVMGetIntrinsicID((LLVMValueRef)Fn);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetFunctionCallConv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  unsigned retVal = LLVMGetFunctionCallConv((LLVMValueRef)Fn);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMSetFunctionCallConv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  unsigned CC;
  enif_get_uint(env, argv[1], (unsigned*)&CC);

LLVMSetFunctionCallConv((LLVMValueRef)Fn,(unsigned)CC);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetGC_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  const char * retVal = LLVMGetGC((LLVMValueRef)Fn);

  return   enif_make_string(env,retVal,ERL_NIF_LATIN1);
}

static ERL_NIF_TERM LLVMSetGC_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

LLVMSetGC((LLVMValueRef)Fn,(const char *)Name);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMAddFunctionAttr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMAttribute PA;
  enif_get_uint(env, argv[1], (LLVMAttribute*)&PA);

LLVMAddFunctionAttr((LLVMValueRef)Fn,(LLVMAttribute)PA);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetFunctionAttr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMAttribute retVal = LLVMGetFunctionAttr((LLVMValueRef)Fn);

  return   enif_make_int(env, (int)retVal);
}

static ERL_NIF_TERM LLVMRemoveFunctionAttr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMAttribute PA;
  enif_get_uint(env, argv[1], (LLVMAttribute*)&PA);

LLVMRemoveFunctionAttr((LLVMValueRef)Fn,(LLVMAttribute)PA);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMCountParams_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  unsigned retVal = LLVMCountParams((LLVMValueRef)Fn);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetParams_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMValueRef * Params;
  llvm_ptr_deref(env, argv[1], (void **) &Params);

LLVMGetParams((LLVMValueRef)Fn,(LLVMValueRef *)Params);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetParam_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  unsigned Index;
  enif_get_uint(env, argv[1], (unsigned*)&Index);

  LLVMValueRef retVal = LLVMGetParam((LLVMValueRef)Fn,(unsigned)Index);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetParamParent_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Inst;
  llvm_ptr_deref(env, argv[0], (void **) &Inst);

  LLVMValueRef retVal = LLVMGetParamParent((LLVMValueRef)Inst);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetFirstParam_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMValueRef retVal = LLVMGetFirstParam((LLVMValueRef)Fn);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetLastParam_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMValueRef retVal = LLVMGetLastParam((LLVMValueRef)Fn);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetNextParam_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Arg;
  llvm_ptr_deref(env, argv[0], (void **) &Arg);

  LLVMValueRef retVal = LLVMGetNextParam((LLVMValueRef)Arg);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetPreviousParam_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Arg;
  llvm_ptr_deref(env, argv[0], (void **) &Arg);

  LLVMValueRef retVal = LLVMGetPreviousParam((LLVMValueRef)Arg);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMAddAttribute_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Arg;
  llvm_ptr_deref(env, argv[0], (void **) &Arg);

  LLVMAttribute PA;
  enif_get_uint(env, argv[1], (LLVMAttribute*)&PA);

LLVMAddAttribute((LLVMValueRef)Arg,(LLVMAttribute)PA);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMRemoveAttribute_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Arg;
  llvm_ptr_deref(env, argv[0], (void **) &Arg);

  LLVMAttribute PA;
  enif_get_uint(env, argv[1], (LLVMAttribute*)&PA);

LLVMRemoveAttribute((LLVMValueRef)Arg,(LLVMAttribute)PA);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetAttribute_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Arg;
  llvm_ptr_deref(env, argv[0], (void **) &Arg);

  LLVMAttribute retVal = LLVMGetAttribute((LLVMValueRef)Arg);

  return   enif_make_int(env, (int)retVal);
}

static ERL_NIF_TERM LLVMSetParamAlignment_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Arg;
  llvm_ptr_deref(env, argv[0], (void **) &Arg);

  unsigned align;
  enif_get_uint(env, argv[1], (unsigned*)&align);

LLVMSetParamAlignment((LLVMValueRef)Arg,(unsigned)align);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMBasicBlockAsValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

  LLVMValueRef retVal = LLVMBasicBlockAsValue((LLVMBasicBlockRef)BB);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMValueIsBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMBool retVal = LLVMValueIsBasicBlock((LLVMValueRef)Val);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMValueAsBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[0], (void **) &Val);

  LLVMBasicBlockRef retVal = LLVMValueAsBasicBlock((LLVMValueRef)Val);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMGetBasicBlockParent_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

  LLVMValueRef retVal = LLVMGetBasicBlockParent((LLVMBasicBlockRef)BB);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetBasicBlockTerminator_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

  LLVMValueRef retVal = LLVMGetBasicBlockTerminator((LLVMBasicBlockRef)BB);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMCountBasicBlocks_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  unsigned retVal = LLVMCountBasicBlocks((LLVMValueRef)Fn);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetBasicBlocks_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMBasicBlockRef * BasicBlocks;
  llvm_ptr_deref(env, argv[1], (void **) &BasicBlocks);

LLVMGetBasicBlocks((LLVMValueRef)Fn,(LLVMBasicBlockRef *)BasicBlocks);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetFirstBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMBasicBlockRef retVal = LLVMGetFirstBasicBlock((LLVMValueRef)Fn);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMGetLastBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMBasicBlockRef retVal = LLVMGetLastBasicBlock((LLVMValueRef)Fn);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMGetNextBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

  LLVMBasicBlockRef retVal = LLVMGetNextBasicBlock((LLVMBasicBlockRef)BB);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMGetPreviousBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

  LLVMBasicBlockRef retVal = LLVMGetPreviousBasicBlock((LLVMBasicBlockRef)BB);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMGetEntryBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMBasicBlockRef retVal = LLVMGetEntryBasicBlock((LLVMValueRef)Fn);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMAppendBasicBlockInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[1], (void **) &Fn);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMBasicBlockRef retVal = LLVMAppendBasicBlockInContext((LLVMContextRef)C,(LLVMValueRef)Fn,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMInsertBasicBlockInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[1], (void **) &BB);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMBasicBlockRef retVal = LLVMInsertBasicBlockInContext((LLVMContextRef)C,(LLVMBasicBlockRef)BB,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMAppendBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMBasicBlockRef retVal = LLVMAppendBasicBlock((LLVMValueRef)Fn,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMInsertBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef InsertBeforeBB;
  llvm_ptr_deref(env, argv[0], (void **) &InsertBeforeBB);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMBasicBlockRef retVal = LLVMInsertBasicBlock((LLVMBasicBlockRef)InsertBeforeBB,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMDeleteBasicBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

LLVMDeleteBasicBlock((LLVMBasicBlockRef)BB);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMRemoveBasicBlockFromParent_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

LLVMRemoveBasicBlockFromParent((LLVMBasicBlockRef)BB);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMMoveBasicBlockBefore_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

  LLVMBasicBlockRef MovePos;
  llvm_ptr_deref(env, argv[1], (void **) &MovePos);

LLVMMoveBasicBlockBefore((LLVMBasicBlockRef)BB,(LLVMBasicBlockRef)MovePos);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMMoveBasicBlockAfter_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

  LLVMBasicBlockRef MovePos;
  llvm_ptr_deref(env, argv[1], (void **) &MovePos);

LLVMMoveBasicBlockAfter((LLVMBasicBlockRef)BB,(LLVMBasicBlockRef)MovePos);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetFirstInstruction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

  LLVMValueRef retVal = LLVMGetFirstInstruction((LLVMBasicBlockRef)BB);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetLastInstruction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBasicBlockRef BB;
  llvm_ptr_deref(env, argv[0], (void **) &BB);

  LLVMValueRef retVal = LLVMGetLastInstruction((LLVMBasicBlockRef)BB);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetInstructionParent_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Inst;
  llvm_ptr_deref(env, argv[0], (void **) &Inst);

  LLVMBasicBlockRef retVal = LLVMGetInstructionParent((LLVMValueRef)Inst);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMGetNextInstruction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Inst;
  llvm_ptr_deref(env, argv[0], (void **) &Inst);

  LLVMValueRef retVal = LLVMGetNextInstruction((LLVMValueRef)Inst);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetPreviousInstruction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Inst;
  llvm_ptr_deref(env, argv[0], (void **) &Inst);

  LLVMValueRef retVal = LLVMGetPreviousInstruction((LLVMValueRef)Inst);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMInstructionEraseFromParent_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Inst;
  llvm_ptr_deref(env, argv[0], (void **) &Inst);

LLVMInstructionEraseFromParent((LLVMValueRef)Inst);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetInstructionOpcode_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Inst;
  llvm_ptr_deref(env, argv[0], (void **) &Inst);

  LLVMOpcode retVal = LLVMGetInstructionOpcode((LLVMValueRef)Inst);

  return   enif_make_int(env, (int)retVal);
}

static ERL_NIF_TERM LLVMGetICmpPredicate_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Inst;
  llvm_ptr_deref(env, argv[0], (void **) &Inst);

  LLVMIntPredicate retVal = LLVMGetICmpPredicate((LLVMValueRef)Inst);

  return   enif_make_int(env, (int)retVal);
}

static ERL_NIF_TERM LLVMSetInstructionCallConv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Instr;
  llvm_ptr_deref(env, argv[0], (void **) &Instr);

  unsigned CC;
  enif_get_uint(env, argv[1], (unsigned*)&CC);

LLVMSetInstructionCallConv((LLVMValueRef)Instr,(unsigned)CC);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetInstructionCallConv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Instr;
  llvm_ptr_deref(env, argv[0], (void **) &Instr);

  unsigned retVal = LLVMGetInstructionCallConv((LLVMValueRef)Instr);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMAddInstrAttribute_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Instr;
  llvm_ptr_deref(env, argv[0], (void **) &Instr);

  unsigned index;
  enif_get_uint(env, argv[1], (unsigned*)&index);

  LLVMAttribute PA;
  enif_get_uint(env, argv[2], (LLVMAttribute*)&PA);

LLVMAddInstrAttribute((LLVMValueRef)Instr,(unsigned)index,(LLVMAttribute)PA);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMRemoveInstrAttribute_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Instr;
  llvm_ptr_deref(env, argv[0], (void **) &Instr);

  unsigned index;
  enif_get_uint(env, argv[1], (unsigned*)&index);

  LLVMAttribute PA;
  enif_get_uint(env, argv[2], (LLVMAttribute*)&PA);

LLVMRemoveInstrAttribute((LLVMValueRef)Instr,(unsigned)index,(LLVMAttribute)PA);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMSetInstrParamAlignment_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Instr;
  llvm_ptr_deref(env, argv[0], (void **) &Instr);

  unsigned index;
  enif_get_uint(env, argv[1], (unsigned*)&index);

  unsigned align;
  enif_get_uint(env, argv[2], (unsigned*)&align);

LLVMSetInstrParamAlignment((LLVMValueRef)Instr,(unsigned)index,(unsigned)align);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMIsTailCall_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef CallInst;
  llvm_ptr_deref(env, argv[0], (void **) &CallInst);

  LLVMBool retVal = LLVMIsTailCall((LLVMValueRef)CallInst);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMSetTailCall_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef CallInst;
  llvm_ptr_deref(env, argv[0], (void **) &CallInst);

  char *IsTailCall_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[1], (char*)IsTailCall_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool IsTailCall = (strcmp(IsTailCall_tmp,"true") == 0);

LLVMSetTailCall((LLVMValueRef)CallInst,(LLVMBool)IsTailCall);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetSwitchDefaultDest_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef SwitchInstr;
  llvm_ptr_deref(env, argv[0], (void **) &SwitchInstr);

  LLVMBasicBlockRef retVal = LLVMGetSwitchDefaultDest((LLVMValueRef)SwitchInstr);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMAddIncoming_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef PhiNode;
  llvm_ptr_deref(env, argv[0], (void **) &PhiNode);

  int IncomingValuessize = 0;
  ERL_NIF_TERM *IncomingValuesarray;
  enif_get_tuple(env, argv[1], &IncomingValuessize, (const ERL_NIF_TERM **)&IncomingValuesarray);
  LLVMValueRef * IncomingValues;
  if (IncomingValuessize == 0)
    IncomingValues = NULL;
  else {
    IncomingValues = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*IncomingValuessize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < IncomingValuessize; i++) {
      enif_get_tuple(env,*(IncomingValuesarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)IncomingValues+i);
    }
  }

  int IncomingBlockssize = 0;
  ERL_NIF_TERM *IncomingBlocksarray;
  enif_get_tuple(env, argv[2], &IncomingBlockssize, (const ERL_NIF_TERM **)&IncomingBlocksarray);
  LLVMBasicBlockRef * IncomingBlocks;
  if (IncomingBlockssize == 0)
    IncomingBlocks = NULL;
  else {
    IncomingBlocks = (LLVMBasicBlockRef *)malloc(sizeof(LLVMBasicBlockRef *)*IncomingBlockssize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < IncomingBlockssize; i++) {
      enif_get_tuple(env,*(IncomingBlocksarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)IncomingBlocks+i);
    }
  }

  unsigned Count;
  enif_get_uint(env, argv[3], (unsigned*)&Count);

LLVMAddIncoming((LLVMValueRef)PhiNode,(LLVMValueRef *)IncomingValues,(LLVMBasicBlockRef *)IncomingBlocks,(unsigned)Count);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMCountIncoming_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef PhiNode;
  llvm_ptr_deref(env, argv[0], (void **) &PhiNode);

  unsigned retVal = LLVMCountIncoming((LLVMValueRef)PhiNode);

  return   enif_make_uint(env, retVal);
}

static ERL_NIF_TERM LLVMGetIncomingValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef PhiNode;
  llvm_ptr_deref(env, argv[0], (void **) &PhiNode);

  unsigned Index;
  enif_get_uint(env, argv[1], (unsigned*)&Index);

  LLVMValueRef retVal = LLVMGetIncomingValue((LLVMValueRef)PhiNode,(unsigned)Index);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetIncomingBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef PhiNode;
  llvm_ptr_deref(env, argv[0], (void **) &PhiNode);

  unsigned Index;
  enif_get_uint(env, argv[1], (unsigned*)&Index);

  LLVMBasicBlockRef retVal = LLVMGetIncomingBlock((LLVMValueRef)PhiNode,(unsigned)Index);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMCreateBuilderInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef C;
  llvm_ptr_deref(env, argv[0], (void **) &C);

  LLVMBuilderRef retVal = LLVMCreateBuilderInContext((LLVMContextRef)C);

  return   llvm_ptr_create(env, RTLLVMBuilderRef, retVal);
}

static ERL_NIF_TERM LLVMCreateBuilder_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef retVal = LLVMCreateBuilder();

  return   llvm_ptr_create(env, RTLLVMBuilderRef, retVal);
}

static ERL_NIF_TERM LLVMPositionBuilder_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

  LLVMBasicBlockRef Block;
  llvm_ptr_deref(env, argv[1], (void **) &Block);

  LLVMValueRef Instr;
  llvm_ptr_deref(env, argv[2], (void **) &Instr);

LLVMPositionBuilder((LLVMBuilderRef)Builder,(LLVMBasicBlockRef)Block,(LLVMValueRef)Instr);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMPositionBuilderBefore_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

  LLVMValueRef Instr;
  llvm_ptr_deref(env, argv[1], (void **) &Instr);

LLVMPositionBuilderBefore((LLVMBuilderRef)Builder,(LLVMValueRef)Instr);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMPositionBuilderAtEnd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

  LLVMBasicBlockRef Block;
  llvm_ptr_deref(env, argv[1], (void **) &Block);

LLVMPositionBuilderAtEnd((LLVMBuilderRef)Builder,(LLVMBasicBlockRef)Block);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetInsertBlock_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

  LLVMBasicBlockRef retVal = LLVMGetInsertBlock((LLVMBuilderRef)Builder);

  return   llvm_ptr_create(env, RTLLVMBasicBlockRef, retVal);
}

static ERL_NIF_TERM LLVMClearInsertionPosition_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

LLVMClearInsertionPosition((LLVMBuilderRef)Builder);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMInsertIntoBuilder_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

  LLVMValueRef Instr;
  llvm_ptr_deref(env, argv[1], (void **) &Instr);

LLVMInsertIntoBuilder((LLVMBuilderRef)Builder,(LLVMValueRef)Instr);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMInsertIntoBuilderWithName_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

  LLVMValueRef Instr;
  llvm_ptr_deref(env, argv[1], (void **) &Instr);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

LLVMInsertIntoBuilderWithName((LLVMBuilderRef)Builder,(LLVMValueRef)Instr,(const char *)Name);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMDisposeBuilder_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

LLVMDisposeBuilder((LLVMBuilderRef)Builder);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMSetCurrentDebugLocation_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

  LLVMValueRef L;
  llvm_ptr_deref(env, argv[1], (void **) &L);

LLVMSetCurrentDebugLocation((LLVMBuilderRef)Builder,(LLVMValueRef)L);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetCurrentDebugLocation_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

  LLVMValueRef retVal = LLVMGetCurrentDebugLocation((LLVMBuilderRef)Builder);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMSetInstDebugLocation_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef Builder;
  llvm_ptr_deref(env, argv[0], (void **) &Builder);

  LLVMValueRef Inst;
  llvm_ptr_deref(env, argv[1], (void **) &Inst);

LLVMSetInstDebugLocation((LLVMBuilderRef)Builder,(LLVMValueRef)Inst);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMBuildRetVoid_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef retVal = LLVMBuildRetVoid((LLVMBuilderRef)B);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildRet_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef V;
  llvm_ptr_deref(env, argv[1], (void **) &V);

  LLVMValueRef retVal = LLVMBuildRet((LLVMBuilderRef)B,(LLVMValueRef)V);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildAggregateRet_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  int RetValssize = 0;
  ERL_NIF_TERM *RetValsarray;
  enif_get_tuple(env, argv[1], &RetValssize, (const ERL_NIF_TERM **)&RetValsarray);
  LLVMValueRef * RetVals;
  if (RetValssize == 0)
    RetVals = NULL;
  else {
    RetVals = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*RetValssize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < RetValssize; i++) {
      enif_get_tuple(env,*(RetValsarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)RetVals+i);
    }
  }

  unsigned N;
  enif_get_uint(env, argv[2], (unsigned*)&N);

  LLVMValueRef retVal = LLVMBuildAggregateRet((LLVMBuilderRef)B,(LLVMValueRef *)RetVals,(unsigned)N);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildBr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMBasicBlockRef Dest;
  llvm_ptr_deref(env, argv[1], (void **) &Dest);

  LLVMValueRef retVal = LLVMBuildBr((LLVMBuilderRef)B,(LLVMBasicBlockRef)Dest);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildCondBr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef If;
  llvm_ptr_deref(env, argv[1], (void **) &If);

  LLVMBasicBlockRef Then;
  llvm_ptr_deref(env, argv[2], (void **) &Then);

  LLVMBasicBlockRef Else;
  llvm_ptr_deref(env, argv[3], (void **) &Else);

  LLVMValueRef retVal = LLVMBuildCondBr((LLVMBuilderRef)B,(LLVMValueRef)If,(LLVMBasicBlockRef)Then,(LLVMBasicBlockRef)Else);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildSwitch_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef V;
  llvm_ptr_deref(env, argv[1], (void **) &V);

  LLVMBasicBlockRef Else;
  llvm_ptr_deref(env, argv[2], (void **) &Else);

  unsigned NumCases;
  enif_get_uint(env, argv[3], (unsigned*)&NumCases);

  LLVMValueRef retVal = LLVMBuildSwitch((LLVMBuilderRef)B,(LLVMValueRef)V,(LLVMBasicBlockRef)Else,(unsigned)NumCases);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildIndirectBr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Addr;
  llvm_ptr_deref(env, argv[1], (void **) &Addr);

  unsigned NumDests;
  enif_get_uint(env, argv[2], (unsigned*)&NumDests);

  LLVMValueRef retVal = LLVMBuildIndirectBr((LLVMBuilderRef)B,(LLVMValueRef)Addr,(unsigned)NumDests);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildInvoke_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[1], (void **) &Fn);

  int Argssize = 0;
  ERL_NIF_TERM *Argsarray;
  enif_get_tuple(env, argv[2], &Argssize, (const ERL_NIF_TERM **)&Argsarray);
  LLVMValueRef * Args;
  if (Argssize == 0)
    Args = NULL;
  else {
    Args = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*Argssize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < Argssize; i++) {
      enif_get_tuple(env,*(Argsarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)Args+i);
    }
  }

  unsigned NumArgs;
  enif_get_uint(env, argv[3], (unsigned*)&NumArgs);

  LLVMBasicBlockRef Then;
  llvm_ptr_deref(env, argv[4], (void **) &Then);

  LLVMBasicBlockRef Catch;
  llvm_ptr_deref(env, argv[5], (void **) &Catch);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[6], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildInvoke((LLVMBuilderRef)B,(LLVMValueRef)Fn,(LLVMValueRef *)Args,(unsigned)NumArgs,(LLVMBasicBlockRef)Then,(LLVMBasicBlockRef)Catch,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildLandingPad_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[1], (void **) &Ty);

  LLVMValueRef PersFn;
  llvm_ptr_deref(env, argv[2], (void **) &PersFn);

  unsigned NumClauses;
  enif_get_uint(env, argv[3], (unsigned*)&NumClauses);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildLandingPad((LLVMBuilderRef)B,(LLVMTypeRef)Ty,(LLVMValueRef)PersFn,(unsigned)NumClauses,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildResume_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Exn;
  llvm_ptr_deref(env, argv[1], (void **) &Exn);

  LLVMValueRef retVal = LLVMBuildResume((LLVMBuilderRef)B,(LLVMValueRef)Exn);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildUnreachable_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef retVal = LLVMBuildUnreachable((LLVMBuilderRef)B);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMAddCase_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Switch;
  llvm_ptr_deref(env, argv[0], (void **) &Switch);

  LLVMValueRef OnVal;
  llvm_ptr_deref(env, argv[1], (void **) &OnVal);

  LLVMBasicBlockRef Dest;
  llvm_ptr_deref(env, argv[2], (void **) &Dest);

LLVMAddCase((LLVMValueRef)Switch,(LLVMValueRef)OnVal,(LLVMBasicBlockRef)Dest);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMAddDestination_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef IndirectBr;
  llvm_ptr_deref(env, argv[0], (void **) &IndirectBr);

  LLVMBasicBlockRef Dest;
  llvm_ptr_deref(env, argv[1], (void **) &Dest);

LLVMAddDestination((LLVMValueRef)IndirectBr,(LLVMBasicBlockRef)Dest);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMAddClause_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LandingPad;
  llvm_ptr_deref(env, argv[0], (void **) &LandingPad);

  LLVMValueRef ClauseVal;
  llvm_ptr_deref(env, argv[1], (void **) &ClauseVal);

LLVMAddClause((LLVMValueRef)LandingPad,(LLVMValueRef)ClauseVal);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMSetCleanup_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef LandingPad;
  llvm_ptr_deref(env, argv[0], (void **) &LandingPad);

  char *Val_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[1], (char*)Val_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool Val = (strcmp(Val_tmp,"true") == 0);

LLVMSetCleanup((LLVMValueRef)LandingPad,(LLVMBool)Val);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMBuildAdd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildAdd((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNSWAdd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNSWAdd((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNUWAdd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNUWAdd((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFAdd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFAdd((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildSub_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildSub((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNSWSub_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNSWSub((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNUWSub_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNUWSub((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFSub_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFSub((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildMul_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildMul((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNSWMul_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNSWMul((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNUWMul_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNUWMul((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFMul_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFMul((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildUDiv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildUDiv((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildSDiv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildSDiv((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildExactSDiv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildExactSDiv((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFDiv_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFDiv((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildURem_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildURem((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildSRem_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildSRem((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFRem_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFRem((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildShl_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildShl((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildLShr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildLShr((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildAShr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildAShr((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildAnd_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildAnd((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildOr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildOr((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildXor_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildXor((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildBinOp_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMOpcode Op;
  enif_get_uint(env, argv[1], (LLVMOpcode*)&Op);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[2], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[3], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildBinOp((LLVMBuilderRef)B,(LLVMOpcode)Op,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNeg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef V;
  llvm_ptr_deref(env, argv[1], (void **) &V);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNeg((LLVMBuilderRef)B,(LLVMValueRef)V,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNSWNeg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef V;
  llvm_ptr_deref(env, argv[1], (void **) &V);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNSWNeg((LLVMBuilderRef)B,(LLVMValueRef)V,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNUWNeg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef V;
  llvm_ptr_deref(env, argv[1], (void **) &V);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNUWNeg((LLVMBuilderRef)B,(LLVMValueRef)V,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFNeg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef V;
  llvm_ptr_deref(env, argv[1], (void **) &V);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFNeg((LLVMBuilderRef)B,(LLVMValueRef)V,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildNot_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef V;
  llvm_ptr_deref(env, argv[1], (void **) &V);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildNot((LLVMBuilderRef)B,(LLVMValueRef)V,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildMalloc_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[1], (void **) &Ty);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildMalloc((LLVMBuilderRef)B,(LLVMTypeRef)Ty,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildArrayMalloc_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[1], (void **) &Ty);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[2], (void **) &Val);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildArrayMalloc((LLVMBuilderRef)B,(LLVMTypeRef)Ty,(LLVMValueRef)Val,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildAlloca_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[1], (void **) &Ty);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildAlloca((LLVMBuilderRef)B,(LLVMTypeRef)Ty,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildArrayAlloca_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[1], (void **) &Ty);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[2], (void **) &Val);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildArrayAlloca((LLVMBuilderRef)B,(LLVMTypeRef)Ty,(LLVMValueRef)Val,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFree_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef PointerVal;
  llvm_ptr_deref(env, argv[1], (void **) &PointerVal);

  LLVMValueRef retVal = LLVMBuildFree((LLVMBuilderRef)B,(LLVMValueRef)PointerVal);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildLoad_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef PointerVal;
  llvm_ptr_deref(env, argv[1], (void **) &PointerVal);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildLoad((LLVMBuilderRef)B,(LLVMValueRef)PointerVal,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildStore_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMValueRef Ptr;
  llvm_ptr_deref(env, argv[2], (void **) &Ptr);

  LLVMValueRef retVal = LLVMBuildStore((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMValueRef)Ptr);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildGEP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Pointer;
  llvm_ptr_deref(env, argv[1], (void **) &Pointer);

  int Indicessize = 0;
  ERL_NIF_TERM *Indicesarray;
  enif_get_tuple(env, argv[2], &Indicessize, (const ERL_NIF_TERM **)&Indicesarray);
  LLVMValueRef * Indices;
  if (Indicessize == 0)
    Indices = NULL;
  else {
    Indices = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*Indicessize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < Indicessize; i++) {
      enif_get_tuple(env,*(Indicesarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)Indices+i);
    }
  }

  unsigned NumIndices;
  enif_get_uint(env, argv[3], (unsigned*)&NumIndices);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildGEP((LLVMBuilderRef)B,(LLVMValueRef)Pointer,(LLVMValueRef *)Indices,(unsigned)NumIndices,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildInBoundsGEP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Pointer;
  llvm_ptr_deref(env, argv[1], (void **) &Pointer);

  int Indicessize = 0;
  ERL_NIF_TERM *Indicesarray;
  enif_get_tuple(env, argv[2], &Indicessize, (const ERL_NIF_TERM **)&Indicesarray);
  LLVMValueRef * Indices;
  if (Indicessize == 0)
    Indices = NULL;
  else {
    Indices = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*Indicessize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < Indicessize; i++) {
      enif_get_tuple(env,*(Indicesarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)Indices+i);
    }
  }

  unsigned NumIndices;
  enif_get_uint(env, argv[3], (unsigned*)&NumIndices);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildInBoundsGEP((LLVMBuilderRef)B,(LLVMValueRef)Pointer,(LLVMValueRef *)Indices,(unsigned)NumIndices,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildStructGEP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Pointer;
  llvm_ptr_deref(env, argv[1], (void **) &Pointer);

  unsigned Idx;
  enif_get_uint(env, argv[2], (unsigned*)&Idx);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildStructGEP((LLVMBuilderRef)B,(LLVMValueRef)Pointer,(unsigned)Idx,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildGlobalString_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  char *Str = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Str, 255, ERL_NIF_LATIN1);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildGlobalString((LLVMBuilderRef)B,(const char *)Str,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildGlobalStringPtr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  char *Str = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Str, 255, ERL_NIF_LATIN1);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildGlobalStringPtr((LLVMBuilderRef)B,(const char *)Str,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMGetVolatile_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef MemoryAccessInst;
  llvm_ptr_deref(env, argv[0], (void **) &MemoryAccessInst);

  LLVMBool retVal = LLVMGetVolatile((LLVMValueRef)MemoryAccessInst);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMSetVolatile_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef MemoryAccessInst;
  llvm_ptr_deref(env, argv[0], (void **) &MemoryAccessInst);

  char *IsVolatile_tmp = (char *) malloc(sizeof(char) * 255);
  enif_get_atom(env, argv[1], (char*)IsVolatile_tmp, 255, ERL_NIF_LATIN1);
  LLVMBool IsVolatile = (strcmp(IsVolatile_tmp,"true") == 0);

LLVMSetVolatile((LLVMValueRef)MemoryAccessInst,(LLVMBool)IsVolatile);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMBuildTrunc_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildTrunc((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildZExt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildZExt((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildSExt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildSExt((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFPToUI_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFPToUI((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFPToSI_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFPToSI((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildUIToFP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildUIToFP((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildSIToFP_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildSIToFP((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFPTrunc_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFPTrunc((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFPExt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFPExt((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildPtrToInt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildPtrToInt((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildIntToPtr_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildIntToPtr((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildBitCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildBitCast((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildZExtOrBitCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildZExtOrBitCast((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildSExtOrBitCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildSExtOrBitCast((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildTruncOrBitCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildTruncOrBitCast((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMOpcode Op;
  enif_get_uint(env, argv[1], (LLVMOpcode*)&Op);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[2], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[3], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildCast((LLVMBuilderRef)B,(LLVMOpcode)Op,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildPointerCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildPointerCast((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildIntCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildIntCast((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFPCast_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  LLVMTypeRef DestTy;
  llvm_ptr_deref(env, argv[2], (void **) &DestTy);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFPCast((LLVMBuilderRef)B,(LLVMValueRef)Val,(LLVMTypeRef)DestTy,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildICmp_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMIntPredicate Op;
  enif_get_uint(env, argv[1], (LLVMIntPredicate*)&Op);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[2], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[3], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildICmp((LLVMBuilderRef)B,(LLVMIntPredicate)Op,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildFCmp_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMRealPredicate Op;
  enif_get_uint(env, argv[1], (LLVMRealPredicate*)&Op);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[2], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[3], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildFCmp((LLVMBuilderRef)B,(LLVMRealPredicate)Op,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildPhi_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[1], (void **) &Ty);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildPhi((LLVMBuilderRef)B,(LLVMTypeRef)Ty,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildCall_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[1], (void **) &Fn);

  int Argssize = 0;
  ERL_NIF_TERM *Argsarray;
  enif_get_tuple(env, argv[2], &Argssize, (const ERL_NIF_TERM **)&Argsarray);
  LLVMValueRef * Args;
  if (Argssize == 0)
    Args = NULL;
  else {
    Args = (LLVMValueRef *)malloc(sizeof(LLVMValueRef *)*Argssize);
    int i,local_size=0;
    ERL_NIF_TERM *local_array;
    for(i = 0;i < Argssize; i++) {
      enif_get_tuple(env,*(Argsarray+i), &local_size, (const ERL_NIF_TERM **)&local_array);
      llvm_ptr_deref(env,*(local_array+1),(void **)Args+i);
    }
  }

  unsigned NumArgs;
  enif_get_uint(env, argv[3], (unsigned*)&NumArgs);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildCall((LLVMBuilderRef)B,(LLVMValueRef)Fn,(LLVMValueRef *)Args,(unsigned)NumArgs,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildSelect_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef If;
  llvm_ptr_deref(env, argv[1], (void **) &If);

  LLVMValueRef Then;
  llvm_ptr_deref(env, argv[2], (void **) &Then);

  LLVMValueRef Else;
  llvm_ptr_deref(env, argv[3], (void **) &Else);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildSelect((LLVMBuilderRef)B,(LLVMValueRef)If,(LLVMValueRef)Then,(LLVMValueRef)Else,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildVAArg_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef List;
  llvm_ptr_deref(env, argv[1], (void **) &List);

  LLVMTypeRef Ty;
  llvm_ptr_deref(env, argv[2], (void **) &Ty);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildVAArg((LLVMBuilderRef)B,(LLVMValueRef)List,(LLVMTypeRef)Ty,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildExtractElement_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef VecVal;
  llvm_ptr_deref(env, argv[1], (void **) &VecVal);

  LLVMValueRef Index;
  llvm_ptr_deref(env, argv[2], (void **) &Index);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildExtractElement((LLVMBuilderRef)B,(LLVMValueRef)VecVal,(LLVMValueRef)Index,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildInsertElement_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef VecVal;
  llvm_ptr_deref(env, argv[1], (void **) &VecVal);

  LLVMValueRef EltVal;
  llvm_ptr_deref(env, argv[2], (void **) &EltVal);

  LLVMValueRef Index;
  llvm_ptr_deref(env, argv[3], (void **) &Index);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildInsertElement((LLVMBuilderRef)B,(LLVMValueRef)VecVal,(LLVMValueRef)EltVal,(LLVMValueRef)Index,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildShuffleVector_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef V1;
  llvm_ptr_deref(env, argv[1], (void **) &V1);

  LLVMValueRef V2;
  llvm_ptr_deref(env, argv[2], (void **) &V2);

  LLVMValueRef Mask;
  llvm_ptr_deref(env, argv[3], (void **) &Mask);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildShuffleVector((LLVMBuilderRef)B,(LLVMValueRef)V1,(LLVMValueRef)V2,(LLVMValueRef)Mask,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildExtractValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef AggVal;
  llvm_ptr_deref(env, argv[1], (void **) &AggVal);

  unsigned Index;
  enif_get_uint(env, argv[2], (unsigned*)&Index);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildExtractValue((LLVMBuilderRef)B,(LLVMValueRef)AggVal,(unsigned)Index,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildInsertValue_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef AggVal;
  llvm_ptr_deref(env, argv[1], (void **) &AggVal);

  LLVMValueRef EltVal;
  llvm_ptr_deref(env, argv[2], (void **) &EltVal);

  unsigned Index;
  enif_get_uint(env, argv[3], (unsigned*)&Index);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[4], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildInsertValue((LLVMBuilderRef)B,(LLVMValueRef)AggVal,(LLVMValueRef)EltVal,(unsigned)Index,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildIsNull_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildIsNull((LLVMBuilderRef)B,(LLVMValueRef)Val,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildIsNotNull_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef Val;
  llvm_ptr_deref(env, argv[1], (void **) &Val);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[2], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildIsNotNull((LLVMBuilderRef)B,(LLVMValueRef)Val,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMBuildPtrDiff_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMBuilderRef B;
  llvm_ptr_deref(env, argv[0], (void **) &B);

  LLVMValueRef LHS;
  llvm_ptr_deref(env, argv[1], (void **) &LHS);

  LLVMValueRef RHS;
  llvm_ptr_deref(env, argv[2], (void **) &RHS);

  char *Name = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[3], (char*)Name, 255, ERL_NIF_LATIN1);

  LLVMValueRef retVal = LLVMBuildPtrDiff((LLVMBuilderRef)B,(LLVMValueRef)LHS,(LLVMValueRef)RHS,(const char *)Name);

  return   llvm_ptr_create(env, RTLLVMValueRef, retVal);
}

static ERL_NIF_TERM LLVMCreateModuleProviderForExistingModule_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMModuleProviderRef retVal = LLVMCreateModuleProviderForExistingModule((LLVMModuleRef)M);

  return   llvm_ptr_create(env, RTLLVMModuleProviderRef, retVal);
}

static ERL_NIF_TERM LLVMDisposeModuleProvider_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleProviderRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

LLVMDisposeModuleProvider((LLVMModuleProviderRef)M);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMCreateMemoryBufferWithContentsOfFile_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  char *Path = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[0], (char*)Path, 255, ERL_NIF_LATIN1);

  LLVMMemoryBufferRef * OutMemBuf = (LLVMMemoryBufferRef *)calloc(1,sizeof(LLVMMemoryBufferRef *));

  char ** OutMessage = (char **)calloc(1,sizeof(char **));

  LLVMBool retVal = LLVMCreateMemoryBufferWithContentsOfFile((const char *)Path,(LLVMMemoryBufferRef *)OutMemBuf,(char **)OutMessage);

  return   enif_make_tuple3(env,   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false"),llvm_ptr_create(env, RTLLVMMemoryBufferRef,*OutMemBuf),*OutMessage != NULL?enif_make_string(env, *OutMessage,ERL_NIF_LATIN1):enif_make_list(env,0));

;
}

static ERL_NIF_TERM LLVMDisposeMemoryBuffer_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMMemoryBufferRef MemBuf;
  llvm_ptr_deref(env, argv[0], (void **) &MemBuf);

LLVMDisposeMemoryBuffer((LLVMMemoryBufferRef)MemBuf);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMGetGlobalPassRegistry_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMPassRegistryRef retVal = LLVMGetGlobalPassRegistry();

  return   llvm_ptr_create(env, RTLLVMPassRegistryRef, retVal);
}

static ERL_NIF_TERM LLVMCreatePassManager_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMPassManagerRef retVal = LLVMCreatePassManager();

  return   llvm_ptr_create(env, RTLLVMPassManagerRef, retVal);
}

static ERL_NIF_TERM LLVMCreateFunctionPassManagerForModule_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMPassManagerRef retVal = LLVMCreateFunctionPassManagerForModule((LLVMModuleRef)M);

  return   llvm_ptr_create(env, RTLLVMPassManagerRef, retVal);
}

static ERL_NIF_TERM LLVMCreateFunctionPassManager_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleProviderRef MP;
  llvm_ptr_deref(env, argv[0], (void **) &MP);

  LLVMPassManagerRef retVal = LLVMCreateFunctionPassManager((LLVMModuleProviderRef)MP);

  return   llvm_ptr_create(env, RTLLVMPassManagerRef, retVal);
}

static ERL_NIF_TERM LLVMRunPassManager_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMPassManagerRef PM;
  llvm_ptr_deref(env, argv[0], (void **) &PM);

  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[1], (void **) &M);

  LLVMBool retVal = LLVMRunPassManager((LLVMPassManagerRef)PM,(LLVMModuleRef)M);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMInitializeFunctionPassManager_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMPassManagerRef FPM;
  llvm_ptr_deref(env, argv[0], (void **) &FPM);

  LLVMBool retVal = LLVMInitializeFunctionPassManager((LLVMPassManagerRef)FPM);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMRunFunctionPassManager_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMPassManagerRef FPM;
  llvm_ptr_deref(env, argv[0], (void **) &FPM);

  LLVMValueRef F;
  llvm_ptr_deref(env, argv[1], (void **) &F);

  LLVMBool retVal = LLVMRunFunctionPassManager((LLVMPassManagerRef)FPM,(LLVMValueRef)F);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMFinalizeFunctionPassManager_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMPassManagerRef FPM;
  llvm_ptr_deref(env, argv[0], (void **) &FPM);

  LLVMBool retVal = LLVMFinalizeFunctionPassManager((LLVMPassManagerRef)FPM);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMDisposePassManager_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMPassManagerRef PM;
  llvm_ptr_deref(env, argv[0], (void **) &PM);

LLVMDisposePassManager((LLVMPassManagerRef)PM);

  return enif_make_atom(env,"ok");
}

// --- Stop generating from Core_8h.xml

// -- Start generating from BitWriter_8h.xml on {{2012,2,25},{14,37,57}}--

static ERL_NIF_TERM LLVMWriteBitcodeToFile_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  char *Path = (char *) malloc(sizeof(char) * 255);
  enif_get_string(env, argv[1], (char*)Path, 255, ERL_NIF_LATIN1);

  int retVal = LLVMWriteBitcodeToFile((LLVMModuleRef)M,(const char *)Path);

  return   enif_make_int(env, retVal);
}

static ERL_NIF_TERM LLVMWriteBitcodeToFD_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  int FD;
  enif_get_int(env, argv[1], (int*)&FD);

  int ShouldClose;
  enif_get_int(env, argv[2], (int*)&ShouldClose);

  int Unbuffered;
  enif_get_int(env, argv[3], (int*)&Unbuffered);

  int retVal = LLVMWriteBitcodeToFD((LLVMModuleRef)M,(int)FD,(int)ShouldClose,(int)Unbuffered);

  return   enif_make_int(env, retVal);
}

static ERL_NIF_TERM LLVMWriteBitcodeToFileHandle_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  int Handle;
  enif_get_int(env, argv[1], (int*)&Handle);

  int retVal = LLVMWriteBitcodeToFileHandle((LLVMModuleRef)M,(int)Handle);

  return   enif_make_int(env, retVal);
}

// --- Stop generating from BitWriter_8h.xml

// -- Start generating from BitReader_8h.xml on {{2012,2,25},{14,37,57}}--

static ERL_NIF_TERM LLVMParseBitcode_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMMemoryBufferRef MemBuf;
  llvm_ptr_deref(env, argv[0], (void **) &MemBuf);

  LLVMModuleRef * OutModule = (LLVMModuleRef *)calloc(1,sizeof(LLVMModuleRef *));

  char ** OutMessage = (char **)calloc(1,sizeof(char **));

  LLVMBool retVal = LLVMParseBitcode((LLVMMemoryBufferRef)MemBuf,(LLVMModuleRef *)OutModule,(char **)OutMessage);

  return   enif_make_tuple3(env,   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false"),llvm_ptr_create(env, RTLLVMModuleRef,*OutModule),*OutMessage != NULL?enif_make_string(env, *OutMessage,ERL_NIF_LATIN1):enif_make_list(env,0));

;
}

static ERL_NIF_TERM LLVMParseBitcodeInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef ContextRef;
  llvm_ptr_deref(env, argv[0], (void **) &ContextRef);

  LLVMMemoryBufferRef MemBuf;
  llvm_ptr_deref(env, argv[1], (void **) &MemBuf);

  LLVMModuleRef * OutModule = (LLVMModuleRef *)calloc(1,sizeof(LLVMModuleRef *));

  char ** OutMessage = (char **)calloc(1,sizeof(char **));

  LLVMBool retVal = LLVMParseBitcodeInContext((LLVMContextRef)ContextRef,(LLVMMemoryBufferRef)MemBuf,(LLVMModuleRef *)OutModule,(char **)OutMessage);

  return   enif_make_tuple3(env,   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false"),llvm_ptr_create(env, RTLLVMModuleRef,*OutModule),*OutMessage != NULL?enif_make_string(env, *OutMessage,ERL_NIF_LATIN1):enif_make_list(env,0));

;
}

static ERL_NIF_TERM LLVMGetBitcodeModuleInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef ContextRef;
  llvm_ptr_deref(env, argv[0], (void **) &ContextRef);

  LLVMMemoryBufferRef MemBuf;
  llvm_ptr_deref(env, argv[1], (void **) &MemBuf);

  LLVMModuleRef * OutM = (LLVMModuleRef *)calloc(1,sizeof(LLVMModuleRef *));

  char ** OutMessage = (char **)calloc(1,sizeof(char **));

  LLVMBool retVal = LLVMGetBitcodeModuleInContext((LLVMContextRef)ContextRef,(LLVMMemoryBufferRef)MemBuf,(LLVMModuleRef *)OutM,(char **)OutMessage);

  return   enif_make_tuple3(env,   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false"),llvm_ptr_create(env, RTLLVMModuleRef,*OutM),*OutMessage != NULL?enif_make_string(env, *OutMessage,ERL_NIF_LATIN1):enif_make_list(env,0));

;
}

static ERL_NIF_TERM LLVMGetBitcodeModule_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMMemoryBufferRef MemBuf;
  llvm_ptr_deref(env, argv[0], (void **) &MemBuf);

  LLVMModuleRef * OutM = (LLVMModuleRef *)calloc(1,sizeof(LLVMModuleRef *));

  char ** OutMessage = (char **)calloc(1,sizeof(char **));

  LLVMBool retVal = LLVMGetBitcodeModule((LLVMMemoryBufferRef)MemBuf,(LLVMModuleRef *)OutM,(char **)OutMessage);

  return   enif_make_tuple3(env,   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false"),llvm_ptr_create(env, RTLLVMModuleRef,*OutM),*OutMessage != NULL?enif_make_string(env, *OutMessage,ERL_NIF_LATIN1):enif_make_list(env,0));

;
}

static ERL_NIF_TERM LLVMGetBitcodeModuleProviderInContext_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMContextRef ContextRef;
  llvm_ptr_deref(env, argv[0], (void **) &ContextRef);

  LLVMMemoryBufferRef MemBuf;
  llvm_ptr_deref(env, argv[1], (void **) &MemBuf);

  LLVMModuleProviderRef * OutMP = (LLVMModuleProviderRef *)calloc(1,sizeof(LLVMModuleProviderRef *));

  char ** OutMessage = (char **)calloc(1,sizeof(char **));

  LLVMBool retVal = LLVMGetBitcodeModuleProviderInContext((LLVMContextRef)ContextRef,(LLVMMemoryBufferRef)MemBuf,(LLVMModuleProviderRef *)OutMP,(char **)OutMessage);

  return   enif_make_tuple3(env,   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false"),llvm_ptr_create(env, RTLLVMModuleProviderRef,*OutMP),*OutMessage != NULL?enif_make_string(env, *OutMessage,ERL_NIF_LATIN1):enif_make_list(env,0));

;
}

static ERL_NIF_TERM LLVMGetBitcodeModuleProvider_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMMemoryBufferRef MemBuf;
  llvm_ptr_deref(env, argv[0], (void **) &MemBuf);

  LLVMModuleProviderRef * OutMP = (LLVMModuleProviderRef *)calloc(1,sizeof(LLVMModuleProviderRef *));

  char ** OutMessage = (char **)calloc(1,sizeof(char **));

  LLVMBool retVal = LLVMGetBitcodeModuleProvider((LLVMMemoryBufferRef)MemBuf,(LLVMModuleProviderRef *)OutMP,(char **)OutMessage);

  return   enif_make_tuple3(env,   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false"),llvm_ptr_create(env, RTLLVMModuleProviderRef,*OutMP),*OutMessage != NULL?enif_make_string(env, *OutMessage,ERL_NIF_LATIN1):enif_make_list(env,0));

;
}

// --- Stop generating from BitReader_8h.xml

// -- Start generating from Analysis_8h.xml on {{2012,2,25},{14,37,57}}--

static ERL_NIF_TERM LLVMVerifyModule_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMModuleRef M;
  llvm_ptr_deref(env, argv[0], (void **) &M);

  LLVMVerifierFailureAction Action;
  llvm_ptr_deref(env, argv[1], (void **) &Action);

  char ** OutMessage = (char **)calloc(1,sizeof(char **));

  LLVMBool retVal = LLVMVerifyModule((LLVMModuleRef)M,(LLVMVerifierFailureAction)Action,(char **)OutMessage);

  return   enif_make_tuple2(env,   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false"),*OutMessage != NULL?enif_make_string(env, *OutMessage,ERL_NIF_LATIN1):enif_make_list(env,0));

;
}

static ERL_NIF_TERM LLVMVerifyFunction_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

  LLVMVerifierFailureAction Action;
  llvm_ptr_deref(env, argv[1], (void **) &Action);

  LLVMBool retVal = LLVMVerifyFunction((LLVMValueRef)Fn,(LLVMVerifierFailureAction)Action);

  return   retVal ? enif_make_atom(env,"true") : enif_make_atom(env,"false");
}

static ERL_NIF_TERM LLVMViewFunctionCFG_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

LLVMViewFunctionCFG((LLVMValueRef)Fn);

  return enif_make_atom(env,"ok");
}

static ERL_NIF_TERM LLVMViewFunctionCFGOnly_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  LLVMValueRef Fn;
  llvm_ptr_deref(env, argv[0], (void **) &Fn);

LLVMViewFunctionCFGOnly((LLVMValueRef)Fn);

  return enif_make_atom(env,"ok");
}

// --- Stop generating from Analysis_8h.xml


static ErlNifFunc nif_funcs[] =
  {
// @@NIF_MAPPINGS@@
// -- Start generating from Disassembler_8h.xml on {{2012,2,25},{14,37,59}}--

// --- Stop generating from Disassembler_8h.xml

// -- Start generating from Core_8h.xml on {{2012,2,25},{14,37,58}}--

    {"LLVMDisposeMessage_internal",1,LLVMDisposeMessage_nif},
    {"LLVMContextCreate_internal",0,LLVMContextCreate_nif},
    {"LLVMGetGlobalContext_internal",0,LLVMGetGlobalContext_nif},
    {"LLVMContextDispose_internal",1,LLVMContextDispose_nif},
    {"LLVMGetMDKindIDInContext_internal",3,LLVMGetMDKindIDInContext_nif},
    {"LLVMGetMDKindID_internal",2,LLVMGetMDKindID_nif},
    {"LLVMModuleCreateWithName_internal",1,LLVMModuleCreateWithName_nif},
    {"LLVMModuleCreateWithNameInContext_internal",2,LLVMModuleCreateWithNameInContext_nif},
    {"LLVMDisposeModule_internal",1,LLVMDisposeModule_nif},
    {"LLVMGetDataLayout_internal",1,LLVMGetDataLayout_nif},
    {"LLVMSetDataLayout_internal",2,LLVMSetDataLayout_nif},
    {"LLVMGetTarget_internal",1,LLVMGetTarget_nif},
    {"LLVMSetTarget_internal",2,LLVMSetTarget_nif},
    {"LLVMDumpModule_internal",1,LLVMDumpModule_nif},
    {"LLVMSetModuleInlineAsm_internal",2,LLVMSetModuleInlineAsm_nif},
    {"LLVMGetModuleContext_internal",1,LLVMGetModuleContext_nif},
    {"LLVMGetTypeKind_internal",1,LLVMGetTypeKind_nif},
    {"LLVMTypeIsSized_internal",1,LLVMTypeIsSized_nif},
    {"LLVMGetTypeContext_internal",1,LLVMGetTypeContext_nif},
    {"LLVMInt1TypeInContext_internal",1,LLVMInt1TypeInContext_nif},
    {"LLVMInt8TypeInContext_internal",1,LLVMInt8TypeInContext_nif},
    {"LLVMInt16TypeInContext_internal",1,LLVMInt16TypeInContext_nif},
    {"LLVMInt32TypeInContext_internal",1,LLVMInt32TypeInContext_nif},
    {"LLVMInt64TypeInContext_internal",1,LLVMInt64TypeInContext_nif},
    {"LLVMIntTypeInContext_internal",2,LLVMIntTypeInContext_nif},
    {"LLVMInt1Type_internal",0,LLVMInt1Type_nif},
    {"LLVMInt8Type_internal",0,LLVMInt8Type_nif},
    {"LLVMInt16Type_internal",0,LLVMInt16Type_nif},
    {"LLVMInt32Type_internal",0,LLVMInt32Type_nif},
    {"LLVMInt64Type_internal",0,LLVMInt64Type_nif},
    {"LLVMIntType_internal",1,LLVMIntType_nif},
    {"LLVMGetIntTypeWidth_internal",1,LLVMGetIntTypeWidth_nif},
    {"LLVMFloatTypeInContext_internal",1,LLVMFloatTypeInContext_nif},
    {"LLVMDoubleTypeInContext_internal",1,LLVMDoubleTypeInContext_nif},
    {"LLVMX86FP80TypeInContext_internal",1,LLVMX86FP80TypeInContext_nif},
    {"LLVMFP128TypeInContext_internal",1,LLVMFP128TypeInContext_nif},
    {"LLVMPPCFP128TypeInContext_internal",1,LLVMPPCFP128TypeInContext_nif},
    {"LLVMFloatType_internal",0,LLVMFloatType_nif},
    {"LLVMDoubleType_internal",0,LLVMDoubleType_nif},
    {"LLVMX86FP80Type_internal",0,LLVMX86FP80Type_nif},
    {"LLVMFP128Type_internal",0,LLVMFP128Type_nif},
    {"LLVMPPCFP128Type_internal",0,LLVMPPCFP128Type_nif},
    {"LLVMFunctionType_internal",4,LLVMFunctionType_nif},
    {"LLVMIsFunctionVarArg_internal",1,LLVMIsFunctionVarArg_nif},
    {"LLVMGetReturnType_internal",1,LLVMGetReturnType_nif},
    {"LLVMCountParamTypes_internal",1,LLVMCountParamTypes_nif},
    {"LLVMGetParamTypes_internal",2,LLVMGetParamTypes_nif},
    {"LLVMStructTypeInContext_internal",4,LLVMStructTypeInContext_nif},
    {"LLVMStructType_internal",3,LLVMStructType_nif},
    {"LLVMStructCreateNamed_internal",2,LLVMStructCreateNamed_nif},
    {"LLVMGetStructName_internal",1,LLVMGetStructName_nif},
    {"LLVMStructSetBody_internal",4,LLVMStructSetBody_nif},
    {"LLVMCountStructElementTypes_internal",1,LLVMCountStructElementTypes_nif},
    {"LLVMGetStructElementTypes_internal",2,LLVMGetStructElementTypes_nif},
    {"LLVMIsPackedStruct_internal",1,LLVMIsPackedStruct_nif},
    {"LLVMIsOpaqueStruct_internal",1,LLVMIsOpaqueStruct_nif},
    {"LLVMGetTypeByName_internal",2,LLVMGetTypeByName_nif},
    {"LLVMArrayType_internal",2,LLVMArrayType_nif},
    {"LLVMPointerType_internal",2,LLVMPointerType_nif},
    {"LLVMVectorType_internal",2,LLVMVectorType_nif},
    {"LLVMGetElementType_internal",1,LLVMGetElementType_nif},
    {"LLVMGetArrayLength_internal",1,LLVMGetArrayLength_nif},
    {"LLVMGetPointerAddressSpace_internal",1,LLVMGetPointerAddressSpace_nif},
    {"LLVMGetVectorSize_internal",1,LLVMGetVectorSize_nif},
    {"LLVMVoidTypeInContext_internal",1,LLVMVoidTypeInContext_nif},
    {"LLVMLabelTypeInContext_internal",1,LLVMLabelTypeInContext_nif},
    {"LLVMX86MMXTypeInContext_internal",1,LLVMX86MMXTypeInContext_nif},
    {"LLVMVoidType_internal",0,LLVMVoidType_nif},
    {"LLVMLabelType_internal",0,LLVMLabelType_nif},
    {"LLVMX86MMXType_internal",0,LLVMX86MMXType_nif},
    {"LLVMTypeOf_internal",1,LLVMTypeOf_nif},
    {"LLVMGetValueName_internal",1,LLVMGetValueName_nif},
    {"LLVMSetValueName_internal",2,LLVMSetValueName_nif},
    {"LLVMDumpValue_internal",1,LLVMDumpValue_nif},
    {"LLVMReplaceAllUsesWith_internal",2,LLVMReplaceAllUsesWith_nif},
    {"LLVMHasMetadata_internal",1,LLVMHasMetadata_nif},
    {"LLVMGetMetadata_internal",2,LLVMGetMetadata_nif},
    {"LLVMSetMetadata_internal",3,LLVMSetMetadata_nif},
    {"LLVMIsAArgument_internal",1,LLVMIsAArgument_nif},
    {"LLVMIsABasicBlock_internal",1,LLVMIsABasicBlock_nif},
    {"LLVMIsAInlineAsm_internal",1,LLVMIsAInlineAsm_nif},
    {"LLVMIsAMDNode_internal",1,LLVMIsAMDNode_nif},
    {"LLVMIsAMDString_internal",1,LLVMIsAMDString_nif},
    {"LLVMIsAUser_internal",1,LLVMIsAUser_nif},
    {"LLVMIsAConstant_internal",1,LLVMIsAConstant_nif},
    {"LLVMIsABlockAddress_internal",1,LLVMIsABlockAddress_nif},
    {"LLVMIsAConstantAggregateZero_internal",1,LLVMIsAConstantAggregateZero_nif},
    {"LLVMIsAConstantArray_internal",1,LLVMIsAConstantArray_nif},
    {"LLVMIsAConstantExpr_internal",1,LLVMIsAConstantExpr_nif},
    {"LLVMIsAConstantFP_internal",1,LLVMIsAConstantFP_nif},
    {"LLVMIsAConstantInt_internal",1,LLVMIsAConstantInt_nif},
    {"LLVMIsAConstantPointerNull_internal",1,LLVMIsAConstantPointerNull_nif},
    {"LLVMIsAConstantStruct_internal",1,LLVMIsAConstantStruct_nif},
    {"LLVMIsAConstantVector_internal",1,LLVMIsAConstantVector_nif},
    {"LLVMIsAGlobalValue_internal",1,LLVMIsAGlobalValue_nif},
    {"LLVMIsAFunction_internal",1,LLVMIsAFunction_nif},
    {"LLVMIsAGlobalAlias_internal",1,LLVMIsAGlobalAlias_nif},
    {"LLVMIsAGlobalVariable_internal",1,LLVMIsAGlobalVariable_nif},
    {"LLVMIsAUndefValue_internal",1,LLVMIsAUndefValue_nif},
    {"LLVMIsAInstruction_internal",1,LLVMIsAInstruction_nif},
    {"LLVMIsABinaryOperator_internal",1,LLVMIsABinaryOperator_nif},
    {"LLVMIsACallInst_internal",1,LLVMIsACallInst_nif},
    {"LLVMIsAIntrinsicInst_internal",1,LLVMIsAIntrinsicInst_nif},
    {"LLVMIsADbgInfoIntrinsic_internal",1,LLVMIsADbgInfoIntrinsic_nif},
    {"LLVMIsADbgDeclareInst_internal",1,LLVMIsADbgDeclareInst_nif},
    {"LLVMIsAEHExceptionInst_internal",1,LLVMIsAEHExceptionInst_nif},
    {"LLVMIsAEHSelectorInst_internal",1,LLVMIsAEHSelectorInst_nif},
    {"LLVMIsAMemIntrinsic_internal",1,LLVMIsAMemIntrinsic_nif},
    {"LLVMIsAMemCpyInst_internal",1,LLVMIsAMemCpyInst_nif},
    {"LLVMIsAMemMoveInst_internal",1,LLVMIsAMemMoveInst_nif},
    {"LLVMIsAMemSetInst_internal",1,LLVMIsAMemSetInst_nif},
    {"LLVMIsACmpInst_internal",1,LLVMIsACmpInst_nif},
    {"LLVMIsAFCmpInst_internal",1,LLVMIsAFCmpInst_nif},
    {"LLVMIsAICmpInst_internal",1,LLVMIsAICmpInst_nif},
    {"LLVMIsAExtractElementInst_internal",1,LLVMIsAExtractElementInst_nif},
    {"LLVMIsAGetElementPtrInst_internal",1,LLVMIsAGetElementPtrInst_nif},
    {"LLVMIsAInsertElementInst_internal",1,LLVMIsAInsertElementInst_nif},
    {"LLVMIsAInsertValueInst_internal",1,LLVMIsAInsertValueInst_nif},
    {"LLVMIsALandingPadInst_internal",1,LLVMIsALandingPadInst_nif},
    {"LLVMIsAPHINode_internal",1,LLVMIsAPHINode_nif},
    {"LLVMIsASelectInst_internal",1,LLVMIsASelectInst_nif},
    {"LLVMIsAShuffleVectorInst_internal",1,LLVMIsAShuffleVectorInst_nif},
    {"LLVMIsAStoreInst_internal",1,LLVMIsAStoreInst_nif},
    {"LLVMIsATerminatorInst_internal",1,LLVMIsATerminatorInst_nif},
    {"LLVMIsABranchInst_internal",1,LLVMIsABranchInst_nif},
    {"LLVMIsAIndirectBrInst_internal",1,LLVMIsAIndirectBrInst_nif},
    {"LLVMIsAInvokeInst_internal",1,LLVMIsAInvokeInst_nif},
    {"LLVMIsAReturnInst_internal",1,LLVMIsAReturnInst_nif},
    {"LLVMIsASwitchInst_internal",1,LLVMIsASwitchInst_nif},
    {"LLVMIsAUnreachableInst_internal",1,LLVMIsAUnreachableInst_nif},
    {"LLVMIsAResumeInst_internal",1,LLVMIsAResumeInst_nif},
    {"LLVMIsAUnaryInstruction_internal",1,LLVMIsAUnaryInstruction_nif},
    {"LLVMIsAAllocaInst_internal",1,LLVMIsAAllocaInst_nif},
    {"LLVMIsACastInst_internal",1,LLVMIsACastInst_nif},
    {"LLVMIsABitCastInst_internal",1,LLVMIsABitCastInst_nif},
    {"LLVMIsAFPExtInst_internal",1,LLVMIsAFPExtInst_nif},
    {"LLVMIsAFPToSIInst_internal",1,LLVMIsAFPToSIInst_nif},
    {"LLVMIsAFPToUIInst_internal",1,LLVMIsAFPToUIInst_nif},
    {"LLVMIsAFPTruncInst_internal",1,LLVMIsAFPTruncInst_nif},
    {"LLVMIsAIntToPtrInst_internal",1,LLVMIsAIntToPtrInst_nif},
    {"LLVMIsAPtrToIntInst_internal",1,LLVMIsAPtrToIntInst_nif},
    {"LLVMIsASExtInst_internal",1,LLVMIsASExtInst_nif},
    {"LLVMIsASIToFPInst_internal",1,LLVMIsASIToFPInst_nif},
    {"LLVMIsATruncInst_internal",1,LLVMIsATruncInst_nif},
    {"LLVMIsAUIToFPInst_internal",1,LLVMIsAUIToFPInst_nif},
    {"LLVMIsAZExtInst_internal",1,LLVMIsAZExtInst_nif},
    {"LLVMIsAExtractValueInst_internal",1,LLVMIsAExtractValueInst_nif},
    {"LLVMIsALoadInst_internal",1,LLVMIsALoadInst_nif},
    {"LLVMIsAVAArgInst_internal",1,LLVMIsAVAArgInst_nif},
    {"LLVMGetFirstUse_internal",1,LLVMGetFirstUse_nif},
    {"LLVMGetNextUse_internal",1,LLVMGetNextUse_nif},
    {"LLVMGetUser_internal",1,LLVMGetUser_nif},
    {"LLVMGetUsedValue_internal",1,LLVMGetUsedValue_nif},
    {"LLVMGetOperand_internal",2,LLVMGetOperand_nif},
    {"LLVMSetOperand_internal",3,LLVMSetOperand_nif},
    {"LLVMGetNumOperands_internal",1,LLVMGetNumOperands_nif},
    {"LLVMConstNull_internal",1,LLVMConstNull_nif},
    {"LLVMConstAllOnes_internal",1,LLVMConstAllOnes_nif},
    {"LLVMGetUndef_internal",1,LLVMGetUndef_nif},
    {"LLVMIsConstant_internal",1,LLVMIsConstant_nif},
    {"LLVMIsNull_internal",1,LLVMIsNull_nif},
    {"LLVMIsUndef_internal",1,LLVMIsUndef_nif},
    {"LLVMConstPointerNull_internal",1,LLVMConstPointerNull_nif},
    {"LLVMMDStringInContext_internal",3,LLVMMDStringInContext_nif},
    {"LLVMMDString_internal",2,LLVMMDString_nif},
    {"LLVMMDNodeInContext_internal",3,LLVMMDNodeInContext_nif},
    {"LLVMMDNode_internal",2,LLVMMDNode_nif},
    {"LLVMGetMDString_internal",2,LLVMGetMDString_nif},
    {"LLVMGetNamedMetadataNumOperands_internal",2,LLVMGetNamedMetadataNumOperands_nif},
    {"LLVMGetNamedMetadataOperands_internal",3,LLVMGetNamedMetadataOperands_nif},
    {"LLVMConstInt_internal",3,LLVMConstInt_nif},
    {"LLVMConstIntOfString_internal",3,LLVMConstIntOfString_nif},
    {"LLVMConstIntOfStringAndSize_internal",4,LLVMConstIntOfStringAndSize_nif},
    {"LLVMConstReal_internal",2,LLVMConstReal_nif},
    {"LLVMConstRealOfString_internal",2,LLVMConstRealOfString_nif},
    {"LLVMConstRealOfStringAndSize_internal",3,LLVMConstRealOfStringAndSize_nif},
    {"LLVMConstIntGetZExtValue_internal",1,LLVMConstIntGetZExtValue_nif},
    {"LLVMConstIntGetSExtValue_internal",1,LLVMConstIntGetSExtValue_nif},
    {"LLVMConstStringInContext_internal",4,LLVMConstStringInContext_nif},
    {"LLVMConstStructInContext_internal",4,LLVMConstStructInContext_nif},
    {"LLVMConstString_internal",3,LLVMConstString_nif},
    {"LLVMConstArray_internal",3,LLVMConstArray_nif},
    {"LLVMConstStruct_internal",3,LLVMConstStruct_nif},
    {"LLVMConstNamedStruct_internal",3,LLVMConstNamedStruct_nif},
    {"LLVMConstVector_internal",2,LLVMConstVector_nif},
    {"LLVMGetConstOpcode_internal",1,LLVMGetConstOpcode_nif},
    {"LLVMAlignOf_internal",1,LLVMAlignOf_nif},
    {"LLVMSizeOf_internal",1,LLVMSizeOf_nif},
    {"LLVMConstNeg_internal",1,LLVMConstNeg_nif},
    {"LLVMConstNSWNeg_internal",1,LLVMConstNSWNeg_nif},
    {"LLVMConstNUWNeg_internal",1,LLVMConstNUWNeg_nif},
    {"LLVMConstFNeg_internal",1,LLVMConstFNeg_nif},
    {"LLVMConstNot_internal",1,LLVMConstNot_nif},
    {"LLVMConstAdd_internal",2,LLVMConstAdd_nif},
    {"LLVMConstNSWAdd_internal",2,LLVMConstNSWAdd_nif},
    {"LLVMConstNUWAdd_internal",2,LLVMConstNUWAdd_nif},
    {"LLVMConstFAdd_internal",2,LLVMConstFAdd_nif},
    {"LLVMConstSub_internal",2,LLVMConstSub_nif},
    {"LLVMConstNSWSub_internal",2,LLVMConstNSWSub_nif},
    {"LLVMConstNUWSub_internal",2,LLVMConstNUWSub_nif},
    {"LLVMConstFSub_internal",2,LLVMConstFSub_nif},
    {"LLVMConstMul_internal",2,LLVMConstMul_nif},
    {"LLVMConstNSWMul_internal",2,LLVMConstNSWMul_nif},
    {"LLVMConstNUWMul_internal",2,LLVMConstNUWMul_nif},
    {"LLVMConstFMul_internal",2,LLVMConstFMul_nif},
    {"LLVMConstUDiv_internal",2,LLVMConstUDiv_nif},
    {"LLVMConstSDiv_internal",2,LLVMConstSDiv_nif},
    {"LLVMConstExactSDiv_internal",2,LLVMConstExactSDiv_nif},
    {"LLVMConstFDiv_internal",2,LLVMConstFDiv_nif},
    {"LLVMConstURem_internal",2,LLVMConstURem_nif},
    {"LLVMConstSRem_internal",2,LLVMConstSRem_nif},
    {"LLVMConstFRem_internal",2,LLVMConstFRem_nif},
    {"LLVMConstAnd_internal",2,LLVMConstAnd_nif},
    {"LLVMConstOr_internal",2,LLVMConstOr_nif},
    {"LLVMConstXor_internal",2,LLVMConstXor_nif},
    {"LLVMConstICmp_internal",3,LLVMConstICmp_nif},
    {"LLVMConstFCmp_internal",3,LLVMConstFCmp_nif},
    {"LLVMConstShl_internal",2,LLVMConstShl_nif},
    {"LLVMConstLShr_internal",2,LLVMConstLShr_nif},
    {"LLVMConstAShr_internal",2,LLVMConstAShr_nif},
    {"LLVMConstGEP_internal",3,LLVMConstGEP_nif},
    {"LLVMConstInBoundsGEP_internal",3,LLVMConstInBoundsGEP_nif},
    {"LLVMConstTrunc_internal",2,LLVMConstTrunc_nif},
    {"LLVMConstSExt_internal",2,LLVMConstSExt_nif},
    {"LLVMConstZExt_internal",2,LLVMConstZExt_nif},
    {"LLVMConstFPTrunc_internal",2,LLVMConstFPTrunc_nif},
    {"LLVMConstFPExt_internal",2,LLVMConstFPExt_nif},
    {"LLVMConstUIToFP_internal",2,LLVMConstUIToFP_nif},
    {"LLVMConstSIToFP_internal",2,LLVMConstSIToFP_nif},
    {"LLVMConstFPToUI_internal",2,LLVMConstFPToUI_nif},
    {"LLVMConstFPToSI_internal",2,LLVMConstFPToSI_nif},
    {"LLVMConstPtrToInt_internal",2,LLVMConstPtrToInt_nif},
    {"LLVMConstIntToPtr_internal",2,LLVMConstIntToPtr_nif},
    {"LLVMConstBitCast_internal",2,LLVMConstBitCast_nif},
    {"LLVMConstZExtOrBitCast_internal",2,LLVMConstZExtOrBitCast_nif},
    {"LLVMConstSExtOrBitCast_internal",2,LLVMConstSExtOrBitCast_nif},
    {"LLVMConstTruncOrBitCast_internal",2,LLVMConstTruncOrBitCast_nif},
    {"LLVMConstPointerCast_internal",2,LLVMConstPointerCast_nif},
    {"LLVMConstIntCast_internal",3,LLVMConstIntCast_nif},
    {"LLVMConstFPCast_internal",2,LLVMConstFPCast_nif},
    {"LLVMConstSelect_internal",3,LLVMConstSelect_nif},
    {"LLVMConstExtractElement_internal",2,LLVMConstExtractElement_nif},
    {"LLVMConstInsertElement_internal",3,LLVMConstInsertElement_nif},
    {"LLVMConstShuffleVector_internal",3,LLVMConstShuffleVector_nif},
    {"LLVMConstExtractValue_internal",3,LLVMConstExtractValue_nif},
    {"LLVMConstInsertValue_internal",4,LLVMConstInsertValue_nif},
    {"LLVMConstInlineAsm_internal",5,LLVMConstInlineAsm_nif},
    {"LLVMBlockAddress_internal",2,LLVMBlockAddress_nif},
    {"LLVMGetGlobalParent_internal",1,LLVMGetGlobalParent_nif},
    {"LLVMIsDeclaration_internal",1,LLVMIsDeclaration_nif},
    {"LLVMGetLinkage_internal",1,LLVMGetLinkage_nif},
    {"LLVMSetLinkage_internal",2,LLVMSetLinkage_nif},
    {"LLVMGetSection_internal",1,LLVMGetSection_nif},
    {"LLVMSetSection_internal",2,LLVMSetSection_nif},
    {"LLVMGetVisibility_internal",1,LLVMGetVisibility_nif},
    {"LLVMSetVisibility_internal",2,LLVMSetVisibility_nif},
    {"LLVMGetAlignment_internal",1,LLVMGetAlignment_nif},
    {"LLVMSetAlignment_internal",2,LLVMSetAlignment_nif},
    {"LLVMAddGlobal_internal",3,LLVMAddGlobal_nif},
    {"LLVMAddGlobalInAddressSpace_internal",4,LLVMAddGlobalInAddressSpace_nif},
    {"LLVMGetNamedGlobal_internal",2,LLVMGetNamedGlobal_nif},
    {"LLVMGetFirstGlobal_internal",1,LLVMGetFirstGlobal_nif},
    {"LLVMGetLastGlobal_internal",1,LLVMGetLastGlobal_nif},
    {"LLVMGetNextGlobal_internal",1,LLVMGetNextGlobal_nif},
    {"LLVMGetPreviousGlobal_internal",1,LLVMGetPreviousGlobal_nif},
    {"LLVMDeleteGlobal_internal",1,LLVMDeleteGlobal_nif},
    {"LLVMGetInitializer_internal",1,LLVMGetInitializer_nif},
    {"LLVMSetInitializer_internal",2,LLVMSetInitializer_nif},
    {"LLVMIsThreadLocal_internal",1,LLVMIsThreadLocal_nif},
    {"LLVMSetThreadLocal_internal",2,LLVMSetThreadLocal_nif},
    {"LLVMIsGlobalConstant_internal",1,LLVMIsGlobalConstant_nif},
    {"LLVMSetGlobalConstant_internal",2,LLVMSetGlobalConstant_nif},
    {"LLVMAddAlias_internal",4,LLVMAddAlias_nif},
    {"LLVMAddFunction_internal",3,LLVMAddFunction_nif},
    {"LLVMGetNamedFunction_internal",2,LLVMGetNamedFunction_nif},
    {"LLVMGetFirstFunction_internal",1,LLVMGetFirstFunction_nif},
    {"LLVMGetLastFunction_internal",1,LLVMGetLastFunction_nif},
    {"LLVMGetNextFunction_internal",1,LLVMGetNextFunction_nif},
    {"LLVMGetPreviousFunction_internal",1,LLVMGetPreviousFunction_nif},
    {"LLVMDeleteFunction_internal",1,LLVMDeleteFunction_nif},
    {"LLVMGetIntrinsicID_internal",1,LLVMGetIntrinsicID_nif},
    {"LLVMGetFunctionCallConv_internal",1,LLVMGetFunctionCallConv_nif},
    {"LLVMSetFunctionCallConv_internal",2,LLVMSetFunctionCallConv_nif},
    {"LLVMGetGC_internal",1,LLVMGetGC_nif},
    {"LLVMSetGC_internal",2,LLVMSetGC_nif},
    {"LLVMAddFunctionAttr_internal",2,LLVMAddFunctionAttr_nif},
    {"LLVMGetFunctionAttr_internal",1,LLVMGetFunctionAttr_nif},
    {"LLVMRemoveFunctionAttr_internal",2,LLVMRemoveFunctionAttr_nif},
    {"LLVMCountParams_internal",1,LLVMCountParams_nif},
    {"LLVMGetParams_internal",2,LLVMGetParams_nif},
    {"LLVMGetParam_internal",2,LLVMGetParam_nif},
    {"LLVMGetParamParent_internal",1,LLVMGetParamParent_nif},
    {"LLVMGetFirstParam_internal",1,LLVMGetFirstParam_nif},
    {"LLVMGetLastParam_internal",1,LLVMGetLastParam_nif},
    {"LLVMGetNextParam_internal",1,LLVMGetNextParam_nif},
    {"LLVMGetPreviousParam_internal",1,LLVMGetPreviousParam_nif},
    {"LLVMAddAttribute_internal",2,LLVMAddAttribute_nif},
    {"LLVMRemoveAttribute_internal",2,LLVMRemoveAttribute_nif},
    {"LLVMGetAttribute_internal",1,LLVMGetAttribute_nif},
    {"LLVMSetParamAlignment_internal",2,LLVMSetParamAlignment_nif},
    {"LLVMBasicBlockAsValue_internal",1,LLVMBasicBlockAsValue_nif},
    {"LLVMValueIsBasicBlock_internal",1,LLVMValueIsBasicBlock_nif},
    {"LLVMValueAsBasicBlock_internal",1,LLVMValueAsBasicBlock_nif},
    {"LLVMGetBasicBlockParent_internal",1,LLVMGetBasicBlockParent_nif},
    {"LLVMGetBasicBlockTerminator_internal",1,LLVMGetBasicBlockTerminator_nif},
    {"LLVMCountBasicBlocks_internal",1,LLVMCountBasicBlocks_nif},
    {"LLVMGetBasicBlocks_internal",2,LLVMGetBasicBlocks_nif},
    {"LLVMGetFirstBasicBlock_internal",1,LLVMGetFirstBasicBlock_nif},
    {"LLVMGetLastBasicBlock_internal",1,LLVMGetLastBasicBlock_nif},
    {"LLVMGetNextBasicBlock_internal",1,LLVMGetNextBasicBlock_nif},
    {"LLVMGetPreviousBasicBlock_internal",1,LLVMGetPreviousBasicBlock_nif},
    {"LLVMGetEntryBasicBlock_internal",1,LLVMGetEntryBasicBlock_nif},
    {"LLVMAppendBasicBlockInContext_internal",3,LLVMAppendBasicBlockInContext_nif},
    {"LLVMInsertBasicBlockInContext_internal",3,LLVMInsertBasicBlockInContext_nif},
    {"LLVMAppendBasicBlock_internal",2,LLVMAppendBasicBlock_nif},
    {"LLVMInsertBasicBlock_internal",2,LLVMInsertBasicBlock_nif},
    {"LLVMDeleteBasicBlock_internal",1,LLVMDeleteBasicBlock_nif},
    {"LLVMRemoveBasicBlockFromParent_internal",1,LLVMRemoveBasicBlockFromParent_nif},
    {"LLVMMoveBasicBlockBefore_internal",2,LLVMMoveBasicBlockBefore_nif},
    {"LLVMMoveBasicBlockAfter_internal",2,LLVMMoveBasicBlockAfter_nif},
    {"LLVMGetFirstInstruction_internal",1,LLVMGetFirstInstruction_nif},
    {"LLVMGetLastInstruction_internal",1,LLVMGetLastInstruction_nif},
    {"LLVMGetInstructionParent_internal",1,LLVMGetInstructionParent_nif},
    {"LLVMGetNextInstruction_internal",1,LLVMGetNextInstruction_nif},
    {"LLVMGetPreviousInstruction_internal",1,LLVMGetPreviousInstruction_nif},
    {"LLVMInstructionEraseFromParent_internal",1,LLVMInstructionEraseFromParent_nif},
    {"LLVMGetInstructionOpcode_internal",1,LLVMGetInstructionOpcode_nif},
    {"LLVMGetICmpPredicate_internal",1,LLVMGetICmpPredicate_nif},
    {"LLVMSetInstructionCallConv_internal",2,LLVMSetInstructionCallConv_nif},
    {"LLVMGetInstructionCallConv_internal",1,LLVMGetInstructionCallConv_nif},
    {"LLVMAddInstrAttribute_internal",3,LLVMAddInstrAttribute_nif},
    {"LLVMRemoveInstrAttribute_internal",3,LLVMRemoveInstrAttribute_nif},
    {"LLVMSetInstrParamAlignment_internal",3,LLVMSetInstrParamAlignment_nif},
    {"LLVMIsTailCall_internal",1,LLVMIsTailCall_nif},
    {"LLVMSetTailCall_internal",2,LLVMSetTailCall_nif},
    {"LLVMGetSwitchDefaultDest_internal",1,LLVMGetSwitchDefaultDest_nif},
    {"LLVMAddIncoming_internal",4,LLVMAddIncoming_nif},
    {"LLVMCountIncoming_internal",1,LLVMCountIncoming_nif},
    {"LLVMGetIncomingValue_internal",2,LLVMGetIncomingValue_nif},
    {"LLVMGetIncomingBlock_internal",2,LLVMGetIncomingBlock_nif},
    {"LLVMCreateBuilderInContext_internal",1,LLVMCreateBuilderInContext_nif},
    {"LLVMCreateBuilder_internal",0,LLVMCreateBuilder_nif},
    {"LLVMPositionBuilder_internal",3,LLVMPositionBuilder_nif},
    {"LLVMPositionBuilderBefore_internal",2,LLVMPositionBuilderBefore_nif},
    {"LLVMPositionBuilderAtEnd_internal",2,LLVMPositionBuilderAtEnd_nif},
    {"LLVMGetInsertBlock_internal",1,LLVMGetInsertBlock_nif},
    {"LLVMClearInsertionPosition_internal",1,LLVMClearInsertionPosition_nif},
    {"LLVMInsertIntoBuilder_internal",2,LLVMInsertIntoBuilder_nif},
    {"LLVMInsertIntoBuilderWithName_internal",3,LLVMInsertIntoBuilderWithName_nif},
    {"LLVMDisposeBuilder_internal",1,LLVMDisposeBuilder_nif},
    {"LLVMSetCurrentDebugLocation_internal",2,LLVMSetCurrentDebugLocation_nif},
    {"LLVMGetCurrentDebugLocation_internal",1,LLVMGetCurrentDebugLocation_nif},
    {"LLVMSetInstDebugLocation_internal",2,LLVMSetInstDebugLocation_nif},
    {"LLVMBuildRetVoid_internal",1,LLVMBuildRetVoid_nif},
    {"LLVMBuildRet_internal",2,LLVMBuildRet_nif},
    {"LLVMBuildAggregateRet_internal",3,LLVMBuildAggregateRet_nif},
    {"LLVMBuildBr_internal",2,LLVMBuildBr_nif},
    {"LLVMBuildCondBr_internal",4,LLVMBuildCondBr_nif},
    {"LLVMBuildSwitch_internal",4,LLVMBuildSwitch_nif},
    {"LLVMBuildIndirectBr_internal",3,LLVMBuildIndirectBr_nif},
    {"LLVMBuildInvoke_internal",7,LLVMBuildInvoke_nif},
    {"LLVMBuildLandingPad_internal",5,LLVMBuildLandingPad_nif},
    {"LLVMBuildResume_internal",2,LLVMBuildResume_nif},
    {"LLVMBuildUnreachable_internal",1,LLVMBuildUnreachable_nif},
    {"LLVMAddCase_internal",3,LLVMAddCase_nif},
    {"LLVMAddDestination_internal",2,LLVMAddDestination_nif},
    {"LLVMAddClause_internal",2,LLVMAddClause_nif},
    {"LLVMSetCleanup_internal",2,LLVMSetCleanup_nif},
    {"LLVMBuildAdd_internal",4,LLVMBuildAdd_nif},
    {"LLVMBuildNSWAdd_internal",4,LLVMBuildNSWAdd_nif},
    {"LLVMBuildNUWAdd_internal",4,LLVMBuildNUWAdd_nif},
    {"LLVMBuildFAdd_internal",4,LLVMBuildFAdd_nif},
    {"LLVMBuildSub_internal",4,LLVMBuildSub_nif},
    {"LLVMBuildNSWSub_internal",4,LLVMBuildNSWSub_nif},
    {"LLVMBuildNUWSub_internal",4,LLVMBuildNUWSub_nif},
    {"LLVMBuildFSub_internal",4,LLVMBuildFSub_nif},
    {"LLVMBuildMul_internal",4,LLVMBuildMul_nif},
    {"LLVMBuildNSWMul_internal",4,LLVMBuildNSWMul_nif},
    {"LLVMBuildNUWMul_internal",4,LLVMBuildNUWMul_nif},
    {"LLVMBuildFMul_internal",4,LLVMBuildFMul_nif},
    {"LLVMBuildUDiv_internal",4,LLVMBuildUDiv_nif},
    {"LLVMBuildSDiv_internal",4,LLVMBuildSDiv_nif},
    {"LLVMBuildExactSDiv_internal",4,LLVMBuildExactSDiv_nif},
    {"LLVMBuildFDiv_internal",4,LLVMBuildFDiv_nif},
    {"LLVMBuildURem_internal",4,LLVMBuildURem_nif},
    {"LLVMBuildSRem_internal",4,LLVMBuildSRem_nif},
    {"LLVMBuildFRem_internal",4,LLVMBuildFRem_nif},
    {"LLVMBuildShl_internal",4,LLVMBuildShl_nif},
    {"LLVMBuildLShr_internal",4,LLVMBuildLShr_nif},
    {"LLVMBuildAShr_internal",4,LLVMBuildAShr_nif},
    {"LLVMBuildAnd_internal",4,LLVMBuildAnd_nif},
    {"LLVMBuildOr_internal",4,LLVMBuildOr_nif},
    {"LLVMBuildXor_internal",4,LLVMBuildXor_nif},
    {"LLVMBuildBinOp_internal",5,LLVMBuildBinOp_nif},
    {"LLVMBuildNeg_internal",3,LLVMBuildNeg_nif},
    {"LLVMBuildNSWNeg_internal",3,LLVMBuildNSWNeg_nif},
    {"LLVMBuildNUWNeg_internal",3,LLVMBuildNUWNeg_nif},
    {"LLVMBuildFNeg_internal",3,LLVMBuildFNeg_nif},
    {"LLVMBuildNot_internal",3,LLVMBuildNot_nif},
    {"LLVMBuildMalloc_internal",3,LLVMBuildMalloc_nif},
    {"LLVMBuildArrayMalloc_internal",4,LLVMBuildArrayMalloc_nif},
    {"LLVMBuildAlloca_internal",3,LLVMBuildAlloca_nif},
    {"LLVMBuildArrayAlloca_internal",4,LLVMBuildArrayAlloca_nif},
    {"LLVMBuildFree_internal",2,LLVMBuildFree_nif},
    {"LLVMBuildLoad_internal",3,LLVMBuildLoad_nif},
    {"LLVMBuildStore_internal",3,LLVMBuildStore_nif},
    {"LLVMBuildGEP_internal",5,LLVMBuildGEP_nif},
    {"LLVMBuildInBoundsGEP_internal",5,LLVMBuildInBoundsGEP_nif},
    {"LLVMBuildStructGEP_internal",4,LLVMBuildStructGEP_nif},
    {"LLVMBuildGlobalString_internal",3,LLVMBuildGlobalString_nif},
    {"LLVMBuildGlobalStringPtr_internal",3,LLVMBuildGlobalStringPtr_nif},
    {"LLVMGetVolatile_internal",1,LLVMGetVolatile_nif},
    {"LLVMSetVolatile_internal",2,LLVMSetVolatile_nif},
    {"LLVMBuildTrunc_internal",4,LLVMBuildTrunc_nif},
    {"LLVMBuildZExt_internal",4,LLVMBuildZExt_nif},
    {"LLVMBuildSExt_internal",4,LLVMBuildSExt_nif},
    {"LLVMBuildFPToUI_internal",4,LLVMBuildFPToUI_nif},
    {"LLVMBuildFPToSI_internal",4,LLVMBuildFPToSI_nif},
    {"LLVMBuildUIToFP_internal",4,LLVMBuildUIToFP_nif},
    {"LLVMBuildSIToFP_internal",4,LLVMBuildSIToFP_nif},
    {"LLVMBuildFPTrunc_internal",4,LLVMBuildFPTrunc_nif},
    {"LLVMBuildFPExt_internal",4,LLVMBuildFPExt_nif},
    {"LLVMBuildPtrToInt_internal",4,LLVMBuildPtrToInt_nif},
    {"LLVMBuildIntToPtr_internal",4,LLVMBuildIntToPtr_nif},
    {"LLVMBuildBitCast_internal",4,LLVMBuildBitCast_nif},
    {"LLVMBuildZExtOrBitCast_internal",4,LLVMBuildZExtOrBitCast_nif},
    {"LLVMBuildSExtOrBitCast_internal",4,LLVMBuildSExtOrBitCast_nif},
    {"LLVMBuildTruncOrBitCast_internal",4,LLVMBuildTruncOrBitCast_nif},
    {"LLVMBuildCast_internal",5,LLVMBuildCast_nif},
    {"LLVMBuildPointerCast_internal",4,LLVMBuildPointerCast_nif},
    {"LLVMBuildIntCast_internal",4,LLVMBuildIntCast_nif},
    {"LLVMBuildFPCast_internal",4,LLVMBuildFPCast_nif},
    {"LLVMBuildICmp_internal",5,LLVMBuildICmp_nif},
    {"LLVMBuildFCmp_internal",5,LLVMBuildFCmp_nif},
    {"LLVMBuildPhi_internal",3,LLVMBuildPhi_nif},
    {"LLVMBuildCall_internal",5,LLVMBuildCall_nif},
    {"LLVMBuildSelect_internal",5,LLVMBuildSelect_nif},
    {"LLVMBuildVAArg_internal",4,LLVMBuildVAArg_nif},
    {"LLVMBuildExtractElement_internal",4,LLVMBuildExtractElement_nif},
    {"LLVMBuildInsertElement_internal",5,LLVMBuildInsertElement_nif},
    {"LLVMBuildShuffleVector_internal",5,LLVMBuildShuffleVector_nif},
    {"LLVMBuildExtractValue_internal",4,LLVMBuildExtractValue_nif},
    {"LLVMBuildInsertValue_internal",5,LLVMBuildInsertValue_nif},
    {"LLVMBuildIsNull_internal",3,LLVMBuildIsNull_nif},
    {"LLVMBuildIsNotNull_internal",3,LLVMBuildIsNotNull_nif},
    {"LLVMBuildPtrDiff_internal",4,LLVMBuildPtrDiff_nif},
    {"LLVMCreateModuleProviderForExistingModule_internal",1,LLVMCreateModuleProviderForExistingModule_nif},
    {"LLVMDisposeModuleProvider_internal",1,LLVMDisposeModuleProvider_nif},
    {"LLVMCreateMemoryBufferWithContentsOfFile_internal",1,LLVMCreateMemoryBufferWithContentsOfFile_nif},
    {"LLVMDisposeMemoryBuffer_internal",1,LLVMDisposeMemoryBuffer_nif},
    {"LLVMGetGlobalPassRegistry_internal",0,LLVMGetGlobalPassRegistry_nif},
    {"LLVMCreatePassManager_internal",0,LLVMCreatePassManager_nif},
    {"LLVMCreateFunctionPassManagerForModule_internal",1,LLVMCreateFunctionPassManagerForModule_nif},
    {"LLVMCreateFunctionPassManager_internal",1,LLVMCreateFunctionPassManager_nif},
    {"LLVMRunPassManager_internal",2,LLVMRunPassManager_nif},
    {"LLVMInitializeFunctionPassManager_internal",1,LLVMInitializeFunctionPassManager_nif},
    {"LLVMRunFunctionPassManager_internal",2,LLVMRunFunctionPassManager_nif},
    {"LLVMFinalizeFunctionPassManager_internal",1,LLVMFinalizeFunctionPassManager_nif},
    {"LLVMDisposePassManager_internal",1,LLVMDisposePassManager_nif},
// --- Stop generating from Core_8h.xml

// -- Start generating from BitWriter_8h.xml on {{2012,2,25},{14,37,57}}--

    {"LLVMWriteBitcodeToFile_internal",2,LLVMWriteBitcodeToFile_nif},
    {"LLVMWriteBitcodeToFD_internal",4,LLVMWriteBitcodeToFD_nif},
    {"LLVMWriteBitcodeToFileHandle_internal",2,LLVMWriteBitcodeToFileHandle_nif},
// --- Stop generating from BitWriter_8h.xml

// -- Start generating from BitReader_8h.xml on {{2012,2,25},{14,37,57}}--

    {"LLVMParseBitcode_internal",1,LLVMParseBitcode_nif},
    {"LLVMParseBitcodeInContext_internal",2,LLVMParseBitcodeInContext_nif},
    {"LLVMGetBitcodeModuleInContext_internal",2,LLVMGetBitcodeModuleInContext_nif},
    {"LLVMGetBitcodeModule_internal",1,LLVMGetBitcodeModule_nif},
    {"LLVMGetBitcodeModuleProviderInContext_internal",2,LLVMGetBitcodeModuleProviderInContext_nif},
    {"LLVMGetBitcodeModuleProvider_internal",1,LLVMGetBitcodeModuleProvider_nif},
// --- Stop generating from BitReader_8h.xml

// -- Start generating from Analysis_8h.xml on {{2012,2,25},{14,37,57}}--

    {"LLVMVerifyModule_internal",2,LLVMVerifyModule_nif},
    {"LLVMVerifyFunction_internal",2,LLVMVerifyFunction_nif},
    {"LLVMViewFunctionCFG_internal",1,LLVMViewFunctionCFG_nif},
    {"LLVMViewFunctionCFGOnly_internal",1,LLVMViewFunctionCFGOnly_nif},
// --- Stop generating from Analysis_8h.xml

  };

ERL_NIF_INIT(llevm,nif_funcs,load_nif,NULL,NULL,NULL)
