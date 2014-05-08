#pragma once

#include <list>
#include <vector>
#include <string>
#include <map>

struct CodeContext
{
	// map of gotos.
	// Key: line number of goto
	// Value: Jump Destination
	std::map<int, int> gotos;
	std::vector<std::string> m_Ops;
};

class Node
{
public:
	virtual void CodeGen(CodeContext& context) = 0;
};

class NNumeric : public Node
{
public:
	NNumeric(std::string& value);
	int m_value;
	virtual void CodeGen(CodeContext& context) { }
};

class NStatement : public Node
{
public:
	virtual void CodeGen(CodeContext& context) = 0;
};

class NRotate : public NStatement
{
public:
	NRotate(NNumeric* dir);
	virtual void CodeGen(CodeContext& context);
private:
	NNumeric* m_Dir;
};

class NForward : public NStatement
{
public:
	virtual void CodeGen(CodeContext& context);
};

class NAttack : public NStatement
{
public:
	virtual void CodeGen(CodeContext& context);
};

class NRanged_attack : public NStatement
{
public:
	virtual void CodeGen(CodeContext& context);
};

class NSave_loc : public NStatement
{
public:
	virtual void CodeGen(CodeContext& context);
};

class NMemory : public NStatement
{
public:
	NMemory(NNumeric*, NNumeric*);
	virtual void CodeGen(CodeContext& context);
private:
	NNumeric* mem_loc;
	NNumeric* change;
};

class NBoolean : public Node
{
public:
	virtual void CodeGen(CodeContext& context) = 0;
};

class NBlock : public Node
{
public:
	NBlock() { m_bMainBlock = false; }
	virtual void CodeGen(CodeContext& context);
	void AddStatement(NStatement* statement);
	void SetMainBlock() { m_bMainBlock = true; }
private:
	std::list<NStatement*> m_Statements;
	bool m_bMainBlock;
};

class NIf : public NStatement
{
public:
	NIf(NBoolean* cond, NBlock* blk);
	NIf(NBoolean* cond, NBlock* blk, NBlock* els);
	virtual void CodeGen(CodeContext& context);

private:
	NBoolean* m_cond = nullptr;
	NBlock* m_blk = nullptr;
	NBlock* m_else = nullptr;
};

class NIs_human : public NBoolean
{
public:
	NIs_human(NNumeric*);
	virtual void CodeGen(CodeContext& context);

private:
	NNumeric* m_pos;
};

class NIs_passable : public NBoolean
{
public:
	virtual void CodeGen(CodeContext& context);
};

class NIs_random : public NBoolean
{
public:
	virtual void CodeGen(CodeContext& context);
};

class NIs_zombie : public NBoolean
{
public:
	NIs_zombie(NNumeric*);
	virtual void CodeGen(CodeContext& context);

private:
	NNumeric* m_pos;
};