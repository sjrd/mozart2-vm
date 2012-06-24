// Copyright © 2011, Université catholique de Louvain
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// *  Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// *  Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef __MODCHUNK_H
#define __MODCHUNK_H

#include "../mozartcore.hh"

#ifndef MOZART_GENERATOR

namespace mozart {

namespace builtins {

//////////////////
// Chunk module //
//////////////////

class ModChunk: public Module {
public:
  ModChunk(): Module("Chunk") {}

  class New: public Builtin<New> {
  public:
    New(): Builtin("new") {}

    OpResult operator()(VM vm, In underlying, Out result) {
      bool isRecord = false;
      MOZART_CHECK_OPRESULT(RecordLike(underlying).isRecord(vm, isRecord));

      if (isRecord) {
        result = Chunk::build(vm, underlying);
        return OpResult::proceed();
      } else {
        return raiseTypeError(vm, u"Record", underlying);
      }
    }
  };

  class Is: public Builtin<Is> {
  public:
    Is(): Builtin("is") {}

    OpResult operator()(VM vm, In value, Out result) {
      bool boolResult = false;
      MOZART_CHECK_OPRESULT(ChunkLike(value).isChunk(vm, boolResult));

      result = Boolean::build(vm, boolResult);
      return OpResult::proceed();
    }
  };
};

}

}

#endif // MOZART_GENERATOR

#endif // __MODCHUNK_H