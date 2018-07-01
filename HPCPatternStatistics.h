#pragma once

#include "HPCParallelPattern.h"
#include <string>
#include "TreeAlgorithms.h"

#define CSV_SEPARATOR_CHAR ","



class HPCPatternStatistic
{
public:
	virtual void Calculate() = 0;

	virtual void Print() = 0;

	virtual void CSVExport(std::string FileName) = 0;
};



class CyclomaticComplexityStatistic : public HPCPatternStatistic
{
public:
	CyclomaticComplexityStatistic();
	
	void Calculate();

	void Print();

	void CSVExport(std::string FileName);

private:
	void SetNodeVisited(PatternTreeNode* Node);

	bool IsNodeVisited(PatternTreeNode* Node);

	std::vector<PatternTreeNode*> VisitedNodes;

	int CountEdges();

	int CountEdges(PatternTreeNode* Root);

	int CountNodes();

	int CountConnectedComponents();

	void MarkConnectedComponent(PatternTreeNode * Node, int ComponentID);

	int Nodes, Edges, ConnectedComponents = 0;

	int CyclomaticComplexity = 0;
};



class LinesOfCodeStatistic : public HPCPatternStatistic
{
public:
	void Calculate();
	
	void Print();

	void CSVExport(std::string FileName);
};



class SimplePatternCountStatistic : public HPCPatternStatistic
{
public:
	SimplePatternCountStatistic();	

	void Calculate();

	void Print();

	void CSVExport(std::string FileName);
};



/*
 * This statistic calculates the fan-in and fan-out numbers for every pattern which occurs in the code.
 * The fan-in number is calculated as the number of patterns which are a direct parent to the pattern in question.
 * The fan-out number is the number of patterns which are direct children to this pattern.
 */
class FanInFanOutStatistic : public HPCPatternStatistic
{
public:
	FanInFanOutStatistic(int maxdepth);

	void Calculate();

	void Print();

	void CSVExport(std::string FileName);

private:
	struct FanInFanOutCounter
	{
		HPCParallelPattern* Pattern;
		int FanIn = 0;
		int FanOut = 0;
	};

	void VisitFunctionCall(FunctionDeclDatabaseEntry* FnEntry, int depth, int maxdepth);

	void VisitPattern(PatternCodeRegion* PatternOcc, int depth, int maxdepth);

	FanInFanOutCounter* LookupFIFOCounter(HPCParallelPattern* Pattern);

	FanInFanOutCounter* AddFIFOCounter(HPCParallelPattern* Pattern);

	std::vector<PatternOccurence*> GetUniquePatternOccList(std::vector<PatternOccurence*> PatternOccs);

	void FindParentPatterns(PatternCodeRegion* Start, std::vector<PatternOccurence*>& Parents, int maxdepth);
	
	void FindChildPatterns(PatternCodeRegion* Start, std::vector<PatternOccurence*>& Children, int maxdepth);

	void FindNeighbourPatternsRec(PatternTreeNode* Current, std::vector<PatternOccurence*>& Results, SearchDirection dir, int depth, int maxdepth);

	int maxdepth;

	std::vector<FanInFanOutCounter*> FIFOCounter;
};
