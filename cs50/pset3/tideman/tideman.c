#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int compare(const void *a, const void *b);
bool has_cycle_helper(int index, bool visited[]);
bool has_cycle(int starting_index);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote ---- OK
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i; 
            return true;
        }
    }
    return false;
    
}

// Update preferences given one voter's ranks ---- OK
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j) 
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other ---- OK
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

int compare(const void *a, const void *b) //function to use qsort
{
    //the function gets 2 pointers void and below we cast it to the struct
    pair first = *((pair*)a);
    pair second = *((pair*)b);
    
    //we then calculate the margins using the preference array
    int first_margin = preferences[first.winner][first.loser] - preferences[first.loser][first.winner];
    int second_margin = preferences[second.winner][second.loser] - preferences[second.loser][second.winner];
    
    return (second_margin - first_margin);
    //second - first bc of the qsort documentation (we need to create a descending)
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), compare); 
    //sizeof is a function to determine the size of each element in the array
}

//has_cycle function helper
bool has_cycle_helper(int index, bool visited[])
{
    //checks if index already visited (it means that will close a cycle)
    if (visited[index] == true)
    {
        return true;
    }
    
    //if it wasnt, now it is
    visited[index] = true;
    
    //now, iterate for "neighboors" in the graph
    for (int i = 0; i < candidate_count; i++)
    {
        //if there is an edge from the candidate index to the ith neighboor && uses recursion
        if (locked[index][i] && has_cycle_helper(i, visited))
        {
            return true;
            
        }
    }
    return false;
}

//checks for cycle for the lock_pairs function
bool has_cycle(int starting_index)
{
    //initialize a boolean array (all values equals to false) to check if already visited the candidate
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }
    return has_cycle_helper(starting_index, visited);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //locked[i][j] = boolean
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (has_cycle(pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

bool is_source(int index)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][index])
        {
            return false;
        }
    }
    return true;
}

int get_source()
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_source(i))
        {
            return i;
        }
    }
    return -1;
}

// Print the winner of the election
void print_winner(void)
{
    int winner = get_source();
    if (winner != -1)
    {
        printf("%s\n", candidates[winner]);
    }
        
}


