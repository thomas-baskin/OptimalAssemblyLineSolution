#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <fstream>

class UnboundedKnapsack
{
    //-------------------------------------------------------------------------
    //      Attributes
    //-------------------------------------------------------------------------
    /**
    * Stores maximum value of the knapsack for a certain capacity.
    */
    std::vector<int> knapsack;

    /**
    * Stores elements that are part of the knapsack with a certain capacity.
    * <li><b>Line:</b> Knapsack capacity</li>
    * <li><b>Column:</b> Elements</li>
    */
    std::vector<std::vector<int> > selectedElements;

    /**
    * Stores maximum knapsack capacity.
    */
    int maximumCapacity;


public:
    //-------------------------------------------------------------------------
    //      Constructor
    //-------------------------------------------------------------------------
    UnboundedKnapsack()
    {
        maximumCapacity = -1;
    }


    //-------------------------------------------------------------------------
    //      Destructor
    //-------------------------------------------------------------------------
    ~UnboundedKnapsack()
    {
        delete this;
    }


    //-------------------------------------------------------------------------
    //      Methods
    //-------------------------------------------------------------------------
    /**
    * Unbounded knapsack allows to use one or more occurrences of an item.
    *
    * @param        w Weight of the elements
    * @param        v Value of the elements
    * @param        N Number of itens
    * @param        W Maximum weight capacity
    * @return       This object to allow chained calls
    */
    UnboundedKnapsack* knapsack_unbounded(std::vector<int>& w, std::vector<int>& v, int N, int W)
    {
        // Stores the maximum value which can be reached with a certain capacity
        knapsack.clear();
        knapsack.resize(W + 1);

        maximumCapacity = W + 1;

        // Stores selected elements with a certain capacity
        selectedElements.resize(W + 1);

        // Initializes maximum value vector with zero
        for (int i = 0; i < W + 1; i++) {
            knapsack[i] = 0;
        }

        // Computes the maximum value that can be reached for each capacity
        for (int capacity = 0; capacity < W + 1; capacity++) {
            // Goes through all the elements
            for (int n = 0; n < N; n++) {
                if (w[n] <= capacity) {
                    // max(knapsack[capacity], knapsack[capacity - w[n]] + v[n])
                    if (knapsack[capacity] <= knapsack[capacity - w[n]] + v[n]) {
                        knapsack[capacity] = knapsack[capacity - w[n]] + v[n];

                        // Stores selected elements
                        selectedElements[capacity].clear();
                        selectedElements[capacity].push_back(n + 1);

                        for (int elem : selectedElements[capacity - w[n]]) {
                            selectedElements[capacity].push_back(elem);
                        }
                    }
                }
            }
        }

        return this;
    }

    /**
    * Returns maximum value for a certain number of elements and a certain
    * capacity.
    *
    * @param        capacity Capacity of the knapsack
    * @return       Maximum possible value with capacity provided
    * @throws       std::invalid_argument If capacity provided is out of bounds
    */
    int getMaximumValue(int capacity)
    {
        if (capacity < 0 || capacity >= maximumCapacity)
            throw std::invalid_argument("Capacity out of bounds");

        return knapsack[capacity];
    }

    /**
    * Returns elements that belong to the knapsack with a certain capacity.
    *
    * @param        capacity Capacity of the knapsack
    * @return       Elements that are part of the knapsack with the capacity
    * provided
    * @throws       std::invalid_argument If capacity provided is out of bounds
    * @apiNote      Elements are referenced by their index + 1
    */
    std::vector<int>& getSelectedElements(int capacity)
    {
        if (capacity < 0 || capacity >= maximumCapacity)
            throw std::invalid_argument("Capacity out of bounds");

        return selectedElements[capacity];
    }

    /**
    * Returns elements that are part of the knapsack with a certain capacity.
    * This method will return a {@link std::string} with the following format:
    * <code>[elem1, elem2, elem3...]</code>
    *
    * @param        capacity Capacity of the knapsack
    * @return       Elements that are part of the knapsack with the capacity
    * provided
    * @apiNote      Elements are referenced by their index + 1
    */
    std::string selectedElements_toString(int capacity)
    {
        std::string response = "[";

        for (int element : selectedElements[capacity]) {
            response.append(std::to_string(element));
            response.append(", ");
        }

        // Removes last ", "
        response.pop_back();
        response.pop_back();

        response.append("]");

        return response;
    }
};


//-------------------------------------------------------------------------
//      Main
//-------------------------------------------------------------------------
/**
* Example made based on this exercise:
* {@link https://www.urionlinejudge.com.br/repository/UOJ_1487_en.html}
*/

// void functionName(std::string fileName)
// {
//     std::ifstream csvMap(fileMap);
//     std::string oneLine;

    // while(getline(csvMap, oneLine)){

    //     std::vector<std::string> v;
    //     std::stringstream ss(fileMap);
    //     while(ss.good()){
    //         std::string substr;
    //         getline(ss, substr, ',');
    //         v.push_back(substr);
    //     }
    //     // this gives us v which contains all the cells in a row

    // }

    // std::vector<std::vector<std::string>> allLines;
    // std::vector<std::string> oneLineOfStrs;
    // std::string oneLine;
    // std::ifstream csvMap(fileName);

    // // Use a while loop together with the getline() function to read the file line by line
    // while (getline(csvMap, oneLine)) 
    // {
    //     for(int i = 0; i < oneLine.length(); i++)
    //     {
    //         oneLineOfStrs.push_back(oneLine[i]);
    //         // if(oneLine[i] == '-')
    //         // {
    //         //     std::cout << i;
    //         // }
    //     }
    //     allLines.push_back(oneLineOfStrs);
    //     oneLineOfStrs.clear();
    // }
// }

int main()
{

    //W = 16
    //val = [345,285,340,1275,1025]
    //wt = [3,3,4,5,5]

    // Open file
    //

    // Create elements_weight // Starters column                //starters in order from lowest number of starters to greatest
    // Create elements_values // Profit column
    // Create totalCapacity = number of starters
    // Create elements = len(startersColumn)

    UnboundedKnapsack* knapsack = new UnboundedKnapsack();
    int totalCapacity = 29, elements = 48;
    std::vector<int> elements_weight = { 1,1,1,1,1,3,3,3,3,4,5,5,5,5,5,5,6,7,7,7,8,9,13,14,15,16,17,18,19,20,20,22,23,25,25,30,30,50,58,72,300,680,1105,3200,4080,4280,4280,8560 };
    std::vector<int> elements_values = { 245,95,95,95,75,345,345,345,285,340,1275,1025,875,875,515,515,1140,1465,1065,565,1280,1875,5605,3230,7225,7020,7515,7310,10075,8300,6820,11710,10885,12775,7945,17070,10450,27050,31510,26640,68500,466600,544475,884000,2479600,2778600,4978600,14957200 };
    //std::vector<int> elements_values = { 345,285,340,1275,1025 };

    knapsack->knapsack_unbounded(elements_weight, elements_values, elements, totalCapacity);

    std::cout << "Maximum value: "
        << knapsack->getMaximumValue(totalCapacity)
        << std::endl;
    std::cout << "Selected elements: "
        << knapsack->selectedElements_toString(totalCapacity)
        << std::endl;

    system("pause");

    return 0;
}