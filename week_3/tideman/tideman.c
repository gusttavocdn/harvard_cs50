#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
int get_candidate_rank(int candidate, int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

int get_candidate_rank(int candidate, int ranks[])
{
    for (int rank = 0; rank < candidate_count; rank++)
    {
        if (ranks[rank] == candidate)
            return rank + 1;
    }
    return -1;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate_i_rank = get_candidate_rank(i, ranks);

        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                int candidate_j_rank = get_candidate_rank(j, ranks);
                if (candidate_i_rank < candidate_j_rank)
                    preferences[i][j] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {

            int first_candidante_rate_preference = preferences[i][j];
            int second_candidante_rate_preference = preferences[j][i];

            if (first_candidante_rate_preference > second_candidante_rate_preference)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if (first_candidante_rate_preference < second_candidante_rate_preference)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;

    for (int i = 0; i < pair_count - 1; i++)
    {
        int swap = 0;
        int i_rate = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];

        for (int j = i + 1; j < pair_count; j++)
        {
            int j_rate = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];

            if (i_rate < j_rate)
            {
                temp = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = temp;
                swap = 1;
            }
        }

        if (swap == 0)
            break;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
bool is_cycle(int loser, int winner)
{
    if (loser == winner)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && is_cycle(i, winner))
        {
            return true;
        }
    }

    return false;
}

void lock_pairs()
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!is_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate i is a source (i.e., not locked in by any other candidate)
        bool is_source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_source = false;
                break;
            }
        }

        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
