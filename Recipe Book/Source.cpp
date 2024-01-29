#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;

// Base class for all recipes
class Recipe {
public:
    // Common attributes for all recipes
    string name;
    vector<string> ingredients;
    vector<string> steps;
    int cookingTime;

    // Default constructor
    Recipe() : name(""), cookingTime(0) {}

    // Constructor with parameters
    Recipe(const string& n, const vector<string>& ing, const vector<string>& st, int time)
        : name(n), ingredients(ing), steps(st), cookingTime(time) {}

    // Setters
    void set_name(const string& n) {
        name = n;
    }

    void set_ingredients(const vector<string>& ing) {
        ingredients = ing;
    }

    void set_steps(const vector<string>& st) {
        steps = st;
    }

    void set_cooking_time(int time) {
        cookingTime = time;
    }

    // Getters
    string get_name() const {
        return name;
    }

    vector<string> get_ingredients() const {
        return ingredients;
    }

    vector<string> get_steps() const {
        return steps;
    }

    int get_cooking_time() const {
        return cookingTime;
    }

    string get_recipe() const {
        string temp;
        temp += "Recipe: " + name + "\n";

        // Add ingredients
        temp += "Ingredients:\n";
        for (const auto& ingredient : ingredients) {
            temp += "- " + ingredient + "\n";
        }

        // Add steps
        temp += "Steps:\n";
        for (const auto& step : steps) {
            temp += step + "\n";
        }

        // Add cooking time
        temp += "Cooking Time: " + to_string(cookingTime) + " minutes\n";

        // Add other attributes specific to MainCourseRecipe or DessertRecipe if needed

        return temp;
    }


    virtual string get_cuisine() const {
        return "";  // Default implementation for non-MainCourseRecipe instances
    }

    // Displaying recipe details
    virtual void display() const {
        cout << "Recipe: " << name << "\n";
        cout << "Ingredients:\n";
        for (const auto& ingredient : ingredients) {
            cout << "- " << ingredient << "\n";
        }
        cout << "Steps:\n";
        for (const auto& step : steps) {
            cout << step << "\n";
        }
        cout << "Cooking Time: " << cookingTime << " minutes\n";
    }

    virtual void edit() {}

    virtual void add_to_shopping_list() const {
        // Add code to add recipe to the shopping list
        cout << "Recipe added to the shopping list.\n";
    }

    virtual void plan_meal(int day) const {
        // Add code to plan the recipe
        cout << "Recipe planned for day " << day << ".\n";
    }

    virtual void set_cuisine(const string& c) {
        // No-op in the base class, as not all recipes have a cuisine
    }
};

// Feature class for nutritional information
class NutritionFeature {
public:
    virtual void display_nutritional_info() const = 0;
};

// Derived class for Main Course recipes
class MainCourseRecipe : public Recipe, public NutritionFeature {
public:
    // Additional attribute for Main Course recipes
    string cuisine;

    // Default constructor
    MainCourseRecipe() : cuisine("") {}

    // Constructor with parameters
    MainCourseRecipe(const string& n, const vector<string>& ing, const vector<string>& st, int time, const string& c)
        : Recipe(n, ing, st, time), cuisine(c) {}

    

    // Setters
   
    void set_cuisine(const string& c) override {
        cuisine = c;
    }

    // Override the virtual function to get cuisine
    string get_cuisine() const override {
        return cuisine;
    }

    // Display function
    void display() const override {
        Recipe::display();
        cout << "Cuisine: " << cuisine << "\n";
    }

    // Function to display nutritional information for Main Course recipes
    void display_nutritional_info() const override {
        // Add code to display nutritional information for Main Course recipes
        cout << "Nutritional information for Main Course: ...\n";
    }
};

// Feature class for meal planning
class MealPlanningFeature {
public:
    virtual void generate_meal_plan() const = 0;
};

// Derived class for Dessert recipes
class DessertRecipe : public Recipe, public MealPlanningFeature {
public:
    // Additional attribute for Dessert recipes
    string type;

    // Default constructor
    DessertRecipe() : type("") {}

    // Constructor with parameters
    DessertRecipe(const string& n, const vector<string>& ing, const vector<string>& st, int time, const string& t)
        : Recipe(n, ing, st, time), type(t) {}

    // Setters
    void set_type(const string& t) {
        type = t;
    }

    // Getters
    string get_type() const {
        return type;
    }

