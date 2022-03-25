#include <stdio.h>

#include <vector>
#include <algorithm>
#include <array>
#include <numeric>
#include <map>
#include <string>

int
main(int argc, char ** argv)
{
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	*
	*	1. Lees alle characters van file in een vector.
	*
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	const char * file = "bible.txt";
	FILE * FP = fopen(file, "r");
	if(FP == NULL)
	{
		printf("Could not open file (%s) !", file);
		return -1;
	}
	std::vector<char> chars;
	while(!feof(FP))
	{
		chars.push_back(fgetc(FP));
	}
	fclose(FP);
	printf("Opened file : %s\n", file);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	*
	*	2. Print hoeveel characters de file bevat
	*      (vraag het aan de vector).
	*
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	printf("Characters\t=\t%d\n", (int)chars.size()-1);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	*
	*	3. Print hoeveel regels de file bevat 
	*	   (gebruik de vector en een STL algorithme).
	*
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */	
	printf("Newlines\t=\t%d\n", (int)std::count(chars.begin(), chars.end(), '\n'));
	
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	*
	*	4. Print hoeveel alfabetische characters de file bevat
	*	   (vector + algorithme).
	*
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */	
	printf("Alphabetic characters\t=\t%d\n", 
		(int)std::count_if(chars.begin(), chars.end(), [](char ch) -> bool 
			{
				return ( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') );
			}
		)
	);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	*
	*	5. Zet de letters in de vector om in kleine letters 
	*	   (max 3 regels code).
	*
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */	
	printf("Converting characters to lower case ... %s\n", 
			std::for_each(chars.begin(), chars.end(), [](char & ch) -> void 
			{ 
				ch = tolower(ch); 
			}
		) ? "DONE" : "!DONE"
	);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	*
	*	6. Tel in een lijst voor iedere letter (a..z) hoe vaak hij voorkomt 
	*	   in de vector (diverse manieren mogelijk).
	*	7. Druk deze lijst af 1) op lettervolgorde 2) op hoe vaak een letter 
	*	   voorkomt (gebruikt een algoritme).
	*
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */	
	std::array<int, 26> letters = {0};
	for(char x = 'a', i = 0; x <= 'z'; ++x, ++i)
	{
		printf("num of '%c':\t%d\t%s", x, letters[i] = std::count(chars.begin(), chars.end(), x), (i+1)%3 ? "; " : "\n");
	}

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
	*
	*	8. Bepaal welke woorden er in de tekst voorkomen en druk de 10 meest 
	*	   voorkomende woorden af. Een woord is aaneengesloten reeks letters. 
	*	   (gebruik een map).
	*
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */	
	std::vector<std::string> words;
	std::string word = "";
	bool isWord = false;
	for(char ch : chars)
	{
		if((ch >= 'a' && ch <= 'z'))
		{
			isWord = true;
			word += ch;
		}
		else if(isWord)
		{
			isWord = false;
			words.push_back(word);
			word.erase();
		}
	}
	std::map<std::string, int> dictionary;
	std::vector<std::pair<int, std::string>> wordFrequency;
	std::for_each(words.begin(), words.end(), [&](std::string word) -> void
		{
			dictionary.insert_or_assign(word, dictionary[word] + 1);
		}
	);
	for(std::pair<std::string, int> pair : dictionary)
	{
		wordFrequency.push_back(std::pair<int, std::string>(pair.second, pair.first));
	}
	std::sort(wordFrequency.begin(), wordFrequency.end(), 
		[](std::pair<int, std::string> & a, std::pair<int, std::string> & b) -> bool
		{
			return a.first > b.first;
		}
	);
	printf("\nMost frequent words:\n");
	int n = 10;
	for(unsigned int i = 0; i < n; ++i)
	{
		printf("\t%d.\t: \"%s\"\t\twith (%d) occurances\n", i+1, &wordFrequency[i].second[0], wordFrequency[i].first);
	}

	return 0;
}