#include "Lexer.h"
#include "llvm/Support/Compiler.h"

namespace charinfo {

LLVM_READNONE inline bool isWhiteSpace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' ||
         c == '\v';
}

LLVM_READNONE inline bool isDigit(char c) { return c >= '0' && c <= '9'; }

LLVM_READNONE inline bool isLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
} // namespace charinfo

void Lexer::next(Token &token) {
  while (*BufferPtr && charinfo::isWhiteSpace(*BufferPtr)) {
    ++BufferPtr;
  }

  if (!*BufferPtr) {
    token.Kind = Token::eoi;
  }

  else if (charinfo::isLetter(*BufferPtr)) {
    const char *end = BufferPtr + 1;
    while (charinfo::isLetter(*end)) {
      ++end;
    }
    llvm::StringRef Name(BufferPtr, end - BufferPtr);
    Token::TokenKind kind = Name == "with" ? Token::KW_with : Token::ident;
    formToken(token, end, kind);
  }

  else if (charinfo::isDigit(*BufferPtr)) {
    const char *end = BufferPtr + 1;
    while (charinfo::isDigit(*end))
      ++end;
    formToken(token, end, Token::number);
  }

  else {
    switch (*BufferPtr) {
#define CASE(ch, tok)                                                          \
  case ch:                                                                     \
    formToken(token, BufferPtr + 1, tok);                                      \
    break

      CASE('+', Token::plus);
      CASE('-', Token::minus);
      CASE('*', Token::star);
      CASE('/', Token::slash);
      CASE('(', Token::l_paren);
      CASE(')', Token::r_paren);
      CASE(':', Token::colon);
      CASE(',', Token::comma);
    default:
      formToken(token, BufferPtr + 1, Token::unknown);
    }
  }
}

void Lexer::formToken(Token &tok, const char *tokEnd, Token::TokenKind kind) {
  tok.Kind = kind;
  tok.Text = llvm::StringRef(BufferPtr, tokEnd - BufferPtr);
  BufferPtr = tokEnd;
}
