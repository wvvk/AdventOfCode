#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <queue>

/* Winnie Kam 
https://adventofcode.com/2022/day/1
*/

using namespace std;

struct ElfInfo
{
    unsigned int elf_num;
    unsigned int calories;
};

vector<unsigned int> ReadInputFile(const string &filename)
{
    ifstream file(filename); 
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file: " << filename << endl;
        return {};
    }

    string line;
    set<unsigned int> calories_each;
    vector<unsigned int> calorie_sums;

    while (getline(file, line))
    {

        if (line.empty())
        {
            // new section
            if (!calories_each.empty())
            {
                unsigned int sum = 0;
                for (unsigned int cal : calories_each)
                {
                    sum += cal;
                }
                calorie_sums.push_back(sum);
                calories_each.clear();
            }
        }
        else
        {
            unsigned int calories = 0;

            stringstream ss(line);
            if (ss >> calories)
            {
                calories_each.insert(calories);
            }
        }
    }

    file.close();
    return calorie_sums;
}

int main(int argc, char *argv[])
{
    auto cmp = [](const ElfInfo &elf1, const ElfInfo &elf2)
    {
        return elf1.calories < elf2.calories;
    };

    priority_queue<ElfInfo,
                   vector<ElfInfo>, decltype(cmp)>
        max_heap(cmp);

    unsigned int elf_num = 0;

    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }

    const string file_name{argv[1]};
    vector<unsigned int> calories =
        ReadInputFile(file_name);

    for (unsigned int cal : calories)
    {
        ElfInfo ei{elf_num, cal};
        max_heap.push(ei);
        elf_num++;
    }

    if (!max_heap.empty()) 
    {
        ElfInfo max_cal = max_heap.top();
        cout << "Elf number " << max_cal.elf_num
             << " carries the most calories with "
             << max_cal.calories << " calories." << endl;
    }

    unsigned int top_three = 3;
    unsigned int top_three_sum = 0;

    while (!max_heap.empty() && top_three)
    {
        ElfInfo max_cal = max_heap.top();
        top_three_sum += max_cal.calories;
        max_heap.pop();
        top_three--;
    }

    cout << "Sum of top 3 elves calories: "
         << top_three_sum << " calories." << endl;

    return 0;
}