    // Display function
    void display() const override {
        Recipe::display();
        cout << "Type: " << type << "\n";
    }

    // Function to generate meal plan for Dessert recipes
    void generate_meal_plan() const override {
        // Add code to generate meal plan for Dessert recipes
        cout << "Meal plan for Dessert: ...\n";
    }
};

// Recipe book class to manage recipes
class RecipeBook {
private:
    vector<Recipe*> recipes;
    map<string, vector<Recipe*>> categoryMap;

public:

    const vector<Recipe*>& getRecipes() const {
        return recipes;
    }

    const map<string, vector<Recipe*>>& getCategoryMap() const {
        return categoryMap;
    }

    // Add a new recipe
    void add_recipe(Recipe* newRecipe) {
        recipes.push_back(newRecipe);

        // Check the type of the recipe and categorize accordingly
        if (dynamic_cast<MainCourseRecipe*>(newRecipe) != nullptr) {
            MainCourseRecipe* mainCourseRecipe = dynamic_cast<MainCourseRecipe*>(newRecipe);
            categoryMap[mainCourseRecipe->get_cuisine()].push_back(mainCourseRecipe);
        }
        else if (dynamic_cast<DessertRecipe*>(newRecipe) != nullptr) {
            DessertRecipe* dessertRecipe = dynamic_cast<DessertRecipe*>(newRecipe);
            categoryMap[dessertRecipe->get_type()].push_back(dessertRecipe);
        }

        categoryMap["All"].push_back(newRecipe);
    }

    // Display all recipes
    void display_all_recipes() const {
        cout << "All Recipes:\n";
        for (const auto& recipe : recipes) {
            recipe->display();
            cout << "-----------------\n";
        }
    }

    // Display recipes based on a specific category
    void display_recipes_by_category(const string& category) const {
        if (categoryMap.find(category) != categoryMap.end()) {
            cout << "Recipes in Category '" << category << "':\n";
            for (const auto& recipe : categoryMap.at(category)) {
                recipe->display();
                cout << "-----------------\n";
            }
        }
        else {
            cout << "Category not found.\n";
        }
    }

    // Search for recipes based on ingredients
    vector<Recipe*> search_recipes_by_ingredient(const string& ingredient) const {
        vector<Recipe*> result;
        for (const auto& recipe : recipes) {
            if (find(recipe->get_ingredients().begin(), recipe->get_ingredients().end(), ingredient) != recipe->get_ingredients().end()) {
                result.push_back(recipe);
            }
        }
        return result;
    }



    // Delete a recipe
    void delete_recipe(Recipe* recipeToDelete) {
        auto it = find(recipes.begin(), recipes.end(), recipeToDelete);
        if (it != recipes.end()) {
            // Remove from categories first
            for (auto& categoryPair : categoryMap) {
                auto& categoryRecipes = categoryPair.second;
                auto catIt = find(categoryRecipes.begin(), categoryRecipes.end(), recipeToDelete);
                if (catIt != categoryRecipes.end()) {
                    categoryRecipes.erase(catIt);
                }
            }

            // Delete the recipe
            delete* it;
            recipes.erase(it);

            cout << "Recipe deleted successfully.\n";
        }
        else {
            cout << "Recipe not found.\n";
        }
    }

    void delete_recipe(size_t index) {
        // Ensure the index is within bounds
        if (index < recipes.size()) {
            // Use erase to remove the recipe at the specified index
            recipes.erase(recipes.begin() + index);
        }
    }

    void display_all_categories() const {
        cout << "Categories:\n";
        int count = 1;
        for (const auto& categoryPair : categoryMap) {
            cout << count << ". " << categoryPair.first << "\n";
            ++count;
        }
    }

};



class Menu {
public:
    Menu(sf::RenderWindow& window) : window(window) {}

