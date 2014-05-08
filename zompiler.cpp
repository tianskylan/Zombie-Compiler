// zompiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "node.h"
#include "parser.hpp"
#include <fstream>
#include <conio.h>

extern int g_LineNumber;
extern NBlock* g_MainBlock;

int _tmain(int argc, _TCHAR* argv[])
{
	zompilerparse();

	if (g_MainBlock)
	{
		CodeContext myContext;
		g_MainBlock->CodeGen(myContext);
		
		
		auto curPair = myContext.gotos.begin();
		auto curValue = curPair->second;
		while (curValue == (++curPair)->first)
		{
			curValue = curPair->second;
			if (curValue == 1)
			{
				break;
			}
		}

		for (auto it = myContext.gotos.begin(); it != myContext.gotos.end(); ++it)
		{
			myContext.m_Ops[(it->first) - 1] = "goto,1";
		}

		//Output the zom file
		std::ofstream fout("out.zom");
		if (fout.is_open())
		{
			for (unsigned int i = 0; i < myContext.m_Ops.size(); ++i)
			{
				fout << myContext.m_Ops[i] << std::endl;
			}
		}
		else
		{
			std::cout << "Cannot create output file out.zom." << std::endl;
		}
	}
	_getch();
	return 0;
}

void zompilererror(const char* s)
{
	std::cout << s << " on line " << g_LineNumber << std::endl;
}
