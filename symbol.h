/* from:  https://github.com/D4ryus/studium/blob/232501b41a4bd9e1d509d998957b1cb1fc6fd16a/sem_06/co_exercise_01/global.h */

/**************** global.h  - SS 2013     ************/

#ifndef GLOBAL_H
#define GLOBAL_H
#endif

#include <limits.h>
#include <ctype.h>
#include <string.h>

//#define TRUE		  1
//#define FALSE		  0
#define BSIZE		512	/* Puffergrösse */
#define NONE		 -1	/* Vorbesetzung für num */
#define EOS	       '\0'	/* End of String */

#define NESTMAX		 10	/* Max. Schachtelungstiefe von Blöcken */
#define STRMAX		999	/* Länge des Stringfeldes */
#define SYMMAX		 20	/* Größe der Teil-Symboltabelle */

/* Definition der Codierung für Tokentypen */
#define INTNUM	       2561	/* Int-Konstante */
#define REALNUM	       2562	/* Real-Konstante */

#define ID		257	/* Identifikator */
#define CONST 		258	/* Schlüsselwort const */
#define VAR		259	/* Schlüsselwort var */
#define PROCEDURE	260	/* Procedure */
#define CALL		261	/* call */
#define BEGIN 		262	/* begin */
#define END		263	/* end */
#define IF		264	/* if */
#define THEN		265	/* then */
#define WHILE		266	/* while */
#define DO		267	/* do */
#define EQ		268	/* = */
#define NE		269	/* != */
#define LT		270	/* <  */
#define	LE		271	/* <= */
#define	GT		272	/* >  */
#define	GE		273	/* >= */
#define ASS		274	/* := */
#define KOMMA		275	/* ,  */
#define SEMICOLON	276	/* ;  */
#define PLUS		277	/* +  */
#define MINUS		278	/* -  */
#define MULT		279	/* *  */
#define DIV		280	/* /  */
#define KLAUF		281	/* (  */
#define KLZU		282	/* )  */
#define PUNKT		283	/* .  */

#define COLON		284	/*  :  */
#define INT		285	/* int */
#define REAL		286	/* real */
#define BOOL		287	/* boolean */
#define TRUE		288	/* true */
#define FALSE		289	/* false */

#define DONE		300	/* Ende-Token */

/* Definition der Art der ST- Einträge  */
#define KONST		310	/* Konstante */
#define INTIDENT	320	/* Identifikator vom Typ int  */
#define REALIDENT	330	/* Identifikator vom Typ real */
#define BOOLIDENT	340	/* Identifikator vom Typ boolean */
#define PROC		400	/* Procedure */

/* Definition der Typen für Typprüfungen   */
#define INT_TYPE	321
#define REAL_TYPE	331
#define BOOL_TYPE	341

/****************Typ und extern-Deklarationen***********************/
/* Symboltabelle  */
struct symtable;

/* Aufbau eines Symboltabellen-Eintrags */
struct st_entry
{
	/* (KONST/INTIDENT/REALIDENT/BOOLIDENT/PROC) */
	int token;		/* Art des Eintrags */
	char *name;		/* Zeiger auf Namen */
	int wertaddr;		/*
				 * Wert bei Konstanten (KONST);
				 * relative Speicheradresse (offset) bei
				 * Variablen
				 */
	struct symtable *subsym; /* Zeiger auf Teil-Symboltabelle bei Art PROC */
};

/* Aufbau der (Teil- )Symboltabelle */
struct symtable
{
	struct symtable *precsym;/* Zeiger auf übergeordnete Symboltabelle;
				  * bei oberster NULL
				  */
	int level;		/* Schachtelungstiefe */
	int anzahl;		/* Anzahl der Symboltabelleneinträge */
	struct st_entry eintrag[SYMMAX]; /* Feld für Einträge */
};

extern FILE *fsym;
extern FILE *ftra;

extern int level;

extern char idname[];		/* Zeiger auf Namen bei Identifikator */
extern int num;			/* Wert einer integer-Konstanten/ Zahl */
extern double realnum; 		/* Wert einer Real-Konstanten */
extern int lineno;		/* Zeilennummer */
extern struct symtable *actsym;	/* Zeiger auf aktuelle Symboltabelle */
extern struct symtable *firstsym;	/* Zeiger auf oberste (globale) Symboltabelle */
extern int tracesw;		/* Kennung, ob Trace gewünscht */

/******************** Prototypen für Prozeduren *******************/
void initialize();		/* Compiler initialisieren */
void stop();			/* Beenden */

void initlexan();		/* Scanner initialisieren */
int lookforres(char *);		/*
				 * sucht in Tabelle der
				 * res. Symbole nach Zeichenkette
				 */
int nextsymbol();		/* liest nächstes Symbol der Eingabe */

struct symtable *create_newsym(); /* Neue ST erzeugen */
struct st_entry *lookup(char *s); /* Namen in ganzer Symboltabelle suchen */
struct st_entry *lookup_in_actsym(char *s);

/* Namen in aktueller Symboltabelle suchen */
struct st_entry *insert(int);	/* Neuen Eintrag in actsym erzeugen */

void constdecl();		/* Verarbeiten einer Konstantendeklaration */
void vardecl();			/* Verarbeiten einer VAriablendeklaration */
void procdecl();		/* Verarbeiten einer Prozedurdeklaration */
int factor(); 			/* Verarbeiten eines Faktors */
int term();			/* Verarbeiten eines Terms */
int expr();			/* Verarbeiten eines Ausdrucks */
int condition(); 		/* Verarbeiten einer Bedingung */
void statement();		/* Verarbeiten Statement */
void program();			/* Programm übersetzen */
void block(struct symtable *neusym); /* Bearbeiten eines Blockes */

void error(int);		/* Fehlerausgabe */
void errortext(char *);		/* Fehlerausgabe */
void warningtext(char *);	/* Warnung ausgeben */
// void generate(int);		/* Codeerzeugung */
void printsymtab(struct symtable *); /* Ausgabe der Symboltabelle */