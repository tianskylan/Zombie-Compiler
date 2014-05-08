%{
#include "node.h"
#include <iostream>
#include <string>
extern int yylex();
extern void yyerror(const char* s);

// Global for the main block
NBlock* g_MainBlock = nullptr;

// Disable the warnings that Bison creates
#pragma warning(disable: 4065)
%}

/* Add one union member for each Node* type */
%union {
    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;
}

/* Terminal symbols */
%token <string> TINTEGER
%token <token> TLBRACE TRBRACE TSEMI TLPAREN TRPAREN TLBRACKET TRBRACKET TINCREMENT TDECREMENT TIF TELSE TEQUAL
%token <token> TMAIN TROTATE TFORWARD TATTACK TRANGED_ATTACK TSAVE_LOC TMEMORY
%token <token> TIS_HUMAN TIS_PASSABLE TIS_RANDOM TIS_ZOMBIE


/* Statements */
%type <block> main_loop block
%type <statement> statement rotate forward attack ranged_attack save_loc memory
%type <statement> if

 
/* Expressions */
%type <numeric> numeric
%type <boolean> boolean is_human is_passable is_random is_zombie

%%

main_loop	: TMAIN TLBRACE block TRBRACE 
{ 
	g_MainBlock = $3;
	g_MainBlock->SetMainBlock();

	std::cout << "Main entry point found!" << std::endl; 
};

block		: statement 
{
	$$ = new NBlock();
	$$->AddStatement($1);
	std::cout << "Single statement" << std::endl; 
}
			| block statement 
{
	$$->AddStatement($2);
	std::cout << "Another statement in block" << std::endl; 
};

statement	: rotate TSEMI
			| forward TSEMI
			| attack TSEMI
			| ranged_attack TSEMI
			| save_loc TSEMI
			| if
			| memory TSEMI
;

boolean		: is_human
			| is_passable
			| is_random
			| is_zombie
;
			
rotate		: TROTATE TLPAREN numeric TRPAREN 
{
	$$ = new NRotate($3);
	std::cout << "Rotate command" << std::endl; 
};

forward		: TFORWARD TLPAREN TRPAREN 
{ 
	$$ = new NForward();
	std::cout << "Forward command" << std::endl; 
};

attack		: TATTACK TLPAREN TRPAREN 
{
	$$ = new NAttack();
	std::cout << "Attack command" << std::endl; 
};

ranged_attack
			: TRANGED_ATTACK TLPAREN TRPAREN 
{
	$$ = new NRanged_attack();
	std::cout << "Ranged_attack command" << std::endl;
};

save_loc	: TSAVE_LOC TLPAREN TRPAREN 
{ 
	$$ = new NSave_loc();
	std::cout << "Save Loc command" << std::endl; 
};

memory		: TMEMORY TLBRACKET numeric TRBRACKET TINCREMENT 
{
	$$ = new NMemory($3, new NNumeric(std::string("1")));
	std::cout << "Memory increment command" << std::endl; 
}
			| TMEMORY TLBRACKET numeric TRBRACKET TDECREMENT 
{ 
	$$ = new NMemory($3, new NNumeric(std::string("-1")));
	std::cout << "Memory decrement command" << std::endl;
}
			| TMEMORY TLBRACKET numeric TRBRACKET TEQUAL numeric 
{ 
	$$ = new NMemory($3, $6);
	std::cout << "Memory assignment command" << std::endl;
};

if			: TIF TLPAREN boolean TRPAREN TLBRACE block TRBRACE
			
{
	$$ = new NIf($3, $6);
	std:: cout << "if command" << std::endl;
};

			| TIF TLPAREN boolean TRPAREN TLBRACE block TRBRACE TELSE TLBRACE block TRBRACE	
{
	$$ = new NIf($3, $6, $10);
	std::cout << "if else command" << std::endl;
};

is_human	: TIS_HUMAN TLPAREN numeric TRPAREN
{
	$$ = new NIs_human($3);
	std::cout << "is_human command" << std::endl; 
};

is_passable	: TIS_PASSABLE TLPAREN TRPAREN
{ 
	$$ = new NIs_passable();
	std::cout << "is_passable command" << std::endl; 
};

is_random	: TIS_RANDOM TLPAREN TRPAREN 
{ 
	$$ = new NIs_random();
	std::cout << "is_random command" << std::endl; 
};

is_zombie	: TIS_ZOMBIE TLPAREN numeric TRPAREN 
{ 
	$$ = new NIs_zombie($3);
	std::cout << "is_zombie command" << std::endl; 
};
		
numeric		: TINTEGER 
{
	$$ = new NNumeric(*($1));
	std::cout << "Numeric value of " << *($1) << std::endl; 
};


%%
