#pragma once

#include "HPCParallelPattern.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"



class HPCPatternBeginInstrHandler : public clang::ast_matchers::MatchFinder::MatchCallback 
{
public:
	void SetCurrentFnEntry(FunctionDeclDatabaseEntry* FnEntry);

	HPCParallelPattern* GetLastPattern() { return LastPattern; }

	virtual void run (const clang::ast_matchers::MatchFinder::MatchResult &Result);

private:
	FunctionDeclDatabaseEntry* CurrentFnEntry;

	HPCParallelPattern* LastPattern;
};



class HPCPatternEndInstrHandler : public clang::ast_matchers::MatchFinder::MatchCallback
{
public:
	void SetCurrentFnEntry(FunctionDeclDatabaseEntry* FnEntry);

	HPCParallelPattern* GetLastPattern() { return LastPattern; }

	virtual void run (const clang::ast_matchers::MatchFinder::MatchResult &Result);

private:
	FunctionDeclDatabaseEntry* CurrentFnEntry;

	HPCParallelPattern* LastPattern;
};