    int showMenu(RecipeBook& recipeBook) {
        int choice = -1;


        while (window.isOpen() && choice == -1) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                    case sf::Keyboard::Num1:
                        addRecipe(recipeBook);
                        break;
                    case sf::Keyboard::Num2:
                        drawRecipeBook(recipeBook);
                        break;
                    case sf::Keyboard::Num3:
                        displayRecipesByCategory(recipeBook);
                        break;
                    case sf::Keyboard::Num4:
                        deleteRecipe(recipeBook);
                        break;
                    case sf::Keyboard::Num0:
                        window.close();
                        break;
                    default:
                        break;
                    }
                }
            }
           
            window.clear();
            this->drawMenu();
            window.display();
        }

        return choice;
    }

    void drawRecipeBook(RecipeBook& recipeBook) {
        window.clear(sf::Color(25, 149, 230));

        // Assuming you have a font loaded for text rendering
        sf::Font font;
        if (!font.loadFromFile("Nexa-Heavy.ttf")) {
            // Handle font loading failure
        }

        // Create a text object for rendering
        sf::Text recipeText;
        recipeText.setFont(font);
        recipeText.setCharacterSize(18);
        recipeText.setFillColor(sf::Color::White);

        sf::Text text1;
        text1.setFont(font);
        text1.setCharacterSize(15);
        text1.setFillColor(sf::Color::White);
        text1.setString("Press Right arow key to move forward \n Press Left arrow key to go back \n Press esc to return to menu");
        text1.setPosition(250, 520);

        window.draw(text1);
        

        // Display all recipes
        const vector<Recipe*>& recipes = recipeBook.getRecipes();

        // Ensure there's at least one recipe
        if (!recipes.empty()) {
            static size_t currentRecipeIndex = 0; // Keep track of the current recipe index

            // Display recipe details using SFML text
            recipeText.setString(recipes[currentRecipeIndex]->get_recipe());
            recipeText.setPosition(10, 10); // Set the position for recipe details
            window.draw(recipeText);

            // Add similar rendering for other recipe details like ingredients, steps, cooking time, etc.
            // You may need to adjust the formatting and positions based on your requirements.

            window.display();  // Display the current recipe

            // Handle user input
            bool exit = false;
            while (window.isOpen() && !exit) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    else if (event.type == sf::Event::KeyPressed) {
                        switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            exit = true;  // Exit the loop and go back to the menu
                            break;
                        case sf::Keyboard::Right:
                            // Navigate to the next recipe
                            currentRecipeIndex = (currentRecipeIndex + 1) % recipes.size();
                            break;
                        case sf::Keyboard::Left:
                            // Navigate to the previous recipe
                            currentRecipeIndex = (currentRecipeIndex == 0) ? recipes.size() - 1 : currentRecipeIndex - 1;
                            break;
                        default:
                            break;
                        }

                        // Update displayed recipe details
                        recipeText.setString(recipes[currentRecipeIndex]->get_recipe());
                        recipeText.setPosition(10, 10); // Adjust position based on your layout
                        window.clear(sf::Color(25, 149, 230));  // Clear the window before redrawing
                        window.draw(recipeText);
                        window.draw(text1);
                        window.display();  // Display the updated recipe
                    }
                }
            }
        }
        else {
            // Display a message if there are no recipes
            recipeText.setString("No recipes available.");
            recipeText.setPosition(10, 10); // Adjust position based on your layout
            window.draw(recipeText);
            window.draw(text1);
            window.display();  // Display the message

            // Handle user input for an empty recipe book
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    // Exit the loop and go back to the menu
                    return;
                }
            }
        }
    }

    void displayRecipesByCategory(const RecipeBook& recipeBook) {
        window.clear(sf::Color(25, 149, 230));

        // Assuming you have a font loaded for text rendering
        sf::Font font;
        if (!font.loadFromFile("Nexa-Heavy.ttf")) {
            // Handle font loading failure
        }

        // Create a text object for rendering
        sf::Text categoryText;
        categoryText.setFont(font);
        categoryText.setCharacterSize(18);
        categoryText.setFillColor(sf::Color::White);

        // Display all categories
        const map<string, vector<Recipe*>>& categories = recipeBook.getCategoryMap();

        if (!categories.empty()) {
            string categoryOptions = "Categories:\n";
            int count = 1;
            for (const auto& categoryPair : categories) {
                categoryOptions += to_string(count) + ". " + categoryPair.first + "\n";
                ++count;
            }

            categoryText.setString(categoryOptions);
            categoryText.setPosition(10, 10); // Set the position for category details
            window.draw(categoryText);

            window.display(); // Display the categories

            // Handle user input
            bool exit = false;
            while (window.isOpen() && !exit) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    else if (event.type == sf::Event::KeyPressed) {
                        switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            exit = true; // Exit the loop and go back to the menu
                            break;
                        case sf::Keyboard::Num1:
                        case sf::Keyboard::Num2:
                        case sf::Keyboard::Num3:
                        case sf::Keyboard::Num4:
                        case sf::Keyboard::Num5:
                            // Assuming you have a function to display recipes for a specific category
                            // Implement the function based on your requirements
                            displayRecipesForSelectedCategory(recipeBook, event.key.code - sf::Keyboard::Num1 + 1);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
        else {
            // Display a message if there are no categories
            categoryText.setString("No categories available.");
            categoryText.setPosition(10, 10); // Adjust position based on your layout
            window.draw(categoryText);
            window.display(); // Display the message

            // Handle user input for an empty category list
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    // Exit the loop and go back to the menu
                    return;
                }
            }
        }
    }

    void displayRecipesForSelectedCategory(RecipeBook recipeBook, int selectedCategory) {
        window.clear(sf::Color(25, 149, 230));

        // Assuming you have a font loaded for text rendering
        sf::Font font;
        if (!font.loadFromFile("Nexa-Heavy.ttf")) {
            // Handle font loading failure
        }

        // Create a text object for rendering
        sf::Text recipeText;
        recipeText.setFont(font);
        recipeText.setCharacterSize(18);
        recipeText.setFillColor(sf::Color::White);

        sf::Text text1;
        text1.setFont(font);
        text1.setCharacterSize(15);
        text1.setFillColor(sf::Color::White);
        text1.setString("Press Right arow key to move forward \n Press Left arrow key to go back \n Press esc to return to menu");
        text1.setPosition(250, 520);

        window.draw(text1);

        // Display recipes for the selected category
        const map<string, vector<Recipe*>>& categories = recipeBook.getCategoryMap();

        int count = 1;
        auto it = categories.begin();
        while (it != categories.end() && count < selectedCategory) {
            ++it;
            ++count;
        }

        if (it != categories.end()) {
            string categoryName = it->first;
            const vector<Recipe*>& categoryRecipes = it->second;

            if (!categoryRecipes.empty()) {
                static size_t currentRecipeIndex = 0; // Keep track of the current recipe index

                // Display recipe details using SFML text
                recipeText.setString(categoryRecipes[currentRecipeIndex]->get_recipe());
                recipeText.setPosition(10, 10); // Set the position for recipe details
                window.draw(recipeText);

                window.display(); // Display the current recipe

                // Handle user input
                bool exit = false;
                while (window.isOpen() && !exit) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                        }
                        else if (event.type == sf::Event::KeyPressed) {
                            switch (event.key.code) {
                            case sf::Keyboard::Escape:
                                this->showMenu(recipeBook);
                                break;
                            case sf::Keyboard::Right:
                                // Navigate to the next recipe
                                currentRecipeIndex = (currentRecipeIndex + 1) % categoryRecipes.size();
                                break;
                            case sf::Keyboard::Left:
                                // Navigate to the previous recipe
                                currentRecipeIndex = (currentRecipeIndex == 0) ? categoryRecipes.size() - 1 : currentRecipeIndex - 1;
                                break;
                            default:
                                break;
                            }

                            // Update displayed recipe details
                            recipeText.setString(categoryRecipes[currentRecipeIndex]->get_recipe());
                            recipeText.setPosition(10, 10); // Adjust position based on your layout
                            window.clear(sf::Color(25, 149, 230)); // Clear the window before redrawing
                            window.draw(recipeText);
                            window.draw(text1);
                            window.display(); // Display the updated recipe
                        }
                    }
                }
            }
            else {
                // Display a message if there are no recipes for the selected category
                recipeText.setString("No recipes available for category: " + categoryName);
                recipeText.setPosition(10, 10); // Adjust position based on your layout
                window.draw(recipeText);
                window.display(); // Display the message

                // Handle user input for an empty recipe list
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        // Exit the loop and go back to the menu
                        return;
                    }
                }
            }
        }
    }

    void addRecipe(RecipeBook& recipeBook) {
        window.clear(sf::Color(25, 149, 230));

        sf::Font font;
        if (!font.loadFromFile("Nexa-Heavy.ttf")) {
            // Handle font loading failure
        }

        sf::Text promptText("Enter Recipe Details:", font, 30);
        promptText.setPosition(10, 10);

        sf::Text userInputText("", font, 20);
        userInputText.setPosition(10, 50);

        window.draw(promptText);
        window.draw(userInputText);
        window.display();

        string name, ingredients, steps, cuisine, type;
        int cookingTime;
        int state = 0; // State machine variable to track user input

        sf::Event event;
        string currentInput;

        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && state < 5) {
                    // Process user input based on state
                    switch (state) {
                    case 0: // Name input
                        name = currentInput;
                        currentInput = "";
                        state++;
                        promptText.setString("Enter Ingredients (comma-separated):");
                        break;
                    case 1: // Ingredients input
                        ingredients = currentInput;
                        currentInput = "";
                        state++;
                        promptText.setString("Enter Steps (each step on a new line):");
                        break;
                    case 2: // Steps input
                        steps = currentInput;
                        currentInput = "";
                        state++;
                        promptText.setString("Enter Cooking Time (in minutes):");
                        break;
                    case 3: // Cooking Time input
                        cookingTime = stoi(currentInput);
                        currentInput = "";
                        state++;
                        promptText.setString("Enter Cuisine Type:");
                        break;
                    case 4: // Cuisine Type input
                        cuisine = currentInput;
                        currentInput = "";
                        state++;
                        promptText.setString("Recipe added successfully! \nPress esc to Return");
                        break;
                    }

                    // Update displayed prompt and user input
                    userInputText.setString(currentInput);
                    window.clear(sf::Color(25, 149, 230));
                    window.draw(promptText);
                    window.draw(userInputText);
                    window.display();
                }
                else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 8) { // Handle backspace
                        if (!currentInput.empty()) {
                            currentInput.pop_back();
                        }
                    }
                    else if (event.text.unicode < 128) {
                        currentInput += static_cast<char>(event.text.unicode);
                    }

                    // Update displayed user input
                    userInputText.setString(currentInput);
                    window.clear(sf::Color(25, 149, 230));
                    window.draw(promptText);
                    window.draw(userInputText);
                    window.display();
                }
            }

            // If state is 5, i.e., recipe added successfully, break the loop
            if (state == 5) {
                break;
            }
        }

   
        // Tokenize ingredients and steps manually
        vector<string> ingredientTokens;
        size_t pos = 0;
        while ((pos = ingredients.find(',')) != string::npos) {
            ingredientTokens.push_back(ingredients.substr(0, pos));
            ingredients.erase(0, pos + 1);
        }
        ingredientTokens.push_back(ingredients);

        vector<string> stepTokens;
        pos = 0;
        while ((pos = steps.find('\n')) != string::npos) {
            stepTokens.push_back(steps.substr(0, pos));
            steps.erase(0, pos + 1);
        }
        stepTokens.push_back(steps);

        // Create a new recipe and add it to the recipe book
        Recipe* newRecipe = new Recipe(name, ingredientTokens, stepTokens, cookingTime);
        newRecipe->set_cuisine(cuisine);
        recipeBook.add_recipe(newRecipe);

        sf::Text text1;
        text1.setFont(font);
        text1.setCharacterSize(15);
        text1.setFillColor(sf::Color::White);
        text1.setString("Press esc to return to menu");
        text1.setPosition(10, 25);

        // Handle user input
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.clear(sf::Color(25, 149, 230)); // Clear the window before redrawing
                        window.display(); // Display the updated recipe
                        sf::sleep(sf::milliseconds(500)); // Add a small delay to show the message
                        this->showMenu(recipeBook);
                        return;
                    default:
                        break;
                    }
                }
            }
        }
    }

    void deleteRecipe(RecipeBook& recipeBook) {
        window.clear(sf::Color(25, 149, 230));

        sf::Font font;
        if (!font.loadFromFile("Nexa-Heavy.ttf")) {
            // Handle font loading failure
        }

        sf::Text promptText("Select a Recipe to Delete:", font, 30);
        promptText.setPosition(10, 10);

        // Display recipe names
        vector<Recipe*> recipes = recipeBook.getRecipes();
        sf::Text recipeListText("", font, 20);
        recipeListText.setPosition(10, 50);

        // Populate recipeListText with recipe names
        for (size_t i = 0; i < recipes.size(); ++i) {
            recipeListText.setString(recipeListText.getString() + std::to_string(i + 1) + ". " + recipes[i]->get_name() + "\n");
        }

        window.draw(promptText);
        window.draw(recipeListText);
        window.display();

        int selectedRecipe = -1; // Initialize to an invalid index
        sf::Event event;

        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    this->showMenu(recipeBook);
                    return;
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num0) {
                    selectedRecipe = 0;
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
                    // Convert the key code to a recipe index
                    selectedRecipe = event.key.code - sf::Keyboard::Num1;
                }
            }

            // Check if a valid recipe is selected
            if (selectedRecipe >= 0 && static_cast<size_t>(selectedRecipe) < recipes.size()) {
                // Delete the selected recipe
                recipeBook.delete_recipe(static_cast<size_t>(selectedRecipe));

                // Display "Recipe Deleted \n Press esc to Return"
                sf::Text deletedText("Recipe Deleted \n Press esc to Return", font, 30);
                deletedText.setPosition(10, 150);

                window.clear(sf::Color(25, 149, 230));
                window.draw(deletedText);
                window.display();

                // Wait for user to press esc before returning to the main menu
                bool exit = false;
                while (window.isOpen() && !exit) {
                    sf::Event innerEvent;
                    while (window.pollEvent(innerEvent)) {
                        if (innerEvent.type == sf::Event::Closed) {
                            window.close();
                        }
                        else if (innerEvent.type == sf::Event::KeyPressed && innerEvent.key.code == sf::Keyboard::Escape) {
                            exit = true;
                            break;
                        }
                    }
                }

                // Return to the main menu
                this->showMenu(recipeBook);
                return;
            }
        }
    }


