# Format Guidelines

1. All classes start with a capital letter
2. All local variables should be named using camelCase
3. All functions should also use camel case and start with a lowercase letter
4. Braces should start on the line following the statement unless the command is being executed in a single line.
5. Use spacing and tabs to appropriately group stuff
6. Functions in source file should be defined in the same order they are declared in the header

## Example Of Good Code Formatting

```
class AnimalHabitat
{
	public:
		AnimalHabitat();
		~AnimalHabitat();
		void eat();
		int getFoodLevel();
		void setFoodLevel(const int& newLevel)

	protected:
		int foodLevel;
		
};

# Coding Practice

1. Whenever possible functions should take a constant reference to any object being passed in
2. Use proper namespaces when creating classes
3. Make all class variables private or protected
4. Create functions to return and set every member variable unless there is *NO* case where it could be passed out/around
5. Always include default constructor and destructor
6. If possible, make any function private or protected
7. Define variables as early as possible without sacrificing efficiency
8. Remove all debug cout statements before submitting code to be pulled
9. Put log statements in useful spots
10. Enclose any situation where an external data could cause an error in the program in try/catch statements
11. Name variables descriptively and reserve names less than three characters for iterators and the like
12. Remember your header guards
13. Do not #include anything in the source file
14. In large functions, it’s a good idea to have one return statement

#Commenting

1. Put comments
2. Comments should be given after every non-standard function definition in header. (Standard functions include default constructors and set/get member variables)