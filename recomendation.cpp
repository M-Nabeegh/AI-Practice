#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class RecommendationSystem {
private:
    unordered_map<string, vector<pair<string, int>>> userPreferences;

public:
    void addUserPreference(const string& user, const string& item, int rating) {
        userPreferences[user].emplace_back(item, rating);
    }

    vector<pair<string, int>> recommendItems(const string& user) {
        vector<pair<string, int>> recommendations;

        // Find similar users (you can use more advanced techniques here)
        for (const auto& entry : userPreferences) {
            if (entry.first != user) {
                // Compare preferences and find similarity
                int similarityScore = calculateSimilarity(userPreferences[user], entry.second);

                // Adjust the threshold as needed
                if (similarityScore > 0) {
                    // Add items from similar users that the current user hasn't rated
                    for (const auto& item : entry.second) {
                        if (!hasUserRatedItem(user, item.first)) {
                            recommendations.emplace_back(item.first, item.second);
                        }
                    }
                }
            }
        }

        // Sort recommendations based on some criteria (e.g., highest rating)
        sort(recommendations.begin(), recommendations.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        return recommendations;
    }

private:
    int calculateSimilarity(const vector<pair<string, int>>& user1, const vector<pair<string, int>>& user2) {
        // Implement a similarity calculation algorithm (e.g., Pearson correlation)
        // This can be a more complex function depending on your requirements
        // For simplicity, let's just return the number of common items
        int commonItems = 0;
        for (const auto& item1 : user1) {
            for (const auto& item2 : user2) {
                if (item1.first == item2.first) {
                    commonItems++;
                    break;
                }
            }
        }
        return commonItems;
    }

    bool hasUserRatedItem(const string& user, const string& item) {
        // Check if the user has rated the item
        for (const auto& userItem : userPreferences[user]) {
            if (userItem.first == item) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    RecommendationSystem recommendationSystem;

    // Add user preferences (user, item, rating)
    recommendationSystem.addUserPreference("User1", "Item1", 5);
    recommendationSystem.addUserPreference("User1", "Item2", 4);
    recommendationSystem.addUserPreference("User2", "Item1", 4);
    recommendationSystem.addUserPreference("User2", "Item3", 5);

    // Get recommendations for a user
    vector<pair<string, int>> recommendations = recommendationSystem.recommendItems("User1");

    // Display recommendations
    cout << "Recommendations for User1:\n";
    for (const auto& recommendation : recommendations) {
        cout << "Item: " << recommendation.first << ", Rating: " << recommendation.second << "\n";
    }

    return 0;
}