private:
    void drawMenu() {

        sf::RectangleShape backgroundRect(sf::Vector2f(window.getSize().x, window.getSize().y));
        backgroundRect.setFillColor(sf::Color(25, 149, 230)); // Blue color
        window.draw(backgroundRect);

        sf::Font font;
        if (!font.loadFromFile("Faster Stroker.otf")) {
            // Handle font loading error
            std::cerr << "Failed to load font." << std::endl;
            return;
        }

        sf::Text title("Recipe Book Menu", font, 50);
        title.setPosition(130, 50);
        window.draw(title);

        std::vector<std::string> options = {
            "1. Add Recipe",
            "2. Display All Recipes",
            "3. Display Recipes by Category",
            "4. Delete Recipe",
            "0. Exit"
        };

        if (!font.loadFromFile("Nexa-Heavy.ttf")) {
            // Handle font loading error
            std::cerr << "Failed to load font." << std::endl;
            return;
        }

        for (size_t i = 0; i < options.size(); ++i) {
            sf::Text option(options[i], font, 40);
            option.setPosition(130, 150 + static_cast<float>(i) * 70);
            window.draw(option);
        }
    }


    sf::RenderWindow& window;
};

int main() {
   

    // Create a RecipeBook
    RecipeBook recipeBook;

    // Add default recipes
    MainCourseRecipe* defaultMainCourse1 = new MainCourseRecipe("Spaghetti Carbonara", { "Spaghetti", "Guanciale", "Pecorino Cheese", "Eggs", "Black Pepper" }, { "Boil spaghetti", "Cook guanciale", "Mix with eggs and cheese", "Add black pepper" }, 25, "Italian");
    MainCourseRecipe* defaultMainCourse2 = new MainCourseRecipe("Chicken Alfredo", { "Fettuccine", "Chicken Breast", "Heavy Cream", "Parmesan Cheese", "Garlic" }, { "Cook fettuccine", "Sauté chicken", "Mix with cream and cheese", "Add garlic" }, 30, "Italian");

    DessertRecipe* defaultDessert1 = new DessertRecipe("Classic Chocolate Cake", { "Flour", "Sugar", "Cocoa Powder", "Baking Powder", "Butter", "Eggs", "Milk", "Vanilla Extract" }, { "Mix dry ingredients", "Cream butter and sugar", "Add eggs and vanilla", "Alternate adding dry ingredients and milk", "Bake in the oven" }, 40, "Cake");
    DessertRecipe* defaultDessert2 = new DessertRecipe("Strawberry Cheesecake", { "Graham Cracker Crust", "Cream Cheese", "Sugar", "Eggs", "Vanilla Extract", "Strawberries" }, { "Prepare crust", "Mix cream cheese, sugar, eggs, and vanilla", "Pour over crust", "Top with strawberries", "Chill in the fridge" }, 45, "Cheesecake");

    recipeBook.add_recipe(defaultMainCourse1);
    recipeBook.add_recipe(defaultMainCourse2);
    recipeBook.add_recipe(defaultDessert1);
    recipeBook.add_recipe(defaultDessert2);


    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Recipe Book Menu");
    Menu menu(window);

    int choice = menu.showMenu(recipeBook);


    return 0;
}