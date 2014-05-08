#include "node.h"
#include <iostream>

void NBlock::AddStatement(NStatement* statement)
{
	m_Statements.push_back(statement);
}

void NBlock::CodeGen(CodeContext& context)
{
	// TODO: Loop through statements in list and code gen them
	for (auto it = m_Statements.begin(); it != m_Statements.end(); ++it)
	{
		(*it)->CodeGen(context);
	}
	if (m_bMainBlock)
	{
		context.m_Ops.push_back("goto,1");
		int lineNumber = context.m_Ops.size();
		context.gotos[lineNumber] = 1;
	}
}

NNumeric::NNumeric(std::string& value)
{
	m_value = std::atoi(value.c_str());
}

NRotate::NRotate(NNumeric* dir)
	: m_Dir(dir)
{
}

void NRotate::CodeGen(CodeContext& context)
{
	if (m_Dir->m_value == 0)
	{
		context.m_Ops.push_back("rotate,0");
	}
	else if (m_Dir->m_value == 1)
	{
		context.m_Ops.push_back("rotate,1");
	}

}


void NForward::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("forward");
}

void NAttack::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("attack");
}

void NRanged_attack::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("ranged_attack");
}

void NSave_loc::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("save_loc");
}

NMemory::NMemory(NNumeric* loc, NNumeric* num)
: mem_loc(loc), change(num)
{
}

void NMemory::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("mem," + std::to_string(mem_loc->m_value));
	if (change->m_value == 1)
	{
		context.m_Ops.push_back("inc");
	}
	else if (change->m_value == -1)
	{
		context.m_Ops.push_back("dec");
	}
	else
	{
		context.m_Ops.push_back("set" + std::to_string(change->m_value));
	}
}

NIf::NIf(NBoolean* cond, NBlock* blk)
	: m_cond(cond), m_blk(blk)
{
	
}

NIf::NIf(NBoolean* cond, NBlock* blk, NBlock* els)
: m_cond(cond), m_blk(blk), m_else(els)
{

}

void NIf::CodeGen(CodeContext& context)
{
	// 1. Test case
	m_cond->CodeGen(context);
	
	// 2. Je to if block
	context.m_Ops.push_back("je,");
	int jePos = context.m_Ops.size() - 1;

	// 3. Else
	if (m_else)
	{
		m_else->CodeGen(context);
	}
	// 4. goto pass if block

	context.m_Ops.push_back("goto,");
	int lineNumber = context.m_Ops.size();



	int gotoPos = context.m_Ops.size() - 1;

	int ifBegin = context.m_Ops.size() + 1;


	// 5. if block
	m_blk->CodeGen(context);
	int ifEnd = context.m_Ops.size() + 1;
	
	// 6. Go back and change step 2 and 4
	context.m_Ops[jePos] += std::to_string(ifBegin);
	context.m_Ops[gotoPos] += std::to_string(ifEnd);
	context.gotos[lineNumber] = ifEnd;

}


NIs_human::NIs_human(NNumeric* inPos) : m_pos(inPos)
{
}

void NIs_human::CodeGen(CodeContext& context)
{
	if (m_pos->m_value == 1)
	{
		context.m_Ops.push_back("test_human,1");
	}
	else if (m_pos->m_value == 2)
	{
		context.m_Ops.push_back("test_human,2");
	}
}

void NIs_passable::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("test_passable");
}

void NIs_random::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("test_random");
}

NIs_zombie::NIs_zombie(NNumeric* inPos) : m_pos(inPos)
{
}

void NIs_zombie::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("test_zombie," + std::to_string(m_pos->m_value));
}