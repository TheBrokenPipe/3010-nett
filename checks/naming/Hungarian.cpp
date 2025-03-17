/* Copyright (C) 2020  Matthys Grobbelaar
 *  Full license notice can be found in Nett.cpp
 */
#include "Hungarian.hpp"

namespace nett {
namespace naming {

static bool IsHungarianNameFuncPtr(llvm::StringRef VarName);
static bool IsHungarianNameChar(llvm::StringRef VarName);
static bool IsHungarianNamePtr(llvm::StringRef VarName);
static bool IsHungarianNameArray(llvm::StringRef VarName);
static bool IsHungarianNameStruct(llvm::StringRef VarName);
static bool IsHungarianNameEnum(llvm::StringRef VarName);

bool IsHungarianVarName(llvm::StringRef VarName, clang::QualType VarType) {

    // Conditionally disable hungarian notation checking 
    #ifdef IGNORE_HUNGARIAN_NOTATION
    return false;
    #endif /* IGNORE_HUNGARIAN_NOTATION */

    llvm::StringRef VarTypeString = VarType.getAsString();
    auto NotFound = llvm::StringRef::npos;

    if (VarType->isFunctionPointerType()) {
        return IsHungarianNameFuncPtr(VarName) || IsHungarianNamePtr(VarName);
    } else if (VarTypeString.find("*") != NotFound) {
        // If the type contains a pointer, it can be one of the following:
        //      -> a pointer to an array
        //      -> simply a pointer to something (int*, char* etc.)
        // We also ignore string checks because often 'str' and 'string'
        // are appropriate names.
        return IsHungarianNameArray(VarName) || IsHungarianNamePtr(VarName);
    } else if (VarTypeString.find("[") != NotFound &&
               VarTypeString.find("]") != NotFound) {
        return IsHungarianNameArray(VarName);
    } else if (VarTypeString.startswith_insensitive("char")) {
        return IsHungarianNameChar(VarName);
    } else if (VarTypeString.startswith_insensitive("struct")) {
        return IsHungarianNameStruct(VarName);
    } else if (VarTypeString.startswith_insensitive("enum")) {
        return IsHungarianNameEnum(VarName);
    }
    return false;
}

static bool IsHungarianNameFuncPtr(llvm::StringRef VarName) {
    return VarName.endswith_insensitive("fp") || VarName.startswith_insensitive("fp");
}

static bool IsHungarianNameChar(llvm::StringRef VarName) {
    return VarName.endswith_insensitive("chr") || VarName.startswith_insensitive("chr") ||
           VarName.find_insensitive("char") != llvm::StringRef::npos;
}

static bool IsHungarianNamePtr(llvm::StringRef VarName) {
    return VarName.endswith_insensitive("ptr") || VarName.startswith_insensitive("ptr") ||
           VarName.find_insensitive("pointer") != llvm::StringRef::npos;
}

static bool IsHungarianNameArray(llvm::StringRef VarName) {
    return VarName.endswith_insensitive("arr") || VarName.startswith_insensitive("arr") ||
           VarName.find_insensitive("array") != llvm::StringRef::npos;
}

static bool IsHungarianNameStruct(llvm::StringRef VarName) {
    return VarName.endswith_insensitive("str") || VarName.startswith_insensitive("str") ||
           VarName.find_insensitive("struct") != llvm::StringRef::npos;
}

static bool IsHungarianNameEnum(llvm::StringRef VarName) {
    return VarName.find_insensitive("enum") != llvm::StringRef::npos;
}

}  // namespace naming
}  // namespace nett