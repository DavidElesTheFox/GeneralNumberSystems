#ifndef TESTER__TESTCASE_H
#define TESTER__TESTCASE_H

#include <iostream>
#include <fstream>


using std::cout;
using std::endl;
using std::string;

namespace Tester
{
	/**
		Ez az osztály õsosztája minden modul tesztnek. A különbözõ elõre definiált függvények segítségével lehet vizsgálni egy kód reagálását különbözõ teszt esetekre.
	  */
    class TestCase
    {
		protected:
			string resultName;		/**< a result fájl neve*/
			std::ofstream* result;	/**< pointer a result fájlra*/
			

			bool ok;			/**< igaz ha a teszteset nem bukott meg*/
		public:
		
			/**
			  Defult konstruktor.
			  @simple
			  */
		    TestCase();
			
			/**
			  Egyszerû konstruktor.
			  @simple
			  */
		    TestCase(string result_name);
			
			/**
				Destruktor.
				@simple
			*/
			~TestCase();
			
			/**
				Bármikor állítható a result fájl
				@simple
			 */
			void setResultFile(string fileName);
			
			/**
				A teszt végeredményét kérdezhetjük le
				@return igaz, ha átment, hamis különben
			  */
			bool isOk() const;
			
			std::string getResultName() const;
	    
			/**
				A teszteset futtatása
				@simple
			*/
		    virtual void run() = 0;
	    
			/**
				megbuktatja a tesztesetet, ha igaz értéket kap
			  */
		    void assertTrue(const bool value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha hamis értéket kap
			  */
		    void assertFalse(const bool value, const string comment  = "") const;
	    
			/**
				megbuktatja a tesztesetet, ha expect egyenlõ a value-val
			  */
		    void assertEquale(const string expect, const string value, const string comment  = "") const;

		    /**
			    megbuktatja a tesztesetet, ha expect egyenl a value-val
		      */
		    void assertEquale(const int expect, const int value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect egyenlõ a value-val
			  */
		    void assertEquale(const double expect, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect nem egyenlõ a value-val
			  */
		    void assertNotEquale(const string expect, const string value, const string comment  = "") const;

		    /**
			    megbuktatja a tesztesetet, ha expect nem egyenlõ a value-val
		      */
		    void assertNotEquale(const int expect, const int value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect nem egyenlõ a value-val
			*/
		    void assertNotEquale(const double expect, const double value, const string comment  = "") const;
		    
			/**
				megbuktatja a tesztesetet, ha expect nagyobb a value-nál
			*/
		    void assertHigher(const double expect, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect nagyobb vagy egyenlõ a value-nál
			*/
		    void assertHigherEquale(const double expect, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect kisebb a value-nál
			*/
		    void assertLower(const double expect, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha expect kisebb vagy egyenlõ a value-nál
			*/
		    void assertLowerEquale(const double expect, const double value, const string comment  = "") const;
	    
			/**
				megbuktatja a tesztesetet, ha value nincs high és low között
			*/
		    void assertNotBetween(const double low, const double high, const double value, const string comment  = "") const;
			
			/**
				megbuktatja a tesztesetet, ha value és expect különbsége nagyobb mint different
			*/
		    void assertDifferentHigher(const double expect, const double different, const double value, const string comment  = "") const;
	
    };
}

#endif
